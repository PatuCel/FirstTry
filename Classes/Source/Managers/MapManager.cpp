#include "Managers/MapManager.h"
#include "Managers/CameraManager.h"
#include "Globals.h"

MapManager* MapManager::m_mapManager = nullptr;

MapManager::MapManager()
{

}

MapManager* MapManager::getInstance()
{
	if(m_mapManager == nullptr)
	{
		m_mapManager = new MapManager();
	}
	return m_mapManager;
}

bool MapManager::loadMap(const std::string filePath)
{
	if(FileUtils::getInstance()->isFileExist(filePath))
	{
		m_map = TMXTiledMap::create(filePath);

		m_layerBackground = m_map->getLayer("background");
		m_layerCollisions = m_map->getLayer("collisions");
		m_layerCollectibles = m_map->getLayer("collectibles");
		m_layerEnemies = m_map->getLayer("enemies");

		//Loop Map
		m_loopStartPosition = (m_map->getMapSize().height *  m_map->getTileSize().height) - SCREEN_RESOLUTION_H/2;
		m_mapCounts = 0;
		m_loopCounts = 0;
		m_loopMap = true;
		m_countMap = false;;
		//Loop Map

		return true;
	}

	return false;
}

void MapManager::checkForLoop()
{
	if((int(CameraManager::getInstance()->getCameraPosition().y) == m_loopStartPosition) || (m_mapCounts == SCREEN_RESOLUTION_H))
	{
		CCLOG("Looping Map!!!");

		Vec2 mapLayerPos = getLayer(MAP_LAYER_BACKGROUND)->getPosition();
		getLayer(MAP_LAYER_BACKGROUND)->setPosition(mapLayerPos.x, mapLayerPos.y + (SCREEN_RESOLUTION_H));

		mapLayerPos = getLayer(MAP_LAYER_COLLISIONS)->getPosition();
		getLayer(MAP_LAYER_COLLISIONS)->setPosition(mapLayerPos.x, mapLayerPos.y + (SCREEN_RESOLUTION_H));

		m_countMap = true;

		if(m_mapCounts == SCREEN_RESOLUTION_H)
		{
			m_mapCounts = 0;
		}

		m_loopCounts++;
	}

	if(m_countMap)
	{
		m_mapCounts++;
	}
}

TMXTiledMap* MapManager::getMap()
{
	return m_map;
}

TMXLayer* MapManager::getLayer(MapLayer mapLayer)
{
	switch(mapLayer)
	{
		case MAP_LAYER_BACKGROUND:
			return m_layerBackground;

		case MAP_LAYER_COLLISIONS:
			return m_layerCollisions;

		case MAP_LAYER_COLLECTIBLES:
			return m_layerCollectibles;

		case MAP_LAYER_ENEMIES:
			return m_layerEnemies;

		default:
			return nullptr;
	}
}

Vec2 MapManager::tileFromPosition(Vec2 position)
{
	int x = position.x / m_map->getTileSize().width;
	int y = (((m_map->getMapSize().height * m_map->getTileSize().height) + (m_loopCounts * SCREEN_RESOLUTION_H)) - position.y) / m_map->getTileSize().height;

	return Vec2(x, y);
}

Vec2 MapManager::positionFromTile(Vec2 tile)
{
	int x = (tile.x * m_map->getTileSize().width) + m_map->getTileSize().width/2;
	int y = (m_map->getMapSize().height * m_map->getTileSize().height) - (tile.y * m_map->getTileSize().height) - m_map->getTileSize().height / 2;

	return Vec2(x, y);
}

std::vector<Vec2> MapManager::getTilesFromLayer(MapLayer mapLayer)
{
	std::vector<Vec2> layerTiles;

	for(int x=0; x<getLayer(mapLayer)->getLayerSize().width; x++)
	{
		for(int y=0; y<getLayer(mapLayer)->getLayerSize().height; y++)
		{
			if(getLayer(mapLayer)->getTileGIDAt(Vec2(x, y)))
			{
				layerTiles.push_back(Vec2(x,y));
			}			
		}
	}

	return layerTiles;
}