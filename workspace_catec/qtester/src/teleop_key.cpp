/*
 * teleop_key.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: catec
 */

#include <ros/ros.h>
#include <signal.h>
#include <termios.h>
#include <uav/FlightPlan.h>
#include <uav/CommandFlags.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <iostream>

#define KEYCODE_R 0x43
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
//#define KEYCODE_Q 0x71
#define KEYCODE_W 119
#define KEYCODE_S 115
#define KEYCODE_Q 113
#define KEYCODE_E 101
#define KEYCODE_SPACE 32
#define KEYCODE_ENTER 10
#define PI 3.141592

using namespace std;

class Teleop {
public:
	Teleop(string nquad);
	void keyLoop();

private:

	void calc()
	{
		vx = abs(mod)*cos(ang);
		vy = abs(mod)*sin(ang);
	}
	string name;
	double vx, vy, h, heading, mod, ang;
	unsigned int counter;
	ros::NodeHandle nh_;
	ros::Publisher vel_pub_;
	ros::Publisher com_pub_;

};

Teleop::Teleop(string nquad):
	name(nquad),vx(0),vy(0),h(1), heading(0), mod(0), ang(0),counter(0) {

	string path=name;
	path.append("/flightplan");
	vel_pub_ = nh_.advertise<uav::FlightPlan> (path.c_str(),
			0);

	path = name;
	path.append("/commandflags");
	com_pub_ = nh_.advertise<uav::CommandFlags> (path.c_str(), 0);



}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig) {
	tcsetattr(kfd, TCSANOW, &cooked);
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

	name = string("uav_");

	name.append(argv[1]);


	ros::init(argc, argv, "teleop_key");
	Teleop teleop_quad(name);

	signal(SIGINT, quit);

	teleop_quad.keyLoop();

	return (0);
}

void Teleop::keyLoop() {
	char c;
	bool dirty = false;

	// get the console in raw mode
	tcgetattr(kfd, &cooked);
	memcpy(&raw, &cooked, sizeof(struct termios));
	raw.c_lflag &= ~(ICANON | ECHO);
	// Setting a new line, then end of file
	raw.c_cc[VEOL] = 1;
	raw.c_cc[VEOF] = 2;
	tcsetattr(kfd, TCSANOW, &raw);
	float vmax = 1;

	puts("Reading from keyboard");
	puts("---------------------------");
	puts("Use arrow keys to move the quadrotor.");

	for (;;) {
		// get the next event from the keyboard
		if (read(kfd, &c, 1) < 0) {
			perror("read():");
			exit(-1);
		}

		ROS_DEBUG("value: 0x%02X\n", c);
		//cout << (int)c << endl;

		switch (c) {
		case KEYCODE_L:
			ROS_DEBUG("Y+");


			ang += 0.04;


			dirty = true;
			break;
		case KEYCODE_R:
			ROS_DEBUG("Y-");


			ang -= 0.04;

			dirty = true;
			break;
		case KEYCODE_U:
			ROS_DEBUG("X+");
			if(mod <= vmax )
			{
				mod += 0.04;
			}
			dirty = true;
			break;
		case KEYCODE_D:
			ROS_DEBUG("X-");
			if(mod >= 0.04 )
			{
				mod -= 0.04;
			}
			dirty = true;
			break;
		case KEYCODE_W:
			ROS_DEBUG("Z+");
			if(h<2)
			{
				h += 0.08f;
			}
			dirty = true;
			break;
		case KEYCODE_S:
			ROS_DEBUG("Z-");
			if(h>0.5)
			{
				h -= 0.08f;
			}
			dirty = true;
			break;

		case KEYCODE_SPACE:
			{
				ROS_DEBUG("Take off");
				uav::CommandFlags cf;
				cf.header.frame_id = "qtester";
				cf.header.stamp = ros::Time::now();
				cf.header.seq = ++counter;
				cf.flags[0] = 1;
				cf.flags[1] = cf.flags[2] = cf.flags[3] = cf.flags[4] = cf.flags[5] = cf.flags[6] = cf.flags[7] = 0;

				com_pub_.publish(cf);
			}
			break;
		case KEYCODE_ENTER:
			{
				ROS_DEBUG("Land");
				uav::CommandFlags cf;
				cf.header.frame_id = "qtester";
				cf.header.stamp = ros::Time::now();
				cf.header.seq = ++counter;
				cf.flags[1] = 1;
				cf.flags[0] = cf.flags[2] = cf.flags[3] = cf.flags[4] = cf.flags[5] = cf.flags[6] = cf.flags[7] = 0;

				com_pub_.publish(cf);
			}
			break;

		}



		if (dirty == true) {
			uav::FlightPlan fp;
			calc();
			fp.header.frame_id  = "qtester";
			fp.header.stamp  = ros::Time::now();
			fp.header.seq	=	++counter;
			fp.modeFp = fp.VELOCITYHEADINGMODE;
			fp.position[0].x = 0;
			fp.position[0].y = 0;
			fp.position[0].z = 1.0f;
			fp.position[1].z = 1.0f;
			fp.position[2].z = 1.0f;
			fp.weight = 1.0f;
			fp.velFlightPlan = mod;
			fp.hFlightPlan = h;
			fp.courseFlightPlan = ang;
			fp.headingFlightPlan = ang;

			/*uav::FlightPlan fp;
			calc();
			fp.header.frame_id  = "qtester";
			fp.header.stamp  = ros::Time::now();
			fp.header.seq	=	++counter;
			fp.modeFp = fp.POSITIONHEADINGMODE;
			fp.position[0].x = 5;
			fp.position[0].y = 5;
			fp.position[0].z = 1.0f;
			fp.position[1].z = 1.0f;
			fp.position[2].z = 1.0f;
			fp.weight = 1.0f;
			fp.velFlightPlan = 2;
			fp.hFlightPlan = h;
			fp.courseFlightPlan = ang;
			fp.headingFlightPlan = ang;*/

			vel_pub_.publish(fp);
			dirty = false;
		}
	}

	return;
}

