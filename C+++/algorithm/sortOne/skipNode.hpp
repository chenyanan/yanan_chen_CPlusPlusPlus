//
//  skipNode.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/20.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef skipNode_hpp
#define skipNode_hpp

#include <utility>

template<typename K, typename E>
struct skipNode {
    typedef std::pair<const K,E> pairType;
    pairType element;
    skipNode<K,E>** next;
    
    skipNode(const pairType& thePair, int size) : element(thePair) {next = new skipNode<K,E>*[size];}
};

#endif /* skipNode_hpp */
