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


//void printBuffer() {
//	std::cout << std::endl << "==========================" << std::endl << std::endl;
//}


static void listConstractor(){
	List<int> list1;
	List<char> list2;
	List<std::string> list3;
	list1.insert(1, list1.end());
	list1.insert(2, list1.end());
	list1.insert(3, list1.end());
	//char a = 'a';
	//char b = 'b';
	//char c = 'c';
	list2.insert('a', list2.end());
	list2.insert('b', list2.end());
	list2.insert('c', list2.end());



	int counter = 1;
	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
		ASSERT_EQUALS(counter++, *it);
	}



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

	RUN_TEST(listExample);

	//printBuffer();
	std::cout << std::endl << "==========================" << std::endl << std::endl;

	return 0;
}
