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

Monitor::Monitor(Actor *actor)
{
    this->actor = actor;
}

void Monitor::ListenAndHandleMassages() {
}

Monitor::~Monitor() {
}
