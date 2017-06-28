/*
 * Company.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: master
 */

#include "Company.h"
#include <typeinfo>

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

void Company::createKidsRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit) {

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
		EscapeRoomWrapper* current_room = *it;
		if ( room == *current_room ) {
			delete *it;
			rooms.erase( *it );
			return;
		}
	}
	throw CompanyRoomNotFoundException();
}

void Company::addEnigma(const EscapeRoomWrapper& room, const Enigma& enigma) {
	for (std::set<EscapeRoomWrapper*>::iterator it=rooms.begin(); it!=rooms.end(); ++it) {
		EscapeRoomWrapper* current_room = *it;
		if ( room == *current_room ) {
			current_room->addEnigma(enigma);
			return;
		}
	}
	throw CompanyRoomNotFoundException();
}

void Company::removeEnigma(const EscapeRoomWrapper& room, const Enigma& enigma) {
	for (std::set<EscapeRoomWrapper*>::iterator it=rooms.begin(); it!=rooms.end(); ++it) {
		EscapeRoomWrapper* current_room = *it;
		if ( room == *current_room ) {
			try {
				current_room->removeEnigma(enigma);
			} catch ( EscapeRoomNoEnigmasException& e) {
				throw CompanyRoomHasNoEnigmasException();
			} catch ( EscapeRoomEnigmaNotFoundException& e) {
				throw CompanyRoomEnigmaNotFoundException();
			}
			return;
		}
	}
	throw CompanyRoomNotFoundException();
}

void Company::addItem(const EscapeRoomWrapper& room, const Enigma& enigma, const string& element) {
	for (std::set<EscapeRoomWrapper*>::iterator rooms_iterator=rooms.begin(); rooms_iterator!=rooms.end(); ++rooms_iterator) {
		EscapeRoomWrapper* current_room = *rooms_iterator;
		if ( room == *current_room ) {

			std::vector<Enigma*> enigmas = current_room->getAllEnigmas();
			for (std::vector<Enigma*>::iterator enigmas_iterator=enigmas.begin(); enigmas_iterator!=enigmas.end(); ++enigmas_iterator) {
				Enigma* current_enigma = *enigmas_iterator;
				if ( enigma == *current_enigma ) {

					current_enigma->addElement(element);
					return;

				}
			}
			throw CompanyRoomEnigmaNotFoundException();
		}
	}
	throw CompanyRoomNotFoundException();
}

void Company::removeItem(const EscapeRoomWrapper& room, const Enigma& enigma, const string& element) {
	for (std::set<EscapeRoomWrapper*>::iterator rooms_iterator=rooms.begin(); rooms_iterator!=rooms.end(); ++rooms_iterator) {
		EscapeRoomWrapper* current_room = *rooms_iterator;
		if ( room == *current_room ) {

			std::vector<Enigma*> enigmas = current_room->getAllEnigmas();
			for (std::vector<Enigma*>::iterator enigmas_iterator=enigmas.begin(); enigmas_iterator!=enigmas.end(); ++enigmas_iterator) {
				Enigma* current_enigma = *enigmas_iterator;
				if ( enigma == *current_enigma ) {
					try {
						current_enigma->removeElement(element);
					} catch ( EnigmaNoElementsException& e) {
						throw CompanyRoomEnigmaHasNoElementsException();
					} catch ( EnigmaElementNotFoundException& e) {
						throw CompanyRoomEnigmaElementNotFoundException();
					}
					return;

				}
			}
			throw CompanyRoomEnigmaNotFoundException();
		}
	}
	throw CompanyRoomNotFoundException();
}

set<EscapeRoomWrapper*> Company::getAllRoomsByType(RoomType type) const {
	std::cout << std::endl;
	set<EscapeRoomWrapper*> filtered_rooms;
	for (std::set<EscapeRoomWrapper*>::iterator it=rooms.begin(); it!=rooms.end(); ++it) {
		EscapeRoomWrapper* current_room = *it;
		if ( typeid(*current_room) == typeid(ScaryRoom) ) {
			std::cout << "ScaryRoom" << std::endl;
		}
	}

	return rooms;
}


}
}

