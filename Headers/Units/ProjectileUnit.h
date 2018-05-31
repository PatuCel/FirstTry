#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ProjectileUnit : public Sprite
{
public:

	enum Type
	{
		AlliedBullet,
		EnemyBullet,
		Homing_Missile,
		Super_Missile,//Iribe added super missile
		Curved,
		TypeCount
	};
	
	static ProjectileUnit* createUnit(int Type, Vec2 position, Vec2 offset,Vec2 AircraftPos);

	float					getMaxSpeed() const;
	void					setSpread(float spread);
	void					setDamage(float damage);
	void					setSpeed(Vec2 speed);
	
	
private:

	float			mDamage;
	int				mSpread;
	Vec2			mSpeed;

};
