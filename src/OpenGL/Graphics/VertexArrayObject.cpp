#include "OpenGL/Graphics/VertexArrayObject.hpp"
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& i_vbDesc)
{
	if (!i_vbDesc.listSize) GE2D_ERROR("VertexArrayObject: listSize is NULL");
	if (!i_vbDesc.vertexSize) GE2D_ERROR("VertexArrayObject: vertexSize is NULL");
	if (!i_vbDesc.verticesList) GE2D_ERROR("VertexArrayObject: verticesList is NULL");

	glGenVertexArrays(1, &this->m_vaoID);
	glBindVertexArray(this->m_vaoID);
	
	glGenBuffers(1, &this->m_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboID);
	glBufferData(GL_ARRAY_BUFFER, i_vbDesc.vertexSize * i_vbDesc.listSize, i_vbDesc.verticesList, GL_STATIC_DRAW);

	for (UINT i = 0; i < i_vbDesc.attributesListSize; i++)
	{
		glVertexAttribPointer(i, i_vbDesc.attributesList[i].numElements, GL_FLOAT, GL_FALSE, i_vbDesc.vertexSize, (void*)((i == 0) ? 0 : i_vbDesc.attributesList[i - 1].numElements * sizeof(GLfloat)));
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	this->m_vbDesc = i_vbDesc;
}

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& i_vbDesc, const IndexBufferDesc& i_ibDesc) :
	VertexArrayObject(i_vbDesc)
{
	if (!i_ibDesc.listSize) GE2D_ERROR("VertexArrayObject: listSize is NULL");
	if (!i_ibDesc.indicesList) GE2D_ERROR("VertexArrayObject: indicesList is NULL");

	glBindVertexArray(this->m_vaoID);

	glGenBuffers(1, &this->m_eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_ibDesc.listSize, i_ibDesc.indicesList, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &this->m_vboID);
	glDeleteBuffers(1, &this->m_eboID);
	glDeleteVertexArrays(1, &this->m_vaoID);
}