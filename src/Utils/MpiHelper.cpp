#include "MpiHelper.h"
#include "mpi.h"

int MpiHelper::ProcesID() {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    return rank;
}
