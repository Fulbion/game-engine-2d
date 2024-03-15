#include "OpenGL/Entity/Component.hpp"
#include "OpenGL/Entity/Entity.hpp"

Component::Component()
{
}

Component::~Component()
{
}

void Component::release()
{
	this->m_entity->removeComponent(this->m_id);
}
