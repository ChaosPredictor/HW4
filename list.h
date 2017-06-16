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


	struct Node {
		T data;
		Node *next;
	};



public:
	List();

	void insert(T value, T* place);
	T* end();
};

template <class T>
List<T>::List() {
	//head = NULL;
}


template <class T>
void insert(T value, T* place) {

}

template <class T>
T* end() {

}


#endif /* LIST_H_ */
