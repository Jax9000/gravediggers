/*
 * Monitor.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#include "Monitor.h"

void* Monitor::Run() {
	is_working = true;
	while(is_working){
		ListenAndHandleMassages();
	}
	return 0;
}

void Monitor::Stop() {
    is_working = false;
}

Monitor::Monitor(Actor *actor, pthread_mutex_t mutex)
{
    this->actor = actor;
    this->mpi_mutex = mutex;
}

void Monitor::ListenAndHandleMassages() {
}

Monitor::~Monitor() {
}
