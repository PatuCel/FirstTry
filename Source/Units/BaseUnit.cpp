#include "Units/BaseUnit.h"
#include "Units/ProjectileUnit.h"
#include "Managers/ConfigManager.h"
#include "Managers/MCBCallLambda.h"


/*
namespace
{
	const std::vector<ConfigManager::AircraftData> DataTable = initializeAircraftData();
}
*/

BaseUnit* BaseUnit::createUnit(const std::string spriteFrameName, Vec2 pos, UnitState state, UnitWeapon weapon, const bool isAllied)
{
	BaseUnit* baseUnit = new (std::nothrow) BaseUnit();

	if(baseUnit && baseUnit->initWithSpriteFrameName(spriteFrameName))
	{
		baseUnit->autorelease();

		baseUnit->setPosition(pos);
		baseUnit->setUnitState(state);
		baseUnit->setUnitWeapon(weapon);
		baseUnit->mShooterMultiplier = 1.0f;
		if (isAllied)//Iribe
			baseUnit->SetShooter(1, baseUnit->mShooterMultiplier, isAllied);
		else
			baseUnit->SetShooter(2, baseUnit->mShooterMultiplier, isAllied);

		return baseUnit;
	}
	
	CC_SAFE_DELETE(baseUnit);
	return nullptr;
}

BaseUnit* BaseUnit::createUnit(Vector<SpriteFrame*> frameArray, float delay, const bool isAllied)
{
	BaseUnit* baseUnit = new (std::nothrow) BaseUnit();

	baseUnit->initWithSpriteFrame(frameArray.front());
	baseUnit->setPosition(0, 0);
	baseUnit->mShooterMultiplier = 1.0f;
	baseUnit->SetShooter(1, baseUnit->mShooterMultiplier, isAllied);//Iribe

	auto animation = Animation::createWithSpriteFrames(frameArray, delay);
	baseUnit->runAction(RepeatForever::create(Animate::create(animation)));

	return baseUnit;
}

void BaseUnit::setUnitState(UnitState newState)
{
	m_unitState = newState;
}

void BaseUnit::setUnitWeapon(UnitWeapon newWeapon)
{
	m_unitWeapon = newWeapon;
}

bool BaseUnit::isAllied() const
{
	return mAirCraftType == Player;
}

///Iribe 

void BaseUnit::ShooterFunc(const int Type, const bool isAllied) {
	BaseUnit::createBullets(Type, isAllied);
}

void BaseUnit::SetShooter(const int Type, const int Multiplier, const bool isAllied) {

	float projectileFrecuency = ConfigManager::GetProjectileDataTable()[Type].fireRate * Multiplier;
	
	auto callLater(MCBPlatformSupport::MCBCallLambda::createWithDelay(projectileFrecuency,[=]() {
		ShooterFunc(Type, isAllied);
	}));

	runAction(CCSequence::createWithTwoActions(CCDelayTime::create(projectileFrecuency), callLater));
}

void BaseUnit::createBullets(const int Type, const bool isAllied)
{
	int mSpreadLevel = ConfigManager::GetProjectileDataTable()[Type].spreadlevel;
	bool isAlliedBullet = isAllied;
	float dirFactor = 0.0f;
	if (isAlliedBullet)
		dirFactor = 1.0f;
	else
		dirFactor = -1.0f;

	switch (mSpreadLevel)
	{
	case 1:
		createProjectile(0.0f, 1.f * dirFactor, 0.0f, 0.5f * dirFactor);
		break;

	case 2:
		createProjectile(0.f, 1.f * dirFactor, -0.33f, 0.33f * dirFactor);
		createProjectile(0.0f, 1.f * dirFactor, 0.0f, 0.5f * dirFactor);
		createProjectile(0.f, 1.f * dirFactor, +0.33f, 0.33f * dirFactor);

		break;

	case 3:
		createProjectile(0.f, 1.f * dirFactor, -0.1f, 0.33f * dirFactor);
		createProjectile(0.0f, 1.f * dirFactor, 0.0f, 0.5f * dirFactor);
		createProjectile(0.f, 1.f * dirFactor, +0.1f, 0.33f * dirFactor);

		break;
	}
}


void BaseUnit::createProjectile(float xDirection, float yDirection, float xOffset, float yOffset)
{
	Vec2 offset = Vec2(xOffset, yOffset);
	cocos2d::Vec2 Direction(xDirection, yDirection);

	Vec2 projectilePos = this->getPosition() + offset + Direction;
	projectileUnit= ProjectileUnit::createUnit(2, projectilePos, offset, this->getPosition());
	Director *pDirector = Director::getInstance();
	Scene* curScene = pDirector->getRunningScene();
	curScene->addChild(projectileUnit, 1);
}

