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
		int								hitPoints;
		float							speed_x;
		float							speed_y;
		std::string						texturePath;
		//sf::IntRect						textureRect;
		float							fireInterval;
		std::vector<Direction>			directions;
		//bool							hasRollAnimation;
		int								spreadLevel;
	};

	static struct ProjectileData
	{
		int								isAllied;
		int								damage;
		float							speed;
		int								spreadlevel;
		std::string						texturePath;
		//sf::IntRect						textureRect;
	};

	bool Load_Shooter_Config(const std::string filePath);

	std::vector<AircraftData> GetAircraftDataTable();
	std::vector<ProjectileData> GetProjectileDataTable();

	

};
#endif//CONFIGMANAGER_H