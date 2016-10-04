/*
 * Monitor.h
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#ifndef RESPONDER_H_
#define RESPONDER_H_

#include "../Actors/Actor.h"

#include "../Utils/BaseMutexMPI.h"

class Responder {
public:
	void* Run();
	void Stop();
    Responder(Actor* actor);
	virtual ~Responder();

protected:
	virtual void ListenAndHandleMassages();

    Actor* actor;
    bool is_working;
};

#endif /* RESPONDER_H_ */
