//
//  WILLDID.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef WILLDID_hpp
#define WILLDID_hpp

#include <stdio.h>
#include "TYPE.h"

class WILLDID {
public:
    static void make(STR path, STR author, STR clsName, VSTR headers, VSTR instance, VSTR instanceType, STR refCntCls);
};

#endif /* WILLDID_hpp */
