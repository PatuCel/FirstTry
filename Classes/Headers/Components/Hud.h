#pragma once
#include "cocos2d.h"
#include "ui/UIButton.h"

class Hud : public cocos2d::Layer
{
private:
	cocos2d::Label* scoreLabel;
	cocos2d::ProgressTimer* hp;
	cocos2d::Node* pauseMenu;
	std::function<void(int id)> buttonPressedListener;
public:
	static Hud* createHud();
	Hud();
	bool init();

private:
	cocos2d::ui::Button* createButton(std::string normal, std::string pressed, std::string icon, cocos2d::Color3B iconColor = cocos2d::Color3B::WHITE);

public:
	void setScore(std::string score);
	void setHP(float percent);
	void addButtonPressedListener(std::function<void(int id)> buttonPressedListener);
};