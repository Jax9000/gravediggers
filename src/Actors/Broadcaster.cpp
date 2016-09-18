/*
 * Broadcaster.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: jjax
 */

#include "Broadcaster.h"
#include <iostream>

Broadcaster::Broadcaster(int id) :
		Actor() {
	this->id = id;
	this->actor_type = ActorUtils::ConvertProcessIdToType(this->id);
	this->isworking = false;
	this->wants_to_send = false;
}

void Broadcaster::Run() {
	this->isworking = true;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MessageModel message;

	while (isworking) {
		for (int i = GRAVEDIGGER; i < size; i++) {
			Send(message, SPAM, i);
		}

		usleep(BROADCAST_DELAY);
	}
}

void Broadcaster::Stop() {
	this->isworking = false;
}
