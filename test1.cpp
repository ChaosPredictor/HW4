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

void printBuffer() {
	std::cout << std::endl << "==========================" << std::endl << std::endl;
}


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

	printBuffer();
}



void testEnigmaConstractor() {
	char *name1 = (char*)"enigma1";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };
	std::set<string> elements0 {};

	//2 parameters
	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA));

	//3 parameters
	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA, 4));
	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA, 0));
	ASSERT_THROWS(EnigmaIllegalSizeParamException, Enigma(name1, MEDIUM_ENIGMA, -1));



	//4 parameters
	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA, 4, elements));
	ASSERT_NO_THROW(Enigma(name1, MEDIUM_ENIGMA, 0, elements0));
	ASSERT_THROWS(EnigmaIllegalSizeParamException, Enigma(name1, MEDIUM_ENIGMA, 3, elements));

}

void testEnigmaCopy() {
	char *name1 = (char*)"enigma1";
	char *name3 = (char*)"enigma3";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };

	Enigma enigma1(name1, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma3(name3, MEDIUM_ENIGMA, 4, elements);

	Enigma enigma2 (enigma1);
    ASSERT_WITH_MESSAGE(enigma1.areEqualyComplex(enigma2), "FAIL: Enigma copy");

    ASSERT_WITH_MESSAGE(enigma3.areEqualyComplex(enigma2), "FAIL: Enigma copy");

	ASSERT_NO_THROW(enigma2.removeElement("John"));
    ASSERT_WITH_MESSAGE(!(enigma1.areEqualyComplex(enigma2)), "FAIL: Enigma copy");

	ASSERT_NO_THROW(enigma2.removeElement("Kelly"));
	ASSERT_NO_THROW(enigma2.removeElement("Amanda"));
	ASSERT_NO_THROW(enigma2.removeElement("Kim"));
}

void testEnigmaAssigment() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	char *name3 = (char*)"enigma3";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };

	Enigma enigma1(name1, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma3(name3, MEDIUM_ENIGMA, 4, elements);

	Enigma enigma2(name2, HARD_ENIGMA);

    ASSERT_WITH_MESSAGE(!(enigma1.areEqualyComplex(enigma2)), "FAIL: Enigma assigment");

	enigma2 = enigma1;

    ASSERT_WITH_MESSAGE(enigma1.areEqualyComplex(enigma2), "FAIL: Enigma assigment");

    ASSERT_WITH_MESSAGE(enigma3.areEqualyComplex(enigma2), "FAIL: Enigma assigment");

	ASSERT_NO_THROW(enigma2.removeElement("John"));
    ASSERT_WITH_MESSAGE(!(enigma1.areEqualyComplex(enigma2)), "FAIL: Enigma assigment");

	ASSERT_NO_THROW(enigma2.removeElement("Kelly"));
	ASSERT_NO_THROW(enigma2.removeElement("Amanda"));
	ASSERT_NO_THROW(enigma2.removeElement("Kim"));
}

void testEnigmaEqual() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };

	Enigma enigma1(name1, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma2(name1, HARD_ENIGMA, 4, elements);
	Enigma enigma3(name2, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma4(name1, MEDIUM_ENIGMA);

    ASSERT_WITH_MESSAGE((enigma1 == enigma4), "FAIL: Enigma equal");
    ASSERT_WITH_MESSAGE(!(enigma1 == enigma2), "FAIL: Enigma equal");
    ASSERT_WITH_MESSAGE(!(enigma1 == enigma3), "FAIL: Enigma equal");

}

void testEnigmaNotEqual() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };

	Enigma enigma1(name1, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma2(name1, HARD_ENIGMA, 4, elements);
	Enigma enigma3(name2, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma4(name1, MEDIUM_ENIGMA);

    ASSERT_WITH_MESSAGE(!(enigma1 != enigma4), "FAIL: Enigma equal");
    ASSERT_WITH_MESSAGE((enigma1 != enigma2), "FAIL: Enigma equal");
    ASSERT_WITH_MESSAGE((enigma1 != enigma3), "FAIL: Enigma equal");

}

void testEnigmaGreater() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };

	Enigma enigma1(name1, HARD_ENIGMA, 4, elements);
	Enigma enigma2(name1, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma3(name1, EASY_ENIGMA, 4, elements);
	Enigma enigma4(name1, MEDIUM_ENIGMA);
	Enigma enigma5(name2, MEDIUM_ENIGMA);

    ASSERT_WITH_MESSAGE((enigma1 > enigma2), "FAIL: Enigma greater");
    ASSERT_WITH_MESSAGE((enigma2 > enigma3), "FAIL: Enigma greater");
    ASSERT_WITH_MESSAGE((enigma1 > enigma3), "FAIL: Enigma greater");
    ASSERT_WITH_MESSAGE((enigma4 > enigma3), "FAIL: Enigma greater");
    ASSERT_WITH_MESSAGE(!(enigma4 > enigma5), "FAIL: Enigma greater");
    ASSERT_WITH_MESSAGE(!(enigma5 > enigma4), "FAIL: Enigma greater");
    ASSERT_WITH_MESSAGE(!(enigma4 > enigma2), "FAIL: Enigma greater");

}

void testEnigmaLess() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	std::set<string> elements { "John", "Kelly", "Amanda", "Kim" };

	Enigma enigma1(name1, HARD_ENIGMA, 4, elements);
	Enigma enigma2(name1, MEDIUM_ENIGMA, 4, elements);
	Enigma enigma3(name1, EASY_ENIGMA, 4, elements);
	Enigma enigma4(name1, MEDIUM_ENIGMA);
	Enigma enigma5(name2, MEDIUM_ENIGMA);

    ASSERT_WITH_MESSAGE((enigma2 < enigma1), "FAIL: Enigma less");
    ASSERT_WITH_MESSAGE((enigma3 < enigma2), "FAIL: Enigma less");
    ASSERT_WITH_MESSAGE((enigma3 < enigma1), "FAIL: Enigma less");
    ASSERT_WITH_MESSAGE((enigma3 < enigma4), "FAIL: Enigma less");
    ASSERT_WITH_MESSAGE(!(enigma4 > enigma5), "FAIL: Enigma less");
    ASSERT_WITH_MESSAGE(!(enigma5 > enigma4), "FAIL: Enigma less");
    ASSERT_WITH_MESSAGE(!(enigma4 > enigma2), "FAIL: Enigma less");

}

void testEnigmaAreEqualyComplex() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	std::set<string> elements1 { "John1", "Kelly1", "Amanda1", "Kim1" };
	std::set<string> elements2 { "John2", "Kelly2", "Amanda2", "Kim2" };
	std::set<string> elements3 { "John3", "Kelly3", "Amanda3" };

	Enigma enigma1(name1, MEDIUM_ENIGMA, 4, elements1);
	Enigma enigma2(name2, MEDIUM_ENIGMA, 4, elements2);
	Enigma enigma3(name1, MEDIUM_ENIGMA, 3, elements3);
	Enigma enigma4(name1, HARD_ENIGMA, 4, elements1);

    ASSERT_WITH_MESSAGE(enigma1.areEqualyComplex(enigma2), "FAIL: Enigma areEqualComplex");
    ASSERT_WITH_MESSAGE(!(enigma1.areEqualyComplex(enigma3)), "FAIL: Enigma areEqualComplex");
    ASSERT_WITH_MESSAGE(!(enigma1.areEqualyComplex(enigma4)), "FAIL: Enigma areEqualComplex");

}

void testEnigmaGetDifficulty() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	char *name3 = (char*)"enigma3";
	std::set<string> elements1 { "John1", "Kelly1", "Amanda1", "Kim1" };
	std::set<string> elements2 { "John2", "Kelly2", "Amanda2" };
	std::set<string> elements3 { "John3", "Kelly3" };

	Enigma enigma1(name1, HARD_ENIGMA, 4, elements1);
	Enigma enigma2(name2, MEDIUM_ENIGMA, 3, elements2);
	Enigma enigma3(name3, EASY_ENIGMA, 2, elements3);

    ASSERT_WITH_MESSAGE(enigma1.getDifficulty() == HARD_ENIGMA, "FAIL: Enigma getDifficulty");
    ASSERT_WITH_MESSAGE(enigma2.getDifficulty() == MEDIUM_ENIGMA, "FAIL: Enigma getDifficulty");
    ASSERT_WITH_MESSAGE(enigma3.getDifficulty() == EASY_ENIGMA, "FAIL: Enigma getDifficulty");

}

void testEnigmaGetName() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	char *name3 = (char*)"enigma3";
	std::set<string> elements1 { "John1", "Kelly1", "Amanda1", "Kim1" };
	std::set<string> elements2 { "John2", "Kelly2", "Amanda2" };
	std::set<string> elements3 { "John3", "Kelly3" };

	Enigma enigma1(name1, HARD_ENIGMA, 4, elements1);
	Enigma enigma2(name2, MEDIUM_ENIGMA, 3, elements2);
	Enigma enigma3(name3, EASY_ENIGMA, 2, elements3);

    ASSERT_WITH_MESSAGE(enigma1.getName() == "enigma1", "FAIL: Enigma getName");
    ASSERT_WITH_MESSAGE(enigma2.getName() == "enigma2", "FAIL: Enigma getName");
    ASSERT_WITH_MESSAGE(enigma3.getName() == "enigma3", "FAIL: Enigma getName");

}

void testEnigmaPrint() {
	char *name1 = (char*)"enigma1";
	char *name2 = (char*)"enigma2";
	std::set<string> elements1 { "John1", "Kelly1", "Amanda1", "Kim1" };
	std::set<string> elements2 { "John2", "Kelly2", "Amanda2" };

	Enigma enigma1(name1, HARD_ENIGMA, 4, elements1);
	Enigma enigma2(name2, MEDIUM_ENIGMA, 3, elements2);

    ASSERT_WITH_MESSAGE(enigma1.getName() == "enigma1", "FAIL: Enigma getName");
    ASSERT_WITH_MESSAGE(enigma2.getName() == "enigma2", "FAIL: Enigma getName");

	std::ostringstream stream;
    stream << enigma1;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "enigma1 (2) 4");

	std::ostringstream stream2;
    stream2 << enigma2;
    std::string str2 =  stream2.str();
    ASSERT_PRINT(str2, "enigma2 (1) 3");
}

void testEnigmaAddElement() {
	char *name1 = (char*)"enigma1";
	std::set<string> elements2 { "John2", "Kelly2", "Amanda2" };

	Enigma enigma1 = Enigma(name1, MEDIUM_ENIGMA, 3, elements2);
	ASSERT_NO_THROW(enigma1.addElement("newElement"));

    std::ostringstream stream;
    stream << enigma1;
    std::string str1 = stream.str();
    ASSERT_PRINT(str1, "enigma1 (1) 4");

	ASSERT_NO_THROW(enigma1.removeElement("John2"));

    std::ostringstream stream2;
    stream2 << enigma1;
    std::string str2 = stream2.str();
    ASSERT_PRINT(str2, "enigma1 (1) 3");
}

void testEnigmaRemoveElement() {
	char *name1 = (char*)"enigma1";
	std::set<string> elements2 { "John2", "Kelly2", "Amanda2" };

	Enigma enigma1 = Enigma(name1, MEDIUM_ENIGMA, 3, elements2);
	ASSERT_NO_THROW(enigma1.addElement("newElement"));

    std::ostringstream stream;
    stream << enigma1;
    std::string str1 = stream.str();
    ASSERT_PRINT(str1, "enigma1 (1) 4");

	ASSERT_THROWS(EnigmaElementNotFoundException, enigma1.removeElement("John3"));
	ASSERT_NO_THROW(enigma1.removeElement("John2"));

    std::ostringstream stream2;
    stream2 << enigma1;
    std::string str2 = stream2.str();
    ASSERT_PRINT(str2, "enigma1 (1) 3");

	ASSERT_NO_THROW(enigma1.removeElement("Kelly2"));
	ASSERT_NO_THROW(enigma1.removeElement("Amanda2"));
	ASSERT_NO_THROW(enigma1.removeElement("newElement"));
	ASSERT_THROWS(EnigmaNoElementsException, enigma1.removeElement("John2"));

}

void testEnigma() {
	RUN_TEST(testEnigmaConstractor);
	RUN_TEST(testEnigmaCopy);
	RUN_TEST(testEnigmaAssigment);
	RUN_TEST(testEnigmaEqual);
	RUN_TEST(testEnigmaNotEqual);
	RUN_TEST(testEnigmaGreater);
	RUN_TEST(testEnigmaLess);
	RUN_TEST(testEnigmaAreEqualyComplex);
	RUN_TEST(testEnigmaGetDifficulty);
	RUN_TEST(testEnigmaGetName);
	RUN_TEST(testEnigmaPrint);
	RUN_TEST(testEnigmaAddElement);
	RUN_TEST(testEnigmaRemoveElement);

	printBuffer();
	//TODO better enigma tests


}



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
	printBuffer();
}



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
	printBuffer();
}



void testCompanyConstractor() {
	string name = "company1";
	string phone = "987654321";

	ASSERT_NO_THROW( Company(name, phone));
	Company company(name, phone);

	std::ostringstream stream;
    stream << company;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "company1 : 987654321\n" );

}

void testCompanyCreateRoom() {
	string name = "company1";
	string phone = "987654321";
	char *room_name = (char*)"room1";

	Company company = Company(name, phone);
	ASSERT_NO_THROW( company.createRoom(room_name, 60, 1, 2));
	ASSERT_THROWS( CompanyMemoryProblemException, company.createRoom(room_name, 60, 0, 2));

	std::ostringstream stream;
    stream << company;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "company1 : 987654321\nroom1 (60/1/2)\n" );


}

void testCompanyCreateScaryRoom() {
	string name = "company1";
	string phone = "987654321";
	char *room_name = (char*)"room1";

	Company company = Company(name, phone);
	ASSERT_THROWS( CompanyMemoryProblemException, company.createScaryRoom(room_name, 60, 0, 2, 3, 4));
	ASSERT_NO_THROW( company.createScaryRoom(room_name, 60, 1, 2, 3, 4));

	std::ostringstream stream;
    stream << company;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "company1 : 987654321\nScary Room: room1 (60/1/2/3)\n" );

}

void testCompanyCreateKidsRoom() {
	string name = "company1";
	string phone = "987654321";
	char *room_name = (char*)"room1";

	Company company = Company(name, phone);
	ASSERT_THROWS( CompanyMemoryProblemException, company.createKidsRoom(room_name, 60, 0, 2, 3));
	ASSERT_NO_THROW( company.createKidsRoom(room_name, 60, 1, 2, 3));

	std::ostringstream stream;
    stream << company;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "company1 : 987654321\nKids Room: room1 (60/1/2/3)\n" );
}

void testCompanyGetAllRooms() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *room_name3 = (char*)"room3";


	Company company = Company(name, phone);
	company.createRoom(room_name1, 60, 1, 2);
	company.createScaryRoom(room_name2, 60, 1, 2, 3, 4);
	company.createKidsRoom(room_name3, 60, 1, 2, 3);
	ASSERT_NO_THROW( company.getAllRooms() );
	set<EscapeRoomWrapper*> rooms = company.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);
}

void testCompanyRemoveRoom() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *room_name3 = (char*)"room3";
	char *room_name4 = (char*)"room4";

	Company company = Company(name, phone);
	company.createRoom(room_name1, 60, 1, 2);
	company.createScaryRoom(room_name2, 60, 1, 2, 3, 4);
	company.createKidsRoom(room_name3, 60, 1, 2, 3);
	ASSERT_NO_THROW( company.getAllRooms() );
	set<EscapeRoomWrapper*> rooms = company.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	ASSERT_THROWS(CompanyRoomNotFoundException, company.removeRoom(EscapeRoomWrapper(room_name4, 60, 1, 2)));
	rooms = company.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	company.removeRoom(EscapeRoomWrapper(room_name1, 60, 1, 2));
	rooms = company.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 2);

}

void testCompanyAddEnigma() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *enigma_name1 = (char*)"enigma1";

	Company company = Company(name, phone);
	company.createRoom(room_name1, 60, 1, 2);

	ASSERT_THROWS(CompanyRoomNotFoundException, company.addEnigma(EscapeRoomWrapper(room_name2, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) ));
	ASSERT_NO_THROW(company.addEnigma(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) ));

}

void testCompanyRemoveEnigma() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *enigma_name1 = (char*)"enigma1";
	char *enigma_name2 = (char*)"enigma2";


	Company company = Company(name, phone);
	company.createRoom(room_name1, 60, 1, 2);

	ASSERT_THROWS(CompanyRoomNotFoundException, company.removeEnigma(EscapeRoomWrapper(room_name2, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) ));

	ASSERT_THROWS(CompanyRoomHasNoEnigmasException, company.removeEnigma(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) ));

	company.addEnigma(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) );

	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, company.removeEnigma(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name2, MEDIUM_ENIGMA, 4) ));

	ASSERT_NO_THROW(company.removeEnigma(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) ));

	ASSERT_THROWS(CompanyRoomHasNoEnigmasException, company.removeEnigma(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) ));

}

void testCompanyAddItem() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *enigma_name1 = (char*)"enigma1";
	char *enigma_name2 = (char*)"enigma2";


	Company company = Company(name, phone);
	company.createRoom(room_name1, 60, 1, 2);

	company.addEnigma(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) );
	ASSERT_THROWS(CompanyRoomNotFoundException, company.addItem(EscapeRoomWrapper(room_name2, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4), "newItem" ));

	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, company.addItem(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name2, MEDIUM_ENIGMA, 4), "newItem" ));

	ASSERT_NO_THROW(company.addItem(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4), "newItem" ) );
}

void testCompanyRemoveItem() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *enigma_name1 = (char*)"enigma1";
	char *enigma_name2 = (char*)"enigma2";

	Company company = Company(name, phone);
	company.createRoom(room_name1, 60, 1, 2);

	company.addEnigma(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4) );

	ASSERT_THROWS(CompanyRoomNotFoundException, company.removeItem(EscapeRoomWrapper(room_name2, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4), "newItem" ));

	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, company.removeItem(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name2, MEDIUM_ENIGMA, 4), "newItem" ));

	ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException, company.removeItem(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4), "newItem" ));

	company.addItem(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4), "newItem" );

	ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException, company.removeItem(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4), "newItem2" ));

	ASSERT_NO_THROW(company.removeItem(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4), "newItem" ) );

	ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException, company.removeItem(EscapeRoomWrapper(room_name1, 60, 1, 2), Enigma(enigma_name1, MEDIUM_ENIGMA, 4), "newItem" ));
}

void testCompanyGetAllRoomsByType() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *room_name3 = (char*)"room3";
	char *room_name4 = (char*)"room4";
	char *room_name5 = (char*)"room5";
	char *room_name6 = (char*)"room6";

	Company company = Company(name, phone);

	set<EscapeRoomWrapper*> rooms = company.getAllRoomsByType(BASE_ROOM);
	ASSERT_EQUALS(rooms.size(), 0);

	company.createRoom(room_name1, 60, 1, 2);
	company.createRoom(room_name5, 60, 1, 2);
	company.createRoom(room_name6, 60, 1, 2);

	rooms = company.getAllRoomsByType(SCARY_ROOM);
	ASSERT_EQUALS(rooms.size(), 0);

	company.createScaryRoom(room_name2, 60, 1, 2, 3, 4);
	company.createScaryRoom(room_name4, 60, 1, 2, 3, 4);
	company.createKidsRoom(room_name3, 60, 1, 2, 3);

	ASSERT_NO_THROW( company.getAllRoomsByType(BASE_ROOM) );
	rooms = company.getAllRoomsByType(BASE_ROOM);
	ASSERT_EQUALS(rooms.size(), 3);
	rooms = company.getAllRoomsByType(SCARY_ROOM);
	ASSERT_EQUALS(rooms.size(), 2);
	rooms = company.getAllRoomsByType(KIDS_ROOM);
	ASSERT_EQUALS(rooms.size(), 1);
}

void testCompanyGetRoomByName() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";

	Company company = Company(name, phone);

	ASSERT_THROWS(CompanyRoomNotFoundException, company.getRoomByName("room1"));

	company.createRoom(room_name1, 60, 1, 2);
	company.createRoom(room_name2, 61, 2, 3);

	EscapeRoomWrapper room_original = EscapeRoomWrapper(room_name1, 60, 1, 2);

	EscapeRoomWrapper* room_returned = company.getRoomByName("room1");
	ASSERT_EQUALS(room_original, *room_returned);

}

void testCompanyPrint() {
	string name = "company1";
	string phone = "987654321";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *room_name3 = (char*)"room3";
	char *room_name4 = (char*)"room4";
	char *room_name5 = (char*)"room5";
	char *room_name6 = (char*)"room6";

	Company company = Company(name, phone);

	ASSERT_THROWS(CompanyRoomNotFoundException, company.getRoomByName("room1"));

	company.createRoom(room_name1, 60, 1, 2);
	company.createRoom(room_name5, 60, 1, 2);
	company.createRoom(room_name6, 60, 1, 2);
	company.createScaryRoom(room_name2, 60, 1, 2, 3, 4);
	company.createScaryRoom(room_name4, 60, 1, 2, 3, 4);
	company.createKidsRoom(room_name3, 60, 1, 2, 3);

	std::ostringstream stream;
    stream << company;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "company1 : 987654321\nroom1 (60/1/2)\nroom5 (60/1/2)\nroom6 (60/1/2)\nScary Room: room2 (60/1/2/3)\nScary Room: room4 (60/1/2/3)\nKids Room: room3 (60/1/2/3)\n" );
}

void testCompany() {
	RUN_TEST(testCompanyConstractor);
	RUN_TEST(testCompanyCreateRoom);
	RUN_TEST(testCompanyCreateScaryRoom);
	RUN_TEST(testCompanyCreateKidsRoom);
	RUN_TEST(testCompanyGetAllRooms);
	RUN_TEST(testCompanyRemoveRoom);
	RUN_TEST(testCompanyAddEnigma);
	RUN_TEST(testCompanyRemoveEnigma);
	RUN_TEST(testCompanyAddItem);
	RUN_TEST(testCompanyRemoveItem);
	RUN_TEST(testCompanyGetAllRoomsByType);
	RUN_TEST(testCompanyGetRoomByName);
	RUN_TEST(testCompanyPrint);

	printBuffer();
}


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




int main() {
	testRoom();
	testEnigma();
	testScaryRoom();
	testKidsRoom();
	testCompany();

	//main2();
	testList();
	testIterator();

	RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(test4);
}
