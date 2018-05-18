#pragma once

#include "cocos2d.h"
USING_NS_CC;

class PlayerUnit;
class Boss;

class GameplayScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);

	void movePlayer(Touch * touch, Event * event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayScene);

	void update(float delta) override;

private:
	PlayerUnit* player;
	Boss* boss;
	TMXTiledMap* testMap;
};
