//
//  SIMPLE.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef SIMPLE_hpp
#define SIMPLE_hpp

#include <stdio.h>
#include "TYPE.h"

class SIMPLE {
public:
    static void make(STR path, STR author, STR clsName, VSTR headers, VSTR instance, VSTR instanceType, STR refCntCls);
};

#endif /* SIMPLE_hpp */
