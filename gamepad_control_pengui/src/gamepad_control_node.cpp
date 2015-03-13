/*
 * joystick_control.cpp
 *
 *  Created on: 17/01/2013
 *      Author: catec
 */

#include <ros/ros.h>
#include <signal.h>
#include <iostream>
#include <catec_msgs/ControlReferenceRwStamped.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/LandAction.h>
#include <actionlib/client/simple_action_client.h>
#include "joystick/joystick.h"

using namespace catec_msgs;
using namespace catec_actions_msgs;

typedef actionlib::SimpleActionClient<TakeOffAction> TakeOffClient;
typedef actionlib::SimpleActionClient<LandAction> LandClient;

void UALStateCallback(const catec_msgs::UALStateStamped::ConstPtr& s);
void quit(int sig);
void tOff_Active_CB();
void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback);
void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result);
void land_Active_CB();
void land_Feedback_CB(const LandFeedbackConstPtr& feedback);
void land_Done_CB(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result);

bool first_ual_state = false;
catec_msgs::UALStateStamped last_ual_state, safe_ual_state;
ControlReferenceRwStamped control_ref_to_send;

int main(int argc, char **argv)
{


		if (argc < 2)
		{
            cout << "This program has one input parameter.\n"<< endl <<
                    "The input parameter is the id of uav." << endl;
			return -1;
		}
		signal(SIGINT, quit);

		string node_name="arcas_joystick_1";
		string uavID="ual_1";

		ros::init(argc, argv, node_name.c_str());

		ros::NodeHandle n;

		string topicname = "/uav_";
		topicname.append(argv[1]);
		topicname.append("/control_references_rw");

		ros::Publisher joystick_publisher = n.advertise<ControlReferenceRwStamped> (topicname.c_str(), 0);


        control_ref_to_send.c_reference_rw.cruise = 0.5;

		topicname = "/uav_";
		topicname.append(argv[1]);
		topicname.append("/ual_state");
		ros::Subscriber subState = n.subscribe(topicname.c_str(), 0, UALStateCallback);

		int fd;
		struct wwvi_js_event wjse;

        wjse.stick2_x = 0; //Roll
        wjse.stick2_y = 0; //Yaw
        wjse.stick_x = 0;  //Pitch
        wjse.stick_y = 0;  //Thrust
        wjse.button[15]=0;  //Take-Off, Button 1 on Joystick
        wjse.button[14]=0;  //Land, Button 2 on Joystick

        //Create takeoff and land clients
        topicname = "/uav_";
        topicname.append(argv[1]);
        topicname.append("/take_off_action");
        TakeOffClient* myTakeOff = new TakeOffClient(topicname,true);

        topicname = "/uav_";
        topicname.append(argv[1]);
        topicname.append("/land_action");
        LandClient* myLand = new LandClient(topicname,true);

        //Wait for takeoff and land servers
        myTakeOff->waitForServer(ros::Duration(0));
        myLand->waitForServer(ros::Duration(0));


		CJoystick joystick;
		fd = joystick.open_joystick();

		if(!fd)
		{
			cerr << "Error opening joystick, is still connected?\r\n" << endl;
			return(-1);
		}

		ros::AsyncSpinner spinner_(0);
		spinner_.start();

		while(ros::ok())
		{

			if(joystick.get_joystick_status(&wjse)!=-1)
			{

                //Pitch
                if(wjse.stick_x*(-1)!=0)
                {
                    //ROS_INFO_STREAM("Input pitch: " << (wjse.stick_x/5000.0) << "; Position x: " << control_ref_to_send.c_reference_rw.position.x);
                    control_ref_to_send.c_reference_rw.position.x = last_ual_state.ual_state.dynamic_state.position.x + (wjse.stick_x/1000.0);
                }

                //Roll
                if(wjse.stick2_x*(-1)!=0)
                {
                    control_ref_to_send.c_reference_rw.position.y = last_ual_state.ual_state.dynamic_state.position.y + (wjse.stick2_x/1000.0);
                }

                //Thrust
				if(wjse.stick_y*(-1)!=0)
				{
                    control_ref_to_send.c_reference_rw.position.z = last_ual_state.ual_state.dynamic_state.position.z + (wjse.stick_y/4000.0);
				}

                //Yaw
				if(wjse.stick2_y*(-1)!=0)
				{
                    control_ref_to_send.c_reference_rw.heading = last_ual_state.ual_state.dynamic_state.orientation.z + (wjse.stick2_y/3000.0);
				}

                //Take-off
                if((joystick.get_joystick_status(&wjse)!=-1) && (wjse.button[15] == 1))
                {
                    //Send current pose in order to make quadrotor stay at its pose after take-off
                    control_ref_to_send.c_reference_rw.position.x = last_ual_state.ual_state.dynamic_state.position.x;
                    control_ref_to_send.c_reference_rw.position.y = last_ual_state.ual_state.dynamic_state.position.y;
                    control_ref_to_send.c_reference_rw.position.z = last_ual_state.ual_state.dynamic_state.position.z;
                    control_ref_to_send.c_reference_rw.heading    = last_ual_state.ual_state.dynamic_state.orientation.z;

                    joystick_publisher.publish(control_ref_to_send);

                    ROS_INFO_STREAM("Sent position: x: " << control_ref_to_send.c_reference_rw.position.x << "; y: " <<
                                                            control_ref_to_send.c_reference_rw.position.y << "; z: " <<
                                                            control_ref_to_send.c_reference_rw.position.z );

                    //Send take-off
                    TakeOffGoal toff_goal;
                    myTakeOff->sendGoal(toff_goal, &tOff_Done_CB, &tOff_Active_CB, &tOff_Feedback_CB);
                    ROS_INFO_STREAM("Take-Off Action Sent");

                    //Wait untill takeoff is completed
                    myTakeOff->waitForResult();
                    ROS_INFO_STREAM("Take-Off Action Completed");
                }

                //Landing
                if((joystick.get_joystick_status(&wjse)!=-1) && (wjse.button[14] == 1))
                {
                    LandGoal land_goal;
                    myLand->sendGoal(land_goal, &land_Done_CB, &land_Active_CB, &land_Feedback_CB);
                    ROS_INFO_STREAM("Land Action Sent");

                    //Wait untill land is completed
                    myLand->waitForResult();
                    ROS_INFO_STREAM("Land Action Completed");
                }

            } else
			{

			}

			joystick_publisher.publish(control_ref_to_send);

			//~20Hz
			usleep(50000);
		}
		return 0;
}

void UALStateCallback(const catec_msgs::UALStateStamped::ConstPtr& s)
{
    last_ual_state = *s;

    if(!first_ual_state)
    {
        first_ual_state = true;
        ROS_INFO_STREAM("First ual state");
        control_ref_to_send.c_reference_rw.position.x = last_ual_state.ual_state.dynamic_state.position.x;
        control_ref_to_send.c_reference_rw.position.y = last_ual_state.ual_state.dynamic_state.position.y;
        control_ref_to_send.c_reference_rw.position.z = last_ual_state.ual_state.dynamic_state.position.z ;
        control_ref_to_send.c_reference_rw.heading = last_ual_state.ual_state.dynamic_state.orientation.z;
    }
}

void quit(int sig)
{
    ros::shutdown();
    exit(0);
}

void tOff_Active_CB()
{

}

void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback)
{

}

void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result)
{

}

void land_Active_CB()
{

}

void land_Feedback_CB(const LandFeedbackConstPtr& feedback)
{

}

void land_Done_CB(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result)
{

}
