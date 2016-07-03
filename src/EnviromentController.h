/*
 * EnviromentController.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef ENVIROMENTCONTROLLER_H_
#define ENVIROMENTCONTROLLER_H_

#include <mpi.h>
#include "Actors/Administration.h"
#include "Actors/Gravedigger.h"
#include "Actors/Official.h"
#include "Enums/ActorType.h"

class EnviromentController {
public:
	EnviromentController(int argc, char *argv[]);
	void Start();

private:
	void RunAdministration();
	void RunGravedigger();
	void RunOfficial();
};

#endif /* ENVIROMENTCONTROLLER_H_ */
