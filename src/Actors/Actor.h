/*
 * Actor.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include <mpi.h>
#include <pthread.h>
#include <iostream>
#include "../Utils/MpiHelper.h"
#include "../Utils/ActorUtils.h"

class Actor {
public:
	Actor();
	Actor(int id);
    virtual void Run(){
    	std::cout << "xD" << std::endl;
    }
	virtual ActorType GetType();
	virtual ~Actor();

protected:
	ActorType actor_type;
	int id;
    bool isworking;
	bool wants_to_send;
    int timer;

};
#endif /* ACTOR_H_ */
