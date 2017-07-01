/*
 * KidsRoom.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: master
 */


#include "KidsRoom.h"

namespace mtm{
namespace escaperoom {

KidsRoom::KidsRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit):
	EscapeRoomWrapper::EscapeRoomWrapper(name, escapeTime, level, maxParticipants),
	ageLimit(ageLimit)
	{	if ( ageLimit < 0 ) throw KidsRoomIllegalAgeLimit();
}

void KidsRoom::setNewAgeLimit(const int& limit) {
	if ( limit < 0 ) throw KidsRoomIllegalAgeLimit();
	ageLimit = limit;
}

int KidsRoom::getAgeLimit() const{
	return ageLimit;
}

/*virtual int KidsRoom::getRoomType() const{
	return 2;
}*/


void KidsRoom::print(std::ostream& output) const {
	output << "Kids Room: ";
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

std::ostream& operator<<(std::ostream& output, const KidsRoom& room) {
    room.print(output);
    return output;
}

}
}
