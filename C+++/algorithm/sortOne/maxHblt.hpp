//
//  maxHblt.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/22.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef maxHblt_hpp
#define maxHblt_hpp

#include "maxPriorityQueue.hpp"
#include "linkedBinaryTree.hpp"
#include "binaryTreeNode.hpp"
#include "myException.hpp"
#include "maxHeap.hpp"
#include <utility>

//令s值是从节点到其子树的外部节点的所有路径中最短的一条
//一颗二叉树称为高度优先左高树，当且仅当其中任何一个内部节点的左孩子的s值都大于或等于右孩子的s值
//若一颗左高树同时还是一颗大根树，则称为maxHblt

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
    void pop();
    void push(const T&);
    void initialize(T*,int);
    void meld(maxHblt<T>& theHblt) {
        meld(linkedBinaryTree<std::pair<int,T>>::root, theHblt.root);
        linkedBinaryTree<std::pair<int,T>>::treeSize += theHblt.treeSize;
        theHblt.root = NULL;
        theHblt.treeSize = 0;
    }
private:
    void meld(binaryTreeNode<std::pair<int,T>>*&, binaryTreeNode<std::pair<int,T>>* &);
};

template<typename T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int,T>>* &x,binaryTreeNode<std::pair<int,T>>* &y) {
    using std::swap;
    
    if (y == NULL)
        return ;
    
    if (x == NULL) {
        x = y; return ;
    }
    
    if (x->element.seconde < y->element.second)
        swap(x, y);
    
    meld(x->rightChild,y);
    
    if (x->leftChild == NULL) {
        x->leftChild = x->rightChild;
        x->rightChild = NULL;
        x->element.first = 1;
    
    } else {
        if (x->leftChild->element.first < x->rightChild->element.first)
            swap(x->leftChild, x->rightChild);
        x->element.first = x->rightChild->element.first + 1;
    }
    
    //现将y融入到x里面去，然后x里面的left和right在做最终调整
}

template<typename T>
void maxHblt<T>::push(const T& theElement) {
    binaryTreeNode<std::pair<int,T>>* q = new binaryTreeNode<std::pair<int,T>>(std::pair<int,T>(1, theElement));
    meld(linkedBinaryTree<std::pair<int,T>>::root,q);
    linkedBinaryTree<std::pair<int,T>>::treeSize++;
}

template<typename T>
void maxHblt<T>::pop() {
    if (linkedBinaryTree<std::pair<int,T>>::root == NULL)
        throw queueEmpty();
    
    binaryTreeNode<std::pair<int,T>>* left = linkedBinaryTree<std::pair<int,T>>::root->leftChild,
                                    *right = linkedBinaryTree<std::pair<int,T>>::root->rightChild;
    delete linkedBinaryTree<std::pair<int,T>>::root;
    linkedBinaryTree<std::pair<int,T>>::root = left;
    meld(linkedBinaryTree<std::pair<int,T>>::root,right);
    linkedBinaryTree<std::pair<int,T>>::treeSize--;
}

template<typename T>
void maxHblt<T>::initialize(T* theElements, int theSize) {
    arrayQueue<binaryTreeNode<std::pair<int,T>>*> q(theSize);
    linkedBinaryTree<std::pair<int,T>>::erase();
    
    for (int i = 1; i <= theSize; ++i)
        q.push(new binaryTreeNode<std::pair<int,T>>(std::pair<int,T>(1, theElements[i])));
    
    for (int i = 1; i < theSize - 1; i++) {
        binaryTreeNode<std::pair<int,T>>* b = q.front();
        q.pop();
        binaryTreeNode<std::pair<int,T>>* c = q.front();
        q.pop();
        meld(b,c);
        q.push(b);
    }
    
    if (theSize > 0)
        linkedBinaryTree<std::pair<int,T>>::root = q.front();
    linkedBinaryTree<std::pair<int,T>>::treeSize = theSize;
}

template<typename T>
void heapSort(T a[], int n) {
    maxHeap<T> heap(1);
    heap.initialize(a,n);
    
    for (int i = n - 1; i >= 1; --i) {
        T x = heap.top();
        heap.pop();
        a[i+1] = x;
    }
    
    heap.deactivateArray();
}

#endif /* maxHblt_hpp */
