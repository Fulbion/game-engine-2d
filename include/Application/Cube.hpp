#pragma once

#include "Engine.hpp"

class Cube : public Entity
{
public:
	Cube();
	~Cube();

	virtual void onCreate();
	virtual void onUpdate(float i_deltaTime);

private:
	float m_elapsedTime = 0.0f;
	Entity* m_entity = nullptr;
};