/*
 * Gravedigger.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Gravedigger.h"

struct sort_pred {
	bool operator()(const std::pair<int, int> &left,
			const std::pair<int, int> &right) {
		return left.second < right.second;
	}
};

Gravedigger::Gravedigger(int id) :
		Actor(id) {
	// TODO Auto-generated constructor stub
	dead_man = -1;
	request_number = 0;
	local_mutex = PTHREAD_MUTEX_INITIALIZER;
}

void Gravedigger::UpdateLocalList(const MessageModel& msg) {
	pthread_mutex_lock(&this->local_mutex);
	for (int i = 0; i < DEAD_LIST_SIZE; i++) {
		local_dead_list.push_back(msg.umarlaks[i]);
	}
	pthread_mutex_unlock(&this->local_mutex);
}

void Gravedigger::deadManRequest(int dead_man) {
	request_number++;
	for (int i = GRAVEDIGGER; i < MpiHelper::GetSize(); i++) {
		if (i != MpiHelper::ProcesID()) {
			MessageModel msg;
			msg.iValue = dead_man;
			SafeSend(msg, DEAD_MAN_REQUEST, i);
		}
	}
}

void Gravedigger::removeFromLocalDeadList(int dead_id) {
	if (local_dead_list.size() > 0) {
		local_dead_list.erase(
				std::remove(local_dead_list.begin(), local_dead_list.end(),
						dead_id), local_dead_list.end());
	}
}

void Gravedigger::entomb() {
	std::stringstream ss;
	ss << "Entombed [" << dead_man << "] by [" << id << "]\n";
	Log(ss);

	entombed_list.push_back(dead_man);
	usleep(rand() % 5000);
	pthread_mutex_lock(&this->mpi_mutex);
	lamport_time++;
	pthread_mutex_unlock(&this->mpi_mutex);

	pthread_mutex_lock(&this->local_mutex);
	removeFromLocalDeadList(dead_man);
	pthread_mutex_unlock(&this->local_mutex);

	MessageModel msg;
	msg.iValue = dead_man;
	BroadcastOtherGravediggers(msg, DEAD_MAN_ENTOMBED);

	dead_man = -1;
}

bool Gravedigger::isDeadListEmpty() {
	pthread_mutex_lock(&this->local_mutex);
	bool ret = local_dead_list.size() == 0;
	pthread_mutex_unlock(&this->local_mutex);
	return ret;
}

int Gravedigger::getNextDeadMan() {
	pthread_mutex_lock(&this->local_mutex);
	int ret = VectorUtils::GetRandomElement(local_dead_list);
	pthread_mutex_unlock(&this->local_mutex);
	return ret;
}

void Gravedigger::Run() {
	isworking = true;
	srand(time(NULL) + id);

	while (isworking) {
		sleep(2);
		if (!isDeadListEmpty()) {
			bool can_entomb = false;
			while (!can_entomb) {
				dead_man = getNextDeadMan();
				if(dead_man >= 0){
					request_status = WAIT;
					deadManRequest(dead_man);
					can_entomb = waitForDeadRespond();
				}
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
	while (request_status == WAIT)
		;
	if (request_status == ACCEPT) {
		return true;
	}
	return false;
}

void Gravedigger::BroadcastOtherGravediggers(MessageModel& msg,
		MessageType type) {
	for (int i = GRAVEDIGGER; i < MpiHelper::GetSize(); i++) {
		if (i != id) {
			SafeSend(msg, type, i);
		}
	}
}

bool Gravedigger::checkIfEntombed(int dead_id) {
	if (entombed_list.size() > 0) {
		for (unsigned int i = 0; i < entombed_list.size(); i++){
			if (entombed_list[i] == dead_id) {
				return true;
			}
		}
	}
	return false;
}
