#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

namespace LittleEngine 
{
	class GameObject;
	class Component 
	{
	public:
		GameObject* gameObject;

		//Component() : gameObject(nullptr) {}
		//virtual ~Component() = 0;

		virtual void onStart	()					= 0;
		virtual void onUpdate	(double deltaTime)	= 0;

	};
}
#endif