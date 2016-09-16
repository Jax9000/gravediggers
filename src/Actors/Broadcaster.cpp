/*
 * Broadcaster.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: jjax
 */

#include "Broadcaster.h"
#include <iostream>

Broadcaster::Broadcaster(int id) : Actor() {
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
    message.actor_type = this->actor_type;
	message.process_id = this->id;

    while(isworking) {
        for(int i=0; i<size; i++) {
			if(i != id){
                std::cout << "Send to " << i << ".\n";
                Send(message, SPAM, i);
			}
		}

		usleep(200);
	}
}

void Broadcaster::Stop() {
	this->isworking = false;
}
