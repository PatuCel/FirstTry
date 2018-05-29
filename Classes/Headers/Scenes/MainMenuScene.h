#pragma once

#include "cocos2d.h"
namespace creator
{
	class CreatorReader;
}
USING_NS_CC;

class MainMenuScene 
{
public:
	static cocos2d::Scene* scene();

private:
    static Scene* createScene(const std::string& ccreatorPath);
	static void repalceScene(const std::string& ccreatorPath);
	static void handleButtonClick(cocos2d::Scene* scene, const std::string& buttonName, const std::string& ccreatorPath);
	static void handleButtonsClick(cocos2d::Scene* scene);	
	//static void handleAnimationButtonClick(cocos2d::Scene* scene);

	static cocos2d::Scene* g_currentScene;
	static creator::CreatorReader* g_reader;  
};
