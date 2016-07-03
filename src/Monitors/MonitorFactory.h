/*
 * MonitorFactory.h
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#ifndef MONITORFACTORY_H_
#define MONITORFACTORY_H_

#include "Monitor.h"
#include "AdministrationMonitor.h"
#include "GravediggerMonitor.h"
#include "OfficialMonitor.h"
#include "../Enums/ActorType.h"


class MonitorFactory {
public:
	static Monitor* Build(ActorType type);
};

#endif /* MONITORFACTORY_H_ */
