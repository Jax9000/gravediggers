/*
 * Broadcaster.h
 *
 *  Created on: Jul 25, 2016
 *      Author: jjax
 */

#ifndef BROADCASTER_H_
#define BROADCASTER_H_

#include "Actor.h"
#include "../Models/MessageModel.h"
#include "unistd.h"

#include <src/Utils/BaseCommunicationMPI.h>

class Broadcaster : public Actor, BaseCommunicationMPI {
public:
	Broadcaster(int id);
    virtual void Run();
	void Stop();
};

#endif /* BROADCASTER_H_ */
