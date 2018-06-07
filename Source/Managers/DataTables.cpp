//DataTables.cpp
#include "../Headers/Managers/DataTables.h"
#include "../Headers/Units/BaseUnit.h"
#include "../Headers/Units/ProjectileUnit.h"
//#include "../Include/Pickup.hpp"
//#include "../Include/Particle.hpp"
//#include "../Include/ConfigManager.hpp"

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<ConfigManager::AircraftData> initializeAircraftData()
{
	ConfigManager::Load_Shooter_Config("Config.json");

	//std::vector<AircraftData> data(Aircraft::TypeCount);
	std::vector<ConfigManager::AircraftData> data = ConfigManager::GetAircraftDataTable();

	return data;
}

std::vector<ConfigManager::ProjectileData> initializeProjectileData()
{
	ConfigManager::Load_Shooter_Config("Config.json");
	std::vector<ConfigManager::ProjectileData> data = ConfigManager::GetProjectileDataTable();
	return data;
}

/*
std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);
	
	data[Pickup::HealthRefill].texture = Textures::Entities;
	data[Pickup::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);
	data[Pickup::HealthRefill].action = [] (Aircraft& a) { a.repair(25); };
	
	data[Pickup::MissileRefill].texture = Textures::Entities;
	data[Pickup::MissileRefill].textureRect = sf::IntRect(40, 64, 40, 40);
	data[Pickup::MissileRefill].action = [](Aircraft& a) { a.collectMissiles(3); };
	
	data[Pickup::FireSpread].texture = Textures::Entities;
	data[Pickup::FireSpread].textureRect = sf::IntRect(80, 64, 40, 40);
	data[Pickup::FireSpread].action = [](Aircraft& a) { a.increaseSpread(); };
	
	
	data[Pickup::FireRate].texture = Textures::Entities;
	data[Pickup::FireRate].textureRect = sf::IntRect(120, 64, 40, 40);
	data[Pickup::FireRate].action = [](Aircraft& a) { a.increaseFireRate(); };

	return data;
}
*/

/*
std::vector<ParticleData> initializeParticleData()
{
	std::vector<ParticleData> data(Particle::ParticleCount);

	data[Particle::Propellant].color = sf::Color(255, 255, 50);
	data[Particle::Propellant].lifetime = sf::seconds(0.6f);

	data[Particle::Smoke].color = sf::Color(50, 50, 50);
	data[Particle::Smoke].lifetime = sf::seconds(4.f);

	return data;
}
*/
