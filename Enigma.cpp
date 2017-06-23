/*
 * Enigma.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: master
 */


#include "Enigma.h"


namespace mtm{
namespace escaperoom{


Enigma::Enigma(const std::string& name, const Difficulty& difficulty, const int& numOfElements):
	name(name),
	difficulty(difficulty),
	numOfElements(numOfElements) {}


bool Enigma::operator==(const Enigma& enigma) const {
	return (this->name.compare(enigma.name) == 0) && this->difficulty == enigma.difficulty;
}

bool Enigma::operator!=(const Enigma& enigma) const {
	return !(*this == enigma);
}

bool Enigma::operator<(const Enigma& enigma) const {
	if (*this==enigma) return false;
	return this->difficulty < enigma.difficulty;
}

bool Enigma::operator>(const Enigma& enigma) const {
	return enigma.difficulty < this->difficulty;
}
//TODO different names same difficulty

bool Enigma::areEqualyComplex(const Enigma& enigma) const {
	return (this->numOfElements == enigma.numOfElements) && this->difficulty == enigma.difficulty;

}

Difficulty Enigma::getDifficulty() const {
	return this->difficulty;
}

string Enigma::getName() const {
	return this->name;
}




std::ostream& operator<<(std::ostream& output, const Enigma& enigma) {
	string name = enigma.getName();
	output << name;
	output << " (";
	output << enigma.getDifficulty();
	output << ")";
	return output;
}

}
}


