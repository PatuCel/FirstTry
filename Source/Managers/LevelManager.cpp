#include "Managers\LevelManager.h"

LevelManager* LevelManager::m_levelManager = nullptr;

LevelManager::LevelManager()
{

}

LevelManager* LevelManager::getInstance()
{
	if(m_levelManager == nullptr)
	{
		m_levelManager = new LevelManager();
	}
	return m_levelManager;
}

bool LevelManager::loadLevel(const std::string filePath)
{
	std::string content;

	if(FileUtils::getInstance()->isFileExist(filePath))
	{
		content = FileUtils::getInstance()->getStringFromFile(filePath);

		if(content.size() > 0)
		{
			m_levelJson.Parse<0>(content.c_str());

			if(!m_levelJson.HasParseError())
			{
				return true;
			}
		}
	}

	return false;
}
