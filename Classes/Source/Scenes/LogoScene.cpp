#include "Scenes/LogoScene.h"
#include "Managers/SceneManager.h"
#include "CreatorReader.h"

using namespace ui; //use for Button, Scrollview,Label,Panel etc.
using namespace cocostudio::timeline;

Scene* LogoScene::createScene()
{
	creator::CreatorReader* reader = creator::CreatorReader::createWithFilename("creator/Scenes/Logo.ccreator");
	reader->setup();
	Scene* scene = reader->getSceneGraph();

	return scene;
	/*
	creator::CreatorReader* reader = creator::CreatorReader::createWithFilename("creator/Scenes/Logo.ccreator");
	reader->setup();
	// get the scene graph
	Scene* scene = reader->getSceneGraph();

	// ...and use it
	//Director::getInstance()->replaceScene(scene);

    // return the scene
    return scene;
	*/
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init() )
    {
        return false;
    }

	initGUI();

    return true;
}

void LogoScene::initGUI(){

	//creator::CreatorReader* reader = creator::CreatorReader::createWithFilename("creator/Scenes/Logo.ccreator");
	//reader->setup();
	// get the scene graph
	//Scene* scene = reader->getSceneGraph();

	// ...and use it
	//::getInstance()->replaceScene(scene);

	// return the scene
	//return scene;

	/*
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("logo.plist");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::createWithSpriteFrameName("logo.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(sprite);
	this->scheduleOnce(schedule_selector(LogoScene::nextScene), 1.5f);
	*/
	this->scheduleOnce(schedule_selector(LogoScene::nextScene), 1.5f);
}

void LogoScene::nextScene(float dt)
{
	this->removeAllChildren();
	SceneManager::getInstance()->changeScene(SceneManager::MAINMENU_SCENE, true);	
}

void LogoScene::onEnter() //Every time you Enter on this scene after push, replace, pop will be enter here
{
	Scene::onEnter();

}

void LogoScene::onExit()
{
	//this->getEventDispatcher()->removeEventListenersForTarget(this);
	Scene::onExit();
}