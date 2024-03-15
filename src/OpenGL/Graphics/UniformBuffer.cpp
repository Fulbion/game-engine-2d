#include "OpenGL/Graphics/UniformBuffer.hpp"
#include <glad/glad.h>

UniformBuffer::UniformBuffer(const UniformBufferDesc& i_desc)
{
	glGenBuffers(1, &this->m_id);
	glBindBuffer(GL_UNIFORM_BUFFER, this->m_id);
	glBufferData(GL_UNIFORM_BUFFER, i_desc.size, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM, 0);
	this->m_size = i_desc.size;
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &this->m_id);
}

void UniformBuffer::setData(void* i_data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->m_id);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, this->m_size, i_data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
