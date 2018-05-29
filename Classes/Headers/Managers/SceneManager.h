#pragma once

#include "cocos2d.h"
USING_NS_CC;

class SceneManager :public Ref
{
public:
	SceneManager();
	~SceneManager();
	static SceneManager* getInstance();

	enum EnumSceneType{
		LOGO_SCENE = 0,	
		MAINMENU_SCENE,						
		LOADING_SCENE,				
		GAMEPLAY_SCENE
	};

	enum EnumLoading{
		LOADING_TO_MAINMENU = 0,
		LOADING_TO_MISSION
	};
	enum EnumMissions{
		NO_MISSION = 0,
		W1_MISSION1,
		W1_MISSION2,
		W1_MISSION3

	};
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	/*
	remove the current scene (popScene)
	*/
	void goBackScene();

	Scene * createScene(const std::string & ccreatorPath);

	//@replace true if you want to replace current scene	
	void changeScene(EnumSceneType SceneType,bool replace);
	/*
	
	*/
	//void loadingScene(EnumLoading loadingType, EnumMissions SceneType);
private:
	static SceneManager* mSceneManager;
};
