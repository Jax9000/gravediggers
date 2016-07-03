/*
 * EnviromentController.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "EnviromentController.h"

EnviromentController::EnviromentController(int argc, char* argv[]) {
	int provided;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
	if (provided < MPI_THREAD_MULTIPLE)
	{
	    printf("ERROR: The MPI library does not have full thread support\n");
	    MPI_Abort(MPI_COMM_WORLD, 1);
	}
}

void EnviromentController::Start() {
	int id;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	switch(id){
	case 0:
		RunAdministration();
		break;
	case 1:
		RunOfficial();
		break;
	default:
		RunGravedigger();
		break;
	}
}

void EnviromentController::RunAdministration() {
	Administration instance;
}

void EnviromentController::RunGravedigger() {
	Gravedigger instance;
}

void EnviromentController::RunOfficial() {
}
