#include "Managers/MapManager.h"

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

		return true;
	}

	return false;
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
	int y = ((m_map->getMapSize().height * m_map->getTileSize().height) - position.y) / m_map->getTileSize().height;

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