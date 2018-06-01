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
		auto layer = SceneManager::getInstance()->createScene(CC_UI_HUD);
		hp = findChild<LoadingBar*>(layer, "hp");
		scoreLabel = findChild<Label*>(layer, "score");

		//Pause Menu
		pauseMenu = findChild<Node*>(layer, "pause_menu");
		findChild<Button*>(layer, "pm_ok")->addClickEventListener([=](Ref* ref) { HideMenu(); });

		findChild<Button*>(layer, "pause")->addClickEventListener([=](Ref* ref) { pauseMenu->isVisible() ? HideMenu() : ShowMenu(); });
		findChild<Button*>(layer, "skill_01")->addClickEventListener([=](Ref* ref) { if (buttonPressedListener) buttonPressedListener(1); });
		findChild<Button*>(layer, "skill_02")->addClickEventListener([=](Ref* ref) { if (buttonPressedListener) buttonPressedListener(2); });
		findChild<Button*>(layer, "skill_03")->addClickEventListener([=](Ref* ref) { if (buttonPressedListener) buttonPressedListener(3); });

		addChild(layer);

		HideMenu();
		return true;
	}

	return false;
}

void Hud::ShowMenu() 
{
	pauseMenu->setVisible(true);
}

void Hud::HideMenu()
{
	pauseMenu->setVisible(false);
}


void Hud::setScore(string score)
{
	scoreLabel->setString(score);
}


void Hud::setHP(float percent)
{
	hp->setPercent(percent);
}

void Hud::addButtonPressedListener(function<void(int id)> buttonPressedListener)
{
	this->buttonPressedListener = buttonPressedListener;
}
