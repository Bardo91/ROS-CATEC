
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
#define PI 3.1415926535897932384626433832795028841971693993751058f

using namespace std;


int kfd = 0;
struct termios cooked, raw;

void quit(int sig) {
			//tcsetattr(kfd, TCSANOW, &cooked);
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
		string qname;

		/// The name of the node is stored in a variable

		qname = string("uav_");

		qname.append(argv[1]);


		ros::init(argc, argv, "posvelcmd");
		ros::NodeHandle n;
		signal(SIGINT, quit);


		ros::Publisher vel_pub;
		ros::Publisher com_pub;

		string path=qname;
		path.append("/flightplan");
		vel_pub = n.advertise<uav::FlightPlan> (path.c_str(), 0);


		path=qname;
		path.append("/commandflags");
		com_pub = n.advertise<uav::CommandFlags> (path.c_str(), 0);


		uav::FlightPlan fp;
		uav::CommandFlags cf;

		while (true)
		{
			int i = 0;
			cout << "tipo de comando (0 = commandflag, 1 = flightplan) " << endl;
			cin >> i;
			if(i == 0)
			{
				cout << "Ha elegido CommandFlag, teclee 0 para despegar y 1 para aterrizar" << endl;
				cin >> i;
				if (i == 0)
				{
					cf.flags[0] = 1;
					cf.flags[1] = 0;
				}
				else if (i == 1)
				{
					cf.flags[0] = 0;
					cf.flags[1] = 1;
				}
				com_pub.publish(cf);
			}
			else if (i == 1)
			{
				double x,y,z,yaw, v;
				cout << "Ha elegido Flightplan, teclee el destino X Y Z YAW" << endl;
				cin >> x >> y >> z >> yaw;
				fp.position[0].x = x;
				fp.position[0].y = y;
				fp.hFlightPlan = fp.position[0].z = z;
				fp.courseFlightPlan = 0;
				fp.modeFp = fp.POSITIONHEADINGMODEWITHVELOCITY;
				fp.header.frame_id = "qtester";
				cout << "Teclee la velocidad" << endl;
				cin >> v;
				fp.velFlightPlan = v;
				fp.headingFlightPlan = yaw;

				vel_pub.publish(fp);
			}
		}


}
