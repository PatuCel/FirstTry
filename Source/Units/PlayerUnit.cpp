#include "Units/PlayerUnit.h"

PlayerUnit* PlayerUnit::createPlayer(const std::string filePath, Vec2 pos, UnitState state, UnitWeapon weapon)
{
	return (PlayerUnit*) createUnit(filePath, pos, state, weapon);
}
