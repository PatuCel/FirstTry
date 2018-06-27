#pragma once

class Boss : public BaseUnit
{
private:
	float _maxHealth;
	float _health;
public:
	static Boss* createBoss(int UnitType,Vector<SpriteFrame*> frameArray, float delay = 0.125f);

	void setHealth(float health);
	void reduceHealth(float damage);
};

