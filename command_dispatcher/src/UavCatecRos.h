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
#include <ros/ros.h>

#include <catec_msgs/ControlReferenceRwStamped.h>
#include <catec_msgs/UALStateStamped.h>

#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/LandAction.h>

#include <actionlib/client/simple_action_client.h>

// CPP includes
#include <string>

class UavCatecROS{
public:
	UavCatecROS(std::string _uavId);
	~UavCatecROS();

	// Actions
	void move(catec_msgs::ControlReferenceRwStamped _reference);

	void takeOff();
	void land();

	// Getters
	catec_msgs::ControlReferenceRwStamped	reference() { return mReference; };
	catec_msgs::UALStateStamped	ualState()	{ return mLastUalState; };

	void position(double * _position) volatile{
		_position[0] = mPosition[0];
		_position[1] = mPosition[1];
		_position[2] = mPosition[2];
	}
	void orientation(double * _orientation) volatile{
		_orientation[0] = mOrientation[0];
		_orientation[1] = mOrientation[1];
		_orientation[2] = mOrientation[2];
	}

	bool hasTakeOff(){	return mHasTakeOff; };


private:
	typedef actionlib::SimpleActionClient<catec_actions_msgs::TakeOffAction> TakeOffClient;
	typedef actionlib::SimpleActionClient<catec_actions_msgs::LandAction> LandClient;

	void ualStateCallback(const catec_msgs::UALStateStamped::ConstPtr& s);


private:	// Private Members
	bool mHasTakeOff;
	catec_msgs::UALStateStamped mLastUalState;
	catec_msgs::ControlReferenceRwStamped mReference;

	double * volatile mPosition;		// 777 cant use classes as volatile.
	double * volatile mOrientation;

	ros::Publisher	mCommander;
	ros::Subscriber mStateSubscriber;

	TakeOffClient*	mTakeOffAction;
	LandClient*		mLandAction;

};

#endif // !UAV_CATEC_ROS_H_H
