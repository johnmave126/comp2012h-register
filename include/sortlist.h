/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * sortlist.h
 *
 * header file for a sorted, douby-linked list
 */

#ifndef _SORTLIST_H
#define _SORTLIST_H

#include "register_common.h"
#include <functional>
#include <stdexcept>

using std::less;
using std::runtime_error;

//Declaration of sortlist
template<typename T, class Compare = less<T> >
class SortList {
    public:
        //Declare iterator class
        class Iterator;
        
        /* default constructor/destructor */
        SortList();
        ~SortList();
        
        /* conversion constructor */
        explicit SortList(const Compare& _comp);

        /* copy constructor */
        SortList(const SortList<T, Compare>& q);
        
        /* assign operator */
        SortList<T, Compare>& operator=(const SortList<T, Compare>& q);
        
        /*
         * isEmpty
         *
         * return true if the sortlist is empty
         */
        inline bool isEmpty() const;
        
        /*
         * size
         *
         * return the size of the sortlist
         */
        inline int size() const;
        
        /*
         * insert
         *
         * item: the item to add
         *
         * insert the item into the sortlist
         */
        inline void insert(T item);

        /*
         * remove
         *
         * delete all the item meet requirement in sortlist
         * null version, to accompany the function below
         */
        int remove() {
            return remove<ReturnTrue<T> >();
        }

        /*
         * remove
         *
         * _comp: a comparison function indicating the item to delete
         *
         * delete all the item meet requirement in sortlist
         * return the number of items deleted
         */
        template<class CompRemove>
        int remove(const CompRemove& _comp = CompRemove());
        
        /*
         * iterator
         *
         * return an iterator that can iterate from front to end
         */
        Iterator iterator() const;
        
    protected:
        //Declare nested class Node
        class Node;

    private:    
        //The pseudo head
        Node *head;
        
        //The pseudo end
        Node *end;
        
        //The size of sortlist
        int length;

        // < operator
        Compare comparator;
};

//Iterator class
template<typename T, class Compare>
class SortList<T, Compare>::Iterator {
    public:
        /* default constructor/destructor */
        Iterator();
        virtual ~Iterator();
        
        /* conversion constructor
         *
         * The iterator will point to the first element of SortList
         * If the sortlist is empty, point to the first
         */
        Iterator(const SortList&);
        
        /* conversion constructor
         *
         * The iterator will point to the node specified
         */
        Iterator(Node&);
        
        /* copy constructor */
        Iterator(const Iterator&);
        
        /* assign operator */
        Iterator& operator=(const Iterator&);
        
        /* dereference operators
         *
         * non-const version
         * throw runtime_error if the node pointed to belongs to
         * a sortlist destroyed, or the iterator points to no node
         */
        T& operator*();
        T* operator->();
        
        /* dereference operators
         *
         * const version
         * throw runtime_error if the node pointed to belongs to
         * a sortlist destroyed, or the iterator points to no node
         */
        T& operator*() const;
        T* operator->() const;
        
        /* comparison operators
         *
         * const to const comparison
         * if any of the iterator compared is not initialized or not valid
         * false will be returned
         */
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
        
        /* comparison operators
         *
         * const to non-const comparison
         * if any of the iterator compared is not initialized or not valid
         * false will be returned
         */
        bool operator==(Iterator&) const;
        bool operator!=(Iterator&) const;
        
        /* comparison operators
         *
         * non-const to const comparison
         * if any of the iterator compared is not initialized or not valid
         * false will be returned
         */
        bool operator==(const Iterator&);
        bool operator!=(const Iterator&);
        
        /* comparison operators
         *
         * non-const to non-const comparison
         * if any of the iterator compared is not initialized or not valid
         * false will be returned
         */
        bool operator==(Iterator&);
        bool operator!=(Iterator&);
        
        /* prefix/postfix ++ operator
         *
         * throw runtime_error if the node pointed to belongs to
         * a sortlist destroyed, or the iterator points to no node.
         * If the iterator comes to the end of the sortlist, there 
         * will be no change to the iterator.
         */
        virtual Iterator& operator++();
        virtual Iterator operator++(int);
        
        /* prefix/postfix -- operator
         *
         * throw runtime_error if the node pointed to belongs to
         * a sortlist destroyed, or the iterator points to no node.
         * If the iterator comes to the beginning of the sortlist, there 
         * will be no change to the iterator.
         */
        virtual Iterator& operator--();
        virtual Iterator operator--(int);
        
    protected:
        typedef Node Node_A;

        /*
         * findValid
         *
         * node: the node to start finding
         *
         * return the address of the nearest valid node found
         * NULL for none found.
         */
        virtual Node* findValid() const;
        
        /*
         * shiftNode
         *
         * node: the node to change to
         *
         * change the node the iterator pointing to to node
         */
        inline void shiftNode(Node* node);
        
        //Pointer to element
        Node *elem;
};

//Node for double linked list
//All members are public for sortlist to modify
//These details are hided to outside classes
template<typename T, class Compare>
class SortList<T, Compare>::Node {
    public:
        /* default constructor/destructor */
        Node();
        ~Node();
        
        /* conversion constructor */
        Node(const T&);
        
        /* copy constructor */
        Node(const Node&);
        
        /* assign operator */
        Node& operator=(const Node&);
        
        /*
         * decCnt
         *
         * node: the node to be decreased count
         *
         * static function
         * Decrease reference count of a node. Free the memory if necessary
         */
        static void decCnt(Node *node);
        
        //Store the data
        T *data;
        //Previous and Next node
        Node *prev;
        Node *next;
        //Reference count
        int cnt;
};

//Implementation begins
/* SortList Node */
template<typename T, class Compare>
SortList<T, Compare>::Node::Node()
:data(NULL), prev(NULL), next(NULL),
 cnt(0) {
}

template<typename T, class Compare>
SortList<T, Compare>::Node::~Node() {
    if(data) {
        delete data;
    }
}

template<typename T, class Compare>
SortList<T, Compare>::Node::Node(const T& t)
:data(new T(t)), prev(NULL), next(NULL),
 cnt(0) {
}

template<typename T, class Compare>
SortList<T, Compare>::Node::Node(const SortList<T, Compare>::Node& t)
:data(new T(*(t.data))), prev(NULL), next(NULL),
 cnt(0) {
}

template<typename T, class Compare>
typename SortList<T, Compare>::Node& SortList<T, Compare>::Node::operator=(const SortList<T, Compare>::Node& t) {
    //Only copy data, leave prev/next and other stuff not changed
    data = new T(t.data);
    return *this;
}

template<typename T, class Compare>
void SortList<T, Compare>::Node::decCnt(SortList<T, Compare>::Node *node) {
    node->cnt--;
    if(node->cnt == 0) {
        //Recycle the memory
        if(node->data) {
            //Free data space
            delete node->data;
            node->data = NULL;
        }
        //Recycle the prev node if applicable
        if(node->prev) {
            decCnt(node->prev);
        }
        //Recycle the next node if applicable
        if(node->next) {
            decCnt(node->next);
        }
        //Delete the node
        delete node;
    }
}

/* SortList Iterator */
template<typename T, class Compare>
SortList<T, Compare>::Iterator::Iterator()
:elem(NULL) {
}

template<typename T, class Compare>
SortList<T, Compare>::Iterator::~Iterator() {
    if(elem) {
        //Decrement reference count
        Node::decCnt(elem);
    }
}

template<typename T, class Compare>
SortList<T, Compare>::Iterator::Iterator(const SortList<T, Compare>& q)
:elem(q.iterator().elem) {
    //Increace reference count
    elem->cnt++;
}

template<typename T, class Compare>
SortList<T, Compare>::Iterator::Iterator(SortList<T, Compare>::Node& p)
:elem(&p) {
    //Increace reference count
    elem->cnt++;
}

template<typename T, class Compare>
SortList<T, Compare>::Iterator::Iterator(const SortList<T, Compare>::Iterator& itr)
:elem(itr.findValid()) {
    if(elem) {
        elem->cnt++;
    }
}

template<typename T, class Compare>
typename SortList<T, Compare>::Iterator& SortList<T, Compare>::Iterator::operator=(const SortList<T, Compare>::Iterator& itr) {
    if(elem) {
        //Decrement reference count
        Node::decCnt(elem);
    }
    //Copy and increase reference count
    elem = itr.findValid();
    if(elem) {
        elem->cnt++;
    }
    return (*this);
}

template<typename T, class Compare>
T& SortList<T, Compare>::Iterator::operator*() {
    if(!elem) {
        throw runtime_error("Uninitialized iterator!");
    }
    Node* t = findValid();
    if(!t) {
        //Clear the iterator
        Node::decCnt(elem);
        elem = NULL;
        throw runtime_error("Iterator no longer valid!");
    }
    shiftNode(t);
    if(!elem->prev && elem->next) {
        //head of a sortlist
        //Indicate empty sortlist
        throw runtime_error("Empty sortlist!");
    }
    if(!elem->next && elem->prev) {
        //end of a sortlist
        throw runtime_error("End of sortlist!");
    }
    return *(elem->data);
}

template<typename T, class Compare>
T* SortList<T, Compare>::Iterator::operator->() {
    //Reuse operator*
    return &(*(*this));
}

template<typename T, class Compare>
T& SortList<T, Compare>::Iterator::operator*() const{
    if(!elem) {
        throw runtime_error("Uninitialized iterator!");
    }
    Node* t = findValid();
    if(!t || elem != t) {
        //Not valid or pointed to a invalid one
        throw runtime_error("Iterator no longer valid!");
    }
    if(!elem->prev && elem->next) {
        //head of a sortlist
        //Indicate empty
        throw runtime_error("Empty sortlist!");
    }
    if(!elem->next && elem->prev) {
        //end of a sortlist
        throw runtime_error("End of sortlist!");
    }
    return *(elem->data);
}

template<typename T, class Compare>
T* SortList<T, Compare>::Iterator::operator->() const{
    //Reuse operator*
    return &(*(*this));
}

template<typename T, class Compare>
bool SortList<T, Compare>::Iterator::operator==(const SortList<T, Compare>::Iterator& itr) const {
    if(!elem || !itr.elem) {
        return false;
    }
    Node* t1 = findValid();
    Node* t2 = itr.findValid();
    if(!t1 || !t2 || t1 != elem || t2 != itr.elem) {
        return false;
    }
    return t1 == t2;
}

template<typename T, class Compare>
bool SortList<T, Compare>::Iterator::operator!=(const SortList<T, Compare>::Iterator& itr) const {
    return !((*this) == itr);
}

template<typename T, class Compare>
bool SortList<T, Compare>::Iterator::operator==(SortList<T, Compare>::Iterator& itr) const {
    if(!elem || !itr.elem) {
        return false;
    }
    Node* t1 = findValid();
    Node* t2 = itr.findValid();
    //Change the current node if needed
    itr.shiftNode(t2);
    if(!t1 || !t2 || t1 != elem) {
        return false;
    }
    return t1 == t2;
}

template<typename T, class Compare>
bool SortList<T, Compare>::Iterator::operator!=(SortList<T, Compare>::Iterator& itr) const {
    return !((*this) == itr);
}

template<typename T, class Compare>
bool SortList<T, Compare>::Iterator::operator==(const SortList<T, Compare>::Iterator& itr) {
    if(!elem || !itr.elem) {
        return false;
    }
    Node* t1 = findValid();
    Node* t2 = itr.findValid();
    //Change the current node if needed
    shiftNode(t1);
    if(!t1 || !t2 || t2 != itr.elem) {
        return false;
    }
    return t1 == t2;
}

template<typename T, class Compare>
bool SortList<T, Compare>::Iterator::operator!=(const SortList<T, Compare>::Iterator& itr) {
    return !((*this) == itr);
}

template<typename T, class Compare>
bool SortList<T, Compare>::Iterator::operator==(SortList<T, Compare>::Iterator& itr) {
    if(!elem || !itr.elem) {
        return false;
    }
    Node* t1 = findValid();
    Node* t2 = itr.findValid();
    //Change the current node if needed
    shiftNode(t1);
    itr.shiftNode(t2);
    if(!t1 || !t2) {
        return false;
    }
    return t1 == t2;
}

template<typename T, class Compare>
bool SortList<T, Compare>::Iterator::operator!=(SortList<T, Compare>::Iterator& itr) {
    return !((*this) == itr);
}

template<typename T, class Compare>
typename SortList<T, Compare>::Iterator& SortList<T, Compare>::Iterator::operator++() {
    if(!elem) {
        throw runtime_error("Uninitialized iterator!");
    }
    if(!elem->prev && elem->next) {
        //head of a sortlist
        //sortlist once empty
        if(elem->next->next) {
            //not empty
            shiftNode(elem->next->next);
        }
    }
    Node* t = findValid();
    //Shift to valid node
    shiftNode(t);
    if(!elem) {
        throw runtime_error("Iterator no longer valid!");
    }
    if(!elem->next && elem->prev) {
        //end of the sortlist
        throw runtime_error("At the end of the sortlist!");
    }
    if(!elem->data) {
        //head of sortlist
        //sortlist is empty
        throw runtime_error("Empty sortlist!");
    }
    //Move to next
    shiftNode(elem->next);
    return (*this);
}

template<typename T, class Compare>
typename SortList<T, Compare>::Iterator SortList<T, Compare>::Iterator::operator++(int) {
    //Reuse prefix ++
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T, class Compare>
typename SortList<T, Compare>::Iterator& SortList<T, Compare>::Iterator::operator--() {
    if(!elem) {
        throw runtime_error("Uninitialized iterator!");
    }
    Node* t = findValid();
    //Shift to valid node
    shiftNode(t);
    if(!elem) {
        throw runtime_error("Iterator no longer valid!");
    }
    if(!elem->prev && elem->next) {
        //head of sortlist
        //sortlist is empty
        throw runtime_error("Empty sortlist!");
    }
    if(!elem->prev->prev) {
        //beginning of the sortlist
        throw runtime_error("At the beginning of the sortlist!");
    }
    //Move to previous
    do {
        shiftNode(elem->prev);
        t = findValid();
    }while(t != elem && t->prev->prev);
    return (*this);
}

template<typename T, class Compare>
typename SortList<T, Compare>::Iterator SortList<T, Compare>::Iterator::operator--(int) {
    //Reuse prefix --
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

template<typename T, class Compare>
typename SortList<T, Compare>::Node* SortList<T, Compare>::Iterator::findValid() const {
    if(elem->data) {
        //Valid
        return elem;
    }
    if(!elem->next && elem->prev) {
        //End of sortlist
        //preserve
        return elem;
    }
    Node* t = elem;
    //Iterate forward
    while(!t->data && t->next) {
        t = t->next;
    }
    if(t->data) {
        //Valid
        return t;
    }
    //Now t->next is null
    if(!t->prev) {
        //destroyed sortlist
        return NULL;
    }
    //End of sortlist
    //Go backwards
    return t->prev;
}

template<typename T, class Compare>
inline void SortList<T, Compare>::Iterator::shiftNode(SortList<T, Compare>::Node* node) {
    if(node) {
        //Shift to a existing node
        //Thread safety
        node->cnt++;
        Node::decCnt(elem);
        elem = node;
    }
    else {
        //Release current element
        Node::decCnt(elem);
        elem = NULL;
    }
}

/* SortList */
template<typename T, class Compare>
SortList<T, Compare>::SortList()
:head(new Node()), end(new Node()),
 length(0), comparator(Compare()) {
    //Generate an empty list
    head->next = end;
    end->prev = head;
    head->cnt++;
    end->cnt++;
}

template<typename T, class Compare>
SortList<T, Compare>::~SortList() {
    Node *t = head;
    Node *p;
    while(t) {
        p = t;
        t = t->next;
        //Make the node independent
        p->prev = NULL;
        p->next = NULL;
        //Free the data
        if(p->data) {
            delete p->data;
            p->data = NULL;
        }
        //Decrease the reference count
        Node::decCnt(p);
    }
}

template<typename T, class Compare>
SortList<T, Compare>::SortList(const SortList<T, Compare>& q)
:head(new typename SortList<T, Compare>::Node()),
 end(new typename SortList<T, Compare>::Node()),
 length(0) {
    Node *t;
    for(t = q.head->next; t->next; t = t->next) {
        //Iterate over the list to do deep copy
        insert(*(t->data));
    }
}

template<typename T, class Compare>
SortList<T, Compare>::SortList(const Compare& _comp)
:head(new Node()), end(new Node()),
 length(0), comparator(_comp) {
    //Generate an empty list
    head->next = end;
    end->prev = head;
    head->cnt++;
    end->cnt++;
}

template<typename T, class Compare>
SortList<T, Compare>& SortList<T, Compare>::operator=(const SortList<T, Compare>& q) {
    Node *t;
    //Empty the sortlist
    remove();
    comparator = q.comparator;
    for(t = q.head->next; t->next; t = t->next) {
        //Iterate over the list to do deep copy
        insert(*(t->data));
    }
    return (*this);
}

template<typename T, class Compare>
inline bool SortList<T, Compare>::isEmpty() const {
    return head->next == end;
}

template<typename T, class Compare>
inline int SortList<T, Compare>::size() const {
    return length;
}

template<typename T, class Compare>
inline void SortList<T, Compare>::insert(T item) {
    Node *t = new Node(item);
    Node *p = head->next;
    //Increase reference count
    t->cnt++;
    //Iterate through the list
    while(p != end && comparator(*(p->data), item)) {
        p = p->next;
    }
    //Insert
    t->next = p;
    t->prev = p->prev;
    t->prev->next = t;
    p->prev = t;
    //Increase size
    length++;
}

template<typename T, class Compare>
template<class CompRemove>
int SortList<T, Compare>::remove(const CompRemove& _comp) {
    Node *t, *p;
    int cnt = 0;
    if(isEmpty()) {
        return 0;
    }
    //Iterate through the list
    t = head->next;
    while(t != end) {
        p = t;
        t = t->next;
        if(_comp(*(p->data))) {
            //Make link
            p->prev->next = t;
            t->prev = p->prev;
            //Increase reference count
            p->prev->cnt++;
            t->cnt++;
            delete p->data;
            p->data = NULL;
            Node::decCnt(p);
            //Decrese size
            length--;
            cnt++;
        }
    }
    return cnt;
}

template<typename T, class Compare>
typename SortList<T, Compare>::Iterator SortList<T, Compare>::iterator() const {
    if(isEmpty()) {
        return Iterator(*head);
    }
    return Iterator(*(head->next));
}

#endif
