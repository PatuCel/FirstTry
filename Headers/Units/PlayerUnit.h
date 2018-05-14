#pragma once
#include "Units/BaseUnit.h"

#include "cocos2d.h"
USING_NS_CC;

class PlayerUnit: public BaseUnit
{
public:
	static PlayerUnit* createPlayer(const std::string filePath, Vec2 pos, UnitState state, UnitWeapon weapon);

};
