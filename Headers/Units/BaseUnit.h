#ifndef  _BASE_UNIT_H_
#define  _BASE_UNIT_H_

#include "cocos2d.h"

class BaseUnit : public cocos2d::Sprite
{
public:
	static BaseUnit* createUnit(const std::string filePath, int state, cocos2d::Vec2 pos);
};

#endif // _BASE_UNIT_H_
