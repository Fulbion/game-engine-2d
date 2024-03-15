#pragma once

#include "OpenGL/Common.hpp"

class UniformBuffer
{
public:
	UniformBuffer(const UniformBufferDesc& i_desc);
	~UniformBuffer();

	void setData(void* i_data);

	inline UINT getID() const { return this->m_id; }

private:
	UINT m_id = 0;
	size_t m_size = 0;
};
