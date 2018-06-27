//ConfigManager.h
#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "../../Headers/Units/BaseUnit.h"
#include "../../Headers/Units/ProjectileUnit.h"
//#include "../Include/Pickup.hpp"

#include "json/document-wrapper.h"
#include "cocos2d.h"

namespace ConfigManager
{
	static struct Direction
	{
		Direction(float angle, float distance)
			: angle(angle)
			, distance(distance)
		{
		}

		float angle;
		float distance;
	};


	static struct AircraftData
	{
		std::string                     name;
		int								hitPoints;
		int								projectileType;
		std::string						texturePath;
	};

	static struct ProjectileData
	{
		std::string						name;
		int								damage;
		float							speed;
		int								spreadlevel;
		float							fireRate;
		std::string						texturePath;
		//sf::IntRect						textureRect;
	};

	bool Load_Shooter_Config(const std::string filePath);

	std::vector<AircraftData> GetAircraftDataTable();
	std::vector<ProjectileData> GetProjectileDataTable();

};
#endif//CONFIGMANAGER_H