/*
 * Actor.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Actor.h"


Actor::Actor() {
	MPI_Comm_rank(MPI_COMM_WORLD, &(this->id));
	actor_type = ActorUtils::ConvertId2Type(this->id);
	monitor = MonitorFactory::Build(actor_type);
}


ActorType Actor::GetType() {
	return actor_type;
}

Actor::~Actor() {
}
