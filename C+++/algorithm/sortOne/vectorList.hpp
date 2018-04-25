//
//  vectorList.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/17.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef vectorList_hpp
#define vectorList_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "myException.hpp"

template<typename T>
class vectorList : public linearList<T> {
public:
    vectorList(int initialCapacity = 10);
    vectorList(const vectorList<T>&);
    ~vectorList() {delete element;}
    
    bool empty() const {return element->empty();}
    int size() const {return (int)element->size();}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    
    int capacity() const { return (int) element->capacity();}
    
    typedef typename vectorList<T>::iterator iterator;
    iterator begin() {return element->begin();}
    iterator end() {return element->end();}
    
protected:
    void checkIndex(int theIndex) const;
    std::vector<T> *element;
};

template<typename T>
vectorList<T>::vectorList(int initialCapacity) {
    if (initialCapacity < 1) {
        std::string s = "Initial capacity = " + std::string(1, initialCapacity) + " Must be > 0";
        throw illegalParameterValue(s);
    }
    
    element = new vectorList<T>;
    element->reserve(initialCapacity);
}

template<typename T>
vectorList<T>::vectorList(const vectorList<T>& theList) {
    element = new vectorList<T>(*theList.element);
}

template<typename T>
void vectorList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= element->size()) {
        std::string s = "index = " + std::string(1, theIndex) + ", size = " + std::string(1, element->size());
        throw illegalIndex(s);
    }
}

template<typename T>
T& vectorList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element->at(theIndex);
}

template<typename T>
int vectorList<T>::indexOf(const T& theElement) const {
    iterator it = find(begin(), end(), theElement);
    if (it == end())
        return -1;
    else return it.position();
}

template<typename T>
void vectorList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    element->erase(begin() + theIndex);
}

template<typename T>
void vectorList<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > element->size()) {
        std::string s = "Index = " + std::string(1, theIndex) + ", size = " + std::string(1, element->size());
        throw illegalIndex(s);
    }
    
    element->insert(element->begin() + theIndex, theElement);
}

#endif /* vectorList_hpp */
