#include "MpiHelper.h"
#include "mpi.h"

int MpiHelper::ProcesID() {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    return rank;
}

int MpiHelper::GetSize() {
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	return size;
}
