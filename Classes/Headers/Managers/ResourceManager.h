#pragma once

#include "cocos2d.h"
#include "2d/CCSpriteFrameCache.h"

using namespace cocos2d;
using namespace std;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* getInstance();
	void LoadSpriteSheet(string spriteSheetplist);
	Sprite* LoadSprite(string spriteName);
	Vector<SpriteFrame*> LoadSpriteAnimation(string format, int count);

private:
	static ResourceManager* mResourceManager;
};