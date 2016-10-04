/*
 * GravediggerMonitor.h
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#ifndef GRAVEDIGGERRESPONDER_H_
#define GRAVEDIGGERRESPONDER_H_

#include "../Actors/Gravedigger.h"
#include "../Responder/Responder.h"

class GravediggerResponder : public Responder{
public:
    GravediggerResponder(Gravedigger * digger);
	bool checkIfCanBeEntomped(const int requesting_deadman_id, const int time, const int requesting_process_id);

protected:
    void ListenAndHandleMassages();

    int * respondTab;
    Gravedigger* gravedigger;

private:
	bool checkIfAllProcessesRespond();
	int officialRespondCounter;
};

#endif /* GRAVEDIGGERRESPONDER_H_ */
