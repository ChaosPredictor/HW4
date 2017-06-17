/*
 * list.h
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */

#ifndef LIST_H_
#define LIST_H_

template <class T>
class List {


	typedef struct node_t {
		T* data;
		struct node_t* next;
	} *Node;

public:

	class Iterator {
	    Node ptr;

	public:
	    Iterator() {}
	    bool operator!=(const Iterator& right) {
	    	return false;
	    }
	    Iterator& operator++() {
			ptr = ptr->next;
			return *this;
	    }
	    Iterator& operator++(int) {
			ptr = ptr->next;
			return *this;
	    }
	    Iterator& operator--() {
			ptr = ptr->next;
			return *this;
	    }
	    Iterator& operator--(int) {
			ptr = ptr->next;
			return *this;
	    }


	    T& operator*() { return *(ptr->data); }
	    const int& operator*() const { return ptr->data; }


	};

	typedef Iterator iterator;


	List() {}

    bool operator==(const List& right) {
    	return true;
    }

    bool operator!=(const List& right) {
    	return false;
    }



    void insert(T data, iterator it) {}
	void insert(T data) {}

	iterator end() {
		Iterator it;
		return it;
	}
	iterator begin() {
		Iterator it;
		return it;
	}
	void remove(iterator& it) {}

	template<class Function>
	void sort(Function f);

	template<class Function>
	iterator find(Function f);

	int getSize() { return 1; }



};

#endif /* LIST_H_ */
