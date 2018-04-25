//
//  pairNode.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/20.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef pairNode_hpp
#define pairNode_hpp

#include <utility>

template<typename K, typename E>
struct pairNode {
    typedef std::pair<const K, E> pairType;
    pairType element;
    pairNode<K,E>* next;
    
    pairNode(const pairType& thePair) : element(thePair) {}
    pairNode(const pairType& thePair, pairNode<K,E>* theNext) : element(thePair) {next = theNext;}
};

#endif /* pairNode_hpp */
