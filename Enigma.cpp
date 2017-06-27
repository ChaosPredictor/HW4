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
		//TODO what to do in case of numOfelements < 0?
	name(name),
	difficulty(difficulty),
	numOfElements(numOfElements) {}

Enigma::Enigma(const std::string& name, const Difficulty& difficulty, const int& numOfElements, set<string> elements) :
	name(name),
	difficulty(difficulty),
	numOfElements(numOfElements) {
	if ( (unsigned)numOfElements != elements.size() ) throw EnigmaIllegalSizeParamException();
	for (set<string>::iterator it = elements.begin(); it != elements.end(); it++) {
		//string* element = *it;
		this->elements.insert(*it);
	}

}


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
	output << ") ";
	output << enigma.numOfElements;
	return output;
}


void Enigma::addElement(string element) {
	//std::cout << "added" << std::endl;
	this->elements.insert(element);
	//std::cout << "added " << this->elements.size() << std::endl;

	numOfElements++;
}

//void removeElement(const string& element);

void Enigma::removeElement(const string& element) {
	//std::cout << "remove " << this->elements.size() << std::endl;

	if ( this->elements.empty() ) throw EnigmaNoElementsException();
	if ( this->elements.erase(element) < 1 ) throw EnigmaElementNotFoundException();
	numOfElements--;
}

}
}


