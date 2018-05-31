#include "cocos2d.h"
#include "AppDelegate.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "main.h"

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	AppDelegate app;
	
	return Application::getInstance()->run();
}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <memory>
#include <jni.h>

namespace
{
	std::unique_ptr<AppDelegate> appDelegate;
}

void cocos_android_app_init(JNIEnv* env)
{
	appDelegate.reset(new AppDelegate());
}
#endif
