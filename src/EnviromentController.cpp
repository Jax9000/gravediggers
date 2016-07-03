/*
 * EnviromentController.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "EnviromentController.h"

EnviromentController::EnviromentController(int argc, char* argv[]) {
	MPI::Init(argc, argv);
}

void EnviromentController::Start() {
	int size, id;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(id < 0){
		// TODO throw sth
		// may this happen?
	}

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
