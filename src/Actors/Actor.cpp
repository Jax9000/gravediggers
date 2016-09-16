/*
 * Actor.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Actor.h"

Actor::Actor() {
	actor_type = UNDEFINED;
	id = -1;
	wants_to_send = false;
	isworking = false;
}

Actor::Actor(int id) {
	this->id = id;
	this->actor_type = ActorUtils::ConvertId2Type(this->id);
	wants_to_send = false;
	isworking = false;
}

ActorType Actor::GetType() {
	return actor_type;
}

Actor::~Actor() {
}

bool Actor::DoWantToSend() {
	//TODO implement this
	return false;
}
