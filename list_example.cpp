#include "list_example.h"


/**
 * Function object for finding a target integer
 */
class EqualTo {
private:
  int target;
public:
  EqualTo(int i) : target(i) {}
  bool operator()(const int& i) const {
    return i == target;
  }
};

class DividedBy {
private:
  int target;
public:
  DividedBy(int i) : target(i) {}
  bool operator()(const int& i) const {
    return i % target == 0;
  }
};


/*
static void listConstractor(){
	List<int> list1;
	List<char> list2;
	List<std::string> list3;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list2.insert('a', list2.end());
	list2.insert('b', list2.end());
	list2.insert('c', list2.end());
	list3.insert("abc", list3.end());
	list3.insert("def", list3.end());
	list3.insert("ghi", list3.end());

	int counter = 1;
	for (List<int>::Iterator it1 = list1.begin(); it1 != list1.end(); ++it1) {
		ASSERT_EQUALS(counter++, *it1);
	}

	List<char>::Iterator it2 = list2.begin();
	ASSERT_EQUALS('a', *it2++);
	ASSERT_EQUALS('b', *it2++);
	ASSERT_EQUALS('c', *it2++);

	List<std::string>::Iterator it3 = list3.begin();
	ASSERT_EQUALS("abc", *it3++);
	ASSERT_EQUALS("def", *it3++);
	ASSERT_EQUALS("ghi", *it3++);
}

static void listCopy(){
	List<int> list10;
	List<char> list20;
	List<std::string> list30;
	list10.insert(1, list10.end());
	list10.insert(2, list10.end());
	list10.insert(3, list10.end());
	list20.insert('a', list20.end());
	list20.insert('b', list20.end());
	list20.insert('c', list20.end());
	list30.insert("abc", list30.end());
	list30.insert("def", list30.end());
	list30.insert("ghi", list30.end());


	List<int> list1(list10);
	List<int>::Iterator it1 = list10.begin();
	list10.remove(it1);
	ASSERT_EQUALS(list10.getSize(), 2);
	ASSERT_EQUALS(list1.getSize(), 3);

	List<char> list2(list20);
	List<char>::Iterator it2 = list2.begin();
	list2.remove(it2);
	ASSERT_EQUALS(list2.getSize(), 2);
	ASSERT_EQUALS(list20.getSize(), 3);

	List<std::string> list3(list30);


	int counter = 1;
	for (List<int>::Iterator it1 = list1.begin(); it1 != list1.end(); ++it1) {
		ASSERT_EQUALS(counter++, *it1);
	}

	it2 = list2.begin();
	//ASSERT_EQUALS('a', *it2);
	//it2++;
	ASSERT_EQUALS('b', *it2);
	it2++;
	ASSERT_EQUALS('c', *it2);

	List<std::string>::Iterator it3 = list3.begin();
	ASSERT_EQUALS("abc", *it3);
	it3++;
	ASSERT_EQUALS("def", *it3);
	it3++;
	ASSERT_EQUALS("ghi", *it3);
}

static void listAssignment(){
	List<int> list10;
	List<char> list20;
	List<std::string> list30;
	list10.insert(1, list10.end());
	list10.insert(2, list10.end());
	list10.insert(3, list10.end());
	list20.insert('a', list20.end());
	list20.insert('b', list20.end());
	list20.insert('c', list20.end());
	list30.insert("abc", list30.end());
	list30.insert("def", list30.end());
	list30.insert("ghi", list30.end());

	List<int> list1;
	list1= list10;
	List<int>::Iterator it1 = list10.begin();
	list10.remove(it1);
	ASSERT_EQUALS(list10.getSize(), 2);
	ASSERT_EQUALS(list1.getSize(), 3);

	List<char> list2;
	list2 = list20;
	List<char>::Iterator it2 = list2.begin();
	list2.remove(it2);
	ASSERT_EQUALS(list2.getSize(), 2);
	ASSERT_EQUALS(list20.getSize(), 3);

	List<std::string> list3;
	list3 = list30;

	int counter = 1;
	for (List<int>::Iterator it1 = list1.begin(); it1 != list1.end(); ++it1) {
		ASSERT_EQUALS(counter++, *it1);
	}

	it2 = list2.begin();
	//ASSERT_EQUALS('a', *it2);
	//it2++;
	ASSERT_EQUALS('b', *it2);
	it2++;
	ASSERT_EQUALS('c', *it2);

	List<std::string>::Iterator it3 = list3.begin();
	ASSERT_EQUALS("abc", *it3++);
	ASSERT_EQUALS("def", *it3++);
	ASSERT_EQUALS("ghi", *it3);
}

static void listBegin(){
	List<int> list1;
	List<char> list2;
	List<std::string> list3;
	list1.insert(1, list1.end());
	List<int>::Iterator it1 = list1.begin();
	ASSERT_EQUALS(1, *it1);
	list1.insert(2, list1.begin());
	it1 = list1.begin();
	ASSERT_EQUALS(2, *it1);
	list1.insert(3, list1.begin());
	it1 = list1.begin();
	ASSERT_EQUALS(3, *it1);

	list2.insert('a', list2.end());
	List<char>::Iterator it2 = list2.begin();
	ASSERT_EQUALS('a', *it2);
	list2.insert('b', list2.begin());
	it2 = list2.begin();
	ASSERT_EQUALS('b', *it2);
	list2.insert('c', list2.begin());
	it2 = list2.begin();
	ASSERT_EQUALS('c', *it2);

	list3.insert("abc", list3.end());
	List<std::string>::Iterator it3 = list3.begin();
	ASSERT_EQUALS("abc", *it3);
	list3.insert("def", list3.begin());
	it3 = list3.begin();
	ASSERT_EQUALS("def", *it3);
	list3.insert("ghi", list3.begin());
	it3 = list3.begin();
	ASSERT_EQUALS("ghi", *it3);

	it1 = list1.begin();
	ASSERT_EQUALS(3, *it1++);
	ASSERT_EQUALS(2, *it1++);
	ASSERT_EQUALS(1, *it1);

	it2 = list2.begin();
	ASSERT_EQUALS('c', *it2++);
	ASSERT_EQUALS('b', *it2++);
	ASSERT_EQUALS('a', *it2);

	it3 = list3.begin();
	ASSERT_EQUALS("ghi", *it3++);
	ASSERT_EQUALS("def", *it3++);
	ASSERT_EQUALS("abc", *it3);
}

static void listEnd(){
	List<int> list1;
	List<char> list2;
	List<std::string> list3;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list2.insert('a', list2.end());
	list2.insert('b', list2.end());
	list2.insert('c', list2.end());
	list3.insert("abc", list3.end());
	list3.insert("def", list3.end());
	list3.insert("ghi", list3.end());

	int counter = 1;
	for (List<int>::Iterator it1 = list1.begin(); it1 != list1.end(); ++it1) {
		ASSERT_EQUALS(counter++, *it1);
	}

	List<char>::Iterator it2 = list2.begin();
	ASSERT_EQUALS('a', *it2++);
	ASSERT_EQUALS('b', *it2++);
	ASSERT_EQUALS('c', *it2++);
	ASSERT_EQUALS(list2.end(), it2);

	List<std::string>::Iterator it3 = list3.begin();
	ASSERT_EQUALS("abc", *it3++);
	ASSERT_EQUALS("def", *it3++);
	ASSERT_EQUALS("ghi", *it3++);
	ASSERT_EQUALS(list3.end(), it3);
}

static void listInsert(){
	List<int> list1;
	List<int> list2;
	list1.insert(1, list1.end());
	list1.insert(2, list1.begin());
	list1.insert(3, list1.end());
	list1.insert(4, list1.begin());
	list1.insert(5);
	List<int>::Iterator it1 = list1.begin();
	ASSERT_NO_THROW(list1.insert(6, it1));
	ASSERT_NO_THROW(list1.insert(7));
	ASSERT_NO_THROW(list1.insert(8, list1.begin()));
	ASSERT_NO_THROW(list1.insert(9, list1.end()));

	list2.insert(1, list2.begin());
	List<int>::Iterator it2 = list2.begin();

	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list1.insert(9, it2));

	it1 = list1.begin();
	for(int i = 0; i < 3; i++) it1++;
	list1.insert(15, it1);

	it1 = list1.begin();
	ASSERT_EQUALS(8, *it1++);
	ASSERT_EQUALS(6, *it1++);
	ASSERT_EQUALS(4, *it1++);
	ASSERT_EQUALS(15, *it1++);
	ASSERT_EQUALS(2, *it1++);
	ASSERT_EQUALS(1, *it1++);
	ASSERT_EQUALS(3, *it1++);
	ASSERT_EQUALS(5, *it1++);
	ASSERT_EQUALS(7, *it1++);
	ASSERT_EQUALS(9, *it1++);
}

static void listRemove(){
	List<int> list1;
	List<int> list2;

	list1.insert(1, list1.end());
	list1.insert(2, list1.begin());
	list1.insert(3, list1.end());
	list1.insert(4, list1.begin());
	list1.insert(5, list1.end());
	list1.insert(6, list1.begin());
	list1.insert(7, list1.end());
	list1.insert(8, list1.begin());
	list1.insert(9, list1.end());

	list2.insert(1, list2.begin());
	List<int>::Iterator it2 = list2.begin();
	List<int>::Iterator it1 = list1.end();

	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list1.remove(it2));
	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list1.remove(it1));

	it1 = list1.begin();

	ASSERT_NO_THROW(list1.remove(it1));

	it1 = list1.begin();
	for(int i = 0; i < 3; i++) it1++;
	ASSERT_NO_THROW(list1.remove(it1));

	it1 = list1.begin();
	for(int i = 0; i < 6; i++) it1++;
	ASSERT_NO_THROW(list1.remove(it1));

	it1 = list1.begin();
	ASSERT_EQUALS(6, *it1++);
	ASSERT_EQUALS(4, *it1++);
	ASSERT_EQUALS(2, *it1++);
	ASSERT_EQUALS(3, *it1++);
	ASSERT_EQUALS(5, *it1++);
	ASSERT_EQUALS(7, *it1++);

	for(List<int>::Iterator it1 = list1.begin(); it1 != list1.end(); ) {
		ASSERT_NO_THROW(list1.remove(it1));
		it1 = list1.begin();
	}
	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list1.remove(it1));
	ASSERT_EQUALS(list1.getSize(), 0 );
}

static void listFind(){
	List<int> list1;

	list1.insert(1, list1.end());
	list1.insert(2, list1.begin());
	list1.insert(3, list1.end());
	list1.insert(4, list1.begin());
	list1.insert(5, list1.end());
	list1.insert(6, list1.begin());
	list1.insert(7, list1.end());
	list1.insert(8, list1.begin());
	list1.insert(9, list1.end());

	List<int>::Iterator it1 = list1.find(DividedBy(3));
	ASSERT_EQUALS(6, *it1);

	it1 = list1.find(DividedBy(2));
	ASSERT_EQUALS(8, *it1);

	it1 = list1.find(DividedBy(5));
	ASSERT_EQUALS(5, *it1);

	it1 = list1.find(DividedBy(9));
	ASSERT_EQUALS(9, *it1);

	it1 = list1.find(DividedBy(11));
	ASSERT_EQUALS(list1.end(), it1);
}

static void listSort(){
	List<int> list1;

	list1.insert(1, list1.end());
	list1.insert(2, list1.begin());
	list1.insert(3, list1.end());
	list1.insert(4, list1.begin());
	list1.insert(5, list1.end());
	list1.insert(6, list1.begin());
	list1.insert(7, list1.end());
	list1.insert(8, list1.begin());
	list1.insert(9, list1.end());

	list1.sort(std::less<int>());

	int counter = 1;
	for (List<int>::Iterator it1 = list1.begin(); it1 != list1.end(); ++it1) {
		ASSERT_EQUALS(counter++, *it1);
	}
}

static void listGetSize(){
	List<int> list1;

	ASSERT_EQUALS(list1.getSize(), 0);

	list1.insert(1, list1.end());
	ASSERT_EQUALS(list1.getSize(), 1);

	list1.insert(2, list1.begin());
	ASSERT_EQUALS(list1.getSize(), 2);

	list1.insert(3, list1.end());
	ASSERT_EQUALS(list1.getSize(), 3);

	list1.insert(4, list1.begin());
	ASSERT_EQUALS(list1.getSize(), 4);

	list1.insert(5, list1.end());
	list1.insert(6, list1.begin());
	list1.insert(7, list1.end());
	list1.insert(8, list1.begin());
	list1.insert(9, list1.end());

	List<int>::Iterator it1 = list1.begin();

	ASSERT_NO_THROW(list1.remove(it1));

	ASSERT_EQUALS(list1.getSize(), 8);

}

static void listEqual() {
	List<int> list1;
	List<int> list2;

	list1.insert(1, list1.end());
	list1.insert(2, list1.begin());
	list1.insert(3, list1.end());
	list1.insert(4, list1.begin());
	list1.insert(5, list1.end());
	list1.insert(6, list1.begin());
	list1.insert(7, list1.end());
	list1.insert(8, list1.begin());
	list1.insert(9, list1.end());

	list2.insert(1, list2.end());
	list2.insert(2, list2.end());
	list2.insert(3, list2.end());
	list2.insert(4, list2.end());
	list2.insert(5, list2.end());
	list2.insert(6, list2.end());
	list2.insert(7, list2.end());
	list2.insert(8, list2.end());
	list2.insert(9, list2.end());

	list1.sort(std::less<int>());

	ASSERT_TRUE(list1 == list2);

}

static void listNotEqual() {
	List<int> list1;
	List<int> list2;

	list1.insert(1, list1.end());
	list1.insert(2, list1.begin());
	list1.insert(3, list1.end());
	list1.insert(4, list1.begin());
	list1.insert(5, list1.end());
	list1.insert(6, list1.begin());
	list1.insert(7, list1.end());

	list2.insert(1, list2.end());
	list2.insert(2, list2.end());
	list2.insert(3, list2.end());
	list2.insert(4, list2.end());
	list2.insert(5, list2.end());
	list2.insert(6, list2.end());
	list2.insert(7, list2.end());
	list2.insert(8, list2.end());

	ASSERT_TRUE(list1 != list2);

	list1.insert(8, list1.begin());
	list1.insert(9, list1.end());

	ASSERT_TRUE(list1 != list2);

	list2.insert(10, list2.end());

	list1.sort(std::less<int>());

	ASSERT_TRUE(list1 != list2);

}

static void listExample(){
	List<int> list;
	list.insert(1, list.end());
	list.insert(2, list.end());
	list.insert(3, list.end());

	int counter = 1;
	for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
		ASSERT_EQUALS(counter++, *it);
	}

	// C++11 syntactic sugar Range-based for-loop
	counter = 1;
	for (int& element : list) {
		ASSERT_EQUALS(counter++, element);
	}

	List<int>::Iterator it = list.begin();
	ASSERT_EQUALS(3, list.getSize());
	list.remove(++it);
	it = list.begin();
	ASSERT_EQUALS(*it, 1);
	list.insert(4, list.begin());
	list.insert(2, list.begin());
	//list.printList();


	// std::less<int> is a function object defined in <functional>
	// it simply calls operator< of the type compared
	list.sort(std::less<int>());
	it = list.begin();
	ASSERT_EQUALS(1, *it);

	it = list.find(EqualTo(3));
	ASSERT_EQUALS(3, *it);
	*it = 3;


	// The following insert should add to end of list
	list.insert(5);


	const List<int> list2(list);
	ASSERT_TRUE(list == list2);
	ASSERT_FALSE(list != list2);

	//test directions
	it = list.begin();
	it++;
	ASSERT_EQUALS(2, *it);
	++it;
	ASSERT_EQUALS(3, *it);
	it--;
	ASSERT_EQUALS(2, *it);
	it++;
	it++;
	ASSERT_EQUALS(4, *it);
	--it;
	ASSERT_EQUALS(3, *it);

	it = list.end();
	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, *it);

	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list.insert(1, list2.begin()) );

	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list.remove(it) );

}

int testList() {
	RUN_TEST(listConstractor);
	RUN_TEST(listCopy);
	RUN_TEST(listAssignment);
	RUN_TEST(listBegin);
	RUN_TEST(listEnd);
	RUN_TEST(listInsert);
	RUN_TEST(listRemove);
	RUN_TEST(listFind);
	RUN_TEST(listSort);
	RUN_TEST(listGetSize);
	RUN_TEST(listEqual);
	RUN_TEST(listNotEqual);

	RUN_TEST(listExample);

	std::cout << std::endl << "==========================" << std::endl << std::endl;

	return 0;
}


static void IteratorPlusPlus() {
	List<int> list1;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list1.insert(4, list1.end());
	list1.insert(5, list1.end());
	list1.insert(6, list1.end());
	list1.insert(7, list1.end());
	list1.insert(8, list1.end());
	list1.insert(9, list1.end());

	List<int>::Iterator it1 = list1.begin();
	int counter = 1;
	ASSERT_EQUALS(counter++, *it1++);
	ASSERT_EQUALS(counter++, *it1++);
	ASSERT_EQUALS(counter++, *it1++);

}

static void PlusPlusIterator() {
	List<int> list1;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list1.insert(4, list1.end());
	list1.insert(5, list1.end());
	list1.insert(6, list1.end());
	list1.insert(7, list1.end());
	list1.insert(8, list1.end());
	list1.insert(9, list1.end());

	List<int>::Iterator it1 = list1.begin();
	int counter = 1;
	ASSERT_EQUALS(counter++, *it1);
	ASSERT_EQUALS(counter++, *++it1);
	ASSERT_EQUALS(counter++, *++it1);

}

static void IteratorMinusMinus() {
	List<int> list1;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list1.insert(4, list1.end());
	list1.insert(5, list1.end());
	list1.insert(6, list1.end());
	list1.insert(7, list1.end());
	list1.insert(8, list1.end());
	list1.insert(9, list1.end());

	List<int>::Iterator it1 = list1.begin();
	for(int i = 0; i < list1.getSize()-1; i++) {
		it1++;
	}
	int counter = 9;
	ASSERT_EQUALS(counter--, *it1--);
	ASSERT_EQUALS(counter--, *it1--);
	ASSERT_EQUALS(counter--, *it1--);

}

static void MinusMinusIterator() {
	List<int> list1;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list1.insert(4, list1.end());
	list1.insert(5, list1.end());
	list1.insert(6, list1.end());
	list1.insert(7, list1.end());
	list1.insert(8, list1.end());
	list1.insert(9, list1.end());

	List<int>::Iterator it1 = list1.begin();
	for(int i = 0; i < list1.getSize()-1; i++) {
		it1++;
	}
	int counter = 9;
	ASSERT_EQUALS(counter--, *it1);
	ASSERT_EQUALS(counter--, *--it1);
	ASSERT_EQUALS(counter--, *--it1);

}

static void IteratorOperatorStar() {
	List<int> list1;
	List<char> list2;
	List<std::string> list3;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list2.insert('a', list2.end());
	list2.insert('b', list2.end());
	list2.insert('c', list2.end());
	list3.insert("abc", list3.end());
	list3.insert("def", list3.end());
	list3.insert("ghi", list3.end());

	List<int>::Iterator it1;
	int counter = 1;
	for (it1 = list1.begin(); it1 != list1.end(); ++it1) {
		ASSERT_EQUALS(counter++, *it1);
	}
	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, *it1 );

	List<char>::Iterator it2 = list2.begin();
	ASSERT_EQUALS('a', *it2++);
	ASSERT_EQUALS('b', *it2++);
	ASSERT_EQUALS('c', *it2++);
	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, *it2 );

	List<std::string>::Iterator it3 = list3.begin();
	ASSERT_EQUALS("abc", *it3++);
	ASSERT_EQUALS("def", *it3++);
	ASSERT_EQUALS("ghi", *it3++);
	ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, *it3 );

}

static void IteratorEqual() {static
	List<int> list1;
	List<int> list2;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());

	List<int>::Iterator it1 = list1.begin();

	list2.insert(1, list2.end());
	list2.insert(2, list2.end());
	list2.insert(3, list2.end());

	List<int>::Iterator it2 = list2.begin();

	ASSERT_FALSE( it1 == it2);

	it1++;
	it1++;
	it1++;
	it2++;
	it2++;
	it2++;
	//TODO not sure
	ASSERT_TRUE( it1 == it2);

	it2 = list1.begin();
	it1 = list1.begin();

	ASSERT_TRUE( it1 == it2);

	it1++;
	it1++;
	it2++;
	it2++;
	ASSERT_TRUE( it1 == it2);
}

static void IteratorNotEqual() {static
	List<int> list1;
	List<int> list2;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());

	List<int>::Iterator it1 = list1.begin();

	list2.insert(1, list2.end());
	list2.insert(2, list2.end());
	list2.insert(3, list2.end());

	List<int>::Iterator it2 = list2.begin();

	ASSERT_TRUE( it1 != it2);

	it1++;
	it1++;
	it1++;
	it2++;
	it2++;
	it2++;
	//TODO not sure
	ASSERT_FALSE( it1 != it2);

	it2 = list1.begin();
	it1 = list1.begin();

	ASSERT_FALSE( it1 != it2);

	it1++;
	it1++;
	it2++;
	it2++;
	ASSERT_FALSE( it1 != it2);
}

static void IteratorCopy() {static
	List<int> list1;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list1.insert(4, list1.end());
	list1.insert(5, list1.end());
	list1.insert(6, list1.end());

	List<int>::Iterator it1 = list1.begin();
	List<int>::Iterator it2 = list1.begin();
	it1++;
	it1++;
	ASSERT_EQUALS(3, *it1);

	it2 = it1;

	ASSERT_EQUALS(3, *it1);
	ASSERT_EQUALS(3, *it2);

	it1++;

	ASSERT_EQUALS(4, *it1);
	ASSERT_EQUALS(3, *it2);

	it2++;
	it2++;

	ASSERT_EQUALS(4, *it1);
	ASSERT_EQUALS(5, *it2);
}

static void IteratorAssignment() {static
	List<int> list1;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	list1.insert(4, list1.end());
	list1.insert(5, list1.end());
	list1.insert(6, list1.end());

	List<int>::Iterator it1 = list1.begin();
	it1++;
	it1++;
	ASSERT_EQUALS(3, *it1);

	List<int>::Iterator it2(it1);

	ASSERT_EQUALS(3, *it1);
	ASSERT_EQUALS(3, *it2);

	it1++;

	ASSERT_EQUALS(4, *it1);
	ASSERT_EQUALS(3, *it2);

	it2++;
	it2++;

	ASSERT_EQUALS(4, *it1);
	ASSERT_EQUALS(5, *it2);
}

int testIterator() {
	RUN_TEST(IteratorPlusPlus);
	RUN_TEST(PlusPlusIterator);
	RUN_TEST(IteratorMinusMinus);
	RUN_TEST(MinusMinusIterator);
	RUN_TEST(IteratorOperatorStar);
	RUN_TEST(IteratorEqual);
	RUN_TEST(IteratorNotEqual);
	RUN_TEST(IteratorCopy);
	RUN_TEST(IteratorAssignment);

	std::cout << std::endl << "==========================" << std::endl << std::endl;

	return 0;
}
*/


