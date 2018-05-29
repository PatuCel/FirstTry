#pragma once
#include "Units/PlayerUnit.h"
#include "Units/EnemyUnit.h"

#include "cocos2d.h"
USING_NS_CC;

class PlayerUnit;
class Boss;
class Hud;

class GameplayScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);

	void movePlayer(Vec2 pos);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayScene);
	
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	bool loadCollectibles();
	bool loadEnemies();

	void update(float) override;
	
	//Iribe
	void				createBullets(bool isAllied);
	void				createProjectile(float xDirection, float yDirection, float xOffset, float yOffset);

	void myFunc();

private:
	std::vector<EnemyUnit*> enemies;
	TMXTiledMap* testMap;
	PlayerUnit* player;
	Boss* boss;
	Hud* hud;
};
