#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameplayScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayScene);
};
