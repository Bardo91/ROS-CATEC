#include <ros/ros.h>
#include <fstream>
#include <actionlib/client/simple_action_client.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/Position.h>
#include <cassert>
#include <geometry_msgs/Point.h>

#include <ros/ros.h>
#include <iostream>
#include <cmath>
#include <string.h>


using namespace std;
using namespace catec_msgs;

#include "quad.h"
#include "radio.h"
#include "UavCatecRos.h"

string node_name;

string uav_full_id[5];
string intruder_full_id[5];
int uav_id[2];
QuadPatrolling *agente[2];
class_radio *radio;
double t;
double dt=1.0/10.0;
double h_des[2];
double speed_max[2];
int dir_ini[2];

double range;
int mode;

//My next waypoint
//WayPointWithCruiseStamped my_next_waypoint[2];

//nextWayPoint
ros::Publisher my_waypoint_pub[2];

//Last state of our uav
UALStateStamped last_ual_state[2];
UALStateStamped intruder_state[3];

bool volando[2];
int num_ag;
int num_intruders;
int cambio[2];
// double path[4][2]; <--- Changed
double path[][2] = {{0.0, 0.0},{5.0, 0.0},{5.0, 5.0},{0.0, 5.0}, {0.0, 0.0},{5.0, 0.0},{5.0, 5.0},{0.0, 5.0}, {0.0, 0.0},{5.0, 0.0},{5.0, 5.0},{0.0, 5.0}, {0.0, 0.0},{5.0, 0.0},{5.0, 5.0},{0.0, 5.0}};
int tam_path = 4;
int indice[2];
double tasks_in [MAX_TASKS][TAM_TASKS];
double pos_inicial[2][2];

ofstream pos_quads[2];
ofstream pos_intruders[3];
ofstream task_assigned[2];
ofstream costes_totales[2];

std::vector<UavCatecROS> uavs;

void sendControlReferences(const ros::TimerEvent& te);

void UAV_StateCallBack(const UALStateStamped::ConstPtr& state);
void Intruder_StateCallBack(const UALStateStamped::ConstPtr& state);

void init(int _argc, char **_argv);

int main(int _argc, char** _argv) {
	cout << "Initalizing main node" << endl;
	node_name = "Patrolling_and_tracking";
	ros::init(_argc,_argv,node_name);
	ros::NodeHandle n;

	init(_argc, _argv);

	UavCatecROS uav1("3");
	UavCatecROS uav2("8");

	uavs.push_back(uav1);
	uavs.push_back(uav2);

	ros::AsyncSpinner spinner(0);
	spinner.start();

	for(unsigned i = 0; i < uavs.size(); i++){
		if(!uavs[i].hasTakeOff()){
			uavs[i].takeOff();
		}
	}

	ros::Timer timer = n.createTimer(ros::Duration(dt), sendControlReferences);

	while(ros::ok()) {
		/*for(unsigned i = 0; i < uavs.size(); i++){
			ControlReferenceRwStamped reference = uav1.reference();
			reference.c_reference_rw.position.x = i*2;
			reference.c_reference_rw.position.y = 0.0;
			reference.c_reference_rw.position.z = 1.5;
			uavs[i].move(reference);
		}*/
		sleep(10);
	}
}

void init(int _argc, char **_argv){
	num_ag = 2;
	uav_full_id[0] = "uav_3";
	uav_full_id[1] = "uav_8";

	dir_ini[0] = 1;
	dir_ini[1] = -1;

	speed_max[0] = 0.5;
	speed_max[1] = 0.7;

	h_des[0] = 1.5;
	h_des[1] = 2;

	range = 10;

	// Waypoints were defined previously

	// Intruder Data
	num_intruders=2;
	intruder_full_id[0] = "uav_5";
	intruder_full_id[1] = "uav_6";

	mode = 1;

	//-----------------------------------------------------------------------------------------------------------------
	// OutputFiles
	cout << "Opening output files" << endl;
	char nombre[50];
	for (int i=0; i<num_ag; i++) {
		sprintf(nombre,"%s_pos",uav_full_id[i].c_str());
		pos_quads[i].open(nombre, ofstream::out);
		assert(pos_quads[i]);
		sprintf(nombre,"%s_tasks",uav_full_id[i].c_str());
		task_assigned[i].open(nombre, ofstream::out);
		assert(task_assigned[i]);
		sprintf(nombre,"%s_costs",uav_full_id[i].c_str());
		costes_totales[i].open(nombre, ofstream::out);
		assert(costes_totales[i]);
	}
	for (int i=0; i<num_intruders; i++) {
		sprintf(nombre,"%s_pos",intruder_full_id[i].c_str());
		pos_intruders[i].open(nombre, ofstream::out);
		assert(pos_intruders[i]);
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Initializing tasks
	for (int i=0; i<MAX_TASKS; i++){
		for (int j=0; j<TAM_TASKS; j++){
			tasks_in[i][j]=-1;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Real main
	cout << "Initalizing main node" << endl;
	node_name = "Patrolling_and_tracking";
	ros::init(_argc,_argv,node_name);
	ros::NodeHandle n;

	string topicname;
	ros::Subscriber agente_sub[2];
	ros::Subscriber intruder_sub[3];

	// Init radio
	cout << "Initalizing radio" << endl;
	radio = new class_radio(0, 10.0, num_ag);

	// Subscribing to uav states
	cout << "Subscribing to uav states" << endl;
	for (int i=0; i<num_intruders; i++) {
		topicname=intruder_full_id[i];
		topicname.append("/ual_state");
		intruder_sub[i]=n.subscribe(topicname.c_str(), 0,Intruder_StateCallBack);
	}

	// Taking off and related...
	cout << "Configuring quads" << endl;
	for (int i=0; i<num_ag; i++) {
		//topicname= node_name;
		//topicname.append("/out_waypoint_");
		//topicname.append(uav_full_id[i]);
		//my_waypoint_pub[i] = n.advertise<WayPointWithCruiseStamped> (topicname.c_str(), 0);
		topicname=uav_full_id[i];
		topicname.append("/ual_state");
		agente_sub[i] = n.subscribe(topicname.c_str(), 0,UAV_StateCallBack);
		sleep(5);
		agente[i]= new QuadPatrolling(i, last_ual_state[i].ual_state.dynamic_state.position.x, last_ual_state[i].ual_state.dynamic_state.position.y, 0.0, speed_max[i], range, 1.0, path, tam_path, dir_ini[i]);
		agente[i]->init_cont(num_ag, 1.0);
		volando[i]=false;
		cambio[i]=0;
		indice[i]=i+1;
	}
}

void sendControlReferences(const ros::TimerEvent& te) {
	ControlReferenceRwStamped res;
	double posiciones[AG_MAX][3];
	int tam;
	int msg_sent[MSG_LENGTH];
	int msg_env[AG_MAX][MSG_LENGTH];
	int id_cont;
	int quad_cont[AG_MAX];
	double tasks_before[AG_MAX][MAX_TASKS][TAM_TASKS];
	struct Agente agentes_before[AG_MAX];
	int tam_plan=0;
	bool listo=true;
	struct Mensaje mensaje_rcv;

	t=t+dt;

	for (int i=0; i<num_ag; i++) {
		agente[i]->x=uavs[i].ualState().ual_state.dynamic_state.position.x;
		agente[i]->y=uavs[i].ualState().ual_state.dynamic_state.position.y;
		agente[i]->z=uavs[i].ualState().ual_state.dynamic_state.position.z;
		cout << "uav " << i << " state: " << agente[i]->x << ", " << agente[i]->y << ", " << agente[i]->z  << endl;
		posiciones[i][POS_X]=agente[i]->x;
		posiciones[i][POS_Y]=agente[i]->y;
		posiciones[i][POS_Z]=agente[i]->z;
		pos_quads[i] << t << ", " << agente[i]->x << ", " << agente[i]->y << ", " << agente[i]->z << ";" << endl;
		task_assigned[i] << t;
		for (int j=0; j<MAX_TASKS; j++)
			if (agente[i]->plan[j]>-1)
				task_assigned[i] << ", " << agente[i]->tasks[agente[i]->plan[j]][0];
			else
				task_assigned[i] << ", " << "-1";
		task_assigned[i] << ";" <<endl;

		costes_totales[i] << t << ", " << agente[i]->coste_mision << ";" <<endl;
	}


	for (int i=0; i<num_intruders; i++) {
		tasks_in[i][1]=(intruder_state[i].ual_state.dynamic_state.position.x-tasks_in[i][3])/dt;
		tasks_in[i][2]=(intruder_state[i].ual_state.dynamic_state.position.y-tasks_in[i][4])/dt;
		tasks_in[i][3]=intruder_state[i].ual_state.dynamic_state.position.x;
		tasks_in[i][4]=intruder_state[i].ual_state.dynamic_state.position.y;
		pos_intruders[i] << t << ", " << tasks_in[i][3] << ", " << tasks_in[i][4] << ", " << "0.0"<< ";" << endl;
	}


	for (int i=0; i<num_ag; i++) {
		tam=radio->receiving(i, posiciones, msg_env);
		if (tam==0) {
			msg_sent[0]=i;
			msg_sent[1]=10;
			msg_sent[2]=1;
			radio->sending(i, msg_sent);
		} else {
			id_cont=agente[i]->decide_cont(msg_env,tam);
			msg_sent[0]=i;
			msg_sent[1]=id_cont;
			msg_sent[2]=2;
			radio->sending(i, msg_sent);
			agente[i]->id_contactado=id_cont;
		}

		for (int k=0;k<AG_MAX;k++){
			for (int j=0;j<MSG_LENGTH;j++){
				msg_env[k][j]=VALOR_NULO;
			}
		}

		agente[i]->incr_cont (dt);
		quad_cont[i]=agente[i]->id_contactado;
		for (int j=0;j<MAX_TASKS;j++){
			for (int k=0;k<TAM_TASKS;k++){
				tasks_before[i][j][k]=agente[i]->tasks[j][k];
			}
		}

		agentes_before[i]=agente[i]->calculaAgente();
	}

	for (int i=0; i<num_ag; i++){
		if (agente[i]->id_contactado>=0 && quad_cont[agente[i]->id_contactado]==i && mode==1) {
			agente[i]->join_tasks(tasks_before[agente[i]->id_contactado],agente[i]->id_contactado);
			agente[i]->task_allocation_one (agentes_before[agente[i]->id_contactado], t);
		} else if (agente[i]->tarea_nueva==1) {
			agente[i]->autoplan(t);
			agente[i]->tarea_nueva=0;
		}

		tam_plan=0;

		while(agente[i]->plan[tam_plan]>-1){
			tam_plan++;
		}

		if (tam_plan>0) {
				agente[i]->estado=2;
				agente[i]->dir=-1;
				agente[i]->ind=0;
				res.c_reference_rw.position.x=agente[i]->tasks[agente[i]->plan[0]][3];
				res.c_reference_rw.position.y=agente[i]->tasks[agente[i]->plan[0]][4];
				res.c_reference_rw.position.z=h_des[i];

				agente[i]->monitoring_tasks (tasks_in, t);

				res.header.frame_id = node_name;
				res.header.stamp = ros::Time::now();
				//res.way_point.cruise = 0.5;

				cout << "Moving as planned" << endl;
				uavs[i].move(res);
				//my_waypoint_pub[i].publish(res);
		} else {
			agente[i]->estado=1;

			if (agente[i]->id_contactado>0 && agentes_before[agente[i]->id_contactado].estado==1) {
				mensaje_rcv.id			=agente[i]->id_contactado;
				mensaje_rcv.dir			=agentes_before[agente[i]->id_contactado].dir;
				mensaje_rcv.vel_max		=agentes_before[agente[i]->id_contactado].vel_max;
				mensaje_rcv.long_izq	=agentes_before[agente[i]->id_contactado].long_izq;
				mensaje_rcv.long_dcha	=agentes_before[agente[i]->id_contactado].long_dcha;
				mensaje_rcv.speed_izq	=agentes_before[agente[i]->id_contactado].speed_izq;
				mensaje_rcv.speed_dcha	=agentes_before[agente[i]->id_contactado].speed_dcha;
				mensaje_rcv.init_ind	=agentes_before[agente[i]->id_contactado].init_ind;
				mensaje_rcv.ind			=agentes_before[agente[i]->id_contactado].ind;
			} else{
				mensaje_rcv.id=-1;
			}
			agente[i]->pathpartition_cv (mensaje_rcv);
			indice[i]=agente[i]->ind;
			res.c_reference_rw.position.x=path[indice[i]][0];
			res.c_reference_rw.position.y=path[indice[i]][1];
			res.c_reference_rw.position.z=h_des[i];

			agente[i]->camino();

			agente[i]->monitoring_tasks (tasks_in, t);

			res.header.frame_id = node_name;
			res.header.stamp = ros::Time::now();
			//res.way_point.cruise = 0.5;

			uavs[i].move(res);
			//my_waypoint_pub[i].publish(res);
		}
	}
}

void UAV_StateCallBack(const UALStateStamped::ConstPtr& state) 
{
	const std::string& name_node = state->header.frame_id; //getPublisherName();

	for (int i=0; i<num_ag; i++)
	{
		if (strcmp(name_node.c_str(),uav_full_id[i].c_str())==0)
			last_ual_state[i] = *state;
	}

}


void Intruder_StateCallBack(const UALStateStamped::ConstPtr& state) 
{
	const std::string& name_node = state->header.frame_id; //getPublisherName();

	for (int i=0; i<num_intruders; i++)
	{
		if (strcmp(name_node.c_str(),intruder_full_id[i].c_str())==0)
		{
			intruder_state[i] = *state;
			tasks_in[i][0]=i;
		}
	}
}

