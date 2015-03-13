/*
 * takeoff.cpp
 *
 *  Created on: 26/11/2012
 *      Author: catec
 */

#include <ros/ros.h>
#include <signal.h>
#include <iostream>
#include "takeoff_land/actions.h"


void quit(int sig) {
	ros::shutdown();
	exit(0);
}

int main(int argc, char** argv)
{
	string node_name="takeoff_land_";
	string uavID="uav_";

	if (argc < 2)
	{
		cout << "This program has one inputs parameters.\n"<< endl <<
				"The first input parameter is id of uav." << endl;
		return -1;
	}

	signal(SIGINT, quit);

	node_name.append(string(argv[1]));
	uavID.append(string(argv[1]));

	ros::init(argc, argv, node_name.c_str());

	ros::NodeHandle n;

	string action_name = uavID;
	action_name.append("/land_action");
	cLand = new LandClient(action_name,true);

	action_name = uavID;
	action_name.append("/take_off_action");
	cTakeOff = new TakeOffClient(action_name,true);

	TakeOffGoal tOff_goal;
	LandGoal land_goal;

	ROS_INFO("Waiting for all servers...");
	cLand->waitForServer();
	cTakeOff->waitForServer();
	ROS_INFO("All servers OK.");

	int quit_=-1;
	while(ros::ok())
		{


			do{
				cout << "To send land insert 0, to takeoff insert 1, to quit insert 2" << endl;
				cin >> quit_;
			}while(quit_!=0 && quit_!=1 && quit_!=2);

			if(quit_==2)
				break;

			switch(quit_)
			{
			case 0:

				cLand->sendGoal(land_goal, &land_Done_CB, &land_Active_CB, &land_Feedback_CB);

				break;
			case 1:

				cTakeOff->sendGoal(tOff_goal, &tOff_Done_CB, &tOff_Active_CB, &tOff_Feedback_CB);
				break;
			default:
				break;
			}

			usleep(1000);
		}
}


