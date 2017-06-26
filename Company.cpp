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

void Company::createRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants) {
	try {
		EscapeRoomWrapper room = EscapeRoomWrapper(name, escapeTime, level, maxParticipants);

		rooms.insert(&room);

	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}

void Company::createScaryRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas) {

	try {
		ScaryRoom room = ScaryRoom(name, escapeTime, level, maxParticipants, ageLimit, numOfScaryEnigmas);

		rooms.insert(&room);

	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}

void Company::createKidsRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit)  {

	try {
		KidsRoom room = KidsRoom(name, escapeTime, level, maxParticipants, ageLimit);

		rooms.insert(&room);

	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}





Company::~Company() {}


}
}

