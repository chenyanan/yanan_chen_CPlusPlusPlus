//
//  GETSET.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef GETSET_hpp
#define GETSET_hpp

#include <stdio.h>
#include "TYPE.h"

class GETSET {
public:
    static void make(STR path, STR author, STR clsName, VSTR headers, VSTR instance, VSTR instanceType, STR refCntCls);
};

#endif /* GETSET_hpp */
