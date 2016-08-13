/*
 * EnviromentController.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "EnviromentController.h"
#include <unistd.h>

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

	switch(id){
	case BROADCASTER:
		RunBroadcaster(id);
		break;
	case ADMINISTRATION:
		RunAdministration(id);
		break;
	case OFFICIAL:
		RunOfficial(id);
		break;
	default:
		RunGravedigger(id);
		break;
	}
}

void EnviromentController::RunAdministration(int id) {
	Administration instance(id);
	RunMonitor(&instance);
}

void EnviromentController::RunGravedigger(int id) {
	Gravedigger instance(id);

}

void EnviromentController::RunBroadcaster(int id) {
	Broadcaster instance(id);
	instance.Run();
}

void EnviromentController::RunOfficial(int id) {
	Official instance(id);
}

void EnviromentController::RunMonitor(Actor* actor) {
	Monitor* monitor = MonitorFactory::Build(actor->GetType());
	pthread_t thread;
	pthread_create(&thread, NULL, &EnviromentController::thread_provider, monitor);
}

void* EnviromentController::thread_provider(void* object) {
	return ((Monitor*)object)->Run();
}
