/*
 * MessageModel.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef MESSAGEMODEL_H_
#define MESSAGEMODEL_H_
#define BUFF_SIZE 32

#include <vector>

#include "../Enums/MessageType.h"
#include "../Enums/ActorType.h"

using namespace std;

struct MessageModel {
    int time;
    int iValue;
    int umarlaks[20];
    bool bValue;
    int request_time;
};

#endif /* MESSAGEMODEL_H_ */
