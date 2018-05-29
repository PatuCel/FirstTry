#include "AppDelegate.h"
#include "Globals.h"
#include "Scenes/GameplayScene.h"
#include "Scenes/MainMenuScene.h"
#include "Managers/SceneManager.h"
#include "Managers/ConfigManager.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

static Size smallResolutionSize = Size(SCREEN_RESOLUTION_W / 2, SCREEN_RESOLUTION_H / 2);
static Size mediumResolutionSize = Size(SCREEN_RESOLUTION_W, SCREEN_RESOLUTION_H);
static Size largeResolutionSize = Size(SCREEN_RESOLUTION_W * 2, SCREEN_RESOLUTION_H * 2);

//target resolution
static cocos2d::Size designResolutionSize = mediumResolutionSize;


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		HDC hScreenDC = GetDC(nullptr);
		int initPosX = (GetDeviceCaps(hScreenDC, HORZRES) / 2) - designResolutionSize.width / 2;
		int initPosY = (GetDeviceCaps(hScreenDC, VERTRES) / 2) - designResolutionSize.height / 2;
		glview = GLViewImpl::createWithRect("FirstTry", Rect(initPosX, initPosY, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("FirstTry");
#endif
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

	std::vector<std::string> searchPaths;
	float scaleFactor = 1.0f;
	Size frameSize = glview->getFrameSize();

	if (frameSize.height > mediumResolutionSize.height)
	{
		searchPaths.push_back("res/HDR");
		scaleFactor = MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width);
	}
	else if (frameSize.height > smallResolutionSize.height)
	{
		searchPaths.push_back("res/HD");
		scaleFactor = MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width);
	}
	else
	{
		searchPaths.push_back("res/SD");
		scaleFactor = MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width);
	}

	director->setContentScaleFactor(scaleFactor);
	FileUtils::getInstance()->setSearchPaths(searchPaths);
	register_all_packages();

	//Init All Managers
	SceneManager::getInstance();
	//Iribe
	ConfigManager::Load_Shooter_Config("Resources/Config.json");

	SceneManager::getInstance()->changeScene(SceneManager::MAINMENU_SCENE, true); //new for calling Scenes

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
