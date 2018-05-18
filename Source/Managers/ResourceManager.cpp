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

Vector<SpriteFrame*> ResourceManager::LoadSpriteAnimation(string format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	char str[100];
	for (int i = 0; i < count; i++)
	{
		sprintf(str, format.c_str(), i);
		frames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return frames;
}