#include "OpenGL/Entity/Entity.hpp"
#include "OpenGL/Entity/EntitySystem.hpp"
#include "OpenGL/Entity/Component.hpp"
#include "OpenGL/Entity/TransformComponent.hpp"

Entity::Entity()
{
	this->m_transformComponent = this->createComponent<TransformComponent>();
}

Entity::~Entity()
{
}

void Entity::release()
{
	this->m_entitySystem->removeEntity(this);
}

bool Entity::createComponentInternal(Component* i_component, size_t i_id)
{
	std::unique_ptr<Component> ptr = std::unique_ptr<Component>(i_component);
	this->m_components.emplace(i_id, std::move(ptr));

	i_component->m_id = i_id;
	i_component->m_entity = this;

	return true;
}

void Entity::removeComponent(size_t i_id)
{
	this->m_components.erase(i_id);
}
