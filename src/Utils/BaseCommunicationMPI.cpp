#include "BaseCommunicationMPI.h"

BaseCommunicationMPI::BaseCommunicationMPI()
{
    lamport_time = 0;
}

void BaseCommunicationMPI::Send(MessageModel &message, MessageType type, int receiver)
{
    lamport_time++;
    message.time =  lamport_time;
    MPI_Send(&message, sizeof(MessageModel), MPI_BYTE, receiver, (int)type, MPI_COMM_WORLD);
    cout << "sended from " << MpiHelper::ProcesID() << " to " << receiver << " type: " << type << " time: " << lamport_time << endl;
}

            MessageModel BaseCommunicationMPI::Receive(int source, int type, MPI_Status *status)
    {
            MessageModel msg;
            MPI_Recv(&msg, sizeof(MessageModel), MPI_BYTE, source, type, MPI_COMM_WORLD, status);
            cout << "recieved from "  << status->MPI_SOURCE <<  " to " << MpiHelper::ProcesID()  << " type: " << type << " time: " << lamport_time << endl;
            lamport_time = std::max(msg.time, lamport_time) + 1;
            return msg;
}

            MessageModel BaseCommunicationMPI::Receive(int source, int type)
    {
            return Receive(source, type, MPI_STATUS_IGNORE);
}
