/*
 * testKidsRoom.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: master
 */

#include "./../KidsRoom.h"
#include "./../mtmtest.h"
#include "./../Exceptions.h"
#include <string>

using namespace mtm::escaperoom;


void testKidsRoomConstractor() {
	char *name1 = (char*)"room1";
	ASSERT_THROWS(EscapeRoomMemoryProblemException, KidsRoom(NULL, 60, 5, 1,  1));

	ASSERT_THROWS(EscapeRoomMemoryProblemException, KidsRoom(name1, 29, 3, 5,  1));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, KidsRoom(name1, 91, 3, 5,  1));
	ASSERT_NO_THROW(KidsRoom(name1, 30, 3, 5, 1));
	ASSERT_NO_THROW(KidsRoom(name1, 90, 3, 5, 1));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, KidsRoom(name1, 60, 0, 5, 1));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, KidsRoom(name1, 60, 11, 5, 1));
	ASSERT_NO_THROW(KidsRoom(name1, 60, 1, 5, 1));
	ASSERT_NO_THROW(KidsRoom(name1, 60, 10, 5, 1));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, KidsRoom(name1, 60, 5, 0, 1));
	ASSERT_NO_THROW(KidsRoom(name1, 60, 5, 1, 1));

	ASSERT_THROWS(KidsRoomIllegalAgeLimit, KidsRoom(name1, 60, 5, 1, -1));

}

void testKidsRoomSetNewAgeLimit() {
	char *name1 = (char*)"room1";

	KidsRoom kids_room1 = KidsRoom(name1, 60, 5, 1, 1);
	int ageLimit = kids_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 1);


	ASSERT_THROWS(KidsRoomIllegalAgeLimit, kids_room1.setNewAgeLimit(-1));
	ageLimit = kids_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 1);

	ASSERT_NO_THROW(kids_room1.setNewAgeLimit(0));
	ageLimit = kids_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 0);

	ASSERT_NO_THROW(kids_room1.setNewAgeLimit(10));
	ageLimit = kids_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 10);

}

void testKidsRoomGetAgeLimit() {
	char *name1 = (char*)"room1";

	KidsRoom kids_room1 = KidsRoom(name1, 60, 5, 1, 1);
	ASSERT_THROWS(KidsRoomIllegalAgeLimit, kids_room1.setNewAgeLimit(-1));

	ASSERT_NO_THROW(kids_room1.getAgeLimit());
	int ageLimit = kids_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 1);

	ASSERT_NO_THROW(kids_room1.setNewAgeLimit(10));
	ageLimit = kids_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 10);

}

void testKidsRoomPrint() {
	char *name1 = (char*)"room1";
	char *name2 = (char*)"room2";

	KidsRoom kids_room1 = KidsRoom(name1, 60, 5, 1, 3);
	KidsRoom kids_room2(name2, 65, 6, 2, 4);

    std::ostringstream stream;
    stream << kids_room1;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "Kids Room: room1 (60/5/1/3)");

    stream.str("");
    stream << kids_room2;
    str =  stream.str();
    ASSERT_PRINT(str, "Kids Room: room2 (65/6/2/4)");

    kids_room2 = kids_room1;

    stream.str("");
    stream << kids_room2;
    str =  stream.str();
    ASSERT_PRINT(str, "Kids Room: room1 (60/5/1/3)");

    kids_room1.setNewAgeLimit(10);

    stream.str("");
    stream << kids_room2;
    str =  stream.str();
    ASSERT_PRINT(str, "Kids Room: room1 (60/5/1/3)");

    stream.str("");
    stream << kids_room1;
    str =  stream.str();
    ASSERT_PRINT(str, "Kids Room: room1 (60/5/1/10)");

}

void testKidsRoom() {
	RUN_TEST(testKidsRoomConstractor);
	RUN_TEST(testKidsRoomSetNewAgeLimit);
	RUN_TEST(testKidsRoomGetAgeLimit);
	RUN_TEST(testKidsRoomPrint);

	std::cout << std::endl << "==========================" << std::endl << std::endl;
}


