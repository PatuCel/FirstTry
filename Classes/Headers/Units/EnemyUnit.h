#pragma once
#include "Units/BaseUnit.h"

#include "cocos2d.h"
USING_NS_CC;

class EnemyUnit: public BaseUnit
{
public:
	static EnemyUnit* createEnemy(int UnitType, Vec2 pos, UnitState state, UnitWeapon weapon);

};
