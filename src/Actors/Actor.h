/*
 * Actor.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include <mpi.h>
#include <pthread.h>

#include "../Utils/ActorUtils.h"
#include "../Monitors/Monitor.h"
#include "../Monitors/MonitorFactory.h"

class Actor {
public:
	Actor();
	virtual ActorType GetType();
	virtual ~Actor();

protected:
	Monitor monitor;
	ActorType actor_type;
	int id;

private:
	static void *thread_provider(void* object);
};

#endif /* ACTOR_H_ */
