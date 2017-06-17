/*
 * list.h
 *
 *  Created on: Jun 16, 2017
 *      Author: master
 */

#ifndef LIST_H_
#define LIST_H_

#include <memory>

template <typename T>
class List;

//template <typename TNode>


template <typename T>
class Node
{
    friend class List<T>;
    //friend class ListIterator<Node<T>>;
    //friend class ListIterator<const Node<T>>;

    Node() : next(nullptr) {}
    Node(const T &data) : data(data), next(nullptr) {}
    Node<T> *next;
    T data;
public:
    typedef T value_type;
};

template <typename T>
class List
{
    typedef Node<T> node;

    std::size_t size;
    node *head = nullptr;
    node *tail = nullptr;
    node *first = nullptr;



    //std::unique_ptr<node> head;
    //std::unique_ptr<node> tail;
    //std::unique_ptr<node> first;





    void init()
    {
        size = 0;
        head.reset(new node);
        tail.reset(new node);
        head->next = tail.get();
    }

public:

    class Iterator {
        //friend class List<typename TNode::value_type>;
        node* p;
    public:
        Iterator(node* p) : p(p) {}
        Iterator(const Iterator& other) : p(other.p) {}
        Iterator operator=(Iterator other) { std::swap(p, other.p); return *this; }
        Iterator& operator++();
        Iterator& operator++(int) { p = p->next; }
        Iterator operator--() { p = p->next; }
        Iterator& operator--(int) { p = p->next; }

        bool operator==(const Iterator& other) { return p == other.p; }
        bool operator!=(const Iterator& other) { return p != other.p; }
        //const int& operator*() const { return p->data; }
        Iterator operator+(int i)
        {
            Iterator iter = *this;
            while (i-- > 0 && iter.p)
            {
                ++iter;
            }
            return iter;
        }
	    T& operator*();
	    const T& operator*() const { return 1; }

    };


    typedef Iterator iterator;
    typedef Iterator const const_iterator;

    //typedef ListIterator<const node> const_iterator;

    List() { init(); }

    List(const List& other)
    {
        init();
        const_iterator i = other.begin();
        while (i != other.end())
        {
            add(*i);
            i++;
        }

        head.reset(other.head.get());
        tail.reset(other.tail.get());
    }

    List(List&& other)
    {
        init();
        size = other.size;
        head = other.head;
        tail = other.tail;
        other.first = nullptr;
        other.size = 0;
    }

    List& operator=(List other)
    {
        swap(*this, other);
        return *this;
    }

    List& operator=(List&& other)
    {
        assert(this != &other);
        while (head->next != tail)
        	printf("TODO something");
            //remove(begin());
        head = other.head;
        tail = other.tail;
        size = other.size;
        first = other.first;
        other.size = 0;
        other.first = nullptr;
        return *this;
    }

    virtual ~List()
    {
        while (head->next != tail)
        	printf("TODO something");
            //remove(begin());
    }

	bool operator==(List second) {
		return true;
	}

	bool operator!=(List second) {
		return false;
}

    friend void swap(List& first, List& second)
    {
        std::swap(first.size, second.size);
        std::swap(first.head, second.head);
        std::swap(first.tail, second.tail);
    }

    void add(const T &value)
    {
        node *first = new node(value);
        first->next = head->next;
        head->next = first;
        size++;
    }

    void remove(iterator& removeIter)
    {
        node *last = head;
        iterator i = begin();

        while (i != removeIter)
        {
            last = i.p;
            ++i;
        }

        if (i != end())
        {
            last->next = i.p->next;
            size--;
            delete i.p;
        }
    }

    const int getSize()
    {
        return size;
    }

    void insert(const T &value, iterator it)
    {
        node *first = new node(value);
        first->next = head->next;
        head->next = first;
        size++;
    }

    void insert(const T &value)
    {
        node *first = new node(value);
        tail->next = first;
        size++;
    }

    iterator begin()
    {
        return iterator(head->next);
    }

    const_iterator begin() const
    {
        return const_iterator(head->next);
    }

    iterator end()
    {
        return iterator(tail);
    }

    const_iterator end() const
    {
        return const_iterator(tail);
    }

	template<class Function>
	void sort(Function f);

	template<class Function>
	iterator find(Function f);
};


#endif /* LIST_H_ */
