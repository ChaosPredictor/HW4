#include "EscapeRoomWrapper.h"
#include "ScaryRoom.h"
#include "KidsRoom.h"
#include "Company.h"
#include "mtmtest.h"
#include <assert.h>
#include "Exceptions.h"
#include <string>
#include "list_example.h"

//TODO remove
#include <iostream>

using namespace mtm::escaperoom;


void testRoomConstractor() {
	char *name1 = (char*)"company1";
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(NULL, 60, 5, 1));

	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 29, 3, 5));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 91, 3, 5));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 30, 3, 5));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 90, 3, 5));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 60, 0, 5));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 60, 11, 5));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 60, 1, 5));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 60, 10, 5));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 60, 5, 0));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 60, 5, 1));

	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(NULL, 5));

	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 0));
	ASSERT_THROWS(EscapeRoomMemoryProblemException, EscapeRoomWrapper(name1, 11));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 1));
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 10));
}

void testRoomCopy() {
	char *name2 = (char*)"company2";
    EscapeRoomWrapper room2 = EscapeRoomWrapper(name2, 60, 3, 10);
    ASSERT_NO_THROW(EscapeRoomWrapper(room2));
    EscapeRoomWrapper room3 = EscapeRoomWrapper(room2);
    ASSERT_WITH_MESSAGE((room2==room3), "FAIL: room.copy");
}

void testRoomAddEnigma() {
	char *company_name1 = (char*)"company1";
	EscapeRoomWrapper room1 = EscapeRoomWrapper(company_name1, 3);
	char *enigma_name1 = (char*)"enigma1";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };
	Enigma enigma1 = Enigma(enigma_name1, MEDIUM_ENIGMA, 4, elements);

	ASSERT_NO_THROW(room1.addEnigma(enigma1));

}

void testRoom() {
	RUN_TEST(testRoomConstractor);
	RUN_TEST(testRoomCopy);
	RUN_TEST(testRoomAddEnigma);

	char *name1 = (char*)"company1";
	char *name2 = (char*)"company2";
    EscapeRoomWrapper room1 = EscapeRoomWrapper(name1, 3);
	ASSERT_NO_THROW(EscapeRoomWrapper(name1, 30, 3, 5));
    EscapeRoomWrapper room2 = EscapeRoomWrapper(name2, 60, 3, 10);
    EscapeRoomWrapper room3 = EscapeRoomWrapper(name2, 30, 3, 5);
    EscapeRoomWrapper room4 = EscapeRoomWrapper(name2, 30, 2, 5);

    ASSERT_NO_THROW(EscapeRoomWrapper(name2, 3));
    ASSERT_NO_THROW(EscapeRoomWrapper(room2));
    ASSERT_WITH_MESSAGE(!(room1==room2), "FAIL: operator==");
    ASSERT_WITH_MESSAGE((room2==room3), "FAIL: operator==");
    ASSERT_WITH_MESSAGE((room1!=room2), "FAIL: operator!=");
    ASSERT_WITH_MESSAGE((room4<room2), "FAIL: operator<");
    ASSERT_WITH_MESSAGE(!(room4>room3), "FAIL: operator>");
    ASSERT_WITH_MESSAGE(room1.level() == 3, "FAIL: level()");
    ASSERT_NO_THROW(room1.rate(1));
    ASSERT_THROWS(EscapeRoomIllegalRateException, room1.rate(6));
    std::ostringstream stream;
    stream << room1;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "company1 (60/3/6)");
    string name = room1.getName();
    ASSERT_WITH_MESSAGE(name.compare("company1\n"), "FAIL: getName");
    ASSERT_WITH_MESSAGE(room1.getRate() == 1, "FAIL: getRate");
    ASSERT_WITH_MESSAGE(room1.getMaxTime() == 60, "FAIL: getMaxTime");
    ASSERT_WITH_MESSAGE(room1.getMaxParticipants() == 6, "FAIL: getMaxParticipants");
}


void testEnigma1() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";

    Enigma enigma1 = Enigma(name1, MEDIUM_ENIGMA, 3);
    Enigma enigma2 = Enigma(name2, MEDIUM_ENIGMA, 3);
    Enigma enigma3 = Enigma(name2, HARD_ENIGMA, 3);
    Enigma enigma4 = Enigma(name2, MEDIUM_ENIGMA, 2);
    ASSERT_WITH_MESSAGE(!(enigma1==enigma2), "FAIL: enigma.operator==");
    ASSERT_WITH_MESSAGE(enigma2==enigma4, "FAIL: enigma.operator==");
    ASSERT_WITH_MESSAGE(enigma1!=enigma2, "FAIL: enigma.operator!=");
    ASSERT_WITH_MESSAGE(enigma2!=enigma3, "FAIL: enigma.operator!=");
    ASSERT_WITH_MESSAGE(!(enigma1==enigma2), "FAIL: enigma.operator==");
    ASSERT_WITH_MESSAGE(!(enigma1>enigma3), "FAIL: enigma.operator>");
    ASSERT_WITH_MESSAGE(enigma1<enigma3, "FAIL: enigma.operator<");
    ASSERT_WITH_MESSAGE(!(enigma1.areEqualyComplex(enigma3)), "FAIL: enigma.areEqualyComplex");
    ASSERT_WITH_MESSAGE(enigma1.areEqualyComplex(enigma2), "FAIL: enigma.areEqualyComplex");
    ASSERT_WITH_MESSAGE(enigma1.getDifficulty() == MEDIUM_ENIGMA, "FAIL: enigma.getName");
    ASSERT_WITH_MESSAGE(enigma1.getName() == "enigma1", "FAIL: enigma.getName");
    std::ostringstream stream;
    stream << enigma1;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "enigma1 (1) 3");

}


void testEnigmaConstractor() {
	char *name1 = (char*)"enigma1";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };

	//2 parameters
	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA));

	//3 parameters
	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA, 4));
	//4 parameters
	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA, 4, elements));
	ASSERT_THROWS(EnigmaIllegalSizeParamException, Enigma(name1, MEDIUM_ENIGMA, 3, elements));

	Enigma enigma1 = Enigma(name1, MEDIUM_ENIGMA, 4, elements);

}

void testEnigmaAddElement() {
	char *name1 = (char*)"enigma1";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };

	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA, 4, elements));
	ASSERT_THROWS(EnigmaIllegalSizeParamException, Enigma(name1, MEDIUM_ENIGMA, 3, elements));

	Enigma enigma1 = Enigma(name1, MEDIUM_ENIGMA, 4, elements);
	ASSERT_NO_THROW(enigma1.addElement("newElement"));

    std::ostringstream stream;
    stream << enigma1;
    std::string str1 = stream.str();
    ASSERT_PRINT(str1, "enigma1 (1) 5");

	ASSERT_NO_THROW(enigma1.removeElement("John"));

    std::ostringstream stream2;
    stream2 << enigma1;
    std::string str2 = stream2.str();
    ASSERT_PRINT(str2, "enigma1 (1) 4");
}


void testEnigma() {
	RUN_TEST(testEnigma1);
	RUN_TEST(testEnigmaConstractor);
	RUN_TEST(testEnigmaAddElement);



}


/*
void test1() {

    ASSERT_NO_THROW(Company("c1","1234"));
    ASSERT_NO_THROW(Company("c2","0541234567"));
}

void test2() {
    Company company("c1","1234");
    ASSERT_NO_THROW(company.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(company.createRoom((char *) "r2", 60, 3, 4));
    ASSERT_NO_THROW(company.createRoom((char *) "r3", 60, 5, 6));
    ASSERT_NO_THROW(company.createKidsRoom((char *) "r4", 60, 2, 2,7));
    ASSERT_NO_THROW(company.createScaryRoom((char *) "r5", 60, 2, 2,11,20));
    ASSERT_NO_THROW(company.removeRoom(EscapeRoomWrapper((char*)"r1",60,2,2)));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeRoom(EscapeRoomWrapper((char*)"r1",60,2,2)));
    ASSERT_NO_THROW(company.removeRoom(ScaryRoom((char*)"r5",60,2,2,11,20)));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeRoom(ScaryRoom((char*)"r5",60,2,2,11,20)));

}

void test3() {
    Company company("c1","1234");
    company.createRoom((char *) "r1", 60, 2, 2);
    company.createRoom((char *) "r2", 60, 3, 4);
    EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room2((char *) "r2", 60, 2, 2);
    Enigma enigma1("e1",EASY_ENIGMA);
    Enigma enigma2("e2",HARD_ENIGMA);

    ASSERT_THROWS(CompanyRoomNotFoundException , company.addEnigma(room2, enigma2));
    ASSERT_NO_THROW(company.addEnigma(room1, enigma1));
    ASSERT_NO_THROW(company.addEnigma(room1, enigma2));
    ASSERT_NO_THROW(company.removeEnigma(room1,enigma1));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException , company.removeEnigma(room1,enigma1));
    ASSERT_NO_THROW(company.removeEnigma(room1,enigma2));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException , company.removeEnigma(room1,enigma2));
}

void test4() {
    Company company("c1","1234");
    company.createRoom((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room2((char *) "r2", 60, 2, 2);
    Enigma enigma1("e1",EASY_ENIGMA);
    Enigma enigma2("e2",HARD_ENIGMA);

    company.addEnigma(room1,enigma1);
    ASSERT_NO_THROW(company.addItem(room1,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException ,company.addItem(room1,enigma2,"x"));
    ASSERT_THROWS(CompanyRoomNotFoundException ,company.addItem(room2,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomNotFoundException, company.removeItem(room2,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException , company.removeItem(room1,enigma2,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException , company.removeItem(room1,enigma1,"y"));
    ASSERT_NO_THROW(company.removeItem(room1,enigma1,"x"));

    company.addEnigma(room1,enigma2);
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException , company.removeItem(room1,enigma2,"x"));

}
*/

int main() {
	testRoom();
	testEnigma();

	main2();

	//RUN_TEST(test1);
    //RUN_TEST(test2);
    //RUN_TEST(test3);
    //RUN_TEST(test4);
}
