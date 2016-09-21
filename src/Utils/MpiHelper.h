#ifndef MPIHELPER_H
#define MPIHELPER_H

#include "mpi.h"
#include "../Enums/ActorType.h"

class MpiHelper {
public:
    static int ProcesID();
    static int GetSize();
    static int GetGravediggerCount();
};

#endif // MPIHELPER_H
