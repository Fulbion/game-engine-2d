#pragma once

#include "OpenGL/Common.hpp"

class ShaderProgram
{
public:
	ShaderProgram(const wchar_t* i_vertexShaderPath, const wchar_t* i_fragmentShaderPath);
	~ShaderProgram();

	inline UINT getID() const { return this->m_programID; }

	void setUniformBufferSlot(const char* i_name, UINT i_slot);

private:
	void attach(const wchar_t* i_shaderFilePath, const ShaderType& i_type);
	void link();

	UINT m_programID;
	std::array<UINT, 2> m_attachedShaders = {};
};
