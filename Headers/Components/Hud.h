#pragma once
#include "cocos2d.h"
#include "ui/UILoadingBar.h"
#include "ui/UIButton.h"
#include "ui/UIRichText.h"

class Hud : public cocos2d::Layer
{
private:
	cocos2d::ui::RichText* score;
	cocos2d::ui::LoadingBar* hp;
public:
	static Hud* createHud();
	bool init();
	void setScore(std::string score);
	void setHP(float percent);
};