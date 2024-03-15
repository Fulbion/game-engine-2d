#include "OpenGL/Input/InputSystem.hpp"

#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	POINT currentMousePosition = {};
	
	GetCursorPos(&currentMousePosition);

	if (this->m_isFirstTime)
	{
		this->m_previousMousePosition = currentMousePosition;
		this->m_isFirstTime = false;
	}

	if (currentMousePosition.x != this->m_previousMousePosition.x || currentMousePosition.y != this->m_previousMousePosition.y)
	{
		auto it = this->m_listeners.begin();

		while (it != this->m_listeners.end())
		{
			(*it).second->onMouseMove(glm::ivec2(currentMousePosition.x - this->m_previousMousePosition.x, currentMousePosition.y - this->m_previousMousePosition.y));
			++it;
		}
	}

	this->m_previousMousePosition = currentMousePosition;

	if (GetKeyboardState(this->m_keysState))
	{
		for (UINT i = 0; i < 256; i++)
		{
			if (this->m_keysState[i] & 0x80)
			{
				auto it = this->m_listeners.begin();

				while (it != this->m_listeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (this->m_keysState[i] != this->m_previousKeysState[i])
							(*it).second->onMouseButtonPressed(MouseButton::Left, { currentMousePosition.x, currentMousePosition.y });
					}

					if (i == VK_MBUTTON)
					{
						if (this->m_keysState[i] != this->m_previousKeysState[i])
							(*it).second->onMouseButtonPressed(MouseButton::Middle, { currentMousePosition.x, currentMousePosition.y });
					}

					if (i == VK_RBUTTON)
					{
						if (this->m_keysState[i] != this->m_previousKeysState[i])
							(*it).second->onMouseButtonPressed(MouseButton::Right, { currentMousePosition.x, currentMousePosition.y });
					}

					(*it).second->onKeyPressed(i);
					++it;
				}
			}

			else
			{
				if (this->m_keysState[i] != this->m_previousKeysState[i])
				{
					auto it = this->m_listeners.begin();

					while (it != this->m_listeners.end())
					{
						if (i == VK_LBUTTON)
						{
							(*it).second->onMouseButtonReleased(MouseButton::Left, { currentMousePosition.x, currentMousePosition.y });
						}

						if (i == VK_MBUTTON)
						{
							(*it).second->onMouseButtonReleased(MouseButton::Middle, { currentMousePosition.x, currentMousePosition.y });
						}

						if (i == VK_RBUTTON)
						{
							(*it).second->onMouseButtonReleased(MouseButton::Right, { currentMousePosition.x, currentMousePosition.y });
						}

						(*it).second->onKeyReleased(i);
						++it;
					}
				}
			}
		}

		memcpy(this->m_previousKeysState, this->m_keysState, sizeof(BYTE) * 256);
	}
}

void InputSystem::addListener(InputListener* i_listener)
{
	this->m_listeners.insert(std::make_pair<InputListener*, InputListener*>(std::forward<InputListener*>(i_listener), std::forward<InputListener*>(i_listener)));
}

void InputSystem::removeListener(InputListener* i_listener)
{
	auto it = this->m_listeners.find(i_listener);

	if (it != this->m_listeners.end())
	{
		this->m_listeners.erase(it);
	}
}
