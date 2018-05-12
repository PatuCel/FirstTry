#include "Scenes\MainMenuScene.h"
#include "Managers\SceneManager.h"

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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cityscene.plist");

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	// background
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(origin.x + visibleSize.x / 2, origin.y + visibleSize.y / 2);
	this->addChild(background);

	// sprite
	//auto frames = getAnimation("capguy/walk/%04d.png", 8);
	//auto sprite = Sprite::createWithSpriteFrame(frames.front());
	//background->addChild(sprite);
	//sprite->setPosition(100, 620);

	//auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	//sprite->runAction(RepeatForever::create(Animate::create(animation)));

	//auto movement = MoveTo::create(10, Vec2(2148, 620));
	//auto resetPosition = MoveTo::create(0, Vec2(-150, 620));
	//auto sequence = Sequence::create(movement, resetPosition, NULL);
	//sprite->runAction(RepeatForever::create(sequence));


	// Menu Items
	auto playItem = MenuItemImage::create("menu_play0.png", "menu_play1.png", [&](Ref *sender) { changeScene(SceneManager::GAMEPLAY_SCENE); });

	if (playItem != nullptr || playItem->getContentSize().width > 0 || playItem->getContentSize().height > 0)
	{
		float x = origin.x + Director::getInstance()->getVisibleSize().width - playItem->getContentSize().width / 2;
		float y = origin.y + playItem->getContentSize().height / 2;
		playItem->setPosition(x, y);
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
