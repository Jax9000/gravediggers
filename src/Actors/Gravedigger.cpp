/*
 * Gravedigger.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Gravedigger.h"

Gravedigger::Gravedigger(int id) : Actor(id) {
	// TODO Auto-generated constructor stub
    mpi_mutex = PTHREAD_MUTEX_INITIALIZER;
}

void Gravedigger::Run() {

}

Gravedigger::~Gravedigger() {
    // TODO Auto-generated destructor stub
}

