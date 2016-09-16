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
	default:
		return new GravediggerMonitor();
	}
}
