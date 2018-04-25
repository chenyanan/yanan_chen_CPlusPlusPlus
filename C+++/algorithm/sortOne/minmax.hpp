//
//  minmax.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/16.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef minmax_hpp
#define minmax_hpp

#include <stdio.h>

template<typename T>
bool minmax(T a[], int n, int& indexOfMin, int& indexOfMax) {
    if (n < 1) return false;
    indexOfMin = indexOfMax = 0;
    for (int i = 1; i < n; ++i) {
        if (a[indexOfMin] > a[i]) indexOfMin = i;
        if (a[indexOfMax] < a[i]) indexOfMax = i;
    }
}

template<typename T>
bool minmax(T a[], int n, int& indexOfMin, int& indexOfMax) {
    if (n < 1) return;
    indexOfMin = indexOfMax = 0;
    for (int i = 1; i < n; ++i) {
        if (a[indexOfMin] > a[i]) indexOfMin = i;
        else if (a[indexOfMax] < a[i]) indexOfMax = i;
    }
    return true;
}

#endif /* minmax_hpp */
