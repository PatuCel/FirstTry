//ConfigManager.cpp
#include "../../Headers/Managers/ConfigManager.h"

static std::vector<ConfigManager::AircraftData> dataAircraft(BaseUnit::TypeCount);

static std::vector<ConfigManager::ProjectileData> dataProjectile(ProjectileUnit::TypeCount);


using namespace ConfigManager;

rapidjson::Document m_levelJson;


std::vector<ConfigManager::ProjectileData> ConfigManager::initializeProjectileData()
{
	ConfigManager::Load_Shooter_Config("Config.json");
	std::vector<ConfigManager::ProjectileData> data = ConfigManager::GetProjectileDataTable();
	return data;
}


bool ConfigManager::Load_Shooter_Config(const std::string filePath)
{

	std::string content;

	if (FileUtils::getInstance()->isFileExist(filePath))
	{
		content = FileUtils::getInstance()->getStringFromFile(filePath);

		if (content.size() > 0)
		{
			m_levelJson.Parse<0>(content.c_str());
			if (m_levelJson.HasParseError())
			{
				return false;
			}

			//Player

			const rapidjson::Value& playerValue = m_levelJson["player"];
			int playerHitpoints = playerValue["hitpoints"].GetFloat();
			const rapidjson::Value& playerSpeedPos = playerValue["speed"];
			Vec2 playerSpeed = Vec2(playerSpeedPos[0].GetInt(), playerSpeedPos[1].GetInt());
			int playerFireInterval= playerValue["hitpoints"].GetFloat();
			int playerSpreadLevel = playerValue["spreadlevel"].GetFloat();
			int playerWeaponType = playerValue["weapontype"].GetFloat();
			//bool playerIsAlly=


			std::vector<ConfigManager::ProjectileData> dataProjectileTest(ProjectileUnit::TypeCount);
			dataProjectile = dataProjectileTest;
			//////Projectiles
			const rapidjson::Value& projectilesValue = m_levelJson["projectiles"];
			int projectilesMembers = projectilesValue.MemberCount();

			for (int x = 0; x < projectilesMembers; x++)
			{
				std::string projectileName = "projectile_" + std::to_string(x + 1);
				const rapidjson::Value& singleProjectileValue = projectilesValue[projectileName.c_str()];
				//std::string projec

				dataProjectile[x].damage = singleProjectileValue["damage"].GetFloat();
				dataProjectile[x].speed = singleProjectileValue["velocity"].GetFloat();
				//dataProjectile[x].isAllied = singleProjectileValue["damage"].GetFloat();
				dataProjectile[x].spreadlevel = singleProjectileValue["spreadlevel"].GetInt();
				dataProjectile[x].fireRate = singleProjectileValue["fireRate"].GetFloat();
				dataProjectile[x].texturePath = singleProjectileValue["texturePath"].GetString();
				
			}
			

			return true;
		}
	}


}


std::vector<AircraftData> ConfigManager::GetAircraftDataTable()
{
	return dataAircraft;
}

std::vector<ProjectileData> ConfigManager::GetProjectileDataTable()
{
	return dataProjectile;
}

