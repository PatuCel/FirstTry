#include "Components/Hud.h"
#include "managers/ResourceManager.h"
#include "managers/SceneManager.h"
#include "Globals.h"

using namespace cocos2d;
using namespace std;
using namespace ui;

Hud* Hud::createHud()
{
	Hud* hud = new Hud();
	return (hud->init()) ? hud : nullptr;
}


bool Hud::init()
{
	if (Layer::init())
	{
		auto layer = SceneManager::getInstance()->createScene(CC_UI_HUD);
		hp = utils::findChild<LoadingBar*>(layer, "hp");
		score = utils::findChild<RichText*>(layer, "score");
		auto button = utils::findChild<Button*>(layer, "pause");
		button->addClickEventListener([=](Ref* ref) {});

		addChild(layer);
		return true;
	}

	return false;
}


void Hud::setScore(string score)
{
	this->score->setColor(Color3B::BLUE);
}


void Hud::setHP(float percent)
{
	hp->setPercent(percent);
	hp->setColor(Color3B::RED);
}
