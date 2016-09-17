/*
 * GravediggerMonitor.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#include "GravediggerMonitor.h"

GravediggerMonitor::GravediggerMonitor(Gravedigger *digger) :
		Monitor(digger) {
	respondTab = new int[MpiHelper::GetSize()];
	for(int i=0; i<MpiHelper::GetSize(); i++)
		respondTab[i] = 0;
}

Gravedigger* GravediggerMonitor::GetGravedigger() {
	return (Gravedigger*) actor;
}

void GravediggerMonitor::ListenAndHandleMassages() {
	MPI_Status status;
	Gravedigger* gravedigger = GetGravedigger();
	MessageModel msg = gravedigger->SafeReceive(MPI_ANY_SOURCE, MPI_ANY_TAG,
			&status);
	switch (status.MPI_TAG) {
	case SPAM:
		break;
	case DEAD_MAN_LIST:
		gravedigger->UpdateLocalList(msg);
		break;
	case DEAD_MAN_REQUEST:
		MessageModel msg_respond;
		msg_respond.requesting_dead_man = msg.requesting_dead_man;
		msg_respond.bValue = gravedigger->getDeadMan() != msg.requesting_dead_man
				|| msg.time < gravedigger->lamport_time;
		gravedigger->SafeSend(msg_respond, DEAD_MAN_RESPOND, status.MPI_SOURCE);
		break;
	case DEAD_MAN_RESPOND:
		int respondingProcess = status.MPI_SOURCE - GRAVEDIGGER;
		respondTab[respondingProcess]++;
		if(respondTab[respondingProcess] == gravedigger->request_number
				&& gravedigger->getRequestStatus() == WAIT) {
			cout << "A" << endl;
			if(!msg.bValue){
				cout << "B" << endl;
				gravedigger->setRequestStatus(REFUSE);
			}
			else
			{
				cout << "C" << endl;
				int responded = 0;
				for(int i = 0; i < MpiHelper::GetSize() - GRAVEDIGGER; i++)
					if(respondTab[i] == gravedigger->request_number)
						responded++;

				if(responded == MpiHelper::GetSize() - GRAVEDIGGER - 1)
					gravedigger->setRequestStatus(ACCEPT);
			}
		}
		cout << "responding process : " << respondingProcess + 2 << " request numeber : " << gravedigger->request_number << " local_request_number " << respondTab[respondingProcess] << " umarlak number : " << gravedigger->getDeadMan() << endl;
		break;
	}
}
