#pragma once
#include "cocos2d.h"

class InputManager
{
public:
	InputManager();
	~InputManager();
	cocos2d::Vec2 pos;

private:
	const static int MAX_TOUCHES = 5;
};

