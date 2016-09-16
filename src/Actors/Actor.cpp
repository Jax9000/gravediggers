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
	mpi_mutex = PTHREAD_MUTEX_INITIALIZER;
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
    pthread_mutex_lock(&this->mpi_mutex);
    MPI_Recv(&msg, sizeof(MessageModel), MPI_BYTE, source, type, MPI_COMM_WORLD, status);
    pthread_mutex_unlock(&this->mpi_mutex);
    return msg;
}

MessageModel Actor::Receive(int source, int type)
{
    MessageModel msg;
    pthread_mutex_lock(&this->mpi_mutex);
    MPI_Recv(&msg, sizeof(MessageModel), MPI_BYTE, source, type, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    pthread_mutex_unlock(&this->mpi_mutex);
    return msg;
}
