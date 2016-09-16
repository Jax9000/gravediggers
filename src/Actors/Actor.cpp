/*
 * Actor.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Actor.h"

Actor::Actor() {
	mpi_mutex = PTHREAD_MUTEX_INITIALIZER;
	actor_type = UNDEFINED;
	id = -1;
	wants_to_send = false;
	isworking = false;
}

Actor::Actor(int id) {
	this->id = id;
	this->actor_type = ActorUtils::ConvertProcessIdToType(this->id);
	wants_to_send = false;
	isworking = false;
}

ActorType Actor::GetType() {
	return actor_type;
}

Actor::~Actor() {
}

pthread_mutex_t Actor::GetMutex() {
	return this->mpi_mutex;
}

MessageModel Actor::Receive(int source, int type, MPI_Status *status)
{
    MessageModel msg;
    MPI_Recv(&msg, sizeof(MessageModel), MPI_BYTE, source, type, MPI_COMM_WORLD, status);
    return msg;
}

MessageModel Actor::Receive(int source, int type)
{
    MessageModel msg;
    MPI_Recv(&msg, sizeof(MessageModel), MPI_BYTE, source, type, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    return msg;
}