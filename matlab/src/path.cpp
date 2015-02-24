/*
 * follower.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: catec
 */


#include <ros/ros.h>
#include <stdlib.h>
#include "codigoc/codigoc.h"

using namespace std;
/*
real_T fa(int x, int y, int z, real_T *A)
{
	return (A)[x-1+(y-1)*100  +(z-1)*10000];
}*/


real_T* fb(int x, int y, int z, real_T *A)
{
	return &(A[x-1+(y-1)*100  +(z-1)*10000]);
}

void addBox(real_T *A, int ax, int ay, int az, int bx, int by, int bz )
{
	int med = 0;
	if(bx < ax){
		med = bx;
		bx = ax;
		ax = med;
	}
	if(by < ay){
		med = by;
		by = ay;
		ay = med;
	}
	if(bz < az){
		med = bz;
		bz = az;
		az = med;
	}
	for(int i = ax; i <= bx; i++)
	{
		for(int j = ay; j <= by; j++)
		{
			for(int k = az; k <= bz; k++)
			{
				*fb(i, j, k, A) = 10000;
			}
		}
	}
}

int main(int argc, char** argv) {


	printf("create codigocModelClass\n");

	ros::init(argc, argv, "path");
	ros::NodeHandle n;

	codigocModelClass matlab;

	printf("initialize\n");
	matlab.initialize();
	printf("initialized\n");

	memset(&matlab.codigoc_U, 0, sizeof(matlab.codigoc_U));
	memset(&matlab.codigoc_U, 0, sizeof(matlab.codigoc_Y));

	int max = 100;

	//Límites de la zona de validez.
	matlab.codigoc_U.limsespacio[0] = 1;
	matlab.codigoc_U.limsespacio[1] = max;
	matlab.codigoc_U.limsespacio[2] = 1;
	matlab.codigoc_U.limsespacio[3] = max;
	matlab.codigoc_U.limsespacio[4] = 1;
	matlab.codigoc_U.limsespacio[5] = 20;

	matlab.codigoc_U.wpini[0] = 3;
	matlab.codigoc_U.wpini[1] = max/2;
	matlab.codigoc_U.wpini[2] = 10;

	matlab.codigoc_U.wpfin[0] = max-3;
	matlab.codigoc_U.wpfin[1] = max/2;
	matlab.codigoc_U.wpfin[2] = 10;

	matlab.codigoc_U.n[0] = max;
	matlab.codigoc_U.n[1] = max;
	matlab.codigoc_U.n[2] = 20;
	ros::Time to = ros::Time::now();

	printf("fill\n");
	for(int i = 1; i <= max; i++)
	{
		for(int j = 1; j <= max; j++)
		{
			//Contornos/Bordes:
			*fb(i, j,1, matlab.codigoc_U.A) = 10000;
			*fb(i, j,20, matlab.codigoc_U.A) = 10000;

			*fb(i, 1, j, matlab.codigoc_U.A) = 10000;
			*fb(i, max, j, matlab.codigoc_U.A) = 10000;

			*fb(1, i, j, matlab.codigoc_U.A) = 10000;
			*fb(max, i, j, matlab.codigoc_U.A) = 10000;


			//Otros obstáculos:

			/*if(j <=7)
			{
				*fb(4, i, j, matlab.codigoc_U.A) = 10000;
			}
			if(j >=3)
			{
				*fb(6, i, j, matlab.codigoc_U.A) = 10000;
			}*/

		}
	}
	//Contornos/Bordes
	addBox( matlab.codigoc_U.A, 1,1,1,1, max , 20);
	addBox( matlab.codigoc_U.A, max,1,1,max, max , 20);


	addBox( matlab.codigoc_U.A, 1,1,1,max, 1 , 20);
	addBox( matlab.codigoc_U.A, 1,max,1,max, max , 20);


	addBox( matlab.codigoc_U.A, 1,1,1,max, max , 1);
	addBox( matlab.codigoc_U.A, 1,1,20,max, max , 20);

	//Otros obstáculos
	addBox( matlab.codigoc_U.A, 8,1,1,8, max , 15);

	addBox( matlab.codigoc_U.A, 88,1,5,88, max , 20);



	printf("end fill, duration %f sec\n", (ros::Time::now() - to ).toSec() );
	printf("start calc\n");
	to = ros::Time::now();

	matlab.step();


	printf("end calc, duration %f sec\n", (ros::Time::now() - to ).toSec() );

	bool b = 0;
	int i = 0;
	while (!b && i < 10)
	{
		printf("%f %f %f\n", matlab.codigoc_Y.trayecTHETALstar[i + 0],  matlab.codigoc_Y.trayecTHETALstar[i + 1000], matlab.codigoc_Y.trayecTHETALstar[i + 2000]);
		i++;
	}
	//ros::spin();

	return (0);
}
