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

	ASSERT_THROWS(EscapeRoomNoEnigmasException, room1.getHardestEnigma());

	room1.addEnigma(enigma1);
	room1.addEnigma(enigma2);
	room1.addEnigma(enigma3);

	ASSERT_NO_THROW(room1.getHardestEnigma());

	Enigma hardestEnigma = room1.getHardestEnigma();

	ASSERT_EQUALS(hardestEnigma, enigma1);

	room1.addEnigma(enigma4);

	hardestEnigma = room1.getHardestEnigma();

	ASSERT_EQUALS(hardestEnigma, enigma4);

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

	std::vector<Enigma> allEnigmas = room1.getAllEnigmas();

	ASSERT_EQUALS(allEnigmas.size(), 0);


	room1.addEnigma(enigma1);
	room1.addEnigma(enigma2);
	room1.addEnigma(enigma3);

	ASSERT_NO_THROW(room1.getAllEnigmas());

	allEnigmas = room1.getAllEnigmas();

	ASSERT_EQUALS(allEnigmas.size(), 3);


}

void testRoom() {
	RUN_TEST(testRoomConstractor);
	RUN_TEST(testRoomCopy);
	RUN_TEST(testRoomAddEnigma);
	RUN_TEST(testRoomRemoveEnigma);
	RUN_TEST(testRoomGetHardestEnigma);
	RUN_TEST(testRoomGetAllEnigmas);





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
	printBuffer();

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
	printBuffer();


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

	ScaryRoom scary_room1 = ScaryRoom(name1, 60, 5, 1, 3, 2);

    std::ostringstream stream;
    stream << scary_room1;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "Scary Room: room1 (60/5/1/3)");

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

	KidsRoom kids_room1 = KidsRoom(name1, 60, 5, 1, 3);

    std::ostringstream stream;
    stream << kids_room1;
    std::string str =  stream.str();
    ASSERT_PRINT(str, "Kids Room: room1 (60/5/1/3)");

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
}

void testCompanyCreateRoom() {
	string name = "company1";
	string phone = "987654321";
	char *room_name = (char*)"room1";

	Company company = Company(name, phone);
	ASSERT_NO_THROW( company.createRoom(room_name, 60, 1, 2));

}

void testCompanyCreateScaryRoom() {
	string name = "company1";
	string phone = "987654321";
	char *room_name = (char*)"room1";

	Company company = Company(name, phone);
	ASSERT_NO_THROW( company.createScaryRoom(room_name, 60, 1, 2, 3, 4));

}

void testCompanyCreateKidsRoom() {
	string name = "company1";
	string phone = "987654321";
	char *room_name = (char*)"room1";

	Company company = Company(name, phone);
	ASSERT_NO_THROW( company.createKidsRoom(room_name, 60, 1, 2, 3));

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
	//char *room_name4 = (char*)"room4";



	Company company = Company(name, phone);
	company.createRoom(room_name1, 60, 1, 2);
	company.createScaryRoom(room_name2, 60, 1, 2, 3, 4);
	company.createKidsRoom(room_name3, 60, 1, 2, 3);
	ASSERT_NO_THROW( company.getAllRooms() );
	set<EscapeRoomWrapper*> rooms = company.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	company.removeRoom(EscapeRoomWrapper(room_name3, 60, 1, 2));
	//rooms = company.getAllRooms();
	//ASSERT_EQUALS(rooms.size(), 3);

			//ASSERT_THROWS(CompanyRoomNotFoundException, company.removeRoom(EscapeRoomWrapper(room_name4, 66, 5, 6)));

			//company.removeRoom(EscapeRoomWrapper(room_name1, 60, 1, 2));
	//rooms = company.getAllRooms();
	//ASSERT_EQUALS(rooms.size(), 2);

}



void testCompany() {
	RUN_TEST(testCompanyConstractor);
	RUN_TEST(testCompanyCreateRoom);
	RUN_TEST(testCompanyCreateScaryRoom);
	RUN_TEST(testCompanyCreateKidsRoom);
	RUN_TEST(testCompanyGetAllRooms);
	RUN_TEST(testCompanyRemoveRoom);


	printBuffer();
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
	testScaryRoom();
	testKidsRoom();
	testKidsRoom();
	testCompany();

	main2();

	//RUN_TEST(test1);
    //RUN_TEST(test2);
    //RUN_TEST(test3);
    //RUN_TEST(test4);
}
