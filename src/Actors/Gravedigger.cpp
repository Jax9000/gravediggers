/*
 * Gravedigger.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Gravedigger.h"
#include <unistd.h>

struct sort_pred {
	bool operator()(const std::pair<int, int> &left,
			const std::pair<int, int> &right) {
		if(left.second == right.second){
			return left.first < right.first;
		}
		return left.second < right.second;
	}
};

Gravedigger::Gravedigger(int id) :
		Actor(id) {
	// TODO Auto-generated constructor stub
	dead_man = -1;
	request_number = 0;
	local_mutex = PTHREAD_MUTEX_INITIALIZER;
	official_request_time = NOT_WAITING;
}

void Gravedigger::UpdateLocalList(const MessageModel& msg) {
	pthread_mutex_lock(&this->local_mutex);
	for (int i = 0; i < DEAD_LIST_SIZE; i++) {
		local_dead_list.push_back(msg.umarlaks[i]);
	}
	pthread_mutex_unlock(&this->local_mutex);
}

void Gravedigger::deadManRequest(int dead_man, int request_time) {
	request_number++;
	for (int i = GRAVEDIGGER; i < MpiHelper::GetSize(); i++) {
		if (i != MpiHelper::ProcesID()) {
			MessageModel msg;
			msg.iValue = dead_man;
			msg.request_time = request_time;
			SafeSend(msg, DEAD_MAN_REQUEST, i);
		}
	}
}

void Gravedigger::removeFromLocalDeadList(int dead_id) {
	if (local_dead_list.size() > 0) {
		for(vector<int>::iterator foo = local_dead_list.begin(); foo != local_dead_list.end(); ++foo){
			if(*foo == dead_id){
				local_dead_list.erase(foo);
				break;
			}
		}
	}
}

void Gravedigger::entomb() {
	std::stringstream ss;
	ss <<  "[" <<  setfill('0') << setw(6) << lamport_time
			<< "] Entombed [" << dead_man << "] by [" << id << "]\n";
	Log(ss);

	MessageModel msg;
	msg.iValue = dead_man;
	BroadcastOtherGravediggers(msg, DEAD_MAN_ENTOMBED);

	entombed_list.push_back(dead_man);
	usleep(rand() % ENTOMB_MAX_UTIME);
	pthread_mutex_lock(&this->mpi_mutex);
	lamport_time++;
	pthread_mutex_unlock(&this->mpi_mutex);

	pthread_mutex_lock(&this->local_mutex);
	removeFromLocalDeadList(dead_man);
	pthread_mutex_unlock(&this->local_mutex);
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
		if (!isDeadListEmpty()) {
			bool can_entomb = false;
			while (!can_entomb) {
				dead_man = getNextDeadMan();
				deadman_request_time = lamport_time;
				if(dead_man >= 0){
					request_status = WAIT;
					deadManRequest(dead_man, deadman_request_time);
					can_entomb = waitForDeadRespond();
				}
			}

			entomb();

			requestOfficial();
			waitForMyTurnInQueue();
			signDocs();
			releaseOfficial();
			dead_man = -1;
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

void Gravedigger::AddUniqueToQueueAndSort(int process_id, int time) {
	pthread_mutex_lock(&local_mutex);
	if(!VectorUtils::CheckIfVectorContainLeftValue(officeQueue, process_id)){
		officeQueue.push_back(std::make_pair(process_id, time));
	} else {
		for(int i=0; i<officeQueue.size(); i++){
			if(officeQueue[i].first == process_id) {
				officeQueue[i].second = time;
			}
		}
	}
	std::sort(officeQueue.begin(), officeQueue.end(), sort_pred());
	pthread_mutex_unlock(&local_mutex);
}

void Gravedigger::requestOfficial() {
	recieved_all_official_response = false;
	pthread_mutex_lock(&mpi_mutex);
	official_request_time = lamport_time;
	pthread_mutex_unlock(&mpi_mutex);
	AddUniqueToQueueAndSort(id, official_request_time);
	MessageModel msg;
	msg.iValue = official_request_time;
	BroadcastOtherGravediggers(msg, LOCK_OFFICIAL);
}

void Gravedigger::waitForMyTurnInQueue() {
	while(recieved_all_official_response == false);
	bool isFirst = false;
	int counter = 0;
	while(!isFirst){
		pthread_mutex_lock(&local_mutex);
		isFirst = (officeQueue[0].first == id);
		pthread_mutex_unlock(&local_mutex);
	}
	stringstream ss;
	ss <<  "[" <<  setfill('0') << setw(6) << lamport_time << "] Enters official critical section\n";
	Log(ss);
}

void Gravedigger::signDocs() {
	usleep(rand() % SIGN_DOCS_MAX_UTIME);
	pthread_mutex_lock(&this->mpi_mutex);
	lamport_time++;
	pthread_mutex_unlock(&this->mpi_mutex);
	stringstream ss;
	ss <<  "[" <<  setfill('0') << setw(6) << lamport_time << "] Docs signed for dead man[" << dead_man << "]" << endl;
	Log(ss);
}

void Gravedigger::removeFromQueue(int process_id) {
	pthread_mutex_lock(&local_mutex);
	if (officeQueue.size() > 0) {
		for(vector< pair<int, int> >::iterator foo = officeQueue.begin(); foo != officeQueue.end(); ++foo){
		    if( foo->first == process_id ){
		        officeQueue.erase(foo);
		        break;
		    }
		}
	}

	pthread_mutex_unlock(&local_mutex);
}

void Gravedigger::releaseOfficial() {
	removeFromQueue(id);
	pthread_mutex_lock(&local_mutex);
	official_request_time = NOT_WAITING;
	pthread_mutex_unlock(&local_mutex);
	MessageModel msg;
	BroadcastOtherGravediggers(msg, UNLOCK_OFFICIAL);
}
