/*
 * testCompany.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: master
 */

#include "./../Company.h"
#include "./../mtmtest.h"
#include "./../Exceptions.h"
#include <string>


using namespace mtm::escaperoom;


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

void testCompanyCopy() {
	string name1 = "company1";
	string name2 = "company2";
	string phone1 = "987654321";
	string phone2 = "987654312";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *room_name3 = (char*)"room3";
	char *room_name4 = (char*)"room4";

	Company company1 = Company(name1, phone1);

	company1.createRoom(room_name1, 60, 1, 2);
	company1.createScaryRoom(room_name2, 60, 1, 2, 3, 4);
	company1.createKidsRoom(room_name3, 60, 1, 2, 3);
	ASSERT_NO_THROW( company1.getAllRooms() );
	set<EscapeRoomWrapper*> rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	ASSERT_THROWS(CompanyRoomNotFoundException, company1.removeRoom(EscapeRoomWrapper(room_name4, 60, 1, 2)));
	rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	Company company2(company1);

	company1.removeRoom(EscapeRoomWrapper(room_name1, 60, 1, 2));
	rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 2);
	rooms = company2.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

}

void testCompanyAssigment() {
	string name1 = "company1";
	string name2 = "company2";
	string phone1 = "987654321";
	string phone2 = "987654312";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *room_name3 = (char*)"room3";
	char *room_name4 = (char*)"room4";

	Company company1 = Company(name1, phone1);
	Company company2 = Company(name2, phone2);

	company1.createRoom(room_name1, 60, 1, 2);
	company1.createScaryRoom(room_name2, 60, 1, 2, 3, 4);
	company1.createKidsRoom(room_name3, 60, 1, 2, 3);
	ASSERT_NO_THROW( company1.getAllRooms() );
	set<EscapeRoomWrapper*> rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	ASSERT_THROWS(CompanyRoomNotFoundException, company1.removeRoom(EscapeRoomWrapper(room_name4, 60, 1, 2)));
	rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	company2 = company1;

	company1.removeRoom(EscapeRoomWrapper(room_name1, 60, 1, 2));
	rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 2);
	rooms = company2.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	company2.removeRoom(ScaryRoom(room_name2, 60, 1, 2, 3, 4));
	company2.removeRoom(KidsRoom(room_name3, 60, 1, 2, 3));


	rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 2);
	rooms = company2.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 1);

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
	rooms.clear();

	rooms = company.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);
}

void testCompanyRemoveRoom() {
	string name1 = "company1";
	string name2 = "company2";
	string phone1 = "987654321";
	string phone2 = "987654312";
	char *room_name1 = (char*)"room1";
	char *room_name2 = (char*)"room2";
	char *room_name3 = (char*)"room3";
	char *room_name4 = (char*)"room4";

	Company company1 = Company(name1, phone1);

	company1.createRoom(room_name1, 60, 1, 2);
	company1.createScaryRoom(room_name2, 60, 1, 2, 3, 4);
	company1.createKidsRoom(room_name3, 60, 1, 2, 3);
	ASSERT_NO_THROW( company1.getAllRooms() );
	set<EscapeRoomWrapper*> rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	ASSERT_THROWS(CompanyRoomNotFoundException, company1.removeRoom(EscapeRoomWrapper(room_name4, 60, 1, 2)));
	rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

	Company company2(company1);

	company1.removeRoom(EscapeRoomWrapper(room_name1, 60, 1, 2));
	rooms = company1.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 2);
	rooms = company2.getAllRooms();
	ASSERT_EQUALS(rooms.size(), 3);

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

	ASSERT_THROWS(CompanyRoomNotFoundException, company.getRoomByName("room2"));

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
	RUN_TEST(testCompanyCopy);
	RUN_TEST(testCompanyAssigment);
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

	std::cout << std::endl << "==========================" << std::endl << std::endl;
}
