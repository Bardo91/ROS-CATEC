/*
 * actions.cpp
 *
 *  Created on: 26/11/2012
 *      Author: catec
 */
#include "actions.h"
#include "strings_tools.h"

void land_Active_CB()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Land Active.");
}

void land_Feedback_CB(const LandFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que se cambie de etapa en el aterrizaje.
	ROS_INFO("Land phase: %d", feedback->phase);
}

void land_Done_CB(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result)
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

void tOff_Active_CB()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Take Off Active.");
}

void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que se cambie de etapa en el despegue.
	ROS_INFO("Take Off phase: %d", feedback->phase);
}

void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Take off finished in state [%s]", state.toString().c_str());
	ROS_INFO("Take off task return: [%s]", takeOffMessage(result).c_str());


	//Si estamos volando enviamos la tarea.
	if(state.state_==state.SUCCEEDED || result->result==TakeOffResult::ALREADY_FLYING)
	{

	}


	//ROS_INFO("Answer: %i", result->sequence.back());
}
