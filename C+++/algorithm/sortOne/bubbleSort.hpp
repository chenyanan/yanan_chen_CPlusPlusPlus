//
//  bubbleSort.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/16.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef bubbleSort_hpp
#define bubbleSort_hpp

#include <stdio.h>

template<typename T>
void bubble(T a[], int n) {
    for (int i = 0; i < n - 1; ++i)
        if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
}

template<typename T>
void bubbleSort(T a[], int n) {
    for (int i = n; i > 1; --i)
        bubble(a, i);
}

template<typename T>
bool Bubble(T a[], int n) {
    bool swapped = false;
    for (int i = 0; i < n - 1; ++i)
        if (a[i] > a[i + 1]) {
            swap(a[i], a[i + 1]);
            swapped = true;
        }
    return swapped;
}

template<typename T>
void BubbleSort(T a[], int n) {
    for (int i =n ; i > 1 && Bubble(a, i); --i);
}



////////////////////
template<typename T>
bool maxBubble(T a[], int n) {
    using std::swap;
    bool sorted = false;
    for (int index = 0; index < n - 1; ++index) {
        if (a[index] > a[index + 1]) {
            swap(a[index], a[index + 1]);
            sorted = true;
        }
    }
    return sorted;
}

template<typename T>
void MaxBubble(T a[], int n) {
    for (int size = n; size > 1 && maxBubble(a, size); --size);
}

template<typename T>
bool minBubble(T a[], int n) {
    using std::swap;
    bool sorted = false;
    for (int index = 0; index < n - 1; ++index) {
        if (a[index] < a[index + 1]) {
            swap(a[index], a[index + 1]);
            sorted = true;
        }
    }
    return sorted;
}

template<typename T>
void MinBubble(T a[], int n) {
    for (int size = n; size > 1 && minBubble(a, size); --size);
}

#endif /* bubbleSort_hpp */
