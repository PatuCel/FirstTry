#include "Managers/SceneManager.h"
#include "Scenes/LogoScene.h"
#include "Scenes/GameplayScene.h"
#include "Scenes/MainMenuScene.h"

SceneManager* SceneManager::mSceneManager = NULL;
SceneManager::SceneManager()
{
}
SceneManager::~SceneManager()
{
}

SceneManager * SceneManager::getInstance()
{
	if (mSceneManager == NULL)
	{
		mSceneManager = new SceneManager();
		if (mSceneManager&&mSceneManager->init())
		{
			mSceneManager->autorelease();
			mSceneManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(mSceneManager);
			mSceneManager = NULL;
		}
	}
	return mSceneManager;
}


// on "init" you need to initialize your instance
bool SceneManager::init()
{
    return true;
}

void SceneManager::changeScene(EnumSceneType SceneType, bool replace){
	
	Scene* pScene = NULL;
	switch (SceneType) {
	case LOGO_SCENE:
		pScene = LogoScene::createScene();
		break;
	case GAMEPLAY_SCENE:
		pScene = GameplayScene::createScene();
		break;
	case MAINMENU_SCENE:
		pScene = MainMenuScene::createScene();
		break;
	}
	if (pScene == NULL)
		return;

	Director *pDirector = Director::getInstance();
	Scene* curScene = pDirector->getRunningScene();
	if (curScene == NULL)
		pDirector->runWithScene(pScene);
	else if (replace)
		pDirector->replaceScene(pScene);
	else
		pDirector->pushScene(pScene);

}
//Only works when there is a PushScene
void SceneManager::goBackScene(){
	Director::getInstance()->popScene();
}

