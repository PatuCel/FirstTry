#include "Managers/ResourceManager.h"

ResourceManager* ResourceManager::mResourceManager = NULL;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::getInstance()
{
	if (mResourceManager == NULL)
	{
		mResourceManager = new ResourceManager();
	}
	return mResourceManager;
}

void ResourceManager::LoadSpriteSheet(string spriteSheetplist)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(spriteSheetplist);
}

Sprite* ResourceManager::LoadSprite(string spriteName)
{
	return Sprite::createWithSpriteFrameName(spriteName);
}