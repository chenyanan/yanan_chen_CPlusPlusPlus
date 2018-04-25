//
//  test.hpp
//  C+++
//
//  Created by chenyanan on 2017/2/3.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef test_hpp
#define test_hpp

#include <stdio.h>
#include "arrayList.hpp"
#include "chain.hpp"
#include "chainNode.hpp"
#include "myException.hpp"
#include "changeLength1D.hpp"

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
class arrayStack : public stack<T> {
public:
    arrayStack(int initialCapacity = 11) {
        if (initialCapacity <= 0) {
            std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
            throw illegalParameterValue(s);
        }
        
        stackLength = initialCapacity;
        element = new T[stackLength];
        top = -1;
    }
    ~arrayStack() {delete element;}
    
    bool empty() const {return top == -1;}
    int size() const {return top + 1;}
    T& top() {
        if (top == -1)
            throw stackEmpty();
        return element[top];
    }
    void pop() {
        if (top == -1)
            throw stackEmpty();
        element[top--].~T();
    }
    void push(const T& theElement) {
        if (top + 1 == stackLength) {
            changeLength1D(element, stackLength, stackLength * 2);
            stackLength *= 2;
        }
        element[++top] = theElement;
    }
protected:
    T* element;
    int stackLength;
    int top;
};

template<typename T>
class chainNode {
public:
    T element;
    chainNode<T>* next;
    
    chainNode(const T& theElement, chainNode<T>* theNext = NULL) : element(theElement) {next = theNext};
};

template<typename T>
class linkedStack : pulick stack<T> {
public:
    linkedStack(int initialCapacity = 11) {top = NULL; stackSize = 0;}
    ~linkedStack() {
        while (top != NULL) {
            chainNode<T>* next = top->next;
            delete top;
            top = next;
        }
    }
    
    bool empty() const {return stackSize == 0;}
    int size() const {return stackSize;}
    T& top() {
        if (stackSize == 0)
            throw stackEmpty();
        return top->element;
    }
    void pop() {
        if (stackSize == 0)
            throw stackEmpty();
        chainNode<T>* next = top->next;
        delete top;
        top = next;
        --stackSize;
    }
    void push(const T& theElement) {
        top = new chainNode<T>(theElement, top);
        ++stackSize;
    }
    
protected:
    chainNode<T>* top;
    int stackSize;
};

template<typename T>
class drivedArrayStack : private arrayList<T>, public stack<T> {
public:
    drivedArrayStack(int initialCapacity = 11) : arrayList(initialCapacity) {};
    ~drivedArrayStack() {};
    
    bool empty() const {return arrayList<T>::empty();}
    int size() const {return arrayList<T>::size();}
    T& top() {
        if (arrayList<T>::empty())
            throw stackEmpty();
        return arrayList<T>::get(arrayList<T>::size() - 1);
    }
    void pop() {
        if (arrayList<T>::empty())
            throw stackEmpty();
        arrayList<T>::erase(arrayList<T>::size() - 1)
    }
    void push(const T& theElement) {
        arrayList<T>::insert(arrayList<T>::size(),theElement);
    }
};

template<typename T>
class drivedLinkedStack : private chain<T>, public stack<T> {
public:
    drivedLinkedStack(int initialCapacity = 11) : chain(initialCapacity) {};
    ~drivedLinkedStack() {}
    
    bool empty() const {return chain<T>::empty();}
    int size() const {return chain<T>::size();}
    T& top() {
        try {chain<T>::get(0);}
        catch(illegalParameterValue e) {throw stackEmpty();}
    }
    void pop() {
        try {chain<T>::erase(0);}
        catch(illegalParameterValue e) {throw stackEmpty();}
    }
    void push(const T& theElement) {
        chain<T>::insert(0, theElement);
    }
}

template<typename T>
class queue {
public:
    virtual ~queue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& front() const = 0;
    virtual T& back() const = 0;
    virtual void pop() = 0;
    virtual void push(const T&) = 0;
};

template<typename T>
class linkedQueue {
public:
    linkedQueue(int initialCapacity = 11) {queueSize = 0; theFront = NULL; theBack = NULL;}
    ~linkedQueue() {
        while (queueFront != queueBack) {
            chainNode<T>* next = theFront->next;
            delete theFront;
            theFront = next;
        }
    }
    bool empty() const {return queueSize == 0;}
    int size() const {return queueSize;}
    T& front() const {
        if (queueSize == 0)
            throw queueEmpty();
        return queueFront->element;
    }
    T& back() const {
        if (queueSize == 0)
            throw queueEmpty();
        return queueBack->element;
    }
    void pop() {
        if (queueSize == 0)
            throw queueEmpty();
        chainNode<T>* next = queueFront->next;
        delete queueFront;
        queueFront = next;
        --queueSize;
    }
    void push(const T& theElement) {
        chainNode<T>* newNode = new chainNode<T>(theElement, queueBack);
        
        if (queueSize == 0) //出错
            queueFront = newNode;
        else
            queueBack->next = newNode;
        queueBack = newNode;
        ++queueSize;
    }
protected:
    chainNode<T>* queueFront;
    chainNode<T>* queueBack;
    int queueSize;
};

template<typename T>
class arrayQueue {
public:
    arrayQueue(int initialCapacity = 11) {
        if (initialCapacity <= 0) {
            std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
            throw illegalParameterValue(s);
        }
        
        queueLength = initialCapacity;
        element = new T[queueLength];
        theBack = 0; //出错
        theFront = 0;  //出错
    }
    ~arrayQueue() {delete element;}
    
    bool empty() const {return theBack == theFront;}
    int size() const {return (theBack - theFront + queueLength) % queueLength};
    T& front() const {
        if (theBack == theFront)
            throw queueEmpty();
        return element[(theFront + 1) % queueLength];
    }
    T& back() const {
        if (theBack == theFront)
            throw queueEmpty();
        return element[theBack % queueLength];
    }
    void pop() {
        if (theBack == theFront)
            throw queueEmpty();
        element[theBack].~T();
        theBack = (theBack - 1) % queueLength;
    }
    void insert(const T& theElement) {
        if ((theBack + 1) % queueLength = theFront) {
            T* newQueue = new T[queueLength * 2];
            int start = (theFront + 1) % queueLength;
            if (start < 2)
                std::copy(element + start, element + start + queueLength - 1, newQueue);   //出错
                
            else {
                std::copy(element + start, element + queueLength, newQueue);
                std::copy(element, element + theBack + 1, newQueue + queueLength - start);   //出错
            }
            theFront = 2 * queueLength - 1;   //出错
            theBack = queueLength - 2;
            queueLength *= 2;
            element = newQueue;
        }
        
        theBack = (theBack + 1) % queueLength;
        element[theBack] = theElement;
    }
    
protected:
    T* element;
    int theBack;
    int theFront;
    int queueLength;
};


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
}

template<>
class hash<int> {
    size_t operator()(const int theInteger) {return size_t(theInteger);}
}

template<>
class hash<long> {
    size_t operator()(const long theLong) {return size_t(theLong);}
}

template<typename K, typename E>
class hashTable {
    hashTable(int theDivisor = 11);
    ~hashTable() {delete [] table;}
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K&) const;
    void insert(const std::pair<const K,E>& thePair);
    
protected:
    int search(const K&) const;
    std::pair<const K,E>** table;
    hash<K> hash;
    int dSize;
    int divisor;
};

template<typename K, typename E>
hashTable<K,E>::hashTable(int theDivisor) {
    if (initialCapacity <= 0) {
        std::string s = "theDivisor = " + std::string(1, initialCapacity) + ", Must be > 0";
        throw illegalParameterValue;
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
    int j = b;
    do {
        if (table[j] != NULL || table[j]->first == theKey)
            return;
        j = (j + 1) % divisor;
    } while(j != b);
    return j;
}

template<typename K, typename E>
std::pair<const K,E>* hashTable<K,E>::find(const K& theKey) const {
    int b = search(theKey);
    
    if (table[b] == NULL || table[b]->first != theKey)
        return NULL;
    
    return table[b];
}

template<typename K, typename E>
void hashTable<K,E>::insert(const std::pair<const K,E>& thePair) {
    int b = search(thePair.first);
    
    if (table[b] == NULL)
        table[b] = new std::pair<const K,E>(thePair);
    else {
        if (table[b]->first == thePair.first)
            table[b]->second = thePair.second;
        else
            throw hashTableFull();
    }
}

template<typename K, typename E>
class hashChain {
public:
    hashChain(int theDivisor = 11) {
        if (theDivisor <= 0) {
            std::string s = "theDivisor = " + std::string(1, theDivisor) + ", Must be > 0";
            throw illegalParameterValue(s);
        }
        
        divisor = theDivisor;
        dSize = 0;
        table = new sortedChain<K,E>[divisor];
    }
    ~hashChain() {delete [] table;}
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K& theKey) const {
        return table[hash(theKey) % divisor].find(theKey);
    }
    void insert(const std::pair<const K,E>& thePair) {
        int homeBucket = hash(theKey) % divisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        if (table[homeBucket].size() > homeSize)
            ++dSize;
    }
    void erase(const K& theKey) {
        int homeBucket = hash(theKey) % divisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].erase(theKey);
        if (table[homeBucket].size() < homeSize)
            --dSize;
    }
    
protected:
    sortedChain<K,E>* table;
    int dSize;
    int divisor;
};

template<typename K, typename E>
struct skipNode {
    typedef std::pair<const K,E> pairType;
    pairType element;
    skipNode<K,E>** next;
    
    skipNode(const pairType& thePair) : element(thePair) {next = NULL;}
    skipNode(const pairType& thePair, int size) : element(thePair) {next = new skipNode<K,E>*[size];}
};

template<typename K, typename E>
class skipList : public dictionary<K,E> {
public:
    skipList(K largeKey, int maxPairs = 10000, float prob = 0.5) {
        cutOff = prob * RAND_MAX;
        maxLevel = (int)ceil(logf((float)maxPairs) / logf(1/prob)) - 1;
        levels = 0;
        dSize = 0;
        tailKey = largeKey;
        
        std::pair<K,E> tailPair;
        tailPair.first = tailKey;
        headerNode = new skipNode<K,E>(tailPair, maxLevel + 1);
        tailNode = new skipNode<K,E>(tailPair, 0);
        last = new skipNode<K,E>*[maxLevel + 1];
        
        for (int i = 0; i <= maxLevel; ++i)
            headerNode->next[i] = tailNode;
    }
    ~skipNode() {
        while (headerNode != tailNode) {
            skipNode<K,E>* next = headerNode->next[0];
            delete headerNode;
            headerNode = next;
        }
        delete tailNode;
        delete [] last;
    }
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K& theKey) const {
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
    void insert(const std::pair<const K,E>& thePair) {
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
            last[theLevel] = headerNode;
        }
        
        skipNode<K,E>* newNode = new skipNode<K,E>(thePair, theLevel);
        for (int i = 0; i <= levels; ++i) {
            newNode->next[i] = last[i]->next[i];
            last[i]->next[i] = newNode;
        }
        
        ++dSize;
        return;
    }
    void erase(const K& theKey) {
        if (theKey > tailKey)
            return;
        
        skipNode<K,E>* theNode = search(theKey);
        
        if (theNode == NULL || theNode->element.first != theKey)
            return;
        
        for (int i = 0; i <= levels && last[i]->next[i] == theNode; ++i)
            last[i]->next[i] = theNode->next[i];
        
        while (levels > 0 && headerNode->next[levels] == tailNode)
            --levels;
        
        delete theNode;
        --dSize;
    }
    
protected:
    float cutOff;
    int maxLevel;
    int levels;
    int dSize;
    K tailKey;
    skipNode<K,E>* headerNode;
    skipNode<K,E>* tailNode;
    skipNode<K,E>** last;
    int level() const {
        int lev = 0;
        while (std::rand() <= cutOff)
            ++lev;
        return (lev <= maxLevel) ? lev : maxLevel;
    }
    skipNode<K,E>* search(const K& theKey) const {
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
};

template<typename T>
class maxPriorityQueue {
public:
    virtual ~maxPriorityQueue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T&) = 0;
};

template<typename T>
class minPriorityQueue {
public:
    virtual ~minPriorityQueue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push() = 0;
};

template<typename T>
class maxHeap : public maxPriorityQueue<T> {
public:
    maxHeap(int initialCapacity = 11) {
        if (initialCapacity < 1) {
            std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
            throw illegalParameterValue(s);
        }
        
        heapLength = initialCapacity + 1;
        heap = new T[heapLength];
        heapSize = 0;
    }
    ~maxHeap() {delete [] heap;}
    
    bool emtpy() const {return heapSize == 0;}
    int size() const {return heapSize;}
    const T& top() {
        if (heapSize == 0)
            throw queueEmpty();
        return heap[1];
    }
    void pop() {
        if (heapSize == 0)
            throw queueEmpty();
        
        heap[1].~T();
        
        T lastElement = heap[heapSize--];
        
        int currentNode = 1, child = 2;
        
        while (child <= heapSize) {
            if (child < heapSize && heap[child] < heap[child + 1])
                ++child;
            
            if (lastElement >= heap[child])
                break;
            
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }
        heap[currentNode] = lastElement;
    }
    void push(const T& theElement) {
        if (heapSize + 1 == heapLength) {
            changeLength1D(heap, heapLength, heapLength * 2);
            heapLength *= 2;
        }
        
        int currentNode = ++heapSize;
        
        while (currentNode != 1 && theElement > heap[currentNode]) {
            heap[currentNode] = heap[currentNode / 2];
            currentNode /= 2;
        }
        heap[currentNode] = theElement;
    }
    void initialize(T* theHeap, int theSize) {
        delete [] heap;
        heap = theHeap;
        heapSize == theSize;
        
        for (int root = theSize / 2; root >= 1; --root) {
            
            T rootElement = heap[root];
            
            int child = root * 2;
            
            while (child <= heapSize) {
                if (child < heapSize && heap[child] < heap[child + 1])
                    ++child;
                
                if (rootElement >= heap[child])
                    break;
                
                heap[child / 2] = heap[child];
                child *= 2;
            }
            heap[child / 2] = rootElement;
        }
    }
    
protected:
    T* heap;
    int heapLength;
    int heapSize;
};

template<typename T>
class minHeap : public minPriorityQueue {
public:
    minHeap(int initialCapacity = 11) {
        if (initialCapacity < 1) {
            std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
            throw illegalParameterValue(s);
        }
        
        heapLength = initialCapacity + 1;
        heap = new T[heapLength];
        heapSize = 0;
    }
    ~minHeap() {delete [] heap;}
    
    bool empty() const {return heapSize == 0;}
    int size() const {return heapSize;}
    const T& top() {
        if (heapSize == 0)
            throw queueEmpty();
        return heap[1];
    }
    void pop() {
        if (heapSize == 0)
            throw queueEmpty();
        
        heap[1].~T();
        
        T lastElement = heap[heapSize--];
        
        int currentNode = 1, child = 2;
        
        while (child <= heapSize) {
            if (child < heapSize && heap[child] > heap[child + 1])
                ++child;
            
            if (lastElement <= heap[child])
                break;
            
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }
        heap[currentNode] = lastElement;
    }
    void push(const T& theElement) {
        if (heapSize + 1 == heapLength) {
            changeLength1D(heap, heapLength, heapLength * 2);
            heapLength *= 2;
        }
        
        int currentNode = ++heapSize;
        
        while (currentNode != 1 && theElement < heap[currentNode]) {
            heap[currentNode] = heap[currentNode / 2];
            currentNode /= 2;
        }
        heap[currentNode] = theElement;
    }
    void initialize(T* theHeap, int theSize;) {   //数组中前一半，大的往下沉
        delete [] heap;
        heap = theHeap;
        heapSize = theSize;
        
        for (int root = theSize / 2; root >= 1; --root) {
            T rootElement = heap[root];
            
            int child = root * 2;
            
            while (child <= heapSize) {
                if (child < heapSize && heap[child] > heap[child + 1])
                    ++child;
                
                if (rootElement <= heap[child])
                    break;
                
                heap[child / 2] = heap[child];
                child *= 2;
            }
            heap[child / 2] = rootElement;
        }
    }
    
protected:
    T* heap;
    int heapLength;
    int heapSize;
};

template<typename T>
class maxHblt : public maxPriorityQueue<T>, public linkedBinaryTree<std::pair<int,T>> {
public:
    bool empty() const {return linkedBinaryTree<std::pair<int,T>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<std::pair<int,T>>::treeSize;}
    const T& top() {
        if (linkedBinaryTree<std::pair<int,T>>::treeSize == 0)
            throw queueEmpty();
        return linkedBinaryTree<std::pair<int,T>>::root->element.second;
    }
    void pop() {
        binaryTreeNode<std::pair<int,T>>* left = linkedBinaryTree<std::pair<int,T>>::root->leftChild;
                                        *right = linkedBinaryTree<std::pair<int,T>>::root->rightChild;
        delete linkedBinaryTree<std::pair<int,T>>::root;
        linkedBinaryTree<std::pair<int,T>>::root = left;
        meld(linkedBinaryTree<std::pair<int,T>>::root, right);
        ++linkedBinaryTree<std::pair<int,T>>::treeSize;
    }
    void push(const T& theElement) {
        binaryTreeNode<std::pair<int,T>>* newNode = new binaryTreeNode<std::pair<int,T>>(std::pair<int,T>(1, theElement));
        meld(linkedBinaryTree<std::pair<int,T>>::root, newNode);
        ++linkedBinaryTree<std::pair<int,T>>::treeSize;
    }
    void meld(maxHblt<T>& theHblt) {
        meld(linkedBinaryTree<std::pair<int,T>>::root, theHblt.root);
        ++linkedBinaryTree<std::pair<int,T>>::treeSize;
        theHblt.root = NULL:
        theHblt.treeSize = 0;
    }
    void initialize(T* theHeap, int theSize) {
        arrayQueue<binaryTreeNode<std::pair<int,T>>*> q(theSize);
        linkedBinaryTree<std::pair<int,T>>::erase();
        
        for (int i = 1; i <= theSize; ++i)
            q.push(new binaryTreeNode<std::pair<int, T>(std::pair<int,T>(1, theHeap)));
        
        for (int i = 1; i <= theSize; ++i) {
            binaryTreeNode<std::pair<int,T>>* b = q.front();
            q.pop();
            binaryTreeNode<std::pair<int,T>>* c = q.fornt();
            q.pop();
            meld(b,c);
            q.push(b);
        }
        
        if (theSize > 0)
            linkedBinaryTree<std::pair<int,T>>::root = q.font();
        linkedBinaryTree<std::Pair<int,T>>::treeSize = theSize;
    }
    
protected:
    meld(binaryTreeNode<std::pair<int,T>*& x, binaryTreeNode<std::pair<int,T>*& y) {
        using std::swap;
        
        if (y == NULL)
            return;
        
        if (x == NULL) {
            x = y; return;
        }
        
        if (x->element.second < y->element.second)
            swap(x, y);
        
        meld(x->rightChild, y);
        
        if (x->leftChild == NULL) {
            x->leftChild = x->rightChild;
            x->rightChild = NULL;
            x->element.first = 1;
        
        } else {
            if (x->leftChild->element.first < x->rightChild->element.first) {
                swap(x->leftChild, x->rightChild);
                x->element.first = x->rightChild->element.first + 1;
            }
        }
    }
    //先把Y融合到X中
    //最后X左右进行调整
};

template<typename T>
class binaryTree {
publci:
    virtual ~bsTree() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*)(T*)) = 0;
    virtual void inOrder(void (*)(T*)) = 0;
    virtual void postOrder(void (*)(T*)) = 0;
    virtual void levelOrder(void (*)(T*)) = 0;
};

template<typename T>
struct binaryTreeNode {
    T element;
    binaryTreeNode<T>* left;
    binaryTreeNode<T>* right;
    
    binaryTreeNode() {left = right = NULL;}
    binaryTreeNode(const T& theElement) : element(theElement) {left = right = NULL;}
    binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeft, binaryTreeNode<T>* theRight) : element(theElement) {left = theLeft; right = theRight;}
};

template<typename T>
class linkedBinaryTree : public binaryTree<T> {
public:
    
    linkedBinaryTree(int initialCapacity = 11) {root = NULL; treeSize = 0;}
    ~linkedBinaryTree() {erase();}
    
    bool empty() const {return treeSize == 0;}
    int size() const {return treeSize;}
    
    T& rootElement() {
        if (treeSize == 0)
            throw treeEmpty();
        return root->element;
    }
    void makeTree(const T& theElement, linkedBinaryTree<T>*& left, linkedBinaryTree<T>*& right) {
        root = new binaryTreeNode<T>(theElement, left.root, right.root);
        treeSize = left.treeSize + right.treeSize + 1;
        left.root = right.root = NULL;
        left.treeSize = right.treeSize = 0;
    }
    
    linkedBinaryTree<T> removeLeftSubtree() {
        linkedBinaryTree<T> leftSubtree;
        leftSubtree.root = root->leftChild;
        count = 0;
        leftSubtree.treeSize = countNodes(leftSubtree.root);
        root->leftChild = NULL;
        treeSize -= leftSubtree.treeSize;
        
        return leftSubtree;
    }
    
    linkedBinaryTree<T> removeRightSubtree() {
        linkedBinaryTree<T> leftSubtree;
        rightSubtree.root = root->leftChild;
        count = 0;
        rightSubtree.treeSize = countNodes(leftSubtree.root);
        root->rightChild = NULL;
        treeSize -= rightSubtree.treeSize;
        
        return rightSubtree;
    }
    
    void preOrder(void (*theVisit)(binaryTreeNode<T>*t)) {visit = theVisit; preOrder(root);}
    void inOrder(void (*theVisit)(binaryTreeNode<T>* t)) {visit = theVisit; inOrder(root);}
    void postOrder(void (*theVisit)(binaryTreeNode<T>* t)) {visit = theVisit; postOrder(root);}
    void levelOrder(void (*theVisit)(binaryTreeNode<T>* t)) {
        arrayQueue<binaryTreeNode<T>*> q;
        bianryTreeNode<T>* t = root;
        
        while (t != NULL) {
            theVisit(t);
            
            if (t->leftChild)
                q.push(t->leftChild);
            if (t->rightChild)
                q.push(t->rightChild);
            
            try {t = q.front();}
            catch (queueEmpty) {return;}
            q.pop();
        }
    }
                  
    void preOrderOutput() {preOrder(output); std::cout << std::endl;}
    void inOrderOutput() {inOrder(output); std::cout << std::endl;}
    void postOrderOutput() {postOrder(output); std::cout << std::endl;}
    void levelOrderOutput() {levelOrder(output); std::cout << std;:end;}
    
    void erase() {
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    int height () {return height(root);}

protected:
    binaryTreeNode<T>* root;
    int treeSize;
    
    static int count;
    static void (*theVisit)(binaryTreeNode<T>*);
    
    static void preOrder(binaryTreeNode<T>* t) {
        if (t != NULL) {
            visit(t);
            preOrder(t->left);
            preOrder(t->right);
        }
    }
    static void inOrder(binaryTreeNode<T>* t) {
        if (t != NULL) {
            inOrder(t->left);
            visit(t);
            inOrder(t->right);
        }
    }
    static void postOrder(binaryTreeNode<T>* t) {
        if (t != NULL) {
            postOrder(t->left);
            postOrder(t->right);
            visit(t);
        }
    }
    static countNodes(binaryTreeNode<T>* t) {
        count = 0;
        theVisit = addToCount;
        preOrder(t);
        return count;
    }
    static int height(binaryTreeNode<T>* t) {
        if (t == NULL)
            return 0;
        int hl = height(t->left);
        int hr = height(t->right);
        if (hl > hr)
            return ++hl;
        else
            return ++hr;
    }
    static void dispose(binaryTreeNode<T>* t) {delete t;}
    static void output(binaryTreeNode<T>* t) {std::cout << t->element << ' ';}
    static void addToCount(binaryTreeNode<T>* t) {++count;}
};

template<typename T> class hash;

template<>
class hash<std::string> {
    size_t operator(std::string theString) {
        unsigned long hashValue = 0;
        int length = (int) theString.length();
        for (int i = 0; i < length; ++i)
            hashValue = 5 * hashValue + theString.at(i);
        return size_t(hashValue);
    }
};

template <>
class hash<int> {
    size_t operator(int theInt) {return size_t(theInt);}
}

template <>
class hash<long> {
    size_t operator(long theLong) {return size_t(theLong);}
}

template<typename K,E>
class hashTable {
public:
    hashTable(int theDivisor = 11) {
        if (initialCapacity < 1) {
            std::string s = "theDivisor = " + std::string(1, initialCapacity) + ", Must be > 0";
            throw illegalParameterValue(s);
        }
        
        divisor = theDivisor;
        dSize = 0;
        
        talbe = new std::pair<const K,E>*[divisor];
        
        for (int i = 0; i < divisor; ++i)   //
            table[i] = NULL;
        
    }
    ~hashTable() {delete [] table;}
    
    bool empty() const {return arraySize;}
    int size() const {return arraySize;}
    std::pair<const K,E>* find(const K& theKey) {
        int j = search(theKey);
        
        if (table[j] == NULL || table[j]->first != theKey)
            return NULL;
        
        return table[j];
    }
    void push(const std::pair<const K,E>& thePair) {
        int j = search(theKey);
        
        if (table[j] == NULl) {
            table[j] = new std::pair<const K,E>(thePair);
            ++dSizel
        }
        else {
            if (table[j]->first == theKey)
                table[j]->second = thePair.second;
            else
                throw hashTableFull();
        }
    }
    
protected:
    int search(const K& theKey) {
        int i = hash(theKey) % divisor;
        int j = i;
        
        do {
            if (j == NULL || table[j]->first == theKey)
                return j;
            j = (j + 1) % divisor;
        } while(j != i);
        
        return j;
    }
    std::pair<const K,E>** table;
    hash<K> hash;
    int dSize;
    int divisor;
};

template<typename T>
class maxPriorityQueue {
public:
    virtual ~maxPriorityQueue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

template<typename T>
class maxHblt : public maxPriorityQueue<T>, public linkedBinaryTree<T> {
public:
    bool empty() const {return linkedBinaryTree<std::pair<int,T>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<std::pair<int,T>>::treeSize;}
    const T& top() {
        if (linkedBinaryTree<std::pair<int,T>>::treeSize == 0)
            throw queueEmpty();
        return linkedBinaryTree<std::pair<int,T>>::root->element;
    }
    void pop() {
        binaryTreeNode<std::pair<int,T>>* left = linkedBinaryTree<std::pair<int,T>>::root->leftChild,
                                        *right = linkedBinaryTree<std::pair<int,T>>::root->rightChild;
        delete linkedBinaryTree<std::pair<int,T>>::root;
        linkedBinaryTree<std::pair<int,T>>::root = left;
        meld(linkedBinaryTree<std::pair<int,T>>::root, right);
        ++linkedBinaryTree<std::pair<int,T>>::treeSize;
    }
    void push(const T& theElement) {
        binaryTreeNode<std::pair<int,T>>* newNode = new binaryTreeNode<std::pair<int,T>>(std::pair<int,T>(1, theElement));
        meld(linkedBinaryTree<std::pair<int,T>>::root, newNode);
        ++linkedBinaryTree<std::pair<int,T>>::treeSize;
    }
    void initialize(T* theElements, int theSize) {
        arrayQueue<binaryTreeNode<std::pair<int,T>> q;
        
        for (int i = 0; i < size; ++i)
            q.push(new binaryTreeNode<std::pair<int,T>>(std::pair<1, theElements[i]));
        
        for (int i = 1; i < size; ++i) {
            binaryTreeNode<std::pair<int,T>>* b = q.front();
            q.pop();
            binaryTreeNode<std::pair<int,T>>* c = q.front();
            q.pop();
            meld(b, c);
            q.push(b);
        }
        
        if (theSize > 0)
            linkedBinaryTree<std::pair<int,T>>::root = q.front();
        linkedBinaryTree<std::pair<int,T>>::treeSize = theSize;
    }
    void meld(maxHblt<T>& theHblt) {
        meld(linkedBinaryTree<std::pair<int,T>>::root, theHblt.root);
        linkedBinaryTree<std::pair<int,T>>::treeSize += theHblt.treeSize;
        theHblt.treeSize = 0;
        theHblt.root = NULL;
    }
    
protected:
    meld(binaryTreeNode<std::pair<int,T>>*& x, binaryTreeNode<std::pair<int,T>>*& y) {
        using std::swap;
        
        if (y == NULL)
            return;
        
        if (x == NULL) {
            x = y; return;
        }
        
        if (x->element.second < y->element.second)
            swap(x,y);
        
        meld(x->rightChild, y);
        
        if (x->leftChild == NULL) {
            x->leftChild = x->rightChild;
            x->rightChild = NULL;
            x->element.first = 1;
        
        } else {
            if (x->leftChild->element.second < x->rightChild->element.second) {
                swap(x->leftChild, x->rightChild);
                x->element.first = x->rightChild->element.first + 1;
            }
        }
    }
};

template<typename T>
class maxHeap : public maxPriorityQueue<T> {
public:
    maxHeap(int initialCapacity = 11) {
        if (initialCapacity < 1) {
            std::string s = "initialCapacity = " + std::string(1, initialCapacity) + ", Must be > 0";
            throw illegalParameterValue(s);
        }
        
        heapLength = initialCapacity + 1;
        heap = new T[heapLength];
        heapSize = 0;
    }
    ~maxHeap() {delete [] heap;}
    
    bool empty() const {return heapSize == 0;}
    int size() const {return heapSize;}
    const T& top() {
        if (heapSize == 0)
            throw queueEmpty();
        return heap[1];
    }
    void pop() {
        if (heapSize == 0)
            throw queueEmpty();
        
        heap[1].~T();
        
        T lastElement = heap[heapSize--];
        
        int currentNode = 1, child = 2;
        
        while (child <= heapSize) {
            if (child < heapSize && heap[child] < heap[child + 1])
                ++child;
            
            if (lastElement >= heap[child])
                break;
            
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }
        heap[currentNode] = lastElement;
    }
    void push(const T& theElement) {
        if (heapSize + 1 = heapLength) {
            changeLength1D(heap, heapLength, heapLength * 2);
            heapLength *= 2;
        }
        
        int currentNode = ++heapSize;
        
        while (currentNode != 1 && heap[currentNode / 2] < theElement) {
            heap[currentNode] = heap[currentNode / 2];
            currentNode /= 2;
        }
        heap[currentNode] = theElement;
    }
    void initialize(T* theHeap, int theSize) {
        delete [] heap;
        heap = theHeap;
        heapSize = theSize;
        
        for (int root = theSize / 2; root >= 1; --root) {
            
            T rootElement = heap[root];
            
            int child = root * 2;
            
            while (child <= heapSize) {
                if (child < heapSize && heap[child] < heap[child + 1])
                    ++child;
                
                if (rootElement >= heap[child])
                    break;
                
                heap[child / 2] = heap[child];
                child *= 2;
            }
            heap[child / 2] = rootElement;
        }
    }
    
protected:
    T* heap;
    int heapLength;
    int heapSize;
};

template<> class hash;

template<>
class hash<std::string> {
    size_t operator(const std::string& theString) {
        unsigned long hashValue = 0;
        int length = (int) theString.length();
        for (int i = 0; i < length; ++i)
            hashValue = hashValue * 5 + theString.at(i);
        return size_t(hashValue);
    }
}

template <>
class hash<int> {
    size_t operator(int theInteger) {return size_t(theInteger);}
}

template<>
class hash<long> {
    size_t operator(long theLong) {return size_t(theLong);}
}

template<typename K, typename E>
class hashTable {
public:
    hashTable(int theDivisor = 11) {
        if (theDivisor < 1) {
            std::string s = "theDivisor = " + std::string(1, theDivisor) + ", must be > 0";
            throw illegalParameterValue(s);
        }
        
        divisor = theDivisor;
        dSize = 0;
        
        table = new std::pair<int,K>*[divisor];
        for (int i = 0; i < divisor; ++i)
            table[i] = NULL;
    }
    ~hashTable() {delete [] table;}
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<K,E>* find(const K& theKey) {
        int i = search(theKey);
        
        if (table[i] == NULL || table[i]->first != theKey)
            return NULL;
        
        return table[i];
    }
    void push(const std::pair<K,E>& thePair) {
        int i = search(thePair.first);
        
        if (table[i] == NULl) {
            table[i] = new std::pair<K,E>(thePair);
            ++dSize;
        } else {
            if (table[i]->first == thePair.first)
                table[i]->second = thePair.second;
            else
                throw hashTableFull();
        }
    }
    
protected:
    int search(const K& theKey) const {
        int i = hash(theKey) % divisor;
        int j = i;
        
        do {
            if (table[j] == NULL || table[j]->first == theKey)
                return j;
            j = (j + 1) % divisor;
        } while (j != i);
        
        return j;
    }
    std::pair<K,E>** table;
    hash<T> hash;
    int dSize;
    int divisor;
};

template<typename K, typename E>
class hashChain {
public:
    hashChain(int theDivisor = 11) {
        if (theDivisor < 1) {
            std::string s = "theDivisor = " + std::string(1, theDivisor) + ", must be > 0";
            throw illegalParameterValue(s);
        }
        
        divisor = theDivisor;
        dSize = 0;
        
        table = new sortedChain<K,E>[divisor];
        for (int i = 0; i < divisor; ++i)
            table[i] = NULL;
    }
    ~hashChain() {delete [] table;}
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    E& find(const K& theKey) {
        return table[hash(theKey) % divisor].find(theKey);
    }
    void push(const std::pair<const K,E>& thePair) {
        int homeBucket = hash(thePair.first) % divisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        if (homeSize < table[homeBucket].size)
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

template<typename K, typename E>
struct skipNode {
    typedef std::pair<const K,E> pairType;
    pairType element;
    skipNode<K,E>** next;
    
    skipNode(const T& theElement, skipNode<K,E>* theNext = NULL) : element(theElement) {next = theNext;}
};

template<typename K, typename E>
class skipList : dictionary<K,E> {
public:
    skipList(K largeKey, int maxPairs, float prob) {
        cutOff = RAND_MAX * prob;
        maxLevel = (int)ceil(logf((float)maxPairs) / logf(1/prog)) - 1;
        levels = 0;
        dSize = 0;
        tailKey = largeKey;
        
        std::pair<K,E> tailPair;
        tailPair.first = tailKey;
        headerNode = new skipNode<K,E>(tailPair, maxLevel + 1);
        tailNode = new skipNode<K,E>(tailPair, 0);
        last = new skipNode<K,E>*[maxLevel + 1];
        
        for (int i = 0; i <= maxLevel; ++i)
            headerNode->next[i] = tailNode;
    }
    ~skipList() {
        while (headerNode != tailNode) {
            skipNode<K,T>* next = headerNode->next[0];
            delete headerNode;
            headerNode = next;
        }
        delete tailNode;
        delete [] last;
    }
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K& theKey) {
        if (theKey > tailKey)
            return NULL;
        
        skipNode<K,E>* beforeNode = headerNode;
        for (int i = levels; i >= 0; --i)
            while (beforeNode->next[i]->element.first < theKey)
                beforeNdoe = beforeNode->next[i];
        
        if (beforeNode != NULL && beforeNode->next[0]->element.first == theKey)
            return &beforeNode->next[0]->element;
    
        return NULL;
    }
    void erase(const K& theKey) {
        if (theKey > tailKey)
            return;
        
        skipNode<K,E>* theNode = search(theKey);
        
        if (theNode == NULL || theNode->element->first != theKey)
            return;
        
        for (int i = 0; i <= levels && last[i]->next[i] == theNode; ++i)
            last[i]->next[i] = theNode->next[i];
        
        while (levels > 0 && headerNode[levels] == theNode)
            --levels;
        
        delete theNode;
        --dSize;
    }
    void push(const std::pair<const K,E>& thePair) {
        if (thePair.first > tailKey)
            throw illegalParameterValue("must be < tailKey");
        
        skipNode<K,E>* theNode = search(theKey);
        
        if (theNode->element->first == theKey) {
            theNode->element.second = thePair.second;
            return;
        }
        
        int theLevel = level();
        if (theLevel > levels) {
            theLevel = ++levels;
            headerNode[levels] = tailNode;
        }
        
        skipNode<K,E>* newNode = new skipNode<K,E>(thePair, theLevel);
        
        for (int i = 0; i <= levels; ++i) {
            newNode->next[i] = last[i]->next[i];
            last[i]->next[i] = newNode;
        }
        
        ++dSize;
        return;
    }
    
protected:
    float cutOff;
    int maxLevel;
    int levels;
    int dSize;
    K tailKey;
    skipNode<K,E>* headerNode;
    skipNode<K,E>* tailNode;
    skipNode<K,E>** last;
    int level() const {
        int lev = 0;
        while (std::rand() <= cutOff)
            ++lev;
        return (lev < maxLevel) ? leve : maxLevel;
    }
    skipNode<K,E>* search(const K& theKey) const {
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
};

template<typename T>
class winnerTree {
public:
    virtual ~winnerTree() {};
    virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
    virtual int winner() const = 0;
    virtual void rePlay(int thePlayer) = 0;
};

template<typename T>
class completeWinnerTree : public winnerTree<T> {
public:
    completeWinnerTree(T* thePlayer, int theNumberOfPlayers) {
        tree = NULL:
        initialize(thePlayer, theNumberOfPlayers)
    }
    ~completeWinnerTree() {delete [] tree;}
    
    void initialize(T* thePlayer, int theNumberOfPlayers) {
        int n = theNumberOfPlayers;
        if (n < 2)
            throw illegalParameterValues("must have at least 2 players");
        
        player = thePlayer;
        numberOfPlayers = n;
        delete [] tree;
        tree = new int[n];
        
        int i, s;
        for (s = 1; 2 * s <= n - 1; s += s);
        
        offset = s * 2 - 1;
        lowExt = 2 * (n - s);
        
        for (i = 2; i <= lowext; i += 2)
            play((offset + i) / 2, i - 1, i);
        
        if (n % 2 == 1) {
            play((n / 2), tree[n - 1], lowext + 1);
            i = lowext + 3;
        } else i = lowext + 2;
        
        for (; i <= n; i += 2)
            play((i - lowext + n - 1) / 2, i - 1, i);
    }
    
    void replay(int thePlayer) {
        int n = numberOfPlayers;
        if (thePlayer < 1 || thePlayer > n)
            throw illegalParameterValues("illegal value of players");
        
        int matchNode, leftChild, rightChild;
        
        if (thePlayer < lowext) {
            matchNode = (offset + thePlayer) / 2;
            leftChild = matchNode * 2 - offset;
            rightChild = leftChild + 1
            
        } else {
            matchNode = (thePlayer - lowext + n - 1) / 2;
            if (matchNode == n - 1 && n % 2 == 1) {
                leftChild = matchNode * 2;
                rightChild = thePlayer;
                
            } else {
                leftChild = matchNode * 2 - (n - 1) + lowext;
                rightChild = leftChild + 1;
            }
        }
        
        tree[matchNode] = (player[tree[leftChild]] <= player[tree[rightChild]]) ? leftChild : rightChild;
        
        if (n % 2 == 1 && matchNode == n - 1) {
            matchNode /= 2;
            tree[matchNode] = (player[tree[n - 1]] <= player[tree[lowext + 1]]) ? tree[n - 1] : tree[lowext + 1];
        }
        
        for (matchNode /= 2; matchNode > 0; matchNode /= 2)
            tree[matchNode] = (player[tree[matchNode * 2]] <= player[tree[matchNode * 2 + 1]]) ? tree[matchNode * 2] : tree[matchNode * 2 + 1];
        
    }
protected:
    int offset;
    int lowext;
    int* tree;
    T* player;
    int numberOfPlayers;
    void play(int p, int leftChild, int rightChild) {
        tree[p] = (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;
        
        while (p % 2 == 1 && p > 1) {
            tree[p] = (player[tree[p - 1]] <= player[tree[p]]) ? tree[p - 1] : tree[p];
            p /= 2;
        }
    }
};

template<typename T>
class maxPriorityQueue {
public:
    virtual ~maxPriorityQueue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

template<typename T>
class maxHblt : public maxPriorityQueue<T>, public linkedBinaryTree<std::pair<int,T>> {
public:
    bool empty() const {return linkedBinaryTree<std::pair<int,T>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<std::pair<int,T>>::treeSize;}
    const T& top() {
        if (linkedBinaryTree<std::pair<int,T>>::treeSize == 0)
            throw queueEmpty();
        return linkedBinaryTree<std::pair<int,T>>::root->element.second;
    }
    void pop() {
        binaryTreeNode<std::pair<int,T>> *left = linkedBinaryTree<std::pair<int,T>>::root->leftChild,
                                        *right = linkedBinaryTree<std::pair<int,T>>::root->rightChild;
        delete linkedBinaryTree<std::pair<int,T>>::root;
        linkedBinaryTree<std::pair<int,T>>::root = left;
        meld(linkedBinaryTree<std::pair<int,T>>::root,right);
        --linkedBinaryTree<std::pair<int,T>>::treeSize;
    }
    void insert(const T& theElement) {
        binaryTreeNode<std::pair<const K,E>> *newNode = new binaryTreeNode<std::pair<int,E>>(1,theElement);
        meld(linkedBinaryTree<std::pair<int,T>>::root, newNode);
        ++linkedBinaryTree<std::pair<int,T>>::treeSize;
    }
    void initialize(T* theElements, int theSize) {
        
        linkedBinaryTree<std::pair<int,T>>::erase();
        arrayQueue<binaryTreeNode<std::pair<int,T>*> q(theSize);
        
        for (int i = 1; i <= theSize; ++i)
            q.push(new binaryTreeNode<std::pair<int,T>>(1, theElements[i]));
        
        for (int i = 1; i < theSize; ++i) {
            binaryTreeNode<std::pair<int,T>> *b = q.front();
            q.pop();
            binaryTreeNode<std::pair<int,T>> *c = q.front();
            q.pop();
            meld(b,c);
            q.push(b);
        }
        
        if (theSize > 0)
            linkedBinaryTree<std::pair<int,T>>::root = q.front();
        linkedBinaryTree<std::pair<int,T>>::treeSize = theSize;
    }
    void meld(maxHblt<T>& theTree) {
        meld(linkedBinaryTree<std::pair<int,T>>::root, theTree.root);
        linkedBinaryTree<std::pair<int,T>>::treeSize += theTree.treeSize;
        theTree.treeSize = 0;
        theTree.root = NULL;
    }
    
protected:
    void meld(binaryTreeNode<std::pair<int,T>*& x, binaryTreeNode<std::pair<int,T>*& y) {
        using std::swap;
        
        if (y == NULL)
            return;
        
        if (x == NULL) {
            x = y; return;
        }
        
        if (x->element.second < y->element.second)
            swap(x,y);
        
        meld(x->rightChild, y);
        
        if (x->leftChild == NULL) {
            x->leftChild = x->rightChild;
            x->rightChild = NULL;
            x->element.first = 1;
            
        } else {
            if (x->leftChild->element.first < x->rightChild->element.first) {
                swap(x->leftChild, x->rightChild);
                x->element.first = x->rightChild->element.first + 1;
            }
        }
    }
};


template<typename K, typename E>
class bsTree : public dictionary<K,E> {
public:
    virtual void ascend() = 0;
};

template<typename K, typename E>
class binarySearchTree : public bsTree<K,E>, public linkedBinaryTree<std::pair<const K,E>> {
public:
    bool empty() const {return linkedBinaryTree<std::pair<const K,E>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<std::pair<const K,E>>::treeSize;}
    std::pair<const K,E>* find(const K& theKey) const {
        
        binaryTreeNode<std::pair<const K,E>> *p = linkedBinaryTree<std::pair<const K,E>>::root;
        
        while (p != NULL) {
            if (p->element.first < theKey)
                p = p->rightChild;
            else
                if (p->element.first > theKey)
                    p = p->leftChild;
                else
                    return &p->element;
        }
        
        return NULL;
    }
    void erase(const K& theKey) {
        
        binaryTreeNode<std::pair<const K,E>> *p = linkedBinaryTree<std::pair<const K,E>>::root, *pp = NULL;
        
        while (p != NULL && p->element.first != theKey)
            if (p->element.first < theKey)
                p = p->rightChild;
            else
                p = p->leftChild;
        
        if (p == NULL)
            return;
        
        if (p->leftChild != NULL && p->rightChild != NULL) {
        
            binaryTreeNode<std::pair<const K,E> *s = p->leftChild, *ps = p;
            
            while (s->rightChild != NULL) {
                ps = s;
                s = s->rightChild;
            }
            
            binaryTreeNode<std::pair<const K,E>> *q = new binaryTreeNode<std::pair<const K,E>>(s->element, p->leftChild, p->rightChild);
            
            if (pp == NULL)
                linkedbinaryTree<std::pair<const K,E>>::root = q;
            else
                if (pp->leftChild == p)
                    pp->leftchild = q;
                else
                    pp->rightChild = q;
            
            if (ps == p) pp = q;
            else pp = ps;
            
            delete p;
            p = s;
        }
        
        binaryTreeNode<std::pair<const K,E>> *c;
        if (p->leftChild != NULL)
            c = p->leftChild;
        else
            c = p->rightChild;
        
        if (p == linkedBinaryTree<std::pair<const K,E>>::root)
            linkedBinaryTree<std::pair<const K,E>>::root = c;
        else
            if (p = pp->leftChild)
                pp->leftChild = c;
            else
                pp->rightChild = c;
        
        --linkedBinaryTree<std::pair<const K,E>>::treeSize;
        delete p;
    }
    void insert(const std::pair<const K,E>& thePair) {
        
        binaryTreeNode<std::pair<const K,E> *p = linkedBinaryTree<std::pair<const K,E>>::root, *pp = NULL;
        
        while (p != NULL) {
            pp = p;
            
            if (p->element.first < thePair.first)
                p = p->rightChild;
            else
                if (p->element.first > thePair.first)
                    p = p->leftChild;
                else {
                    p->element.second = thePair.second;
                    return;
                }
        }
        
        binaryTreeNode<std::pair<const K,E>> *newNode = new binaryTreeNode<std::pair<const K,E>>(thePair);
        
        if (linkedBinaryTree<std::pair<const K,E>>::root != NULL)
            if (pp->leftChild == NULL)
                pp->leftChild = newNode;
            else
                pp->rightChild = newNode;
        else
            linkedBinaryTree<std::pair<const K,E>>::root = newNode;
        
        ++linkedBinaryTree<std::pair<const K,E>>::treeSize;
    }
    void ascend() {linkedBinaryTree<std::pair<const K,E>>::inOrderOutput();}
};

template<typename T>
class maxPriorityQueue {
public:
    virtual ~maxPriorityQueue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

template<typename T>
class maxHblt : public maxPriorityQueue<T>, public linkedBinaryTree<std::pair<int,T>> {
public:
    bool empty() const {return linkedBinaryTree<std::pair<const K,E>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<std::pair<const K,E>>::treeSize;}
    T& top() {
        if (linkedBinaryTree<std::pair<int,T>>::treeSize == 0)
            throw queueEmpty();
        return linkedBinaryTree<std::pair<int,T>>::tree[1];
    }
    void pop() {
        binaryTreeNode<std::pair<int,T>> *left = linkedBinaryTree<std::pair<int,T>>::root->leftChild,
                                        *right = linkedBinaryTree<std::pair<int,T>>::root->rightChild;
        delete linkedBinaryTree<std::pair<int,T>>::root;
        linkedBinaryTree<std::pair<int,T>>::root = left;
        meld(linkedBinaryTree<std::pair<int,T>>::root, right);
        --linkedBinaryTree<std::pair<int,T>>::treeSize;
    }
    void push(const T& theElement) {
        bianryTreeNode<std::pair<int,T>> *newNode = new binaryTreeNode<std::pair<int,T>>(1, theElement);
        meld(linkedBinaryTree<std::pair<const K,E>>::root, newNode);
        ++linkedBinaryTree<std::pair<const K,E>>::treeSize;
    }
    void initialize(T* theElements, int size) {
        arrayQueue<binaryTreeNode<std::pair<int,T>>*> q(size);
        for (int i = 1; i < size; ++i)
            q.push(new binaryTreeNode<std::pair<int,T>>(1, theElements[i]));
                   
        for (int i = 1; i< size; ++i) {
            binaryTreeNode<std::pair<int,T>> *b = q.front();
            q.pop();
            binaryTreeNode<std::pair<int,T>> *c = q.front();
            q.pop();
            meld(b,c);
            q.push(b);
        }
        
        if (size > 0)
            linkedBinaryTree<std::pair<int,T>>::root = q.front();
        linkedBinaryTree<std::pair<int,T>>::treeSize == size;
    }
    void meld(maxHblt<T>& theHblt) {
        meld(linkedBinaryTree<std::pair<int,T>>::root, theHblt.root);
        linkedBinaryTree<std::pair<int,T>>::treeSize += theHblt.treeSize;
        theHblt.treeSize = 0;
        theHblt.root = NULL;
    }
    
protected:
    void meld(binaryTreeNode<std::pair<int,T>>*& x, binaryTreeNode<std::pair<int,T>>*& y) {
        using std::swap;
        
        if (y == NULL)
            return;
        
        if (x == NULL) {
            x = y; return;
        }
        
        if (x->element.second < y->element.second)
            swap(x, y);
        
        meld(x->rightChild, y);
        
        if (x->leftChild == NULL) {
            x->leftChild = x->rightChild;
            x->rightChild = NULL;
            x->element.first = 1;
            
        } else {
            if (x->leftChild->element.first < x->rightChild->element.first) {
                swap(x->leftChild, x->rightChild);
                x->element.first = x->rightChild->element.first + 1;
            }
        }
    }
};

template<typename T>
struct binaryTreeNode {
public:
    T element;
    binaryTreeNode<T> *leftChild;
    binaryTreeNode<T> *rightChild;
    
    bianryTreeNode() {leftChild = rightChild = NULL;}
    binaryTreeNode(const T& theElement) : element(theElement) {leftChild = rightChild = NULL;}
    binaryTreeNode(const T& theElement, binartTreeNode<T>* left, binaryTreeNode<T>* right) : element(theElement) {leftChild = left; rightChild = right;}
};

template<typename K, typename E>
class binaryTree {
public:
    virtual ~binaryTree() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*)(T*)) = 0;
    virtual void inOrder(void(*)(T*)) = 0;
    virtual void postOrder(void (*)(T*)) = 0;
    virtual void levelOrder(void (*)(T*)) = 0;
};

template<typename T>
class linkedBinaryTree : public binaryTree<binaryTreeNode<T>> {
public:
    linkedBinaryTree() {root = NULL; treeSize = 0;}
    ~linkedBinaryTree() {erase();}
    
    T* rootElement() {
        if (treeSize == 0)
            return NULL;
        else
            return &root->element;
    }
    void makeTree(const T& theElement, binaryTreeNode<T>& left, binaryTreeNode<T>& right) {
        root = new bianryTreeNode<T>(theElement,left.root,right.root);
        treeSize = left.treeSize + right.treeSize + 1;
        left.treeSize = right.treeSize = 0;
        left.root = right.root = NULL;
    }
    
    bool empty() const {return treeSize == 0;}
    int size() const {return treeSize;}
    
    linkedBinaryTree<T>* removeLeftSubtree() {
        linkedBinaryTree<T> *leftSubtree = new linkedBinaryTree<T>();
        leftSubtree.root = root->leftChild;
        count = 0;
        leftSubtree.treeSize = countNodes(leftSubtree.root);
        root->leftChild = NULL;
        treeSize -= leftSubtree.treeSize;
        return leftSubtree;
    }
    
    linkedBinaryTree<T>* removeRightSubtree() {
        linkedBinaryTree<T> *rightSubtree = new linkedBinaryTree<T>();
        rightSubtree.root = root->rightChild;
        count = 0;
        rightSubtree.treeSize = countNodes(rightSubtree.root);
        root->rightChild = NULL;
        treeSize -= rightSubtree.treeSize;
        return rightSubtree;
    }
    
    void preOrder(void (*theVisit)(bianryTreeNode<T>* t)) {visit = theVisist; preOrder(root);}
    void inOrder(void (*theVisit)(binaryTreeNode<T>* t)) {viist = theVisit; inOrder(root);}
    void postOrder(void (*theVisit)(binaryTreeNode<T>* t)) {viist = theVisit; postOrder(root);}
    void levelOrder(void (*theVisit)(binaryTreeNode<T>* t)) {
        
        arrayQueue<binaryTreeNode<T>*> q;
        binaryTreeNode<T>* t = root;
        
        while (t != NULL) {
            theVisit(t);
            
            if (t->leftChild != NULL)
                q.push(t->leftChild);
            if (t->rightChild != NULL)
                q.push(t->rightChild);
            
            try {t = q.front();}
            catch(queueEmpty) {return;}
            q.pop();
        }
    }
    
    void preOrderOutput() {preOrder(output); std::cout << std::endl;}
    void inOrderOutput() {inOrder(output); std::cout << std::end;}
    void postOrderOutput() {postOrder(output); std::cout << std::end;}
    void levelOrderOutput() {levelOrder(output); std:;cout << std::end;}
    
    int height() const {return height(root);}
    void erase() {
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    
protected:
    binaryTreeNode<T>* root;
    int treeSize;
    
    static int count;
    static void (*visit)(void (*)(binaryTreeNode<T>*));
    
    static void preOrder(binaryTreeNode<T>* t) {
        if (t != NULL) {
            visit(t);
            preOrder(t->leftChild);
            preOrder(t->rightChild);
        }
    }
    
    static void inOrder(binaryTreeNode<T>* t) {
        if (t != NULL) {
            inOrder(t->leftChild);
            visit(t);
            inOrder(t->rightChild);
        }
    }
    
    static void postOrder(binaryTreeNode<T>* t) {
        if (t != NULL) {
            postOrder(t->leftChild);
            postOrder(t->rightChild);
            visit(t);
        }
    }
    
    static int countNodes(binaryTreeNode<T>* t) {
        visit = addToCount;
        count = 0;
        preOrder(t);
        return count;
    }
    
    static void addToCount(binaryTreeNode<T>* t) {++count;}
    static void dispose(binaryTreeNode<T>* t) {delete t;}
    static void output(binaryTreeNode<T>* t) {std::cout << t->element << ' ';}
    
    static int height(binaryTreeNode<T>* t) {
        if (t == NULL)
            return 0;
        int hl = height(t->leftChild);
        int hr = height(t->rightChild);
        if (hl < hr)
            return ++hl;
        else
            return ++hr;
    }
};

template<typename K, typename E>
class bsTree : public dictionary<K,E> {
public:
    virtual void ascend() = 0;
};

template<typename K, typename E>
class binarySearchTree : public bsTree<T>, public linkedBinaryTree<std::pair<const K,E>> {
public:
    bool empty() const {return linkedBinaryTree<std::pair<const K,E>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<std::pair<const K,E>>::treeSize;}
    
    std::pair<const K,E>* find(const K& theKey) {
        
        bianryTreeNode<std::pair<const K,E> *p = linkedBinaryTree<std::pair<const K,E>>::root;
        
        while (p != NULL) {
            if (p->element.first < theKey)
                p = p->rightChild;
            else
                if (p->element.first > theKey)
                    p = p->leftChild;
                else
                    return &p->element;
        }
        
        return NULL;
    }
    
    void insert(const std::pair<const K,E>& thePair) {
        
        binaryTreeNode<std::pair<const K,E>> *p = linkedBinaryTree<std::pair<const K,E>>::root;
        
        while (p != NULL) {
            if (p->element.first < theKey)
                p = p->rightChild;
            else
                if (p->element.first > theKey)
                    p = p->leftchild;
                else {
                    p->element.second = thePair.second;
                    return;
                }
        }
        
        binaryTreeNode<std::pair<const K,E>> *newNode = new binaryTreeNode<std::pair<const K,E>>(thePair);
        
        if (linkedBinaryTree<std::pair<const K,E>>::root != NULL)
            if (pp->leftChild == p)
                pp->leftChild = newNode;
            else
                pp->rightChild = newNode;
        else
            linkedBinaryTree<std::pair<const K,E>>::root = newNode;
        ++linkedBinaryTree<std::pair<const K,E>>::treeSize;
    }
    
    void erase(const K& theKey) {
        
        binaryTreeNode<std::pair<const K,E>> *p = linkedBinaryTree<std::pair<const K,E>>::root, *pp = NULL;
        
        while (p != NULL && p->element.first != theKey) {
            if (p->element.first < theKey)
                p = p->rightChild;
            else
                p = p->leftChild;
        }
        
        if (p == NULL)
            return;
        
        if (p->leftChild != NULL && p->rightChild != NULL) {
        
            binaryTreeNode<std::pair<const K,E>> *s = p->leftChild, *ps = p;
            
            while (s->rightChild != NULL) {
                ps = s;
                s = s->rightChild;
            }
            
            binaryTreeNode<std::pair<const K,E>> *q = new binaryTreeNode<std::pair<const K,E>>(s->element, p->leftChild, p->rightChild);
            
            if (pp == NULL)
                linkedBinaryTree<std::pair<const K,E>>::root = q;
            else
                if (pp->leftChild == p)
                    pp->leftchild = q;
                else
                    pp->rightChild = q;
            
            if (ps = p) pp = q;
            else pp = ps;
            
            delete p;
            p = s;
        }
        
        binaryTreeNode<std::pair<const K,E>> *c;
        if (p->leftChild != NULl)
            c = p->leftChild;
        else
            c = p->rightChild;
        
        if (p == linkedBinaryTree<std::pair<const K,E>>::root)
            linkedBinaryTree<std::pair<const K,E>>::root = c;
        else
            if (pp->leftChild == p)
                pp->leftChild = c;
            else
                pp->rightChild = c;
        
        --linkedBinaryTree<std::pair<const K,E>>::treeSize;
        delete p;
    }
    
    void ascend() {linkedBinaryTree<std::pair<const K,E>>::inOrderOutput();}
};



#endif /* test_hpp */
