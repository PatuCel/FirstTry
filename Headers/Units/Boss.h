#pragma once

class Boss : public BaseUnit
{
public:
	static Boss* createBoss(Vector<SpriteFrame*> frameArray, float delay = 0.125f);
};

