/*
 * arbitrer.cpp
 *
 *  Created on: Aug 30, 2012
 *      Author: catec
 */

#include <ros/ros.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>

#include <uav/CommandFlags.h>
#include <uav/FlightPlan.h>


using namespace std;

ros::Publisher pubFlightPlan;
ros::Publisher pubCommandFlags;

void FlightPlanCallback(const uav::FlightPlan::ConstPtr& fp) {

	pubFlightPlan.publish(*fp);
}


void CommandFlagsCallback(const uav::CommandFlags::ConstPtr& cm) {
	pubCommandFlags.publish(*cm);
}

int main(int argc, char** argv) {

	/**
	 * \brief The first argument for the executable is the name of the executable ("quad" in this case).
	 * The second argument is the number of the quadrotor.
	 * The third argument is the path to the qos file.
	 *
	 * If the number of arguments is less than three, the input arguments are wrong.
	 *
	 */
	if (argc < 2)
	{
		cout << "This program has one input parameter.\n"<<
				"The first input parameter is the number of the quadrotor." << endl;
		return -1;
	}


	// The quad ID is stored in a global variable
	stringstream qname;
	qname << "quad" << string(argv[1]);

	stringstream name;
	name << "arbitrer" << string(argv[1]);

	int quadID = atoi(string(argv[1]).c_str());

	cout << "quad " << quadID << endl;

	ros::init(argc, argv, name.str());
	ros::NodeHandle n;


	string topicname = qname.str();
	topicname.append("/flying");
	bool b;
	ros::param::get(topicname.c_str(), b);
	if (!b)
	{
		cout << "parameter " << topicname << " not configured.\n" << endl;
		return -1;
	}

	topicname = qname.str();
	topicname.append("/flightplan");

	pubFlightPlan = n.advertise<uav::FlightPlan> (topicname.c_str(), 0);

	topicname = name.str();
	topicname.append("/flightplan");

	ros::Subscriber subFlightPlan = n.subscribe(topicname.c_str(), 0, FlightPlanCallback);

	topicname = qname.str();
	topicname.append("/commandflags");

	pubCommandFlags = n.advertise<uav::CommandFlags> (topicname.c_str(), 0);

	topicname = name.str();
	topicname.append("/commandflags");

	ros::Subscriber subCommandFlags = n.subscribe(topicname.c_str(), 0, CommandFlagsCallback);

	ros::spin();
}
