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
		while(!actor->DoWantToSend()){
			ListenAndHandleMessages();
		}
	}
	return 0;
}

void Monitor::SetActor(Actor* actor) {
	this->actor = actor;
}

void Monitor::Stop() {
	is_working = false;
}

void Monitor::ListenAndHandleMessages() {
	MessageModel* message = new MessageModel();
	MPI_Status status;
	int* number = new int();

	int buf[32];
//	MPI_Recv(buf, 32, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
//    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	MPI_Recv(message, sizeof(MessageModel), MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	switch(message->message_type){
	case SPAM:
		//cout << "monitor recv: " << actor->GetType() << endl;
		break;
	}
	is_working = false;
}
