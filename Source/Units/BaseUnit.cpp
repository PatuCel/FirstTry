#include "Units/BaseUnit.h"

USING_NS_CC;

BaseUnit* BaseUnit::createUnit(const std::string filePath, int state, cocos2d::Vec2 pos)
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
