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
	std::function<void(int id)> buttonPressedListener;
public:
	static Hud* createHud();
	Hud();
	bool init();
	void setScore(std::string score);
	void setHP(float percent);
	void addButtonPressedListener(std::function<void(int id)> buttonPressedListener);
};