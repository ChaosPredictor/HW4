/*
 * testEnigma.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: master
 */


#include "./../Enigma.h"
#include "./../mtmtest.h"
#include "./../Exceptions.h"
#include <string>

using namespace mtm::escaperoom;


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

	std::cout << std::endl << "==========================" << std::endl << std::endl;

}

