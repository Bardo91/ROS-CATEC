/*
 * follower.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: catec
 */



#include "collision-helper.h"



int main(int argc, char** argv) {


	ros::init(argc, argv, "stlcollision");
	ros::NodeHandle n;

	marker_pub = n.advertise<visualization_msgs::Marker>("prueba",0);
	double discretization_rate[3];
	double side;
	string input, output;

	//Discretization rate on XYZ dimensions, or the dimensions of the collision boxes on which the model is to be divided.
	ros::param::get("~rate_x", discretization_rate[0]);
	ros::param::get("~rate_y", discretization_rate[1]);
	ros::param::get("~rate_z", discretization_rate[2]);
	//Input file
	ros::param::get("~input", input);
	//Dimensions of the thickness of a new layer of protection added for security reasons.

	ros::param::get("~side", side);
	//Output f file
	ros::param::get("~output", output);
	cout << "rate " << discretization_rate[0] << " "<< discretization_rate[1] << " "<< discretization_rate[2] << endl;
	cout << "input " << input << " output "<< output << endl;

	discreteCollisionMap(input, discretization_rate, output, side);

	/*
	discretization_rate[0] = 0.03;
	discretization_rate[1] = 0.03;
	discretization_rate[2] = 0.03;
	discreteCollisionMap("meshes/torus.stl", discretization_rate);
	*/



	/*discretization_rate[0] = 0.05;
	discretization_rate[1] = 0.05;
	discretization_rate[2] = 0.1;
	discreteCollisionMap("meshes/lander2.stl", discretization_rate);*/



/*
	discretization_rate[0] = 0.005;
	discretization_rate[1] = 0.005;
	discretization_rate[2] = 0.01;
	discreteCollisionMap("meshes/quadrotor_base2.stl", discretization_rate);
*/


	/**
	 * Now let's test the collision algorithm
	 */
/*
	//int triBoxOverlap(float boxcenter[3],float boxhalfsize[3],float triverts[3][3]);
	float boxcenter[3];
	boxcenter[0] = boxcenter[1] = boxcenter[2] = 0.5;

	float boxhalfsize[3];
	boxhalfsize[0] = boxhalfsize[1] = boxhalfsize[2] = 0.5;

	float triverts[3][3];
	//tri 0:
	triverts[0][0] = 2;
	triverts[0][1] = 0;
	triverts[0][2] = 0;
	//tri 1:
	triverts[1][0] = 2;
	triverts[1][1] = 1;
	triverts[1][2] = 0;
	//tri 2:
	triverts[2][0] = 0.5;
	triverts[2][1] = 0.5;
	triverts[2][2] = 1.5;

	cout << "is colliding? " << triBoxOverlap(boxcenter, boxhalfsize, triverts) << endl;
*/

	return (0);
}

