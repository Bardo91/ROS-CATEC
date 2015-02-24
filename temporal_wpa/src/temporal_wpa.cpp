#include <ros/ros.h>
#include <iostream>
#include <catec_actions_msgs/GoToWayPointsAction.h>
#include <actionlib/server/action_server.h>

#include <tf/transform_datatypes.h>
#include <tf/tf.h>

#include <catec_msgs/WayPointWithCruiseStamped.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/Position.h>
using namespace std;
#define PI 3.14159265
#include "actions/gtwp_action.h"




int main(int argc, char** argv)
{
	string node_name;
	string uavID;

	if (argc < 2)
	{
		cout << "This program has one inputs parameters.\n"<< endl <<
				"The first input parameter is number of uav." << endl;
		return -1;
	}

	node_name ="temporal_wpa_";
	node_name.append(argv[1]);
	uavID="uav_";
	uavID.append(argv[1]);

	ros::init(argc,argv,node_name);

	string action_name = uavID;
	action_name.append("/go_to_way_point_action");
	GTWPActionClass action(action_name,node_name);

	ros::spin();

	return 0;

}
