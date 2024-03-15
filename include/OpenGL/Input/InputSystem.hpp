#pragma once

#include "OpenGL/Common.hpp"

#include "OpenGL/Input/InputListener.hpp"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();

	void addListener(InputListener* i_listener);
	void removeListener(InputListener* i_listener);

private:
	std::unordered_map<InputListener*, InputListener*> m_listeners;
	BYTE m_keysState[256] = {};
	BYTE m_previousKeysState[256] = {};
	POINT m_previousMousePosition = {};
	bool m_isFirstTime = true;
};
