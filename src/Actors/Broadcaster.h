/*
 * Broadcaster.h
 *
 *  Created on: Jul 25, 2016
 *      Author: jjax
 */

#ifndef BROADCASTER_H_
#define BROADCASTER_H_

#include "Actor.h"

class Broadcaster : public Actor {
public:
	Broadcaster(int id);
	void Run();
	void Stop();

private:
	bool isworking;
	bool wants_to_send;
};

#endif /* BROADCASTER_H_ */
