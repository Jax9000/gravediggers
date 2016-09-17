/*
 * Administration.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#include "Administration.h"

Administration::Administration(int id) : Actor::Actor(id) {
	// TODO Auto-generated constructor stub
	current_umarlak = 0;
}

void Administration::Run() {
	isworking = true;
    while(isworking){
        MessageModel msg;
		fillWithUmarlaks(msg.umarlaks, DEAD_LIST_SIZE);
        for(int i=GRAVEDIGGER; i<MpiHelper::GetSize(); i++){
        	Send(msg, DEAD_MAN_LIST, i);
        }
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
