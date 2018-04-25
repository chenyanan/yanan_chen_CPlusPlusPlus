//
//  polyEval.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/16.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef polyEval_hpp
#define polyEval_hpp

#include <stdio.h>

template<typename T>
T polyEval(T coeff[], int n, const T& x) {
    T y = 1, value = coeff[0];
    for (int i = 1; i <= n; ++i) {
        y *= x;
        value += y * coeff[i];
    }
    return value;
}

template<typename T>
T horner(T coeff[], int n, const T& x) {
    T value = coeff[n];
    for (int i = 1; i <= n; ++i)
        value = value * x + coeff[n - 1];
    return value;
}

#endif /* polyEval_hpp */
