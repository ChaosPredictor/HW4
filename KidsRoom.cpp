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
	{}

void KidsRoom::setNewAgeLimit(const int& limit) {
	if ( limit < 0 ) throw KidsRoomIllegalAgeLimit();
	ageLimit = limit;
}

int KidsRoom::getAgeLimit() const{
	return ageLimit;
}

}
}
