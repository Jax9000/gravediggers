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
}

bool GravediggerMonitor::checkIfCanBeEntomped(const int dead_id, const int time) {
	return !gravedigger->checkIfEntombed(dead_id)
			&& (gravedigger->getDeadMan() != dead_id
					|| time < gravedigger->lamport_time);
}

bool GravediggerMonitor::checkIfAllProcessesRespond() {
	int responded = 0;
	for (int i = 0; i < MpiHelper::GetSize() - GRAVEDIGGER; i++)
		if (respondTab[i] == gravedigger->request_number)
			responded++;
	return responded == MpiHelper::GetSize() - GRAVEDIGGER - 1;
}

void GravediggerMonitor::ListenAndHandleMassages() {
	MPI_Status status;
	MessageModel msg = gravedigger->SafeReceive(MPI_ANY_SOURCE, MPI_ANY_TAG,
			&status);
	std::stringstream ss;
	ss.clear();
	switch (status.MPI_TAG) {
	case SPAM:
		break;
	case DEAD_MAN_LIST:
		gravedigger->UpdateLocalList(msg);
		break;
	case DEAD_MAN_REQUEST:
		MessageModel msg_respond;
		msg_respond.iValue = msg.iValue;
		msg_respond.bValue = checkIfCanBeEntomped(msg.iValue, msg.time);
		ss << "My dead_man: " << gravedigger->getDeadMan() << ", requesting: " << msg.iValue << " time ["
				<< gravedigger->lamport_time << ":" << msg.time <<  "] respond: " << msg_respond.bValue << endl;
		gravedigger->Log(ss);
		gravedigger->SafeSend(msg_respond, DEAD_MAN_RESPOND, status.MPI_SOURCE);
		break;
	case DEAD_MAN_ENTOMBED:
		gravedigger->removeFromLocalDeadList(msg.iValue);
		break;
	case DEAD_MAN_RESPOND:
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
}
