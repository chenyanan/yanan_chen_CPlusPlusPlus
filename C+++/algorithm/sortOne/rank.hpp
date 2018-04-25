//
//  rank.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/16.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef rank_hpp
#define rank_hpp

#include <stdio.h>
#include <algorithm>

template<typename T>
void rank(T a[], int n, int r[]) {
    for (int i = 0; i < n; ++i)
        r[i] = 0;
    
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] <= a[i]) r[i]++;
            else r[j]++;
}

template<typename T>
void rearrange(T a[], int n, int r[]) {
    T *u = new T[n];
    
    for (int i = 0; i < n; ++i)
        u[r[i]] = a[i];
    
    for (int i = 0; i < n; ++i)
        a[i] = u[i];
    
    delete [] u;
}

template<typename T>
void rearRange(T a[], int n, int r[]) {
    using std::swap;
    int t;
    for (int i = 0; i < n; ++i)
        while (r[i] != i) {
            t = r[i];
            swap(a[i], a[t]);
            swap(r[i], r[t]);
        }
}

#endif /* rank_hpp */
