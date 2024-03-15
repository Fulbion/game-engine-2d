#pragma once

#include "OpenGL/Common.hpp"

class Component
{
public:
	Component();
	virtual ~Component();

	void release();

private:
	size_t m_id = 0;
	Entity* m_entity = nullptr;

	friend class Entity;
};
