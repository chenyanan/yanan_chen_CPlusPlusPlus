//
//  graphChain.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/24.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef graphChain_hpp
#define graphChain_hpp

#include "chain.hpp"

template<typename T>
class graphChain : public chain<T>
{
public:
    T* eraseElement(int theVertex)
    {
        chainNode<T>* current = chain<T>::firstNode, *tail = NULL;
        
        while (current != NULL && current->element != theVertex)
        {
            tail = current;
            current = current->next;
        }
        
        if (current == NULL)
            return NULL;
        
        T* theElement = &current->element;
        
        if (tail != NULL)
            tail->next = current->next;
        else
            chain<T>::firstNode = current->next;
        
        delete current;
        chain<T>::listSize--;
        return theElement;
    }
};

#endif /* graphChain_hpp */
