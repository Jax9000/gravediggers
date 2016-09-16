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
	void Stop();
	void SetActor(Actor* actor);
	void SetMutex(pthread_mutex_t mutex);
	virtual ~Monitor();

protected:
	virtual void ListenAndHandleMassages();

	Actor* actor;
	pthread_mutex_t mpi_mutex;
	bool is_working;
};

#endif /* MONITOR_H_ */
