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

void ScaryRoom::setNewAgeLimit(const int& limit) {
	if ( limit < 0 ) throw ScaryRoomIllegalAgeLimit();
	ageLimit = limit;
}

void ScaryRoom::incNumberOfScaryEnigmas() {
	numOfScaryEnigmas++;
}

int ScaryRoom::getAgeLimit() const{
	return ageLimit;
}

std::ostream& operator<<(std::ostream& output, const ScaryRoom& room) {
	output << "Scary Room: ";
	output << room.getName();
	output << " (";
	output << room.getMaxTime();
	output << "/";
	output << room.getRoomLevel();
	output << "/";
	output << room.getMaxParticipants();
	output << "/";
	output << room.getAgeLimit();
	output << ")";
	return output;
}

}
}

