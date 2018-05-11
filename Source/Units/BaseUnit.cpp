#include "BaseUnit.h"

USING_NS_CC;

bool BaseUnit::init(std::string spritePath, int posX, int posY)
{
	m_unitPosX = posX;
	m_unitPosY = posY;

	m_unitSprite = Sprite::create(spritePath);

	if(m_unitSprite != nullptr)
	{
		m_unitSprite->setPosition(m_unitPosX, m_unitPosY);

		return true;
	}

	return false;
}

cocos2d::Sprite* BaseUnit::getSprite()
{
	return m_unitSprite;
}
