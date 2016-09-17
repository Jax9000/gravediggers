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
    GravediggerMonitor(Gravedigger * digger,  pthread_mutex_t mutex);
};

#endif /* GRAVEDIGGERMONITOR_H_ */
