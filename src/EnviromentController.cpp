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
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
	if (provided < MPI_THREAD_MULTIPLE)
	{
	    printf("ERROR: The MPI library does not have full thread support\n");
	    MPI_Abort(MPI_COMM_WORLD, 1);
	}


	if(fork()){

	} else {
		int buf;
		MPI_Recv(&buf, 44, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "XD";
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
	RunMonitor(&instance);
}

void EnviromentController::RunBroadcaster(int id) {
	Broadcaster instance(id);
	RunMonitor(&instance);
	instance.Run();
}

void EnviromentController::RunOfficial(int id) {
	Official instance(id);
	RunMonitor(&instance);
}

void EnviromentController::RunMonitor(Actor* actor) {
	Monitor* monitor = MonitorFactory::Build(actor->GetType());
	monitor->SetActor(actor);
	pthread_t thread;
	pthread_create(&thread, NULL, &EnviromentController::thread_provider, monitor);
}

void* EnviromentController::thread_provider(void* object) {
	return ((Monitor*)object)->Run();
}
