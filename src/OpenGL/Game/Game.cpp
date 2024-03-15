#include <Windows.h>
#include <chrono>

#include "OpenGL/Game/Game.hpp"
#include "OpenGL/Input/InputSystem.hpp"
#include "OpenGL/Graphics/VertexArrayObject.hpp"
#include "OpenGL/Graphics/ShaderProgram.hpp"
#include "OpenGL/Graphics/UniformBuffer.hpp"
#include "OpenGL/Graphics/Graphics.hpp"
#include "OpenGL/Entity/EntitySystem.hpp"
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

static glm::mat4x4 orthoLH(float i_width, float i_height, float i_nearPlane, float i_farPlane)
{
	glm::mat4x4 output = glm::identity<glm::mat4x4>();
	output[0][0] = 2.0f / i_width;
	output[1][1] = 2.0f / i_height;
	output[2][2] = 1.0f / (i_farPlane - i_nearPlane);
	output[3][2] = -(i_nearPlane / (i_farPlane - i_nearPlane));
	return output;
}

Game::Game()
{
	this->m_graphics = std::make_unique<Graphics>();
	this->m_window = std::make_unique<Window>();
	this->m_entitySystem = std::make_unique<EntitySystem>();
	this->m_inputSystem = std::make_unique<InputSystem>();

	this->m_window->makeCurrentContext();

	this->m_graphics->setViewport(this->m_window->getSize());
}

Game::~Game()
{
}

void Game::onCreate()
{
	this->m_inputSystem->addListener(this);

	glm::vec3 cubeVertices[] =
	{
		{ -0.5f, -0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },

		{  0.5f, -0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },
	};

	UINT cubeIndices[] =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	glm::vec2 texcoordsList[] =
	{
		{ 0, 0 },
		{ 0, 1 },
		{ 1, 0 },
		{ 1, 1 }
	};

	Vertex verticesList[] =
	{
		{ cubeVertices[0], texcoordsList[1] },
		{ cubeVertices[1], texcoordsList[0] },
		{ cubeVertices[2], texcoordsList[2] },
		{ cubeVertices[3], texcoordsList[3] },

		{ cubeVertices[4], texcoordsList[1] },
		{ cubeVertices[5], texcoordsList[0] },
		{ cubeVertices[6], texcoordsList[2] },
		{ cubeVertices[7], texcoordsList[3] },

		{ cubeVertices[1], texcoordsList[1] },
		{ cubeVertices[6], texcoordsList[0] },
		{ cubeVertices[5], texcoordsList[2] },
		{ cubeVertices[2], texcoordsList[3] },

		{ cubeVertices[7], texcoordsList[1] },
		{ cubeVertices[0], texcoordsList[0] },
		{ cubeVertices[3], texcoordsList[2] },
		{ cubeVertices[4], texcoordsList[3] },

		{ cubeVertices[3], texcoordsList[1] },
		{ cubeVertices[2], texcoordsList[0] },
		{ cubeVertices[5], texcoordsList[2] },
		{ cubeVertices[4], texcoordsList[3] },

		{ cubeVertices[7], texcoordsList[1] },
		{ cubeVertices[6], texcoordsList[0] },
		{ cubeVertices[1], texcoordsList[2] },
		{ cubeVertices[0], texcoordsList[3] }
	};

	VertexAttribute attribsList[] =
	{
		sizeof(glm::vec3) / sizeof(GLfloat), // Position
		sizeof(glm::vec2) / sizeof(GLfloat)  // Color
	};

	this->m_vao = this->m_graphics->createVAO({ (void*)verticesList, sizeof(Vertex), sizeof(verticesList) / sizeof(Vertex), attribsList, sizeof(attribsList) / sizeof(VertexAttribute) }, { (void*)cubeIndices, sizeof(cubeIndices) });
	this->m_uniform = this->m_graphics->createUniformBuffer({ sizeof(UniformData) });
	this->m_shader = this->m_graphics->createShaderProgram({ L"../../../resources/shaders/vertex.vert", L"../../../resources/shaders/fragment.frag" });
	this->m_shader->setUniformBufferSlot("UniformData", 0);
}

void Game::onUpdateInternal()
{
	this->m_inputSystem->update();

	auto currentTime = std::chrono::system_clock::now();
	auto elapsedTime = std::chrono::duration<double>();

	if (this->m_previousTime.time_since_epoch().count())
		elapsedTime = currentTime - this->m_previousTime;
	this->m_previousTime = currentTime;

	float deltaTime = static_cast<float>(elapsedTime.count());
	this->m_deltaTime = deltaTime;

	this->onUpdate(deltaTime);
	this->m_entitySystem->update(deltaTime);

	this->m_scale += 3.14159f * deltaTime;
	float currentScale = abs(sin(this->m_scale));

	glm::mat4x4 world = glm::identity<glm::mat4x4>();
	glm::mat4x4 temp;
	glm::mat4x4 projection = glm::identity<glm::mat4x4>();
	
	temp = glm::identity<glm::mat4x4>();
	temp = glm::rotate(temp, (float)(this->m_cubeRotationX), MATRIX_ROTATION_X_AXIS);
	
	world *= temp;

	temp = glm::identity<glm::mat4x4>();
	temp = glm::rotate(temp, (float)(this->m_cubeRotationY), MATRIX_ROTATION_Y_AXIS);
	
	world *= temp;
	
	// temp = glm::identity<glm::mat4x4>();
	// temp = glm::identity<glm::mat4x4>();
	world = glm::translate(world, { 0, 0, -1 });

	// world *= temp;

	// world = glm::inverse(world);

	Rect<UINT> displaySize = this->m_window->getSize();
	// The glm::orthoLH function was setting the cube at the top-left of the window.
	// I created a new one so it's set to the center.
	projection = orthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.f);
	// projection = glm::perspectiveFovLH(glm::radians(90.0f), (float)displaySize.width, (float)displaySize.height, 0.01f, 100.f);

	UniformData data = { world, projection };
	this->m_uniform->setData(&data);

	this->m_graphics->clear(0.1, 0.1f, 0.4f, 1.0f);

	this->m_graphics->setFaceCulling(CullType::Back);
	this->m_graphics->setWindingOrder(WindingOrder::CW);
	this->m_graphics->setVAO(this->m_vao);
	this->m_graphics->setUniformBuffer(this->m_uniform, 0);
	this->m_graphics->setShaderProgram(this->m_shader);
	this->m_graphics->drawIndexedTriangles(TriangleType::TriangleList, 36);

	this->m_window->present(false);
}

void Game::onKeyPressed(int i_key)
{
	if (i_key == VK_LEFT)
	{
		this->m_cubeRotationY += 1 * this->m_deltaTime;
	}

	if (i_key == VK_RIGHT)
	{
		this->m_cubeRotationY -= 1 * this->m_deltaTime;
	}

	if (i_key == VK_UP)
	{
		this->m_cubeRotationX += 1 * this->m_deltaTime;
	}

	if (i_key == VK_DOWN)
	{
		this->m_cubeRotationX -= 1 * this->m_deltaTime;
	}
}

void Game::onKeyReleased(int i_key)
{
}

void Game::onMouseMove(const glm::ivec2& i_position)
{
	this->m_cubeRotationX += i_position.y * this->m_deltaTime;
	this->m_cubeRotationY += i_position.x * this->m_deltaTime;
}

void Game::onMouseButtonPressed(const MouseButton& i_button, const glm::ivec2& i_position)
{
	if (i_button == MouseButton::Left)
		this->m_canRotate = true;
}

void Game::onMouseButtonReleased(const MouseButton& i_button, const glm::ivec2& i_position)
{
	if (i_button == MouseButton::Left)
		this->m_canRotate = false;
}

void Game::onQuit()
{
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
				if (MessageBox(this->m_window->getHWND(), L"Do you want to quit the application?", L"Lowbyte 3D - OpenGL", MB_ICONQUESTION | MB_YESNO) == IDYES)
				#endif // NDEBUG
				this->m_isRunning = false;
			}

			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		this->onUpdateInternal();
	}

	this->onQuit();
}

void Game::quit()
{
	this->m_isRunning = false;
}
