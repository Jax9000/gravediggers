#ifndef BASECOMMUNICATIONMPI_H
#define BASECOMMUNICATIONMPI_H

#include <mpi.h>
#include <algorithm>
#include <iostream>
#include "../Models/MessageModel.h"
#include "../Utils/MpiHelper.h"

using namespace std;

class BaseCommunicationMPI
{
public:
    BaseCommunicationMPI();
    void Send(MessageModel &message, MessageType type,  int receiver);
    MessageModel Receive(int source, int type, MPI_Status *status);
    MessageModel Receive(int source, int type);


    int lamport_time;

};

#endif // BASECOMMUNICATIONMPI_H
