#include "OpenGL/Graphics/ShaderProgram.hpp"
#include <glad/glad.h>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& i_desc)
{
	this->m_programID = glCreateProgram();
	this->attach(i_desc.vertexShaderPath, ShaderType::VertexShader);;
	this->attach(i_desc.fragmentShaderPath, ShaderType::FragmentShader);;
	this->link();
}

ShaderProgram::~ShaderProgram()
{
	for (UINT i = 0; i < 2; i++)
	{
		glDetachShader(this->m_programID, this->m_attachedShaders[i]);
		glDeleteShader(this->m_attachedShaders[i]);
	}

	glDeleteProgram(this->m_programID);
}

void ShaderProgram::setUniformBufferSlot(const char* i_name, UINT i_slot)
{
	GLuint index = glGetUniformBlockIndex(this->m_programID, i_name);
	glUniformBlockBinding(this->m_programID, index, i_slot);
}

void ShaderProgram::attach(const wchar_t* i_shaderFilePath, const ShaderType& i_type)
{
	std::string shaderCode;

	std::ifstream shaderStream(i_shaderFilePath);

	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}

	else
	{
		LB_WARNING("ShaderProgram: " << i_shaderFilePath << " not found");
		return;
	}

	GLuint shaderID = 0;

	switch (i_type)
	{
	case ShaderType::VertexShader:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;

	case ShaderType::FragmentShader:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;

	default:
		break;
	}

	const char* sourcePointer = shaderCode.c_str();

	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	{
		GLint logLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)
		{
			std::vector<char> errorMessage(logLength + 1);
			glGetShaderInfoLog(shaderID, logLength, NULL, &errorMessage[0]);
			LB_WARNING("ShaderProgram: " << i_shaderFilePath << " compiled with errors: " << std::endl << &errorMessage[0]);
			return;
		}
	}

	glAttachShader(this->m_programID, shaderID);
	this->m_attachedShaders[static_cast<int>(i_type)] = shaderID;
	
	LB_INFO("ShaderProgram: " << i_shaderFilePath << " compiled successfully");
}

void ShaderProgram::link()
{
	glLinkProgram(this->m_programID);

	{
		GLint logLength = 0;
		glGetShaderiv(this->m_programID, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)
		{
			std::vector<char> errorMessage(logLength + 1);
			glGetShaderInfoLog(this->m_programID, logLength, NULL, &errorMessage[0]);
			LB_WARNING("ShaderProgram: " << &errorMessage[0]);
			return;
		}
	}
}
