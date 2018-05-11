#ifndef  _BASE_UNIT_H_
#define  _BASE_UNIT_H_

#include "cocos2d.h"
USING_NS_CC;

class BaseUnit : public Sprite
{
public:
	static BaseUnit* createUnit(const std::string filePath, int state, Vec2 pos);
};

#endif // _BASE_UNIT_H_
