#include "Units/BaseUnit.h"

BaseUnit* BaseUnit::createUnit(const std::string filePath, Vec2 pos, UnitState state, UnitWeapon weapon)
{
	BaseUnit* baseUnit = new (std::nothrow) BaseUnit();

	if(baseUnit && baseUnit->initWithFile(filePath))
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

void BaseUnit::setUnitState(UnitState newState)
{
	m_unitState = newState;
}

void BaseUnit::setUnitWeapon(UnitWeapon newWeapon)
{
	m_unitWeapon = newWeapon;
}
