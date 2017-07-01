/*
 * testScaryRoom.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: master
 */

#include "./../ScaryRoom.h"
#include "./../mtmtest.h"
#include "./../Exceptions.h"
#include <string>

using namespace mtm::escaperoom;


void testScaryRoomConstractor() {
	char *name1 = (char*)"room1";
	ASSERT_THROWS(EscapeRoomMemoryProblemException, ScaryRoom(NULL, 60, 5, 1, 1, 1));

	ASSERT_THROWS(EscapeRoomMemoryProblemException, ScaryRoom(name1, 29, 3, 5, 1, 1));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, ScaryRoom(name1, 91, 3, 5, 1, 1));
	ASSERT_NO_THROW(ScaryRoom(name1, 30, 3, 5, 1, 1));
	ASSERT_NO_THROW(ScaryRoom(name1, 90, 3, 5, 1, 1));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, ScaryRoom(name1, 60, 0, 5, 1, 1));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, ScaryRoom(name1, 60, 11, 5, 1, 1));
	ASSERT_NO_THROW(ScaryRoom(name1, 60, 1, 5, 1, 1));
	ASSERT_NO_THROW(ScaryRoom(name1, 60, 10, 5, 1, 1));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, ScaryRoom(name1, 60, 5, 0, 1, 1));
	ASSERT_NO_THROW(ScaryRoom(name1, 60, 5, 1, 1, 1));

	ASSERT_THROWS(ScaryRoomIllegalAgeLimit, ScaryRoom(name1, 60, 5, 1, -1, 1));
	ASSERT_THROWS(ScaryRoomException, ScaryRoom(name1, 60, 5, 1, 1, -1));


}

void testScaryRoomSetNewAgeLimit() {
	char *name1 = (char*)"room1";

	ScaryRoom scary_room1 = ScaryRoom(name1, 60, 5, 1, 1, 1);
	int ageLimit = scary_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 1);


	ASSERT_THROWS(ScaryRoomIllegalAgeLimit, scary_room1.setNewAgeLimit(-1));
	ageLimit = scary_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 1);

	ASSERT_NO_THROW(scary_room1.setNewAgeLimit(0));
	ageLimit = scary_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 0);

	ASSERT_NO_THROW(scary_room1.setNewAgeLimit(10));
	ageLimit = scary_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 10);

}

void testScaryRoomIncNumberOfScaryEnigmas() {
	char *name1 = (char*)"room1";

	ScaryRoom scary_room1 = ScaryRoom(name1, 60, 5, 1, 1, 1);
	ASSERT_NO_THROW(scary_room1.incNumberOfScaryEnigmas());
	//TODO have no way to test
}

void testScaryRoomGetAgeLimit() {
	char *name1 = (char*)"room1";

	ScaryRoom scary_room1 = ScaryRoom(name1, 60, 5, 1, 1, 1);
	ASSERT_THROWS(ScaryRoomIllegalAgeLimit, scary_room1.setNewAgeLimit(-1));

	ASSERT_NO_THROW(scary_room1.getAgeLimit());
	int ageLimit = scary_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 1);

	ASSERT_NO_THROW(scary_room1.setNewAgeLimit(10));
	ageLimit = scary_room1.getAgeLimit();
	ASSERT_EQUALS(ageLimit, 10);

}

void testScaryRoomPrint() {
	char *name1 = (char*)"room1";
	char *name2 = (char*)"room2";

	ScaryRoom scary_room1 = ScaryRoom(name1, 60, 5, 1, 3, 2);
	ScaryRoom scary_room2(name2, 65, 6, 2, 4, 3);

    std::ostringstream stream;
    stream << scary_room1;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "Scary Room: room1 (60/5/1/3)");

    stream.str("");
    stream << scary_room2;
    str =  stream.str();
    ASSERT_PRINT(str, "Scary Room: room2 (65/6/2/4)");

    scary_room2 = scary_room1;

    stream.str("");
    stream << scary_room2;
    str =  stream.str();
    ASSERT_PRINT(str, "Scary Room: room1 (60/5/1/3)");

    scary_room1.setNewAgeLimit(10);

    stream.str("");
    stream << scary_room2;
    str =  stream.str();
    ASSERT_PRINT(str, "Scary Room: room1 (60/5/1/3)");

    stream.str("");
    stream << scary_room1;
    str =  stream.str();
    ASSERT_PRINT(str, "Scary Room: room1 (60/5/1/10)");

}

void testScaryRoom() {
	RUN_TEST(testScaryRoomConstractor);
	RUN_TEST(testScaryRoomSetNewAgeLimit);
	RUN_TEST(testScaryRoomIncNumberOfScaryEnigmas);
	RUN_TEST(testScaryRoomGetAgeLimit);
	RUN_TEST(testScaryRoomPrint);

	std::cout << std::endl << "==========================" << std::endl << std::endl;
}

