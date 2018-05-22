#include "Components/Hud.h"
#include "managers/ResourceManager.h"
#include "ui/UILoadingBar.h"

using namespace cocos2d;
using namespace std;

Hud* Hud::createHud()
{
	Hud* hud = new Hud();
	return (hud->init()) ? hud : nullptr;
}

bool Hud::init()
{
	if (Layer::init())
	{
		auto winSize = Director::getInstance()->getWinSize();
		scoreLabel = Label::createWithSystemFont("000 466 764", "Arial", 16);
		scoreLabel->setTextColor(Color4B::YELLOW);
		scoreLabel->setPosition(winSize.width - scoreLabel->getContentSize().width / 2, winSize.height - scoreLabel->getContentSize().height / 2);

		auto bar = ui::LoadingBar::create("hp_loadingbar.png");
		bar->setPercent(100);
		bar->setColor(Color3B::YELLOW);
		bar->setPosition(Vec2(bar->getContentSize().width / 2, winSize.height - bar->getContentSize().height / 2));
		
		auto hp = Sprite::create("hud_bar_hp.png");
		hp->setPosition(Vec2(bar->getContentSize().width / 2, bar->getContentSize().height / 2));
		bar->addChild(hp);

		addChild(bar, 0, "hp");
		addChild(scoreLabel, 3);
		return true;
	}

	return false;
}

void Hud::setScore(string score)
{
	scoreLabel->setString(score);
}


void Hud::updateRP(string score)
{
	scoreLabel->setString(score);
}
