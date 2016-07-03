/*
 * ActorUtils.h
 *
 *  Created on: Jul 3, 2016
 *      Author: jjax
 */

#ifndef ACTORUTILS_H_
#define ACTORUTILS_H_

#include "../Enums/ActorType.h"

class ActorUtils {
public:
	static ActorType ConvertId2Type(int id);
};

#endif /* ACTORUTILS_H_ */
