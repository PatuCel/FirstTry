#include "SimpleAudioEngine.h"
#include "Scenes/GameplayScene.h"
#include "Units/PlayerUnit.h"
#include "Units/Boss.h"
#include "Managers/LevelManager.h"
#include "Managers/ResourceManager.h"
#include "ui/UILoadingBar.h"


Scene* GameplayScene::createScene()
{
    return GameplayScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameplayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if(!Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameplayScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);


	ResourceManager::getInstance()->LoadSpriteSheet("tp_level_01.plist");

	// boss sprite
	auto frameArray = ResourceManager::getInstance()->LoadSpriteAnimation("frame_%02d_delay-0.05s.png", 20);
	_boss = Boss::createBoss(frameArray, 0.05f);
	_boss->setPosition(visibleSize.width / 2, visibleSize.height - _boss->getContentSize().height / 2);
	_boss->setHealth(500);
	this->addChild(_boss);

	_player = PlayerUnit::createPlayer("player.png", Vec2(50, 50), BaseUnit::UnitState::UNIT_STATE_NORMAL, BaseUnit::UnitWeapon::UNIT_WEAPON_DEFAULT);
	this->addChild(_player, 1);

	LevelManager::getInstance()->readLevel("level_001.json");

	testMap = TMXTiledMap::create("test.tmx");
	this->addChild(testMap, 0);

	///Touch events
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) { return true; };
	listener->onTouchMoved = [=](Touch* touch, Event* event) { movePlayer(touch, event); };
	listener->onTouchEnded = [=](Touch* touch, Event* event) {};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

    return true;
}


void GameplayScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void GameplayScene::movePlayer(Touch* touch, Event* event)
{
	auto location = touch->getLocation();
	if (_player->getBoundingBox().containsPoint(location))
		_player->setPosition(location);

	//Test health -- 
	if (_boss->getBoundingBox().containsPoint(location))
	{
		_boss->setPosition(location);
		_boss->reduceHealth(10);
	}
}

void GameplayScene::update(float delta)
{
	testMap->setPosition(Vec2(testMap->getPosition().x, testMap->getPosition().y - 1));
}