#include "Managers/LevelManager.h"

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

bool LevelManager::readLevel(const std::string filePath)
{
	std::string content;

	if(FileUtils::getInstance()->isFileExist(filePath))
	{
		content = FileUtils::getInstance()->getStringFromFile(filePath);

		if(content.size() > 0)
		{
			m_levelJson.Parse<0>(content.c_str());
			if(m_levelJson.HasParseError())
			{
				return false;
			}

			//Test
			const rapidjson::Value& wavesValue = m_levelJson["waves"];
			int wavesMembers = wavesValue.MemberCount();

			for(int x = 0; x < wavesMembers; x++)
			{
				std::string waveName = "wave_" + std::to_string(x+1);
				const rapidjson::Value& singleWave = wavesValue[waveName.c_str()];
				int singleWaveMembers = singleWave.MemberCount();

				for(int y = 0; y < singleWaveMembers; y++)
				{
					std::string enemyName = "enemy_" + std::to_string(y + 1);
					const rapidjson::Value& singleEnemy = singleWave[enemyName.c_str()];

					std::string enemy_type = singleEnemy["type"].GetString();
					std::string enemy_behavior = singleEnemy["behavior"].GetString();

					const rapidjson::Value& tmp_initialPosition = singleEnemy["initialPosition"];
					Vec2 enemy_initialPosition = Vec2(tmp_initialPosition[0].GetInt(), tmp_initialPosition[1].GetInt());
				}
			}
			//Test

			return true;
		}
	}

	return false;
}
