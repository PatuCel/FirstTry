#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ProjectileUnit : public Sprite
{
public:

	enum Type
	{
		Normal,
		Special,
		TypeCount
	};
	
	static ProjectileUnit* createUnit(int Type, Vec2 position, Vec2 offset,Vec2 AircraftPos);

	
	void					setSpread(int spread);
	void					setDamage(float damage);
	void					setSpeed(Vec2 speed);
	float					toDegree(float radian);
	float					toRadian(float degree);


	int						getSpread();
	float					getDamage();
	Vec2					getSpeed();

private:

	float			mDamage;
	int				mSpread;
	Vec2			mSpeed;
	float			mTravelledDistance;

};
