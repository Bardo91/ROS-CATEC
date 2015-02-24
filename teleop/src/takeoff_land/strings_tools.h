/*
 * strings_tools.h
 *
 *  Created on: Nov 2, 2012
 *      Author: catec-ros
 */

#ifndef STRINGS_TOOLS_H_
#define STRINGS_TOOLS_H_

#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/LandAction.h>

using namespace catec_actions_msgs;
using namespace std;

string landMessage(const LandResultConstPtr& result);
string takeOffMessage(const TakeOffResultConstPtr& result);


#endif /* STRINGS_TOOLS_H_ */
