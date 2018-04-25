//
//  indexedBSTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/22.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef indexedBSTree_hpp
#define indexedBSTree_hpp

#include <utility>
#include "bsTree.hpp"

template<typename K, typename E>
class indexedBSTree : public bsTree<K,E> {
public:
    virtual std::pair<const K, E>* get(int) const = 0;
    virtual void Delete(int) = 0;
};

#endif /* indexedBSTree_hpp */
