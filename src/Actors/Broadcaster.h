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

class Broadcaster : public Actor {
public:
	Broadcaster(int id);
	void Run();
	void Stop();
};

#endif /* BROADCASTER_H_ */
