#include <iostream>
#include <math.h> 
#include <mpi.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include "Models/MessageModel.h"
using namespace std;

int main(int argc, char *argv[]) {
	MPI::Init(argc, argv);

	int size, rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	MessageModel message;

	if (rank == 0) {
		if (fork() == 0) {
			MPI_Recv(&message, sizeof(MessageModel), MPI_BYTE, MPI_ANY_SOURCE,
					MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << message.content << endl;
		} else {

		}
		sleep(2);
	}

	if (rank == 1) {
		if (fork() == 0) {
			cout << "XD" << endl;
		} else {
			strcpy(message.content, "dupa");
			MPI_Send(&message,sizeof(MessageModel), MPI_BYTE, 0, 1, MPI_COMM_WORLD);
		}
		sleep(2);
	}

	MPI::Finalize();
	return 0;
}

