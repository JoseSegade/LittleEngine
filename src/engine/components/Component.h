#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
class GameObject;
#include "engine/scene/GameObject.h"

namespace LittleEngine 
{
	class Component 
	{
	public:
		GameObject* gameObject;

		Component();
		virtual ~Component();

		virtual void OnStart();
		virtual void OnUpdate(double deltaTime);

	};
}
#endif