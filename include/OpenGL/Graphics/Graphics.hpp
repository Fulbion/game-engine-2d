#pragma once

#include <glad/glad_wgl.h>
#include <glad/glad.h>

#include "OpenGL/Common.hpp"

class Graphics
{
public:
	Graphics();
	~Graphics();

	VertexArrayObjectPtr createVAO(const VertexBufferDesc& i_vbDesc);
	VertexArrayObjectPtr createVAO(const VertexBufferDesc& i_vbDesc, const IndexBufferDesc& i_ibDesc);
	ShaderProgramPtr createShaderProgram(const wchar_t* i_vertexShaderPath, const wchar_t* i_fragmentShaderPath);
	UniformBufferPtr createUniformBuffer(const UniformBufferDesc& i_desc);
	TexturePtr createTexture(const char* i_imagePath);

	void clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
	void setFaceCulling(const CullType& i_cullType);
	void setWindingOrder(const WindingOrder& i_order);
	void setViewport(const RECT& i_size);
	void setVAO(const VertexArrayObjectPtr& i_vao);
	void setUniformBuffer(const UniformBufferPtr& i_buffer, UINT i_slot);
	void setShaderProgram(const ShaderProgramPtr& i_shaderProgram);
	void setTexture(const TexturePtr& i_texture);
	void drawTriangles(const TriangleType& i_triangleType, GLsizei i_vertexCount, GLuint i_offset);
	void drawIndexedTriangles(const TriangleType& i_triangleType, GLsizei i_indexCount);

private:

};
