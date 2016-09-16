/*
 * Monitor.h
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include "../Actors/Actor.h"

#include <src/Utils/BaseMutexMPI.h>

class Monitor : public BaseMutexMPI {
public:
	void* Run();
	void Stop();
    Monitor(Actor* actor, pthread_mutex_t mutex);
	virtual ~Monitor();

protected:
	virtual void ListenAndHandleMassages();

    Actor* actor;
	bool is_working;
};

#endif /* MONITOR_H_ */
