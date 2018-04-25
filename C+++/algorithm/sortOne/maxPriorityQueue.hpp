//
//  maxPriorityQueue.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/22.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef maxPriorityQueue_hpp
#define maxPriorityQueue_hpp

//一棵大根树是这样一棵树，其中每个节点的值都大于或等于其子节点(如果有子节点的话)的值

template<typename T>
class maxPriorityQueue {
public:
    virtual ~maxPriorityQueue() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

#endif /* maxPriorityQueue_hpp */
