/*
 * EscapeRoomWrapper.cpp
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */


//TODO remove it
#include <stdio.h>
#include "EscapeRoomWrapper.h"

namespace mtm{



namespace escaperoom {

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& escapeTime, const int& level, const int& maxParticipants) {
	room = escapeRoomCreate(name, escapeTime, maxParticipants, level);
	if(room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}

}

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& level) {
	room = escapeRoomCreate(name, 60, 6, level);
	if(room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}
	//TODO is it possible w/o code duplication
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper& room) {
	this->room = escapeRoomCopy(room.room);
	if(this->room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}
}

EscapeRoomWrapper& EscapeRoomWrapper::operator=(const EscapeRoomWrapper& room) {
	if( this == &room) {
		return *this;
	}
	escapeRoomDestroy(this->room);
	this->room = escapeRoomCopy(room.room);
	if(this->room == NULL) {
		throw EscapeRoomMemoryProblemException();
	}
	return *this;
	//TODO is it possible w/o code duplication
}

EscapeRoomWrapper::~EscapeRoomWrapper() {
	escapeRoomDestroy(room);
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper& room) const {
	return areEqualRooms(this->room, room.room);
}

bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper& room) const {
	return !(this->room==room.room);
}

bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper& room) const {
	return isBiggerRoom(this->room, room.room);
}

bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper& room) const {
	return (room.room < this->room);
}

int EscapeRoomWrapper::level() const {
	return getLevel(this->room);
}

void EscapeRoomWrapper::rate(const int& newRate) const {
	if (updateRate(this->room, newRate) != ESCAPEROOM_SUCCESS) {
		throw EscapeRoomIllegalRateException();
	}
}

std::ostream& operator<<(std::ostream& output, const EscapeRoomWrapper& room) {
	char* name = roomGetName(room.room);
	output << name;
	output << " (";
	output << roomGetMaxTime(room.room);
	output << "/";
	output << getLevel(room.room);
	output << "/";
	output << roomGetMaxParticipants(room.room);
	output << ")";
	free(name);
	return output;
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

}
}
