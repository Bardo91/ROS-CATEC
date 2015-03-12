/*
 * arbitrer2.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: Jonathan Ruiz Páez
 */
#include <ros/ros.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>

#include <uav/CommandFlags.h>
#include <uav/FlightPlan.h>
#include <uav/Position.h>
#include <uav/Rotation.h>

#define PI 3.14159265

#define EVALUATING 0 //Seleccionamos el siguiente punto al que volar
#define ROTATING   1 //Rotamos la nave hasta ver de frente el punto final
#define WAITING    2 //Esperamos a que la nave este rotada antes de moverla
#define SENDING    3 //Enviamos la ruta a la nave
using namespace std;

typedef struct{
	double x, y, z;
}DVector3;

typedef struct{
	int x, y, z;
}IVector3;



int state;
bool obstacleAvoidance;
int wait_control;

ros::Publisher pubFlightPlan;
ros::Publisher pubCommandFlags;

uav::FlightPlan fpPathFollower;
uav::FlightPlan fpObstacleAvoidance;
uav::FlightPlan actualFlightPlan, lastFlightPlan;
uav::FlightPlan rotationFlighPlan;

//Posicion del quadrotor
DVector3 actual_position;
DVector3 actual_rotation;
bool positionOK,rotationOK, pathFollowerOK, obstacleAvoidanceOK ;




void PathFollowerCallBack(const uav::FlightPlan::ConstPtr& fp) {
	cout << "Path Follower receiving..." << endl;
	pathFollowerOK = true;

	if(state!=ROTATING)
	{
	   fpPathFollower = *fp;
	   fpPathFollower.headingFlightPlan = 0;
	}
}
void ObstacleAvoidanceCallBack(const uav::FlightPlan::ConstPtr& fp) {
	cout << "Obstacle Avoidance..." << fp->velFlightPlan << endl;
	obstacleAvoidanceOK = true;

    if(state!=ROTATING)
    {
	   fpObstacleAvoidance = *fp;

	   if(fp->velFlightPlan>0)
	   {
		   cout << "New point: " << fp->position[0].x << ";" << fp->position[0].y << endl;
	   }
    }
}
void CommandFlagsCallback(const uav::CommandFlags::ConstPtr& cm) {
	cout << "Comando recibido." << endl;
	pubCommandFlags.publish(*cm);

}

void PositionCallback(const uav::Position::ConstPtr& fp) {
	//The position in normal coordinates is also stored
	actual_position.x = fp->position.x;
	actual_position.y = fp->position.y;
	actual_position.z = fp->position.z;

	positionOK = true;
}
void RotationCallback(const uav::Rotation::ConstPtr& fp) {

	actual_rotation.x = fp->rotation.x;
	actual_rotation.y = fp->rotation.y;
	actual_rotation.z = fp->rotation.z;

    rotationOK = true;
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "Arbitrer_2_0");
	ros::NodeHandle n;



	pubFlightPlan = n.advertise<uav::FlightPlan> ("quad1/flightplan", 0);
	pubCommandFlags = n.advertise<uav::CommandFlags> ("quad1/commandflags", 0);

	ros::Subscriber sub1 = n.subscribe("arbitrer1/flightplan", 1000, PathFollowerCallBack); //arbitrer_pw1/flightplan
	ros::Subscriber sub2 = n.subscribe("arbitrer_oa1/flightplan", 1000, ObstacleAvoidanceCallBack);
	ros::Subscriber sub3 = n.subscribe("arbitrer1/commandflags", 0, CommandFlagsCallback);
	ros::Subscriber sub4 = n.subscribe("quad1/position",1000,PositionCallback);
	ros::Subscriber sub5 = n.subscribe("quad1/rotation", 1000,	RotationCallback);


	//Inicializamos el estado
	state = EVALUATING;

	int modeFp = uav::FlightPlan::POSITIONHEADINGMODE;
	rotationFlighPlan.header.seq = 0;
	rotationFlighPlan.header.stamp = ros::Time::now();
	rotationFlighPlan.modeFp = modeFp;
	rotationFlighPlan.weight = 1;
	rotationFlighPlan.hFlightPlan = rotationFlighPlan.position[0].z = 0;
	rotationFlighPlan.courseFlightPlan = 0;
	rotationFlighPlan.header.frame_id = "qtester";
	rotationFlighPlan.velFlightPlan = 1.0;

	ros::AsyncSpinner spinner(4);
	spinner.start();
	obstacleAvoidance = false;

	while(ros::ok()){

		//cout << positionOK << rotationOK << pathFollowerOK << obstacleAvoidanceOK << endl;

		if(positionOK && rotationOK /*&& pathFollowerOK*/ && obstacleAvoidanceOK)
		{
			if(state==EVALUATING)
			{
				cout << "State: EVALUATING" << endl;
				lastFlightPlan = actualFlightPlan;
				//Seleccionamos el siguiente punto al que viajar
				if(fpObstacleAvoidance.velFlightPlan==0){
					//Si la velocidad del plan de vuelo de ObstacleAvoidance es 0, es que no hay obstaculo.
					if(!obstacleAvoidance){
						actualFlightPlan = fpPathFollower;
					}

				}else{
					//En caso contario, tenemos un obstaculo que evitar.
					actualFlightPlan = fpObstacleAvoidance;
					obstacleAvoidance = true;
				}

				if(lastFlightPlan.position[0].x == actualFlightPlan.position[0].x && lastFlightPlan.position[0].y == actualFlightPlan.position[0].y){
					//state = state;
				}else
				{
					state = ROTATING;
				}
			}
			else if(state == ROTATING)
			{

				//Girar el quadRotor hasta que vea de frente el punto objetivo
				geometry_msgs::Point vector;
				vector.x = actualFlightPlan.position[0].x - actual_position.x;
				vector.y = actualFlightPlan.position[0].y - actual_position.y;

				rotationFlighPlan.position[0].x = actual_position.x;
				rotationFlighPlan.position[0].y = actual_position.y;

				rotationFlighPlan.headingFlightPlan = atan(vector.y/vector.x);
				if(vector.x < 0)
				{
					rotationFlighPlan.headingFlightPlan += PI;
				}

				if(rotationFlighPlan.headingFlightPlan > PI)
				{
					rotationFlighPlan.headingFlightPlan -= 2*PI;
				}
				else if (rotationFlighPlan.headingFlightPlan < (-PI))
				{
					rotationFlighPlan.headingFlightPlan += 2*PI;
				}

				if((actualFlightPlan.headingFlightPlan + (PI/20)) > rotationFlighPlan.headingFlightPlan && (actualFlightPlan.headingFlightPlan - (PI/20)) < rotationFlighPlan.headingFlightPlan)
				{
					//Mantenemos la misma ruta anterior.

					rotationFlighPlan.headingFlightPlan = actualFlightPlan.headingFlightPlan;
				}
				else
				{
					cout << "ROTATION: Nueva ruta enviada." << endl;
					rotationFlighPlan.position[0].x = actual_position.x;
					rotationFlighPlan.position[0].y = actual_position.y;


				}
				actualFlightPlan.headingFlightPlan = rotationFlighPlan.headingFlightPlan;
				pubFlightPlan.publish(rotationFlighPlan);


				//cout << "State: ROTATING actual:" << actual_rotation.z << " deseada:" << rotationFlighPlan.headingFlightPlan << endl;
				if(actual_rotation.z < (rotationFlighPlan.headingFlightPlan + (PI/16)) && actual_rotation.z > (rotationFlighPlan.headingFlightPlan - (PI/16)))
				{
					state = WAITING;
					wait_control = 0;
				}

			}
			else if(state == WAITING)
			{
				cout << "State: WAITING" << endl;
				//Esperar un tiempo por si nos llega algun aviso de obstacle avoidance
				if(wait_control > 10)
					state = SENDING;
				else
					wait_control++;

			}
			else if(state == SENDING)
			{
				cout << "State: SENDING" << endl;
				//Si todo fue bien, enviamos el plan de vuelo al quadrotor.
				pubFlightPlan.publish(actualFlightPlan);
				state = EVALUATING;

				if(obstacleAvoidance)
				{
					geometry_msgs::Point delta;
					delta.x = fabs(actual_position.x - actualFlightPlan.position[0].x);
					delta.y = fabs(actual_position.y - actualFlightPlan.position[0].y);
					delta.z = fabs(actual_position.z - actualFlightPlan.position[0].z);
					double dt = sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);

					if(dt < 0.3)
						obstacleAvoidance = false;
				}
			}

			//Dormimos durante un cierto timepo, debemos ejecutar este bucle como minimo a 10Hz
			usleep(20000);

		}
	}

}
