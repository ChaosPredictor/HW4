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

	List();

	~List();

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

	Node& lastNode() {
		Node *node = head;
		while(node != nullptr && node->next != tail) {
			node = node->next;
		}
		return *node;
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

private:

	int size;
	Node* head;
	Node* tail;
	Iterator iterator;

};



template<class T>
List<T>::List() {
	//Node* head;
	tail = nullptr;
	//head = new *Node;
    //tail = new *Node;
    head = tail;
    //tail->last = head;
	//iterator = new Iterator;
	size = 0;
}

template<class T>
List<T>::~List() {
	this->printList();
	List<T>::Iterator it = this->begin();
	int i = 0;
	while( i < 5 && it != this->end() ) {
		printf("run list dict\n");
		this->remove(it);
		this->printList();
		it = this->begin();
		i++;
	}
	//delete head;
	//delete tail;
	printf("distractor run\n");
}


template<class T>
int List<T>::getSize() {
	return size;
}

template<class T>
void List<T>::insert(const T& data, Iterator iterator) {
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
	return Iterator(head);
}

template<class T>
typename List<T>::Iterator List<T>::end() {
	return Iterator(tail);
}

template<class T>
void List<T>::remove(Iterator& iterator) {
	Node *node_right;
	Node *node_left;
	if( iterator.ptr == head && iterator.ptr->next == tail ) {
		head = tail;
	} else if ( iterator.ptr == head ) {
		head = iterator.ptr->next;
		iterator.ptr->next->last = nullptr;
	} else  if( iterator.ptr->next == tail) {
    	node_left = iterator.ptr->last;
    	node_left->next = tail;
    } else if( iterator.ptr->last == head) {
    	node_right = iterator.ptr->next;
    	head = node_right;
    } else {
    	Node *node_right = iterator.ptr->next;
        Node *node_left = iterator.ptr->last;
        node_right->last = node_left;
        node_left->next = node_right;
    }
	delete iterator.ptr;
    size--;
}




template<class T>
class List<T>::Node {
    friend class List<T>;
    friend class List<T>::Iterator;

    Node() : next(nullptr), last(nullptr) {}
    Node(const T& data) : data(new T(data)), next(nullptr), last(nullptr) {}
    ~Node() {
    	printf("dictor Node\n");
    	//delete last;
    	//delete next;
    	if ( data != nullptr ) delete data;
    }

    T *data;
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
    	return *(ptr->next->data);
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

    bool operator!=(const Iterator& right);

    Iterator& operator++();

    Iterator operator++(int);

    Iterator& operator--();

    Iterator operator--(int);

    T& operator*();


};

template<class T>
bool List<T>::Iterator::operator!=(const Iterator& right) {
	return this->ptr != right.ptr;
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
	return *(ptr->data);
}

#endif /* LIST_H_ */
