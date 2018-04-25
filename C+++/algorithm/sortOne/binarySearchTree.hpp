//
//  binarySearchTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/22.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef binarySearchTree_hpp
#define binarySearchTree_hpp

#include "bsTree.hpp"
#include "linkedBinaryTree.hpp"

//二叉搜索树是一颗二叉树，可能为空，一颗非空的二叉树满足以下特征
//每个元素有一个关键字，并且任意两个元素的关键字都不同，因此所有的关键字都是唯一的
//在根节点左子树中，元素的关键字(如果有的话)都小于根节点的关键字
//在根节点的右子树中，元素的关键字(如果有的话)都大于根节点的关键字
//根节点的左右字树叶都是二叉搜索树

template<typename K, typename E>
class binarySearchTree : public bsTree<K,E>, public linkedBinaryTree<std::pair<const K, E>> {
public:
    bool empty() const {return linkedBinaryTree<std::pair<const K, E>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<std::pair<const K, E>>::treeSize;}
    std::pair<const K,E>* find(const K& theKey) const;
    void insert(const std::pair<const K,E>& thePair);
    void erase(const K& theKey);
    void ascend() {linkedBinaryTree<std::pair<const K, E>>::inOrderOutput();}
};

template<typename K, typename E>
std::pair<const K,E>* binarySearchTree<K,E>::find(const K& theKey) const {
    binaryTreeNode<std::pair<const K,E>>* p = linkedBinaryTree<std::pair<const K, E>>::root;
    while (p != NULL)
        if (theKey < p->element.first)
            p = p->leftChild;
        else
            if (theKey > p->element.first)
                p = p->rightChild;
            else
                return &p->element;
    return NULL;
}

template<typename K, typename E>
void binarySearchTree<K,E>::insert(const std::pair<const K,E>& thePair) {
    binaryTreeNode<std::pair<const K,E>>* p = linkedBinaryTree<std::pair<const K, E>>::root, *pp = NULL;
    
    while (p != NULL) {
        pp = p;
        
        if (thePair.first < p->element.first)
            p = p->leftChild;
        else
            if (thePair.first > p->element.first)
                p = p->rightChild;
            else
            {
                p->element.second = thePair.second;
                return;
            }
    }
    
    binaryTreeNode<std::pair<const K,E>>* newNode = new binaryTreeNode<std::pair<const K,E>>(thePair);
    if (linkedBinaryTree<std::pair<const K, E>>::root != NULL)
        if (thePair.first < pp->element.first)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;
    else
        linkedBinaryTree<std::pair<const K, E>>::root = newNode;
    linkedBinaryTree<std::pair<const K, E>>::treeSize++;
}

template<typename K, typename E>
void binarySearchTree<K,E>::erase(const K& theKey) {
    binaryTreeNode<std::pair<const K,E>>* p = linkedBinaryTree<std::pair<const K, E>>::root, *pp = NULL;
    
    while (p != NULL && p->element.first != theKey) {
        pp = p;
        if (theKey < p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    
    if (p == NULL)
        return;
    
    //删除两个节点的情况，最终变成删除一个节点的情况
    if (p->leftChild != NULL && p->rightChild != NULL) {
        binaryTreeNode<std::pair<const K,E>>* s = p->leftChild, *ps = p;
        
        while (s->rightChild != NULL) {
            ps = s;
            s = s->rightChild;
        }
        
        binaryTreeNode<std::pair<const K,E>>* q = new binaryTreeNode<std::pair<const K,E>>(s->element, p->leftChild, p->rightChild);
        
        if (pp == NULL)
            linkedBinaryTree<std::pair<const K, E>>::root = q;
        else
            if (p == pp->leftChild)
                pp->leftChild = q;
            else
                pp->rightChild = q;
        
        if (ps == p) pp = q;
        else pp = ps;
        
        delete p;
        p = s;
    }
    
    //删除一个节点的情况
    binaryTreeNode<std::pair<const K,E>>* c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;
    
    if (p == linkedBinaryTree<std::pair<const K,E>>::root)
        linkedBinaryTree<std::pair<const K,E>>::root = c;
    else {
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    
    --linkedBinaryTree<std::pair<const K,E>>::treeSize;
    delete p;
}

#endif /* binarySearchTree_hpp */
