#include <functional>
#include "list.h"
#include "mtmtest.h"


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


static void listExample(){
	List<int> list;
	//list.printList();
	list.insert(1, list.end());
	//list.printList();
	list.insert(2, list.end());
	//list.printList();
	list.insert(3, list.end());
	//list.printList();

	//list.insert(4, list.end());

	//printf("begin address: %p   end address: %p \n", (void*)(list.begin().ptr), (void*)(list.end().ptr));


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


int main2() {
  RUN_TEST(listExample);

  return 0;
}
