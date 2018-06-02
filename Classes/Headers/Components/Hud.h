#pragma once
#include "cocos2d.h"
#include "ui/UILoadingBar.h"
#include "ui/UIButton.h"

class Hud : public cocos2d::Layer
{
private:
	cocos2d::Label* scoreLabel;
	cocos2d::ui::LoadingBar* hp;
	cocos2d::Node* pauseMenu;
	std::function<void(int id)> buttonPressedListener;
public:
	static Hud* createHud();
	Hud();
	bool init();
	void ShowMenu();
	void HideMenu();
	void setScore(std::string score);
	void setHP(float percent);
	void addButtonPressedListener(std::function<void(int id)> buttonPressedListener);
};