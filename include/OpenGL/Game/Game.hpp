#pragma once

#include <memory>
#include <chrono>

#include <glm/glm.hpp>

#include "OpenGL/Common.hpp"

class EntitySystem;
class Graphics;
class Window;
class Game
{
public:
	Game();
	~Game();

	void run();
	void quit();

protected:
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

private:
	bool m_isRunning = true;

	std::unique_ptr<Graphics> m_graphics;
	std::unique_ptr<Window> m_window;

	VertexArrayObjectPtr m_vao;
	ShaderProgramPtr m_shader;
	UniformBufferPtr m_uniform;
	TexturePtr m_texture;

	std::chrono::system_clock::time_point m_previousTime;

	float m_deltaTime = 0.0f;
};
