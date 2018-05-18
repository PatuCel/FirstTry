#include "Units/BaseUnit.h"
#include "Units/Boss.h"
#include "ui/UILoadingBar.h"

using namespace ui;

Boss* Boss::createBoss(Vector<SpriteFrame*> frameArray, float delay)
{
	return (Boss*)createUnit(frameArray, delay);
}

void Boss::setHealth(float health)
{
	_maxHealth = health;
	_health = health;

	auto bar = ui::LoadingBar::create("ui_loadingbar.png");
	bar->setPercent(100);
	bar->setColor(Color3B::GREEN);
	bar->setPosition(Vec2(getContentSize().width / 2, 0));
	addChild(bar, 0, "health");
}

void Boss::reduceHealth(float attack)
{
	if (_health > 0)
	{
		_health -= attack;
		
		if (getChildrenCount() > 0)
		{
			auto healthBar = (LoadingBar*)getChildByName("health");
			if (healthBar)
			{
				float percent = _health / _maxHealth * 100;
				healthBar->setPercent(percent);
				
				if(percent< 30)
					healthBar->setColor(Color3B::RED);
			}
		}

		if (_health <= 0)
			setUnitState(BaseUnit::UNIT_STATE_DYING);
	}
}

