//
//  hashTable.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/20.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef hashTable_hpp
#define hashTable_hpp

#include "hash.hpp"
#include "myException.hpp"

template<typename K, typename E>
class hashTable {
public:
    hashTable(int theDivisor = 11);
    ~hashTable(){delete[] table;}
    
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    std::pair<const K,E>* find(const K&) const;
    void insert(const std::pair<const K,E>&);
    
protected:
    int search(const K&) const;
    std::pair<const K,E>** table;
    hash<K> hash;
    int dSize;
    int divisor;
};

template<typename K, typename E>
hashTable<K,E>::hashTable(int theDivisor) {
    divisor = theDivisor;
    dSize = 0;
    
    table = new std::pair<const K,E>* [divisor];
    for (int i = 0; i < divisor; ++i)
        table[i] = NULL;
}

template<typename K, typename E>
int hashTable<K,E>::search(const K& theKey) const {
    int i = (int) hash(theKey) % divisor;
    int j = i;
    do {
        if (table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    } while(j != i);
    
    return j;
}

template<typename K, typename E>
std::pair<const K,E>* hashTable<K,E>::find(const K& theKey) const {
    int b = search(theKey);
    
    if (table[b] == NULL || table[b]->first != theKey)
        return NULL;
    
    return table[b];
}

template<typename K, typename E>
void hashTable<K,E>::insert(const std::pair<const K,E>& thePair) {
    int b = search(thePair.first);
    
    if (table[b] == NULL) {
        table[b] = new std::pair<const K,E>(thePair);
        dSize++;
    
    } else {
        if (table[b]->first == thePair.first) {
            table[b]->second = thePair.second;
        } else
            throw hashTableFull();
    }
}

#endif /* hashTable_hpp */
