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

	//template <class TNode>
	class Iterator {
		Iterator();
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
