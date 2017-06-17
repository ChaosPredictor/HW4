/*
 * list.h
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */

#ifndef LIST_H_
#define LIST_H_

//typedef int T;

//template <class T>
//typedef bool(*CompareNodes)(const T&, const T&);



//template <typename T>
//using CompareNodes = typename bool(*CompareNodes)<T>(const T&, const T&);


template <class T>
class List{




	typedef struct node_t* Node;
	struct node_t {
		T n;
		Node next;
	};


public:
	List();
	List(const List& l);
	~List();
	List& operator=(const List&);


	//template <class TNode>
	class Iterator {
		Node* p;

	    //
	    //Iterator(const LinkedListIterator& other) : p(other.p) {}
	    //Iterator& operator=(LinkedListIterator other) { std::swap(p, other.p); return *this; }


	public:
		Iterator();
		//Iterator(Node* p) : p(p) {}
		//Iterator(const Iterator& other) : p(other.p) {}
		//Iterator& operator=(Iterator other) { std::swap(p, other.p); return *this; }
	    //const T& operator*() const { return 1; }

		bool operator!=(const Iterator& second);
		Iterator& operator++();
		//void operator++(int);
	    T& operator*() { return 1; }
	    const T& operator*() const { return 1; }




	};
    typedef Iterator iterator;


	bool operator==(List second) {
		return true;
	}



	template<class Function>
	void sort(Function f);

	template<class Function>
	iterator find(Function f);

	iterator end() {}
	iterator begin() {}

	iterator insert(const T value) {}
	iterator insert(const T value, iterator place ) {}



	int getSize() {
		return 1;
	}



	void remove(iterator& removeIter) {

	}

};


template <class T>
List<T>::List() {
	//head = NULL;
}


#endif /* LIST_H_ */
