//
//  Anotherr.hpp
//  C+++
//
//  Created By chenyanan on 2017/01/13
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef Anotherr_hpp
#define Anotherr_hpp

#include "TYPE.h"
#include "RCT.h"

class Anotherr : public RCT {
public:
	mutable STR _name;
	mutable INT _Age;
	mutable STR _birth;
	mutable PTR _Sex;
	mutable Vblk _didClick;

	const STR& getName();
	const INT& getAge();
	const STR& getBirth();
	const PTR& getSex();
	const Vblk& getDidClick();

	void setName(STR name);
	void setAge(INT Age);
	void setBirth(STR birth);
	void setSex(PTR Sex);
	void setDidClick(Vblk didClick);

	~Anotherr();
	Anotherr(STR name = "",INT Age = 0,STR birth = "",PTR Sex = nullptr,Vblk didClick = NULL);
};

template<typename T> class SPR;
typedef SPR<Anotherr> SAnotherr;
typedef std::vector<SPR<Anotherr>> VSAnotherr;


#endif /* Anotherr_hpp */