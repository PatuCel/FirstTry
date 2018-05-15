#include "../../Headers/Managers/ResourceManager.h"

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

rapidjson::Document* ResourceManager::LoadJson(string jsonFileName)
{
	rapidjson::Document* jsonDocument;

	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(jsonFileName);
	ifstream file(fullpath.c_str());
	string strTemp;
	string strJson = "";
	while (std::getline(file, strTemp))
	{
		strJson += strTemp;
		strJson.push_back('\n');
	}

	bool error = jsonDocument->Parse<0>(strJson.c_str()).HasParseError();

	return jsonDocument;
}