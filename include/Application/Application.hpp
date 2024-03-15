#pragma once

#include "Engine.hpp"
#include "Application/Cube.hpp"

class Application : public Game
{
public:
	Application();
	~Application();

	virtual void onCreate();
	virtual void onUpdate(float i_deltaTime);

private:
	float m_elapsedTime = 0.0f;
	Cube* m_cube = nullptr;
};
