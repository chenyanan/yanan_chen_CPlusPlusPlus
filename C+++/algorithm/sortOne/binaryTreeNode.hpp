//
//  binaryTreeNode.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/21.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef binaryTreeNode_hpp
#define binaryTreeNode_hpp

template<typename T>
struct binaryTreeNode {
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;
    
    binaryTreeNode() {leftChild = rightChild = NULL;}
    binaryTreeNode(const T& theElement) : element(theElement) {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T& theElement,
                   binaryTreeNode *theLeftChild,
                   binaryTreeNode *theRightChild) : element(theElement) {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

#endif /* binaryTreeNode_hpp */
