#include "OpenGL/Window/Window.hpp"

#include <glad/glad_wgl.h>
#include <glad/glad.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		break;
	}

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}

	case WM_SETFOCUS:
	{
		Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		window->onFocus();
	}

	case WM_KILLFOCUS:
	{
		Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		window->onKillFocus();
	}

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return NULL;
}

Window::Window()
{
	const wchar_t* CLASS_NAME = L"LB_CLASS";
	WNDCLASSEX wc = {};
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpfnWndProc = &WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.lpszMenuName = L"";
	wc.style = CS_OWNDC;

	ATOM classID = RegisterClassEx(&wc);

	RECT rc = { 0, 0, 1280, 720 };
	AdjustWindowRect(&rc, WS_SYSMENU, false);

	this->m_hwnd = CreateWindowEx(
		NULL,                           // Optional window styles
		MAKEINTATOM(classID),           // Window class
		L"Game Engine 2D - OpenGL",     // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,

		NULL,       // Parent window    
		NULL,       // Menu
		NULL,       // Instance handle
		NULL        // Additional application data
	);

	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
	
	ShowWindow(this->m_hwnd, SW_SHOW);
	UpdateWindow(this->m_hwnd);

	HDC hDC = GetDC(this->m_hwnd);

	int pixelFormatAttributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int pixelFormat = 0;
	UINT numFormat = 0;
	wglChoosePixelFormatARB(hDC, pixelFormatAttributes, NULL, 1, &pixelFormat, &numFormat);

	PIXELFORMATDESCRIPTOR pfd = {};
	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);

	int attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	this->m_hglrc = wglCreateContextAttribsARB(hDC, 0, attributes);
}

Window::~Window()
{
	wglDeleteContext(this->m_hglrc);
	DestroyWindow(this->m_hwnd);
}

void Window::makeCurrentContext()
{
	wglMakeCurrent(GetDC(this->m_hwnd), this->m_hglrc);
}

void Window::present(bool i_vSync)
{
	wglSwapIntervalEXT(i_vSync);
	wglSwapLayerBuffers(GetDC(this->m_hwnd), WGL_SWAP_MAIN_PLANE);;
}

void Window::onFocus()
{
	this->m_hasFocus = true;
}

void Window::onKillFocus()
{
	this->m_hasFocus = false;
}
