/*
 * EscapeRoomWrapper.cpp
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */


//TODO remove it
#include <stdio.h>
#include "EscapeRoomWrapper.h"

namespace mtm{
namespace escaperoom {

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& escapeTime, const int& level, const int& maxParticipants) {
	//EscapeRoom escapeRoom = escapeRoomCreate(name, escapeTime, maxParticipants, level);
	this = escapeRoomCreate(name, escapeTime, maxParticipants, level);

	//printf("EscapeRoomWrapper constructor\n");
}

EscapeRoomWrapper::~EscapeRoomWrapper() {
	escapeRoomDestroy(this);

}

}
}
