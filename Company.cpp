/*
 * Company.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: master
 */

#include "Company.h"


namespace mtm{
namespace escaperoom{

Company::Company(string name, string phoneNumber) : name(name), phoneNumber(phoneNumber) {}

Company::~Company() {
	for (std::set<EscapeRoomWrapper*>::iterator it=rooms.begin(); it!=rooms.end(); ++it) {
		delete *it;
	}
}

void Company::createRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants) {
	try {
		EscapeRoomWrapper* room = new EscapeRoomWrapper(name, escapeTime, level, maxParticipants);

		rooms.insert(room);

	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}

void Company::createScaryRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas) {

	try {
		ScaryRoom* room = new ScaryRoom(name, escapeTime, level, maxParticipants, ageLimit, numOfScaryEnigmas);

		rooms.insert(room);

	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}

void Company::createKidsRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit)  {

	try {
		KidsRoom* room = new KidsRoom(name, escapeTime, level, maxParticipants, ageLimit);

		rooms.insert(room);

	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}

set<EscapeRoomWrapper*> Company::getAllRooms() const {
	return rooms;
}

void Company::removeRoom(const EscapeRoomWrapper& room) {
	for (std::set<EscapeRoomWrapper*>::iterator it=rooms.begin(); it!=rooms.end(); ++it) {
		if ( room.getName() == (*it)->getName()) {
			delete *it;
			rooms.erase( *it );
			return;
		}

	}
	throw CompanyRoomNotFoundException();

}


}
}

