///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		ROS-CATEC:
//			Author:	Pablo R.S.
//			Date:	2015-MAR-22
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CORE_AGENT_ROS_AGENT_H_
#define CORE_AGENT_ROS_AGENT_H_

#include <string>

#include <catec_msgs/ControlReferenceRwStamped.h>
#include <catec_msgs/UALStateStamped.h>

#include <ros/ros.h>

namespace ros_catec{
	class RosAgent{
	public:		// Public interface.
		RosAgent			(std::string _uavName);
		virtual ~RosAgent	();

		void position		(double * _position) volatile;
		void orientation	(double * _orientation) volatile;

	private:	// Private methods.
		virtual void stateCallback	(const catec_msgs::UALStateStamped::ConstPtr& s);

	private:	// Private members.
		double * volatile mPosition;		// 777 cant use ualstatestamped as volatile.
		double * volatile mOrientation;

		ros::Subscriber mStateSubscriber;

	};

}	//	namespace ros_catec


#endif	//	CORE_AGENT_ROS_AGENT_H_
