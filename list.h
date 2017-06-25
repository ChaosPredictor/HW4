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

	class Node;


public:

	class Iterator;

	List() {
    	head = new Node;
        tail = new Node;
        head->next = tail;
        tail->last = head;
    	//iterator = new Iterator;
    	size = 0;
	}

    bool operator==(const List& right) {
    	return true;
    }

    bool operator!=(const List& right) {
    	return false;
    }

    void insert(const T& data, Iterator iterator);

	void insert(T data) {}

	typename List<T>::Iterator begin();

	typename List<T>::Iterator end();

	void remove(Iterator& iterator);

	template<class Function>
	void sort(Function f);

	template<class Function>
	typename List<T>::Iterator find(Function f);

	int getSize();

	//TODO remove it
	void printList() {
		printf("\n\n");
		printf("size: %d\n", size);
		printf("head address: %p   tail address: %p \n", (void*)head, (void*)tail);
		Node *node = head->next;
		while(node->next != nullptr) {
			printf("node data: %d   address: %p  next adrs: %p   last adrs: %p\n", node->data, (void*)node, (void*)node->next, (void*)node->last);
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
int List<T>::getSize() {
	return size;
}

template<class T>
void List<T>::insert(const T& data, Iterator iterator) {
    Node *new_node = new Node(data);
    Node *node = head;
    //TODO redesign
    while( node->next != nullptr && node->next != iterator.ptr ) {
    	node = node->next;
    }
    Node *node_left = node;
    Node *node_right = node->next;

    node_left->next = new_node;
    new_node->last = node_left;

    new_node->next = node_right;
    node_right->last = new_node;
	size++;
}

template<class T>
template<class Function>
void List<T>::sort(Function f) {
	for (List<T>::Iterator it1 = this->begin(); it1.nextIterator() != this->end(); ++it1) {
		for (List<T>::Iterator it2 = this->begin(); it2.nextIterator() != this->end(); ++it2) {
			//printf("%d  ", *it2);
			//if ( it2.nextIterator() != this->end() ) {
			if (!(f(*it2, it2.nextData()))) {
					//printf ("y ");
				std::swap( *it2, it2.nextData() );
			}
				//else printf("n ");
			//}
		}
		//printf("\n");
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
	return Iterator(head->next);
}

template<class T>
typename List<T>::Iterator List<T>::end() {
	return Iterator(tail);
}

template<class T>
void List<T>::remove(Iterator& iterator) {
    Node *node_right = iterator.ptr->next;
    Node *node_left = iterator.ptr->last;
    node_right->last = node_left;
    node_left->next = node_right;
    size--;
}




template<class T>
class List<T>::Node {
    friend class List<T>;
    friend class List<T>::Iterator;

    Node() : next(nullptr), last(nullptr) {}
    Node(const T& data) : data(data), next(nullptr), last(nullptr) {}

    T data;
    Node *next;
    Node *last;

public:
    typedef T value_type;
};


template<class T>
class List<T>::Iterator {
    friend class List<T>;
//TODO mode ptr back to private

    T& nextData() {
    	return ptr->next->data;
    }

    Iterator nextIterator() {
    	return ptr->next;
    }

public:
	Node* ptr;

    Iterator() {
    	//List list = malloc(sizeof(*list));
    	//if (list == NULL) return NULL;
    }

    Iterator(Node* ptr) : ptr(ptr) {}

    Iterator(const Iterator& other) : ptr(other.ptr) {}

    bool operator!=(const Iterator& right) {
    	return this->ptr != right.ptr;
    }

    Iterator& operator++();

    Iterator operator++(int);

    Iterator& operator--();

    Iterator operator--(int);

    T& operator*() {
    	return ptr->data;
    }




    //const int& operator*() const {
    //	return ptr->data;
    //}

};

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



#endif /* LIST_H_ */
