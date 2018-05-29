#include "Units/ProjectileUnit.h"

ProjectileUnit* ProjectileUnit::createUnit(const std::string spriteFrameName, Vec2 pos,int Type)
{
	ProjectileUnit* projectileUnit = new (std::nothrow) ProjectileUnit();

	if(projectileUnit && projectileUnit->initWithSpriteFrameName(spriteFrameName))
	{
		projectileUnit->autorelease();

		projectileUnit->setPosition(pos);

		return projectileUnit;
	}
	
	CC_SAFE_DELETE(projectileUnit);
	return nullptr;
}


float ProjectileUnit::getMaxSpeed() const
{
	return 10.f;
}

void ProjectileUnit::setCurrentPosition(Vec2 position)
{
	mCurrentPosition = position;
}

void ProjectileUnit::setCurrentVelocity(Vec2 velocity)
{
	mCurrentVelocity = velocity;
}