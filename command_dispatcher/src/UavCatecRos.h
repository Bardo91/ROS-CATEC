///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		EC-SAFEMOBIL:	PatrollingCV - uav_vision
//			Author:	Pablo R.S.
//			Date:	2015-FEB-18
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef UAV_CATEC_ROS_H_H
#define UAV_CATEC_ROS_H_H

// CATEC includes
#include "core/agents/RosAgent.h"

#include <ros/ros.h>

#include <catec_msgs/ControlReferenceRwStamped.h>
#include <catec_msgs/UALStateStamped.h>

#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/LandAction.h>

#include <actionlib/client/simple_action_client.h>

// CPP includes
#include <string>

class UavCatecROS: public ros_catec::RosAgent {
public:
	UavCatecROS(std::string _uavId);

	// Actions
	void move(catec_msgs::ControlReferenceRwStamped _reference);

	void takeOff();
	void land();

	// Getters
	catec_msgs::ControlReferenceRwStamped	reference() { return mReference; };

	bool hasTakeOff(){	return mHasTakeOff; };
private:
	typedef actionlib::SimpleActionClient<catec_actions_msgs::TakeOffAction> TakeOffClient;
	typedef actionlib::SimpleActionClient<catec_actions_msgs::LandAction> LandClient;


private:	// Private Members
	bool mHasTakeOff;
	catec_msgs::ControlReferenceRwStamped mReference;

	ros::Publisher	mCommander;

	TakeOffClient*	mTakeOffAction;
	LandClient*		mLandAction;

};

#endif // !UAV_CATEC_ROS_H_H
