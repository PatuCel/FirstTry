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
	void checkForLoop();

	TMXTiledMap* getMap();
	TMXLayer* getLayer(MapLayer mapLayer);
	Vec2 tileFromPosition(Vec2 position);
	Vec2 positionFromTile(Vec2 tile);
	std::vector<Vec2> getTilesFromLayer(MapLayer mapLayer);

private:
	static MapManager* m_mapManager;

	TMXTiledMap* m_map;
	TMXLayer* m_layerBackground;
	TMXLayer* m_layerCollisions;
	TMXLayer* m_layerCollectibles;
	TMXLayer* m_layerEnemies;

	float m_screenScale;

	bool m_loopMap;
	bool m_countMap;	
	int m_loopStartPosition;
	int m_mapCounts;
	int m_loopCounts;

	MapManager();
};