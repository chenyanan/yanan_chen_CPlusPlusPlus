//
//  stack.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/19.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>
#include <algorithm>
#include "myException.hpp"
#include "arrayList.hpp"
#include "chain.hpp"

template<typename T>
class stack {
public:
    virtual ~stack() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

template<typename T>
class derivedArrayStackWithCatch : private arrayList<T>, public stack<T> {
public:
    derivedArrayStackWithCatch(int initialCapacity = 10) : arrayList<T> (initialCapacity) {}
    bool empty() const {return arrayList<T>::empty();}
    int size() const {return arrayList<T>::size();}
    T& top() {
        try {return get(arrayList<T>::size() - 1);}
        catch (illegalIndex) {throw stackEmpty();}
    }
    void pop() {
        try {erase(arrayList<T>::size() - 1);}
        catch (illegalIndex) {throw stackEmpty();}
    }
    void push(const T& theElement) {insert(arrayList<T>::size(), theElement);}
};

template<typename T>
class derivedLinkedStackWithCatch : private chain<T>, public stack<T> {
public:
    derivedLinkedStackWithCatch(int initialCapacity = 10) : chain<T> (initialCapacity) {}
    bool empty() const {return chain<T>::empty();}
    int size() const {return chain<T>::size();}
    T& top() {
        try {return chain<T>::get(0);}
        catch (illegalIndex) {throw stackEmpty();}
    }
    void pop() {
        try {chain<T>::erase(0);}
        catch (illegalIndex) {throw stackEmpty();}
    }
    void push(const T& theElement) {insert(0, theElement);}
};

template<typename T>
class arrayStack : public stack<T>
{
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() {delete[] stack;}
    bool empty() const {return stackTop == -1;}
    int size() const {return stackTop + 1;}
    T& top()
    {
        if (stackTop == -1)
            throw stackEmpty();
        return stack[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
            throw stackEmpty();
        stack[stackTop--].~T();
    }
    void push(const T& theElement);
private:
    int stackTop;
    int arrayLength;
    T* stack;
};

template<typename T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::string s = "Initial capacity = " + std::string(1, initialCapacity) + ", Must be > 0";
        throw illegalParameterValue(s);
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template<typename T>
void arrayStack<T>::push(const T& theElement)
{
    if (stackTop == arrayLength - 1)
    {
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    stack[++stackTop] = theElement;
}

template<typename T>
class linkedStack : public stack<T> {
public:
    linkedStack(int initialCapacity = 10) {stackTop = NULL; stackSize = 0;}
    ~linkedStack();
    bool empty() const {return stackSize == 0;}
    int size() const {return stackSize;}
    T& top() {
        if (stackSize == 0)
            throw stackEmpty("stack empty");
        return stackTop->element;
    }
    void pop();
    void push(const T& theElement) {
        stackTop = new chainNode<T>(theElement, stackTop);
        stackSize++;
    }
private:
    chainNode<T>* stackTop;
    int stackSize;
};

template<typename T>
linkedStack<T>::~linkedStack() {
    while (stackTop != NULL) {
        chainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

template<typename T>
void linkedStack<T>::pop() {
    if (stackSize == 0)
        throw stackEmpty();
    
    chainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    stackSize--;
}

#endif /* stack_hpp */
