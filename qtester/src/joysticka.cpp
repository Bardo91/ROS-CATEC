/*
 * joysticka.cpp
 *
 *  Created on: Sept 4, 2012
 *      Author: catec
 */

#include "joystick.h"


int CJoystick::open_joystick() {
	joystick_fd = open(JOYSTICK_DEVNAME, O_RDONLY | O_NONBLOCK); /* read write for force feedback? */
	if (joystick_fd < 0)
		return joystick_fd;

	/* maybe ioctls to interrogate features here? */

	return joystick_fd;
}

int CJoystick::read_joystick_event(struct js_event *jse) {
	int bytes;

	bytes = read(joystick_fd, jse, sizeof(*jse));

	if (bytes == -1)
		return 0;

	if (bytes == sizeof(*jse))
		return 1;

	printf("Unexpected bytes from joystick:%d\n", bytes);

	return -1;
}

void CJoystick::close_joystick() {
	close(joystick_fd);
}

int CJoystick::get_joystick_status(struct wwvi_js_event* wjse) {
	int rc;
	struct js_event jse;
	if (joystick_fd < 0)
		return -1;

	// memset(wjse, 0, sizeof(*wjse));
	while ((rc = read_joystick_event(&jse) == 1)) {
		jse.type &= ~JS_EVENT_INIT; /* ignore synthetic events */
		if (jse.type == JS_EVENT_AXIS) {
			switch (jse.number) {
			case 0:
				wjse->stick_x = jse.value;
				break;
			case 1:
				wjse->stick_y = jse.value;
				break;
			case 2:
				wjse->stick_x = jse.value;
				break;
			case 3:
				wjse->stick_y = jse.value;
				break;
			default:
				break;
			}
		} else if (jse.type == JS_EVENT_BUTTON) {
			if (jse.number < 10) {
				switch (jse.value) {
				case 0:
				case 1:
					wjse->button[jse.number] = jse.value;
					break;
				default:
					break;
				}
			}
		}
	}
	// printf("%d\n", wjse->stick1_y);
	return 0;
}


Teleop::Teleop(string nquad) :
	name(nquad), vx(0), vy(0), h(1.5), heading(0), x(0), y(0), counter(0)  {

	string path = name;
	path.append("/flightplan");
	vel_pub_ = nh_.advertise<uav::FlightPlan> (path.c_str(), 0);

	path = name;
	path.append("/commandflags");
	com_pub_ = nh_.advertise<uav::CommandFlags> (path.c_str(), 0);



}

void quit(int sig) {
	ros::shutdown();
	exit(0);
}

int main(int argc, char** argv) {

	if (argc < 2) {
		cout << "This program has one input parameter.\n"
				<< "The first input parameter is the number of the quadrotor."
				<< endl;
		return -1;
	}

	// Auxiliary variable
	string name;

	/// The name of the node is stored in a variable

	name = string("arbitrer");

	name.append(argv[1]);

	ros::init(argc, argv, "joysticka");
	Teleop teleop_quad(name);

	signal(SIGINT, quit);

	teleop_quad.keyLoop();

	return (0);
}

void Teleop::keyLoop() {
	bool dirty = false;

	ros::Time start = ros::Time::now();

	puts("Reading from joystick");
	puts("---------------------------");

	int fd, rc;
	int done = 0;

	struct js_event jse;
	CJoystick joystick;

	fd = joystick.open_joystick();
	if (fd < 0) {
		printf("open failed.\n");
		exit(1);
	}
	//We'll send the flightplan with heading at 10Hz if trigger is activated
	int sendheading = 0;
	while (!done) {
		rc = joystick.read_joystick_event(&jse);
		usleep(1000);
		sendheading++;
		heading +=headingvel/4000;
		if(heading > PI)
		{	heading += -2*PI;}
		if(heading < -PI)
		{	heading += 2*PI; }
		if(sendheading > 99)
		{
			sendheading = 0;
		}


		if (rc == 1) {
			printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n",
					jse.time, jse.value, jse.type, jse.number);
			switch (jse.number) {
			case 0:
				if (jse.type == 2) {
					vy = -1.41 * ((double) jse.value) / 32767.0f;
					dirty = true;
					cout << "vy: " << vy << endl;
				}
				else if (jse.type == 1) {
					trigger = jse.value;
					if (!trigger)
						headingvel = 0;
					cout << "trigger: " << trigger << endl;
				}
				break;
			case 1:
				if (jse.type == 2) {
					vx = -1.41 * ((double) jse.value) / 32767.0f;
					dirty = true;
					cout << "vx: " << vx << endl;
				}
				break;
			case 2:
				if (jse.type == 2 && trigger) {
					headingvel = -PI * ((double) jse.value) / 32767.0f;
					dirty = true;
					cout << "headingvel: " << headingvel << " heading: " << heading << endl;
				}
				break;
			case 3:
				if (jse.type == 2) {
					h = 20*abs(-2 * ((double) jse.value - 32767) / 65534.0f);
					if(h < 0.3)
					{
						h = 0.3;
					}
					dirty = true;
					cout << "h: " << h << endl;
				}
				break;
			case 6:
				if (jse.type == 1 && jse.value == 1) {

					uav::CommandFlags cf;
					cf.header.frame_id = "qtester";
					cf.header.stamp  = ros::Time::now();
					counter++;
					cf.header.seq=counter;
					cf.flags[0] = 1;
					com_pub_.publish(cf);
					cout << "Take off" << endl;
				}
				break;
			case 10:
				if (jse.type == 1 && jse.value == 1) {

					uav::CommandFlags cf;
					cf.header.frame_id = "qtester";
					cf.header.stamp  = ros::Time::now();
					counter++;
					cf.header.seq=counter;
					cf.flags[1] = 1;
					com_pub_.publish(cf);
					cout << "Land" << endl;
				}
				break;
			}

		}


		if (dirty == true || (sendheading == 1 && trigger) ) {
			uav::FlightPlan fp;
			fp.header.frame_id = "qtester";
			fp.header.stamp = ros::Time::now();
			fp.header.seq = ++counter;
			fp.modeFp = fp.VELOCITYHEADINGMODE;
			/*fp.position[0].x = 0;
			fp.position[0].y = 0;
			fp.position[0].z = 1.0f;
			fp.position[1].z = 1.0f;
			fp.position[2].z = 1.0f;*/
			fp.weight = 1.0f;
			fp.velFlightPlan = sqrt(vx * vx + vy * vy);
			fp.hFlightPlan = h;
			//fp.hFlightPlan = 1.5;
			if(fp.velFlightPlan>0)
				fp.courseFlightPlan = atan2(vy, vx);
			else
				fp.courseFlightPlan = 0;
			fp.headingFlightPlan = heading;
			vel_pub_.publish(fp);
			dirty = false;

			if (sendheading == 1 && trigger)
				cout << "headingvel: " << headingvel << " heading: " << heading << endl;
		}
	}

}
