/*
 * testEscapeRoomWrapper.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: master
 */

#include "./../EscapeRoomWrapper.h"
#include "./../mtmtest.h"
#include "./../Exceptions.h"
#include <string>

using namespace mtm::escaperoom;


void testRoomConstractor() {
	char *name1 = (char*)"room1";

	//4 parameters constractor
	//name = null
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(NULL, 60, 5, 1));

	//escapeTime
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 29, 3, 5));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 91, 3, 5));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 30, 3, 5));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 90, 3, 5));

	//level
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 60, 0, 5));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 60, 11, 5));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 60, 1, 5));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 60, 10, 5));

	//maxParticipants
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 60, 5, 0));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 60, 5, 1));

	//2 parameters constractor
	//name null
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(NULL, 5));

	//level
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 0));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 11));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 1));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 10));

	EscapeRoomWrapper room(name1, 10);
	ASSERT_EQUALS(room.getAllEnigmas().size(), 0);
	EscapeRoomWrapper room2(name1, 60, 10, 5);
	ASSERT_EQUALS(room2.getAllEnigmas().size(), 0);
}

void testRoomCopy() {
	char *name1 = (char*)"room1";
	char *name3 = (char*)"room3";
	EscapeRoomWrapper room1(name1, 60, 3, 10);
	EscapeRoomWrapper room3(name3, 60, 3, 10);
    Enigma enigma1("enigma_name1", EASY_ENIGMA, 2);
    Enigma enigma2("enigma_name2", HARD_ENIGMA, 2);
    Enigma enigma3("enigma_name3", HARD_ENIGMA);

    room1.addEnigma(enigma1);
    room1.addEnigma(enigma2);

    EscapeRoomWrapper room2(room1);

	ASSERT_EQUALS(room2.getAllEnigmas().size(), 2);

    room1.removeEnigma(enigma1);
    room2.addEnigma(enigma3);

	ASSERT_EQUALS(room1.getAllEnigmas().size(), 1);
	ASSERT_EQUALS(room2.getAllEnigmas().size(), 3);

}

void testRoomAssigment() {
	char *name1 = (char*)"room1";
	char *name2 = (char*)"room2";

    Enigma enigma1("enigma_name1", EASY_ENIGMA, 2);
    Enigma enigma2("enigma_name2", HARD_ENIGMA, 2);
    Enigma enigma3("enigma_name3", HARD_ENIGMA, 2);
    Enigma enigma4("enigma_name4", MEDIUM_ENIGMA, 2);
    Enigma enigma5("enigma_name5", MEDIUM_ENIGMA);


    EscapeRoomWrapper room1(name1, 60, 3, 10);
    EscapeRoomWrapper room2(name2, 60, 3, 10);

    room1.addEnigma(enigma1);
    room1.addEnigma(enigma2);
    room1.addEnigma(enigma3);
    room2.addEnigma(enigma4);

    room2 = room1;

	ASSERT_EQUALS(room2.getAllEnigmas().size(), 3);

    room1.removeEnigma(enigma1);
    room2.addEnigma(enigma5);

	ASSERT_EQUALS(room1.getAllEnigmas().size(), 2);
	ASSERT_EQUALS(room2.getAllEnigmas().size(), 4);

}

void testRoomDestructor() {
	char *name1 = (char*)"room1";

    Enigma enigma1("enigma_name1", EASY_ENIGMA, 2);
    Enigma enigma2("enigma_name2", HARD_ENIGMA, 2);
    Enigma enigma3("enigma_name3", HARD_ENIGMA, 2);

    EscapeRoomWrapper room1(name1, 60, 3, 10);

    room1.addEnigma(enigma1);
    room1.addEnigma(enigma2);
    room1.addEnigma(enigma3);
    //TODO how to test?
}

void testRoomEqual() {
	char *name1 = (char*)"room1";
	char *name2 = (char*)"room2";
	EscapeRoomWrapper room1(name1, 60, 4, 10);
	EscapeRoomWrapper room3(name1, 30, 8, 10);
	EscapeRoomWrapper room4(name1, 30, 4, 5);
	EscapeRoomWrapper room5(name2, 60, 4, 10);
    Enigma enigma1("enigma_name1", EASY_ENIGMA, 2);
    Enigma enigma2("enigma_name2", HARD_ENIGMA, 2);
    room1.addEnigma(enigma1);
    room1.addEnigma(enigma2);

    EscapeRoomWrapper room2(room1);

    ASSERT_WITH_MESSAGE((room1==room2), "FAIL: operator==");

    room1.removeEnigma(enigma1);

    ASSERT_WITH_MESSAGE((room1==room2), "FAIL: operator==");

    ASSERT_WITH_MESSAGE((room1==room3), "FAIL: operator==");
    ASSERT_WITH_MESSAGE((room1==room4), "FAIL: operator==");

    ASSERT_WITH_MESSAGE(!(room1==room5), "FAIL: operator==");

}

void testRoomNotEqual() {
	char *name1 = (char*)"room1";
	char *name2 = (char*)"room2";
	EscapeRoomWrapper room1(name1, 30, 4, 10);
	EscapeRoomWrapper room3(name1, 60, 8, 10);
	EscapeRoomWrapper room4(name1, 60, 4, 5);
	EscapeRoomWrapper room5(name2, 60, 4, 10);
    Enigma enigma1("enigma_name1", EASY_ENIGMA, 2);
    Enigma enigma2("enigma_name2", HARD_ENIGMA, 2);
    room1.addEnigma(enigma1);
    room1.addEnigma(enigma2);

    EscapeRoomWrapper room2(room1);

    ASSERT_WITH_MESSAGE(!(room1!=room2), "FAIL: operator!=");

    room1.removeEnigma(enigma1);

    ASSERT_WITH_MESSAGE(!(room1!=room2), "FAIL: operator!=");

    ASSERT_WITH_MESSAGE((room1!=room3), "FAIL: operator!=");
    ASSERT_WITH_MESSAGE((room1!=room4), "FAIL: operator!=");

    ASSERT_WITH_MESSAGE((room1!=room5), "FAIL: operator!=");

}

void testRoomGreater() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);
	EscapeRoomWrapper room2(name1, 61, 4, 10);
	EscapeRoomWrapper room3(name1, 60, 5, 10);
	EscapeRoomWrapper room4(name1, 60, 4, 11);

    ASSERT_WITH_MESSAGE((room2>room1), "FAIL: operator>");
    ASSERT_WITH_MESSAGE((room3>room1), "FAIL: operator>");
    ASSERT_WITH_MESSAGE((room1>room4), "FAIL: operator>");
}

void testRoomLess() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);
	EscapeRoomWrapper room2(name1, 30, 4, 10);
	EscapeRoomWrapper room3(name1, 60, 3, 10);
	EscapeRoomWrapper room4(name1, 60, 4, 9);

    ASSERT_WITH_MESSAGE((room2<room1), "FAIL: operator<");
    ASSERT_WITH_MESSAGE((room3<room1), "FAIL: operator<");
    ASSERT_WITH_MESSAGE((room1<room4), "FAIL: operator<");
}

void testRoomPrint() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);

	std::ostringstream stream;
    stream << room1;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "room1 (60/4/10)");
}

void testRoomLevel() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);

	ASSERT_EQUALS(room1.level(), 4);
}

void testRoomRate() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);

	ASSERT_THROWS(EscapeRoomIllegalRateException, room1.rate(6));
	ASSERT_THROWS(EscapeRoomIllegalRateException, room1.rate(0));
	ASSERT_NO_THROW(room1.rate(1));
}

void testRoomGetName() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);

	ASSERT_EQUALS(room1.getName(), "room1");
}

void testRoomGetMaxTime() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);

	ASSERT_EQUALS(room1.getMaxTime(), 60);
}

void testRoomGetMaxParticipants() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);

	ASSERT_EQUALS(room1.getMaxParticipants(), 10);
}

void testRoomGetRate() {
	char *name1 = (char*)"room1";
	EscapeRoomWrapper room1(name1, 60, 4, 10);

	ASSERT_NO_THROW(room1.rate(1));
	ASSERT_NO_THROW(room1.rate(2));
	ASSERT_NO_THROW(room1.rate(3));
	ASSERT_NO_THROW(room1.rate(4));
	ASSERT_NO_THROW(room1.rate(5));

	ASSERT_EQUALS(room1.getRate(), 3);

	ASSERT_NO_THROW(room1.rate(5));
	ASSERT_NO_THROW(room1.rate(5));
	ASSERT_NO_THROW(room1.rate(5));
	ASSERT_NO_THROW(room1.rate(5));
	ASSERT_NO_THROW(room1.rate(5));

	ASSERT_EQUALS(room1.getRate(), 4);
}

void testRoomAddEnigma() {
	char *company_name1 = (char*)"company1";
	EscapeRoomWrapper room1 = EscapeRoomWrapper(company_name1, 3);
	char *enigma_name1 = (char*)"enigma1";
	char *enigma_name2 = (char*)"enigma2";

	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };
	Enigma enigma1 = Enigma(enigma_name1, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma2(enigma_name2, MEDIUM_ENIGMA);

	ASSERT_NO_THROW(room1.addEnigma(enigma1));

	std::vector<Enigma*> allEnigmas = room1.getAllEnigmas();
	ASSERT_EQUALS(allEnigmas.size(), 1);




}

void testRoomRemoveEnigma() {
	char *company_name1 = (char*)"company1";
	EscapeRoomWrapper room1 = EscapeRoomWrapper(company_name1, 3);

	char *enigma_name1 = (char*)"enigma1";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };
	Enigma enigma1 = Enigma(enigma_name1, MEDIUM_ENIGMA, 4, elements);

	char *enigma_name2 = (char*)"enigma2";
	std::set<string> elements2 { "John2", "Kelly2", "Amanda2" };
	Enigma enigma2 = Enigma(enigma_name2, EASY_ENIGMA, 3, elements2);

	ASSERT_THROWS(EscapeRoomNoEnigmasException, room1.removeEnigma(enigma1));

	room1.addEnigma(enigma1);

	ASSERT_THROWS(EscapeRoomEnigmaNotFoundException, room1.removeEnigma(enigma2));

	ASSERT_NO_THROW(room1.removeEnigma(enigma1));
	room1.addEnigma(enigma2);

	ASSERT_THROWS(EscapeRoomEnigmaNotFoundException, room1.removeEnigma(enigma1));

}

void testRoomGetHardestEnigma() {
	char *company_name1 = (char*)"company1";
	EscapeRoomWrapper room1 = EscapeRoomWrapper(company_name1, 3);

	char *enigma_name1 = (char*)"enigma1";
	char *enigma_name2 = (char*)"enigma2";
	char *enigma_name3 = (char*)"enigma3";
	char *enigma_name4 = (char*)"enigma4";

	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };
	Enigma enigma1 = Enigma(enigma_name1, MEDIUM_ENIGMA, 4, elements);

	std::set<string> elements2 { "John2", "Kelly2", "Amanda2" };
	Enigma enigma2 = Enigma(enigma_name2, EASY_ENIGMA, 3, elements2);

	Enigma enigma3 = Enigma(enigma_name3, MEDIUM_ENIGMA);
	Enigma enigma4 = Enigma(enigma_name4, HARD_ENIGMA);


	ASSERT_THROWS(EscapeRoomNoEnigmasException, room1.getHardestEnigma());

	room1.addEnigma(enigma1);
	room1.addEnigma(enigma2);
	room1.addEnigma(enigma3);

	ASSERT_NO_THROW(room1.getHardestEnigma());

	Enigma result_enigma = room1.getHardestEnigma();
	ASSERT_EQUALS(result_enigma, enigma1);

	room1.addEnigma(enigma4);

	result_enigma = room1.getHardestEnigma();
	ASSERT_EQUALS(result_enigma, enigma4);
}

void testRoomGetAllEnigmas() {
	char *company_name1 = (char*)"company1";
	EscapeRoomWrapper room1 = EscapeRoomWrapper(company_name1, 3);

	char *enigma_name1 = (char*)"enigma1";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };
	Enigma enigma1 = Enigma(enigma_name1, MEDIUM_ENIGMA, 4, elements);

	char *enigma_name2 = (char*)"enigma2";
	std::set<string> elements2 { "John2", "Kelly2", "Amanda2" };
	Enigma enigma2 = Enigma(enigma_name2, EASY_ENIGMA, 3, elements2);

	char *enigma_name3 = (char*)"enigma3";
	std::set<string> elements3 { "John3", "Kelly3", "Amanda3" };
	Enigma enigma3 = Enigma(enigma_name3, MEDIUM_ENIGMA, 3, elements3);

	char *enigma_name4 = (char*)"enigma4";
	std::set<string> elements4 { "John4", "Kelly4", "Amanda4" };
	Enigma enigma4 = Enigma(enigma_name4, HARD_ENIGMA, 3, elements4);

	ASSERT_NO_THROW(room1.getAllEnigmas());

	std::vector<Enigma*> allEnigmas = room1.getAllEnigmas();

	ASSERT_EQUALS(allEnigmas.size(), 0);

	room1.addEnigma(enigma1);
	room1.addEnigma(enigma2);
	room1.addEnigma(enigma3);

	ASSERT_NO_THROW(room1.getAllEnigmas());

	allEnigmas = room1.getAllEnigmas();
	ASSERT_EQUALS(allEnigmas.size(), 3);

	room1.addEnigma(enigma4);

	allEnigmas = room1.getAllEnigmas();
	ASSERT_EQUALS(allEnigmas.size(), 4);

}

void testRoom() {
	RUN_TEST(testRoomConstractor);
	RUN_TEST(testRoomCopy);
	RUN_TEST(testRoomDestructor);
	RUN_TEST(testRoomAssigment);
	RUN_TEST(testRoomEqual);
	RUN_TEST(testRoomNotEqual);
	RUN_TEST(testRoomGreater);
	RUN_TEST(testRoomLess);
	RUN_TEST(testRoomPrint);
	RUN_TEST(testRoomLevel);
	RUN_TEST(testRoomRate);
	RUN_TEST(testRoomGetName);
	RUN_TEST(testRoomGetMaxTime);
	RUN_TEST(testRoomGetMaxParticipants);
	RUN_TEST(testRoomGetRate);
	RUN_TEST(testRoomAddEnigma);
	RUN_TEST(testRoomRemoveEnigma);
	RUN_TEST(testRoomGetHardestEnigma);
	RUN_TEST(testRoomGetAllEnigmas);

	std::cout << std::endl << "==========================" << std::endl << std::endl;
}
