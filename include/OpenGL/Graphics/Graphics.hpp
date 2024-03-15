#pragma once

#include <glad/glad_wgl.h>
#include <glad/glad.h>

#include "OpenGL/Common.hpp"
#include "OpenGL/Math/Rect.hpp"

class Graphics
{
public:
	Graphics();
	~Graphics();

	VertexArrayObjectPtr createVAO(const VertexBufferDesc& i_vbDesc);
	VertexArrayObjectPtr createVAO(const VertexBufferDesc& i_vbDesc, const IndexBufferDesc& i_ibDesc);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& i_desc);
	UniformBufferPtr createUniformBuffer(const UniformBufferDesc& i_desc);

	void clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);;
	void setFaceCulling(const CullType& i_cullType);
	void setWindingOrder(const WindingOrder& i_order);
	void setViewport(const Rect<UINT>& i_size);
	void setVAO(const VertexArrayObjectPtr& i_vao);
	void setUniformBuffer(const UniformBufferPtr& i_buffer, UINT i_slot);
	void setShaderProgram(const ShaderProgramPtr& i_shaderProgram);
	void drawTriangles(const TriangleType& i_triangleType, GLsizei i_vertexCount, GLuint i_offset);
	void drawIndexedTriangles(const TriangleType& i_triangleType, GLsizei i_indexCount);

private:

};
