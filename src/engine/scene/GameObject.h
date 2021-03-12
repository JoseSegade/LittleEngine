#pragma once

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <vector>
#include <string>
class Component;
#include "engine/components/Component.h"
#include "engine/components/Transform.h"

namespace LittleEngine
{
	class GameObject {
	public:
		int id;
		std::string name;

		GameObject();
		~GameObject();

	private:
		std::vector<Component> components;
		std::vector<GameObject> children;
		Transform* transform;
	};

};

#endif // !GAMEOBJECT_H_

