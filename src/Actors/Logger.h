/*
 * Logger.h
 *
 *  Created on: Sep 18, 2016
 *      Author: jjax
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "../Defines.h"
#include "../Enums/MessageType.h"
#include "../Actors/Actor.h"
#include <iostream>
#include <mpi.h>
#include <iomanip>

using std::cout;

class Logger : public Actor {
public:
	void Run();
};

#endif /* LOGGER_H_ */
