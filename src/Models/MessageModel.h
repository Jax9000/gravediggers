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
    int requesting_dead_man;
    int umarlaks[20];
};

#endif /* MESSAGEMODEL_H_ */
