//ConfigManager.cpp
#include "../../Headers/Managers/ConfigManager.h"

static std::vector<ConfigManager::AircraftData> dataAircraft(BaseUnit::TypeCount);

static std::vector<ConfigManager::ProjectileData> dataProjectile(ProjectileUnit::TypeCount);


using namespace ConfigManager;

rapidjson::Document m_levelJson;



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

			////Aircrafts

			std::vector<ConfigManager::AircraftData> dataAircraftTest(BaseUnit::TypeCount);
			dataAircraft = dataAircraftTest;
			
			const rapidjson::Value& aircraftsValue = m_levelJson["aircrafts"];
			int aircraftsMembers = aircraftsValue.MemberCount();

			for (int x = 0; x < aircraftsMembers; x++)
			{
				std::string aircraftName = "aircraft_" + std::to_string(x);
				const rapidjson::Value& singleAircraftValue = aircraftsValue[aircraftName.c_str()];
			
				dataAircraft[x].name= singleAircraftValue["name"].GetString();
				dataAircraft[x].hitPoints = singleAircraftValue["hitpoints"].GetInt();
				dataAircraft[x].projectileType = singleAircraftValue["projectile_type"].GetInt();
				dataAircraft[x].texturePath = singleAircraftValue["texturePath"].GetString();
		
			}

			
			std::vector<ConfigManager::ProjectileData> dataProjectileTest(ProjectileUnit::TypeCount);
			dataProjectile = dataProjectileTest;
			//////Projectiles
			const rapidjson::Value& projectilesValue = m_levelJson["projectiles"];
			int projectilesMembers = projectilesValue.MemberCount();

			for (int x = 0; x < projectilesMembers; x++)
			{
				std::string projectileName = "projectile_" + std::to_string(x);
				const rapidjson::Value& singleProjectileValue = projectilesValue[projectileName.c_str()];
				//std::string projec

				dataProjectile[x].name = singleProjectileValue["name"].GetString();
				dataProjectile[x].damage = singleProjectileValue["damage"].GetFloat();
				dataProjectile[x].speed = singleProjectileValue["velocity"].GetFloat();
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

