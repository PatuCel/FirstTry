#include "Managers\InputManager.h"
#include "cocos\base\CCEventDispatcher.h"

USING_NS_CC;

InputManager::InputManager()
{
}

void InputManager::init()
{

	//Create the labels:
	for (int i = 0; i < MAX_TOUCHES; ++i)
	{
		labelTouchLocations[i] = Label::createWithSystemFont("", "Arial", 42);
		labelTouchLocations[i]->setVisible(false);
		//this->addChild(labelTouchLocations[i]);
	}

	cocos2d::EventListenerMouse* mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = [] (cocos2d::Event* event) {
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		mouseEvent->getMouseButton();
		std::stringstream labelmsg;
		auto bounds = event->getCurrentTarget()->getBoundingBox();
		if(bounds.containsPoint(tou
	};

}


InputManager::~InputManager()
{
}
