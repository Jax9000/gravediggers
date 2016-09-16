/*
 * Administration.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef ADMINISTRATION_H_
#define ADMINISTRATION_H_

#include "Actor.h"

#include <src/Utils/BaseCommunicationMPI.h>

class Administration : public Actor, public BaseCommunicationMPI {
public:
	Administration(int id);
    virtual void Run();
	virtual ~Administration();
};

#endif /* ADMINISTRATION_H_ */
