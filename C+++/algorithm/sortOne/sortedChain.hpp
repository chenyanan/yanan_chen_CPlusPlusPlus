//
//  sortedChain.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/20.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef sortedChain_hpp
#define sortedChain_hpp

#include "dictionary.hpp"
#include "pairNode.hpp"

template<typename K, typename E>
class sortedChain : public dictionary<K,E> {
public:
    sortedChain() {firstNode = NULL; dSize = 0;}
    ~sortedChain();
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K&) const;
    void erase(const K&);
    void insert(const std::pair<const K,E>&);
    
protected:
    pairNode<K,E>* firstNode;
    int dSize;
};

template<typename K, typename E>
sortedChain<K,E>::~sortedChain() {
    while (firstNode != NULL) {
        pairNode<K,E>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<typename K, typename E>
std::pair<const K,E>* sortedChain<K,E>::find(const K& theKey) const {
    pairNode<K,E>* currentNode = firstNode;
    
    while (currentNode != NULL &&
           currentNode->element.first != theKey)
        currentNode = currentNode->next;
    
    if (currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element;
    
    return NULL;
}

template<typename K, typename E>
void sortedChain<K,E>::insert(const std::pair<const K,E>& thePair) {
    pairNode<K,E> *p = firstNode, *tp = NULL;
    
    while (p != NULL && p->element.first < thePair.first) {
        tp = p;
        p = p->next;
    }
    
    if (p != NULL && p->element.first == thePair.first) {
        p->element.second = thePair.second;
        return;
    }
    
    pairNode<K,E> *newNode = new pairNode<K,E>(thePair, p);
    
    if (tp == NULL) firstNode = newNode;
    else tp->next = newNode;
    
    dSize++;
    return;
}

template<typename K, typename E>
void sortedChain<K,E>::erase(const K& theKey) {
    pairNode<K,E>* p = firstNode, tp = NULL;
    
    while (p != NULL && p->element.first != theKey) {
        tp = p;
        p = p->next;
    }
    
    if (p != NULL && p->element.first == theKey) {
        if (tp == NULL) firstNode = p->next;
        else tp->next = p->next;
        
        delete p;
        --dSize;
    }
}

#endif /* sortedChain_hpp */
