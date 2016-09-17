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
#include "Actors/Broadcaster.h"
#include "Enums/ActorType.h"
#include "Monitors/Monitor.h"

#define BROADCASTER 0
#define ADMINISTRATION 1
#define GRAVEDIGGER 2

class EnviromentController {
public:
	EnviromentController(int argc, char *argv[]);
	void Start();

private:
    Actor* RunBroadcaster(int id);
    Actor* RunAdministration(int id);
    Actor* RunGravedigger(int id);
	static void* thread_provider(void *object);
};

#endif /* ENVIROMENTCONTROLLER_H_ */
