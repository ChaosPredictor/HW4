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
	numOfScaryEnigmas(numOfScaryEnigmas) {
	if ( ageLimit < 0 ) throw ScaryRoomIllegalAgeLimit();
	if ( numOfScaryEnigmas < 0 ) throw ScaryRoomException();
}

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

/*virtual int ScaryRoom::getRoomType() const {
	return 1;
}*/


void ScaryRoom::print(std::ostream& output) const {
	output << "Scary Room: ";
	output << getName();
	output << " (";
	output << getMaxTime();
	output << "/";
	output << getRoomLevel();
	output << "/";
	output << getMaxParticipants();
	output << "/";
	output << getAgeLimit();
	output << ")";
}



std::ostream& operator<<(std::ostream& output, const ScaryRoom& room) {
    room.print(output);
    return output;
}




}
}

