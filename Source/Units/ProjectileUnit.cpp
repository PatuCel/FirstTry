#include "Units/ProjectileUnit.h"
#include "Managers/ConfigManager.h"

namespace
{
	const std::vector<ConfigManager::ProjectileData> DataTable = initializeProjectileData();
}

/*
std::vector<ConfigManager::ProjectileData> initializeProjectileData()
{
	ConfigManager::Load_Shooter_Config("Config.json");
	std::vector<ConfigManager::ProjectileData> data = ConfigManager::GetProjectileDataTable();

	return data;
}
*/

ProjectileUnit* ProjectileUnit::createUnit(int Type)
{
	ProjectileUnit* projectileUnit = new (std::nothrow) ProjectileUnit();

	std::string spriteFrameName = DataTable[Type].texturePath;

	if(projectileUnit && projectileUnit->initWithSpriteFrameName(spriteFrameName))
	{
		projectileUnit->autorelease();
		
		projectileUnit->setDamage(DataTable[Type].damage);
		
		projectileUnit->setSpeed(Vec2(DataTable[Type].speed, DataTable[Type].speed));
		projectileUnit->setSpread(DataTable[Type].spreadlevel);

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