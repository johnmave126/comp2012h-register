/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * hashmap.h
 *
 * header file for a simple hashmap
 */

#ifndef _HASHMAP_H
#define _HASHMAP_H

#include "register_common.h"
#include "sortlist.h"
#include <functional>
#include <stdexcept>

using std::less;
using std::runtime_error;

//Declaration of Hashmap
template<typename Key, typename Value, class Hasher, class Compare = less<Value> >
class Hashmap {
    public:
        class Iterator;
        class Iterator_All;

        /* default constructor/destructor */
        Hashmap();
        ~Hashmap();

        /* conversion constructor */
        explicit Hashmap(Hasher _hash, int _slot = 503, Compare _comp = Compare());

        /* copy constructor */
        Hashmap(const Hashmap&);

        /* assign operator */
        Hashmap<Key, Value, Hasher, Compare>& operator=(const Hashmap<Key, Value, Hasher, Compare>&);

        /* subscript operator */
        //Return NULL if not found. Return the first one if multiple instances.
        Value* operator[](const Key&);

        /*
         * isEmpty
         *
         * return true if the hashmap is empty
         */
        inline bool isEmpty() const;
        
        /*
         * size
         *
         * return the size of the hashmap
         */
        inline int size() const;

        /*
         * insert
         *
         * hashKey: the key of the item
         * item: the item to insert
         *
         * insert the item into the hashmap
         */
        void insert(const Key& hashKey, const Value& item);

        /*
         * remove
         *
         * hashKey: the key of the items
         *
         * delete all the item meet requirement in Hashmap
         * a simpler version to accompany the function below
         */
        int remove(const Key& hashKey) {
            return remove<ReturnTrue<Value> >(hashKey);
        }

        /*
         * remove
         *
         * hashKey: the key of the items
         *
         * delete all the item meet requirement in Hashmap
         * a simpler version to accompany the function below
         */
        template<class CompRemove>
        int remove(const Key& hashKey) {
            CompRemove t = CompRemove();
            return remove<CompRemove>(hashKey, t);
        }

        /*
         * remove
         *
         * hashKey: the key of the items
         * _comp: a comparison function indicating the item to deletes
         *
         * delete all the item meet requirement in Hashmap
         * return the number of items deleted
         */
        template<class CompRemove>
        int remove(const Key& hashKey, CompRemove& _comp);

        /*
         * query
         *
         * hashKey: the key of the items
         *
         * return an iterator to iterate all the items of hashKey
         * The iteration must be wrapped by a try-catch
         */
        Iterator query(const Key& hashKey) const;

        /*
         * apply
         *
         * hashKey: the key of the items
         * _cbk: the callback to call when item found
         *
         * apply the callback to all the items with hashKey
         */
        template<class Callback>
        void apply(const Key& hashKey, Callback& _cbk) const;

        /*
         * dump
         *
         * dump all the record in order
         */
        Iterator_All dump() const;

    private:
        //Node
        struct Node {
            Key k;
            Value val;
        };

        //Comparator for Node
        class _Compare {
            public:
                _Compare() {}
                _Compare(const Compare &_cmp): cmp(_cmp) {}
                _Compare& operator=(const _Compare& c) {
                    cmp = c.cmp;
                    return (*this);
                }
                bool operator()(const Node &a, const Node &b) {
                    return cmp(a.val, b.val);
                }
                bool operator()(const Value &a, const Value &b) {
                    return cmp(a, b);
                }
            private:
                Compare cmp;
        };
        _Compare comp;

        //Serve for remove
        template<class CompRemove>
        class _CustomRemove {
            public:
                _CustomRemove(const Key& hashKey, const CompRemove& _comp)
                :k(hashKey), cmp(_comp) {}
                bool operator()(const Node& n) {return (n.k == k) && cmp(n.val);}
            private:
                Key k;
                CompRemove  cmp;
        };

        //The buckets
        SortList<Node, _Compare> **arr_bucket;

        //The number of slots
        int slotn;

        //The size of Hashmap
        int length;

        //The hash function
        Hasher hashFunctoin;
};

//The Iterator
template<typename Key, typename Value, class Hasher, class Compare>
class Hashmap<Key, Value, Hasher, Compare>::Iterator: public SortList<Node, _Compare>::Iterator {
    public:
        /* default constructor/destructor */
        Iterator();
        virtual ~Iterator();

        /* conversion constructor
         *
         * The iterator will point to the first element of SortList
         * If the sortlist is empty, point to the first
         */
        Iterator(const SortList<Node, _Compare>&, const Key&);
        
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
        Value& operator*();
        Value* operator->();
        
        /* dereference operators
         *
         * const version
         * throw runtime_error if the node pointed to belongs to
         * a sortlist destroyed, or the iterator points to no node
         */
        Value& operator*() const;
        Value* operator->() const;

    protected:
        /*
         * findValid
         *
         * node: the node to start finding
         *
         * return the address of the nearest valid node found
         * NULL for none found.
         */
        virtual typename SortList<Node, _Compare>::Iterator::Node_A* findValid() const;

    private:
        //Key to follow
        Key hashKey;
};

//A special iterator to iterate all the map
template<typename Key, typename Value, class Hasher, class Compare>
class Hashmap<Key, Value, Hasher, Compare>::Iterator_All {
    public:
        /* default constructor/destructor */
        Iterator_All();
        ~Iterator_All();

        /* conversion constructor
         *
         * The iterator will initialize according to the map
         */
        Iterator_All(const Hashmap<Key, Value, Hasher, Compare>&);
        
        /* copy constructor */
        Iterator_All(const Iterator_All&);
        
        /* assign operator */
        Iterator_All& operator=(const Iterator_All&);

        /* dereference operators
         *
         * non-const version
         * throw runtime_error if the node pointed to belongs to
         * a sortlist destroyed, or the iterator points to no node
         */
        Value& operator*();
        Value* operator->();
        
        /* dereference operators
         *
         * const version
         * throw runtime_error if the node pointed to belongs to
         * a sortlist destroyed, or the iterator points to no node
         */
        Value& operator*() const;
        Value* operator->() const;
        
        /* prefix/postfix ++ operator
         *
         * throw runtime_error if the node pointed to belongs to
         * a sortlist destroyed, or the iterator points to no node.
         * If the iterator comes to the end of the hashmap, there 
         * will be no change to the iterator.
         */
        Iterator_All& operator++();
        Iterator_All operator++(int);

    private:
        /* removeNull
         *
         * remove iterators which are at the end
         */
        void removeNull();

        /* findSmall
         *
         * return the smallest iterator of all
         */
        typename SortList<Node, _Compare>::Iterator* findSmall();

        //size
        int size;

        //Iterators
        typename SortList<Node, _Compare>::Iterator** arr_itr;

        //Current one
        typename SortList<Node, _Compare>::Iterator* current;

        _Compare comp;
};

/* Hashmap Iterator_All */
template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Iterator_All::Iterator_All()
:size(0), arr_itr(NULL) {
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Iterator_All::~Iterator_All() {
    int i;
    //Free the memory
    if(arr_itr) {
        for(i = 0; i < size; i++) {
            delete arr_itr[i];
        }
        delete [] arr_itr;
    }
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Iterator_All::Iterator_All(const Hashmap<Key, Value, Hasher, Compare>& h)
:size(h.slotn),
 arr_itr(new typename SortList<Node, _Compare>::Iterator*[size]),
 comp(h.comp) {
    int i;
    //Init the Iterator list
    for(i = 0; i < size; i++) {
        arr_itr[i] = new typename SortList<Node, _Compare>::Iterator(*(h.arr_bucket[i]));
    }
    //Clean up
    removeNull();
    //Set head
    current = findSmall();
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Iterator_All::Iterator_All(const Hashmap<Key, Value, Hasher, Compare>::Iterator_All& itr)
:size(itr.size),
 arr_itr(new typename SortList<Node, _Compare>::Iterator*[size]),
 comp(itr.comp) {
    int i;
    //Init the Iterator list
    for(i = 0; i < size; i++) {
        arr_itr[i] = new typename SortList<Node, _Compare>::Iterator(*(itr.arr_itr[i]));
    }
    //Clean up
    removeNull();
    //Set head
    current = findSmall();
}

template<typename Key, typename Value, class Hasher, class Compare>
typename Hashmap<Key, Value, Hasher, Compare>::Iterator_All& Hashmap<Key, Value, Hasher, Compare>::Iterator_All::operator=(const Hashmap<Key, Value, Hasher, Compare>::Iterator_All& itr) {
    int i;
    //Free the memory
    if(arr_itr) {
        for(i = 0; i < size; i++) {
            delete arr_itr[i];
        }
        delete [] arr_itr;
    }

    size = itr.size;
    //Allocate memory
    arr_itr = new typename SortList<Node, _Compare>::Iterator*[size];
    //Init the Iterator list
    for(i = 0; i < size; i++) {
        arr_itr[i] = new typename SortList<Node, _Compare>::Iterator(*(itr.arr_itr[i]));
    }
    //Clean up
    removeNull();
    //Set head
    current = findSmall();

    return (*this);
}

template<typename Key, typename Value, class Hasher, class Compare>
Value& Hashmap<Key, Value, Hasher, Compare>::Iterator_All::operator*() {
    if(!current) {
        //At the end
        throw runtime_error("Iteration at the end");
    }
    return current->operator*().val;
}

template<typename Key, typename Value, class Hasher, class Compare>
Value* Hashmap<Key, Value, Hasher, Compare>::Iterator_All::operator->() {
    //Reuse
    return &(*(*this));
}

template<typename Key, typename Value, class Hasher, class Compare>
Value& Hashmap<Key, Value, Hasher, Compare>::Iterator_All::operator*() const {
    if(!current) {
        //At the end
        throw runtime_error("Iteration at the end");
    }
    return current->operator*().val;
}

template<typename Key, typename Value, class Hasher, class Compare>
Value* Hashmap<Key, Value, Hasher, Compare>::Iterator_All::operator->() const {
    //Reuse
    return &(*(*this));
}

template<typename Key, typename Value, class Hasher, class Compare>
typename Hashmap<Key, Value, Hasher, Compare>::Iterator_All& Hashmap<Key, Value, Hasher, Compare>::Iterator_All::operator++() {
    if(!current) {
        //At the end
        throw runtime_error("Iteration at the end");
    }
    current->operator++();
    removeNull();
    current = findSmall();
    return (*this);
}

template<typename Key, typename Value, class Hasher, class Compare>
typename Hashmap<Key, Value, Hasher, Compare>::Iterator_All Hashmap<Key, Value, Hasher, Compare>::Iterator_All::operator++(int) {
    //Reuse
    Iterator_All tmp = (*this);
    operator++();
    return tmp;
}

template<typename Key, typename Value, class Hasher, class Compare>
void Hashmap<Key, Value, Hasher, Compare>::Iterator_All::removeNull() {
    int i = 0;
    while(i < size) {
        try{
            arr_itr[i]->operator*();
        }
        catch(runtime_error& e) {
            //Remove
            delete arr_itr[i];
            arr_itr[i] = NULL;
            arr_itr[i] = arr_itr[size - 1];
            size--;
            continue;
        }
        i++;
    }
}

template<typename Key, typename Value, class Hasher, class Compare>
typename SortList<typename Hashmap<Key, Value, Hasher, Compare>::Node, typename Hashmap<Key, Value, Hasher, Compare>::_Compare>::Iterator* Hashmap<Key, Value, Hasher, Compare>::Iterator_All::findSmall() {
    int i = 0;
    typename SortList<Node, _Compare>::Iterator* res;
    if(size == 0) {
        return NULL;
    }
    res = arr_itr[0];
    for(i = 1; i < size; i++) {
        if(!comp(res->operator*(), arr_itr[i]->operator*())) {
            res = arr_itr[i];
        }
    }
    return res;
}

/* Hashmap Iterator */
template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Iterator::Iterator()
:SortList<Node, _Compare>::Iterator() {
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Iterator::~Iterator() {
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Iterator::Iterator(const SortList<Node, _Compare>& q, const Key& _hashKey)
:SortList<Node, _Compare>::Iterator(q), hashKey(_hashKey) {
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Iterator::Iterator(const Hashmap<Key, Value, Hasher, Compare>::Iterator& itr)
:SortList<Node, _Compare>::Iterator(itr), hashKey(itr.hashKey) {
}

template<typename Key, typename Value, class Hasher, class Compare>
typename Hashmap<Key, Value, Hasher, Compare>::Iterator& Hashmap<Key, Value, Hasher, Compare>::Iterator::operator=(const Hashmap<Key, Value, Hasher, Compare>::Iterator& itr) {
    SortList<Node, _Compare>::Iterator::operator=(itr);
    hashKey = itr.hashKey;
    return (*this);
}

template<typename Key, typename Value, class Hasher, class Compare>
Value& Hashmap<Key, Value, Hasher, Compare>::Iterator::operator*() {
    return SortList<Node, _Compare>::Iterator::operator*().val;
}

template<typename Key, typename Value, class Hasher, class Compare>
Value* Hashmap<Key, Value, Hasher, Compare>::Iterator::operator->() {
    //Reuse operator*
    return &(*(*this));
}

template<typename Key, typename Value, class Hasher, class Compare>
Value& Hashmap<Key, Value, Hasher, Compare>::Iterator::operator*() const{
    return SortList<Node, _Compare>::Iterator::operator*().val;
}

template<typename Key, typename Value, class Hasher, class Compare>
Value* Hashmap<Key, Value, Hasher, Compare>::Iterator::operator->() const{
    //Reuse operator*
    return &(*(*this));
}

template<typename Key, typename Value, class Hasher, class Compare>
typename SortList<typename Hashmap<Key, Value, Hasher, Compare>::Node, typename Hashmap<Key, Value, Hasher, Compare>::_Compare>::Iterator::Node_A* Hashmap<Key, Value, Hasher, Compare>::Iterator::findValid() const {
    typename SortList<Node, _Compare>::Iterator::Node_A* elem = SortList<Node, _Compare>::Iterator::elem;
    typename SortList<Node, _Compare>::Iterator::Node_A* t = elem;
    if(elem->data) {
        while(t->data && t->data->k != hashKey) {
            t = t->next;
        }
        if(t->data) {
            //Valid
            return t;
        }
    }
    if(!t->next && t->prev) {
        //End of sortlist
        //preserve
        return t;
    }
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

/* Hashmap */
template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Hashmap()
:comp(Compare()), arr_bucket(new SortList<Node, _Compare>*[503]),
 slotn(503), length(0), hashFunctoin(Hasher()) {
    int i;
    for(i = 0; i < slotn; i++) {
        arr_bucket[i] = new SortList<Node, _Compare>(comp);
    }
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::~Hashmap() {
    int i;
    if(arr_bucket) {
        for(i = 0; i < slotn; i++) {
            delete arr_bucket[i];
        }
        delete [] arr_bucket;
    }
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Hashmap(Hasher _hash, int _slot, Compare _comp)
:comp(_comp), arr_bucket(new SortList<Node, _Compare>*[(_slot > 0) ? (_slot) : (503)]),
 slotn((_slot > 0) ? (_slot) : (503)), length(0), hashFunctoin(_hash) {
    int i;
    for(i = 0; i < slotn; i++) {
        arr_bucket[i] = new SortList<Node, _Compare>(comp);
    }
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>::Hashmap(const Hashmap<Key, Value, Hasher, Compare>& m)
:comp(m.comp), arr_bucket(new SortList<Node, _Compare>*[m.slotn]),
 slotn(m.slotn), length(m.length), hashFunctoin(m.hashFunctoin) {
    int i;
    for(i = 0; i < slotn; i++) {
        arr_bucket[i] = new SortList<Node, _Compare>(*(m.arr_bucket[i]));
    }
}

template<typename Key, typename Value, class Hasher, class Compare>
Hashmap<Key, Value, Hasher, Compare>& Hashmap<Key, Value, Hasher, Compare>::operator=(const Hashmap<Key, Value, Hasher, Compare>& m) {
    int i;
    //Remove the original
    if(arr_bucket) {
        for(i = 0; i < slotn; i++) {
            delete arr_bucket[i];
        }
        delete [] arr_bucket;
    }

    slotn = m.slotn;
    length = m.length;
    comp = m.comp;
    hashFunctoin = m.hashFunctoin;
    arr_bucket = NULL;

    if(m.arr_bucket) {
        arr_bucket = new SortList<Node, _Compare>*[slotn];
        for(i = 0; i < slotn; i++) {
            arr_bucket[i] = new SortList<Node, _Compare>(*(m.arr_bucket[i]));
        }
    }

    return (*this);
}

template<typename Key, typename Value, class Hasher, class Compare>
Value* Hashmap<Key, Value, Hasher, Compare>::operator[](const Key& hashKey) {
    Iterator itr = Iterator(*arr_bucket[hashFunctoin(hashKey, slotn)], hashKey);
    try {
        return &(*itr);
    }
    catch(runtime_error& e) {
        //End of iteration
        return NULL;
    }
    return NULL;
}

template<typename Key, typename Value, class Hasher, class Compare>
inline bool Hashmap<Key, Value, Hasher, Compare>::isEmpty() const {
    return length == 0;
}

template<typename Key, typename Value, class Hasher, class Compare>
inline int Hashmap<Key, Value, Hasher, Compare>::size() const {
    return length;
}

template<typename Key, typename Value, class Hasher, class Compare>
void Hashmap<Key, Value, Hasher, Compare>::insert(const Key& hashKey, const Value& item) {
    Node tmp;
    tmp.k = hashKey;
    tmp.val = item;
    //Locate the bucket
    arr_bucket[hashFunctoin(hashKey, slotn)]->insert(tmp);
    length++;
}

template<typename Key, typename Value, class Hasher, class Compare>
template<class CompRemove>
int Hashmap<Key, Value, Hasher, Compare>::remove(const Key& hashKey, CompRemove& _comp) {
    //Use custom remove function
    _CustomRemove<CompRemove> t = _CustomRemove<CompRemove>(hashKey, _comp);
    int cnt = arr_bucket[hashFunctoin(hashKey, slotn)]->remove<_CustomRemove<CompRemove> >(t);
    length -= cnt;
    return cnt;
}

template<typename Key, typename Value, class Hasher, class Compare>
typename Hashmap<Key, Value, Hasher, Compare>::Iterator Hashmap<Key, Value, Hasher, Compare>::query(const Key& hashKey) const {
    //Simply use constructor of Iterator
    return Iterator(*arr_bucket[hashFunctoin(hashKey, slotn)], hashKey);
}

template<typename Key, typename Value, class Hasher, class Compare>
template<class Callback>
void Hashmap<Key, Value, Hasher, Compare>::apply(const Key& hashKey, Callback& _cbk) const {
    Iterator itr = Iterator(*arr_bucket[hashFunctoin(hashKey, slotn)], hashKey);
    try {
        while(true) {
            _cbk(*itr);
            itr++;
        }
    }
    catch(runtime_error& e) {
        //End of iteration
    }
}


template<typename Key, typename Value, class Hasher, class Compare>
typename Hashmap<Key, Value, Hasher, Compare>::Iterator_All Hashmap<Key, Value, Hasher, Compare>::dump() const {
    //Simply use constructor of Iterator
    return Iterator_All(*this);
}

#endif
