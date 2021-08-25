#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

using std::end;

class Component;
class Entity;

using ComponentID = std::size_t;
inline ComponentID getComponentID()
{
	static ComponentID lastId = 0;
	return lastId++;
}

template <typename T> ComponentID getComponentID() noexcept
{
	static ComponentID typeId = getComponentID();
	return typeId;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init(){}
	virtual void update(){}
	virtual void draw(){}
};

class Entity
{
public:
	void Update()
	{
		for (auto& c : components) c->update();
		for (auto& c : components) c->draw();
	}

	void Draw()
	{

	}

	bool isActive()
	{
		return active;
	}

	void destroy()
	{
		active = false;
	}

	template <typename T> bool hasComponent() const
	{
		return ComponentBitSet(getComponentID<T>)
	}

	template<typename T, typename... Targs>
	T& addComponent(Targs&&... margs)
	{
		T* c(new T(std::forward < Targs>(margs)...);
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeId<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;

	}

	template<typename T> T& getComponentID() const
	{
		auto ptr(componentArray[getComponentTypeId]);
		return *static_cast<T*>(ptr);
	}


private:	
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
public:
	void Update()
	{
		for (auto& e : entities)
		{
			e->Update();
		}
	}

	void Draw()
	{
		for (auto& e : entities)
		{
			e->Draw();
		}
	}

	void Refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity)
		{
				return !mEntity->isActive();
		}),

			end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

};
