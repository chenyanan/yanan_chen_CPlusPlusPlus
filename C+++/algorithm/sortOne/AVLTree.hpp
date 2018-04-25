//
//  AVLTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/3/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <stdio.h>
#include "linkedBinaryTree.hpp"



template<typename K, typename E>
struct avlNode {
    const K key;
    E val;
    int bf;
    
    avlNode(const std::pair<const K,E>& thePair) : key(thePair.first), E(thePair.second) {bf = 0;}
    avlNode(const K& theKey, const E& theVal) : key(theKey), val(theVal) {bf = 0;}
    avlNode(const K& theKey, const E& theVal, const int& theBF) : key(theKey), val(theVal) {bf = theBF;}
};

template<typename K, typename E>
class linkedAVLTree : public bsTree<K,E>, public linkedBinaryTree<avlNode<K,E>> {
public:
    bool empty() const {return linkedBinaryTree<avlNode<K,E>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<avlNode<K,E>>::treeSize;}
    avlNode<K,E>* find(const K& theKey) {
    
        avlNode<K,E> *p = linkedBinaryTree<avlNode<K,E>>::root, *pp = NULL;
        
        while (p != NULL)
            if (p->key < theKey)
                p = p->rightChild;
            else
                if (p->ley > theKey)
                    p = p->leftChild;
                else
                    return &p->element;
        
        return NULL;
    }
}

#endif /* AVLTree_hpp */
