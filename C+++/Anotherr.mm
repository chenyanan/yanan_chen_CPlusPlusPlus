//
//  Anotherr.cpp
//  C+++
//
//  Created By chenyanan on 2017/01/13
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#include "Anotherr.hpp"
#pragma mark - getter
const STR& Anotherr::getName() {
	return _name;
}

const INT& Anotherr::getAge() {
	return _Age;
}

const STR& Anotherr::getBirth() {
	return _birth;
}

const PTR& Anotherr::getSex() {
	return _Sex;
}

const Vblk& Anotherr::getDidClick() {
	return _didClick;
}


#pragma mark - setter
void Anotherr::setName(STR name) {
	_name = name;
}

void Anotherr::setAge(INT Age) {
	_Age = Age;
}

void Anotherr::setBirth(STR birth) {
	_birth = birth;
}

void Anotherr::setSex(PTR Sex) {
	_Sex = Sex;
}

void Anotherr::setDidClick(Vblk didClick) {
	_didClick = didClick;
}


#pragma mark - parameter init
Anotherr::Anotherr(STR name,
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
_didClick(didClick) 
{

}


#pragma mark - deinit
Anotherr::~Anotherr() {
	printf("Anotherr dealloc\n");
}

