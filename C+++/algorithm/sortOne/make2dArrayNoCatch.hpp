//
//  make2dArrayNoCatch.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/24.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef make2dArrayNoCatch_hpp
#define make2dArrayNoCatch_hpp

template<typename T>
void make2dArray(T** &x, int numberOfRows, int numberOfColumns)
{
    x = new T* [numberOfRows];
    
    for (int i = 0; i < numberOfRows; ++i)
        x[i] = new T[numberOfColumns];
}

#endif /* make2dArrayNoCatch_hpp */
