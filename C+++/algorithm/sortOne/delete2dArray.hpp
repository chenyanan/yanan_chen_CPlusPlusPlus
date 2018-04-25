//
//  delete2dArray.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/24.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef delete2dArray_hpp
#define delete2dArray_hpp

template<typename T>
void delete2dArray(T** &theArray, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; ++i)
        delete[] theArray[i];
    
    delete[] theArray;
    theArray = 0;
}

#endif /* delete2dArray_hpp */
