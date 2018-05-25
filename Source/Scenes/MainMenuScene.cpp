#include "Scenes/MainMenuScene.h"
#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"

using namespace cocos2d;


Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}


bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	ResourceManager::getInstance()->LoadSpriteSheet("tp_level_01.plist");

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	// background
	//auto background = ResourceManager::getInstance()->LoadSprite("background.png");
	//background->setPosition(origin.x + visibleSize.x / 2, origin.y + visibleSize.y / 2);
	//this->addChild(background);

	// Menu Items
	auto playItem = MenuItemImage::create("menu_play0.png", "menu_play1.png", [&](Ref *sender) { changeScene(SceneManager::GAMEPLAY_SCENE); });

	if (playItem != nullptr || playItem->getContentSize().width > 0 || playItem->getContentSize().height > 0)
	{
		playItem->setPosition(origin.x + visibleSize.x / 2, origin.y + visibleSize.y / 2);
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void MainMenuScene::changeScene(int scene)
{
		this->removeAllChildren();
		SceneManager::getInstance()->changeScene((SceneManager::EnumSceneType)scene, true);
}


Vector<SpriteFrame*> MainMenuScene::getAnimation(const char *format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}
