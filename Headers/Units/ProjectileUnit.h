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
	
	static ProjectileUnit* createUnit(const std::string spriteFrameName, Vec2 pos, int Type);

	float					getMaxSpeed() const;
	void					setCurrentPosition(Vec2 position);
	void					setCurrentVelocity(Vec2 velocity);
	
	
private:

	Vec2			mCurrentPosition;
	Vec2			mCurrentVelocity;

};
