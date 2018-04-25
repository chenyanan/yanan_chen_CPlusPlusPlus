//
//  edge.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/23.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef edge_hpp
#define edge_hpp

template<typename T>
class edge {
public:
    virtual ~edge() {}
    virtual int vertex1() const = 0;
    virtual int vertex2() const = 0;
    virtual T weight() const = 0;
};

class unweightedEdge : public edge<bool> {
    unweightedEdge(int theV1, int theV2) {v1 = theV1, v2 = theV2;}
    int vertex1() const {return v1;}
    int vertex2() const {return v2;}
    bool weight() const {throw undefinedMethod("weight");}
private:
    int v1, v2;
};

template<typename T>
class weightedEdge : public edge<T> {
    weightedEdge() {}
    weightedEdge(int theV1, int theV2, T theW) {v1 = theV1; v2 = theV2; w = theW;}
    ~weightedEdge() {}
    int vertex1() const {return v1;}
    int vertex2() const {return v2;}
    T weight() const {return w;}
    operator T() const {return w;}
private:
    int v1, v2;
    T w;
};

#endif /* edge_hpp */
