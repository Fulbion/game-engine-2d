#include "Application/Cube.hpp"

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::onCreate()
{
	this->m_entity = this->getEntitySystem()->createEntity<Entity>();
	this->m_entity->createComponent<Component>();
}

void Cube::onUpdate(float i_deltaTime)
{
	this->m_elapsedTime += i_deltaTime;

	/*
		
		if (this->m_entity && this->m_elapsedTime >= 3)
		{
			this->m_entity->getComponent<Component>()->release();
			this->m_entity->release();
			this->m_entity = nullptr;
		}

	*/

	this->m_entity->getTransformComponent()->setRotation({ this->m_elapsedTime, 0, 0 });
}