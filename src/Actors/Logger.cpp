/*
 * Logger.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: jjax
 */

#include "Logger.h"

void Logger::Run() {
	isworking = true;
	while (isworking) {
		char msg[MAX_LOG_LENGTH];
		MPI_Status status;
		MPI_Recv(&msg, MAX_LOG_LENGTH, MPI_CHAR, MPI_ANY_SOURCE, LOG, MPI_COMM_WORLD, &status);
		cout << "[" << status.MPI_SOURCE << "]: " << msg;
	}
}
