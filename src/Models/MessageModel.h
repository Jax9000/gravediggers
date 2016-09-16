/*
 * MessageModel.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef MESSAGEMODEL_H_
#define MESSAGEMODEL_H_
#define BUFF_SIZE 32

#include "../Enums/MessageType.h"
#include "../Enums/ActorType.h"

using namespace std;

struct MessageModel {
    enum ActorType actor_type;
	int process_id;
	char content[BUFF_SIZE];
};

#endif /* MESSAGEMODEL_H_ */
