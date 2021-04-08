#pragma once

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <vector>
#include <string>
class Component;
#include "engine/components/Component.h"
#include "engine/components/Transform.h"
#include "engine/graphics/Renderer.h"
#include "engine/components/MeshRenderer.h"

namespace LittleEngine
{
	class GameObject {
	public:
		unsigned int	id;
		const char*		name;

		GameObject(unsigned int id, const char* name);
		GameObject(unsigned int id, const char* name, Transform* t);
		~GameObject();

		
		virtual void onStart			();
		virtual void onUpdate			(double deltaTime);
		virtual void onRender			(ProgramObject* program, ViewProj &viewProj);

		void addChild					(GameObject* child);
		void addComponent				(Component* component);
		void updateTransformationMatrix	();

		inline void turnVisibilityOn	() { m_isVisible = true; }
		inline void turnVisibilityOff	() { m_isVisible = false; }
		inline bool isVisible			() const { return m_isVisible; }

		GameObject* getChildById		(unsigned int id);
		GameObject* getChildByName		(const char* name);

		template<typename T>
		T*	getComponent				()				  const;

		Transform*					transform;
	private:
		std::vector<Component*>		components;
		std::vector<GameObject*>	children;
		bool						m_isVisible;
	};

	template<typename T>
	inline T* GameObject::getComponent() const
	{
		for (auto component : components)
		{
			if (typeid(*component) == typeid(T))
			{
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}

};

#endif // !GAMEOBJECT_H_

