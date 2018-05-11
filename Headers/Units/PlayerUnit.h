#ifndef  _PLAYER_UNIT_H_
#define  _PLAYER_UNIT_H_

#include "Units/BaseUnit.h"

#include "cocos2d.h"
USING_NS_CC;

class PlayerUnit: public BaseUnit
{
public:
	static PlayerUnit* createPlayer(const std::string filePath, int state, Vec2 pos);

};

#endif // _PLAYER_UNIT_H_
