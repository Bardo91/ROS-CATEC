/*
 * tester.cpp
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


/**
 * This executable creates a lot of dummy commandflags and flightplans sent to test the arbitrer.
 */

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
	stringstream name;
	name << "test" << string(argv[1]);

	stringstream aname;
	aname << "arbitrer" << string(argv[1]);

	int quadID = atoi(string(argv[1]).c_str());


	ros::init(argc, argv, name.str());
	ros::NodeHandle n;

	string topicname = aname.str();
	topicname.append("/flightplan");

	pubFlightPlan = n.advertise<uav::FlightPlan> (topicname.c_str(), 0);


	topicname = aname.str();
	topicname.append("/commandflags");

	pubCommandFlags = n.advertise<uav::CommandFlags> (topicname.c_str(), 0);
	int counter = 0;

	while(ros::ok())
	{
		uav::CommandFlags cf;

		cf.header.frame_id = name.str();
		cf.header.stamp = ros::Time::now();
		cf.header.seq = ++counter;
		cf.flags[0] = 1;
		cf.flags[1] = cf.flags[2] = cf.flags[3] = cf.flags[4] = cf.flags[5] = cf.flags[6] = cf.flags[7] = 0;
		pubCommandFlags.publish(cf);

		uav::FlightPlan fp;
		fp.header.frame_id = name.str();
		fp.header.stamp = ros::Time::now();
		fp.header.seq = ++counter;
		fp.modeFp = fp.POSITIONHEADINGMODEWITHVELOCITY;

		fp.position[0].x = 0;
		fp.position[0].y = 0;
		fp.position[0].z = 0.5f;

		fp.weight = 1.0f;
		fp.velFlightPlan = 3;
		fp.hFlightPlan = 0.5;
		fp.courseFlightPlan = 0;
		fp.headingFlightPlan = 0;
		pubFlightPlan.publish(fp);


		ros::spinOnce();
		usleep(100000);
	}

}
