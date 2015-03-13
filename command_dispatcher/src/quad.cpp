/*
 * quad.cpp
 *
 *  Created on: January 20, 2015
 *      Authors: Jose Joaquin Acevedo
 */
 
 
#include "quad.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include <ros/ros.h>


  QuadPatrolling::QuadPatrolling(int id_in, double x_in, double y_in, double z_in, double vel_max_in, double range_in, double tpo_in, double path_in[4][2], int tam_path_in, int dir_in)
  {
	id=id_in;
	x=x_in;
	y=y_in;
	z=z_in;
	vel_max=vel_max_in;
	range=range_in;
	tpo_min_cont=tpo_in;
	
	for (int i=0; i<N_CAP; i++)
	capacidades[i]=0;
	
	estado=1;
	
	for (int i=0; i<MAX_TASKS;i++)
	    for(int j=0; j<TAM_TASKS; j++)
	            tasks[i][j]=-1.0;
	

    id_contactado=-1;
       
	for (int i=0; i<MAX_TASKS; i++)
        plan[i]=-1;    
        
    for (int i=0; i<MAX_AGENTES; i++)
		contactados[i]=tpo_min_cont;  

        
    tarea_nueva=1;
    coste_mision=0.0;  

    vel=vel_max_in;
    long_izq=0.0;
    long_dcha=0.0;
    long_total=0.0;
    speed_izq=0.0;
    speed_dcha=0.0;
    speed_total=0.0;
    flag=0;
   
    int dist_aux=10000;
    ind=-1;
    tam_path=tam_path_in;
    for (int i=0; i<tam_path; i++)
    {
	path[i][0]=path_in[i][0];
	path[i][1]=path_in[i][1];
        if (i==0)
		path_dist[i]=0.0;
	else
		path_dist[i]=norma(path[i][0]-path[i-1][0],path[i][1]-path[i-1][1]);
	
	if (norma(path[i][0]-x,path[i][1]-y)<dist_aux)
	{
		ind=i;
		dist_aux=norma(path[i][0]-x,path[i][1]-y);
	}

    }
    init_ind=ind;
    ind_sup=ind;
    ind_inf=ind;
    ind_aux=ind;
    dir=dir_in;
    dir_aux=dir;
    dist_inf=0.0;
    dist_sup=0.0;
    
    	     
  }

  QuadPatrolling::~QuadPatrolling()
  {
;
  }

  void QuadPatrolling::pathpartition_cv (struct Mensaje mensaje_rcv)
  {
	vel=vel_max;

		if (mensaje_rcv.id>0 && vel>mensaje_rcv.vel_max)
			vel=mensaje_rcv.vel_max;

		if (ind==0 || ind==tam_path-1)
		{
			if (dir==-1)
			{
				ind_inf=0;
				init_ind=0;
				long_izq=0;
				speed_izq=0;
			}
			else
			{
				ind_sup=tam_path-1;
				long_dcha=0;
				speed_dcha=0;
			}
			dir=-dir;
			ind=ind+dir;
			if (ind<0)
				ind=0;

			speed_total=speed_dcha+speed_izq+vel_max;
			long_total=long_izq+long_dcha;
			dist_inf=speed_izq*(long_total/speed_total)+path_dist[init_ind];
			dist_sup=dist_inf+vel_max*(long_total/speed_total);
			ind_aux=-1;
			dist_aux=100000;
			for (int i=0; i<=tam_path-1;i++)
				if (dist_aux>abs(path_dist[i]-dist_inf))
				{
					dist_aux=abs(path_dist[i]-dist_inf);
					ind_aux=i;
				}
			ind_inf=ind_aux;
			ind_aux=-1;
			dist_aux=100000;
			for (int i=0; i<=tam_path-1;i++)
				if (dist_aux>abs(path_dist[i]-dist_inf))
				{
					dist_aux=abs(path_dist[i]-dist_inf);
					ind_aux=i;
				}
			ind_sup=ind_aux;
		}
		else if (mensaje_rcv.id>0 && abs(ind-mensaje_rcv.id)<5)
		{
			if (mensaje_rcv.init_ind<init_ind)
				init_ind=mensaje_rcv.init_ind;
			if (mensaje_rcv.vel_max<vel)
				vel=mensaje_rcv.vel_max;
			
			if (flag==0)
			{
				if (ind<mensaje_rcv.ind)
				{
					speed_dcha=mensaje_rcv.speed_dcha+mensaje_rcv.vel_max;
					long_dcha=mensaje_rcv.long_dcha;
				}
				else
				{
					speed_izq=mensaje_rcv.speed_izq+mensaje_rcv.vel_max;
					long_izq=mensaje_rcv.long_izq;
				}
				speed_total=speed_dcha+speed_izq+vel_max;
				long_total=long_izq+long_dcha;
				dist_inf=speed_izq*(long_total/speed_total)+path_dist[init_ind];
				dist_sup=dist_inf+vel_max*(long_total/speed_total);
				ind_aux=-1;
				dist_aux=100000;
				for (int i=0; i<=tam_path-1;i++)
					if (dist_aux>abs(path_dist[i]-dist_inf))
					{
						dist_aux=abs(path_dist[i]-dist_inf);
						ind_aux=i;
					}
				ind_inf=ind_aux;
				ind_aux=-1;
				dist_aux=100000;
				for (int i=0; i<=tam_path-1;i++)
					if (dist_aux>abs(path_dist[i]-dist_inf))
					{
						dist_aux=abs(path_dist[i]-dist_inf);
						ind_aux=i;
					}
				ind_sup=ind_aux;	
				
				if ((ind>=ind_sup && dir==1 && flag==0)||(ind<=ind_inf && dir==-1 && flag==0))
				{
					dir=-dir;
					flag=1;
					ind=ind+dir;
				}	
				else
				{
					dir_aux=dir;
					flag=2;
				}		
			}
			if ((ind>=ind_sup && dir==1)||(ind<=ind_inf && dir==-1))
			{
				dir=-dir;
				flag=1;
			}
		}
		else
		{
			if (dir==0)
				dir=dir_aux;
			if (flag==1 && (dir==1 && ind>ind_inf+1 || dir==-1 && ind<ind_sup-1))
				flag=0;
			if ((ind>ind_sup && dir==1 && flag==2)||(ind<=ind_inf && dir==-1 && flag==2))
			{
				dir=-dir_aux;
				flag=1;
			}
		}


  }

  void QuadPatrolling::task_allocation_one (struct Agente agente_cont, double now)
  {
         Agente agente_1= calculaAgente();
		 int tam;
		 int plan_basic[MAX_TASKS];
		 int count=0;
		 int plan_total[MAX_COMB][MAX_TASKS];
		 int i=0;
		 int j=0;
		int k=0;

		 for (i=0; i<MAX_TASKS; i++){
			 if (tasks[i][8]<=3 && tasks[i][0]>-1){
				 plan_basic[count]=i;
				 count=count+1;
			 }
		 }
		 for (i=count; i<MAX_TASKS;i++)
		     plan_basic[i]=-1;

			     
		 tam=combinaciones(count, plan_basic, plan_total);

       /*  for (i=0; i<tam;i++)
	{
		for (j=0; j<=count; j++)
			cout << plan_total[i][j];
		cout << endl;
	}*/	

	//ROS_INFO("count %d  tam %d", count, tam);

         int plan_a[MAX_TASKS];
         int plan_b[MAX_TASKS];

         Costes coste;
         coste.cost=100000000;
         coste.arrive_time=-1;
         Costes coste_aux=coste;
         Costes coste1;
         Costes coste2;
         int plan_a_elegido[MAX_TASKS]; 
         int plan_b_elegido[MAX_TASKS]; 
         int k1=0;
         int k2=0;
         int distancia;

	if (tam<=0)
		for (i=0; i<MAX_TASKS;i++)
		{
			plan_a_elegido[i]=-1;
			plan_b_elegido[i]=-1;
			plan_a[i]=-1;
			plan_b[i]=-1;
		}


         for (i=0; i<tam;i++)
         {
		for (j=0; j<=count; j++)
                {
		
			for (k1=0; k1<j; k1++)
                      	  plan_a[k1]=plan_total[i][k1]; 
					
			for (k2=j; k2<MAX_TASKS; k2++)
			{
                       	 plan_a[k2]=-1;
                       	 if (k2<count)
                       		 plan_b[k2-j]=plan_total [i][k2];
                   	}
                    	for (k2=count-j;k2<MAX_TASKS;k2++)
                       	 plan_b[k2]=-1;
		
                
                coste1=calcula_coste(plan_a,tasks,agente_1);
                coste2=calcula_coste(plan_b,tasks,agente_cont);
                    
                coste_aux.cost=coste1.cost+coste2.cost;
                //	ROS_INFO("plan a %d", plan_a[0]);
		if (coste_aux.cost<coste.cost)
                {
                        coste.cost=coste_aux.cost;
                        for (k=0;k<MAX_TASKS;k++)
                        {
                            plan_a_elegido[k]=plan_a[k];
                            plan_b_elegido[k]=plan_b[k];
                        }
                        coste.arrive_time=coste2.arrive_time;
			coste_mision=coste1.cost;
			
		}   
		}

          }  

          for (i=0;i<MAX_TASKS;i++)
          {
              if (plan_a_elegido[i]>-1)
              {
                 tasks[plan_a_elegido[i]][6]=now;
                 tasks[plan_a_elegido[i]][8]=2;
                 tasks[plan_a_elegido[i]][9]=agente_1.id;

              }
              if (plan_b_elegido[i]>-1)
              {
                 tasks[plan_b_elegido[i]][6]=now;
                 distancia=norma(coste.arrive_time*tasks[plan_b_elegido[i]][1]+tasks[plan_b_elegido[i]][3]-tasks[plan_b_elegido[0]][3],coste.arrive_time*tasks[plan_b_elegido[i]][2]+tasks[plan_b_elegido[i]][4]-tasks[plan_b_elegido[0]][4]);
                 if (i==0 || distancia<range)
                    tasks[plan_b_elegido[i]][8]=4;
                 else
                    tasks[plan_b_elegido[i]][8]=3;   
                 
                 tasks[plan_b_elegido[i]][9]=agente_cont.id;   
              } 

          }     

			
          for (j=0;j<MAX_TASKS;j++)
              plan[j]=plan_a_elegido[j]; 

          id_contactado=-1;
  }
  
  
void QuadPatrolling::monitoring_tasks (double tasks_in [MAX_TASKS][TAM_TASKS], double now)
{
	double pos[2];
	double pos_task[2];
	double new_task[TAM_TASKS];
	//int count=0;
	int i=0;
	int j=0;
	int k=0;
	int dentro=1;
	pos[0]=x;
	pos[1]=y;
			

	for (i=0; i<MAX_TASKS; i++)
            {
                if (tasks_in[i][0]>-1)
                {
                                 pos_task[0]=tasks_in[i][3];
                                 pos_task[1]=tasks_in[i][4];
                                 if (norma(pos_task[0]-pos[0],pos_task[1]-pos[1])<=range)
                                 {
                                    for(j=0;j<TAM_TASKS; j++)
                                        new_task[j]=tasks_in[i][j];
                                        
                                    dentro=1;
                                    for (k=0; k<MAX_TASKS; k++)
                                        if (new_task[0]==tasks[k][0])
                                        {
                                           dentro=0;
                                           tasks[k][1]=new_task[1];
                                           tasks[k][2]=new_task[2];
                                           tasks[k][3]=new_task[3];
                                           tasks[k][4]=new_task[4];
                                           tasks[k][5]=now;
                                        }         
                                    if (dentro==1)
                                    {
                                       new_task[5]=now;
                                       new_task[8]=1;
                                       tarea_nueva=1;
                                       k=0;
                                       while (tasks[k][0]>-1)
                                             k++;
                                       for (j=0;j<TAM_TASKS;j++)
                                           tasks[k][j]=new_task[j];          
                                    }                                            
                                 }
                }
            }

}

			
   void QuadPatrolling::join_tasks (double tasks_cont [MAX_TASKS][TAM_TASKS], int id_cont)
   {		

		double task_1[MAX_TASKS][TAM_TASKS];
            	double task_2[MAX_TASKS][TAM_TASKS];

		for (int i=0;i<MAX_TASKS;i++)
		{
			for (int j=0; j<TAM_TASKS; j++)
			{             
			task_1[i][j]=tasks[i][j];
			task_2[i][j]=tasks_cont[i][j];
			}
		}
            int id1=id;
            int id2=id_cont;
            int nocoincide=0;
            int i=0;
            int j=0;
	    int k=0;
            int count=0;
            
            for (i=0;i<MAX_TASKS;i++)
                for (j=0;j<TAM_TASKS;j++)
                {
                    task_1[i][j]=tasks[i][j];
                    task_2[i][j]=tasks_cont[i][j];
                }

	for (i=0; i<MAX_TASKS; i++)
	   if (task_2[i][0]>-1)
            {
		for (j=0; j<MAX_TASKS; j++)
                {
		    if (task_1[j][0]==task_2[i][0] && task_1[j][0]>-1)
                    {
			if (task_2[i][5]>task_1[j][5] || (task_2[i][5]==task_1[j][5] && id1<id2))
                        {
						   tasks[j][1]=task_2[i][1];
						   tasks[j][2]=task_2[i][2];
						   tasks[j][3]=task_2[i][3];
						   tasks[j][4]=task_2[i][4];
						   tasks[j][5]=task_2[i][5];
					   }
                       if (task_2[i][6]>task_1[j][6] || (task_2[i][6]==task_1[j][6] && id1<id2))
                       {
						   tasks[j][6]=task_2[i][6];
						   tasks[j][7]=task_2[i][7];
						   tasks[j][8]=task_2[i][8];
						   tasks[j][9]=task_2[i][9]; 
                       }   
                       tasks[j][8]=min(task_1[j][8],task_2[i][8]);
                      }
		      else
                        nocoincide=nocoincide+1;     
          
		} 
		if (nocoincide>=MAX_TASKS)
                {
                    count=0;
                    while (tasks[count][0]>-1)
                          count++;
                          
		    for (k=0; k<TAM_TASKS;k++)
                        tasks[count][k]=task_2[i][k];
		} 
                nocoincide=0;
	   }
	 }


void QuadPatrolling::incr_cont (double dT)
{
     for (int i=0;i<MAX_AGENTES;i++)
		 contactados[i]=contactados[i]+dT;
}

  		
int QuadPatrolling::decide_cont (int msg_rcv[MAX_AGENTES][MSG_LENGTH], int tam)
{
		 double tpo_max=tpo_min_cont;
		 int id_cont=-1;
		 for (int i=0; i<tam; i++)
        	 {
				 if (msg_rcv [i][1]==id && id_contactado>-1 && msg_rcv[i][0]==id_contactado)
                		 {
					 id_cont=msg_rcv[i][0];
					 tpo_max=100000000;
				 }
				 else if (contactados[msg_rcv [i][0]]>=tpo_max)
                 		 {
					 id_cont=msg_rcv[i][0];
					 tpo_max=contactados[msg_rcv[i][0]];
				 }
		 }
		if (id_cont>-1)
			 contactados [id_cont]=0;

		return id_cont;
}

  
struct Agente QuadPatrolling::calculaAgente()
{
	struct Agente a;
	for (int i=0; i<N_CAP;i++){
	a.capacidades[i]=capacidades[i];
	}
	a.x=x;
	a.y=y;
	a.vel_max=vel_max;
	a.range=range;
	a.estado=estado;
	a.id=id;
	a.plan=plan[0];   //añadido necesario probar
	a.dir=dir;
	a.long_izq=long_izq;
	a.long_dcha=long_dcha;
	a.speed_izq=speed_izq;
	a.speed_dcha=speed_dcha;
	a.init_ind=init_ind;
	a.ind=ind;
	a.estado=estado;
	return a;
}

  		
void QuadPatrolling::autoplan (double now)
{
            struct Agente agente1=calculaAgente();
            int plan_basic[MAX_TASKS];
            int plan_total[MAX_COMB][MAX_TASKS];
	    int count=0;
	    int i=0;
	    int j=0;

	    for (i=0; i<MAX_TASKS; i++)
            {
		if (tasks[i][8]<=3 && tasks[i][0]>-1) 
                {  
                    plan_basic[count]=i;
		    count=count+1;
		}
	    }
	    for (i=count;i<MAX_TASKS;i++)
			    plan_basic[i]=-1;

            int num_combinaciones=combinaciones(count,plan_basic,plan_total);
   
            int plan_a[MAX_TASKS];
            int coste=100000000;
            int plan_a_elegido[MAX_TASKS];
            struct Costes c;

	   if (num_combinaciones<=0)
		for (i=0;i<MAX_TASKS;i++)
			plan_a_elegido[i]=-1;

	    for (i=0; i<num_combinaciones; i++)
            {
		for (j=0; j<MAX_TASKS;j++)
                    plan_a[j]=plan_total[i][j];
		c=calcula_coste(plan_a,tasks,agente1);
		if (c.cost<coste)
                {
                        coste=c.cost;
			coste_mision=coste;
                        for (j=0; j<MAX_TASKS;j++)
                            plan_a_elegido[j]=plan_a[j];
		}      
	   }


	   for (i=0; i<MAX_TASKS; i++)
	  {
		if (plan_a_elegido[i]>-1)
                {
                    tasks[plan_a_elegido[i]][6]=now;
                    tasks[plan_a_elegido[i]][8]=2;
                    tasks[plan_a_elegido[i]][9]=agente1.id;     
                }
                plan[i]=plan_a_elegido[i];
            }
}

double QuadPatrolling::norma(double x, double y)
{
	return sqrt(x*x+y*y);
}


int QuadPatrolling::combinaciones(int n, int C[MAX_TASKS], int C_out[MAX_COMB][MAX_TASKS])
{
    int i;
    int inc = 0;
    int it = n * (n - 1);

   if (n==1)
   {
	inc=1;
	C_out[0][0]=C[0];
	for (int j=1;j<MAX_TASKS;j++)
		C_out[0][j]=-1;
   }
   else
    while (inc < it) {
        for (i = n - 1; i > 0; i--) {
            int aux = C[i-1];
            C[i-1] = C[i];
            C[i] = aux;
            for (int j = 0; j < MAX_TASKS; j++)
		{
		if (j<n)
              	  C_out[inc][j]=C[j];
		else
		  C_out[inc][j]=-1;
		}
            inc++;
        }
    }
    return inc;      
}
  
struct Costes QuadPatrolling::calcula_coste (int plan [MAX_TASKS], double tasks_cont [MAX_TASKS][TAM_TASKS], struct Agente a)
{
 int i=0;
 int j=0;
 struct Costes c;
 
 if (plan[0]==-1)
 {
	 c.cost=0;
     c.arrive_time=-1;
 }
 else 
 {
	 double mytasks[MAX_TASKS][TAM_TASKS];
	 int count=0; 

	 for (i=0; i<MAX_TASKS;i++)
		 if (plan[i]>-1)
         {
			
			 for (j=0;j<TAM_TASKS;j++)
				 mytasks[count][j]=tasks[plan[i]][j];
			 count=count+1;
		 }


     int pos_dest[2]={tasks[plan[0]][3],tasks[plan[0]][4]};

     c.arrive_time = norma(pos_dest[0]-a.x,pos_dest[1]-a.y)/a.vel_max;



     for (i=0; i<count; i++)
         {
			mytasks [i][3]=mytasks[i][3]+c.arrive_time*mytasks[i][1];
			mytasks [i][4]=mytasks[i][4]+c.arrive_time*mytasks[i][2];
         }
         
     c.cost=CTE_TPO*c.arrive_time;
     if (count>0) 
	{
		c.cost=c.cost+CTE_SEGUIR;
		if (a.plan>-1 && a.plan!=plan[0])  // añadido, necesario probar
			c.cost=c.cost+CTE_CAMBIO;
	}

     double distancia;
     for (i=0; i<count; i++)
     {
	     distancia = norma(mytasks[i][3]-pos_dest[0],mytasks[i][4]-pos_dest[1]);
	
	     if (distancia>a.range)
		    c.cost=c.cost+CTE_PERDIDO*i;
	      else 
            c.cost=c.cost+CTE_BENEFICIO*distancia*distancia+CTE_VEL*(norma(mytasks[i][1]-mytasks[0][1],mytasks[i][2]-mytasks[0][2]))*(norma(mytasks[i][1]-mytasks[0][1],mytasks[i][2]-mytasks[0][2]));   // cambiado tasks por mytasks, creo que estaba mal
     }
 }
 return c;
}

void QuadPatrolling::init_cont(int num, double tpo)
{
	tpo_min_cont=tpo;

	for (int i=0; i<num; i++)
		contactados[i]=tpo;

}

void QuadPatrolling::camino()
{
	if (norma(x-path[ind][0],y-path[ind][1])<1.0)
		ind=ind+dir;
}
