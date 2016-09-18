/*
 * Gravedigger.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef GRAVEDIGGER_H_
#define GRAVEDIGGER_H_

#include <iostream>
#include <unistd.h>
#include <algorithm>

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

	void removeFromLocalDeadList(int);

	int request_number;
	std::vector<pair<int, int> > officeQueue;
	vector<int> entombed_list;

private:
	vector<int> local_dead_list;
	bool can_remove;
	int dead_man;
	int request_time;
	RequestStatus request_status;
    pthread_mutex_t process_mutex;

	void deadManRequest(int dead_man);
	bool waitForDeadRespond();
	void entomb();
	bool isDeadListEmpty();
	int getNextDeadMan();


    void BroadcastOtherGravediggers(MessageModel &msg, MessageType type);
};

#endif /* GRAVEDIGGER_H_ */
