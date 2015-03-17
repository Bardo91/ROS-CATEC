///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		EC-SAFEMOBIL:	PatrollingCV - uav_vision
//			Author:	Pablo R.S.
//			Date:	2015-FEB-18
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "UavCatecRos.h"
#include <iostream>

using namespace std;
using namespace catec_msgs;
using namespace catec_actions_msgs;

void tOff_Active_CB();
void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback);
void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result);
void land_Active_CB();
void land_Feedback_CB(const LandFeedbackConstPtr& feedback);
void land_Done_CB(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result);


//---------------------------------------------------------------------------------------------------------------------
UavCatecROS::UavCatecROS(string _uavId): mHasTakeOff(false){
	mPosition 		= new double[3];
	mOrientation 	= new double[3];

	ros::NodeHandle n;
	
	string topicname = "/uav_";
	topicname.append(_uavId);
	topicname.append("/control_references_rw");
	mCommander = n.advertise<ControlReferenceRwStamped>(topicname.c_str(), 0);

	topicname = "/uav_";
	topicname.append(_uavId);
	topicname.append("/ual_state");
	mStateSubscriber = n.subscribe(topicname.c_str(), 0, &UavCatecROS::ualStateCallback, this);

	//Create takeoff and land clients
	topicname = "/uav_";
	topicname.append(_uavId);
	topicname.append("/take_off_action");
	mTakeOffAction = new TakeOffClient(topicname, true);
	mTakeOffAction->waitForServer(ros::Duration(0));

	topicname = "/uav_";
	topicname.append(_uavId);
	topicname.append("/land_action");
	mLandAction = new LandClient(topicname, true);
	mLandAction->waitForServer(ros::Duration(0));
}

//---------------------------------------------------------------------------------------------------------------------
UavCatecROS::~UavCatecROS(){
	delete[] mPosition;
	delete[] mOrientation;
}

//---------------------------------------------------------------------------------------------------------------------
void UavCatecROS::move(ControlReferenceRwStamped _reference){
	mReference = _reference;
	mCommander.publish(_reference);
}

//---------------------------------------------------------------------------------------------------------------------
void UavCatecROS::takeOff(){
	//Send take-off
	TakeOffGoal toff_goal;
	mTakeOffAction->sendGoal(toff_goal, &tOff_Done_CB, &tOff_Active_CB, &tOff_Feedback_CB);

	//Wait untill takeoff is completed
	mTakeOffAction->waitForResult();
	mHasTakeOff = true;
}

//---------------------------------------------------------------------------------------------------------------------
void UavCatecROS::land(){
	LandGoal land_goal;
	mLandAction->sendGoal(land_goal, &land_Done_CB, &land_Active_CB, &land_Feedback_CB);

	//Wait untill land is completed
	mLandAction->waitForResult();
	mHasTakeOff = false;
}

//---------------------------------------------------------------------------------------------------------------------
// Private Callbacks
void UavCatecROS::ualStateCallback(const catec_msgs::UALStateStamped::ConstPtr& s){
	mLastUalState = *s;

	mPosition[0] = s->ual_state.dynamic_state.position.x;
    mPosition[1] = s->ual_state.dynamic_state.position.y;
	mPosition[2] = s->ual_state.dynamic_state.position.z;

	mOrientation[0] = s->ual_state.dynamic_state.orientation.x;
    mOrientation[1] = s->ual_state.dynamic_state.orientation.y;
    mOrientation[2] = s->ual_state.dynamic_state.orientation.z;
}


//---------------------------------------------------------------------------------------------------------------------
// Unimplemented actions

void tOff_Active_CB(){

}

void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback){

}

void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result){

}

void land_Active_CB(){

}

void land_Feedback_CB(const LandFeedbackConstPtr& feedback){

}

void land_Done_CB(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result){

}
