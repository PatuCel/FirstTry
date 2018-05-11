#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "ui/CocosGUI.h" //Button Widgets,Labels etc
#include "cocostudio/CocoStudio.h" //CCLoader 

#include "cocos2d.h"
USING_NS_CC;

class LogoScene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual void onEnter();
	virtual void onExit();
	void initGUI();//init all the graphics of the scene

    // implement the "static create()" method manually
	CREATE_FUNC(LogoScene);
	//go to the next scene with a Delay of 1.5sec
	void nextScene(float);
};

#endif // __LOGO_SCENE_H__
