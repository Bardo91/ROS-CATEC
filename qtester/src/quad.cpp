#include "ros/ros.h"
#include "turtlesim/TeleportAbsolute.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <time.h>

#include <uav/Position.h>
#include <uav/Rotation.h>
#include <uav/Space_Configuration.h>
#include <uav/Velocity.h>
#include <uav/Battery.h>
#include <uav/Error.h>
#include <uav/CommandFlags.h>
#include <qtester/Move.h>
#include <qtester/Land.h>
#include <uav/FlightPlan.h>
using namespace std;

ros::ServiceClient* ptrClient = NULL;
ros::Publisher* ptrPubFlightplan = NULL;
ros::Publisher* ptrPubCommandFlags = NULL;

uav::Position actualPos;
uav::Rotation actualRot;


/**
 * A count of how many messages we have sent. This is used to create
 * a unique string for each message.
 */
unsigned int counter = 0;

/*!
 * \brief The name of the quadrotor node. It will be something like "/quad7/"
 */
string name;

/*!
 * \brief Armonizes a ROS name, deleting the '/' character of the first and last letters if it exists.
 * \param id The string to be armonized. As it is passed by reference, the parameter is used as input as well as output parameter.
 */
void getID(string& id) {
	if (id.empty())
		return;
	if (id.at(0) == '/')
		id.erase(0, 1);
	if (id.length() > 0 && id.at(id.length() - 1) == '/') {
		id.erase(id.length() - 1, 1);
	}

}

/*!
 * \brief The callback function to call when a Position packet is received.
 * \param fp The Position.
 */
void PositionCallback(const uav::Position::ConstPtr& fp) {

	if(ptrClient)
	{
		turtlesim::TeleportAbsolute srv;
		srv.request.x = fp->position.x+5;
		srv.request.y = fp->position.y+5;
		srv.request.theta = 0.0f;
		ptrClient->call(srv);
	}
	actualPos.position.x = fp->position.x;
	actualPos.position.y = fp->position.y;
	actualPos.position.z = fp->position.z;

	/*cout << "Position:" << endl;
	cout << fp->header.seq << ", " << fp->header.stamp.sec << ", "
			<< fp->header.stamp.nsec << ", " << fp->header.frame_id << endl;
	printf("%i, %i\n", fp->status, fp->quality);
	cout << fp->position.x << ", " << fp->position.y << ", " << fp->position.z
			<< endl;*/

	return;
}

/*!
 * \brief The callback function to call when a Rotation packet is received.
 * \param fp The Rotation.
 */
void RotationCallback(const uav::Rotation::ConstPtr& fp) {

	actualRot.rotation.x = fp->rotation.x;
	actualRot.rotation.y = fp->rotation.y;
	actualRot.rotation.z = fp->rotation.z;
	/*cout << "Rotation:" << endl;
	cout << fp->header.seq << ", " << fp->header.stamp.sec << ", "
			<< fp->header.stamp.nsec << ", " << fp->header.frame_id << endl;
	printf("%i, %i\n", fp->status, fp->quality);
	cout << fp->rotation.x << ", " << fp->rotation.y << ", " << fp->rotation.z
			<< endl;*/

	return;
}

/*!
 * \brief The callback function to call when a Velocity packet is received.
 * \param fp The Velocity.
 */
void VelocityCallback(const uav::Velocity::ConstPtr& fp) {
	/*cout << "Velocity:" << endl;
	cout << fp->header.seq << ", " << fp->header.stamp.sec << ", "
			<< fp->header.stamp.nsec << ", " << fp->header.frame_id << endl;
	printf("%i, %i\n", fp->status, fp->quality);
	cout << fp->velocity.x << ", " << fp->velocity.y << ", " << fp->velocity.z
			<< endl;*/

	return;
}

/*!
 * \brief The callback function to call when a Battery packet is received.
 * \param fp The Battery.
 */
void BatteryCallback(const uav::Battery::ConstPtr& fp) {
	/*cout << "Battery:" << endl;
	cout << fp->header.seq << ", " << fp->header.stamp.sec << ", "
			<< fp->header.stamp.nsec << ", " << fp->header.frame_id << endl;
	printf("%i, %i\n", fp->status, fp->quality);
	cout << fp->voltage << ", " << fp->current << endl;*/

	return;
}

/*!
 * \brief The callback function to call when a Configuration packet is received.
 * \param fp The Configuration.
 */
void ConfigurationCallback(const uav::Space_Configuration::ConstPtr& fp) {
	/*cout << "Configuration:" << endl;
	cout << fp->header.seq << ", " << fp->header.stamp.sec << ", "
			<< fp->header.stamp.nsec << ", " << fp->header.frame_id << endl;
	cout << fp->scalar.x << ", " << fp->scalar.y << ", " << fp->scalar.z
			<< endl;
	cout << fp->northAngle << ", " << fp->utmLongitude << ", "
			<< fp->utmLatitude << ", " << fp->utmHeight << endl;*/

	return;
}

/*!
 * \brief The callback function to call when an Error packet is received.
 * \param fp The Error.
 */
void ErrorCallback(const uav::Error::ConstPtr& fp) {

	return;
}

/**
 * If Land::land == 0, it will send a motors on command, else it will send a land command.
 */
void CommandFlagsCallback(const qtester::Land::ConstPtr& ld) {
	if(ptrPubCommandFlags)
	{
		uav::CommandFlags cf;
		cf.header.frame_id = ld->nodename;
		cf.header.stamp  = ros::Time::now();
		counter++;
		cf.header.seq=counter;
		cout << "Received commandflag land =  " << ld->land  << endl;
		if(ld->land>0)
			cf.flags[1] = 1;
		else
			cf.flags[0] = 1;
		ptrPubCommandFlags->publish(cf);
	}
	return;
}

/*!
 * \brief The function to call when a FlightPlan is received. It will send the flightplan command to the QNX server through DDS.
 * \param fp The FlightPlan command.
 */
void FlightPlanCallback(const qtester::Move::ConstPtr& mv) {

	if(ptrPubFlightplan)
	{
		uav::FlightPlan fp;
		fp.header.frame_id  = "qtester";
		fp.header.stamp  = ros::Time::now();
		fp.header.seq	=	++counter;
		fp.modeFp = fp.POSITIONHEADINGMODE;
		fp.position[0].x = mv->x;
		fp.position[0].y = mv->y;
		fp.position[0].z = 1.0f;
		fp.weight = 1.0f;
		fp.velFlightPlan = 1.0f;
		fp.hFlightPlan = 1.0f;
		fp.courseFlightPlan = 1.0f;
		fp.headingFlightPlan = 0.0f;
		ptrPubFlightplan->publish(fp);
		cout << "Received flightplan position: " << mv->x << ", " << mv->y  << endl;
	}
	return;
}


int main(int argc, char **argv) {


	if (argc < 2)
	{
		cout << "This program has one input parameter.\n"<<
				"The first input parameter is the number of the quadrotor." << endl;
		return -1;
	}
	name = string("quad");
	name.append(argv[1]);
	/*!
	 * The ros::init() function needs to see argc and argv so that it can perform
	 * any ROS arguments and name remapping that were provided at the command line. For programmatic
	 * remappings you can use a different version of init() which takes remappings
	 * directly, but for most command-line programs, passing argc and argv is the easiest
	 * way to do it.  The third argument to init() is the name of the node.
	 *
	 * You must call one of the versions of ros::init() before using any other
	 * part of the ROS system.
	 */
	ros::init(argc, argv, "qtester");

	/**
	 * NodeHandle is the main access point to communications with the ROS system.
	 * The first NodeHandle constructed will fully initialize this node, and the last
	 * NodeHandle destructed will close down the node.
	 */
	ros::NodeHandle n;

	ros::ServiceClient foo = n.serviceClient<turtlesim::TeleportAbsolute>("/turtlesim1/turtle1/teleport_absolute");
	ptrClient = &foo;



	string topicname = name;
	topicname.append("/position");

	ros::Subscriber subPosition = n.subscribe(topicname.c_str(), 0,
			PositionCallback);

	topicname = name;
	topicname.append("/rotation");

	ros::Subscriber subRotation = n.subscribe(topicname.c_str(), 0,
			RotationCallback);

	topicname = name;
	topicname.append("/velocity");

	ros::Subscriber subVelocity = n.subscribe(topicname.c_str(), 0,
			VelocityCallback);

	topicname = name;
	topicname.append("/battery");

	ros::Subscriber subBattery = n.subscribe(topicname.c_str(), 0,
			BatteryCallback);

	topicname = name;
	topicname.append("/configuration");

	ros::Subscriber subConfiguration = n.subscribe(topicname.c_str(), 0,
			ConfigurationCallback);

	topicname = name;
	topicname.append("/error");
	ros::Subscriber subError = n.subscribe(topicname.c_str(), 0,
			ErrorCallback);

	topicname = name;
	topicname.append("/flightplan");

	ros::Publisher pubFlightplan = n.advertise<uav::FlightPlan> (
			topicname.c_str(), 0);
	ptrPubFlightplan = &pubFlightplan;


	topicname = name;
	topicname.append("/commandflags");

	ros::Publisher pubCommandFlags = n.advertise<uav::CommandFlags> (
			topicname.c_str(), 0);
	ptrPubCommandFlags = &pubCommandFlags;


	ros::Subscriber subFlightPlan = n.subscribe("qtester/flightplan", 0,
			FlightPlanCallback);

	ros::Subscriber subCommandFlags = n.subscribe("qtester/commandflags", 0,
			CommandFlagsCallback);

	ros::Rate loop_rate(10);


	/**
	 * This is a message object. You stuff it with data, and then publish it.
	 */

	sleep(1);

	uav::FlightPlan fp;
	uav::CommandFlags cf;
	fp.header.frame_id = cf.header.frame_id = "qtester";

	/**
	 * We send a first command to start motors.
	 */
	fp.header.seq=cf.header.seq=counter;
	fp.modeFp = fp.POSITIONMODE;

	fp.weight = 1.0f;
	fp.velFlightPlan = 1.0f;
	fp.hFlightPlan = 1.0f;
	fp.courseFlightPlan = 1.0f;
	fp.headingFlightPlan = actualRot.rotation.z;
	fp.position[0].x = actualPos.position.x;
	fp.position[0].y = actualPos.position.y;
	fp.position[0].z = 1.0f;

	cf.flags[0] = 1;
	fp.header.stamp = ros::Time::now();
	//pubFlightplan.publish(fp);

	sleep(1);

	cf.header.stamp = ros::Time::now();
	//pubCommandFlags.publish(cf);
	//printf("Sent commandflag seq %i", cf.header.seq);
	++counter;


	ros::MultiThreadedSpinner spinner(4);
	spinner.spin();

/*
	while (ros::ok()) {


		fp.header.stamp = cf.header.stamp = ros::Time::now();
		fp.header.seq=cf.header.seq=count;

		cf.flags[0] = 1;

		fp.modeFp = fp.POSITIONMODE;

		fp.position[0].x = 3.5f;
		fp.position[0].y = 4.5f;
		fp.position[0].z = 0.5f;

		fp.weight = 1.0f;
		fp.velFlightPlan = 1.0f;
		fp.hFlightPlan = 1.0f;
		fp.courseFlightPlan = 1.0f;
		fp.headingFlightPlan = 1.0f;

		//pubFlightplan.publish(fp);
		//pubCommandFlags.publish(cf);
		//printf("Sent commandflag seq %i\n", cf.header.seq);

		ros::spinOnce();

		loop_rate.sleep();

		++count;
	}*/

	return 0;
}
