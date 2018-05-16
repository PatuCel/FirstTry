#pragma once

#include "json/document-wrapper.h"

#include "cocos2d.h"
USING_NS_CC;

class LevelManager
{
public:
	static LevelManager* getInstance();

	bool readLevel(const std::string filePath);

private:
	static LevelManager* m_levelManager;
	rapidjson::Document m_levelJson;

	LevelManager();
};