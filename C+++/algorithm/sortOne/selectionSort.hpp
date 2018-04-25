//
//  selectionSort.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/16.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef selectionSort_hpp
#define selectionSort_hpp

#include <stdio.h>
#include "myException.hpp"

template<typename T>
int indexOfMax(T a[], int n) {
    if (n <= 0)
        throw illegalParameterValue("n must be > 0");
    
    int indexOfMax = 0;
    for (int i = 1; i < n; ++i)
        if (a[indexOfMax] < a[i])
            indexOfMax = i;
    return indexOfMax;
}

template<typename T>
void selectionsort(T a[], int n) {
    for (int size = n; size > 1; --size) {
        int j = indexOfMax(a, size);
        swap(a[j], a[size - 1]);
    }
}

template<typename T>
void selectionSort(T a[], int n) {
    bool sorted = false;
    for (int size = n; !sorted && (size > 1); --size) {
        int indexOfMax = 0;
        sorted = true;
        for (int i = 1; i < size; ++i)
            if (a[indexOfMax] <= a[i]) indexOfMax = i;
            else sorted = false;
        swap(a[indexOfMax], a[size - 1]);
    }
}

/////////////////

//template<typename T>
//void maxSelect(T a[], int n) {
//    using std::swap;
//    int indexOfMax = n - 1;
//    for (int size = n; size > 1; --size)
//        if (a[indexOfMax] < a[size - 2])
//            indexOfMax = size - 2;
//    swap(a[indexOfMax], a[n - 1]);
//}
//
//template<typename T>
//void MaxSelect(T a[], int n) {
//    for (int size = n; size > 1; --size)
//        maxSelect(a, size);
//}

//template<typename T>
//void minSelect(T a[], int n) {
//    using std::swap;
//    int indexOfMin = n - 1;
//    for (int size = n; size > 1; --size)
//        if (a[indexOfMin] > a[size - 2])
//            indexOfMin = size - 2;
//    swap(a[indexOfMin], a[n - 1]);
//}
//
//template<typename T>
//void MinSelect(T a[], int n) {
//    for (int size = n; size > 1; --size)
//        minSelect(a, size);
//}

template<typename T>
void MaxSelect(T a[], int n) {
    using std::swap;
    bool sorted = false;
    for (int size = n; !sorted && size > 1; --size) {
        sorted = true;
        int indexOfMax = 0;
        for (int index = 1; index < size; ++index) {
            if (a[indexOfMax] < a[index]) indexOfMax = index;
            else sorted = false;
        }
        swap(a[indexOfMax], a[size - 1]);
    }
}

template<typename T>
void MinSelect(T a[], int n) {
    using std::swap;
    bool sorted = false;
    for (int size = n; !sorted && size > 1; --size) {
        sorted = true;
        int indexOfMin = 0;
        for (int index = 1; index < size; ++index) {
            if (a[indexOfMin] > a[index]) indexOfMin = index;
            else sorted = false;
        }
        swap(a[indexOfMin], a[size - 1]);
    }
}



#endif /* selectionSort_hpp */
