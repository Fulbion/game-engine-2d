#pragma once

#include "OpenGL/Common.hpp"

class EntitySystem;
class Entity
{
public:
	Entity();
	virtual ~Entity();

	void release();

	inline EntitySystem* getEntitySystem() const
	{
		return this->m_entitySystem;
	}

	inline TransformComponent* getTransformComponent() const
	{
		return this->m_transformComponent;
	}

	template<typename T>
	T* createComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component class");
		
		auto c = this->getComponent<T>();

		if (!c)
		{
			size_t id = typeid(T).hash_code();
			c = new T();

			if (this->createComponentInternal(c, id))
				return c;
		}

		return nullptr;
	}

	template<typename T>
	T* getComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component class");
		size_t id = typeid(T).hash_code();
		return (T*)this->getComponentInternal(id);
	}

protected:
	virtual void onCreate() {}
	virtual void onUpdate(float i_deltaTime) {}

	size_t m_id;
	EntitySystem* m_entitySystem = nullptr;
	TransformComponent* m_transformComponent = nullptr;

private:
	std::unordered_map<size_t, std::unique_ptr<Component>> m_components;
	// std::unordered_set<Component*> m_componentsToDestroy;

	bool createComponentInternal(Component* i_component, size_t i_id);
	void removeComponent(size_t i_id);
	
	inline Component* getComponentInternal(size_t i_id) const
	{
		auto it = this->m_components.find(i_id);
		if (it == this->m_components.end())
			return nullptr;
		return it->second.get();
	}

	friend class EntitySystem;
	friend class Component;
};