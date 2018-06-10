#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "ProjectileUnit.h"

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
	
	static BaseUnit* createUnit(const std::string spriteFrameName, Vec2 pos, UnitState state, UnitWeapon weapon, const bool isAllied);
	static BaseUnit* createUnit(Vector<SpriteFrame*> frameArray, float delay, const bool isAllied);
	void setUnitState(UnitState newState);
	void setUnitWeapon(UnitWeapon newWeapon);

	//Iribe
	void ShooterFunc(const int Type, const bool isAllied);
	void SetShooter(const int Type, const int Multiplier, const bool isAllied);
	void				createBullets(const int Type, const bool isAllied);
	void				createProjectile(const int Type,float xDirection, float yDirection, float xOffset, float yOffset);
	bool				isAllied() const;



private:
	UnitState m_unitState;
	UnitWeapon m_unitWeapon;
	ProjectileUnit* projectileUnit;

	int	mSpreadLevel;
	float mShooterMultiplier;
	AirCraftType   mAirCraftType;
};
