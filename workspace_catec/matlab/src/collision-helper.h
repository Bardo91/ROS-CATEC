/*
 * collision-helper.h
 *
 *  Created on: Jul 23, 2012
 *      Author: catec
 */

#ifndef COLLISION_HELPER_H_
#define COLLISION_HELPER_H_



#include <ros/ros.h>
#include <stdlib.h>
#include <geometry_msgs/Point.h>
#include <visualization_msgs/Marker.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>

#include "collmath.h"
#include "codigoc/codigoc.h"

using namespace std;

ros::Publisher marker_pub;


#include "collision-helper.h"

typedef struct {
	string filepath;
	string namemodel;
	int n[3];
	double step[3];
	double min[3];
	double* matrix;
}BoxCollisionFile;


class Triangle {
public:
	geometry_msgs::Point normal;
	geometry_msgs::Point points[3];
	unsigned short int count;
	Triangle()
	{
		count = 0;
	}
	void print()
	{
		cout << "tri:\n" <<	"normal " << normal. x << " " << normal. y << " " << normal. z << endl <<
				"points\n " << points[0]. x << " " << points[0]. y << " " << points[0]. z << endl <<
				 points[1]. x << " " << points[1]. y << " " << points[1]. z << endl <<
				 points[2]. x << " " << points[2]. y << " " << points[2]. z << endl <<
				 "count " << count << endl;
	}
};

void writeFile(BoxCollisionFile boxesfile);
BoxCollisionFile readFile(string filepath);
vector<Triangle> readSTL(string filepath);
void publish_rviz(BoxCollisionFile boxesfile);
void publish_rviz(BoxCollisionFile boxesfile, double t);
void publish_rviz(ExternalInputs_codigoc boxesfile, double t);
void publish_rviz(vector<Triangle> tri_list, double t);

BoxCollisionFile addRadius(BoxCollisionFile box, double side);


void discreteCollisionMap(string filepath, double discretization_rate[3], string output, double side);



int getIndex(int i,int j, int k, int n[3]);





#endif /* COLLISION_HELPER_H_ */
