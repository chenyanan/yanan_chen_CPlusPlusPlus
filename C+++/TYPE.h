//
//  TYPE.hpp
//  C++Project
//
//  Created by chenyanan on 2017/1/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef TYPE_hpp
#define TYPE_hpp

#include <string>
#include <vector>

//should check details of NSInteger to update
#if __LP64__ || (TARGET_OS_EMBEDDED && !TARGET_OS_IPHONE) || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64
typedef long INT;
#else
typedef int  INT;
#endif

typedef void* PTR;
typedef std::string STR;

typedef void(^Vblk)(void);
typedef void(^Sblk)(STR str);
typedef void(^Pblk)(PTR ptr);
typedef void(^Iblk)(INT integer);

typedef std::vector<std::string> VSTR;

#endif /* TYPE_hpp */
