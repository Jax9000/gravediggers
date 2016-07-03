/*
 * MonitorFactory.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#include "MonitorFactory.h"

Monitor* MonitorFactory::Build(ActorType type) {
	switch(type){
	case ADMINISTRATION:
		return new AdministrationMonitor();
	case OFFICIAL:
		return new OfficialMonitor();
	default:
		return new GravediggerMonitor();
	}
}
