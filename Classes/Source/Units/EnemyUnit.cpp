#include "Units/EnemyUnit.h"
#include "Managers/ConfigManager.h"

EnemyUnit* EnemyUnit::createEnemy(int UnitType, Vec2 pos, UnitState state, UnitWeapon weapon)
{
	std::string filePath = ConfigManager::GetAircraftDataTable()[UnitType].texturePath;
	return (EnemyUnit*) createUnit(UnitType,filePath, pos, state, weapon,false);
}
