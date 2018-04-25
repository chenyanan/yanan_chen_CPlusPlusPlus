//
//  winnerTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/2/24.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef winnerTree_hpp
#define winnerTree_hpp

#include <stdio.h>

template<typename T>
class winnerTree {
public:
    virtual ~winnerTree() {};
    virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
    virtual int winner() const = 0;
    virtual void rePlay(int thePlayer) = 0;
};

#endif /* winnerTree_hpp */
