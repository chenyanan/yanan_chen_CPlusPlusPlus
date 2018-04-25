//
//  chain.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/17.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef chain_hpp
#define chain_hpp

#include <string>
#include <algorithm>
#include "myException.hpp"
#include "linearList.hpp"

template<typename T>
struct chainNode {
    T element;
    chainNode<T> *next;
    
    chainNode() {}
    chainNode(const T& element) {this->element = element;}
    chainNode(const T& element, chainNode<T> *next) {this->element = element;this->next = next;}
};

template<typename T>
class chain : public linearList<T> {
public:
    chain(int initialCapacity = 10);
    chain(const chain<T>&);
    ~chain();
    
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    
    class iterator {
    public:
        iterator(chainNode<T> * theNode = NULL) {node = theNode;}
        T& operator*() const {return node->element;}
        T* operator->() const {return &node->element;}
        
        iterator& operator++() {node = node->next;return *this;}
        iterator operator++(int) {iterator old = *this;node = node->next;return old;}
        
        bool operator!=(const iterator right) const {return node != right.node;}
        bool operator==(const iterator right) const {return node == right.node;}
    protected:
        chainNode<T>* node;
    };
    
    iterator begin() {return iterator(firstNode);}
    iterator end() {return iterator(NULL);}
    
protected:
    void checkIndex(int theIndex) const;
    chainNode<T> *firstNode;
    int listSize;
};

template<typename T>
chain<T>::chain(int initialCapacity) {
    if (initialCapacity < 1) {
        std::string s = "Initial capacity = " + std::string(1, initialCapacity) + ", Must be > 0";
        throw illegalParameterValue(s);
    }
    firstNode = NULL;
    listSize = 0;
}

template<typename T>
chain<T>::chain(const chain<T>& theList) {
    listSize = theList.listSize;
    
    if (listSize == 0) {
        firstNode = NULL;
        return;
    }
    
    chainNode<T>* sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode;
    while (sourceNode != NULL) {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;
}

template<typename T>
chain<T>::~chain() {
    while (firstNode != NULL) {
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<typename T>
void chain<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::string s = "index = " + std::string(1, theIndex) + ", size = " + std::string(1, listSize);
        throw illegalIndex(s);
    }
}

template<typename T>
T& chain<T>::get(int theIndex) const {
    checkIndex(theIndex);
    
    chainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; ++i)
        currentNode = currentNode->next;
    return currentNode->element;
}

template<typename T>
int chain<T>::indexOf(const T& theElement) const {
    chainNode<T> *currentNode = firstNode;
    int index = 0;
    while (currentNode != NULL && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    
    if (currentNode == NULL)
        return -1;
    else
        return index;
}

template<typename T>
void chain<T>::erase(int theIndex) {
    checkIndex(theIndex);
    
    chainNode<T>* deleteNode;
    if (theIndex == 0) {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    
    } else {
        chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; ++i)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;
    }
    listSize--;
    delete deleteNode;
}

template<typename T>
void chain<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        std::string s = "Index = " + std::string(1, theIndex) + ", size = " + std::string(1, listSize);
        throw illegalIndex(s);
    }
    
    if (theIndex == 0) {
        firstNode = new chainNode<T>(theElement, firstNode);
    
    } else {
        chainNode<T>* p = firstNode;
        for (int i =0; i < theIndex - 1; ++i)
            p = p->next;
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

#endif /* chain_hpp */
