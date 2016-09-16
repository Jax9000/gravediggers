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
#include "../Utils/MpiHelper.h"
#include "../Enums/MessageType.h"
#include "../Models/MessageModel.h"
#include "../Utils/ActorUtils.h"

class Actor {
public:
	Actor();
	Actor(int id);
	virtual ActorType GetType();
	virtual ~Actor();
	pthread_mutex_t GetMutex();

protected:
    template<typename T>
    void Send(T &message, MessageType type,  int receiver) {
        MPI_Send(&message, sizeof(T), MPI_BYTE, receiver, (int)type, MPI_COMM_WORLD);
    }

    MessageModel Receive(int source, int type, MPI_Status *status);
    MessageModel Receive(int source, int type);
    
	ActorType actor_type;
	int id;
	bool isworking;
	bool wants_to_send;
	pthread_mutex_t mpi_mutex;
    int timer;
    
private:
	static void *thread_provider(void* object);
};

#endif /* ACTOR_H_ */
