#ifndef BASEMUTEXMPI_H
#define BASEMUTEXMPI_H

#include <pthread.h>
#include "BaseCommunicationMPI.h"

class BaseMutexMPI: public BaseCommunicationMPI {
public:
	BaseMutexMPI();

	void SafeSend(MessageModel &message, MessageType type, int receiver) {
		pthread_mutex_lock(&this->mpi_mutex);
		Send(message, type, receiver);
		pthread_mutex_unlock(&this->mpi_mutex);
	}

	MessageModel SafeReceive(int source, int type, MPI_Status *status);
	MessageModel SafeReceive(int source, int type);
	void Log(stringstream &ss);
protected:

	pthread_mutex_t mpi_mutex;
};

#endif // BASEMUTEXMPI_H
