#include "Application/Application.hpp"

Application::Application()
{
}

Application::~Application()
{
}

void Application::onCreate()
{
	Game::onCreate();
	this->m_cube = this->getEntitySystem()->createEntity<Cube>();
}

void Application::onUpdate(float i_deltaTime)
{
	this->m_elapsedTime += i_deltaTime;

}
