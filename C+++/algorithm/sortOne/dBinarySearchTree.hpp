//
//  dBinarySearchTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/23.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef dBinarySearchTree_hpp
#define dBinarySearchTree_hpp

#include "binarySearchTree.hpp"

template<typename K, typename E>
class dBinarySearchTree : public binarySearchTree<K,E> {
public:
    void insert(const std::pair<const K,E>&);
};

template<typename K, typename E>
void dBinarySearchTree<K,E>::insert(const std::pair<const K,E>& thePair) {
    binaryTreeNode<std::pair<const K,E>>* p = binarySearchTree<K,E>::root, *pp = NULL;
    
    while (p != NULL) {
        pp = p;/Users/chenyanan/Desktop/C+++/C+++/算法/sortOne/dictionary.hpp
        
        if (thePair.first <= p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    
    binaryTreeNode<std::pair<const K,E>>* newNode = new binaryTreeNode<std::pair<const K,E>>(thePair);
    
    if (binarySearchTree<K,E>::root != NULL)
        if (thePair.first <= pp->element.first)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;
    else
        binarySearchTree<K,E>::root = newNode;
    binarySearchTree<K,E>::treeSize++;
}

template<typename K, typename E>
class dBinarySearchTreeWithGE : public dBinarySearchTree<K,E> {
public:
    std::pair<const K,E>* findGE(const K& theKey) const;
};

template<typename K, typename E>
std::pair<const K,E>* dBinarySearchTreeWithGE<K,E>::findGE(const K& theKey) const {
    binaryTreeNode<std::pair<const K,E>>* currentNode = binarySearchTree<K,E>::root;
    std::pair<const K,E>* bestElement = NULL;
    
    while (currentNode != NULL)
        if (currentNode->element.first >= theKey) {
            bestElement = &currentNode->element;
            currentNode = currentNode->leftChild;
        }
        else
            currentNode = currentNode->rightChild;
    
    return bestElement;
}

#endif /* dBinarySearchTree_hpp */
