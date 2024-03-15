#pragma once

#include "OpenGL/Common.hpp"

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& i_vbDesc);
	VertexArrayObject(const VertexBufferDesc& i_vbDesc, const IndexBufferDesc& i_ibDesc);
	~VertexArrayObject();

	inline UINT getID() const { return this->m_vaoID; }
	inline size_t getVertexBufferSize() const { return this->m_vbDesc.listSize; }
	inline size_t getVertexSize() const { return this->m_vbDesc.vertexSize; }

private:
	UINT m_vaoID = 0;
	UINT m_vboID = 0;
	UINT m_elementBufferID = 0;

	VertexBufferDesc m_vbDesc;
};
