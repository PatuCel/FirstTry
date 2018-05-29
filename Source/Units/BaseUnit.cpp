#include "Units/BaseUnit.h"
#include "Units/ProjectileUnit.h"

BaseUnit* BaseUnit::createUnit(const std::string spriteFrameName, Vec2 pos, UnitState state, UnitWeapon weapon)
{
	BaseUnit* baseUnit = new (std::nothrow) BaseUnit();

	if(baseUnit && baseUnit->initWithSpriteFrameName(spriteFrameName))
	{
		baseUnit->autorelease();

		baseUnit->setPosition(pos);
		baseUnit->setUnitState(state);
		baseUnit->setUnitWeapon(weapon);

		return baseUnit;
	}
	
	CC_SAFE_DELETE(baseUnit);
	return nullptr;
}

BaseUnit* BaseUnit::createUnit(Vector<SpriteFrame*> frameArray, float delay)
{
	BaseUnit* baseUnit = new (std::nothrow) BaseUnit();

	baseUnit->initWithSpriteFrame(frameArray.front());
	baseUnit->setPosition(0, 0);

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


