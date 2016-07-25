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
#include "Actors/Broadcaster.h"
#include "Enums/ActorType.h"

#define BROADCASTER 0
#define ADMINISTRATION 1
#define OFFICIAL 2
#define GRAVEDIGGER 3

class EnviromentController {
public:
	EnviromentController(int argc, char *argv[]);
	void Start();

private:
	void RunBroadcaster(int id);
	void RunAdministration(int id);
	void RunGravedigger(int id);
	void RunOfficial(int id);
};

#endif /* ENVIROMENTCONTROLLER_H_ */
