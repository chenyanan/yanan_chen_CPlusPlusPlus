//
//  sortedArray.hpp
//  C+++
//
//  Created by chenyanan on 2017/2/15.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef sortedArray_hpp
#define sortedArray_hpp

#include <stdio.h>
#include "dictionary.hpp"
#include "myException.hpp"
#include "changeLength1D.hpp"

template<typename K, typename E>
class sortedArray {
public:
    sortedArray(int initialCapacity = 10);
    ~sortedArray() {delete [] element;}
    
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    std::pair<K,E>* find(const K&) const;
    void insert(const std::pair<K,E>& thePair);
    void erase(const K&);
    
    void print() const;
    
protected:
    std::pair<K,E>* element;
    int arrayLength;
    int listSize;
    
    int recursiveBinarySearch(std::pair<K,E>* element, const K& key, int begin, int end) const {
        if (end < begin) return begin;
        int mid = begin + (end - begin) / 2;
        if (element[mid]->first > key) recursiveBinarySearch(element, key, begin, mid - 1);
        else if (element[mid]->first < key) recursiveBinarySearch(element, key, mid + 1, end);
        else return mid;
    }
    
    int iteratedBinarySearch(std::pair<K,E>* element, const K& key, int begin, int end) const {
        while (begin <= end) {
            int mid = begin + (end - begin) / 2;
            if (element[mid].first > key) end = mid - 1;
            else if (element[mid].first < key) begin = mid + 1;
            else return mid;
        }
        return begin;
    }
};

template<typename K, typename E>
sortedArray<K,E>::sortedArray(int initialCapacity) {
    if (initialCapacity < 0) {
        std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
        throw illegalParameterValue(s);
    }
    
    arrayLength = initialCapacity;
    element = new std::pair<K,E>[arrayLength];
    listSize = 0;
}

template<typename K, typename E>
std::pair<K,E>* sortedArray<K,E>::find(const K& theKey) const {
    int location = iteratedBinarySearch(element, theKey, 0, listSize - 1);
    std::pair<K,E>& node = element[location];
    
    if (node.first == theKey)
        return &node;
    
    return NULL;
}
    
template<typename K, typename E>
void sortedArray<K,E>::insert(const std::pair<K,E>& thePair) {
    if (listSize == arrayLength) {
        changeLength1D(element, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }
    
    int location = iteratedBinarySearch(element, thePair.first, 0, listSize - 1);
    std::pair<K,E>& node = element[location];
    
    if (node.first == thePair.first)
        node.second = thePair.second;
    else
    {
        std::copy_backward(element + location, element + listSize, element + listSize + 1);
        element[location] = std::pair<K,E>(thePair);
        ++listSize;
    }
}

template<typename K, typename E>
void sortedArray<K,E>::erase(const K& theKey) {
    int location = iteratedBinarySearch(element, theKey, 0, listSize - 1);
    std::pair<K,E>& node = element[location];
    
    if (node.first == theKey)
    {
        std::copy(element + location + 1, element + listSize, element + location);
        typedef std::pair<K,E> pairType;
        element[--listSize].~pairType();
    }
}

template<typename K, typename E>
void sortedArray<K,E>::print() const
{
    for (int i = 0; i < listSize; ++i)
        printf("key = %d, value = %d\n", element[i].first, element[i].second);
}

#endif /* sortedArray_hpp */
