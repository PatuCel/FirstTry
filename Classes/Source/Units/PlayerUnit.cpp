#include "Units/PlayerUnit.h"

bool PlayerUnit::m_moveToUp = false;
bool PlayerUnit::m_moveToLeft = false;
bool PlayerUnit::m_moveToDown = false;
bool PlayerUnit::m_moveToRight = false;

PlayerUnit* PlayerUnit::createPlayer(const std::string filePath, Vec2 pos, UnitState state, UnitWeapon weapon)
{
	return (PlayerUnit*) createUnit(filePath, pos, state, weapon,true);
}

void PlayerUnit::startPlayerDirection(PlayerMoveDirection direction)
{
	switch(direction)
	{
		case PLAYER_MOVE_DIRECTION_UP:
			m_moveToUp = true;
			break;

		case PLAYER_MOVE_DIRECTION_LEFT:
			m_moveToLeft = true;
			break;

		case PLAYER_MOVE_DIRECTION_DOWN:
			m_moveToDown = true;
			break;

		case PLAYER_MOVE_DIRECTION_RIGHT:
			m_moveToRight = true;
			break;
	}
}

void PlayerUnit::stopPlayerDirection(PlayerMoveDirection direction)
{
	switch(direction)
	{
	case PLAYER_MOVE_DIRECTION_UP:
		m_moveToUp = false;
		break;

	case PLAYER_MOVE_DIRECTION_LEFT:
		m_moveToLeft = false;
		break;

	case PLAYER_MOVE_DIRECTION_DOWN:
		m_moveToDown = false;
		break;

	case PLAYER_MOVE_DIRECTION_RIGHT:
		m_moveToRight = false;
		break;
	}
}