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


#include "simulation_functions.cpp"
#include "../actions/battery_recharge_action.h"
#include <batterymodel.h>
#include <catec_msgs/ScientificInfo.h>
#include <ros/ros.h>
#include <cstdlib>
#include <ctime>
#include <nav_msgs/Odometry.h>

#include <gazebo/SetModelState.h>
#include <gazebo/GetModelState.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>

using namespace std;

extern LandActionClass *land_action;
extern TakeOffActionClass *take_off_action;

extern string uavID;

//ros::Subscriber sub_stage;
ros::Publisher state_pub;
ros::Subscriber sub_scientific_info_;

catec_msgs::ScientificInfo last_scientific_info_;

ros::ServiceClient setState;
ros::ServiceClient getstate;

BatteryModel *battery_model_;
BatteryActionWrapper *battery_action_wraper_;
bool has_goal_battery_recharge_action_;

void UpdateGazeboState();

void link_loop(const ros::TimerEvent& te)
{

	UpdateGazeboState();

	Twist res;
	Update(&res);


    battery_action_wraper_->uavUpdateState(actual_state);
    if(!battery_action_wraper_->getHasgoal() && has_goal_battery_recharge_action_)
    {
        battery_model_->setBatterytime(ros::Duration(battery_action_wraper_->getLastBatteryLevel()));
    }
    has_goal_battery_recharge_action_ = battery_action_wraper_->getHasgoal();


	//Actualizamos el estado en las actions
	land_action->uavUpdateState(actual_state);
    take_off_action->uavUpdateState(actual_state, battery_action_wraper_->getHasgoal());

	//Intercambiamos linear x por y, para que se corresponda con el testbed
	double x,y;
	x = res.linear.x;
	y = res.linear.y;

	res.linear.x = x;
	res.linear.y = y;

	gazebo::SetModelState srv;
	srv.request.model_state.model_name = uavID;

	srv.request.model_state.pose = lastPose;

    //Hacemos vibrar un poco le uav para darle un poco de realismo.
	if(actual_state!=LANDED)
	{
		tf::Quaternion q;

		int r,p;
		r = (rand()%20)-10;
		p = (rand()%20)-10;

		q = tf::createQuaternionFromRPY(r/1000.0,p/1000.0,tf::getYaw(lastPose.orientation));
		srv.request.model_state.pose.orientation.x = q.x();
		srv.request.model_state.pose.orientation.y = q.y();
		srv.request.model_state.pose.orientation.z = q.z();
		srv.request.model_state.pose.orientation.w = q.w();
	}

	//srv.request.model_state.pose.orientation.x = 0;
	//srv.request.model_state.pose.orientation.y = 0;

	srv.request.model_state.twist = res;

	srv.request.model_state.reference_frame = "world";
	setState.call(srv);
}

void GazeboProcessState(const gazebo::GetModelState& state) {

	//Intercambiamos linear x por y, para que se corresponda con el testbed
	lastPose.position.x = state.response.pose.position.x;
	lastPose.position.y = state.response.pose.position.y;
	lastPose.position.z = state.response.pose.position.z;

	lastPose.orientation.x = state.response.pose.orientation.x;
	lastPose.orientation.y = state.response.pose.orientation.y;
	lastPose.orientation.z = state.response.pose.orientation.z;
	lastPose.orientation.w = state.response.pose.orientation.w;

	lastVel.angular.x = state.response.twist.angular.x;
	lastVel.angular.y = state.response.twist.angular.y;
	lastVel.angular.z = state.response.twist.angular.z;


	lastVel.linear.x = state.response.twist.linear.x;
	lastVel.linear.y = state.response.twist.linear.y;
	lastVel.linear.z = state.response.twist.linear.z;

	catec_msgs::UALStateStamped res;

	res.header.frame_id = uavID;
	res.header.stamp = ros::Time::now();

	res.ual_state.cpu_usage = 50;
	res.ual_state.memory_usage = 50;
	res.ual_state.remaining_battery = 50;

	res.ual_state.dynamic_state.position.valid = 1;

	btScalar yaw,pitch,roll;

	btQuaternion q(lastPose.orientation.x,lastPose.orientation.y,lastPose.orientation.z,lastPose.orientation.w);


	btMatrix3x3 m(q);



	m.getEulerYPR(yaw,pitch,roll);
	res.ual_state.dynamic_state.position.x = lastPose.position.x;
	res.ual_state.dynamic_state.position.y = lastPose.position.y;
	res.ual_state.dynamic_state.position.z = lastPose.position.z;

	res.ual_state.dynamic_state.orientation.valid = 1;
	res.ual_state.dynamic_state.orientation.x = roll;//lastPose.orientation.x;
	res.ual_state.dynamic_state.orientation.y = pitch;//lastPose.orientation.y;
	res.ual_state.dynamic_state.orientation.z = tf::getYaw(lastPose.orientation);//lastPose.orientation.z;

	res.ual_state.dynamic_state.velocity.valid = 1;
	res.ual_state.dynamic_state.velocity.x = lastVel.linear.x;
	res.ual_state.dynamic_state.velocity.y = lastVel.linear.y;
	res.ual_state.dynamic_state.velocity.z = lastVel.linear.z;

     unsigned int batt_ = 0;
    if(!battery_action_wraper_->getHasgoal())
    {
        batt_= battery_model_->update(last_scientific_info_.enable, actual_state!=LANDED);

    }
    else
    {
        batt_ = battery_action_wraper_->getLastBatteryLevel();
    }
    res.ual_state.remaining_battery = (batt_/(30.0*60.0))*100;

	state_pub.publish(res);


	return ;
}

void scientificInfoCallback(const catec_msgs::ScientificInfoConstPtr &scientific_info)
{
    last_scientific_info_ = *scientific_info;
}

void initialize_link(string id, ros::NodeHandle n_)
{
	srand((unsigned)time(0));
	string topicname;
	/*topicname = id;
	topicname.append("/base_pose_ground_truth");
	sub_stage = n_.subscribe(topicname.c_str(), 0, StageCallback);

	topicname = id;
	topicname.append(string("/cmd_vel"));
	stagevel_pub = n_.advertise<geometry_msgs::Twist> (topicname.c_str(), 0);
*/
	topicname =uavID;
	topicname.append("/ual_state");
	state_pub = n_.advertise<catec_msgs::UALStateStamped> (topicname.c_str(), 0);

	setState = n_.serviceClient<gazebo::SetModelState>("/gazebo/set_model_state");
	getstate = n_.serviceClient<gazebo::GetModelState>("/gazebo/get_model_state");

    battery_model_ = new BatteryModel(n_);
    battery_model_->setBatterytime(ros::Duration(30*60));

    battery_action_wraper_ = new BatteryActionWrapper(&n_);

    sub_scientific_info_ = n_.subscribe("/scientific_info", 0, scientificInfoCallback);

}

void UpdateGazeboState() {
		gazebo::GetModelState state;

		state.request.model_name = uavID;
		state.request.relative_entity_name = "world";


		getstate.call(state);

		GazeboProcessState(state);
}

