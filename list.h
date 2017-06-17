/*
 * list.h
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */

#ifndef LIST_H_
#define LIST_H_

//typedef int T;

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
		bool operator++();
	    T& operator*() { return 1; }
	    const T& operator*() const { return 1; }



	};
    typedef Iterator iterator;





	void insert(T value, iterator place){

	}

	iterator end() {

	}
	iterator begin() {

	}

};

template <class T>
List<T>::List() {
	//head = NULL;
}


#endif /* LIST_H_ */
