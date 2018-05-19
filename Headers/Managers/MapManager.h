#pragma once

#include "cocos2d.h"
USING_NS_CC;

enum MapLayer {
	MAP_LAYER_BACKGROUND = 0,
	MAP_LAYER_COLLISIONS,
	MAP_LAYER_COLLECTIBLES,
	MAP_LAYER_ENEMIES
};

class MapManager
{
public:
	static MapManager* getInstance();

	bool loadMap(const std::string filePath);

	TMXTiledMap* getMap();
	TMXLayer* getLayer(MapLayer mapLayer);
	Vec2 tileFromPosition(Vec2 position);

private:
	static MapManager* m_mapManager;

	TMXTiledMap* m_map;
	TMXLayer* m_layerBackground;
	TMXLayer* m_layerCollisions;
	TMXLayer* m_layerCollectibles;
	TMXLayer* m_layerEnemies;

	MapManager();
};