#include "Units/ProjectileUnit.h"
#include "Managers/ConfigManager.h"

ProjectileUnit* ProjectileUnit::createUnit(int Type,Vec2 position, Vec2 offset, Vec2 AircraftPos)
{
	ProjectileUnit* projectileUnit = new (std::nothrow) ProjectileUnit();

	std::string spriteFrameName = ConfigManager::GetProjectileDataTable()[Type].texturePath;

	if(projectileUnit && projectileUnit->initWithSpriteFrameName(spriteFrameName))
	{
		projectileUnit->autorelease();
		
		projectileUnit->setDamage(ConfigManager::GetProjectileDataTable()[Type].damage);
		
		projectileUnit->setSpeed(Vec2(ConfigManager::GetProjectileDataTable()[Type].speed, ConfigManager::GetProjectileDataTable()[Type].speed));
		projectileUnit->setSpread(ConfigManager::GetProjectileDataTable()[Type].spreadlevel);
		projectileUnit->setPosition(position);

		float bulletSpeed = 1/ConfigManager::GetProjectileDataTable()[Type].speed;

		offset.normalize();
		auto shootAmount = offset * 1000;

		auto realDest = shootAmount + AircraftPos;

		auto actionMove = MoveTo::create(1.5f, realDest);
		auto actionRemove = RemoveSelf::create();
		projectileUnit->runAction(Sequence::create(actionMove, actionRemove, nullptr));

		return projectileUnit;
	}
	
	CC_SAFE_DELETE(projectileUnit);
	return nullptr;
}





float ProjectileUnit::getMaxSpeed() const
{
	return 10.f;
}


void ProjectileUnit::setSpeed(Vec2 speed)
{
	mSpeed = speed;
}

void ProjectileUnit::setDamage(float damage)
{
	mDamage = damage;
}

void ProjectileUnit::setSpread(float spread)
{
	mSpread = spread;
}