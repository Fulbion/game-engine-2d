#pragma once

#include "OpenGL/Common.hpp"

class ShaderProgram;
class Texture
{
public:
	Texture(const char* i_imagePath);
	~Texture();

	inline UINT getID() const { return this->m_id; }

private:
	UINT m_id = 0;
};