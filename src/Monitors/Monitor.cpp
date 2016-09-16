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

void Monitor::SetActor(Actor* actor) {
	this->actor = actor;
}

void Monitor::SetMutex(pthread_mutex_t mutex) {
	this->mpi_mutex = mutex;
}

void Monitor::Stop() {
	is_working = false;
}

void Monitor::ListenAndHandleMassages() {
}

Monitor::~Monitor() {
}
