///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		ROS-CATEC:
//			Author:	Pablo R.S.
//			Date:	2015-MAR-22
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RosAgent.h"

using namespace std;

namespace ros_catec{
	//-----------------------------------------------------------------------------------------------------------------
	RosAgent::RosAgent(std::string _uavName){
		mPosition 		= new double[3];
		mOrientation 	= new double[3];

		ros::NodeHandle nodeHandle;

		string stateTopic = _uavName;
		stateTopic.append("/ual_state");
		mStateSubscriber = nodeHandle.subscribe(stateTopic.c_str(), 0, &RosAgent::stateCallback, this);
	}

	//-----------------------------------------------------------------------------------------------------------------
	RosAgent::~RosAgent(){
		delete[] mPosition;
		delete[] mOrientation;
	}

	//-----------------------------------------------------------------------------------------------------------------
	void RosAgent::position(double * _position) volatile{
		_position[0] = mPosition[0];
		_position[1] = mPosition[1];
		_position[2] = mPosition[2];
	}

	//-----------------------------------------------------------------------------------------------------------------
	void RosAgent::orientation(double * _orientation) volatile{
		_orientation[0] = mOrientation[0];
		_orientation[1] = mOrientation[1];
		_orientation[2] = mOrientation[2];
	}

	//-----------------------------------------------------------------------------------------------------------------
	void RosAgent::stateCallback(const catec_msgs::UALStateStamped::ConstPtr& s){
		mPosition[0] = s->ual_state.dynamic_state.position.x;
		mPosition[1] = s->ual_state.dynamic_state.position.y;
		mPosition[2] = s->ual_state.dynamic_state.position.z;

		mOrientation[0] = s->ual_state.dynamic_state.orientation.x;
		mOrientation[1] = s->ual_state.dynamic_state.orientation.y;
		mOrientation[2] = s->ual_state.dynamic_state.orientation.z;
	}

	//-----------------------------------------------------------------------------------------------------------------
}	// namespace ros_catec.


