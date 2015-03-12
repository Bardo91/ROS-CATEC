/*
 * position_in.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: catec-ros
 */

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

using namespace std;




int main(int argc, char** argv)
{
	double x,y,z;
	ros::init(argc,argv,"position_in");

	ros::NodeHandle n;



	string topicname = "uav_1/flightplan";
	ros::Publisher stagevel_pub = n.advertise<geometry_msgs::Twist> (topicname.c_str(), 0);



	while(ros::ok())
	{
		ROS_INFO("position_in initiated...");

		cout << "Insert x position:" << endl;

		scanf("%f",x);

		cout << "Insert y position:" << endl;
		scanf("%f",y);

		cout << "Insert z position:" << endl;
		scanf("%f",z);

		uav::FlightPlan fp;
		fp.header.frame_id  = "qtester";
		fp.header.stamp  = ros::Time::now();
		fp.header.seq	=	++counter;
		fp.modeFp = fp.POSITIONHEADINGMODEWITHVELOCITY;
		fp.position[0].x = x;
		fp.position[0].y = y;
		fp.position[0].z = z;
		fp.position[1].z = z;
		fp.position[2].z = z;
		fp.weight = 1.0f;
		fp.velFlightPlan = 1;
		fp.hFlightPlan = 1;
		fp.courseFlightPlan = 0;
		fp.headingFlightPlan = 0;

		stagevel_pub.publish(fp);


	}


	return 0;
}


