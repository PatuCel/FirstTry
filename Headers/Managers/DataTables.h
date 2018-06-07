//DataTables.hpp
#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "cocos2d.h"
#include "../Headers/Managers/ConfigManager.h"

/*
struct PickupData
{
	std::function<void(Aircraft&)>	action;
	Textures::ID					texture;
	sf::IntRect						textureRect;
};
*/

/*
struct ParticleData
{
	sf::Color						color;
	sf::Time						lifetime;
};
*/

std::vector<ConfigManager::AircraftData>	initializeAircraftData();
std::vector<ConfigManager::ProjectileData>	initializeProjectileData();


//d::vector<PickupData>		initializePickupData();
//std::vector<ParticleData>	initializeParticleData();

#endif //DATATABLES_HPP
