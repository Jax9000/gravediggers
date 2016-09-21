/*
 * GravediggerMonitor.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#include "GravediggerMonitor.h"

GravediggerMonitor::GravediggerMonitor(Gravedigger *digger) :
		Monitor(digger) {
	gravedigger = (Gravedigger*) actor;
	respondTab = new int[MpiHelper::GetSize()];
	for(int i=0; i<MpiHelper::GetSize(); i++)
		respondTab[i] = 0;
	officialRespondCounter = 0;
}

bool GravediggerMonitor::checkIfCanBeEntomped(const int requesting_deadman_id, const int time, const int requesting_process_id) {
	return !gravedigger->checkIfEntombed(requesting_deadman_id) &&
			(gravedigger->getDeadMan() != requesting_deadman_id ||
					(time < gravedigger->lamport_time || requesting_process_id < gravedigger->getId()));
}

bool GravediggerMonitor::checkIfAllProcessesRespond() {
	int responded = 0;
	for (int i = 0; i < MpiHelper::GetGravediggerCount(); i++)
		if (respondTab[i] == gravedigger->request_number)
			responded++;
	return responded == MpiHelper::GetGravediggerCount() - 1;
}

void GravediggerMonitor::ListenAndHandleMassages() {
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
		msg_respond.bValue = checkIfCanBeEntomped(msg.iValue, msg.time, status.MPI_SOURCE);
//		ss << "My dead_man: " << gravedigger->getDeadMan() << ", requesting: " << msg.iValue << " time ["
//				<< gravedigger->lamport_time << ":" << msg.time <<  "] respond: " << msg_respond.bValue << endl;
//		gravedigger->Log(ss);
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
		gravedigger->removeOfficial(status.MPI_SOURCE);
		break;
	}

}
