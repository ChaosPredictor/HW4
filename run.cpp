/*
 * run.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: master
 */

#include "./tests/testList.cpp"

#include "./tests/testEnigma.cpp"
#include "./tests/testEscapeRoomWrapper.cpp"
#include "./tests/testKidsRoom.cpp"
#include "./tests/testScaryRoom.cpp"

#include "./tests/testCompany.cpp"



int main() {
	testList();
	testIterator();

	testEnigma();
	testRoom();
	testKidsRoom();
	testScaryRoom();
	testCompany();
}
