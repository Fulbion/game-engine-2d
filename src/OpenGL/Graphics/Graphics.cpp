#include <stdexcept>

#include "OpenGL/Graphics/Graphics.hpp"
#include "OpenGL/Graphics/VertexArrayObject.hpp"
#include "OpenGL/Graphics/ShaderProgram.hpp"
#include "OpenGL/Graphics/UniformBuffer.hpp"

Graphics::Graphics()
{
	const wchar_t* CLASS_NAME = L"OpenGL Dummy Window";
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = CLASS_NAME;
	wc.style = CS_CLASSDC;

	ATOM classID = RegisterClassEx(&wc);

	HWND dummyWindow = CreateWindowEx(
		NULL,                           // Optional window styles
		MAKEINTATOM(classID),           // Window class
		L"OpenGL Dummy Window",         // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		NULL,       // Instance handle
		NULL        // Additional application data
	);

	HDC dummyDC = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;

	int pixelFormat = ChoosePixelFormat(dummyDC, &pfd);
	SetPixelFormat(dummyDC, pixelFormat, &pfd);

	HGLRC dummyGLRC = wglCreateContext(dummyDC);
	wglMakeCurrent(dummyDC, dummyGLRC);

	if (!gladLoadWGL(dummyDC)) LB_ERROR("Graphics: gladLoadWGL failed");
	if (!gladLoadGL()) LB_ERROR("Graphics: gladLoadGL failed");

	wglMakeCurrent(dummyDC, nullptr);
	wglDeleteContext(dummyGLRC);
	ReleaseDC(dummyWindow, dummyDC);
	DestroyWindow(dummyWindow);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}

Graphics::~Graphics()
{
}

VertexArrayObjectPtr Graphics::createVAO(const VertexBufferDesc& i_vbDesc)
{
	return std::make_shared<VertexArrayObject>(i_vbDesc);
}

VertexArrayObjectPtr Graphics::createVAO(const VertexBufferDesc& i_vbDesc, const IndexBufferDesc& i_ibDesc)
{
	return std::make_shared<VertexArrayObject>(i_vbDesc, i_ibDesc);
}

ShaderProgramPtr Graphics::createShaderProgram(const ShaderProgramDesc& i_desc)
{
	return std::make_shared<ShaderProgram>(i_desc);
}

UniformBufferPtr Graphics::createUniformBuffer(const UniformBufferDesc& i_desc)
{
	return std::make_shared<UniformBuffer>(i_desc);
}

void Graphics::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::setFaceCulling(const CullType& i_cullType)
{
	GLenum cullType = 0;

	switch (i_cullType)
	{
	case CullType::Back:
		cullType = GL_BACK;

	case CullType::Front:
		cullType = GL_FRONT;

	case CullType::Both:
		cullType = GL_FRONT_AND_BACK;

	default:
		cullType = GL_BACK;
	}

	glEnable(GL_CULL_FACE);
	glCullFace(cullType);
}

void Graphics::setWindingOrder(const WindingOrder& i_order)
{
	GLenum order = 0;

	switch (i_order)
	{
	case WindingOrder::CW:
		order = GL_CW;

	case WindingOrder::CCW:
		order = GL_CCW;

	default:
		order = GL_CW;
	}

	glFrontFace(order);
}

void Graphics::setViewport(const Rect<UINT>& i_size)
{
	glViewport(i_size.left, i_size.top, i_size.width, i_size.height);
}

void Graphics::setVAO(const VertexArrayObjectPtr& i_vao)
{
	glBindVertexArray(i_vao->getID());
}

void Graphics::setUniformBuffer(const UniformBufferPtr& i_buffer, UINT i_slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, i_slot, i_buffer->getID());
}

void Graphics::setShaderProgram(const ShaderProgramPtr& i_shaderProgram)
{
	glUseProgram(i_shaderProgram->getID());
}

void Graphics::drawTriangles(const TriangleType& i_triangleType, GLsizei i_vertexCount, GLuint i_offset)
{
	switch (i_triangleType)
	{
	case TriangleType::TriangleList:
		glDrawArrays(GL_TRIANGLES, i_offset, i_vertexCount);
		break;

	case TriangleType::TriangleStrip:
		glDrawArrays(GL_TRIANGLE_STRIP, i_offset, i_vertexCount);
		break;

	default:
		glDrawArrays(GL_TRIANGLES, i_offset, i_vertexCount);
		break;
	}
}

void Graphics::drawIndexedTriangles(const TriangleType& i_triangleType, GLsizei i_indexCount)
{
	switch (i_triangleType)
	{
	case TriangleType::TriangleList:
		glDrawElements(GL_TRIANGLES, i_indexCount, GL_UNSIGNED_INT, nullptr);
		break;

	case TriangleType::TriangleStrip:
		glDrawElements(GL_TRIANGLE_STRIP, i_indexCount, GL_UNSIGNED_INT, nullptr);
		break;

	default:
		glDrawElements(GL_TRIANGLES, i_indexCount, GL_UNSIGNED_INT, nullptr);
		break;
	}
}
