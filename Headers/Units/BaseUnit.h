#ifndef  _BASE_UNIT_H_
#define  _BASE_UNIT_H_

#include "cocos2d.h"

class BaseUnit : cocos2d::Sprite
{
public:
	static BaseUnit* create(const std::string filePath);
};

#endif // _BASE_UNIT_H_
