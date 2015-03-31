/*************************************************************************
 *
 * FADA-CATEC
 * __________________
 *
 *  [2013] FADA-CATEC
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of FADA-CATEC and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to FADA-CATEC
 * and its suppliers and may be covered by Europe and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from FADA-CATEC.
 *
 * Created on: 23-Oct-2012
 * Engineer: Jonathan Ruiz Páez
 * Email: jruiz@catec.aero
 */
#include <ros/ros.h>
#include <iostream>

#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/ControlReferenceRwStamped.h>
#include <actionlib/server/action_server.h>
#include<common.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>

#define PI 3.1415926535897932384626433832795028841971693993751058f
using namespace std;
using namespace geometry_msgs;


/*TODO: De momento solo está integrado el real, ya que no hay control y solo se lee el estado
	del vehículo, en principio no hay mayor problema, pero sería buena idea generar uno
	simulado para poder usarlo en las simulaciones de los experimentos en gazebo */

/*!
 * \brief The number of the UGV node. Its range will be 0 to 15.
 */
string ugvID;
int ugvIntID;

/*!
 * \brief Type of the UAV node. 1: Rw; 2: Fw.
 */
string ugvType;

/*!
 * \brief Last pose of UAV, should be updated by link function.
 */
geometry_msgs::Pose lastPose;

/*!
 * \brief Last velocity of UAV, should be updated by link function.
 */
Twist lastVel;


/*!
 * \brief Last control reference received
 */
catec_msgs::ControlReferenceRwStamped lastControlReferenceRw;
//catec_msgs::ControlReferenceFwStamped lastControlReferenceFw;

/*!
 * \brief Time where receive commandFlag.
 */
ros::Time cmdFlagTime;
ros::Duration cmdFlagDuration;


//Frequency of the main loop
double timerate = 50;

/*
 * Implemented in simulation_functions.cpp/real_functions.cpp
 * */
void ControlReferencesRwCallback(const catec_msgs::ControlReferenceRwStamped::ConstPtr& fp);

//void ControlReferencesFwCallback(const catec_msgs::ControlReferenceFwStamped::ConstPtr& fp);



#include "link/qnx_lineTracker.cpp"




void ControlReferencesRwCallback(const catec_msgs::ControlReferenceRwStamped::ConstPtr& fp)
{
	
		lastControlReferenceRw = *fp;

	
}
/*
void ControlReferencesFwCallback(const catec_msgs::ControlReferenceFwStamped::ConstPtr& fp)
{
	if(actual_state==FLYING)
	{
		lastControlReferenceFw = *fp;
	}
}*/



int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "This program has two input parameter.\n"<<
				"The first input parameter is the number of the UGV." << endl <<
				"The second input parameter is the type of the UGV." << endl;
		return -1;
	}

	// The UGV ID is stored in a global variable
	ugvID="ugv_";
	ugvID.append(string(argv[1]));

	ugvType = string(argv[2]);
	if(ugvType == "1"){
		cout << "UGV type: Rw;" << endl;
	}else if(ugvType == "2"){
		cout << "UGV type: Fw;" << endl;
	}else
	{
		cout << "Unknow ugv type;" << endl;
		return 1;
	}
		try
	{
		ugvIntID = boost::lexical_cast<int>(argv[1]);
	}
	catch(boost::bad_lexical_cast const&)
	{
		perror("The first argument is not a number.");
		return 1;
	}

	lastPose.position.x = -5;
	lastPose.position.y = ugvIntID -3;

	string topicname;

	ros::init(argc,argv,ugvID);


	ros::NodeHandle n;

	ros::Subscriber subFlightPlan;
	if(ugvType=="1")
	{
		cout << "Suscripcion iniciada..." << endl;
		topicname = ugvID;
		topicname.append("/control_references_rw");
		subFlightPlan = n.subscribe(topicname.c_str(), 0, ControlReferencesRwCallback);
	}else
	{
		/*topicname = ugvID;
		topicname.append("/control_references_fw");
		ros::Subscriber subFlightPlan = n.subscribe(topicname.c_str(), 0, ControlReferencesRwCallback);*/
	}


	initialize_link(ugvID,n);

	ros::Timer timer = n.createTimer(ros::Duration(1/timerate), link_loop);

	ros::spin();


	return 0;
}


/*
void ControlReferencesFwCallback(const catec_msgs::ControlReferenceFwStamped::ConstPtr& fp)
{
	if(actual_state==FLYING)
	{
		lastControlReferenceFw = *fp;
	}
}*/



