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

protected:
    template<typename T>
    void Send(T &message, MessageType type,  int receiver) {
        MPI_Send(&message, sizeof(T), MPI_BYTE, receiver, (int)type, MPI_COMM_WORLD);
    }

//    void * Receive(int source, MessageType type, MPI_Comm comm, MPI_Status *status) {
//        void * msg;
//        int size = 0;
//        switch (type) {
//        case SPAM:
//            msg = new MessageModel();
//            size = sizeof(MessageModel);
//            break;
//        default:
//            break;
//        }
//        MPI_Recv(msg, size, MPI_BYTE, source, (int)type, comm, status);
//        return msg;
//    }

    MessageModel Receive(int source, int type, MPI_Status *status);
    MessageModel Receive(int source, int type);
    
	ActorType actor_type;
	int id;
	bool isworking;
	bool wants_to_send;
    int timer;

private:
	static void *thread_provider(void* object);
};

#endif /* ACTOR_H_ */
