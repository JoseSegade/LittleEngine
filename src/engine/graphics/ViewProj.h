#pragma once
#ifndef VIEWPROJ_H_
#define VIEWPROJ_H_

#include <glm/glm.hpp>

namespace LittleEngine
{
	struct ViewProj 
	{
		glm::mat4 view;
		glm::mat4 proj;
		glm::mat4 viewProj;

		ViewProj(glm::mat4 view, glm::mat4 proj) : view(view), proj(proj), viewProj(proj* view) {};
		~ViewProj() {};
	};
}

#endif // !VIEWPROJ_H_

