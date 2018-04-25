//
//  vertexIterator.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/23.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef vertexIterator_hpp
#define vertexIterator_hpp

template<typename T>
class vertexIterator {
public:
    virtual ~vertexIterator(){}
    virtual int next() = 0;
    virtual int next(T&) = 0;
};

#endif /* vertexIterator_hpp */
