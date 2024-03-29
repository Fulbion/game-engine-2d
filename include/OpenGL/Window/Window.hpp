#pragma once

#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	inline HWND getHWND() const { return this->m_hwnd; }

	inline RECT getSize() const
	{
		RECT rc = {};
		GetClientRect(this->m_hwnd, &rc);
		return { 0, 0, rc.right - rc.left, rc.bottom - rc.top };
	}

	void makeCurrentContext();
	void present(bool i_vSync);

	virtual void onFocus();
	virtual void onKillFocus();

	inline bool hasFocus() const
	{
		return this->m_hasFocus;
	}

private:
	// Window handle
	HWND m_hwnd = nullptr;
	// Context handle
	HGLRC m_hglrc = nullptr;

	bool m_hasFocus = true;
};
