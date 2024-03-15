#pragma once

#include <memory>
#include <chrono>

#include <glm/glm.hpp>

#include "OpenGL/Common.hpp"
#include "OpenGL/Input/InputListener.hpp"

class EntitySystem;
class Graphics;
class Window;
class Game : public InputListener
{
public:
	Game();
	~Game();

	void run();
	void quit();

	inline EntitySystem* getEntitySystem() const
	{
		return this->m_entitySystem.get();
	}

protected:
	virtual void onCreate();
	virtual void onUpdate(float i_deltaTime) {}
	virtual void onQuit();

private:
	void onUpdateInternal();

	virtual void onKeyPressed(int i_key) override;
	virtual void onKeyReleased(int i_key) override;

	bool m_isRunning = true;

	std::unique_ptr<Graphics> m_graphics;
	std::unique_ptr<Window> m_window;
	std::unique_ptr<EntitySystem> m_entitySystem;
	std::unique_ptr<InputSystem> m_inputSystem;

	VertexArrayObjectPtr m_vao;
	ShaderProgramPtr m_shader;
	UniformBufferPtr m_uniform;

	std::chrono::system_clock::time_point m_previousTime;

	float m_deltaTime = 0.0f;
	float m_scale = 0.0f;
	float m_cubeRotationX = 0.0f;
	float m_cubeRotationY = 0.0f;
	bool m_canRotate = false;

	void onMouseMove(const glm::ivec2& i_position) override;
	void onMouseButtonPressed(const MouseButton& i_button, const glm::ivec2& i_position) override;
	void onMouseButtonReleased(const MouseButton& i_button, const glm::ivec2& i_position) override;
};
