/*
 * ActorUtils.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#include "ActorUtils.h"

ActorType ActorUtils::ConvertProcessIdToType(int id) {
	switch(id){
	case 0:
		return BROADCASTER;
	case 1:
		return ADMINISTRATION;
	case 2:
		return OFFICIAL;
	default:
		return GRAVEDIGGER;
	}
}
