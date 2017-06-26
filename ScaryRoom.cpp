/*
 * ScaryRoom.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: master
 */

#include "ScaryRoom.h"

namespace mtm{
namespace escaperoom {


ScaryRoom::ScaryRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas):
	EscapeRoomWrapper::EscapeRoomWrapper(name, escapeTime, level, maxParticipants),
	ageLimit(ageLimit),
	numOfScaryEnigmas(numOfScaryEnigmas) {}

}
}

