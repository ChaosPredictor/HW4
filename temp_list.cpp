/*
 * temp_list.cpp
 *
 *  Created on: Jun 24, 2017
 *      Author: master
 */




#include <stdlib.h>
#include <memory>

//#pragma once

template <typename T>
class LinkedList;

template <typename TNode>
class LinkedListIterator
{
    friend class LinkedList<typename TNode::value_type>;
    TNode* p;
public:
    LinkedListIterator(TNode* p) : p(p) {}
    LinkedListIterator(const LinkedListIterator& other) : p(other.p) {}
    LinkedListIterator& operator=(LinkedListIterator other) { std::swap(p, other.p); return *this; }
    void operator++() { p = p->next; }
    void operator++(int) { p = p->next; }
    bool operator==(const LinkedListIterator& other) { return p == other.p; }
    bool operator!=(const LinkedListIterator& other) { return p != other.p; }
    const int& operator*() const { return p->data; }
    LinkedListIterator<TNode> operator+(int i)
    {
        LinkedListIterator<TNode> iter = *this;
        while (i-- > 0 && iter.p)
        {
            ++iter;
        }
        return iter;
    }
};

template <typename T>
class Node
{
    friend class LinkedList<T>;
    friend class LinkedListIterator<Node<T>>;
    friend class LinkedListIterator<const Node<T>>;

    Node() : next(nullptr) {}
    Node(const T &data) : data(data), next(nullptr) {}
    Node<T> *next;
    T data;
public:
    typedef T value_type;
};

template <typename T>
class LinkedList
{
    typedef Node<T> node;

    std::size_t size;
    std::unique_ptr<node> head;
    std::unique_ptr<node> tail;

    void init()
    {
        size = 0;
        head.reset(new node);
        tail.reset(new node);
        head->next = tail.get();
    }

public:
    typedef LinkedListIterator<node> iterator;
    typedef LinkedListIterator<const node> const_iterator;

    LinkedList() { init(); }

    LinkedList(const LinkedList& other)
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

    LinkedList(LinkedList&& other)
    {
        init();
        size = other.size;
        head = other.head;
        tail = other.tail;
        other.first = nullptr;
        other.size = 0;
    }

    LinkedList& operator=(LinkedList other)
    {
        swap(*this, other);
        return *this;
    }

    LinkedList& operator=(LinkedList&& other)
    {
        assert(this != &other);
        while (head->next != tail)
            remove(begin());
        head = other.head;
        tail = other.tail;
        size = other.size;
        //first = other.first;
        //other.size = 0;
        //other.first = nullptr;
        return *this;
    }

    virtual ~LinkedList()
    {
        while (head->next != tail.get())
            remove(begin());
    }

    friend void swap(LinkedList& first, LinkedList& second)
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
        node *last = head.get();
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
        return iterator(tail.get());
    }

    const_iterator end() const
    {
        return const_iterator(tail.get());
    }
};
