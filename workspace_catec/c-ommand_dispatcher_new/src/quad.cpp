
/*
 * quad.cpp
 *
 *  Created on: May 22, 2013
 *      Authors: Adrian Peralta y Jose Joaquin Acevedo
 */
 
#include "quad.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include <ros/ros.h>


  class_quad::class_quad(int id_in, double x_in, double y_in, double z_in, double vel_max_in, double range_in, double tpo_in)
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
  }

  class_quad::~class_quad()
  {
;
  }

  void class_quad::task_allocation_one (struct agente agente_cont, double now)
  {
         agente agente_1= calculaAgente();
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

         costes coste;
         coste.cost=100000000;
         coste.arrive_time=-1;
         costes coste_aux=coste;
         costes coste1;
         costes coste2;
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
  
  
void class_quad::monitoring_tasks (double tasks_in [MAX_TASKS][TAM_TASKS], double now)
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

			
   void class_quad::join_tasks (double tasks_cont [MAX_TASKS][TAM_TASKS], int id_cont)
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


void class_quad::incr_cont (double dT)
{
     for (int i=0;i<MAX_AGENTES;i++)
		 contactados[i]=contactados[i]+dT;
}

  		
int class_quad::decide_cont (int msg_rcv[MAX_AGENTES][MSG_LENGTH], int tam) 
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

  
struct agente class_quad::calculaAgente()
{
	struct agente a;
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
	return a;
}

  		
void class_quad::autoplan (double now)
{
            struct agente agente1=calculaAgente();
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
            struct costes c;

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

double class_quad::norma(double x, double y)
{
	return sqrt(x*x+y*y);
}


int class_quad::combinaciones(int n, int C[MAX_TASKS], int C_out[MAX_COMB][MAX_TASKS])
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
  
struct costes class_quad::calcula_coste (int plan [MAX_TASKS], double tasks_cont [MAX_TASKS][TAM_TASKS], struct agente a) 
{
 int i=0;
 int j=0;
 struct costes c;
 
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

void class_quad::init_cont(int num, double tpo)
{
	tpo_min_cont=tpo;

	for (int i=0; i<num; i++)
		contactados[i]=tpo;

}
