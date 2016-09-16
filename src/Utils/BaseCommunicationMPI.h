#ifndef BASECOMMUNICATIONMPI_H
#define BASECOMMUNICATIONMPI_H

#include <mpi.h>

#include "../Models/MessageModel.h"

class BaseCommunicationMPI
{
protected:
    BaseCommunicationMPI();
protected:
    template<typename T>
    void Send(T &message, MessageType type,  int receiver) {
        MPI_Send(&message, sizeof(T), MPI_BYTE, receiver, (int)type, MPI_COMM_WORLD);
    }

    MessageModel Receive(int source, int type, MPI_Status *status);
    MessageModel Receive(int source, int type);

};

#endif // BASECOMMUNICATIONMPI_H
