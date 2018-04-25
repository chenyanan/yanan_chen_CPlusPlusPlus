//
//  minPriorityQueue.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/23.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef minPriorityQueue_hpp
#define minPriorityQueue_hpp

//一颗小根树是这样一棵树，其中每个节点的值都小于或等于其子节点(如果有子节点的话)的值

template<typename T>
class minPriorityQueue {
public:
    virtual ~minPriorityQueue(){}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

#endif /* minPriorityQueue_hpp */
