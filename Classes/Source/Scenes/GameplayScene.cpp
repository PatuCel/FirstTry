#include "SimpleAudioEngine.h"
#include "Scenes/GameplayScene.h"
#include "Units/PlayerUnit.h"
#include "Units/Boss.h"
#include "Units/EnemyUnit.h"
#include "Managers/ResourceManager.h"
#include "Managers/MapManager.h"
#include "Managers/CameraManager.h"
#include "Globals.h"
#include "ui/UILoadingBar.h"
#include "components/Hud.h"

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


	ResourceManager::getInstance()->LoadSpriteSheet("units.plist");

	ResourceManager::getInstance()->LoadSpriteSheet("tp_level_01.plist");
	

	// boss sprite
	auto frameArray = ResourceManager::getInstance()->LoadSpriteAnimation("frame_%02d_delay-0.05s.png", 20);
	boss = Boss::createBoss(frameArray, 0.05f);
	boss->setPosition(visibleSize.width / 2, visibleSize.height - boss->getContentSize().height);
	boss->setHealth(500);
	this->addChild(boss, 2);

	player = PlayerUnit::createPlayer("player.png", Vec2(visibleSize.width / 2, visibleSize.height / 4), BaseUnit::UnitState::UNIT_STATE_NORMAL, BaseUnit::UnitWeapon::ALLIED);
	this->addChild(player, 1);

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

	hud = Hud::createHud();
	hud->setScore("961");	//Player Score
	hud->setHP(65);			//Player Health
	hud->addButtonSkillListener([=](int id) { }); //TODO:
	hud->addButtonPauseListener([=](bool isPaused) {}); //TODO:
	this->addChild(hud, 10);

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


void GameplayScene::movePlayer(PlayerMoveDirection direction)
{
	bool canMovePlayer = true;

	int moveOffsetX = 0;
	int moveOffsetY = 0;

	switch (direction)
	{
		case PLAYER_MOVE_DIRECTION_UP:
			moveOffsetY -= 2;
			break;

		case PLAYER_MOVE_DIRECTION_LEFT:
			moveOffsetX += 2;
			break;

		case PLAYER_MOVE_DIRECTION_DOWN:
			moveOffsetY += 2;
			break;

		case PLAYER_MOVE_DIRECTION_RIGHT:
			moveOffsetX -= 2;
			break;
	}

	Vec2 newPos = player->getPosition() + Vec2(moveOffsetX, moveOffsetY);

	Vec2 tilePosition = MapManager::getInstance()->tileFromPosition(newPos);
	int tileGID = MapManager::getInstance()->getLayer(MapLayer::MAP_LAYER_COLLISIONS)->getTileGIDAt(tilePosition);

	if (tileGID)
	{
		CCLOG("Tile Collision!!!");
		canMovePlayer = false;
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		Rect playerRect = Rect(Vec2(player->getBoundingBox().origin.x + moveOffsetX, player->getBoundingBox().origin.y + moveOffsetY), player->getBoundingBox().size);
		Rect enemyRect = enemies[i]->getBoundingBox();

		if (playerRect.intersectsRect(enemyRect))
		{
			CCLOG("Enemy Collision!!!");
			canMovePlayer = false;
		}
	}

	if (canMovePlayer)
	{
		player->setPosition(newPos);
	}
}


void GameplayScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		player->startPlayerDirection(PLAYER_MOVE_DIRECTION_UP);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		player->startPlayerDirection(PLAYER_MOVE_DIRECTION_LEFT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		player->startPlayerDirection(PLAYER_MOVE_DIRECTION_DOWN);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		player->startPlayerDirection(PLAYER_MOVE_DIRECTION_RIGHT);
	}
}

void GameplayScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		player->stopPlayerDirection(PLAYER_MOVE_DIRECTION_UP);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		player->stopPlayerDirection(PLAYER_MOVE_DIRECTION_LEFT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		player->stopPlayerDirection(PLAYER_MOVE_DIRECTION_DOWN);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		player->stopPlayerDirection(PLAYER_MOVE_DIRECTION_RIGHT);
	}
}

bool GameplayScene::loadCollectibles()
{
	return true;
}

bool GameplayScene::loadEnemies()
{
	std::vector<Vec2> enemiesTiles = MapManager::getInstance()->getTilesFromLayer(MAP_LAYER_ENEMIES);

	for (int x = 0; x<enemiesTiles.size(); x++)
	{
		EnemyUnit* tmpEnemy;

		int enemyTileGID = MapManager::getInstance()->getLayer(MapLayer::MAP_LAYER_ENEMIES)->getTileGIDAt(enemiesTiles[x]);

		switch (enemyTileGID)
		{
			case 3: //Enemy0 Type: 01
				tmpEnemy = EnemyUnit::createEnemy("enemy01.png", Vec2(MapManager::getInstance()->positionFromTile(enemiesTiles[x])), BaseUnit::UnitState::UNIT_STATE_NORMAL, BaseUnit::UnitWeapon::ALLIED);
				break;

			case 4: //Enemy Type: 02
				tmpEnemy = EnemyUnit::createEnemy("enemy02.png", Vec2(MapManager::getInstance()->positionFromTile(enemiesTiles[x])), BaseUnit::UnitState::UNIT_STATE_NORMAL, BaseUnit::UnitWeapon::ALLIED);
				break;
		}
		
		enemies.push_back(tmpEnemy);
	}

	for (int y = 0; y<enemies.size(); y++)
	{
		this->addChild(enemies[y], 1);
	}

	return true;
}


void GameplayScene::update(float delta)
{
	/*Vec2 cameraPos = CameraManager::getInstance()->getCameraPosition();	

	MapManager::getInstance()->checkForLoop();

	CameraManager::getInstance()->setCameraPosition(Vec2(cameraPos.x, cameraPos.y + 1));

	movePlayer(Vec2(player->getPosition().x, player->getPosition().y + 1));
	hud->setPositionY(hud->getPositionY() + 1);
	boss->setPositionY(boss->getPositionY() + 1);*/

	if(player->isMovingUp() && !player->isMovingDown())
	{
		movePlayer(PLAYER_MOVE_DIRECTION_DOWN);
	}
	else if(player->isMovingDown() && !player->isMovingUp())
	{
		movePlayer(PLAYER_MOVE_DIRECTION_UP);
	}

	if(player->isMovingLeft() && !player->isMovingRight())
	{
		movePlayer(PLAYER_MOVE_DIRECTION_RIGHT);
	}
	else if(player->isMovingRight() && !player->isMovingLeft())
	{
		movePlayer(PLAYER_MOVE_DIRECTION_LEFT);
	}
}