//
//  anotherText.hpp
//  C+++
//
//  Created by chenyanan on 2017/2/7.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef anotherText_hpp
#define anotherText_hpp

#include <stdio.h>
#include <stdlib.h>
#include "myException.hpp"
#include "changeLength1D.hpp"

template<typename T>
bool maxBubble(T* a, int size) {
    bool sorted = true;
    for (int i = 1; i < size; ++i)
        if (a[i - 1] > a[i]) {
            std::swap(a[i - 1], a[i]);
            sorted = false;
        }
    return sorted;
}

template<typename T>
void MaxBubble(T* a, int size) {
    for (int i = size; i > 1 && !maxBubble(a, i); ++i);
}

template<typename T>
bool minBubble(T* a, int size) {
    bool sorted = true;
    for (int i = 1; i < size; ++i)
        if (a[i - 1] < a[i]) {
            std::swap(a[i - 1], a[i]);
            sorted = false;
        }
    return sorted;
}

template<typename T>
void MinBubble(T* a, int size) {
    for (int i = size; i > 1 && !minBubble(a, i); ++i);
}

template<typename T>
void MinSelect(T* a, int size) {
    bool sorted = false;
    for (int i = size; i > 1 && !sorted; --i) {
        sorted = true;
        int minIndex = 0;
        for (int j = 1; j < i; ++j) {
            if (a[minIndex] > a[j]) minIndex = j;
            else sorted = false;
        }
    }
}

template<typename T>
void MaxSelect(T* a, int size) {
    bool sorted = false;
    for (int i = size; i > 1 && !sorted; --i) {
        sorted = true;
        int maxIndex = 0;
        for (int j = 1; j < i; ++j) {
            if (a[maxIndex] < a[j]) maxIndex = j;
            else sorted = false;
        }
    }
}

template<typename T>
void MaxInsert(T* a, int size) {
    for (int i = 1; i < size; ++i) {
        int j;
        T t = a[i];
        for (int j = i - 1; j >= 0 && t < a[j]; --j)
            a[j + 1] = a[j];
        a[j + 1] = t;
    }
}

template<typename T>
void MinInsert(T* a, int size) {
    for (int i = 1; i < size; ++i) {
        int j;
        T t = a[i];
        for (int j = i - 1; j >= 0 && t > a[j]; --j)
            a[j + 1] = a[j];
        a[j + 1] = t;
    }
}

template<typename T>
class linearList {
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual int indexOf(const T&) const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void erase(int theIndex) = 0;
};

template<typename T>
class arrayList : public linearList<T> {
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>& theList);
    ~arrayList() {delete [] element;}
    
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    int indexOf(const T& theElement) const;
    T& get(int theIndex) const;
    void insert(int theIndex, const T& theElement);
    void erase(int theIndex);
    
    class arrayListIterator;
    arrayListIterator begin() {return arrayListIterator(element);}
    arrayListIterator end() {return arrayListIterator(element + listSize);}
    
    class arrayListIterator {
        arrayListIterator(T* thePosition = NULL) {position = thePosition;}
        ~arrayListIterator(){}
        
        bool operator!=(const arrayListIterator& right) {return position != right.position;}
        bool operator==(const arrayListIterator& right) {return position == right.position;}
        
        arrayListIterator& operator++() {++position; return *this;}
        arrayListIterator operator++(int) {arrayListIterator old = *this; ++position; return old;}
        
        arrayListIterator& operator--() {--position; return *this;}
        arrayListIterator operator--(int) {arrayListIterator old = *this; --position; return old;}
        
        T& operator*() {return *position;}
        T* operator->() {return &*position;}
        
    protected:
        T* position;
    };
    
protected:
    void checkIndex(int theIndex) const;
    T* element;
    int arrayLength;
    int listSize;
};

template<typename T>
arrayList<T>::arrayList(int initialCapacity) {
    if (initialCapacity < 0) {
        std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
        throw illegalParameterValue(s);
    }
    
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template<typename T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
    listSize = theList.listSize;
    arrayLength = theList.arrayLength;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + listSize, element);
}

template<typename T>
void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::string s = "theIndex = " + std::string(1, theIndex) + ", Must be > 0 && < listSize";
        throw illegalParameterValue(s);
    }
}

template<typename T>
int arrayList<T>::indexOf(const T& theElement) const {
    int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
    if (theIndex == listSize)
        return -1;
    else return theIndex;
}

template<typename T>
T& arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

template<typename T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T();
}

template<typename T>
void arrayList<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        std::string s = "theIndex = " + std::string(1, theIndex) + ", Must be > 0 && <= listSize";
        throw illegalParameterValue(s);
    }
    
    if (listSize == arrayLength) {
        changeLength1D(element, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }
    
    std::copy_backward(element + theIndex, element + listSize, element + theIndex + 1);
    element[theIndex] = theElement;
    ++listSize;
}

template<typename T>
struct chainNode {
    T element;
    chainNode<T>* next;
    
    chainNode(const T& theElement) : element(theElement) {}
    chainNode(const T& theElement, chainNode<T>* theNext = NULL) : element(theElement) {next = theNext;}
};

template<typename T>
class chainList : public linearList<T> {
public:
    chainList(int initialCapacity = 11) {firstNode = NULL; listSize = 0;}
    chainList(const chainList<T>& theList);
    ~chainList();
    
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    int indexOf(const T& theElement) const;
    T& get(int theIndex) const;
    void insert(int theIndex, const T& theElement);
    void erase(int theIndex);
    
    class chainListIterator;
    chainListIterator begin() {return chainListIterator(firstNode);}
    chainListIterator end() {return chainListIterator(NULL);}
    
    class chainListIterator {
    public:
        chainListIterator(chainNode<T>* thePosition) {position = thePosition;}
        ~chainListIterator(){}
        
        bool operator!=(const chainListIterator& right) {return position != right.position;}
        bool operator==(const chainListIterator& right) {return position == right.position;}
        
        chainListIterator operator++(int) {chainListIterator old = *this; position = position->next; return old;}
        chainListIterator& operator++() {position = position->next; return *this;}
        
        T& operator*() {return position->element;}
        T* operator->() {return &position->element;}
        
    protected:
        chainNode<T>* position;
    };
    
protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* firstNode;
    int listSize;
};

template<typename T>
chainList<T>::chainList(const chainList<T>& theList) {
    listSize = theList.listSize;
    
    if (listSize == 0) {
        firstNode = NULL;
        return;
    }
    
    chainNode<T>* sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode.element);
    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode;
    while (sourceNode != NULL) {
        targetNode->next = new chainNode<T>(sourceNode.element);
        sourceNode = sourceNode->next;
        targetNode = targetNode->next;
    }
    targetNode->next = NULL;
}

template<typename T>
chainList<T>::~chainList() {
    while (firstNode != NULL) {
        chainNode<T>* next = firstNode->next;
        delete firstNode;
        firstNode = next;
    }
}

template<typename T>
void chainList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::string s = "theIndex = " + std::string(1, theIndex) + ", Must be > 0 && < listSize";
        throw illegalParameterValue(s);
    }
}

template<typename T>
int chainList<T>::indexOf(const T& theElement) const {
    int theIndex = 0;
    chainNode<T>* currentNode = firstNode;
    
    while (currentNode != NULL && currentNode->element != theElement)
        currentNode = currentNode->next;
    
    if (currentNode != NULL && currentNode->element == theElement)
        return theIndex;
    return -1;
}

template<typename T>
T& chainList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    
    chainNode<T>* currentNode = firstNode;
    
    for (int i = 1; i <= theIndex; ++i)
        currentNode = currentNode->next;
    
    return currentNode->element;
}

template<typename T>
void chainList<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        std::string s = "theIndex = " + std::string(1, theIndex) + ", Must be > 0 && <= listSize";
        throw illegalParameterValue(s);
    }
    
    if (theIndex == 0)
    {
        firstNode = new chainNode<T>(theElement, firstNode);
    }
    else
    {
        chainNode<T>* p = firstNode;
        for (int i = 1; i < theIndex; ++i)
            p = p->next;
        p->next = new chainNode<T>(theElement, p->next);
    }
    ++listSize;
}

template<typename T>
void chainList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    
    chainNode<T>* deleteNode = NULL;
    if (theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T>* p = firstNode;
        for (int i = 1; i < theIndex; ++i)
            p = p->next;
        deleteNode = p->next;
        p->next = deleteNode->next;
    }
    
    delete deleteNode;
    --listSize;
}

template<typename T>
class stack {
public:
    virtual ~stack() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& front() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

template<typename T>
class arrayStack : public stack<T> {
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() {delete [] stack;}
    
    bool empty() const {return stackTop == -1;}
    int size() const {return stackTop + 1;}
    T& front() {
        if (stackTop == -1)
            throw stackEmpty();
        return stack[stackTop];
    }
    void pop() {
        if (stackTop == -1)
            throw stackEmpty();
        stack[stackTop--].~T();
    }
    void push(const T& theElement);
protected:
    T* stack;
    int stackTop;
    int stackLength;
};

template<typename T>
arrayStack<T>::arrayStack(int initialCapacity) {
    if (initialCapacity < 0) {
        std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
        throw illegalParameterValue(s);
    }
    
    stackLength = initialCapacity;
    stack = new T[stackLength];
    stackTop = -1;
}

template<typename T>
void arrayStack<T>::push(const T& theElement) {
    if (stackTop + 1 == stackLength) {
        changeLength1D(stack, stackLength, stackLength * 2);
        stackLength *= 2;
    }
    
    stack[++stackTop] = theElement;
}

template<typename T>
class linkedStack : public stack<T> {
public:
    linkedStack(int initialCapacity = 10) {stackTop = NULL; stackSize = 0;}
    ~linkedStack() {
        while (stackTop != NULL) {
            chainNode<T>* next = stackTop->next;
            delete stackTop;
            stackTop = next;
        }
    }
    
    bool empty() const {return stackSize == 0;}
    int size() const {return stackSize;}
    T& front() {
        if (stackSize == 0)
            throw stackEmpty();
        return stackTop->element;
    }
    void pop() {
        if (stackSize == 0)
            throw stackEmpty();
        chainNode<T>* next = stackTop->next;
        delete stackTop;
        stackTop = next;
        --stackSize;
    }
    void push(const T& theElement) {
        stackTop = new chainNode<T>(theElement, stackTop);
        ++stackSize;
    }
protected:
    chainNode<T>* stackTop;
    int stackSize;
};

template<typename T>
class drivedArrayStackWithCatch : private arrayList<T>, public stack<T> {
public:
    drivedArrayStackWithCatch(int initialCapacity = 10) : arrayList<T>(initialCapacity) {}
    
    bool empty() const {return arrayList<T>::empty();}
    int size() const {return arrayList<T>::size();}
    T& front() {
        try {return arrayList<T>::get(arrayList<T>::size() - 1);}
        catch(illegalParameterValue e) {throw stackEmpty();}
    }
    void pop() {
        try {arrayList<T>::erase(arrayList<T>::size() - 1);}
        catch(illegalParameterValue e) {throw stackEmpty();}
    }
    void push(const T& theElement) {
        arrayList<T>::insert(arrayList<T>::size(), theElement);
    }
};

template<typename T>
class drivedLinkedStackWithCatch : private chainList<T>, public stack<T> {
public:
    drivedLinkedStackWithCatch(int initialCapacity = 10) : chainList<T>(initialCapacity) {}
    
    bool empty() const {return chainList<T>::empty();}
    int size() const {return chainList<T>::size();}
    T& front() {
        try {return chainList<T>::get(0);}
        catch(illegalParameterValue e) {throw stackEmpty();}
    }
    void pop() {
        try {chainList<T>::erase(0);}
        catch(illegalParameterValue e) {throw stackEmpty();}
    }
    void push(const T& theElement) {
        chainList<T>::insert(0, theElement);
    }
};

template<typename T>
class queue {
public:
    virtual ~queue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

template<typename T>
class arrayQueue : public queue<T> {
public:
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue() {delete [] queue;}
    
    bool empty() const {return theFront == theBack;}
    int size() const {return (theBack - theFront + queueLength) % queueLength;}
    T& front() {
        if (theFront == theBack)
            throw queueEmpty();
        return queue[(theFront + 1) % queueLength];
    }
    T& back() {
        if (theFront == theBack)
            throw queueEmpty();
        return queue[theBack];
    }
    void pop();
    void push(const T& theElement);
protected:
    int theFront;
    int theBack;
    int queueLength;
    T* queue;
};

template<typename T>
arrayQueue<T>::arrayQueue(int initialCapacity) {
    if (initialCapacity < 0) {
        std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
        throw illegalParameterValue(s);
    }
    
    queueLength = initialCapacity;
    queue = new T[queueLength];
    theFront = queueLength - 1;
    theBack = queueLength - 1;
}

template<typename T>
void arrayQueue<T>::pop() {
    if (theFront == theBack)
        throw queueEmpty();
    
    theFront = (theFront + 1) % queueLength;
    queue[theFront].~T();
}

template<typename T>
void arrayQueue<T>::push(const T& theElement) {
    if ((theBack + 1) % queueLength == theFront) {
        T* newQueue = new T[queueLength * 2];
        
        int start = (theFront + 1) % queueLength;
        if (start < 2)
            std::copy(queue + start, queue + start + queueLength - 1, newQueue);
        else
        {
            std::copy(queue + start, queue + queueLength, newQueue);
            std::copy(queue, queue + theBack + 1, newQueue + queueLength - start);
        }
        theFront = queueLength * 2 - 1;
        theBack = queueLength - 1;
        queueLength *= 2;
        delete [] queue;
        queue = newQueue;
    }
    theBack = (theBack + 1) % queueLength;
    queue[theBack] = theElement;
}

template<typename T>
class linkedQueue : public queue<T> {
public:
    linkedQueue(int initialCapacity = 10) {theFront = theBack = NULL; queueSize = 0;}
    ~linkedQueue();
    
    bool empty() const {return queueSize == 0;}
    int size() const {return queueSize;}
    T& front() {
        if (queueSize == 0)
            throw queueEmpty();
        return theFront->element;
    }
    T& back() {
        if (queueSize == 0)
            throw queueEmpty();
        return theBack->element;
    }
    void pop() {
        if (queueSize == 0)
            throw queueEmpty();
        
        chainNode<T>* tmp = theFront->next;
        delete theFront;
        theFront = tmp;
        --queueSize;
    }
    void push(const T& theElement) {
        chainNode<T>* tmp = new chainNode<T>(theElement, NULL);
        
        if (queueSize == 0)
            theFront = tmp;
        else
            theBack->next = tmp;
        theBack = tmp;
        ++queueSize;
    }
protected:
    chainNode<T>* theFront;
    chainNode<T>* theBack;
    int queueSize;
};

template<typename T>
linkedQueue<T>::~linkedQueue() {
    while (theFront != NULL) {
        chainNode<T>* tmp = theFront->next;
        delete theFront;
        theFront = tmp;
    }
}

template<typename K, typename E>
class dictionary {
public:
    virtual ~dictionary() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual std::pair<const K,E>* find(const K&) const = 0;
    virtual void erase(const K&) = 0;
    virtual void insert(const std::pair<const K,E>&) = 0;
};

template<typename K, typename E>
struct pairNode {
    typedef std::pair<const K,E> pairType;
    pairType element;
    pairNode<K,E>* next;
    
    pairNode(const pairType& thePair, pairNode<K,E>* theNext = NULL) : element(thePair) {next = theNext;}
};

template<typename K, typename E>
class sortedChain : public dictionary<K,E> {
public:
    sortedChain(int initialCapacity = 10) {firstNode = NULL; listSize = 0;}
    ~sortedChain();
    
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    std::pair<const K,E>* find(const K&) const;
    void insert(const std::pair<const K,E>& thePair);
    void erase(const K&);
protected:
    pairNode<K,E>* firstNode;
    int listSize;
};

template<typename K, typename E>
sortedChain<K,E>::~sortedChain() {
    while (firstNode != NULL) {
        pairNode<K,E>* next = firstNode->next;
        delete firstNode;
        firstNode = next;
    }
}

template<typename K, typename E>
std::pair<const K,E>* sortedChain<K,E>::find(const K& theKey) const {
    pairNode<K,E>* currentNode = firstNode;
    
    while (currentNode != NULL && currentNode->element.first < theKey)
        currentNode = currentNode->next;
    
    if (currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element;
    
    return NULL;
}

template<typename K, typename E>
void sortedChain<K,E>::insert(const std::pair<const K,E>& thePair) {
    pairNode<K,E>* p = firstNode, tp = NULL;
    
    while (p != NULL && p->element.first < thePair.first) {
        tp = p;
        p = p->next;
    }
    
    if (p != NULL && p->element.first == thePair.first) {
        p->element.second = thePair.second;
        return;
    }
    
    pairNode<K,E>* newNode = new pairNode<K,E>(thePair,p);
    if (tp == NULL) firstNode = newNode;
    else tp->next = newNode;
    
    ++listSize;
}

template<typename K, typename E>
void sortedChain<K,E>::erase(const K& theKey) {
    pairNode<K,E>* p = firstNode, tp = NULL;
    
    while (p != NULL && p->element.first < theKey) {
        tp = p;
        p = p->next;
    }
    
    if (p != NULL && p->element.first == theKey) {
        if (tp == NULL) firstNode = p->next;
        else tp->next = p->next;
        
        delete p;
        --listSize;
    }
}

template<typename K, typename E>
struct skipNode {
    typedef std::pair<const K,E> pairType;
    pairType element;
    skipNode<K,E>** next;
    
    skipNode(const pairType& thePair, int size) : element(thePair) {next = new skipNode<K,E>*[size];}
};

template<typename K, typename E>
class skipList : public dictionary<K,E> {
public:
    skipList(K, int maxPairs = 10000, float prob = 0.5);
    ~skipList();
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K&) const;
    void insert(const std::pair<const K,E>& thePair);
    void erase(const K&);
    
protected:
    float cutOff;
    int maxLevel;
    int levels;
    int dSize;
    K tailKey;
    skipNode<K,E>* headerNode;
    skipNode<K,E>* tailNode;
    skipNode<K,E>** last;
    int level() const;
    skipNode<K,E>* search(const K&) const;
};

template<typename K, typename E>
skipList<K,E>::skipList(K largeKey, int maxPairs, float prob) {
    cutOff = RAND_MAX * prob;
    maxLevel = (int)ceil(logf((float)maxPairs) / logf(1/prob)) - 1;
    levels = 0;
    dSize = 0;
    tailKey = largeKey;
    std::pair<const K,E> tailPair(tailKey, NULL);
    headerNode = new skipNode<K,E>(tailPair, maxLevel + 1);
    tailNode = new skipNode<K,E>(tailPair, 0);
    last = new skipNode<K,E>*[maxLevel + 1];
    
    for (int i = 0; i <= maxLevel; ++i)
        headerNode->next[i] = tailNode;
}

template<typename K, typename E>
skipList<K,E>::~skipList() {
    while (headerNode != tailNode) {
        skipNode<K,E>* next = headerNode->next[0];
        delete headerNode;
        headerNode = next;
    }
    delete tailNode;
    delete [] last;
}

template<typename K, typename E>
int skipList<K,E>::level() const {
    int lev = 0;
    while (std::rand() <= cutOff)
        ++lev;
    return (lev <= maxLevel) ? lev : maxLevel;
}

template<typename K, typename E>
std::pair<const K,E>* skipList<K,E>::find(const K& theKey) const {
    if (theKey > tailKey)
        return NULL;
    
    skipNode<K,E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; --i)
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
    
    if (beforeNode->next[0]->element.first == theKey)
        return &beforeNode->next[0]->element;
    
    return NULL;
}

template<typename K, typename E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const {
    if (theKey > tailKey)
        return NULL;
    
    skipNode<K,E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; --i) {
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;
    }
    
    return beforeNode->next[0];
}

template<typename K, typename E>
void skipList<K,E>::insert(const std::pair<const K,E>& thePair) {
    if (thePair.first > tailKey)
        throw illegalParameterValue("Must be < tailKey");
    
    skipNode<K,E>* theNode = search(thePair.first);
    if (theNode->element.first == thePair.first) {
        theNode->element.second = thePair.second;
        return;
    }
    
    int theLevel = level();
    if (theLevel > levels) {
        theLevel = ++levels;
        last[levels] = headerNode;
    }
    
    skipNode<K,E>* newNode = new skipNode<K,E>(thePair, levels);
    for (int i = 0; i <= levels; ++i) {
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }
    
    ++dSize;
    return;
}

template<typename K, typename E>
void skipList<K,E>::erase(const K& theKey) {
    if (theKey > tailKey)
        return;
    
    skipNode<K,E>* theNode = search(theKey);
    if (theNode->element.first != theKey)
        return;
    
    for (int i = 0; i <= levels && last[i]->next[i] == theNode; ++i)
        last[i]->next[i] = theNode->next[i];
    
    while (levels > 0 && last[levels]->next[levels] == tailNode)
        --levels;
    
    delete theNode;
    --dSize;
}

template<typename T> class hash;

template<>
class hash<std::string> {
    size_t operator()(const std::string& theString) {
        unsigned long hashValue = 0;
        int length = (int) theString.length();
        for (int i = 0; i < length; ++i)
            hashValue = hashValue * 5 + theString.at(i);
        return size_t(hashValue);
    }
};

template<>
class hash<int> {
    size_t operator()(const int theInteger) {return size_t(theInteger);}
};

template<>
class hash<long> {
    size_t operator()(const long theLong) {return size_t(theLong);}
};

template<typename K, typename E>
class hashTable {
public:
    hashTable(int theDivisor = 11);
    ~hashTable() {delete [] table;}
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K&) const;
    void insert(const std::pair<const K,E>& thePair);
    void erase(const K&);
    
protected:
    int search(const K&) const;
    std::pair<const K,E>** table;
    hash<K> hash;
    int dSize;
    int divisor;
};

template<typename K, typename E>
hashTable<K,E>::hashTable(int theDivisor) {
    if (theDivisor <= 0) {
        std::string s = "theDivisor = " + std::string(1, theDivisor) + ", Must be > 0";
        throw illegalParameterValue(s);
    }
    
    divisor = theDivisor;
    dSize = 0;
    table = new std::pair<const K,E>*[divisor];
    
    for (int i = 0; i < divisor; ++i)
        table[i] = NULL;
}

template<typename K, typename E>
int hashTable<K,E>::search(const K& theKey) const {
    int i = (int) hash(theKey) % divisor;
    int j = i;
    do {
        if (table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    } while (j != i);
    return j;
}

template<typename K, typename E>
std::pair<const K,E>* hashTable<K,E>::find(const K& theKey) const {
    int i = search(theKey);
    
    if (table[i] == NULL || table[i]->first != theKey)
        return NULL;
    
    return table[i];
}

template<typename K, typename E>
void hashTable<K,E>::erase(const K& theKey) {
    int i = search(theKey);
    
    if (table[i] == NULL || table[i]->first != theKey)
        return;
    
    delete table[i];
    --dSize;
}

template<typename K, typename E>
void hashTable<K,E>::insert(const std::pair<const K,E>& thePair) {
    int i = search(thePair.first);
    
    if (table[i] == NULL) {
        table[i] = new std::pair<const K,E>(thePair);
        ++dSize;
        
    } else {
        if (table[i]->first == thePair.first)
            table[i]->second = thePair.second;
        else
            throw hashTableFull();
    }
}

template<typename K, typename E>
class hashChain : public dictionary<K,E> {
public:
    hashChain(int theDivisor = 11);
    ~hashChain() {delete [] table;}
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K& theKey) const {
        return table[hash(theKey) % divisor].find(theKey);
    }
    void insert(const std::pair<const K,E>& thePair) {
        int homeBucket = (int) hash(thePair.first) % divisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        if (table[homeBucket].size() > homeSize)
            ++dSize;
    }
    void erase(const K& theKey) {
        table[hash(theKey) % divisor].erase(theKey);
    }
    
protected:
    sortedChain<K,E>* table;
    hash<K> hash;
    int dSize;
    int divisor;
};
#endif /* anotherText_hpp */
