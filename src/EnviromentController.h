/*
 * EnviromentController.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef ENVIROMENTCONTROLLER_H_
#define ENVIROMENTCONTROLLER_H_

#include <mpi.h>
#include <typeinfo>
#include "Actors/Administration.h"
#include "Actors/Gravedigger.h"
#include "Actors/Broadcaster.h"
#include "Enums/ActorType.h"
#include "Actors/Logger.h"
#include "Responder/GravediggerResponder.h"
#include "Responder/Responder.h"


class EnviromentController {
public:
	EnviromentController(int argc, char *argv[]);
	void Start();

private:
    Broadcaster* RunBroadcaster(int id);
    Administration* RunAdministration(int id);
    Gravedigger* RunGravedigger(int id);
	static void* thread_provider(void *object);
};

#endif /* ENVIROMENTCONTROLLER_H_ */
