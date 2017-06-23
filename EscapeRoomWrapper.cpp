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
	room = escapeRoomCreate(name, escapeTime, maxParticipants, level);
	if(room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}

}

escaperoom::EscapeRoomWrapper::~EscapeRoomWrapper() {
	escapeRoomDestroy(room);

}

}
}
