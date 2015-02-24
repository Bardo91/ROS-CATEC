/*
 * pathplanner.cpp
 *
 *  Created on: Jul 24, 2012
 *      Author: catec
 */



#include <ros/ros.h>
#include <iostream>
#include <cmath>
#include "src/collision-helper.h"
#include "src/codigoc/codigoc.h"

#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/WayPoint.h>
#include <catec_msgs/WayPointWithCruise.h>
#include <catec_msgs/WayPointWithCruiseStamped.h>
#include <catec_msgs/Position.h>

#include <geometry_msgs/Point.h>

using namespace std;
using namespace catec_msgs;

//UAV id
int uav_id;
string uav_full_id;

//Node name
string node_name;

//Color of collisionBox
int color = 10000;

float color_r[] = {1.0, 0.0, 0.0};
float color_g[] = {0.0, 1.0, 0.0};
float color_b[] = {0.0, 0.0, 1.0};

//Embedded class for all the matlab code for pathfinding algorithm
//It also contains the updated matrix including the uavs, land and obstacles
codigocModelClass matlab;

//Dimensions of the matlab's world
int mn[] = {100,100,20};


//Escale for matlab obstacles
geometry_msgs::Point scale;


//The last dynamic paths of all uavs, erase before update world.
vector<Position> collision_paths;

//Last state of our uav
UALStateStamped last_ual_state;

//Last waypoints of all uav in the virtual world
map<string, UALStateStamped> last_states;

//My next waypoint
WayPointWithCruiseStamped my_next_waypoint;

//My actual path
vector<geometry_msgs::Point> path;

//Last waypoints of all uav in the virtual world
map<string, WayPointWithCruiseStamped> last_waypoints;

//State of this uav publisher
ros::Publisher state_pub;

//Path marker publisher
ros::Publisher path_pub;

//nextWayPoint
ros::Publisher my_waypoint_pub, my_waypoint_pub_others;

//My next waypoint
void myWayPointCallback(const WayPointWithCruiseStamped::ConstPtr& wp);

//Next uav's waypoint callback
void nextWayPointCallback(const WayPointWithCruiseStamped::ConstPtr& wp);

//Actual state of our uav
void UALStateCallback(const UALStateStamped::ConstPtr& state);

//Actual state of others uavs
void otherUALStateCallback(const UALStateStamped::ConstPtr& state);

//Update World
void updateWorld();

//Calculate path of this uav
void calculatePath();

//Publish rviz
void publishRviz();

//Publish Velocity Vector in Rviz
void publishVelocityVectorRviz();

//Erase old collision path
void eraseCollision(vector<Position> *vec);

//Add new Collision
void addCollision(vector<Position> *vec, string uav_id, PositionWithCheck actual_position, WayPointWithCruise waypoint, int colorValue);

//Initialize matlab
void initializeMatlab();


int main(int argc, char** argv)
{

	if (argc < 2)
		{
			cout << "This program has two inputs parameters.\n"<< endl <<
					"The first input parameter is the number of the UAV." << endl;
			return -1;
		}

		//The UAV ID is stored in a global variable
		uav_full_id="uav_";
		uav_full_id.append(string(argv[1]));

		try
		{
			uav_id = boost::lexical_cast<int>(argv[1]);
		}
		catch(boost::bad_lexical_cast const&)
		{
			perror("The second argument is not a number.");
			return 1;
		}


	last_ual_state.ual_state.dynamic_state.position.x = uav_id -3;
	last_ual_state.ual_state.dynamic_state.position.y = -5;

	//Init ROS.
	node_name = "path_planner_";

	std::stringstream ss;
	ss << uav_id;

	node_name.append(ss.str());
	ros::init(argc, argv, node_name.c_str());

	ros::NodeHandle n;

	//Subscribe to my waypoints
	string topicname = node_name;
	topicname.append("/in_waypoint");
	ros::Subscriber subMyWayPoint = n.subscribe(topicname.c_str(), 0, myWayPointCallback);

	//Subscribe to others uav's waypoints
	topicname = "/uavs_next_waypoint";
	ros::Subscriber subWayPoints = n.subscribe(topicname.c_str(), 0, nextWayPointCallback);

	//Subscribe to others uav's state
	topicname = "/uavs_actual_state";
	ros::Subscriber subUavState = n.subscribe(topicname.c_str(), 0, otherUALStateCallback);

	//Subscribe to ours uav state
	topicname = "uav_";
	topicname.append(ss.str());
	topicname.append("/ual_state");
	ros::Subscriber subState = n.subscribe(topicname.c_str(), 0, UALStateCallback);


	//Publisher for send to others our actual state
	topicname = "/uavs_actual_state";
	state_pub = n.advertise<UALStateStamped> (topicname.c_str(), 0);

	//Publisher for send to others our next waypoint
	topicname = "/uavs_next_waypoint";
	my_waypoint_pub_others = n.advertise<WayPointWithCruiseStamped> (topicname.c_str(), 0);

	//Publisher for send to path_follower our next waypoint
	topicname= node_name;
	topicname.append("/out_waypoint");
	my_waypoint_pub = n.advertise<WayPointWithCruiseStamped> (topicname.c_str(), 0);


	//For publish path in rviz
	//This publiser will be used to publish the path line for rviz
	topicname = node_name;
	topicname.append("/colision");
	marker_pub = n.advertise<visualization_msgs::Marker>(topicname,1);

	topicname = node_name;
		topicname.append("/path");
		path_pub = n.advertise<visualization_msgs::Marker>(topicname,1);

	initializeMatlab();


	ros::AsyncSpinner spinner(1);
	spinner.start();

	while(ros::ok())
	{
		ros::Time tinit = ros::Time::now();
		//Run path planning at max-speed.
		updateWorld();

		calculatePath();

		publishRviz();

		//if(node_name.compare("path_planner_2")==0)
		//cerr << "Computed in secs: " << (ros::Time::now() - tinit).toSec() << endl;
	}
	return 0;
}

//My next waypoint
void myWayPointCallback(const WayPointWithCruiseStamped::ConstPtr& wp)
{
	my_next_waypoint = *wp;
}

//Next uav's waypoint callback
void nextWayPointCallback(const WayPointWithCruiseStamped::ConstPtr& wp)
{
	if(wp->header.frame_id.compare(node_name) != 0)
	{
		last_waypoints[wp->header.frame_id] = *wp;

	}
}

//Actual state of our uav
void UALStateCallback(const UALStateStamped::ConstPtr& state)
{
	//Hold state
	last_ual_state = *state;

	//Publish state to other path_planner
	last_ual_state.header.frame_id = node_name;
	state_pub.publish(last_ual_state);
}

//Actual state of others uavs
void otherUALStateCallback(const UALStateStamped::ConstPtr& state)
{
	//Store only the uavs with more priority of ours.
	if(state->header.frame_id.compare(node_name) != 0)
	{
		last_states[state->header.frame_id] = *state;
	}
}

//Update World
void updateWorld()
{
	eraseCollision(&collision_paths);

	for(map<string,WayPointWithCruiseStamped>::iterator it = last_waypoints.begin(); it != last_waypoints.end(); it++)
	{
		if(last_states.count(it->first))
			addCollision(&collision_paths,it->second.header.frame_id,last_states[it->first].ual_state.dynamic_state.position,it->second.way_point,color);
	}

}

//Calculate path of this uav
void calculatePath()
{
	WayPointWithCruiseStamped res;
	res.header.frame_id = node_name;
	res.header.stamp = ros::Time::now();
	res.way_point.cruise = my_next_waypoint.way_point.cruise;
	res.way_point.x = last_ual_state.ual_state.dynamic_state.position.x;
	res.way_point.y = last_ual_state.ual_state.dynamic_state.position.y;
	res.way_point.y = last_ual_state.ual_state.dynamic_state.position.y;

	//Calculate the new path.

	//[100, 100, 20] is the maximum spatial granularity allowed at the moment
		matlab.codigoc_U.n[0] = mn[0];
		matlab.codigoc_U.n[1] = mn[1];
		matlab.codigoc_U.n[2] = mn[2];

	/*geometry_msgs::Point scale;

	//First the scale is computed
	scale.x = (matlab.codigoc_U.limsespacio[1] - matlab.codigoc_U.limsespacio[0])/matlab.codigoc_U.n[0];
	scale.y = (matlab.codigoc_U.limsespacio[3] - matlab.codigoc_U.limsespacio[2])/matlab.codigoc_U.n[1];
	scale.z = (matlab.codigoc_U.limsespacio[5] - matlab.codigoc_U.limsespacio[4])/matlab.codigoc_U.n[2];*/



	//Set our position
	matlab.codigoc_U.wpini[0] = last_ual_state.ual_state.dynamic_state.position.x;
	matlab.codigoc_U.wpini[1] = last_ual_state.ual_state.dynamic_state.position.y;
	matlab.codigoc_U.wpini[2] = last_ual_state.ual_state.dynamic_state.position.z;

	//Set initial waypoint
	matlab.codigoc_U.wpfin[0] = my_next_waypoint.way_point.x;
	matlab.codigoc_U.wpfin[1] = my_next_waypoint.way_point.y;
	matlab.codigoc_U.wpfin[2] = my_next_waypoint.way_point.z;


	//Calculamos el vector unitario y la distancia del way point.
	geometry_msgs::Vector3 pos_vector, pos_unit_vector;
	pos_vector.x = matlab.codigoc_U.wpfin[0] - last_ual_state.ual_state.dynamic_state.position.x;
	pos_vector.y = matlab.codigoc_U.wpfin[1] - last_ual_state.ual_state.dynamic_state.position.y;
	pos_vector.z = matlab.codigoc_U.wpfin[2] - last_ual_state.ual_state.dynamic_state.position.z;
	double distance = sqrt(pow(pos_vector.x,2) + pow(pos_vector.y,2) + pow(pos_vector.z,2));
	pos_unit_vector.x = pos_vector.x/distance;
	pos_unit_vector.y = pos_vector.y/distance;
	pos_unit_vector.z = pos_vector.z/distance;

	//Reducimos la distancia del way point para el jerezano.
	if(distance > 5.0)
	{
		matlab.codigoc_U.wpfin[0] =last_ual_state.ual_state.dynamic_state.position.x +  pos_unit_vector.x * 3.0;
		matlab.codigoc_U.wpfin[1] =last_ual_state.ual_state.dynamic_state.position.y + pos_unit_vector.y * 3.0;
		matlab.codigoc_U.wpfin[2] =last_ual_state.ual_state.dynamic_state.position.z + pos_unit_vector.z * 3.0;
		distance = 5.0;
	}

	//If the final point is occupied the final point must be change.
		geometry_msgs::Vector3 pos_matlab;
		pos_matlab.x = (matlab.codigoc_U.wpfin[0]- matlab.codigoc_U.limsespacio[0])/scale.x;
		pos_matlab.y = (matlab.codigoc_U.wpfin[1] - matlab.codigoc_U.limsespacio[2])/scale.y;
		pos_matlab.z = (matlab.codigoc_U.wpfin[2] - matlab.codigoc_U.limsespacio[4])/scale.z;

	//Si nuestro waypoint coincide con un espacio ocupado vamos reduciendo la distancia.
	while(matlab.codigoc_U.A[getIndex(pos_matlab.x, pos_matlab.y, pos_matlab.z, mn)]>0 && distance > 0)
	{
		matlab.codigoc_U.wpfin[0] = last_ual_state.ual_state.dynamic_state.position.x + (pos_unit_vector.x * distance);
		matlab.codigoc_U.wpfin[1] = last_ual_state.ual_state.dynamic_state.position.y + (pos_unit_vector.y * distance);
		matlab.codigoc_U.wpfin[2] = last_ual_state.ual_state.dynamic_state.position.z + (pos_unit_vector.z * distance);

		pos_matlab.x = (matlab.codigoc_U.wpfin[0]- matlab.codigoc_U.limsespacio[0])/scale.x;
		pos_matlab.y = (matlab.codigoc_U.wpfin[1] - matlab.codigoc_U.limsespacio[2])/scale.y;
		pos_matlab.z = (matlab.codigoc_U.wpfin[2] - matlab.codigoc_U.limsespacio[4])/scale.z;
		distance -= 0.01;
	}


	//If all is correct compute the path
	if(distance > 0 && matlab.codigoc_U.A[getIndex(last_ual_state.ual_state.dynamic_state.position.x, last_ual_state.ual_state.dynamic_state.position.y, last_ual_state.ual_state.dynamic_state.position.z, mn)]<100.0)
	{

			//This variable is used to know how much time takes to compute the path. Right now it takes between 0 and 10 seconds
			ros::Time tinit = ros::Time::now();


			//The following method call will compute the path
			matlab.step();

			ROS_INFO("Computed in secs: %f",(ros::Time::now() - tinit).toSec());
			cout << "Next WayPoint: " << matlab.codigoc_U.wpfin[0] << ";" << matlab.codigoc_U.wpfin[1] << ";" << matlab.codigoc_U.wpfin[0] << endl;

			bool b = false;
			int i= 0;
			for(; i < 10 && !b; i++)
			{
				printf("%f %f %f\n", matlab.codigoc_Y.trayecTHETALstar[i + 0],  matlab.codigoc_Y.trayecTHETALstar[i + 1000],
						matlab.codigoc_Y.trayecTHETALstar[i + 2000]);
				if (matlab.codigoc_Y.trayecTHETALstar[i + 0] == 0 && matlab.codigoc_Y.trayecTHETALstar[i + 1000] == 0 &&
						matlab.codigoc_Y.trayecTHETALstar[i + 2000] == 0)
				{
					b = true;
				}
			}



				path.clear();



				for(int j = 0; j < i-1; j++)
				{
					geometry_msgs::Point pp;
					pp.x = matlab.codigoc_Y.trayecTHETALstar[j + 0];
					pp.y = matlab.codigoc_Y.trayecTHETALstar[j + 1000];
					pp.z = matlab.codigoc_Y.trayecTHETALstar[j + 2000];

					if(j > 0 && pp.x > -30)
					{
						path.push_back(pp);

					}

				}
	}//Matlab path
	else
	{//Wait for valid conditions

		cerr << "Cant compute path.. distance: " << distance << " ocupation: " << matlab.codigoc_U.A[getIndex(last_ual_state.ual_state.dynamic_state.position.x, last_ual_state.ual_state.dynamic_state.position.y, last_ual_state.ual_state.dynamic_state.position.z, mn)] << endl;

		path.clear();


		geometry_msgs::Point pp;
		pp.x = last_ual_state.ual_state.dynamic_state.position.x;
		pp.y = last_ual_state.ual_state.dynamic_state.position.y;
		pp.z = last_ual_state.ual_state.dynamic_state.position.z;

		path.push_back(pp);
	}

	//Publish next point of the path
	if(path.size()>0)
	{
		res.way_point.x = path[0].x;
		res.way_point.y = path[0].y;
		res.way_point.z = path[0].z;

		my_waypoint_pub.publish(res);
		my_waypoint_pub_others.publish(res);
	}
}

//Publish rviz
void publishRviz()
{
	visualization_msgs::Marker marker;

	marker.header.frame_id = "/my_frame";
	marker.header.stamp = ros::Time::now();

	marker.ns = "stl";
	marker.id = 145980;

	marker.type = visualization_msgs::Marker::LINE_STRIP;

	marker.action = visualization_msgs::Marker::ADD;

	marker.pose.position.x = 0;
	marker.pose.position.y = 0;
	marker.pose.position.z = 0;

	marker.pose.orientation.x = 0;
	marker.pose.orientation.y = 0;
	marker.pose.orientation.z = 0;
	marker.pose.orientation.w = 1;

	//scale.x defines the line width
	marker.scale.x = 0.05;
	marker.scale.y = 0;
	marker.scale.z = 0;

	marker.color.r = color_r[uav_id];
	marker.color.g = color_g[uav_id];
	marker.color.b = color_b[uav_id];
	marker.color.a = 1.0f;

	marker.lifetime = ros::Duration(1.5);

	geometry_msgs::Point actual;
	actual.x = last_ual_state.ual_state.dynamic_state.position.x;

	actual.y = last_ual_state.ual_state.dynamic_state.position.y;

	actual.z = last_ual_state.ual_state.dynamic_state.position.z;

	marker.points.push_back(actual);

	for(unsigned int i=0; i< path.size();i++)
	{
		cout << "Point " << i << " :" << path[i].x << ";" << path[i].y << endl;
		marker.points.push_back(path[i]);
	}


	path_pub.publish ( marker );
	publish_rviz(matlab.codigoc_U, 1.5);

	publishVelocityVectorRviz();
}


//Publish Velocity Vector in Rviz
void publishVelocityVectorRviz()
{
	visualization_msgs::Marker marker;

		marker.header.frame_id = "/my_frame";
		marker.header.stamp = ros::Time::now();

		marker.ns = "vel_vec";
		marker.id = 145980;

		marker.type = visualization_msgs::Marker::LINE_STRIP;

		marker.action = visualization_msgs::Marker::ADD;

		marker.pose.position.x = 0;
		marker.pose.position.y = 0;
		marker.pose.position.z = 0;

		marker.pose.orientation.x = 0;
		marker.pose.orientation.y = 0;
		marker.pose.orientation.z = 0;
		marker.pose.orientation.w = 1;

		//scale.x defines the line width
		marker.scale.x = 0.1;
		marker.scale.y = 0;
		marker.scale.z = 0;

		marker.color.r = 1.0;
		marker.color.g = 1.0;
		marker.color.b = 1.0;
		marker.color.a = 1.0f;

		marker.lifetime = ros::Duration(1.5);

		geometry_msgs::Point actual;
		actual.x = last_ual_state.ual_state.dynamic_state.position.x;
		actual.y = last_ual_state.ual_state.dynamic_state.position.y;
		actual.z = last_ual_state.ual_state.dynamic_state.position.z;

		geometry_msgs::Point vel_vec_final_point;

		vel_vec_final_point.x = last_ual_state.ual_state.dynamic_state.position.x + last_ual_state.ual_state.dynamic_state.velocity.x;
		vel_vec_final_point.y = last_ual_state.ual_state.dynamic_state.position.y + last_ual_state.ual_state.dynamic_state.velocity.y;
		vel_vec_final_point.z = last_ual_state.ual_state.dynamic_state.position.z + last_ual_state.ual_state.dynamic_state.velocity.z;

		marker.points.push_back(actual);
		marker.points.push_back(vel_vec_final_point);

		path_pub.publish ( marker );
}
//Erase Collision
void eraseCollision(vector<Position> *vec)
{
	//cerr << "Tamano vec: " << (*vec).size() << endl;
	for(std::size_t i = 0; i != (*vec).size(); i++)
	{
		matlab.codigoc_U.A[getIndex((*vec)[i].x, (*vec)[i].y, (*vec)[i].z, mn)] = 0;
	}
	(*vec).clear();
}

//Add new Collision
void addCollision(vector<Position> *vec,string uav_name, PositionWithCheck actual_position, WayPointWithCruise waypoint, int colorValue)
{
	geometry_msgs::Vector3 pos_vector, pos_unit_vector, pos_matlab;
	pos_vector.x = waypoint.x - actual_position.x;
	pos_vector.y = waypoint.y - actual_position.y;
	pos_vector.z = waypoint.z - actual_position.z;


	double safety_secs = 3;
	//For distance to the next wayPoint
		//double distance = sqrt(pow(pos_vector.x,2) + pow(pos_vector.y,2) + pow(pos_vector.z,2));

	//For calculate unit vector.
	double distance = sqrt(pow(pos_vector.x,2) + pow(pos_vector.y,2) + pow(pos_vector.z,2));




	pos_unit_vector.x = pos_vector.x/distance;
	pos_unit_vector.y = pos_vector.y/distance;
	pos_unit_vector.z = pos_vector.z/distance;



	int x, x_actual = last_ual_state.ual_state.dynamic_state.position.x;//actual_position.x;
	int y, y_actual = last_ual_state.ual_state.dynamic_state.position.y;//actual_position.y;
	int z, z_actual = last_ual_state.ual_state.dynamic_state.position.z;//actual_position.z;


 //For colission.
	distance = sqrt(pow(last_ual_state.ual_state.dynamic_state.velocity.x * safety_secs,2) + pow(last_ual_state.ual_state.dynamic_state.velocity.y * safety_secs,2) + pow(last_ual_state.ual_state.dynamic_state.velocity.z * safety_secs,2));


	//Include path in collision map
	for(double i=0;i<=distance;i +=0.01)
	{
		if(uav_name.compare(node_name) < 0)
		{
			pos_matlab.x = (((pos_unit_vector.x * i) + actual_position.x)- matlab.codigoc_U.limsespacio[0])/scale.x;
			pos_matlab.y = (((pos_unit_vector.y * i) + actual_position.y ) - matlab.codigoc_U.limsespacio[2])/scale.y;
			pos_matlab.z = ((((pos_unit_vector.z * i) + actual_position.z)) - matlab.codigoc_U.limsespacio[4])/scale.z;
		}else
		{
			pos_matlab.x = (( actual_position.x)- matlab.codigoc_U.limsespacio[0])/scale.x;
			pos_matlab.y = (( actual_position.y ) - matlab.codigoc_U.limsespacio[2])/scale.y;
			pos_matlab.z = (( actual_position.z) - matlab.codigoc_U.limsespacio[4])/scale.z;
		}

		if(pos_matlab.z < 0)
			pos_matlab.z = 0;

		x = pos_matlab.x;
		y = pos_matlab.y;
		z = pos_matlab.z;

		int x_,y_,z_;

		if(actual_position.x!=x_actual || actual_position.y!=y_actual || actual_position.z !=z_actual)
		{
			for(x_ = x-2; x_ < x+4; x_++)
				for(y_ = y-2; y_ < y+4; y_++)
					for(z_ = z-2; z_ < z+4; z_++)
					{
						if(x_ > -1 && x_ < mn[0] && y_ > -1 && y_ < mn[1] && z_ > -1 && z_ < mn[2])
						{
							matlab.codigoc_U.A[getIndex(x_, y_, z_, mn)] = colorValue;

							Position inc;
							inc.x = x_;//pos_matlab.x;
							inc.y = y_;//pos_matlab.y;
							inc.z = z_;//pos_matlab.z;
							(*vec).push_back(inc);
						}
					}
		}
		//if(pos_matlab.z > -1.0)
	   // matlab.codigoc_U.A[getIndex(pos_matlab.x, pos_matlab.y, pos_matlab.z, mn)] = colorValue;

		//Set collision in vector for deleting


	}

}
//Initialize matlab
void initializeMatlab()
{
	matlab.initialize();
	memset(&matlab.codigoc_U, 0, sizeof(matlab.codigoc_U));
	memset(&matlab.codigoc_U, 0, sizeof(matlab.codigoc_Y));

	matlab.codigoc_U.limsespacio[0] = -10;
	matlab.codigoc_U.limsespacio[1] = matlab.codigoc_U.limsespacio[0] + (1.3)*20;
	matlab.codigoc_U.limsespacio[2] = -10;
	matlab.codigoc_U.limsespacio[3] = matlab.codigoc_U.limsespacio[2]  + (1.3)*20;
	matlab.codigoc_U.limsespacio[4] = 0;
	matlab.codigoc_U.limsespacio[5] = matlab.codigoc_U.limsespacio[4] + (1.5)*4;

	//[100, 100, 20] is the maximum spatial granularity allowed at the moment
	matlab.codigoc_U.n[0] = mn[0];
	matlab.codigoc_U.n[1] = mn[1];
	matlab.codigoc_U.n[2] = mn[2];


	//Initialize matlab world whit land collision.
	int firstcount = 0;
	for(int i = 0; i < mn[0]; i++)
	{
		for(int j = 0; j < mn[1]; j++)
		{
			for(int k = 0; k < mn[2]; k++)
			{

					firstcount++;

					//if(k!=0)
						matlab.codigoc_U.A[getIndex(i,j,k, mn)] = 0;
					//else
					//	matlab.codigoc_U.A[getIndex(i,j,k, mn)] = color;

			}
		}
	}

	//First the scale is computed
	scale.x = (matlab.codigoc_U.limsespacio[1] - matlab.codigoc_U.limsespacio[0])/matlab.codigoc_U.n[0];
	scale.y = (matlab.codigoc_U.limsespacio[3] - matlab.codigoc_U.limsespacio[2])/matlab.codigoc_U.n[1];
	scale.z = (matlab.codigoc_U.limsespacio[5] - matlab.codigoc_U.limsespacio[4])/matlab.codigoc_U.n[2];


}
