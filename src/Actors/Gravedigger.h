/*
 * Gravedigger.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef GRAVEDIGGER_H_
#define GRAVEDIGGER_H_

#define NOT_WAITING -1

#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <iomanip>

#include "Actor.h"

#include "../Defines.h"
#include "../Utils/BaseMutexMPI.h"
#include "../Utils/VectorUtils.h"
#include "../Utils/MpiHelper.h"
#include "../Enums/RequestStatus.h"

class Gravedigger : public Actor, public BaseMutexMPI {
public:
	Gravedigger(int id);
	void Run() override;
	virtual ~Gravedigger();
	void UpdateLocalList(const MessageModel& msg);
	bool checkIfEntombed(int dead_id);
	void AddUniqueToQueueAndSort(int process_id, int time);
	void removeFromLocalDeadList(int);
	void removeFromQueue(int process_id);

	int getDeadMan() const {
		return dead_man;
	}

	const vector<int>& getLocalDeadList() const {
		return local_dead_list;
	}

	void setRequestStatus(RequestStatus requestStatus) {
		request_status = requestStatus;
	}

	RequestStatus getRequestStatus() const {
		return request_status;
	}


	bool isRecievedAllOfficialResponse() const {
		return recieved_all_official_response;
	}

	void setRecievedAllOfficialResponse(bool recievedAllOfficialResponse) {
		recieved_all_official_response = recievedAllOfficialResponse;
	}

	int getOfficialRequestTime() const {
		return official_request_time;
	}

	void setOfficialRequestTime(int officialRequestTime) {
		official_request_time = officialRequestTime;
	}

	int request_number;
	std::vector<pair<int, int> > officeQueue;
	int official_request_time;
	vector<int> entombed_list;
	int deadman_request_time;

private:
	vector<int> local_dead_list;
	int dead_man;
	RequestStatus request_status;
	bool recieved_all_official_response;
    pthread_mutex_t local_mutex;

	void deadManRequest(int dead_man, int request_time);
	bool waitForDeadRespond();
	void entomb();
	bool isDeadListEmpty();
	int getNextDeadMan();
    void BroadcastOtherGravediggers(MessageModel &msg, MessageType type);
	void requestOfficial();
	void waitForMyTurnInQueue();
	void signDocs();
	void releaseOfficial();
};

#endif /* GRAVEDIGGER_H_ */
