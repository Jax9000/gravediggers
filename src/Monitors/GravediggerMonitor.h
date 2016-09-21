/*
 * GravediggerMonitor.h
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#ifndef GRAVEDIGGERMONITOR_H_
#define GRAVEDIGGERMONITOR_H_

#include "Monitor.h"
#include "../Actors/Gravedigger.h"

class GravediggerMonitor : public Monitor{
public:
    GravediggerMonitor(Gravedigger * digger);
	bool checkIfCanBeEntomped(const int requesting_deadman_id, const int time, const int requesting_process_id);

protected:
    void ListenAndHandleMassages();

    int * respondTab;
    Gravedigger* gravedigger;

private:
	bool checkIfAllProcessesRespond();
	int officialRespondCounter;
};

#endif /* GRAVEDIGGERMONITOR_H_ */
