#pragma once

/// <summary>
/// I implement my own Rect struct, becuase the RECT type provided by the Windows API is less intuitive.
/// On the other hand, this one uses the left, top, width and height attributes.
/// </summary>
/// <typeparam name="T">The type of all the attributes (`float` if nothing is provided)</typeparam>
template<typename T = float>
struct Rect
{
	T left, top, width, height;

	Rect() {}
	Rect(T i_left, T i_top, T i_width, T i_height) :
		left(i_left), top(i_top), width(i_width), height(i_height)
	{
	}
};
