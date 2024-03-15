#include "OpenGL/Entity/EntitySystem.hpp"
#include "OpenGL/Entity/Entity.hpp"

EntitySystem::EntitySystem()
{
}

EntitySystem::~EntitySystem()
{
}

bool EntitySystem::createEntityInternal(Entity* i_entity, size_t i_id)
{
	std::unique_ptr<Entity> ptr = std::unique_ptr<Entity>(i_entity);
	this->m_entities[i_id].emplace(i_entity, std::move(ptr));

	i_entity->m_id = i_id;
	i_entity->m_entitySystem = this;

	i_entity->onCreate();

	return true;
}

void EntitySystem::removeEntity(Entity* i_entity)
{
	this->m_entitiesToDestroy.emplace(i_entity);
}

void EntitySystem::update(float i_deltaTime)
{
	for (auto& e : m_entitiesToDestroy)
	{
		this->m_entities[e->m_id].erase(e);
	}

	this->m_entitiesToDestroy.clear();

	for (auto&& [id, entities] : this->m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			entity->onUpdate(i_deltaTime);
		}
	}
}
