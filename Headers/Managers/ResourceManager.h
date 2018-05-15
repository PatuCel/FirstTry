#pragma once

#include "cocos2d.h"
#include "2d/CCSpriteFrameCache.h"
#include "external/json/document.h"
#include <fstream>
#include <string>

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
	rapidjson::Document* LoadJson(string jsonFileName);

private:
	static ResourceManager* mResourceManager;
};