#include "BaseCommunicationMPI.h"

BaseCommunicationMPI::BaseCommunicationMPI() {
	lamport_time = 0;
}

void BaseCommunicationMPI::Send(MessageModel &message, MessageType type,
		int receiver) {
	if (type != SPAM) {
		lamport_time++;
	}
	message.time = lamport_time;
	MPI_Send(&message, sizeof(MessageModel), MPI_BYTE, receiver, (int) type,
	MPI_COMM_WORLD);
}

MessageModel BaseCommunicationMPI::Receive(int source, int type,
		MPI_Status *status) {
	MessageModel msg;
	MPI_Recv(&msg, sizeof(MessageModel), MPI_BYTE, source, type, MPI_COMM_WORLD,
			status);
	if (status->MPI_TAG != SPAM) {
		lamport_time = std::max(msg.time, lamport_time);
	}
	return msg;
}

MessageModel BaseCommunicationMPI::Receive(int source, int type) {
	MPI_Status status;
	return Receive(source, type, &status);
}

void BaseCommunicationMPI::Log(std::stringstream &ss) {
	char buffer[MAX_LOG_LENGTH];
	sprintf(buffer, "%s", ss.str().c_str());
	buffer[MAX_LOG_LENGTH - 1] = '\n';
	MPI_Send(buffer, MAX_LOG_LENGTH, MPI_CHAR, LOGGER, LOG, MPI_COMM_WORLD);
}

BaseCommunicationMPI::~BaseCommunicationMPI() {
}
