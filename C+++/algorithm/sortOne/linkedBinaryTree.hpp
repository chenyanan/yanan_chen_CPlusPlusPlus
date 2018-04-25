//
//  linkedBinaryTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/21.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef linkedBinaryTree_hpp
#define linkedBinaryTree_hpp

#include <iostream>
#include "binaryTree.hpp"
#include "binaryTreeNode.hpp"
#include "myException.hpp"
#include "queue.hpp"

struct booster {
    int degradeToLeaf, degradeFromParent;
    bool boosterHere;
    
    void output(std::ostream& out) const {
        std::cout << boosterHere << ' ' << degradeToLeaf << ' ' << degradeFromParent << ' ';
    }
};

template<typename E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>> {
public:
    linkedBinaryTree() {root = NULL; treeSize = 0;}
    ~linkedBinaryTree() {erase();}
    bool empty() const {return treeSize == 0;}
    int size() const {return treeSize;}
    E* rootElement() const;
    void makeTree(const E& element, linkedBinaryTree<E>&, linkedBinaryTree<E>&);
    linkedBinaryTree<E>& removeLeftSubtree();
    linkedBinaryTree<E>& removeRightSubtree();
    
    void preOrder(void(*theVisit)(binaryTreeNode<E>*)) {visit = theVisit; preOrder(root);}
    void inOrder(void(*theVisit)(binaryTreeNode<E>*)) {visit = theVisit; inOrder(root);}
    void postOrder(void(theVisit)(binaryTreeNode<E>*)) {visit = theVisit; postOrder(root);}
    void levelOrder(void(*)(binaryTreeNode<E>*));
    
    void preOrderOutput() {preOrder(output); std::cout << std::endl;}
    void inOrderOutput() {inOrder(output); std::cout << std::endl;}
    void postOrderOutput() {postOrder(output); std::cout << std::endl;}
    void levelOrderOutput() {levelOrder(output); std::cout << std::endl;}
    
    void erase() {
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    int height() const { return height(root);}
    
protected:
    binaryTreeNode<E> *root;
    int treeSize;
    static void (*visit)(binaryTreeNode<E>*);
    static int count;
    static void preOrder(binaryTreeNode<E>* t);
    static void inOrder(binaryTreeNode<E>* t);
    static void postOrder(binaryTreeNode<E>* t);
    static void countNodes(binaryTreeNode<E>* t) {
        visit = addToCount;
        count = 0;
        preOrder(t);
    }
    static void dispose(binaryTreeNode<E>* t) {delete t;}
    static void output(binaryTreeNode<E>* t) { std::cout << t->element << ' ';}
    static void addToCount(binaryTreeNode<E>* t) {count++;}
    static int height(binaryTreeNode<E>* t);
};

template<> void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
template<> void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
template<> void (*linkedBinaryTree<std::pair<int,int>>::visit)(binaryTreeNode<std::pair<int,int>>*);
template<> void (*linkedBinaryTree<std::pair<const int, char>>::visit)(binaryTreeNode<std::pair<const int,char>>*);
template<> void (*linkedBinaryTree<std::pair<const int,int>>::visit)(binaryTreeNode<std::pair<const int,int>>*);

template<typename E>
E* linkedBinaryTree<E>::rootElement() const {
    if (treeSize == 0)
        return NULL;
    else
        return &root->element;
}

template<typename E>
void linkedBinaryTree<E>::makeTree(const E& element, linkedBinaryTree<E>& left, linkedBinaryTree<E>& right) {
    root = new binaryTreeNode<E>(element, left.root, right.root);
    treeSize= left.treeSize + right.treeSize + 1;
    
    left.root = right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template<typename E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree() {
    if (treeSize == 0)
        throw treeEmpty();
    
    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = root->leftChild;
    count = 0;
    leftSubtree.treeSize = countNodes(leftSubtree.root);
    root->leftChild = NULL;
    treeSize -= leftSubtree.treeSize;
    
    return leftSubtree;
}

template<typename E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree() {
    if (treeSize == 0)
        throw treeEmpty();
    
    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = root->rightChild;
    count = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root);
    root->rightChild = NULL;
    treeSize -= rightSubtree.treeSize;
    
    return rightSubtree;
}

template<typename E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E>* t) {
    if (t != NULL) {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<typename E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E>* t) {
    if (t != NULL) {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

template<typename E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>* t) {
    if (t != NULL) {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

template<typename E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E>*)) {
    arrayQueue<binaryTreeNode<E>*> q;
    binaryTreeNode<E>* t = root;
    while (t != NULL) {
        theVisit(t);
        if (t->leftChild != NULL)
            q.push(t->leftChild);
        if (t->rightChild != NULL)
            q.push(t->rightChild);
        
        try{t = q.front();}
        catch (queueEmpty) {return;}
        q.pop();
    }
}

template<typename E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t) {
    if (t == NULL)
        return 0;
    int hl = height(t->leftChild);
    int hr = height(t->rightChild);
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}

#endif /* linkedBinaryTree_hpp */
