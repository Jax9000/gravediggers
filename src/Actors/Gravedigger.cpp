/*
 * Gravedigger.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Gravedigger.h"

Gravedigger::Gravedigger(int id) : Actor(id) {
	// TODO Auto-generated constructor stub
    mpi_mutex = PTHREAD_MUTEX_INITIALIZER;
}

void Gravedigger::updateLocalList(const MessageModel& msg) {
	for (int i = 0; i < 20; i++) {
		local_dead_list.push_back(msg.umarlaks[i]);
	}
}

void Gravedigger::deadManRequest(int dead_man) {
	//TODO dead_rquest()
	for (int i = GRAVEDIGGER; i < MpiHelper::GetSize(); i++) {
		if (i != MpiHelper::ProcesID()) {
			MessageModel msg;
			msg.requesting_dead_man = dead_man;
			Send(msg, DEAD_MAN_REQUEST, i);
		}
	}
}

void Gravedigger::Run() {
	isworking = true;
	while(isworking){
		MessageModel msg = Receive(ADMINISTRATION, DEAD_MAN_LIST);
		updateLocalList(msg);
		accept_request = false;
		can_remove = false;
		while(!can_remove){
			int dead_man = VectorUtils::GetRandomElement(local_dead_list);

			deadManRequest(dead_man);



			//TODO receive_daead_respond()

		}
//		std::cout << "Gravedigger ["<<MpiHelper::ProcesID() << "] get [" <<

	}
}

Gravedigger::~Gravedigger() {
    // TODO Auto-generated destructor stub
}

