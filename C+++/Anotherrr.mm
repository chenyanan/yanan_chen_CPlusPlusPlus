//
//  Anotherrr.cpp
//  C+++
//
//  Created By chenyanan on 2017/01/13
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#include "Anotherrr.hpp"
#pragma mark - getter
const STR& Anotherrr::getName() {
	return _name;
}

const INT& Anotherrr::getAge() {
	return _Age;
}

const STR& Anotherrr::getBirth() {
	return _birth;
}

const PTR& Anotherrr::getSex() {
	return _Sex;
}

const Vblk& Anotherrr::getDidClick() {
	return _didClick;
}


#pragma mark - setter
void Anotherrr::setName(STR name) {
	if (_nameWlStBlk) {
		_nameWlStBlk(name);
	}

	_name = name;

	if (_nameDiStBlk) {
		_nameDiStBlk(name);
	}
}

void Anotherrr::setAge(INT Age) {
	if (_AgeWlStBlk) {
		_AgeWlStBlk(Age);
	}

	_Age = Age;

	if (_AgeDiStBlk) {
		_AgeDiStBlk(Age);
	}
}

void Anotherrr::setBirth(STR birth) {
	if (_birthWlStBlk) {
		_birthWlStBlk(birth);
	}

	_birth = birth;

	if (_birthDiStBlk) {
		_birthDiStBlk(birth);
	}
}

void Anotherrr::setSex(PTR Sex) {
	if (_SexWlStBlk) {
		_SexWlStBlk(Sex);
	}

	_Sex = Sex;

	if (_SexDiStBlk) {
		_SexDiStBlk(Sex);
	}
}

void Anotherrr::setDidClick(Vblk didClick) {
	if (_didClickWlStBlk) {
		_didClickWlStBlk();
	}

	_didClick = didClick;

	if (_didClickDiStBlk) {
		_didClickDiStBlk();
	}
}


#pragma mark - parameter init
Anotherrr::Anotherrr(STR name,
                     INT Age,
                     STR birth,
                     PTR Sex,
                     Vblk didClick)
:
RCT(1),
_name(name),
_Age(Age),
_birth(birth),
_Sex(Sex),
_didClick(didClick),
_nameWlStBlk(NULL),
_AgeWlStBlk(NULL),
_birthWlStBlk(NULL),
_SexWlStBlk(NULL),
_didClickWlStBlk(NULL),
_nameDiStBlk(NULL),
_AgeDiStBlk(NULL),
_birthDiStBlk(NULL),
_SexDiStBlk(NULL),
_didClickDiStBlk(NULL) 
{

}


#pragma mark - deinit
Anotherrr::~Anotherrr() {
	printf("Anotherrr dealloc\n");
}

