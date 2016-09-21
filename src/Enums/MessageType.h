/*
 * MessageType.h
 *
 *  Created on: Jul 2, 2016
 *      Author: jjax
 */

#ifndef MESSAGETYPE_H_
#define MESSAGETYPE_H_

enum MessageType {
	EXAMPLE_TYPE,
	SPAM,
	LOG,
	DEAD_MAN_LIST,
	DEAD_MAN_REQUEST,
	DEAD_MAN_RESPOND,
	DEAD_MAN_ENTOMBED,
	LOCK_OFFICIAL,
	UNLOCK_OFFICIAL,
	LOCK_OFFICIAL_RESPOND
};

#endif /* MESSAGETYPE_H_ */
