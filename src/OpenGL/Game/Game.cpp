#include <Windows.h>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OpenGL/Game/Game.hpp"
#include "OpenGL/Graphics/VertexArrayObject.hpp"
#include "OpenGL/Graphics/ShaderProgram.hpp"
#include "OpenGL/Graphics/UniformBuffer.hpp"
#include "OpenGL/Graphics/Graphics.hpp"
#include "OpenGL/Window/Window.hpp"


struct UniformData
{
	glm::mat4x4 world;
	glm::mat4x4 projection;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texcoord;
};

Game::Game()
{
	this->m_graphics = std::make_unique<Graphics>();
	this->m_window = std::make_unique<Window>();

	this->m_window->makeCurrentContext();

	this->m_graphics->setViewport(this->m_window->getSize());
}

Game::~Game()
{
}

void Game::onCreate()
{
	
}

void Game::onUpdate()
{
	this->m_graphics->clear(0, 1, 0, 1);

	this->m_window->present(false);
}

void Game::onQuit()
{
	this->m_isRunning = false;
}

void Game::run()
{
	this->onCreate();

	while (this->m_isRunning)
	{
		MSG msg;

		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				#ifdef NDEBUG
				if (MessageBox(this->m_window->getHWND(), L"Do you want to quit the application?", L"Game Engine 2D - OpenGL", MB_ICONQUESTION | MB_YESNO) == IDYES)
				#endif // NDEBUG
				this->m_isRunning = false;
			}

			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		Sleep(1);
		this->onUpdate();
	}

	this->onQuit();
}

void Game::quit()
{
	this->m_isRunning = false;
}
