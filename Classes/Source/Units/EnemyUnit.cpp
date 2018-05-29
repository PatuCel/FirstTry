#include "Units/EnemyUnit.h"

EnemyUnit* EnemyUnit::createEnemy(const std::string filePath, Vec2 pos, UnitState state, UnitWeapon weapon)
{
	return (EnemyUnit*) createUnit(filePath, pos, state, weapon);
}
