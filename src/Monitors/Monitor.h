/*
 * Monitor.h
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include "../Actors/Actor.h"
#include "../Models/MessageModel.h"
#include <iostream>

using namespace std;

class Monitor {
public:
	void* Run();
	void SetActor(Actor* actor);
	void Stop();

protected:
	Actor* actor;
	bool is_working;
	void ListenAndHandleMessages();
};

#endif /* MONITOR_H_ */
