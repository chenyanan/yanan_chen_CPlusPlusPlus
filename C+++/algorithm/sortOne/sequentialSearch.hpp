//
//  sequentialSearch.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/16.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef sequentialSearch_hpp
#define sequentialSearch_hpp

#include <stdio.h>

template<typename T>
int sequentialSearch(T a[], int n, const T& x) {
    int i;
    for (i = 0; i < n && a[i] != x; ++i);
    if (i == n) return -1;
    else return i;
}

template<typename T>
int rSeaquentialSearch(T a[], int n, const T& x) {
    if (n < 1) return -1;
    if (a[n - 1] == x) return n - 1;
    return rSeaquentialSearch(a, n - 1, x);
}

template<typename T>
int sequentialSearch(T a[], int n, const T& x) {
    a[n] = x;
    int i;
    for (i = 0; a[i] != x; ++i);
    if (i == n) return -1;
    return i;
}

#endif /* sequentialSearch_hpp */
