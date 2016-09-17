/*
 * Gravedigger.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef GRAVEDIGGER_H_
#define GRAVEDIGGER_H_

#include "Actor.h"

#include "../Utils/BaseMutexMPI.h"


class Gravedigger : public Actor, public BaseMutexMPI {
public:
	Gravedigger(int id);
	void Run() override;
	virtual ~Gravedigger();
};

#endif /* GRAVEDIGGER_H_ */
