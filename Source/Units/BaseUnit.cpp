#include "Units/BaseUnit.h"

BaseUnit* BaseUnit::createUnit(const std::string filePath, int state, Vec2 pos)
{
	BaseUnit* baseUnit = new (std::nothrow) BaseUnit();

	if(baseUnit && baseUnit->initWithFile(filePath))
	{
		baseUnit->autorelease();
		baseUnit->setPosition(pos);
		return baseUnit;
	}

	CC_SAFE_DELETE(baseUnit);
	return nullptr;
}
