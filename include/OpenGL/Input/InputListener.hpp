#pragma once

class InputListener
{
public:
	InputListener()
	{

	}

	~InputListener()
	{

	}

	virtual void onKeyPressed(int i_key) = 0;
	virtual void onKeyReleased(int i_key) = 0;
	virtual void onMouseMove(const glm::ivec2& i_position) = 0;
	virtual void onMouseButtonPressed(const MouseButton& i_button, const glm::ivec2& i_position) = 0;
	virtual void onMouseButtonReleased(const MouseButton& i_button, const glm::ivec2& i_position) = 0;

private:

};