/*
 * send_WayPointWithCruiseStamped.cpp
 *
 *  Created on: 23/11/2012
 *      Author: catec
 */
#include <ros/ros.h>
#include <signal.h>
#include <iostream>

#include <catec_msgs/WayPointWithCruiseStamped.h>

using namespace std;
using namespace catec_msgs;

void quit(int sig) {
	ros::shutdown();
	exit(0);
}

int main(int argc, char** argv)
{
	string node_name;

	if (argc < 2)
	{
		cout << "This program has one inputs parameters.\n"<< endl <<
				"The first input parameter isname of node." << endl;
		return -1;
	}

	signal(SIGINT, quit);

	node_name = string(argv[1]);
	ros::init(argc, argv, node_name.c_str());

	ros::NodeHandle n;

	string topicname;
	cout << "Insert Pusblish name like '/uav_1/in_waypoint':" << endl;
	cin >> topicname;

	cout << endl << "This node will publish WayPointWithCruiseStamped messages in topic " << topicname << endl;

	ros::Publisher my_waypoint_pub = n.advertise<WayPointWithCruiseStamped> (topicname.c_str(), 0);

	WayPointWithCruiseStamped wp;
	wp.header.frame_id = node_name;
	int quit_=-1;
	while(ros::ok())
	{


		do{
			cout << "To send waypoint insert 0, to quit insert 1" << endl;
			cin >> quit_;
		}while(quit_!=0 && quit_!=1);

		if(quit_==1)
			break;


		cout << "Insert x position:" << endl;
		cin >> wp.way_point.x;

		cout << "Insert y position:" << endl;
		cin >> wp.way_point.y;

		cout << "Insert z position:" << endl;
		cin >> wp.way_point.z;

		cout << "Insert cruise velocity:" << endl;
		cin >> wp.way_point.cruise;

		wp.header.seq++;
		wp.header.stamp = ros::Time::now();

		my_waypoint_pub.publish(wp);

		usleep(1000);
	}

	return 0;
}
