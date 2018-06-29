#include "Units/ProjectileUnit.h"
#include "Managers/ConfigManager.h"
#include "Globals.h"

ProjectileUnit* ProjectileUnit::createUnit(int Type,Vec2 position, Vec2 offset, Vec2 AircraftPos)
{
	ProjectileUnit* projectileUnit = new (std::nothrow) ProjectileUnit();

	std::string spriteFrameName = ConfigManager::GetProjectileDataTable()[Type].texturePath;

	if(projectileUnit && projectileUnit->initWithSpriteFrameName(spriteFrameName))
	{
		projectileUnit->autorelease();
		
		projectileUnit->setDamage(ConfigManager::GetProjectileDataTable()[Type].damage);
		
		//projectileUnit->setSpeed(Vec2(ConfigManager::GetProjectileDataTable()[Type].speed, ConfigManager::GetProjectileDataTable()[Type].speed));
		projectileUnit->setSpread(ConfigManager::GetProjectileDataTable()[Type].spreadlevel);
		projectileUnit->setPosition(position);

		float projectileSpeed =0.0f;
		float projectileSpeedFactor = ConfigManager::GetProjectileDataTable()[Type].speed;
		if (projectileSpeedFactor <= 0) {
			projectileSpeed = 0.0f;
		}
		else {
			projectileSpeed = (1.0f / projectileSpeedFactor);
		}
		float bulletSpeed = PROJECTILE_SPEED_FACTOR * (projectileSpeed);
		

		projectileUnit->setSpeed(Vec2(projectileSpeed, projectileSpeed));

		offset.normalize();
		auto shootAmount = offset * 1000;

		auto realDest = shootAmount + AircraftPos;


		
		///Projectile Pattern//TO DO: to add different type of projectiles, Homing Missiles, Curve Lasers. 

		switch (Type)
		{
		case 0:
		{
			auto actionMove = MoveTo::create(bulletSpeed, realDest);
			auto actionRemoveZero = RemoveSelf::create();
			projectileUnit->runAction(Sequence::create(actionMove, actionRemoveZero, nullptr));
		}
			break;
		case 1:
		{
			/*
			ccBezierConfig configName;
			configName.controlPoint_1 = Point(AircraftPos.x - 100, AircraftPos.y + 100);
			configName.controlPoint_2 = Point(AircraftPos.x + 200, AircraftPos.y + 100);
			configName.endPosition = realDest;

			auto actionMoveBezier = BezierTo::create(bulletSpeed, configName);

			auto actionRemoveOne = RemoveSelf::create();
			projectileUnit->runAction(Sequence::create(actionMoveBezier, actionRemoveOne, nullptr));
			*/

			auto actionMove = MoveTo::create(bulletSpeed, realDest);
			auto actionRemoveZero = RemoveSelf::create();
			projectileUnit->runAction(Sequence::create(actionMove, actionRemoveZero, nullptr));
		}
			break;
		default:
		{
			MoveTo * actionMove = MoveTo::create(bulletSpeed, realDest);
			auto actionRemoveZero = RemoveSelf::create();
			projectileUnit->runAction(Sequence::create(actionMove, actionRemoveZero, nullptr));
		}
			break;
		}

		return projectileUnit;
	}
	
	CC_SAFE_DELETE(projectileUnit);
	return nullptr;
}

void ProjectileUnit::setSpeed(Vec2 speed)
{
	mSpeed = speed;
}

void ProjectileUnit::setDamage(float damage)
{
	mDamage = damage;
}

void ProjectileUnit::setSpread(int spread)
{
	mSpread = spread;
}


Vec2 ProjectileUnit::getSpeed()
{
	return mSpeed;
}

float ProjectileUnit::getDamage()
{
	return mDamage;
}

int ProjectileUnit::getSpread()
{
	return mSpread;
}

float ProjectileUnit::toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float ProjectileUnit::toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}