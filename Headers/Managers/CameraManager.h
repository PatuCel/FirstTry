#pragma once

#include "cocos2d.h"
USING_NS_CC;

class CameraManager
{
public:
	static CameraManager* getInstance();

	static void setCameraPosition(Vec2 pos);
	static Vec2 getCameraPosition();

private:
	static CameraManager* m_cameraManager;

	static Camera* m_camera;

	CameraManager();
};
