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
		ALLIED = 0,
		ENEMY,
	};

	enum AirCraftType
	{
		Player,
		Raptor,
		Avenger,
		Falcon,
		Crow,
		Condor,
		TypeCount
	};
	
	static BaseUnit* createUnit(const std::string spriteFrameName, Vec2 pos, UnitState state, UnitWeapon weapon);
	static BaseUnit* createUnit(Vector<SpriteFrame*> frameArray, float delay);
	void setUnitState(UnitState newState);
	void setUnitWeapon(UnitWeapon newWeapon);

	//Iribe
	
	bool				isAllied() const;



private:
	UnitState m_unitState;
	UnitWeapon m_unitWeapon;
	SpriteFrame* m_sprite;
	Scene* m_Escena;

	int	mSpreadLevel;
	AirCraftType   mAirCraftType;
};
