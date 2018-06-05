#include "Components/Hud.h"
#include "managers/ResourceManager.h"
#include "managers/SceneManager.h"

using namespace cocos2d;
using namespace utils;
using namespace std;
using namespace ui;

Hud* Hud::createHud()
{
	Hud* hud = new Hud();
	return (hud->init()) ? hud : nullptr;
}

Hud::Hud() : buttonSkillListener(nullptr)
{
}

bool Hud::init()
{
	if (Layer::init())
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		ResourceManager::getInstance()->LoadSpriteSheet("hud.plist");


		//ProgressTimer (Progressbar)
		Sprite* barBorder = ResourceManager::getInstance()->LoadSprite("img_borderbar.png");
		barBorder->setAnchorPoint(Vec2(0, 1.0f));
		barBorder->setPosition(Vec2(5, visibleSize.height - 2));

		Sprite* barBg = ResourceManager::getInstance()->LoadSprite("img_bar.png");
		hp = ProgressTimer::create(barBg);
		hp->setType(ProgressTimerType::BAR);
		hp->setAnchorPoint(Vec2(0.0, 0.0));
		hp->setPosition(Vec2(0.0, 0.0));
		hp->setBarChangeRate(Vec2(1, 0));
		hp->setMidpoint(Vec2(0.0, 0.0));
		hp->setPercentage(100);
		barBorder->addChild(hp);

		//Puase button
		auto pauseBtn = createButton("img_circle.png", "img_circle_bg.png", "img_pause.png", Color3B::YELLOW);
		pauseBtn->setScale(0.7f);
		pauseBtn->setColor(Color3B::GRAY);
		pauseBtn->setPosition(Vec2(visibleSize.width - pauseBtn->getContentSize().width / 2, visibleSize.height - pauseBtn->getContentSize().height / 2));
		pauseBtn->addClickEventListener([=](Ref* ref)
		{
			bool isVisible = !pauseLabel->isVisible();
			pauseLabel->setVisible(isVisible);
			if (buttonPauseListener)
				buttonPauseListener(isVisible);
		});

		//Score label
		scoreLabel = Label::createWithBMFont("fonts/mikado_outline_shadow.fnt", "0", CCTextAlignment::RIGHT);
		scoreLabel->setAnchorPoint(Vec2(1.0f, 1.0f));
		scoreLabel->setPosition(visibleSize.width - (pauseBtn->getContentSize().width + 10), visibleSize.height - 10);
		scoreLabel->setBMFontSize(22);

		//Pause Label
		pauseLabel = Label::createWithBMFont("fonts/mikado_outline_shadow.fnt", "Paused", CCTextAlignment::RIGHT);
		pauseLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		pauseLabel->setBMFontSize(32);
		pauseLabel->setVisible(false);

		//Skill Buttons
		auto skill01 = createButton("img_circle.png", "img_circle_bg.png", "img_skill01.png");
		skill01->setColor(Color3B(27, 201, 48));
		skill01->setPosition(Vec2(5 + skill01->getContentSize().width / 2, skill01->getContentSize().height * 4));
		skill01->addClickEventListener([=](Ref* ref) { if (buttonSkillListener) buttonSkillListener(1); });

		auto skill02 = createButton("img_circle.png", "img_circle_bg.png", "img_skill02.png");
		skill02->setColor(Color3B(255, 202, 33));
		skill02->setPosition(Vec2(5 + skill02->getContentSize().width / 2, skill01->getContentSize().height * 3));
		skill02->addClickEventListener([=](Ref* ref) { if (buttonSkillListener) buttonSkillListener(2); });

		auto skill03 = createButton("img_circle.png", "img_circle_bg.png", "img_skill03.png");
		skill03->setColor(Color3B(0, 235, 255));
		skill03->setPosition(Vec2(5 + skill03->getContentSize().width / 2, skill01->getContentSize().height * 2));
		skill03->addClickEventListener([=](Ref* ref) { if (buttonSkillListener) buttonSkillListener(3); });

		addChild(barBorder);
		addChild(scoreLabel);
		addChild(pauseLabel);
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
	auto button = Button::create(normal, pressed, "", Widget::TextureResType::PLIST); //Load from hud.plist
	auto btnIcon = ResourceManager::getInstance()->LoadSprite(icon);
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
	hp->runAction(ProgressTo::create(1.0f, percent)); //hp->runAction(ProgressFromTo::create(2.0f, 30.0f, 75.0f)); // filling from 30% to 75% in 2 seconds
}

void Hud::addButtonSkillListener(function<void(int id)> buttonSkillListener)
{
	this->buttonSkillListener = buttonSkillListener;
}

void Hud::addButtonPauseListener(std::function<void(bool isPaused)> buttonPauseListener)
{
	this->buttonPauseListener = buttonPauseListener;
}
