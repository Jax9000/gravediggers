#ifndef BASEMUTEXMPI_H
#define BASEMUTEXMPI_H

#include <pthread.h>
#include "BaseCommunicationMPI.h"

class BaseMutexMPI : public BaseCommunicationMPI
{
public:
    BaseMutexMPI();
    pthread_mutex_t GetMutex();

protected:
        template<typename T>
        void SafeSend(T &message, MessageType type,  int receiver) {
            pthread_mutex_lock(&this->mpi_mutex);
            Send(message, type, receiver);
            pthread_mutex_unlock(&this->mpi_mutex);
        }

        MessageModel SafeReceive(int source, int type, MPI_Status *status);
        MessageModel SafeReceive(int source, int type);
        pthread_mutex_t mpi_mutex;
};

#endif // BASEMUTEXMPI_H
