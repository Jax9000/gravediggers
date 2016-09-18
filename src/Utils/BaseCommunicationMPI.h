#ifndef BASECOMMUNICATIONMPI_H
#define BASECOMMUNICATIONMPI_H

#include <mpi.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "../Models/MessageModel.h"
#include "../Utils/MpiHelper.h"
#include "../Defines.h"

using namespace std;

class BaseCommunicationMPI
{
public:
    BaseCommunicationMPI();
    void Send(MessageModel &message, MessageType type,  int receiver);
    MessageModel Receive(int source, int type, MPI_Status *status);
    MessageModel Receive(int source, int type);
    virtual void Log(std::stringstream &ss);
    virtual ~BaseCommunicationMPI();

    int lamport_time;
};

#endif // BASECOMMUNICATIONMPI_H
