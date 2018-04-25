//
//  minHeap.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/23.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef minHeap_hpp
#define minHeap_hpp

#include "minPriorityQueue.hpp"
#include "myException.hpp"
#include "changelength1D.hpp"
#include <algorithm>
#include <string>

template<typename T>
class minHeap : public minPriorityQueue<T> {
public:
    minHeap(int initialCapacity = 10);
    ~minHeap() {delete[] heap;}
    bool empty() const {return heapSize == 0;}
    int size() const {return heapSize;}
    const T& top() {
        if (heapSize == 0)
            throw queueEmpty();
        return heap[1];
    }
    void pop();
    void push(const T&);
    void initialize(T*, int);
    void deactivateArray() {heap = NULL; arrayLength = heapSize = 0;}
private:
    int heapSize;
    int arrayLength;
    T* heap;
};

template<typename T>
minHeap<T>::minHeap(int initialCapacity) {
    if (initialCapacity < 1)
    {
        std::string s = "Initial capacity = " + std::string(1, initialCapacity) + ", Must be > 0";
        throw illegalParameterValue(s);
    }
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

template<typename T>
void minHeap<T>::push(const T& theElement) {
    if (heapSize == arrayLength - 1) {
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > theElement) {
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }
    
    heap[currentNode] = theElement;
}

template<typename T>
void minHeap<T>::pop() {
    if (heapSize == 0)
        throw queueEmpty();
    
    heap[1].~T();
    
    T lastElement = heap[heapSize--];
    
    int currentNode = 1, child = 2;
    while (child <= heapSize) {
        if (child < heapSize && heap[child] > heap[child + 1])
            child++;
        
        if (lastElement <= heap[child])
            break;
        
        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    
    heap[currentNode] = lastElement;
}

template<typename T>
void minHeap<T>::initialize(T *theHeap, int theSize) {
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;
    
    for (int root = heapSize / 2; root >= 1; root--) {
        T rootElement = heap[root];
        
        int child = 2 * root;
        
        while (child <= heapSize) {
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            
            if (rootElement <= heap[child])
                break;
            
            heap[child / 2] = heap[child];
            child *= 2;
        }
        heap[child / 2] = rootElement;
    }
}

#endif /* minHeap_hpp */
