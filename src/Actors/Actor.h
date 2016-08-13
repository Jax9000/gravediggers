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

class Actor {
public:
	Actor();
	Actor(int id);
	virtual ActorType GetType();
	virtual ~Actor();

protected:
	ActorType actor_type;
	int id;
	bool isworking;
	bool wants_to_send;

private:
	static void *thread_provider(void* object);
};

#endif /* ACTOR_H_ */
