/*
 * Administration.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Administration.h"

Administration::Administration(int id) : Actor::Actor(id) {
	// TODO Auto-generated constructor stub
    srand (time(NULL));
}

void Administration::Run() {
    isworking = true;
    while(isworking){
        int umarlaks[20];
        fillWithUmarlaks(umarlaks, 20);
        MessageModel model;
        model.umarlaks = umarlaks;
//TODO send to others
        sleep(rand()%MAX_SLEEP_TIME);
    }
}

Administration::~Administration() {
    // TODO Auto-generated destructor stub
}

void Administration::fillWithUmarlaks(int *array, int size)
{
    for(int i =0; i<size; i++){
        array[i] = current_umarlak++;
    }
}
