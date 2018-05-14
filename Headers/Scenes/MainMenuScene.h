#pragma once

#include "cocos2d.h"
USING_NS_CC;

class MainMenuScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

	void changeScene(int scene);

	Vector<SpriteFrame*> getAnimation(const char * format, int count);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};
