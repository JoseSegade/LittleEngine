#pragma once
#ifndef ICOMPUTABLE_H_
#define ICOMPUTABLE_H_

#define LITTLE_ENGINE_WORK_GROUP_SIZE 512

#include "engine/scene/GameObject.h"
#include "engine/graphics/ProgramObject.h"

namespace LittleEngine
{
	class GameObject;
	class IComputable : virtual public Component
	{
	public:
		virtual void onCompute(ProgramObject *program) = 0;
	};
}

#endif // !ICOMPUTABLE_H_

