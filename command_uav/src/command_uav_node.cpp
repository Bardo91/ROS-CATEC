///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	command_uav_node.cpp
//		Author: Pablo R.S.
//		Date: 14/08/2014
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ros/ros.h>
#include <signal.h>
#include <iostream>
#include <catec_msgs/ControlReferenceRwStamped.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/LandAction.h>
#include <actionlib/client/simple_action_client.h>

//-------- camera includes  ------------------------------------------------
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>

//----------------------------------------------------------------------
//-------- opencv includes -----------------------------------------------
#include <opencv/cv.h>
#include <opencv/highgui.h>

//----------------------------------------------------------------------
//---------- BOViL includes --------------------------------------------

//#include <algorithms/segmentation/ColorClustering.h>
//#include <core/BOViL_core>
//----------------------------------------------------------------------

#include <tf/transform_datatypes.h>

using namespace catec_msgs;
using namespace catec_actions_msgs;
using namespace std;
using namespace cv;

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

// ----- Subscriber callback -----
void imageSubscriberCallback(const sensor_msgs::Image & msg){
	//ROS_INFO("Image width: %d", msg.width);
	//ROS_INFO("Image height: %d", msg.height);
	
	std::vector<uint8_t> imgData = msg.data;
	//ROS_INFO("Image size: %d", imgData.size());
	
	Mat img(msg.height, msg.width, CV_8UC3, imgData.data());
	//cvtcolor(img, img, CV_BGR2HSV);
	// 666 TODO: segmentate image
	imshow("uav_camera", img);
	ROS_INFO("Img showed");
	waitKey(1);

}
//---------------------------------

bool first_ual_state = false;
catec_msgs::UALStateStamped last_ual_state, safe_ual_state;
ControlReferenceRwStamped control_ref_to_send;

int main(int argc, char **argv) {
		if (argc < 2) {
			cout << "This program has one input parameter.\n"<< endl <<
					"The input parameter is the id of uav." << endl;
			return -1;
		}

		signal(SIGINT, quit);

		string node_name="command_uav_node";
		bool positionSentLastTime=false;
		bool hasTakeOff = false;

		string uavID="ual_1";

		ros::init(argc, argv, node_name.c_str());

		ros::NodeHandle n;
		double length;
		double length_scaled;
		double max_cruise;

		string topicname = "/uav_";
		topicname.append(argv[1]);
		topicname.append("/control_references_rw");

		// 666 TODO: Image source subscriber
		ros::Subscriber imgSubscriber = n.subscribe("/overhead_camera/image_raw", 1, imageSubscriberCallback);
		
		imgSubscriber;

		// 666 TODO: change name of publisher
		ros::Publisher commander_publisher = n.advertise<ControlReferenceRwStamped> (topicname.c_str(), 0);

		topicname = "/uav_";
		topicname.append(argv[1]);
		topicname.append("/ual_state");
		ros::Subscriber subState = n.subscribe(topicname.c_str(), 0, UALStateCallback);

		int fd;

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

		ros::AsyncSpinner spinner_(0);
		spinner_.start();

		while(ros::ok()) {
			//---------------------------------------------------------------------------------------------
			// 666 TODO: when
			if(true) {
				//---------------------------------------------------------------------------------------------
				tf::Vector3 quad_desired_position, quad_desired_position_unity, quad_calculated_position;

				// 666 TODO: add desired position
				quad_desired_position = tf::Vector3(	(0.0),
									(0.0),
									(0.0));
					// last_ual_state.ual_state.dynamic_state.position.x or y or z

				max_cruise = 1.5; //max cruise in m/s
				length = quad_desired_position.length();
				length_scaled = length / (1024 / max_cruise); //1024 is maximum input by PS3 joystick; therefore we limit length_scaled to 1.5m (only using one stick!)

				//---------------------------------------------------------------------------------------------
				// Cruise
				if (length_scaled <= max_cruise)
				{
					control_ref_to_send.c_reference_rw.cruise = length_scaled;
				}
				else
				{
					control_ref_to_send.c_reference_rw.cruise = max_cruise;
				}
				//---------------------------------------------------------------------------------------------
				// If z component of the desired position vector is more than 50% limit the cruise velocity to 0.5
				if ((quad_desired_position.z() *2) > length && length_scaled > 0.5 )
				{
					control_ref_to_send.c_reference_rw.cruise = 0.5;
				}

				quad_desired_position_unity =  quad_desired_position / length;
				quad_calculated_position = quad_desired_position_unity * 1.5;  // 1.5 is the distance [m] between desired and current position
				//---------------------------------------------------------------------------------------------
				if (length != 0.0) {
					//Pitch
					control_ref_to_send.c_reference_rw.position.x = last_ual_state.ual_state.dynamic_state.position.x + quad_calculated_position.x();


					//Roll
					control_ref_to_send.c_reference_rw.position.y = last_ual_state.ual_state.dynamic_state.position.y + quad_calculated_position.y();


					//Thrust
					control_ref_to_send.c_reference_rw.position.z = last_ual_state.ual_state.dynamic_state.position.z + quad_calculated_position.z();

					positionSentLastTime = true;

				}else if(positionSentLastTime) {
					positionSentLastTime = false;
					control_ref_to_send.c_reference_rw.position.x = last_ual_state.ual_state.dynamic_state.position.x;
					control_ref_to_send.c_reference_rw.position.y = last_ual_state.ual_state.dynamic_state.position.y;
					control_ref_to_send.c_reference_rw.position.z = last_ual_state.ual_state.dynamic_state.position.z;
					control_ref_to_send.c_reference_rw.cruise = 0;

				}
				//---------------------------------------------------------------------------------------------
				//Yaw
				if(/*666 TODO: when to change yaw*/false) {
					control_ref_to_send.c_reference_rw.heading = last_ual_state.ual_state.dynamic_state.orientation.z + (0.0/*666 TODO: how much*/);
				}

				//---------------------------------------------------------------------------------------------
				//Take-off: see the number of button (number 1)
				if(/*666 TODO: when to take-off*/
					!hasTakeOff) {
					//Send current pose in order to make quadrotor stay at its pose after take-off
					hasTakeOff = true;
					control_ref_to_send.c_reference_rw.position.x = last_ual_state.ual_state.dynamic_state.position.x;
					control_ref_to_send.c_reference_rw.position.y = last_ual_state.ual_state.dynamic_state.position.y;
					control_ref_to_send.c_reference_rw.position.z = last_ual_state.ual_state.dynamic_state.position.z;
					control_ref_to_send.c_reference_rw.heading    = last_ual_state.ual_state.dynamic_state.orientation.z;

					commander_publisher.publish(control_ref_to_send);

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
				//---------------------------------------------------------------------------------------------
				//Landing: see the number of button (number 2)
				if(/* 666 TODO: when to land */false && last_ual_state.ual_state.dynamic_state.position.z >= 0.5) {
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
			//---------------------------------------------------------------------------------------------
			control_ref_to_send.c_reference_rw.position.x = 5.0;
			control_ref_to_send.c_reference_rw.position.y = 2.0;
			control_ref_to_send.c_reference_rw.position.z = 2.0;
			control_ref_to_send.c_reference_rw.heading    = last_ual_state.ual_state.dynamic_state.orientation.z;

			commander_publisher.publish(control_ref_to_send);

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
