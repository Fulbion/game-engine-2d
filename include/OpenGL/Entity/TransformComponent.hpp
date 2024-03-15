#pragma once

#include <glm/glm.hpp>

#include "OpenGL/Common.hpp"
#include "OpenGL/Entity/Component.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent();
	virtual ~TransformComponent();

	inline glm::vec3 getPosition() const { return this->m_position; }
	inline glm::vec3 getRotation() const { return this->m_rotation; }
	inline glm::vec3 getScale() const { return this->m_scale; }
	inline glm::mat4x4 getWorldMatrix() const { return this->m_world; }

	inline void setPosition(const glm::vec3& i_position) { this->m_position = i_position; this->updateWorldMatrix(); }
	inline void setRotation(const glm::vec3& i_rotation) { this->m_rotation = i_rotation; this->updateWorldMatrix(); }
	inline void setScale(const glm::vec3& i_scale) { this->m_scale = i_scale; this->updateWorldMatrix(); }

protected:
	void updateWorldMatrix();

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale = { 1, 1, 1 };
	glm::mat4x4 m_world;

private:

};
