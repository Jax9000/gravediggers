/*
 * Monitor.h
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include "../Actors/Actor.h"

class Monitor {
public:
	void* Run();
	void SetActor(Actor* actor);

protected:
	Actor* actor;
};

#endif /* MONITOR_H_ */
