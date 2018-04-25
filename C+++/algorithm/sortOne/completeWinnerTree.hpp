//
//  completeWinnerTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/2/24.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef completeWinnerTree_hpp
#define completeWinnerTree_hpp

#include <stdio.h>
#include "winnerTree.hpp"
#include "myException.hpp"

//tree[1:n-1] 表示比赛结果
//player[1:n] 表示参赛选手

//s 是tree树最下一层最左边的那个节点的序号
//lowExt 是最底层外部节点总数，数值是2 * (n - s)
//offset 是tree树全满时数组的偏移量，数值是2 * s - 1

//对于任何一个外部节点，他在tree上所对应的父节点的序号是
//if (i <= lowExt) {p = (i + offset) / 2;}
//else {p = (i - lowExt + n - 1) / 2;}
//其中n - 1是tree中比赛的总数，i - lowExt, 是去除了lowExt的剩下的部分
//续接在tree上面

//i从2开始，递增2

//如果n是奇数，lowExt + 1是一个计数，将和他比较的内部节点是tree[n - 1], 这个节点将放在n / 2中

//play时候每当发现是奇数的时候，就连带左边的偶数一起再计算一遍

//先处理最下层所对应的外部节点
//处理预留下来的

template<typename T>
class completeWinnerTree : public winnerTree<T> {
public:
    completeWinnerTree(T* thePlayer, int theNumberOfPlayers) {
        tree = NULL;
        initialize(thePlayer, theNumberOfPlayers);
    }
    ~completeWinnerTree() {delete [] tree;}

    void initialize(T* thePlayer,int theNumberOfPlayers) {
        int n = theNumberOfPlayers;
        if (n < 2)
            throw illegalParameterValue("must have at least 2 players");
        
        player = thePlayer;
        numberOfPlayers = n;
        delete [] tree;
        tree = new int[n];
        
        int i, s;
        for (s = 1; 2 * s <= n - 1; s += s);
        
        lowExt = 2 * (n - s);
        offset = 2 * s - 1;
        
        for (i = 2; i <= lowExt; i += 2)
            play((offset + i) / 2, i - 1, i);
        
        if (n % 2 == 1) {
            play(n / 2, tree[n - 1], lowExt + 1);
            i = lowExt + 3;
        }
        else i = lowExt + 2;
        
        for (; i <= n; i += 2)
            play((i - lowExt + n - 1) / 2, i - 1, i);
    }
    
    int winner() const {return tree[1];}
    int winner(int i) const {return (i < numberOfPlayers) ? tree[i] : 0;}
    void rePlay(int thePlayer) {
        int n = numberOfPlayers;
        if (thePlayer <= 0 || thePlayer > n)
            throw illegalParameterValue("Player index is illegal");
        
        int matchNode, leftChild, rightChild;
        
        if (thePlayer <= lowExt) {
            matchNode = (offset + thePlayer) / 2;
            leftChild = 2 * matchNode - offset;
            rightChild = leftChild + 1;
        
        } else {
            matchNode = (thePlayer - lowExt + n - 1) / 2;
            if (2 * matchNode == n - 1) {
                leftChild = tree[2 * matchNode];
                rightChild = thePlayer;
            
            } else {
                leftChild = 2 * matchNode - n + 1 + lowExt;
                rightChild = leftChild + 1;
            }
        }
        
        tree[matchNode] = (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;
        
        //考虑是不是临界点的情况，并且要是奇偶结合的情况
        if (matchNode == n - 1 && n % 2 == 1) {
            matchNode /= 2;
            tree[matchNode] = (player[tree[n - 1]] <= player[lowExt + 1]) ? tree[n - 1] : lowExt + 1;
        }
        
        matchNode /= 2;
        for (; matchNode >= 1; matchNode /= 2)
            tree[matchNode] = (player[tree[2 * matchNode]] <= player[tree[2 * matchNode + 1]]) ? tree[2 * matchNode] : tree[2 * matchNode + 1];
    }
    
protected:
    int lowExt;
    int offset;
    int* tree;
    int numberOfPlayers;
    T* player;
    void play(int p, int leftChild, int rightChild) {
        tree[p] = (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;
        
        //是奇数继续再计算一遍
        while (p % 2 == 1 && p > 1) {
            tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ? tree[p - 1] : tree[p];
            p /= 2;
        }
    }
};

#endif /* completeWinnerTree_hpp */
