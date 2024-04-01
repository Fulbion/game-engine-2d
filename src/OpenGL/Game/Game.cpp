#include <Windows.h>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image/stb_image.h>

#include "OpenGL/Game/Game.hpp"
#include "OpenGL/Graphics/VertexArrayObject.hpp"
#include "OpenGL/Graphics/ShaderProgram.hpp"
#include "OpenGL/Graphics/UniformBuffer.hpp"
#include "OpenGL/Graphics/Graphics.hpp"
#include "OpenGL/Window/Window.hpp"

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
	glm::vec3 positions[] =
	{
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f,  0.5f, 0.0f),
		glm::vec3( 0.5f,  0.5f, 0.0f),
	};

	glm::vec2 texcoords[] =
	{
		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(0, 1),
		glm::vec2(1, 1),
	};

	Vertex vertices[] =
	{
		{ positions[0], texcoords[0] },
		{ positions[1], texcoords[1] },
		{ positions[2], texcoords[2] },
		{ positions[3], texcoords[3] }
	};

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 1
	};

	VertexAttribute attributes[] =
	{
		sizeof(glm::vec3) / sizeof(GLfloat),
		sizeof(glm::vec2) / sizeof(GLfloat)
	};

	
	this->m_shader = this->m_graphics->createShaderProgram(L"../../../resources/shaders/vertex.vert", L"../../../resources/shaders/fragment.frag");
	this->m_vao = this->m_graphics->createVAO({ (void*)vertices, sizeof(Vertex), sizeof(vertices) / sizeof(Vertex), attributes, sizeof(attributes) / sizeof(VertexAttribute)}, {(void*)indices, sizeof(indices)});
	this->m_texture = this->m_graphics->createTexture("../../../resources/textures/diamond_ore.png");
	
	GLuint tex0Uniform = glGetUniformLocation(this->m_shader->getID(), "tex0");
	glUseProgram(this->m_shader->getID());
	glUniform1i(tex0Uniform, 0);
}

void Game::onUpdate()
{
	this->m_graphics->clear(0.14, 0.17, 0.21, 1);

	this->m_graphics->setShaderProgram(this->m_shader);
	this->m_graphics->setTexture(this->m_texture);
	this->m_graphics->setVAO(this->m_vao);

	this->m_graphics->drawIndexedTriangles(TriangleType::TriangleList, 6);

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
