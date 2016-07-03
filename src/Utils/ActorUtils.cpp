/*
 * ActorUtils.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#include "ActorUtils.h"

ActorType ActorUtils::ConvertId2Type(int id) {
	switch(id){
	case 0:
		return ADMINISTRATION;
	case 1:
		return OFFICIAL;
	default:
		return GRAVEDIGGER;
	}
	return UNDEFINED;
}
