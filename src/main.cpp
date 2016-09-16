#include "EnviromentController.h"
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

	EnviromentController enviroment_controller(argc, argv);
	enviroment_controller.Start();

	MPI::Finalize();
	return 0;
}

