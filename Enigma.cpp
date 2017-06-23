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
	numOfElements(numOfElements)
{}


}
}


