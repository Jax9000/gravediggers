/*
 * Gravedigger.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Gravedigger.h"

struct sort_pred {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second < right.second;
    }
};

Gravedigger::Gravedigger(int id) :
		Actor(id) {
	// TODO Auto-generated constructor stub
	mpi_mutex = PTHREAD_MUTEX_INITIALIZER;
	dead_man = -1;
	request_number = 0;
}

void Gravedigger::UpdateLocalList(const MessageModel& msg) {
	//TODO:
	//Add mutex to local_dead_list
	for (int i = 0; i < 20; i++) {
		local_dead_list.push_back(msg.umarlaks[i]);
	}
}

void Gravedigger::deadManRequest(int dead_man) {
	request_number++;
	for (int i = GRAVEDIGGER; i < MpiHelper::GetSize(); i++) {
		if (i != MpiHelper::ProcesID()) {
			MessageModel msg;
			msg.requesting_dead_man = dead_man;
			SafeSend(msg, DEAD_MAN_REQUEST, i);
		}
	}
}

void Gravedigger::entomb() {
	cout << "Entombed [" << dead_man << "] by [" << id << "]\n";
	//sleep(rand() %  + 2);
	usleep(rand()%5000);
	lamport_time++;
	local_dead_list.erase(
			std::remove(local_dead_list.begin(), local_dead_list.end(),
					dead_man), local_dead_list.end());
	//TODO:
	//send to others info about entombing
	dead_man = -1;
}

void Gravedigger::Run() {
	isworking = true;
	srand(time(NULL) + id);

	while (isworking) {
		usleep(20);
		if (local_dead_list.size() > 0) {
			can_remove = false;
			while (!can_remove) {
				dead_man = VectorUtils::GetRandomElement(local_dead_list);
				request_status = WAIT;
				deadManRequest(dead_man);
				can_remove = waitForDeadRespond();
			}

			MessageModel msg;
			msg.requesting_dead_man = dead_man;
			for (int i = GRAVEDIGGER; i < MpiHelper::GetSize(); i++) {
				if (i != MpiHelper::ProcesID())
					SafeSend(msg, DEAD_MAN_ENTOMBED, i);
			}

			entomb();

			officeQueue.push_back(std::make_pair(id, lamport_time));
			std::sort(officeQueue.begin(), officeQueue.end(), sort_pred());
		}
	}
}

Gravedigger::~Gravedigger() {
	// TODO Auto-generated destructor stub
}

bool Gravedigger::waitForDeadRespond() {
	while (request_status == WAIT);
	if (request_status == ACCEPT) {
		return true;
	}
	return false;
}
