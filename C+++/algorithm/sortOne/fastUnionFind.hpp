//
//  fastUnionFind.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/23.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef fastUnionFind_hpp
#define fastUnionFind_hpp

struct unionFindNode {
    int parent;
    bool root;
    unionFindNode() {parent = 1; root = true;}
};

class fastUnionFind {
public:
    fastUnionFind(int numberOfElements) {
        node = new unionFindNode[numberOfElements + 1];
    }
    
    void unite(int rootA, int rootB) {
        if (node[rootA].parent < node[rootB].parent) {
            node[rootB].parent += node[rootA].parent;
            node[rootA].root = false;
            node[rootA].parent = rootB;
        
        } else {
            node[rootA].parent += node[rootB].parent;
            node[rootB].root = false;
            node[rootB].parent = rootA;
        }
    }
    
    int find(int theElement) {
        int theRoot = theElement;
        while (!node[theRoot].root)
            theRoot = node[theRoot].parent;
        
        int currentNode = theElement;
        while (currentNode != theRoot) {
            int parentNode = node[currentNode].parent;
            node[currentNode].parent = theRoot;
            currentNode = parentNode;
        }
        
        return theRoot;
    }
    
protected:
    unionFindNode *node;
};

#endif /* fastUnionFind_hpp */
