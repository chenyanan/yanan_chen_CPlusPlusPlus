//
//  skipList.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/20.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef skipList_hpp
#define skipList_hpp

#include <math.h>
#include <string>
#include "dictionary.hpp"
#include "skipNode.hpp"
#include "myException.hpp"

template<typename K, typename E>
class skipList : public dictionary<K,E> {
public:
    skipList(K, int maxPairs = 10000, float prob = 0.5);
    ~skipList();
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K&) const;
    void erase(const K&);
    void insert(const std::pair<const K,E>&);
    
protected:
    float cutOff;
    int level() const;
    int levels;
    int dSize;
    int maxLevel;
    K tailKey;
    skipNode<K,E>* search(const K&) const;
    skipNode<K,E>* headerNode;
    skipNode<K,E>* tailNode;
    skipNode<K,E>** last;
};

template<typename K, typename E>
skipList<K,E>::skipList(K largeKey, int maxPairs, float prob) {
    cutOff = prob * RAND_MAX;
    maxLevel = (int)ceil(logf((float) maxPairs) / logf(1/prob)) - 1;
    levels = 0;
    dSize = 0;
    tailKey = largeKey;
    
    std::pair<const K,E> tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K,E>(tailPair, maxLevel + 1);
    tailNode = new skipNode<K,E>(tailPair,0);
    last = new skipNode<K,E>*[maxLevel + 1];
    
    for (int i = 0; i <= maxLevel; ++i)
        headerNode->next[i] = tailNode;
}

template<typename K, typename E>
skipList<K,E>::~skipList() {
    skipNode<K,E> *nextNode;
    
    while (headerNode != tailNode) {
        nextNode = headerNode->next[0];
        delete headerNode;
        headerNode = nextNode;
    }
    delete tailNode;
    delete[] last;
}

template<typename K, typename E>
std::pair<const K,E>* skipList<K,E>::find(const K& theKey) const {
    if (theKey >= tailKey)
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
int skipList<K,E>::level() const {
    int lev = 0;
    while(rand() <= cutOff)
        ++lev;
    return (lev <= maxLevel) ? lev : maxLevel;
}

template<typename K, typename E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const {
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
    if (thePair.first >= tailKey)
        throw illegalParameterValue("Must be tailKey");
    
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
    
    skipNode<K,E>* newNode = new skipNode<K,E>(thePair, theLevel + 1);
    for (int i = 0; i <= theLevel; ++i) {
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }
    
    dSize++;
    return;
}

template<typename K, typename E>
void skipList<K,E>::erase(const K& theKey) {
    if (theKey >= tailKey)
        return;
    
    skipNode<K,E>* theNode = search(theKey);
    if (theNode->element.first != theKey)
        return;
    
    for (int i = 0; i <= levels && last[i]->next[i] == theNode; ++i)
        last[i]->next[i] = theNode->next[i];
    
    while (levels > 0 && headerNode->next[levels] == tailNode)
        levels--;
    
    delete theNode;
    dSize--;
}


#endif /* skipList_hpp */
