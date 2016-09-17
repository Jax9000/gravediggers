#include "BaseMutexMPI.h"


BaseMutexMPI::BaseMutexMPI()
{
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

pthread_mutex_t BaseMutexMPI::GetMutex()
{
    return  this->mpi_mutex;
}
