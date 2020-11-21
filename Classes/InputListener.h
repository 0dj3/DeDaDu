#pragma once
#ifndef __Input_Listener_H__
#define __Input_Listener_H__

#include "cocos2d.h"

class InputListener
{
public:
	static InputListener* Instance() {
		if (!instance)
			instance = new InputListener();
		return instance;
	}

	bool Init(cocos2d::Layer* layer);

	cocos2d::EventListenerKeyboard* kbListener;
	bool keyStates[256] = {};

	cocos2d::EventListenerMouse* mouseListener;
	bool mouseStates[15] = {};
	cocos2d::Vec2 mousePosition;

private:
	static InputListener* instance;

	InputListener() { }
	~InputListener() { }

	InputListener(InputListener const&) = delete;
	InputListener& operator= (InputListener const&) = delete;
};

#endif // __Input_Listener_H__
