#include "EnviromentController.h"
#include <unistd.h>
#include <stdio.h>
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

//	EnviromentController enviroment_controller(argc, argv);
//	enviroment_controller.Start();

	int provided;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provided);
	if (provided < MPI_THREAD_SERIALIZED)
	{
	    printf("ERROR: The MPI library does not have full thread support\n");
	    MPI_Abort(MPI_COMM_WORLD, 1);
	}

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if(rank != 5){
		if(fork()){
			int number = 10;
			MPI_Recv(&number, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		} else {
			int number = 10;
			MPI_Recv(&number, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			cout << "process: " << rank << " otrzymal: " << number << endl;
		}
	} else {
		for(int i = 1; i < 10; i++){
			if(i != rank){
				MPI_Send(&i, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
			}
		}
	}



	sleep(5000);
	MPI::Finalize();
	return 0;
}

