/*
 * list.h
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */

#ifndef LIST_H_
#define LIST_H_

#include "Exceptions.h"

template <class T>
class List {


public:

	class Iterator;

	List();

	List(const List<T>& other);

	~List();

    bool operator==(const List& right);

    bool operator!=(const List& right);

    void insert(const T& data, Iterator iterator );

	void insert(T data);

	typename List<T>::Iterator begin();

	typename List<T>::Iterator begin() const;

	typename List<T>::Iterator end();

	typename List<T>::Iterator end() const;

	void remove(Iterator& iterator);

	template<class Function>
	void sort(Function f);

	template<class Function>
	typename List<T>::Iterator find(Function f);

	int getSize();

private:

	class Node;

	Node& lastNode();

	bool isIteratorOfList(Iterator& iterator){
		for (List<T>::Iterator it = this->begin(); it != this->end(); ++it) {
			if ( it == iterator) {
				return true;
			}
		}
		return false;
	}

	//TODO remove it
	void printList() {
		printf("\n\n");
		printf("size: %d\n", size);
		printf("head address: %p   tail address: %p \n", (void*)head, (void*)tail);
		Node *node = head;
		while(node != nullptr ) {
			printf("node data: %d   address: %p  next adrs: %p   last adrs: %p\n", *(node->data), (void*)node, (void*)node->next, (void*)node->last);
			node = node->next;
		}
	}

	//TODO remove it
	void printList() const {
		printf("\n\n");
		printf("size: %d\n", size);
		printf("head address: %p   tail address: %p \n", (void*)head, (void*)tail);
		Node *node = head;
		while(node != nullptr ) {
			printf("node data: %d   address: %p  next adrs: %p   last adrs: %p\n", *(node->data), (void*)node, (void*)node->next, (void*)node->last);
			node = node->next;
		}
	}

private:

	int size;
	Node* head;
	Node* tail;
	Iterator iterator;

};

template<class T>
List<T>::List() : size(0), head(nullptr), tail(nullptr) {}

template<class T>
List<T>::List(const List<T>& list) : size(0), head(nullptr), tail(nullptr){
	for (List<T>::Iterator it = list.begin(); it != list.end(); ++it) {
		this->insert(*it);
	}
}

template<class T>
List<T>::~List() {
	//this->printList();
	List<T>::Iterator it = this->begin();
	//int i = 0;
	while( it != this->end() ) {
		//printf("run list dict\n");
		this->remove(it);
		//this->printList();
		it = this->begin();
	}
	//delete head;
	//delete tail;
	//printf("distractor run\n");
}

template<class T>
bool List<T>::operator==(const List& right) {
	List<T>::Iterator right_iterator = right.begin();
	for (List<T>::Iterator it = begin(); it != end(); ++it) {
		if ( *right_iterator != *it ) return false;
		++right_iterator;
	}
	if ( right_iterator != right.end() ) return false;
	return true;
}

template<class T>
bool List<T>::operator!=(const List& right) {
	return (!(*this == right));
}

template<class T>
void List<T>::insert(const T& data, Iterator iterator) {
	if ( iterator != nullptr && !(this->isIteratorOfList(iterator))) throw mtm::ListExceptions::ElementNotFound();
    Node *new_node = new Node(data);
    if ( head == tail ) {
    	new_node->last = head;
    	head = new_node;
    	new_node->next = tail;
    } else if ( iterator.ptr == head ) {
    	new_node->next = head;
        Node *node_right = iterator.ptr;
    	head = new_node;
    	node_right->last = new_node;
    } else if ( iterator.ptr == tail ) {
    	new_node->next = tail;
        Node *node_left = &(this->lastNode());
        node_left->next = new_node;
        new_node->last = node_left;
    } else {
        Node *node_right = iterator.ptr;
        Node *node_left = node_right->last;

        node_left->next = new_node;
        new_node->last = node_left;

        new_node->next = node_right;
        node_right->last = new_node;
    }
	size++;
    //TODO redesign

}

template<class T>
void List<T>::insert(T data) {
	insert(data, this->tail);
}

template<class T>
int List<T>::getSize() {
	return size;
}

template<class T>
template<class Function>
void List<T>::sort(Function f) {
	for (List<T>::Iterator it1 = this->begin(); it1.getIteratorOnNextNode() != this->end(); ++it1) {
		for (List<T>::Iterator it2 = this->begin(); it2.getIteratorOnNextNode() != this->end(); ++it2) {
			if (!(f(*it2, it2.nextNodeData()))) {
				std::swap( *it2, it2.nextNodeData() );
			}
		}
	}
}

template<class T>
template<class Function>
typename List<T>::Iterator List<T>::find(Function f) {
	for (List<T>::Iterator it = this->begin(); it != this->end(); ++it) {
		if (f(*it)) {
			return it;
		}
	}
	return this->end();
}

template<class T>
typename List<T>::Iterator List<T>::begin() {
	return Iterator(head);
}
//TODO maybe remove
template<class T>
typename List<T>::Iterator List<T>::begin() const {
	return Iterator(head);
}

template<class T>
typename List<T>::Iterator List<T>::end() {
	return Iterator(tail);
}
//TODO maybe remove
template<class T>
typename List<T>::Iterator List<T>::end() const {
	return Iterator(tail);
}

template<class T>
void List<T>::remove(Iterator& iterator) {
	if (!(this->isIteratorOfList(iterator))) throw mtm::ListExceptions::ElementNotFound();
	Node *node_right;
	Node *node_left;
	if( iterator.ptr == head && iterator.ptr->next == tail ) {
		head = tail;
	} else if ( iterator.ptr == head ) {
		head = iterator.ptr->next;
		iterator.ptr->next->last = nullptr;
	} else {
    	node_right = iterator.ptr->next;
        node_left = iterator.ptr->last;
        node_right->last = node_left;
        node_left->next = node_right;
	}

	delete iterator.ptr;
    size--;
}

template<class T>
typename List<T>::Node& List<T>::lastNode() {
	Node *node = head;
	while(node != nullptr && node->next != tail) {
		node = node->next;
	}
	return *node;
}



template<class T>
class List<T>::Node {
    friend class List<T>;

    friend class List<T>::Iterator;

    Node();
    Node(const T& data);
    ~Node();

    T *data;
    Node *next;
    Node *last;

public:
    T& getData();

    typedef T value_type;
};

template<class T>
List<T>::Node::Node() : next(nullptr), last(nullptr) {}

template<class T>
List<T>::Node::Node(const T& data) : data(new T(data)), next(nullptr), last(nullptr) {}

template<class T>
List<T>::Node::~Node() {
	if ( data != nullptr ) delete data;
}

template<class T>
T& List<T>::Node::getData() {
	return *data;
}



template<class T>
class List<T>::Iterator {
    friend class List<T>;

	Node* ptr;

public:

    Iterator();
    Iterator(Node* ptr);
    Iterator(const Iterator& other);

    bool operator==(const Iterator& right);

    bool operator!=(const Iterator& right);

    Iterator& operator++();

    Iterator operator++(int);

    Iterator& operator--();

    Iterator operator--(int);

    T& operator*();

private:
    T& nextNodeData();

    Iterator getIteratorOnNextNode();

    Node nextNode();
};

template<class T>
List<T>::Iterator::Iterator() {}

template<class T>
List<T>::Iterator::Iterator(Node* ptr) : ptr(ptr) {}

template<class T>
List<T>::Iterator::Iterator(const Iterator& other) : ptr(other.ptr) {}

template<class T>
bool List<T>::Iterator::operator==(const Iterator& right) {
	return this->ptr == right.ptr;
}

template<class T>
bool List<T>::Iterator::operator!=(const Iterator& right) {
	return (!( *this == right ));
	//return this->ptr != right.ptr;
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
	ptr = ptr->next;
	return *this;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
	Iterator result = *this;
	++*this;
	return result;
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
	ptr = ptr->last;
	return *this;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
	Iterator result = *this;
	--*this;
	return result;
}

template<class T>
T& List<T>::Iterator::operator*() {
	if ( ptr == nullptr ) throw mtm::ListExceptions::ElementNotFound();
	return ptr->getData();
}

template<class T>
T& List<T>::Iterator::nextNodeData() {
	return *(this->getIteratorOnNextNode());
}

template<class T>
typename List<T>::Node List<T>::Iterator::nextNode() {
	return *(this->getIteratorOnNextNode().ptr);
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::getIteratorOnNextNode() {
	return ptr->next;
}


#endif /* LIST_H_ */
