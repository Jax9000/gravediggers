/*
 * Gravedigger.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef GRAVEDIGGER_H_
#define GRAVEDIGGER_H_

#include <iostream>
#include <unistd.h>
#include "Actor.h"

#include "../Utils/BaseMutexMPI.h"
#include "../Utils/VectorUtils.h"
#include "../Utils/MpiHelper.h"


class Gravedigger : public Actor, public BaseMutexMPI {
public:
	Gravedigger(int id);
	void Run() override;
	virtual ~Gravedigger();

private:
	vector<int> local_dead_list;
	bool accept_request;
	bool can_remove;

	void updateLocalList(const MessageModel& msg);
	void deadManRequest(int dead_man);
};

#endif /* GRAVEDIGGER_H_ */
