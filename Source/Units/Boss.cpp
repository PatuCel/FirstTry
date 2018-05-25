#include "Units/BaseUnit.h"
#include "Units/Boss.h"

Boss* Boss::createBoss(Vector<SpriteFrame*> frameArray, float delay)
{
	return (Boss*) createUnit(frameArray, delay);
}
