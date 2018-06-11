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


static Size lowResolutionSize = Size(SCREEN_RESOLUTION_WIDTH, SCREEN_RESOLUTION_HEIGHT);
static Size highResolutionSize = Size(SCREEN_RESOLUTION_WIDTH * 2, SCREEN_RESOLUTION_HEIGHT * 2);

static Size designResolutionSize = lowResolutionSize; //Scale Test: Size(768, 1024); 

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

	//Iribe
	ConfigManager::Load_Shooter_Config("Config.json");

	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("FirstTry", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
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
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);

	std::vector<std::string> searchPaths;

	Size frameSize = glview->getFrameSize();
	if (frameSize.height >= highResolutionSize.height || frameSize.width >= highResolutionSize.width)
	{
		searchPaths.push_back(SEARCH_PATH_HD);
		director->setContentScaleFactor(highResolutionSize.width / frameSize.width);
	}
	else
	{
		searchPaths.push_back(SEARCH_PATH_SD);
		director->setContentScaleFactor(lowResolutionSize.width / frameSize.width);
	}

	//Cocos Creator Scenes 
	searchPaths.push_back(SEARCH_PATH_CREATOR_SCENES);
	FileUtils::getInstance()->setSearchPaths(searchPaths);

	register_all_packages();

	//Init All Managers
	SceneManager::getInstance();

	SceneManager::getInstance()->changeScene(SceneManager::GAMEPLAY_SCENE, true); //new for calling Scenes

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
