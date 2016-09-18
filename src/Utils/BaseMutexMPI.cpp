#include "BaseMutexMPI.h"


BaseMutexMPI::BaseMutexMPI()
{
	mpi_mutex = PTHREAD_MUTEX_INITIALIZER;
}

MessageModel BaseMutexMPI::SafeReceive(int source, int type, MPI_Status *status)
{
    pthread_mutex_lock(&this->mpi_mutex);
    MessageModel msg;
    msg = Receive(source, type, status);
    pthread_mutex_unlock(&this->mpi_mutex);
    return msg;
}

MessageModel BaseMutexMPI::SafeReceive(int source, int type)
{
    return SafeReceive(source, type, MPI_STATUS_IGNORE);
}

void BaseMutexMPI::Log(stringstream &ss) {
	pthread_mutex_lock(&this->mpi_mutex);
	BaseCommunicationMPI::Log(ss);
	pthread_mutex_unlock(&this->mpi_mutex);
}
