#ifndef  _BASE_UNIT_H_
#define  _BASE_UNIT_H_

#include "cocos2d.h"

class BaseUnit
{
public:
	int m_unitPosX;
	int m_unitPosY;
	cocos2d::Sprite* m_unitSprite;

	bool init(std::string spritePath, int posX, int posY);
	cocos2d::Sprite* getSprite();
};

#endif // _BASE_UNIT_H_
