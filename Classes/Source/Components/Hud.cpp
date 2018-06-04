#include "Components/Hud.h"
#include "managers/ResourceManager.h"
#include "managers/SceneManager.h"
#include "Globals.h"

using namespace cocos2d;
using namespace utils;
using namespace std;
using namespace ui;

Hud* Hud::createHud()
{
	Hud* hud = new Hud();
	return (hud->init()) ? hud : nullptr;
}

Hud::Hud() : buttonPressedListener(nullptr)
{
}

bool Hud::init()
{
	if (Layer::init())
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		//Score label
		scoreLabel = Label::createWithBMFont("fonts/mikado_outline_shadow.fnt", "999", CCTextAlignment::RIGHT);
		scoreLabel->setAnchorPoint(Vec2(1.0f, 1.0f));
		scoreLabel->setPosition(visibleSize.width - 50, visibleSize.height - 10);
		scoreLabel->setBMFontSize(22);

		//Puase button
		auto pauseBtn = createButton("img_circle.png", "img_circle_bg.png", "img_pause.png", Color3B::YELLOW);
		pauseBtn->setScale(0.7f);
		pauseBtn->setColor(Color3B::GRAY);
		pauseBtn->setPosition(Vec2(visibleSize.width - pauseBtn->getContentSize().width / 2, visibleSize.height - pauseBtn->getContentSize().height / 2));
		pauseBtn->addClickEventListener([=](Ref* ref) { if (buttonPressedListener) buttonPressedListener(0); });

		//Skill Buttons
		auto skill01 = createButton("img_circle.png", "img_circle_bg.png", "img_skill01.png");
		skill01->setColor(Color3B(27, 201, 48));
		skill01->setPosition(Vec2(skill01->getContentSize().width / 2, skill01->getContentSize().height * 4));
		skill01->addClickEventListener([=](Ref* ref) { if (buttonPressedListener) buttonPressedListener(1); });

		auto skill02 = createButton("img_circle.png", "img_circle_bg.png", "img_skill02.png");
		skill02->setColor(Color3B(255, 202, 33));
		skill02->setPosition(Vec2(skill02->getContentSize().width / 2, skill01->getContentSize().height * 3));
		skill02->addClickEventListener([=](Ref* ref) { if (buttonPressedListener) buttonPressedListener(2); });

		auto skill03 = createButton("img_circle.png", "img_circle_bg.png", "img_skill03.png");
		skill03->setColor(Color3B(0, 235, 255));
		skill03->setPosition(Vec2(skill03->getContentSize().width / 2, skill01->getContentSize().height * 2));
		skill03->addClickEventListener([=](Ref* ref) { if (buttonPressedListener) buttonPressedListener(3); });

		addChild(scoreLabel);
		addChild(pauseBtn);
		addChild(skill01);
		addChild(skill02);
		addChild(skill03);
		return true;
	}

	return false;
}

Button* Hud::createButton(std::string normal, std::string pressed, std::string icon, Color3B iconColor)
{
	auto button = Button::create(normal, pressed);
	auto btnIcon = Sprite::create(icon);
	btnIcon->setColor(iconColor);
	btnIcon->setPosition(Vec2(button->getContentSize().width / 2, button->getContentSize().height / 2));
	button->addChild(btnIcon);

	return button;
}


void Hud::setScore(string score)
{
	scoreLabel->setString(score);
}


void Hud::setHP(float percent)
{
	//hp->setPercent(percent); //TODO
}

void Hud::addButtonPressedListener(function<void(int id)> buttonPressedListener)
{
	this->buttonPressedListener = buttonPressedListener;
}
