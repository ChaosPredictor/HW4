/*
 * list.h
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */

#ifndef LIST_H_
#define LIST_H_

#include <memory>

//typedef int T;

//template <class T>
//typedef bool(*CompareNodes)(const T&, const T&);



//template <typename T>
//using CompareNodes = typename bool(*CompareNodes)<T>(const T&, const T&);

template <typename T>
class List;


template <class T>
class Node {

	friend class List<T>;

	Node(const T &data) : data(data), next (nullptr) {}
    Node<T> *next;
    T data;
/*
	typedef struct node_t* Node;
	struct node_t {
		T n;
		Node next;
	};*/

};



template <class T>
class List{

/*
	typedef struct node_t* Node;
	struct node_t {
		T n;
		Node next;
	};
*/


public:
    typedef Node<T> node;
    std::unique_ptr<node> head;
    std::unique_ptr<node> tail;


    void init()
    {
        //size = 0;
        head.reset(new node);
        tail.reset(new node);
        head->next = tail.get();
    }



	List() { init(); }
	List(List& l) { init(); }
	List(const List& l) { init(); }
	~List();
	List& operator=(const List&);


	class Iterator {
		Node<T>* p;

	    //
	    //Iterator(const LinkedListIterator& other) : p(other.p) {}
	    //Iterator& operator=(LinkedListIterator other) { std::swap(p, other.p); return *this; }


	public:
		Iterator();
		Iterator(Node<T> p) : p(p) {}
		//Iterator(const Iterator& other) : p(other.p) {}
		//Iterator& operator=(Iterator other) { std::swap(p, other.p); return *this; }
	    //const T& operator*() const { return 1; }

		bool operator!=(const Iterator& second);
		Iterator& operator++();
		Iterator& operator++(int);
		Iterator& operator--();
		Iterator& operator--(int);
	    T& operator*() { return 1; }
	    const T& operator*() const { return 1; }




	};
    typedef Iterator iterator;


	bool operator==(List second) {
		return true;
	}

	bool operator!=(List second) {
		return false;
	}

	template<class Function>
	void sort(Function f);

	template<class Function>
	iterator find(Function f);

	iterator end() {
		return iterator(tail.get());
	}
	iterator begin() {}

	iterator insert(const T value) {}
	iterator insert(const T value, const iterator place ) {}



	int getSize() {
		return 1;
	}



	void remove(iterator& removeIter) {

	}

};

/*
template <class T>
List<T>::List() {
	//head = NULL;
}*/


#endif /* LIST_H_ */
