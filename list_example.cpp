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


	RUN_TEST(listExample);

	std::cout << std::endl << "==========================" << std::endl << std::endl;

	return 0;
}
