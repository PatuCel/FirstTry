#ifndef  _PLAYER_UNIT_H_
#define  _PLAYER_UNIT_H_

#include "Units/BaseUnit.h"

class PlayerUnit: public BaseUnit
{
public:
	static PlayerUnit* createPlayer(const std::string filePath, int state, cocos2d::Vec2 pos);

};

#endif // _PLAYER_UNIT_H_
