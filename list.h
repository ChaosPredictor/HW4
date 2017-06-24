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

	//Node createNode() {
	//	Node
	//	return node
	//}

	//typedef struct node_t *Node;


	//template <typename T>
	class Node
	{
	    friend class List<T>;
	    //friend class LinkedListIterator<Node<T>>;
	    //friend class LinkedListIterator<const Node<T>>;

	    Node() : next(nullptr) {}
	    Node(const T& data) : data(data), next(nullptr) {}
	    Node *next;
	    T data;
	public:
	    typedef T value_type;
	};


public:

	class Iterator {
	    friend class List<T>;

		Node* ptr;

	public:
	    Iterator() {
	    	//List list = malloc(sizeof(*list));
	    	//if (list == NULL) return NULL;
	    }

	    Iterator(Node* ptr) : ptr(ptr) {}

	    Iterator(const Iterator& other) : ptr(other.ptr) {}

	    bool operator!=(const Iterator& right) {
	    	return false;
	    }

	    Iterator& operator++() {
			//ptr = ptr->next;
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




	//typedef Iterator iterator;

	List() {
    	head = new Node;
        tail = head;
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
        Node *node = head->next;
        while( node->next != iterator.ptr ) {
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


	typename List<T>::Iterator end() {
		//Node node = iterator->ptr;
		//while ( node.next != nullptr) {
		//	node = node.next;
		//}
		//iterator->ptr = node.next;
		//return iterator;
		//Node* node = tail;
		return Iterator(tail);
	}

	Iterator begin() {
		Iterator it;
		return it;
	}

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

private:
	//struct node_t {
	//	T* data;
	//	struct node_t* next;
	//};

	int size;
	Node* head;
	Node* tail;
	Iterator iterator;

};

#endif /* LIST_H_ */
