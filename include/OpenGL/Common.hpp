#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <Windows.h>
#include <glm/glm.hpp>

#define MATRIX_ROTATION_X_AXIS glm::vec3(1, 0, 0)
#define MATRIX_ROTATION_Y_AXIS glm::vec3(0, 1, 0)
#define MATRIX_ROTATION_Z_AXIS glm::vec3(0, 0, 1)

class GraphicsEngine;
class VertexArrayObject;
class ShaderProgram;
class UniformBuffer;
class Texture;

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
typedef std::shared_ptr<Texture> TexturePtr;

struct VertexAttribute
{
	UINT numElements = 0;
};

struct VertexBufferDesc
{
	void* verticesList = nullptr;
	size_t vertexSize = 0;
	size_t listSize = 0;

	VertexAttribute* attributesList = nullptr;
	size_t attributesListSize = 0;
};

struct IndexBufferDesc
{
	void* indicesList = nullptr;
	size_t listSize = 0;
};

struct UniformBufferDesc
{
	size_t size = 0;
};

struct Image
{
	int width, height, colorChannels;
	uint8_t* bytes;
};

enum class ShaderType
{
	VertexShader,
	FragmentShader
};

enum class TriangleType
{
	TriangleList,
	TriangleStrip
};

enum class CullType
{
	Back,
	Front,
	Both
};

enum class WindingOrder
{
	CW,
	CCW
};

enum class MouseButton
{
	Left,
	Middle,
	Right
};

#define GE2D_ERROR(...)\
{\
	std::stringstream sstr;\
	sstr << "Error: " << __VA_ARGS__ << std::endl;\
	throw std::runtime_error(sstr.str());\
}

#define GE2D_WARNING(...) std::wclog << "Warning: " << __VA_ARGS__ << std::endl;

#define GE2D_INFO(...) std::wclog << "Info: " << __VA_ARGS__ << std::endl;