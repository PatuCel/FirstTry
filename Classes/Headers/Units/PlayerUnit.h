#pragma once
#include "Units/BaseUnit.h"

#include "cocos2d.h"
USING_NS_CC;

enum PlayerMoveDirection {
	PLAYER_MOVE_DIRECTION_UP = 0,
	PLAYER_MOVE_DIRECTION_LEFT,
	PLAYER_MOVE_DIRECTION_DOWN,
	PLAYER_MOVE_DIRECTION_RIGHT
};

class PlayerUnit: public BaseUnit
{
public:
	static PlayerUnit* createPlayer(int UnitType, Vec2 pos, UnitState state, UnitWeapon weapon);
	static void startPlayerDirection(PlayerMoveDirection direction);
	static void stopPlayerDirection(PlayerMoveDirection direction);

	static bool isMovingUp() { return m_moveToUp; }
	static bool isMovingLeft() { return m_moveToLeft; }
	static bool isMovingDown() { return m_moveToDown; }
	static bool isMovingRight() { return m_moveToRight; }

private:
	static bool m_moveToUp;
	static bool m_moveToLeft;
	static bool m_moveToDown;
	static bool m_moveToRight;
};
