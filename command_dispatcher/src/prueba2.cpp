#include <ros/ros.h>
#include <fstream>
#include <actionlib/client/simple_action_client.h>
#include <catec_actions_msgs/GoToWayPointsAction.h>
#include <catec_actions_msgs/LandAction.h>
#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/TargetAction.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/Target.h>
#include <catec_msgs/WayPoint.h>
#include <catec_msgs/WayPointWithCruise.h>
#include <catec_msgs/WayPointWithCruiseStamped.h>
#include <catec_msgs/Position.h>

#include <geometry_msgs/Point.h>

#include <ros/ros.h>
#include <iostream>
#include <cmath>

#include <iostream>



using namespace std;
using namespace catec_actions_msgs;
using namespace catec_msgs;

#include "strings_tools.h"
#include "quad.h"
#include "radio.h"

string node_name;

string uav_full_id[5];
int uav_id[2];
class_quad *agente[2];
class_radio *radio;
double t;
double dt=1.0/10.0;
double h_des[2];

double x_off;
double y_off;

double range;


typedef actionlib::SimpleActionClient<LandAction> LandClient;
typedef actionlib::SimpleActionClient<TakeOffAction> TakeOffClient;

//My next waypoint
WayPointWithCruiseStamped my_next_waypoint[2];

//nextWayPoint
ros::Publisher my_waypoint_pub[2];

//Last state of our uav
UALStateStamped last_ual_state[2];

UALStateStamped intruder_state[3];

LandClient *cLand0;
TakeOffClient *cTakeOff0;
LandClient *cLand1;
TakeOffClient *cTakeOff1;

bool LandGoalSended[2];
bool TakeOffGoalSended[2];
bool volando[2];
int num_ag;
int num_intruders;
int cambio[2];
double path[4][2];
int indice[2];
double tasks_in [MAX_TASKS][TAM_TASKS];
double pos_inicial[2][2];
TakeOffGoal tOff_goal[2];

ofstream pos_quads[2];
ofstream pos_intruders[3];
ofstream task_assigned[2];
ofstream costes_totales[2];

void land_Active_CB0();
void land_Feedback_CB0(const LandFeedbackConstPtr& feedback);
void land_Done_CB0(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result);

void tOff_Active_CB0();
void tOff_Feedback_CB0(const TakeOffFeedbackConstPtr& feedback);
void tOff_Done_CB0(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result);

void land_Active_CB1();
void land_Feedback_CB1(const LandFeedbackConstPtr& feedback);
void land_Done_CB1(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result);

void tOff_Active_CB1();
void tOff_Feedback_CB1(const TakeOffFeedbackConstPtr& feedback);
void tOff_Done_CB1(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result);

/*
 * Callbacks for Land
 *
 *
 * */

void land_Active_CB0()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Land Active.");
}

void land_Feedback_CB0(const LandFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que se cambie de etapa en el aterrizaje.
	ROS_INFO("Land phase: %d", feedback->phase);
}

void land_Done_CB0(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Land finished in state [%s]", state.toString().c_str());
	ROS_INFO("Land task return: [%s]", landMessage(result).c_str());
}

void land_Active_CB1()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Land Active.");
}

void land_Feedback_CB1(const LandFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que se cambie de etapa en el aterrizaje.
	ROS_INFO("Land phase: %d", feedback->phase);
}

void land_Done_CB1(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Land finished in state [%s]", state.toString().c_str());
	ROS_INFO("Land task return: [%s]", landMessage(result).c_str());
}

/*
 * Callbacks for TakeOff
 *
 *
 * */

void tOff_Active_CB0()
{
	//Se ejecutara cuando la tarea pase al estado activo
	pos_inicial[0][0]=last_ual_state[0].ual_state.dynamic_state.position.x;
	pos_inicial[0][1]=last_ual_state[0].ual_state.dynamic_state.position.y;
	ROS_INFO("Take Off Active.");
}

void tOff_Feedback_CB0(const TakeOffFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que se cambie de etapa en el despegue.
	ROS_INFO("Take Off phase: %d", feedback->phase);
}

void tOff_Done_CB0(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Take off finished in state [%s]", state.toString().c_str());
	ROS_INFO("Take off task return: [%s]", takeOffMessage(result).c_str());
//volando[0]=true;
	pos_inicial[0][0]=last_ual_state[0].ual_state.dynamic_state.position.x;
	pos_inicial[0][1]=last_ual_state[0].ual_state.dynamic_state.position.y;
	sleep(10);
	cTakeOff1->sendGoal(tOff_goal[1], &tOff_Done_CB1, &tOff_Active_CB1, &tOff_Feedback_CB1);
	
}

void tOff_Active_CB1()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Take Off Active.");
	pos_inicial[1][0]=last_ual_state[1].ual_state.dynamic_state.position.x;
	pos_inicial[1][1]=last_ual_state[1].ual_state.dynamic_state.position.y;
}

void tOff_Feedback_CB1(const TakeOffFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que se cambie de etapa en el despegue.
	ROS_INFO("Take Off phase: %d", feedback->phase);
}

void tOff_Done_CB1(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Take off finished in state [%s]", state.toString().c_str());
	ROS_INFO("Take off task return: [%s]", takeOffMessage(result).c_str());
//volando[1]=true;
	pos_inicial[1][0]=last_ual_state[1].ual_state.dynamic_state.position.x;
	pos_inicial[1][1]=last_ual_state[1].ual_state.dynamic_state.position.y;
	
}

void sendControlReferences(const ros::TimerEvent& te)
{

	WayPointWithCruiseStamped res;
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

	t=t+dt;



	
	
	for (int i=0; i<num_ag; i++)
	{
		agente[i]->x=last_ual_state[i].ual_state.dynamic_state.position.x;
		agente[i]->y=last_ual_state[i].ual_state.dynamic_state.position.y;
		agente[i]->z=last_ual_state[i].ual_state.dynamic_state.position.z;
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


	for (int i=0; i<num_intruders; i++)
	{
		
		
		tasks_in[i][1]=(intruder_state[i].ual_state.dynamic_state.position.x-tasks_in[i][3])/dt;
		tasks_in[i][2]=(intruder_state[i].ual_state.dynamic_state.position.y-tasks_in[i][4])/dt;
		tasks_in[i][3]=intruder_state[i].ual_state.dynamic_state.position.x;
		tasks_in[i][4]=intruder_state[i].ual_state.dynamic_state.position.y;
		pos_intruders[i] << t << ", " << tasks_in[i][3] << ", " << tasks_in[i][4] << ", " << "0.0"<< ";" << endl;
	}


	for (int i=0;i<num_ag;i++)
		listo=listo && volando[i];

	if (listo==false)
	{

	    for (int i=0;i<num_ag;i++)
	    if (volando[i]==false)
	    {
		res.way_point.x=pos_inicial[i][0];
	        res.way_point.y=pos_inicial[i][1];
	        res.way_point.z=h_des[i];
		if ((agente[i]->z-h_des[i])>-0.2)
			volando[i]=true;
		res.header.frame_id = node_name;
		res.header.stamp = ros::Time::now();
		res.way_point.cruise = 0.5;

		my_waypoint_pub[i].publish(res);
            }
	}
	else
	{



	for (int i=0; i<num_ag; i++)
	{
		if (volando[i]==true)
		{
			tam=radio->receiving(i, posiciones, msg_env);
			if (tam==0)
			{
				msg_sent[0]=i;
				msg_sent[1]=10;
				msg_sent[2]=1;
				radio->sending(i, msg_sent);
			}
			else
			{
				id_cont=agente[i]->decide_cont(msg_env,tam);
				msg_sent[0]=i;
				msg_sent[1]=id_cont;
				msg_sent[2]=2;
				radio->sending(i, msg_sent);
				agente[i]->id_contactado=id_cont;
			}
			
			for (int k=0;k<AG_MAX;k++)
				for (int j=0;j<MSG_LENGTH;j++)
					msg_env[k][j]=VALOR_NULO;

			agente[i]->incr_cont (dt);
			//quad_cont[i]=agente[agente[i]->id_contactado]->id_contactado;
		//	quad_cont[i]=agente[i]->id_contactado;
			quad_cont[i]=agente[i]->id_contactado;
			for (int j=0;j<MAX_TASKS;j++)
				for (int k=0;k<TAM_TASKS;k++)
					tasks_before[i][j][k]=agente[i]->tasks[j][k];


			agentes_before[i]=agente[i]->calculaAgente ();

		}
		
	}



	for (int i=0; i<num_ag; i++)
	{
		if (volando[i]==true)
		{	
			if (agente[i]->id_contactado>=0 && quad_cont[agente[i]->id_contactado]==i)
			{
			//	ROS_INFO("task in %f %f %f %f %f",tasks_before[agente[i]->id_contactado][0][0],tasks_before[agente[i]->id_contactado][0][1],tasks_before[agente[i]->id_contactado][0][2],tasks_before[agente[i]->id_contactado][0][3],tasks_before[agente[i]->id_contactado][0][4]);		
			//	ROS_INFO("task id: %d",i);
				agente[i]->join_tasks(tasks_before[agente[i]->id_contactado],agente[i]->id_contactado);
			//	ROS_INFO("task %f %f %f %f %f",agente[i]->tasks[0][0],agente[i]->tasks[0][1],agente[i]->tasks[0][2],agente[i]->tasks[0][3],agente[i]->tasks[0][4]);
				agente[i]->task_allocation_one (agentes_before[agente[i]->id_contactado], t);
			//	ROS_INFO("plan %d",agente[i]->plan[0]);
			}
			else if (agente[i]->tarea_nueva==1)
			{	
				agente[i]->autoplan(t);	
				agente[i]->tarea_nueva=0;
			}

			tam_plan=0;
			while(agente[i]->plan[tam_plan]>-1)
				tam_plan++;

			if (tam_plan>0)
			{
				agente[i]->estado=2;
				res.way_point.x=agente[i]->tasks[agente[i]->plan[0]][3]+x_off;
				res.way_point.y=agente[i]->tasks[agente[i]->plan[0]][4]+y_off;
				res.way_point.z=h_des[i];
				/**if (i==0)
					res.way_point.z=2.0;
				else
					res.way_point.z=3.0;
				cambio[i]=1;**/		
			}
			else
			{
				/**if (i==0)
					res.way_point.z=2.0;
				else
					res.way_point.z=3.0;*/
				agente[i]->estado=1;
				res.way_point.x=path[indice[i]][0];
				res.way_point.y=path[indice[i]][1];
				res.way_point.z=h_des[i];

				if ((agente[i]->x-res.way_point.x)*(agente[i]->x-res.way_point.x)+(agente[i]->y-res.way_point.y)*(agente[i]->y-res.way_point.y)<1.0)
				{
					indice[i]++;
					if (indice[i]>3)
						indice[i]=0;
				}
			}

			agente[i]->monitoring_tasks (tasks_in, t);
		//	ROS_INFO("task in %f %f %f %f %f",tasks_in[0][0],tasks_in[0][1],tasks_in[0][2],tasks_in[0][3],tasks_in[0][4]);
		//	ROS_INFO("task %f %f %f %f %f",agente[i]->tasks[0][0],agente[i]->tasks[0][1],agente[i]->tasks[0][2],agente[i]->tasks[0][3],agente[i]->tasks[0][4]);
		//	ROS_INFO("quad %d plan %d",agente[i]->id, agente[i]->plan[0]);

			res.header.frame_id = node_name;
			res.header.stamp = ros::Time::now();
			res.way_point.cruise = 0.5;

			my_waypoint_pub[i].publish(res);
		//	ROS_INFO("Enviando posicion a %d: %f, %f %f", i, res.way_point.x , res.way_point.y , res.way_point.z);
		}

	}
	}

}

void UAV_StateCallBack0(const UALStateStamped::ConstPtr& state) 
{
	last_ual_state[0] = *state;
}

void UAV_StateCallBack1(const UALStateStamped::ConstPtr& state) 
{
	last_ual_state[1] = *state;
}

void Intruder0_StateCallBack(const UALStateStamped::ConstPtr& state) 
{
	intruder_state[0] = *state;
	tasks_in[0][0]=0;
	//ROS_INFO("task %f %f %f %f %f %f %f %f %f %f %f %f %f",tasks_in[0][0],tasks_in[0][1],tasks_in[0][2],tasks_in[0][3],tasks_in[0][4],tasks_in[0][5],tasks_in[0][6],tasks_in[0][7],tasks_in[0][8],tasks_in[0][9],tasks_in[0][10],tasks_in[0][11],tasks_in[0][12],tasks_in[0][13]);
}

void Intruder1_StateCallBack(const UALStateStamped::ConstPtr& state) 
{
	intruder_state[1] = *state;
	tasks_in[1][0]=1;
	//ROS_INFO("task %f %f %f %f %f",tasks_in[1][0],tasks_in[1][1],tasks_in[1][2],tasks_in[1][3],tasks_in[1][4]);
}

void Intruder2_StateCallBack(const UALStateStamped::ConstPtr& state) 
{
	intruder_state[2] = *state;
	tasks_in[2][0]=2;
	//ROS_INFO("task %f %f %f %f %f",tasks_in[2][0],tasks_in[2][1],tasks_in[2][2],tasks_in[2][3],tasks_in[2][4]);
}


int main(int argc, char** argv)
{
	ROS_INFO("  arguments [%d]", argc);
	if (argc < 5)
	{
		cout << "This program should have at least one input parameter.\n"<< endl <<
				"Each input parameter is the number of each UAV." << endl;
		return -1;
	}

	//The UAV ID is stored in a global variable
	num_ag=2;
	num_intruders=3;
	t=0.0;

	char nombre[50];

	for(unsigned i = 0; i < argc; i++){
		cout << "Argument number " << i << "is: " << argv[i] << endl;
	}

	//-------------------------------------------------------------------------------------------------------------
	std::cout << "Initializing output files" << std::endl;
	for (int i=0; i<num_ag; i++)
	{
		// Getting uav name
		uav_full_id[i]="uav_";
		uav_full_id[i].append(string(argv[i+1]));

		// Output Files
		sprintf(nombre,"uav_%d_pos",i);
		pos_quads[i].open(nombre, ofstream::out);
		if (!pos_quads[i])
		{
			ROS_INFO("Error al abrir fichero de salida");
			return -1;
		}
		sprintf(nombre,"uav_%d_tasks",i);
		task_assigned[i].open(nombre, ofstream::out);
		if (!task_assigned[i])
		{
			ROS_INFO("Error al abrir fichero de salida");
			return -1;
		}
		sprintf(nombre,"uav_%d_costs",i);
		costes_totales[i].open(nombre, ofstream::out);
		if (!costes_totales[i])
		{
			ROS_INFO("Error al abrir fichero de salida");
			return -1;
		}		
	}
	//-------------------------------------------------------------------------------------------------------------
	
	std::cout << "Initializing nodes" << std::endl;
	node_name = "prueba_test";
	ros::init(argc,argv,node_name);
	ros::NodeHandle n;

	string topicname;
	ros::Subscriber sub[argc];
	ros::Subscriber intruders[3];


	std::cout << "Getting offsets" << std::endl;
	x_off=atof(argv[num_ag+3]);
	y_off=atof(argv[num_ag+4]);
	range=atof(argv[num_ag+5]);

	std::cout << "Subscribing to uav state node" << std::endl;
	//Nos suscribimos al topico para conocer el estado del UAV
	for (int i=0; i<num_ag; i++)
	{	
		topicname= node_name;
		topicname.append("/out_waypoint_");
		topicname.append(string(argv[i+1]));
		my_waypoint_pub[i] = n.advertise<WayPointWithCruiseStamped> (topicname.c_str(), 0);
		TakeOffGoalSended[i]=false;
		LandGoalSended[i]=false;
		agente[i]= new class_quad(i, 0.0, 0.0, 0.0, 1.0, range, 1.0);
		agente[i]->init_cont(num_ag, 1.0);
		h_des[i]=atof(argv[num_ag+1+i]);
		volando[i]=false;
		cambio[i]=0;
		indice[i]=i+1;
	}
	radio = new class_radio(0, 10.0, num_ag);

	path[0][0]=-3.5;
	path[0][1]=-3.5;
	path[1][0]=3.5;
	path[1][1]=-3.5;
	path[2][0]=3.5;
	path[2][1]=3.5;
	path[3][0]=-3.5;
	path[3][1]=3.5;	


	std::cout << "Main loop" << std::endl;
	for (int i=0; i<MAX_TASKS; i++)
		for (int j=0; j<TAM_TASKS; j++)
			tasks_in[i][j]=-1;


		topicname=uav_full_id[0];
		topicname.append("/ual_state");

		cout << "MAIN: Subscribing to: " << topicname << endl;

		sub[0] = n.subscribe(topicname.c_str(), 0,UAV_StateCallBack0);
		topicname=uav_full_id[1];
		topicname.append("/ual_state");
		sub[1] = n.subscribe(topicname.c_str(), 0,UAV_StateCallBack1);

		/*topicname=string(argv[num_ag+6]);
		//topicname.append("/ual_state");
		intruders[0]=n.subscribe(topicname.c_str(), 0,Intruder0_StateCallBack);
		pos_intruders[0].open("intruder0_pos", ofstream::out);
		if (!pos_intruders[0])
		{
			ROS_INFO("Error al abrir fichero de salida");
			return -1;
		}
		topicname=string(argv[num_ag+7]);
		//topicname.append("/ual_state");
		intruders[1]=n.subscribe(topicname.c_str(), 0,Intruder1_StateCallBack);
		pos_intruders[1].open("intruder1_pos", ofstream::out);
		if (!pos_intruders[1])
		{
			ROS_INFO("Error al abrir fichero de salida");
			return -1;
		}
		topicname=string(argv[num_ag+8]);
		//topicname.append("/ual_state");
		intruders[2]=n.subscribe(topicname.c_str(), 0,Intruder2_StateCallBack);
		pos_intruders[2].open("intruder2_pos", ofstream::out);
		if (!pos_intruders[2])
		{
			ROS_INFO("Error al abrir fichero de salida");
			return -1;
		}*/

		
		topicname = uav_full_id[0];
		topicname.append("/land_action");
		cLand0 = new LandClient(topicname,true);
		topicname = uav_full_id[0];
		topicname.append("/take_off_action");
		cTakeOff0 = new TakeOffClient(topicname,true);
		
		topicname = uav_full_id[1];
 		topicname.append("/land_action");
		cLand1 = new LandClient(topicname,true);
		topicname = uav_full_id[1];
		topicname.append("/take_off_action");
		cTakeOff1 = new TakeOffClient(topicname,true);       
		


	ROS_INFO("Waiting for all servers...");
	cLand0->waitForServer();
	cTakeOff0->waitForServer();
	cLand1->waitForServer();
	cTakeOff1->waitForServer();
	ROS_INFO("All servers OK.");

		cTakeOff0->sendGoal(tOff_goal[0], &tOff_Done_CB0, &tOff_Active_CB0, &tOff_Feedback_CB0);
		
		for (int i=0; i<num_ag; i++)
			TakeOffGoalSended[i] = true;

	ros::Timer timer = n.createTimer(ros::Duration(dt), sendControlReferences);


	ros::AsyncSpinner spinner(0);
	spinner.start();

	while(ros::ok())
	{
		sleep(5);
	}
}
