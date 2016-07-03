/*
 * Actor.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Actor.h"


Actor::Actor() {
	MPI_Comm_rank(MPI_COMM_WORLD, &(this->id));
	actor_type = ActorUtils::ConvertId2Type(this->id);
	monitor = *(MonitorFactory::Build(actor_type));

    pthread_t thread;
    pthread_create(&thread, NULL, &Actor::thread_provider, &monitor);
}


ActorType Actor::GetType() {
	return actor_type;
}

Actor::~Actor() {
}

void* Actor::thread_provider(void *object) {
	return ((Monitor*)object)->Run();
}
