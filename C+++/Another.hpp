//
//  Another.hpp
//  C+++
//
//  Created By chenyanan on 2017/01/13
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef Another_hpp
#define Another_hpp

#include "TYPE.h"
#include "RCT.h"

struct Another : public RCT {
	mutable STR _name;
	mutable INT _Age;
	mutable STR _birth;
	mutable PTR _Sex;
	mutable Vblk _didClick;

	~Another();
	Another(STR name = "",INT Age = 0,STR birth = "",PTR Sex = nullptr,Vblk didClick = NULL);
};

template<typename T> class SPR;
typedef SPR<Another> SAnother;
typedef std::vector<SPR<Another>> VSAnother;


#endif /* Another_hpp */
