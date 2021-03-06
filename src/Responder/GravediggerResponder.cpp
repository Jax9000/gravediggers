/*
 * GravediggerMonitor.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#include "../Responder/GravediggerResponder.h"

GravediggerResponder::GravediggerResponder(Gravedigger *digger) :
		Responder(digger) {
	gravedigger = (Gravedigger*) actor;
	respondTab = new int[MpiHelper::GetSize()];
	for(int i=0; i<MpiHelper::GetSize(); i++)
		respondTab[i] = 0;
	officialRespondCounter = 0;
}

bool GravediggerResponder::checkIfCanBeEntomped(const int requesting_deadman_id, const int time, const int requesting_process_id) {
	bool isEntombed = gravedigger->checkIfEntombed(requesting_deadman_id);
	bool notMyDeadMan = gravedigger->getDeadMan() != requesting_deadman_id;
	bool heRequestedFirst = time < gravedigger->deadman_request_time;
	bool requestedInTheSameTime = time == gravedigger->deadman_request_time;
	bool hasSmallerId = requesting_process_id < gravedigger->getId();
	return !isEntombed &&
			(notMyDeadMan || heRequestedFirst || (requestedInTheSameTime && hasSmallerId));
}

bool GravediggerResponder::checkIfAllProcessesRespond() {
	int responded = 0;
	for (int i = 0; i < MpiHelper::GetGravediggerCount(); i++)
		if (respondTab[i] == gravedigger->request_number)
			responded++;
	return responded == MpiHelper::GetGravediggerCount() - 1;
}

void GravediggerResponder::ListenAndHandleMassages() {
	MPI_Status status;
	MessageModel msg = gravedigger->SafeReceive(MPI_ANY_SOURCE, MPI_ANY_TAG,
			&status);
	std::stringstream ss;
	ss.clear();
	MessageModel msg_respond;
	switch (status.MPI_TAG) {
	case SPAM:
		break;
	case DEAD_MAN_LIST:
		gravedigger->UpdateLocalList(msg);
		break;
	case DEAD_MAN_REQUEST:
		msg_respond.iValue = msg.iValue;
		msg_respond.bValue = checkIfCanBeEntomped(msg.iValue, msg.request_time, status.MPI_SOURCE);
		gravedigger->SafeSend(msg_respond, DEAD_MAN_RESPOND, status.MPI_SOURCE);
		break;
	case DEAD_MAN_ENTOMBED:
		gravedigger->removeFromLocalDeadList(msg.iValue);
		break;
	case DEAD_MAN_RESPOND:{
			int respondingProcess = status.MPI_SOURCE - GRAVEDIGGER;
			respondTab[respondingProcess]++;
			if(respondTab[respondingProcess] == gravedigger->request_number
					&& gravedigger->getRequestStatus() == WAIT) {
				if(!msg.bValue){
					gravedigger->setRequestStatus(REFUSE);
				}
				else if(checkIfAllProcessesRespond())
				{
					gravedigger->setRequestStatus(ACCEPT);
				}
			}
			break;
		}
	case LOCK_OFFICIAL:
		gravedigger->AddUniqueToQueueAndSort(status.MPI_SOURCE, msg.iValue);
		msg_respond.iValue = gravedigger->getOfficialRequestTime();
		gravedigger->SafeSend(msg_respond, LOCK_OFFICIAL_RESPOND, status.MPI_SOURCE);
		break;
	case LOCK_OFFICIAL_RESPOND:
		if(msg.iValue != NOT_WAITING){
			gravedigger->AddUniqueToQueueAndSort(status.MPI_SOURCE, msg.iValue);
		}

		officialRespondCounter++;
		if(officialRespondCounter >= MpiHelper::GetGravediggerCount() - 1){
			gravedigger->setRecievedAllOfficialResponse(true);
			officialRespondCounter = 0;
		}
		break;
	case UNLOCK_OFFICIAL:
		gravedigger->removeFromQueue(status.MPI_SOURCE);
		break;
	}

}
