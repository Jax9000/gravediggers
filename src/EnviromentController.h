/*
 * EnviromentController.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef ENVIROMENTCONTROLLER_H_
#define ENVIROMENTCONTROLLER_H_

#include "Models/ActorsModel.h"
#include <mpi.h>

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
