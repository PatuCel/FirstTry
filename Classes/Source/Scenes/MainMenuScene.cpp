#include "Scenes\MainMenuScene.h"
#include "Managers\SceneManager.h"
#include "..\libs\cocos_creator\reader\CreatorReader.h"
#include "globals.h"

using namespace cocos2d;

cocos2d::Scene* MainMenuScene::g_currentScene = nullptr;;
creator::CreatorReader* MainMenuScene::g_reader = nullptr;


Scene* MainMenuScene::scene()
{
	auto scene = createScene(CC_SCENE_MENU_MAIN);
	MainMenuScene::handleButtonsClick(scene);
	return scene;
}

////////////////////////////////////////////////////
// private functions
///////////////////////////////////////////////////

cocos2d::Scene* MainMenuScene::createScene(const std::string& ccreatorPath)
{
	auto reader = creator::CreatorReader::createWithFilename(ccreatorPath);
	reader->setup();
	auto scene = reader->getSceneGraph();

	MainMenuScene::g_reader = reader;
	MainMenuScene::g_currentScene = scene;

	return scene;;
}

void MainMenuScene::repalceScene(const std::string& ccreatorPath)
{
	auto scene = createScene(ccreatorPath);
	//auto backButton = MainMenuScene::createBackButton();
	//scene->addChild(backButton);
	Director::getInstance()->replaceScene(scene);
}

void MainMenuScene::handleButtonClick(cocos2d::Scene* scene, const std::string& buttonName, const std::string& ccreatorPath)
{
	auto button = utils::findChild<ui::Button*>(scene, buttonName);
	button->addClickEventListener([=](Ref*) {
		SceneManager::getInstance()->changeScene(SceneManager::GAMEPLAY_SCENE,true);
		//MainMenuScene::repalceScene(ccreatorPath);
	});
}

void MainMenuScene::handleButtonsClick(cocos2d::Scene* scene)
{
	MainMenuScene::handleButtonClick(scene, "Play_button", "creator/scenes/Label/CreatorLabels.ccreator");
	/*MainMenuScene::handleButtonClick(scene, "mask", "creator/scenes/Mask/Mask.ccreator");
	MainMenuScene::handleButtonClick(scene, "pageview", "creator/scenes/pageview/pageview.ccreator");
	MainMenuScene::handleButtonClick(scene, "prefab", "creator/scenes/prefab/prefab-test.ccreator");
	MainMenuScene::handleButtonClick(scene, "richtext", "creator/scenes/richtext/CreatorRichtext.ccreator");
	MainMenuScene::handleButtonClick(scene, "slider", "creator/scenes/slider/slider.ccreator");
	MainMenuScene::handleButtonClick(scene, "sprites", "creator/scenes/sprites/CreatorSprites.ccreator");
	MainMenuScene::handleButtonClick(scene, "tilemap", "creator/scenes/tilemap/CreatorTilemap.ccreator");
	MainMenuScene::handleButtonClick(scene, "toggle", "creator/scenes/toggle/toggle.ccreator");
	MainMenuScene::handleButtonClick(scene, "toggle_group", "creator/scenes/toggle_group/toggle_group.ccreator");
	MainMenuScene::handleButtonClick(scene, "ui", "creator/scenes/ui/CreatorUI.ccreator");*/

	//MainMenuScene::handleAnimationButtonClick(scene);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//HelloWorld::handleButtonClick(scene, "webview", "creator/scenes/webview/WebView.ccreator");
#endif
	/*MainMenuScene::handleColliderButtonClick(scene);
	MainMenuScene::handleVideoButtonClick(scene);
	MainMenuScene::handleDragonbones(scene);*/

	//MainMenuScene::handleButtonClick(scene, "motionstreak", "creator/scenes/motionstreak/motionstreak.ccreator");
}
