/*
 * Administration.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef ADMINISTRATION_H_
#define ADMINISTRATION_H_

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Actor.h"
#include <src/Utils/BaseCommunicationMPI.h>

#define MAX_SLEEP_TIME 10

class Administration : public Actor, public BaseCommunicationMPI {
public:
	Administration(int id);
    virtual void Run();
	virtual ~Administration();

protected:
    void fillWithUmarlaks(int* array, int size);
    int current_umarlak;
};

#endif /* ADMINISTRATION_H_ */
