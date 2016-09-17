/*
 * EnviromentController.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "EnviromentController.h"
#include <unistd.h>
#include <iostream>

EnviromentController::EnviromentController(int argc, char* argv[]) {
	int provided;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provided);
	if (provided < MPI_THREAD_SERIALIZED)
	{
	    printf("ERROR: The MPI library does not have full thread support\n");
	    MPI_Abort(MPI_COMM_WORLD, 1);
	}
}

void EnviromentController::Start() {
	int id;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
    Actor* actor;
	switch(id){
	case BROADCASTER:
        actor = RunBroadcaster(id);
		break;
	case ADMINISTRATION:
        actor = RunAdministration(id);
		break;
	default:
        actor = RunGravedigger(id);
		break;
	}
    actor->Run();
}

Administration* EnviromentController::RunAdministration(int id) {
    Administration* instance = new Administration(id);
    return instance;
}

Gravedigger* EnviromentController::RunGravedigger(int id) {
	Gravedigger* instance = new Gravedigger(id);
    GravediggerMonitor * monitor = new GravediggerMonitor(instance, instance->GetMutex());
    pthread_t thread;
    pthread_create(&thread, NULL, &EnviromentController::thread_provider, monitor);
    return instance;
}

Broadcaster* EnviromentController::RunBroadcaster(int id) {
    Broadcaster* instance = new Broadcaster(id);
    return instance;
}

void* EnviromentController::thread_provider(void* object) {
	return ((Monitor*)object)->Run();
}
