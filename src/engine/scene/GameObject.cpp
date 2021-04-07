#include "GameObject.h"


LittleEngine::GameObject::GameObject(unsigned int id, const char* name) : id(id), name(name), transform(new Transform()), children(), components()
{
}

LittleEngine::GameObject::GameObject(unsigned int id, const char* name, Transform* t) :id(id), name(name), transform(t), children(), components()
{
}

LittleEngine::GameObject::~GameObject()
{
}

void LittleEngine::GameObject::onStart()
{
	for (GameObject* child : children) 
	{
		child->onStart();
	}

	for (Component* component : components)
	{
		component->onStart();
	}
}

void LittleEngine::GameObject::onUpdate(double deltaTime)
{

	for (GameObject* child : children)
	{
		child->onUpdate(deltaTime);
	}

	for (Component* component : components)
	{
		component->onUpdate(deltaTime);
	}
}

void LittleEngine::GameObject::addChild(GameObject* child)
{
	children.push_back(child);
}

void LittleEngine::GameObject::addComponent(Component* component)
{
	component->gameObject = this;
	components.push_back(component);
}

LittleEngine::GameObject* LittleEngine::GameObject::getChildById(unsigned int id)
{
	if (this->id == id)
	{
		return this;
	}

	for (GameObject* child : children)
	{
		GameObject* obj = child->getChildById(id);
		if (obj != nullptr)
		{
			return nullptr;
		}
	}
	return nullptr;
}

LittleEngine::GameObject* LittleEngine::GameObject::getChildByName(const char* name)
{
	if (this->name == name)
	{
		return this;
	}

	for (GameObject* child : children)
	{
		GameObject* obj = child->getChildByName(name);
		if (obj != nullptr)
		{
			return nullptr;
		}
	}
	return nullptr;
}

