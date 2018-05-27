#pragma once
#include "cocos2d.h"

class Hud : public cocos2d::Layer
{
private:
	cocos2d::Label* scoreLabel;
public:
	static Hud* createHud();
	bool init();
	void setScore(std::string score);
	void setHP(float percent);
};