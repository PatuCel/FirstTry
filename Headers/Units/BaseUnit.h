#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BaseUnit : public Sprite
{
public:

	enum UnitState {
		UNIT_STATE_NORMAL = 0,
		UNIT_STATE_SPAWNING,
		UNIT_STATE_DYING,		
		UNIT_STATE_UNKNOW
	};

	enum UnitWeapon {
		UNIT_WEAPON_NONE = 0,
		UNIT_WEAPON_DEFAULT,
		UNIT_WEAPON_SUPER
	};

	UnitState m_unitState;
	UnitWeapon m_unitWeapon;

	static BaseUnit* createUnit(const std::string spriteFrameName, Vec2 pos, UnitState state, UnitWeapon weapon);
	void setUnitState(UnitState newState);
	void setUnitWeapon(UnitWeapon newWeapon);
};
