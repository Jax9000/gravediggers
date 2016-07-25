/*
 * Broadcaster.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: jjax
 */

#include "Broadcaster.h"

Broadcaster::Broadcaster(int id) : Actor() {
	this->id = id;
	this->actor_type = ActorUtils::ConvertId2Type(this->id);
	this->isworking = false;
}

void Broadcaster::Run() {
	this->isworking = true;
	while(isworking){

	}
}

void Broadcaster::Stop() {
	this->isworking = false;
}
