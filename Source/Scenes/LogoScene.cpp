#include "Scenes/LogoScene.h"
#include "Managers/SceneManager.h"

using namespace ui; //use for Button, Scrollview,Label,Panel etc.
using namespace cocostudio::timeline;

Scene* LogoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LogoScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	initGUI();

    return true;
}

void LogoScene::initGUI(){	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("Logo.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(sprite);
	this->scheduleOnce(schedule_selector(LogoScene::nextScene), 1.5f);	
}

void LogoScene::nextScene(float dt)
{
	this->removeAllChildren();
	SceneManager::getInstance()->changeScene(SceneManager::GAMEPLAY_SCENE, true);	
}

void LogoScene::onEnter() //Every time you Enter on this scene after push, replace, pop will be enter here
{
	Layer::onEnter();

}

void LogoScene::onExit()
{
	//this->getEventDispatcher()->removeEventListenersForTarget(this);
	Layer::onExit();
}