#include "Units/PlayerUnit.h"

PlayerUnit* PlayerUnit::createPlayer(const std::string filePath, int state, cocos2d::Vec2 pos)
{
	return (PlayerUnit*) createUnit(filePath, state, pos);
}
