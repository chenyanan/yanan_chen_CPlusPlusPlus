//
//  hashChain.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/20.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef hashChain_hpp
#define hashChain_hpp

#include "hash.hpp"
#include "dictionary.hpp"
#include "sortedChain.hpp"

template<typename K, typename E>
class hashChain : public dictionary<K,E> {
public:
    hashChain(int theDivisor = 11) {
        divisor = theDivisor;
        dSize = 0;
        table = new sortedChain<K,E> [divisor];
    }
    ~hashChain(){delete [] table;}
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K& theKey) const {
        return table[hash(theKey) % divisor].find(theKey);
    }
    void insert(const std::pair<const K,E>& thePair) {
        int homeBucket = (int)hash(thePair.first)%divisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        if (table[homeBucket].size() > homeSize)
            dSize++;
    }
    void erase(const K& theKey) {
        table[hash(theKey) % divisor].erase(theKey);
    }
protected:
    sortedChain<K,E>* table;
    hash<K> hash;
    int dSize;
    int divisor;
};

#endif /* hashChain_hpp */
