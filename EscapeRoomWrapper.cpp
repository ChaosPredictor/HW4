/*
 * EscapeRoomWrapper.cpp
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */


//TODO remove it
#include <stdio.h>
#include "EscapeRoomWrapper.h"

#define DEFAULT_MAX_TIME 60
#define DEFAULT_MAX_PARTICIPANTS 6

namespace mtm{
namespace escaperoom {

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& level) : enigmas() {
	if( name == NULL || level < 1 || level > 10 ) throw EscapeRoomMemoryProblemException();

	room = escapeRoomCreate(name, DEFAULT_MAX_TIME, DEFAULT_MAX_PARTICIPANTS, level);
	if(room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}
	//TODO is it possible w/o code duplication
}

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& escapeTime, const int& level, const int& maxParticipants) : enigmas() {
	if( name == NULL || escapeTime < 30 || escapeTime > 90 || level < 1 || level > 10 || maxParticipants < 1 ) throw EscapeRoomMemoryProblemException();
	room = escapeRoomCreate(name, escapeTime, maxParticipants, level);
	if(room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}

}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper& room_to_copy) {
	if( &room_to_copy == nullptr ) throw EscapeRoomMemoryProblemException();
	//TODO maybe w/o it
	room = escapeRoomCopy(room_to_copy.room);
	if( room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}
	//std::cout << std::endl;
	//std::cout << "copy" << std::endl;
	//std::cout << std::endl;

	std::vector<Enigma*> enigmas_to_copy = room_to_copy.enigmas;
	for (std::vector<Enigma*>::iterator it=enigmas_to_copy.begin(); it!=enigmas_to_copy.end(); ++it) {
		Enigma* current_enigma = new Enigma(**it);
		enigmas.push_back(current_enigma);
	}
}

EscapeRoomWrapper& EscapeRoomWrapper::operator=(const EscapeRoomWrapper& room_to_copy){
	if( this == &room_to_copy) {
		return *this;
	}
	for (std::vector<Enigma*>::iterator it=enigmas.begin(); it!=enigmas.end(); ++it) {
		delete *it;
	}
	enigmas.clear();
	escapeRoomDestroy(this->room);

	this->room = escapeRoomCopy(room_to_copy.room);
	if(this->room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}
	//std::cout << std::endl;
	//std::cout << "=" << std::endl;
	//std::cout << std::endl;

	std::vector<Enigma*> enigmas_to_copy = room_to_copy.enigmas;
	for (std::vector<Enigma*>::iterator it=enigmas_to_copy.begin(); it!=enigmas_to_copy.end(); ++it) {
		Enigma* current_enigma = new Enigma(**it);
		enigmas.push_back(current_enigma);
	}
	return *this;
	//TODO is it possible w/o code duplication
}

EscapeRoomWrapper::~EscapeRoomWrapper() {
	for (std::vector<Enigma*>::iterator it=enigmas.begin(); it!=enigmas.end(); ++it) {
		delete *it;
	}
	escapeRoomDestroy(room);
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper& room_to_compare) const {
	return areEqualRooms(this->room, room_to_compare.room);
}

bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper& room_to_compare) const {
	return !(*this == room_to_compare);
}

bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper& room) const {
	return isBiggerRoom(this->room, room.room);
}

bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper& room) const {
	return (room > *this);
}

int EscapeRoomWrapper::level() const {
	return getLevel(this->room);
}

void EscapeRoomWrapper::rate(const int& newRate) const {
	if (updateRate(this->room, newRate) != ESCAPEROOM_SUCCESS) {
		throw EscapeRoomIllegalRateException();
	}
}

std::string EscapeRoomWrapper::getName() const {
	char* char_name = roomGetName(this->room);
	std::string name = char_name;
	free(char_name);
	//TODO find better solution
	return name;
}

double EscapeRoomWrapper::getRate() const {
	return roomGetRate(this->room);
}

int EscapeRoomWrapper::getMaxTime() const {
	return roomGetMaxTime(this->room);
}

int EscapeRoomWrapper::getMaxParticipants() const {
	return roomGetMaxParticipants(this->room);
}

void EscapeRoomWrapper::addEnigma(const Enigma& enigma) {
	Enigma* new_enigma = new Enigma(enigma);
	//Enigma* new_enigma(&enigma);
	enigmas.push_back(new_enigma);
}

void EscapeRoomWrapper::removeEnigma(const Enigma& enigma) {
	if (enigmas.empty() ) throw EscapeRoomNoEnigmasException();
	for (std::vector<Enigma*>::iterator it=enigmas.begin(); it!=enigmas.end(); ++it) {
		Enigma* current_enigma = *it;
		if ( enigma == *current_enigma ) {
			delete *it;
			enigmas.erase( it );
			return;
		}
	}
	throw EscapeRoomEnigmaNotFoundException();



	/*

	if (enigmas.empty() ) throw EscapeRoomNoEnigmasException();
	int i = 0;
	for(auto const& value: enigmas) {
		if ( value == *enigma) {
			enigmas.erase(enigmas.begin() + i);
			return;
		}
		i++;
	}
	throw EscapeRoomEnigmaNotFoundException();*/
}

Enigma EscapeRoomWrapper::getHardestEnigma() {
	//TODO test
	if ( enigmas.empty() ) throw EscapeRoomNoEnigmasException();
	//TODO pointer
	Enigma hardest_enigma = Enigma(*enigmas.front());
	for (std::vector<Enigma*>::iterator it=enigmas.begin(); it!=enigmas.end(); ++it) {
		Enigma* current_enigma = *it;
		if ( hardest_enigma.getDifficulty() < current_enigma->getDifficulty()) {
			hardest_enigma = *current_enigma;
		}

		/*
		if ( enigma == *current_enigma ) {
			delete *it;
			enigmas.erase( it );
			return;
		}*/
	}


/*
	if (enigmas.size() == 0 ) throw EscapeRoomNoEnigmasException();
	Enigma hardestEnigma = enigmas[0];
	for(auto const& value: enigmas) {
		if ( hardestEnigma.getDifficulty() < value.getDifficulty()) {
			hardestEnigma = value;
		}
	}*/
	return hardest_enigma;
}

std::vector<Enigma*> EscapeRoomWrapper::getAllEnigmas() {
	return enigmas;
}

int EscapeRoomWrapper::getRoomLevel() const {
	return getLevel(this->room);
}

void EscapeRoomWrapper::print(std::ostream& output) const{
	output << getName();
	output << " (";
	output << getMaxTime();
	output << "/";
	output << getRoomLevel();
	output << "/";
	output << getMaxParticipants();
	output << ")";
	return;
}

std::ostream& operator<<(std::ostream& output, const EscapeRoomWrapper& room) {
    room.print(output);
    return output;
}




}
}
