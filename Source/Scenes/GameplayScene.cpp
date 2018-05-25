#include "SimpleAudioEngine.h"
#include "Scenes/GameplayScene.h"
#include "Units/Boss.h"
#include "Units/EnemyUnit.h"
#include "Managers/ResourceManager.h"
#include "Managers/MapManager.h"
#include "Managers/CameraManager.h"
#include "Globals.h"

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
	//auto frameArray = ResourceManager::getInstance()->LoadSpriteAnimation("frame_%02d_delay-0.05s.png", 20);
	//auto boss = Boss::createBoss(frameArray, 0.05f);
	//boss->setPosition(visibleSize.width / 2, visibleSize.height - boss->getContentSize().height / 2);
	//this->addChild(boss, 1);

	_player = PlayerUnit::createPlayer("player.png", Vec2(SCREEN_RESOLUTION_W/2, SCREEN_RESOLUTION_H/2), BaseUnit::UnitState::UNIT_STATE_NORMAL, BaseUnit::UnitWeapon::UNIT_WEAPON_DEFAULT);
	this->addChild(_player, 1);
	
	MapManager::getInstance()->loadMap("test.tmx");
	this->addChild(MapManager::getInstance()->getMap(), 0);
	loadCollectibles();
	loadEnemies();	
		
	///Touch events
	/*auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) { return true; };
	listener->onTouchMoved = [=](Touch* touch, Event* event) { movePlayer(touch, event); };
	listener->onTouchEnded = [=](Touch* touch, Event* event) {};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameplayScene::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameplayScene::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

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

void GameplayScene::movePlayer(Vec2 pos)
{
	Vec2 tilePosition = MapManager::getInstance()->tileFromPosition(pos);
	int tileGID = MapManager::getInstance()->getLayer(MapLayer::MAP_LAYER_COLLISIONS)->getTileGIDAt(tilePosition);
	if(!tileGID)
	{
		_player->setPosition(pos);
	}
}

void GameplayScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		_player->startPlayerDirection(PLAYER_MOVE_DIRECTION_UP);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		_player->startPlayerDirection(PLAYER_MOVE_DIRECTION_LEFT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		_player->startPlayerDirection(PLAYER_MOVE_DIRECTION_DOWN);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		_player->startPlayerDirection(PLAYER_MOVE_DIRECTION_RIGHT);
	}
}
void GameplayScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		_player->stopPlayerDirection(PLAYER_MOVE_DIRECTION_UP);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		_player->stopPlayerDirection(PLAYER_MOVE_DIRECTION_LEFT);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		_player->stopPlayerDirection(PLAYER_MOVE_DIRECTION_DOWN);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		_player->stopPlayerDirection(PLAYER_MOVE_DIRECTION_RIGHT);
	}
}

bool GameplayScene::loadCollectibles()
{
	return true;
}

bool GameplayScene::loadEnemies()
{
	std::vector<Vec2> enemiesTiles =  MapManager::getInstance()->getTilesFromLayer(MAP_LAYER_ENEMIES);

	for(int x=0; x<enemiesTiles.size(); x++)
	{
		auto tmpEnemy = EnemyUnit::createEnemy("player.png", Vec2(MapManager::getInstance()->positionFromTile(enemiesTiles[x])), BaseUnit::UnitState::UNIT_STATE_NORMAL, BaseUnit::UnitWeapon::UNIT_WEAPON_DEFAULT);
		_enemies.push_back(tmpEnemy);
	}

	for(int y=0; y<_enemies.size(); y++)
	{
		this->addChild(_enemies[y], 1);
	}

	return true;
}

void GameplayScene::update(float delta)
{
	CameraManager::getInstance()->setCameraPosition(Vec2(CameraManager::getInstance()->getCameraPosition().x, CameraManager::getInstance()->getCameraPosition().y + 1));
	
	movePlayer(Vec2(_player->getPosition().x, _player->getPosition().y + 1));

	if(_player->isMovingUp() && !_player->isMovingDown())
	{
		movePlayer(Vec2(_player->getPosition().x, _player->getPosition().y + 2));
	}
	else if(_player->isMovingDown() && !_player->isMovingUp())
	{
		movePlayer(Vec2(_player->getPosition().x, _player->getPosition().y - 2));
	}

	if(_player->isMovingLeft() && !_player->isMovingRight())
	{
		movePlayer(Vec2(_player->getPosition().x - 2, _player->getPosition().y));
	}
	else if(_player->isMovingRight() && !_player->isMovingLeft())
	{
		movePlayer(Vec2(_player->getPosition().x + 2, _player->getPosition().y));
	}
}