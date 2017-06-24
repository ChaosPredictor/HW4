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


	//typedef Iterator iterator;

	List() {
    	head = new Node;
        tail = new Node;
        head->next = tail;
    	//iterator = new Iterator;
    	size = 0;
	}

    bool operator==(const List& right) {
    	return true;
    }

    bool operator!=(const List& right) {
    	return false;
    }

    void insert(const T& data, Iterator iterator) {
        Node *new_node = new Node(data);
        Node *node = head;
        while( node->next != nullptr && node->next != iterator.ptr ) {
        	node = node->next;
        }
        node->next = new_node;
        new_node->next = iterator.ptr;
    	size++;
    }

	void insert(T data) {}

	/*Iterator end() {
		//Node node = iterator->ptr;
		//while ( node.next != nullptr) {
		//	node = node.next;
		//}
		//iterator->ptr = node.next;
		//return iterator;
		Node* node = tail;
		return Iterator(node);
	}*/


	typename List<T>::Iterator begin();

	typename List<T>::Iterator end();

	void remove(Iterator& iterator) {}

	template<class Function>
	void sort(Function f);

	template<class Function>
	Iterator find(Function f){

		return Iterator();
		//TODO in case of not found move to end
	}

	int getSize() {
		return size;
	}


	void printList() {
		printf("\n\n");
		printf("size: %d\n", size);
		printf("head address: %p   tail address: %p \n", (void*)head, (void*)tail);
		Node *node = head->next;
		while(node->next != nullptr) {
			printf("node data: %d   address: %p   next adrs: %p \n", node->data, (void*)node, (void*)node->next);
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
typename List<T>::Iterator List<T>::begin() {
	return Iterator(head->next);
}


template<class T>
typename List<T>::Iterator List<T>::end() {
	return Iterator(tail);
}





template<class T>
class List<T>::Node {
    friend class List<T>;
    friend class List<T>::Iterator;
    //friend class LinkedListIterator<const Node<T>>;

    Node() : next(nullptr) {}

    T data;
    Node *next;

public:
    Node(const T& data) : data(data), next(nullptr) {}
    typedef T value_type;
};


template<class T>
class List<T>::Iterator {
    friend class List<T>;

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

    Iterator& operator++() {
		ptr = ptr->next;
		return *this;
    }

    Iterator& operator++(int) {
		//ptr = ptr->next;
		return *this;
    }

    Iterator& operator--() {
		//ptr = ptr->next;
		return *this;
    }

    Iterator& operator--(int) {
		//ptr = ptr->next;
		return *this;
    }

    T& operator*() {
    	//Node node = ptr;
    	return ptr->data;
    }

    const int& operator*() const {
    	return ptr->data;
    }

};




#endif /* LIST_H_ */
