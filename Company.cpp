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
	EscapeRoomWrapper room2 = room;
/*	unsigned size = rooms.size();
	//std::set<EscapeRoomWrapper*>::iterator it = rooms.find(&room2);
	//if ( it == nullptr ) throw CompanyRoomNotFoundException();
	rooms.erase( rooms.find(&room2) );
	if ( rooms.size() == size ) throw CompanyRoomNotFoundException();*/

	//EscapeRoomWrapper* room3 = *(rooms.begin());
	//std::cout << room3->getName() << std::endl;

	std::cout << std::endl;

	for (std::set<EscapeRoomWrapper*>::iterator it=rooms.begin(); it!=rooms.end(); ++it) {
		EscapeRoomWrapper* room3 = *it;
		std::cout << room3->getName();
		if ( room.getName() == room3->getName()) {
			std::cout << "yes";
		}
		std::cout << std::endl;

	}

	/*
	unsigned size = rooms.size();
	for (std::set<EscapeRoomWrapper*>::iterator it=rooms.begin(); it!=rooms.end(); ++it) {
		EscapeRoomWrapper room3 = *it;
		std::cout << *it << std::endl;
		std::cout << &room << std::endl;
		if ( room2.getName() == room3.getName() ) {
			rooms.erase(*it);
			printf("yes\n");
			return;
		} else {
			printf("no\n");
		}
	}
	if ( rooms.size() == size ) throw CompanyRoomNotFoundException();*/
}


}
}

