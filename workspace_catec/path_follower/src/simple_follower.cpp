
#include <ros/ros.h>
#include <iostream>
#include <math.h>
#include <boost/lexical_cast.hpp>
#include <catec_msgs/ControlReferenceRwStamped.h>
#include <catec_msgs/WayPointWithCruiseStamped.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/UALMultiState.h>

#define PI 3.14159265

using namespace std;

/*
 * The uav identifier that this follower control.
 * */
string id;
string uavID;

/*
 * WayPoint from LocalPlanner
 * */
catec_msgs::WayPointWithCruiseStamped last_way_point;
void WayPointCallback(const catec_msgs::WayPointWithCruiseStamped::ConstPtr& w);

/*
 * Last UAL State (for actual Position)
 * */
catec_msgs::UALStateStamped last_ual_state;
void UALStateCallback(const catec_msgs::UALStateStamped::ConstPtr& s);

/*
 * Control References Publisher
 * */
ros::Publisher control_reference_pub;

/*
 * Calculate and send next controlReferences
 * */
void sendControlReferences(const ros::TimerEvent& te);

/*
 * Maximum distance between two references commands.
 * */
double max_distance;

int main(int argc, char** argv)
{

	if (argc < 3)
	{
		cout << "This program has two inputs parameters.\n"<< endl <<
				"The first input parameter is the number of the UAV." << endl <<
				"The second input parameter is the distance between references commands." << endl;
		return -1;
	}

	// The UAV ID is stored in a global variable
	uavID="uav_";
	uavID.append(string(argv[1]));
	id = argv[1];

	try
	{
		max_distance = boost::lexical_cast<double>(argv[2]);
	}
	catch(boost::bad_lexical_cast const&)
	{
		perror("The second argument is not a number.");
		return 1;
	}

	ros::init(argc,argv,"simple_follower");

	ros::NodeHandle n;



	string topicname = uavID;
	topicname.append("/ual_state");
	ros::Subscriber subState = n.subscribe(topicname.c_str(), 0, UALStateCallback);

	topicname = "path_follower_";
	topicname.append(string(id));
	topicname.append("/way_point_callback");
	ros::Subscriber subWayPoint = n.subscribe(topicname.c_str(), 0, WayPointCallback);

	topicname = "path_follower_";
	topicname.append(id);
	topicname.append(string("/control_references_rw"));
	control_reference_pub = n.advertise<catec_msgs::ControlReferenceRwStamped> (topicname.c_str(), 0);

	ros::Timer timer = n.createTimer(ros::Duration(1.0/30.0), sendControlReferences);

	ros::spin();

	return 0;
}

void sendControlReferences(const ros::TimerEvent& te)
{
	catec_msgs::Position desp_vector, desp_vector_normalized, desp_vector_final;

	desp_vector.x = last_way_point.way_point.x - last_ual_state.ual_state.dynamic_state.position.x;
	desp_vector.y = last_way_point.way_point.y - last_ual_state.ual_state.dynamic_state.position.y;
	desp_vector.z = last_way_point.way_point.z - last_ual_state.ual_state.dynamic_state.position.z;

	double vector_length = sqrt(pow(desp_vector.x,2) + pow(desp_vector.y,2) + pow(desp_vector.z,2));

	desp_vector_normalized.x = desp_vector.x/vector_length;
	desp_vector_normalized.y = desp_vector.y/vector_length;
	desp_vector_normalized.z = desp_vector.z/vector_length;

	desp_vector_final.x = desp_vector_normalized.x * max_distance;
	desp_vector_final.y = desp_vector_normalized.y * max_distance;
	desp_vector_final.z = desp_vector_normalized.z * max_distance;

	catec_msgs::ControlReferenceRwStamped res;


	if(vector_length > max_distance)
	{
		res.c_reference_rw.position.x = last_ual_state.ual_state.dynamic_state.position.x + desp_vector_final.x;
		res.c_reference_rw.position.y = last_ual_state.ual_state.dynamic_state.position.y + desp_vector_final.y;
		res.c_reference_rw.position.z = last_ual_state.ual_state.dynamic_state.position.z + desp_vector_final.z;
	}
	else
	{
		res.c_reference_rw.position.x = last_way_point.way_point.x;
		res.c_reference_rw.position.y = last_way_point.way_point.y;
		res.c_reference_rw.position.z = last_way_point.way_point.z;

	}




	res.c_reference_rw.cruise = last_way_point.way_point.cruise;

	res.c_reference_rw.heading = atan2(desp_vector.y,desp_vector.x) + PI/2;


				//if(v_distance.x < 0)
				//{
				res.c_reference_rw.heading += PI;
				//}

				if(res.c_reference_rw.heading > PI)
				{
					res.c_reference_rw.heading -= 2*PI;
				}
				else if (res.c_reference_rw.heading < (-PI))
				{
					res.c_reference_rw.heading += 2*PI;
				}

	control_reference_pub.publish(res);
    ROS_INFO("Vector_lenght: %f   max_distance: %f", vector_length,max_distance);
	ROS_INFO("Next way point [%f %f %f]", last_way_point.way_point.x,last_way_point.way_point.y,last_way_point.way_point.z);
	ROS_INFO("Next Reference [%f %f %f]", res.c_reference_rw.position.x,res.c_reference_rw.position.y,res.c_reference_rw.position.z);
}
void WayPointCallback(const catec_msgs::WayPointWithCruiseStamped::ConstPtr& w)
{
	last_way_point = *w;
}
void UALStateCallback(const catec_msgs::UALStateStamped::ConstPtr& s)
{
	last_ual_state = *s;
}
