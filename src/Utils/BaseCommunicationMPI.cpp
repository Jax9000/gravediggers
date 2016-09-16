#include "BaseCommunicationMPI.h"

BaseCommunicationMPI::BaseCommunicationMPI()
{
}

MessageModel BaseCommunicationMPI::Receive(int source, int type, MPI_Status *status)
{
    MessageModel msg;
    MPI_Recv(&msg, sizeof(MessageModel), MPI_BYTE, source, type, MPI_COMM_WORLD, status);
    return msg;
}

MessageModel BaseCommunicationMPI::Receive(int source, int type)
{
    return Receive(source, type, MPI_STATUS_IGNORE);
}
