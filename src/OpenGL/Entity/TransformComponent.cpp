#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "OpenGL/Entity/TransformComponent.hpp"

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::updateWorldMatrix()
{
	this->m_world = glm::identity<glm::mat4x4>();
	
	glm::mat4x4 temp;
	
	// Scale
	temp = glm::identity<glm::mat4x4>();
	temp = glm::scale(temp, this->m_scale);
	this->m_world *= temp;

	// Rotation
	temp = glm::identity<glm::mat4x4>();
	temp = glm::rotate(temp, (float)(this->m_rotation.x), MATRIX_ROTATION_X_AXIS);
	this->m_world *= temp;
	temp = glm::identity<glm::mat4x4>();
	temp = glm::rotate(temp, (float)(this->m_rotation.y), MATRIX_ROTATION_Y_AXIS);
	this->m_world *= temp;
	temp = glm::identity<glm::mat4x4>();
	temp = glm::rotate(temp, (float)(this->m_rotation.z), MATRIX_ROTATION_Z_AXIS);
	this->m_world *= temp;

	// Translation
	temp = glm::identity<glm::mat4x4>();
	temp = glm::translate(temp, this->m_position);
	this->m_world *= temp;
}
