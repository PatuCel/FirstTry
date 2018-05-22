#include "Managers/CameraManager.h"

CameraManager* CameraManager::m_cameraManager = nullptr;
Camera* CameraManager::m_camera = nullptr;

CameraManager::CameraManager()
{
	m_camera = Camera::getDefaultCamera();
}

CameraManager* CameraManager::getInstance()
{
	if(m_cameraManager == nullptr)
	{
		m_cameraManager = new CameraManager();
	}
	return m_cameraManager;
}

void CameraManager::setCameraPosition(Vec2 pos)
{
	m_camera->setPosition(pos);
}

Vec2 CameraManager::getCameraPosition()
{
	return m_camera->getPosition();
}