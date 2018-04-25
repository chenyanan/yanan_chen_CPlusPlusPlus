//
//  Anotherrr.hpp
//  C+++
//
//  Created By chenyanan on 2017/01/13
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef Anotherrr_hpp
#define Anotherrr_hpp

#include "TYPE.h"
#include "RCT.h"

class Anotherrr : public RCT {
public:
	mutable STR _name;
	mutable INT _Age;
	mutable STR _birth;
	mutable PTR _Sex;
	mutable Vblk _didClick;

	mutable Sblk _nameWlStBlk;
	mutable Iblk _AgeWlStBlk;
	mutable Sblk _birthWlStBlk;
	mutable Pblk _SexWlStBlk;
	mutable Vblk _didClickWlStBlk;

	mutable Sblk _nameDiStBlk;
	mutable Iblk _AgeDiStBlk;
	mutable Sblk _birthDiStBlk;
	mutable Pblk _SexDiStBlk;
	mutable Vblk _didClickDiStBlk;

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

	~Anotherrr();
	Anotherrr(STR name = "",INT Age = 0,STR birth = "",PTR Sex = nullptr,Vblk didClick = NULL);
};

template<typename T> class SPR;
typedef SPR<Anotherrr> SAnotherrr;
typedef std::vector<SPR<Anotherrr>> VSAnotherrr;


#endif /* Anotherrr_hpp */