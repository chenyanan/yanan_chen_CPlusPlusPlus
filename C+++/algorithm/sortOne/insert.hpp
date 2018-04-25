//
//  insert.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/16.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef insert_hpp
#define insert_hpp

#include <stdio.h>

template<typename T>
void insert(T a[], int& n, const T& x) {
    int i;
    for (i = n - 1; i >= 0 && x < a[i]; --i)
        a[i + 1] = a[i];
    a[i + 1] = x;
    n++;
}

template<typename T>
void insertsort(T a[], int n) {
    for (int i = 1; i < n; ++i) {
        T t = a[i];
        insert(a, i, t);
    }
}

template<typename T>
void insertSort(T a[], int n) {
    for (int i = 1; i < n; i++) {
        T t = a[i];
        int j;
        for (j = i - 1; j >= 0 && t < a[j]; --j)
            a[j + 1] = a[j];
        a[j + 1] = t;
    }
}

#endif /* insert_hpp */
