/*
 * actions.h
 *
 *  Created on: 26/11/2012
 *      Author: catec
 */

#ifndef ACTIONS_H_
#define ACTIONS_H_
#include <actionlib/client/simple_action_client.h>
#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/LandAction.h>


using namespace std;
using namespace catec_actions_msgs;

typedef actionlib::SimpleActionClient<TakeOffAction> TakeOffClient;
typedef actionlib::SimpleActionClient<LandAction> LandClient;

LandClient *cLand;
TakeOffClient *cTakeOff;

void tOff_Active_CB();
void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback);
void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result);

void land_Active_CB();
void land_Feedback_CB(const LandFeedbackConstPtr& feedback);
void land_Done_CB(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result);

#endif /* ACTIONS_H_ */
