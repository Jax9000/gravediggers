/*
 * Monitor.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#include "../Responder/Responder.h"

void* Responder::Run() {
	is_working = true;
	while (is_working) {
		if (actor->getIsworking()) {
			ListenAndHandleMassages();
		}
	}
	return 0;
}

void Responder::Stop() {
	is_working = false;
}

Responder::Responder(Actor *actor) {
	this->actor = actor;
}

void Responder::ListenAndHandleMassages() {
}

Responder::~Responder() {
}
