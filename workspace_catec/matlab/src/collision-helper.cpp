/*
 * collision-helper.h
 *
 *  Created on: Jul 23, 2012
 *      Author: catec
 */

#ifndef COLLISION_HELPER_CPP_
#define COLLISION_HELPER_CPP_

#include "collision-helper.h"
#include <stdexcept>

/**
 * Method used to get the index of the one-dimensional matrix on the matlab class that stores the collision information,
 * given the 3D coordinates.
 */

int getIndex(int i,int j, int k, int n[3])
{
	//if(i < n[0] && j < n[1] && k < n[2])


	if(i >= n[0])
	{
		stringstream ss;
		ss << "index i = " << i << "is bigger than n = " << n[0];
		throw std::out_of_range(ss.str());
	}
	else if(j >= n[1])
	{
		stringstream ss;
		ss << "index j = " << j << "is bigger than n = " << n[1];
		throw std::out_of_range(ss.str());
	}
	else if(k > n[2])
	{
		stringstream ss;
		ss << "index k = " << k << "is bigger than n = " << n[2];
		throw std::out_of_range(ss.str());
	}

	return i + j*n[0] + k*n[0]*n[1];
}


/**
 * Read the STL file and store all triangles.
 */
vector<Triangle> readSTL(string filepath)
{
	vector<Triangle> tri_list;

	ifstream file;
	string fileName = filepath;
	file.open(fileName.c_str(), fstream::in | fstream::binary );

	if(!file)
	{
		cout << "Error opening " << fileName << endl;
		return tri_list;
	}

	for(int i = 0; i < 80; i++)
	{
		char a;
		file.read((char*)&a, 1 );
	}

	char a[4];
	file.read((char*)a, 4 );
	unsigned int tam;
	memcpy(&tam, &a, 4);
	cout << "tam: " << tam << endl;
	ros::Time init = ros::Time::now();
	geometry_msgs::Point max, min;
	memset(&max, 0, sizeof(max));
	memset(&min, 0, sizeof(min));


	for(unsigned int i = 0; i < tam && !file.eof(); i++)
	{
		Triangle t;
		float a;
		char vv[50];
		file.read((char*)vv, 50);

		memcpy(&a, &vv[0], 4);
		t.normal.x = a;
		memcpy(&a, &vv[4], 4);
		t.normal.y = a;
		memcpy(&a, &vv[8], 4);
		t.normal.z = a;
		memcpy(&a, &vv[12], 4);
		t.points[0].x = a;
		memcpy(&a, &vv[16], 4);
		t.points[0].y = a;
		memcpy(&a, &vv[20], 4);
		t.points[0].z = a;
		memcpy(&a, &vv[24], 4);
		t.points[1].x = a;
		memcpy(&a, &vv[28], 4);
		t.points[1].y = a;
		memcpy(&a, &vv[32], 4);
		t.points[1].z = a;
		memcpy(&a, &vv[36], 4);
		t.points[2].x = a;
		memcpy(&a, &vv[40], 4);
		t.points[2].y = a;
		memcpy(&a, &vv[44], 4);
		t.points[2].z = a;
		memcpy(&t.count, &vv[48], 2);

		max.x = std::max(max.x, t.points[0].x);
		max.x = std::max(max.x, t.points[1].x);
		max.x = std::max(max.x, t.points[2].x);


		max.y = std::max(max.y, t.points[0].y);
		max.y = std::max(max.y, t.points[1].y);
		max.y = std::max(max.y, t.points[2].y);

		max.z = std::max(max.z, t.points[0].z);
		max.z = std::max(max.z, t.points[1].z);
		max.z = std::max(max.z, t.points[2].z);


		min.x = std::min(min.x, t.points[0].x);
		min.x = std::min(min.x, t.points[1].x);
		min.x = std::min(min.x, t.points[2].x);


		min.y = std::min(min.y, t.points[0].y);
		min.y = std::min(min.y, t.points[1].y);
		min.y = std::min(min.y, t.points[2].y);

		min.z = std::min(min.z, t.points[0].z);
		min.z = std::min(min.z, t.points[1].z);
		min.z = std::min(min.z, t.points[2].z);

		//t.print();
		tri_list.push_back(t);
	}

	return tri_list;
}

/**
 * Notice that discretization_rate = (limsespacio[1]-limsespacio[0]/n[0];
 */
void discreteCollisionMap(string filepath, double discretization_rate[3], string output, double side)
{

	/**
	 * Read the STL file and store all triangles.
	 */
	vector<Triangle> tri_list;

	ifstream file;
	string fileName = filepath;
	file.open(fileName.c_str(), fstream::in | fstream::binary );

	if(!file)
	{
		cout << "Error opening " << fileName << endl;
		return;
	}

	for(int i = 0; i < 80; i++)
	{
		char a;
		file.read((char*)&a, 1 );
	}

	char a[4];
	file.read((char*)a, 4 );
	unsigned int tam;
	memcpy(&tam, &a, 4);
	cout << "tam: " << tam << endl;
	ros::Time init = ros::Time::now();
	geometry_msgs::Point max, min;
	memset(&max, 0, sizeof(max));
	memset(&min, 0, sizeof(min));


	for(unsigned int i = 0; i < tam && !file.eof(); i++)
	{
		Triangle t;
		float a;
		char vv[50];
		file.read((char*)vv, 50);

		memcpy(&a, &vv[0], 4);
		t.normal.x = a;
		memcpy(&a, &vv[4], 4);
		t.normal.y = a;
		memcpy(&a, &vv[8], 4);
		t.normal.z = a;
		memcpy(&a, &vv[12], 4);
		t.points[0].x = a;
		memcpy(&a, &vv[16], 4);
		t.points[0].y = a;
		memcpy(&a, &vv[20], 4);
		t.points[0].z = a;
		memcpy(&a, &vv[24], 4);
		t.points[1].x = a;
		memcpy(&a, &vv[28], 4);
		t.points[1].y = a;
		memcpy(&a, &vv[32], 4);
		t.points[1].z = a;
		memcpy(&a, &vv[36], 4);
		t.points[2].x = a;
		memcpy(&a, &vv[40], 4);
		t.points[2].y = a;
		memcpy(&a, &vv[44], 4);
		t.points[2].z = a;
		memcpy(&t.count, &vv[48], 2);

		max.x = std::max(max.x, t.points[0].x);
		max.x = std::max(max.x, t.points[1].x);
		max.x = std::max(max.x, t.points[2].x);


		max.y = std::max(max.y, t.points[0].y);
		max.y = std::max(max.y, t.points[1].y);
		max.y = std::max(max.y, t.points[2].y);

		max.z = std::max(max.z, t.points[0].z);
		max.z = std::max(max.z, t.points[1].z);
		max.z = std::max(max.z, t.points[2].z);


		min.x = std::min(min.x, t.points[0].x);
		min.x = std::min(min.x, t.points[1].x);
		min.x = std::min(min.x, t.points[2].x);


		min.y = std::min(min.y, t.points[0].y);
		min.y = std::min(min.y, t.points[1].y);
		min.y = std::min(min.y, t.points[2].y);

		min.z = std::min(min.z, t.points[0].z);
		min.z = std::min(min.z, t.points[1].z);
		min.z = std::min(min.z, t.points[2].z);

		//t.print();
		tri_list.push_back(t);
	}

	cout << "elapsed time: " << (ros::Time::now() - init).toSec() << " size of vector: " << tri_list.size() << endl;

	cout << "maxmin bounds: max " << max.x << " " << max.y << " " << max.z << " min " << min.x << " " << min.y << " " << min.z << endl;

	int n[3];
	n[0] = (int)ceil((max.x-min.x)/discretization_rate[0]);
	n[1] = (int)ceil((max.y-min.y)/discretization_rate[1]);
	n[2] = (int)ceil((max.z-min.z)/discretization_rate[2]);

	double* d = new double[ n[0]*n[1]*n[2] ];

	memset(d, 0, n[0]*n[1]*n[2]*sizeof(double));

	cout << "d dimensions are " << n[0] << " " << n[1] << " " << n[2] << endl;

	if(n[0] > 100 || n[1] > 100  || n[2] > 20 )
	{
		cout << "discretization steps are too big. Maximum is 100*100*20" << endl;
		return ;
	}

	cout << "OK " << endl;

	int mycount = 0;

	for (int i = 0; i< n[0]; i++ )
	{


		for(int j = 0; j < n[1]; j++)
		{

			for(int k = 0; k < n[2]; k++)
			{
				float boxcenter[3];

				float boxhalfsize[3];

				boxcenter[0] = min.x + (i + 0.5)*discretization_rate[0];
				boxcenter[1] = min.y + (j + 0.5)*discretization_rate[1];
				boxcenter[2] = min.z + (k + 0.5)*discretization_rate[2];

				boxhalfsize[0] = discretization_rate[0]/2;
				boxhalfsize[1] = discretization_rate[1]/2;
				boxhalfsize[2] = discretization_rate[2]/2;


				int ncollisions = 0;
				for(unsigned int p = 0; p < tri_list.size() && ncollisions == 0; p++)
				{

					float triverts[3][3];

					//tri 0:
					triverts[0][0] = tri_list[p].points[0].x;
					triverts[0][1] = tri_list[p].points[0].y;
					triverts[0][2] = tri_list[p].points[0].z;
					//tri 1:
					triverts[1][0] = tri_list[p].points[1].x;
					triverts[1][1] = tri_list[p].points[1].y;
					triverts[1][2] = tri_list[p].points[1].z;
					//tri 2:
					triverts[2][0] = tri_list[p].points[2].x;
					triverts[2][1] = tri_list[p].points[2].y;
					triverts[2][2] = tri_list[p].points[2].z;
					ncollisions=triBoxOverlap(boxcenter, boxhalfsize, triverts);
					if(ncollisions)
					{
						//cout << "IS colliding vertex " << getIndex(i,j,k,n) << endl;
						//d[getIndex(i,j,k,n)] = 10000;
					}
				}
				if (ncollisions > 0)
				{
					mycount++;
					d[getIndex(i,j,k,n)] = 10000;
				}

			}
		}
	}

	cout << "COUNT COLLISIONS " << mycount << endl;




	BoxCollisionFile boxesfile;
	boxesfile.filepath = output;
	boxesfile.namemodel = "quadrotor";
	boxesfile.n[0] = n[0];
	boxesfile.n[1] = n[1];
	boxesfile.n[2] = n[2];
	boxesfile.step[0] = discretization_rate[0];
	boxesfile.step[1] = discretization_rate[1];
	boxesfile.step[2] = discretization_rate[2];
	boxesfile.min[0] = min.x;
	boxesfile.min[1] = min.y;
	boxesfile.min[2] = min.z;
	boxesfile.matrix = d;

	sleep(2);
	//publish_rviz(boxesfile);

	//writeFile(boxesfile);
	//BoxCollisionFile boxes2 = readFile(boxesfile.filepath);
	//BoxCollisionFile boxes2 = addRadius(readFile(boxesfile.filepath), side);

	BoxCollisionFile boxes2 = addRadius(boxesfile, side);

	writeFile(boxes2);

	publish_rviz(boxes2);



	return;
}


void publish_rviz(ExternalInputs_codigoc boxesfile, double t)
{
	visualization_msgs::Marker marker;

	marker.header.frame_id = "/my_frame";
	marker.header.stamp = ros::Time::now();

	marker.ns = "stl";
	marker.id = 0;

	marker.type = visualization_msgs::Marker::CUBE;

	marker.action = visualization_msgs::Marker::ADD;

	marker.pose.position.x = 0;
	marker.pose.position.y = 0;
	marker.pose.position.z = 0;

	marker.pose.orientation.x = 0;
	marker.pose.orientation.y = 0;
	marker.pose.orientation.z = 0;
	marker.pose.orientation.w = 1;

	marker.scale.x = (boxesfile.limsespacio[1]-boxesfile.limsespacio[0])/boxesfile.n[0];
	marker.scale.y = (boxesfile.limsespacio[3]-boxesfile.limsespacio[2])/boxesfile.n[1];
	marker.scale.z = (boxesfile.limsespacio[5]-boxesfile.limsespacio[4])/boxesfile.n[2];

	cout << "RVIZ SCALE: " << marker.scale.x << " " << marker.scale.y << " " << marker.scale.z << endl;
	cout << "RVIZ MIN: " << boxesfile.limsespacio[0] << " " << boxesfile.limsespacio[2] << " " << boxesfile.limsespacio[4] << endl;
	cout << "RVIZ MAX: " << boxesfile.limsespacio[1] << " " << boxesfile.limsespacio[3] << " " << boxesfile.limsespacio[5] << endl;
	cout << "RVIZ MAX: " << boxesfile.n[0] << " " << boxesfile.n[1] << " " << boxesfile.n[2] << endl;


	ros::Time tinit = ros::Time::now();

	marker.color.r = 0.0f;
	marker.color.g = 1.0f;
	marker.color.b = 0.0f;
	marker.color.a = 1.0f;

	marker.lifetime = ros::Duration(t);

	int mycount = 0;

	int mn[] = {100,100,20};

	for (int i = 0; i< 100; i++ )
	{
		for(int j = 0; j < 100; j++)
		{
			for(int k = 0; k < 20; k++)
			{
				float boxcenter[3];

				//float boxhalfsize[3];

				boxcenter[0] = boxesfile.limsespacio[0] + (i + 0.0)*marker.scale.x;
				boxcenter[1] = boxesfile.limsespacio[2] + (j + 0.0)*marker.scale.y;
				boxcenter[2] = boxesfile.limsespacio[4] + (k + 0.0)*marker.scale.z;

				if(boxesfile.A[getIndex(i,j,k, mn)] > 0)
				{
					mycount++;
					usleep(400);
					marker.id = getIndex(i,j,k, mn);
					marker.pose.position.x = boxcenter[0];
					marker.pose.position.y = boxcenter[1];
					marker.pose.position.z = boxcenter[2];

					marker.color.r = ((double)i)/((double)boxesfile.n[0]);
					marker.color.g = ((double)j)/((double)boxesfile.n[1]);
					marker.color.b = ((double)k)/((double)boxesfile.n[2]);


					marker_pub.publish ( marker );

					/*geometry_msgs::Point p;
					p.x = boxcenter[0];
					p.y = boxcenter[1];
					p.z = boxcenter[2];

					marker.points.push_back(p);

					std_msgs::ColorRGBA c;
					c.r = ((double)i)/((double)boxesfile.n[0]);
					c.g = ((double)j)/((double)boxesfile.n[1]);
					c.b = ((double)k)/((double)boxesfile.n[2]);
					c.a = 1.0f;
					marker.colors.push_back(c);*/

				}

			}
		}
	}




	cout << "RVIZ publishing done in secs: " << (ros::Time::now() - tinit).toSec() << endl;

	cout << "RVIZ COUNT:  " << mycount << endl;

}



void publish_rviz(BoxCollisionFile boxesfile, double t)
{

	//sleep(3);
	visualization_msgs::Marker marker;

	marker.header.frame_id = "/my_frame";
	marker.header.stamp = ros::Time::now();

	marker.ns = "stl";
	marker.id = 0;

	marker.type = visualization_msgs::Marker::CUBE;

	marker.action = visualization_msgs::Marker::ADD;

	marker.pose.position.x = 0;
	marker.pose.position.y = 0;
	marker.pose.position.z = 0;

	marker.pose.orientation.x = 0;
	marker.pose.orientation.y = 0;
	marker.pose.orientation.z = 0;
	marker.pose.orientation.w = 1;

	marker.scale.x = boxesfile.step[0];
	marker.scale.y = boxesfile.step[1];
	marker.scale.z = boxesfile.step[2];

	cout << "RVIZ SCALE: " << marker.scale.x << " " << marker.scale.y << " " << marker.scale.z << endl;

	marker.color.r = 0.0f;
	marker.color.g = 1.0f;
	marker.color.b = 0.0f;
	marker.color.a = 1.0f;


	int mycount = 0;

	for (int i = 0; i< boxesfile.n[0]; i++ )
	{
		for(int j = 0; j < boxesfile.n[1]; j++)
		{
			for(int k = 0; k < boxesfile.n[2]; k++)
			{
				float boxcenter[3];

				//float boxhalfsize[3];

				boxcenter[0] = boxesfile.min[0] + (i + 0.5)*boxesfile.step[0];
				boxcenter[1] = boxesfile.min[1] + (j + 0.5)*boxesfile.step[1];
				boxcenter[2] = boxesfile.min[2] + (k + 0.5)*boxesfile.step[2];

				/*boxhalfsize[0] = boxesfile.step[0]/2;
				boxhalfsize[1] = boxesfile.step[1]/2;
				boxhalfsize[2] = boxesfile.step[2]/2;*/

				if(boxesfile.matrix[getIndex(i,j,k, boxesfile.n)] > 0)
				{
					mycount++;
					usleep(400);
					marker.id = getIndex(i,j,k, boxesfile.n);
					marker.pose.position.x = boxcenter[0];
					marker.pose.position.y = boxcenter[1];
					marker.pose.position.z = boxcenter[2];

					//cout << "marker " << marker.id << " position: " << marker.pose.position.x << " " << marker.pose.position.y << " " << marker.pose.position.z << endl;


					marker.color.r = ((double)i)/((double)boxesfile.n[0]);
					marker.color.g = ((double)j)/((double)boxesfile.n[1]);
					marker.color.b = ((double)k)/((double)boxesfile.n[2]);

					marker.lifetime = ros::Duration(t);

					marker_pub.publish ( marker );
				}
			}
		}
	}



	cout << "RVIZ COUNT:  " << mycount << " lifetime: " << marker.lifetime << endl;
}


void publish_rviz(vector<Triangle> tri_list, double t)
{

	//sleep(3);
	visualization_msgs::Marker marker;

	marker.header.frame_id = "/my_frame";
	marker.header.stamp = ros::Time::now();

	marker.ns = "std";
	marker.id = 600000;

	marker.type = visualization_msgs::Marker::TRIANGLE_LIST;

	marker.action = visualization_msgs::Marker::ADD;

	marker.pose.position.x = -2.5;
	marker.pose.position.y = -2.4;
	marker.pose.position.z = -1.1;

	marker.pose.orientation.x = 0;
	marker.pose.orientation.y = 0;
	marker.pose.orientation.z = 0;
	marker.pose.orientation.w = 1;

	marker.scale.x = 1;
	marker.scale.y = 1;
	marker.scale.z = 1;

	cout << "RVIZ SCALE: " << marker.scale.x << " " << marker.scale.y << " " << marker.scale.z << endl;

	marker.color.r = 0.7f;
	marker.color.g = 0.0f;
	marker.color.b = 0.0f;
	marker.color.a = 1.0f;

	marker.lifetime = ros::Duration(t);

	std_msgs::ColorRGBA color;
	int mycount = 0;
	int size = tri_list.size();

	for (vector<Triangle>::iterator it = tri_list.begin(); it != tri_list.end(); it++ )
	{
		marker.points.push_back(it->points[0]);
		marker.points.push_back(it->points[1]);
		marker.points.push_back(it->points[2]);

		color.r = (float)mycount/size;
		color.g = (float)mycount/size;
		color.b = (float)mycount/size;
		color.a = 1.0f;
		marker.colors.push_back(color);
		marker.colors.push_back(color);
		marker.colors.push_back(color);

		mycount++;

	}
	marker.mesh_use_embedded_materials = false;

	marker_pub.publish ( marker );

	cout << "RVIZ COUNT:  " << mycount << endl;
}



void publish_rviz(BoxCollisionFile boxesfile)
{

	publish_rviz(boxesfile, 0);
}

/**
 * This function stores the collision matrix in a binary file. The binary format allows the file to be compact.
 * The collision matrix is stored in a file to be loaded later, without having to compute the matrix every time.
 * The file format is as follows:
 *
 * name: The first 80 char characters. It's the name of the model.
 * n: 3 ints. Indicates the number of rows on each axis (X, Y , Z).
 * step: 3 doubles. Indicates the discrete stepping (in meters) on each axis (X, Y , Z).
 * min: 3 doubles. Indicates the position (in meters) on the axis of the lowest point of the matrix.
 * matrix: N[0]*N[1]*N[2] doubles. The collision matrix.
 *
 */

void writeFile(BoxCollisionFile boxesfile)
{
	ofstream file;
	file.open( boxesfile.filepath.c_str(), fstream::out | fstream::binary );
	cout << "writing to " <<  boxesfile.filepath.c_str() << endl;

	if(!file)
	{
		cout << "Error opening " << boxesfile.filepath << endl;
		return;
	}

	for(unsigned int i = 0; i < 80; i++)
	{
		char a = 0;
		if(i < boxesfile.namemodel.size() )
		{
			a = boxesfile.namemodel[i];
		}
		file.write(&a, 1 );
	}
	file.write((char*)boxesfile.n, 3*sizeof(int));
	file.write((char*)boxesfile.step, 3*sizeof(double));
	file.write((char*)boxesfile.min, 3*sizeof(double));

	file.write( (char*) boxesfile.matrix, boxesfile.n[0]*boxesfile.n[1]*boxesfile.n[2]*sizeof(double));

	file.close();
	cout << "end" << endl;

	return;
}

BoxCollisionFile readFile(string filepath)
{
	BoxCollisionFile boxesfile;


	ifstream file;
	boxesfile.filepath = filepath;

	file.open(boxesfile.filepath.c_str(), fstream::in | fstream::binary );


	if(!file)
	{
		cout << "Error opening " << boxesfile.filepath << endl;
		return boxesfile;
	}
	cout << "READING" << endl;

	char buffer[80];
	file.read(buffer, 80 );
	boxesfile.namemodel = string(buffer);

	cout << boxesfile.namemodel << endl;
	file.read( (char*)boxesfile.n, 3*sizeof(int) );
	file.read( (char*)boxesfile.step, 3*sizeof(double) );
	file.read( (char*)boxesfile.min, 3*sizeof(double) );
	if(boxesfile.n[0] > 0 && boxesfile.n[1] > 0 && boxesfile.n[2] > 0)
	{
		boxesfile.matrix = new double[ boxesfile.n[0]*boxesfile.n[1]*boxesfile.n[2] ];
		file.read( (char*)boxesfile.matrix, boxesfile.n[0]*boxesfile.n[1]*boxesfile.n[2]*sizeof(double) );
	}
	else
	{
		boxesfile.matrix = NULL;
	}
	file.close();

	cout << "READING END" << endl;

	return boxesfile;
}

void quadFill(int a, int b, int c, BoxCollisionFile r,  int addn[3])
{
	for (int i = a ; i < a + 2*addn[0]; i++)
	{
		 for (int j = b ; j < b + 2*addn[1]; j++)
		 {
			 for (int k = c; k< c + 2*addn[2]; k++)
			 {
				 r.matrix[getIndex(i,j,k, r.n)] = 10000;
			 }
		 }
	 }
}

BoxCollisionFile addRadius(BoxCollisionFile box, double side)
{
	//first we'll need to create a bigger matrix so that the new radius margins fit in.

	double radius = side/2;
	 BoxCollisionFile r = box;


	 if( radius > 0.0)
	 {
		 ROS_INFO("Doing the thing!\n");
		 int addn[3];

		 addn[0] = ((int)ceil(radius/box.step[0]));
		 addn[1] = ((int)ceil(radius/box.step[1]));
		 addn[2] = ((int)ceil(radius/box.step[2]));
		 cout << "addn " << addn[0] << " " << addn[1] << " " << addn[2] << endl;

		 r.n[0] = box.n[0] + 2 * addn[0];
		 r.n[1] = box.n[1] + 2 * addn[1];
		 r.n[2] = box.n[2] + 2 * addn[2];

		 r.min[0] = box.min[0] - addn[0] * box.step[0];
		 r.min[1] = box.min[1] - addn[1] * box.step[1];
		 r.min[2] = box.min[2] - addn[2] * box.step[2];

		 r.matrix = new double[ r.n[0]*r.n[1]*r.n[2] ];
		 memset(r.matrix, 0, r.n[0]*r.n[1]*r.n[2]*sizeof(double));


		 for (int i = 0; i < box.n[0]; i++)
		 {
			 for (int j = 0; j < box.n[1]; j++)
			 {
				 for (int k = 0; k< box.n[2]; k++)
				 {
					 //r.matrix[getIndex(i + addn[0], j + addn[1], k + addn[2], r.n)] = box.matrix[ getIndex(i, j, k, box.n) ];
					 if(box.matrix[ getIndex(i, j, k, box.n) ] > 0)
					 {
						 quadFill(i,j,k, r, addn);
					 }
				 }
			 }
		 }
	 }


	 return r;

}



#endif /* COLLISION_HELPER_CPP_ */
