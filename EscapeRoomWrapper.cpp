/*
 * EscapeRoomWrapper.cpp
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */


//TODO remove it
#include <stdio.h>
#include "EscapeRoomWrapper.h"



mtm::escaperoom::EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& escapeTime, const int& level, const int& maxParticipants) {
	EscapeRoom escapeRoom = escapeRoomCreate(name, escapeTime, maxParticipants, level);

	escapeRoomDestroy(escapeRoom);

	//printf("EscapeRoomWrapper constructor\n");
}

mtm::escaperoom::EscapeRoomWrapper::~EscapeRoomWrapper() {

}
