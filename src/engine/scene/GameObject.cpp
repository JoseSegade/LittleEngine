#include "GameObject.h"


LittleEngine::GameObject::GameObject(unsigned int id, const char* name) : id(id), name(name), transform(new Transform()), children(), components(), m_isVisible(true)
{
}

LittleEngine::GameObject::GameObject(unsigned int id, const char* name, Transform* t) :id(id), name(name), transform(t), children(), components(), m_isVisible(true)
{
}

LittleEngine::GameObject::~GameObject()
{
	for (Component* component : components)
	{
		delete component;
	}
	components.clear();
	for (GameObject* gameObject : children)
	{
		delete gameObject;
	}
	children.clear();
	delete transform;
	delete[] this;
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

void LittleEngine::GameObject::onRender(ProgramObject* program, ViewProj &viewProj)
{
	if (m_isVisible)
	{		
		for (Component* component : components)
		{
			IRenderizable* renderizable = dynamic_cast<IRenderizable*>(component);
			if (renderizable != nullptr)
			{
				renderizable->onRender(program, viewProj);
			}
		}
		for (GameObject* gameObject : children)
		{
			gameObject->onRender(program, viewProj);
		}
	}
}

void LittleEngine::GameObject::onCompute(ProgramObject* program)
{
	if (m_isVisible)
	{
		for (Component* component : components)
		{
			IComputable* computable = dynamic_cast<IComputable*>(component);
			if (computable != nullptr)
			{
				computable->onCompute(program);
			}
		}
		for (GameObject* gameObject : children)
		{
			gameObject->onCompute(program);
		}
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

void LittleEngine::GameObject::updateTransformationMatrix()
{
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

