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
#include <iostream>

#include "../Utils/ActorUtils.h"

class Actor {
public:
	Actor();
	Actor(int id);
	virtual ActorType GetType();
	virtual ~Actor();
	pthread_mutex_t GetMutex();

protected:
	ActorType actor_type;
	int id;
	bool isworking;
	bool wants_to_send;
	pthread_mutex_t mpi_mutex;

private:
	static void *thread_provider(void* object);
};

#endif /* ACTOR_H_ */
