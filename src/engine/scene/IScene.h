#pragma once
#ifndef ISCENE_H_
#define ISCENE_H_

namespace LittleEngine 
{
	struct IScene
	{
		virtual ~IScene() = 0;
		virtual void load() = 0;
		virtual void render() = 0;
		virtual void update(double deltaTime) = 0;
	};
}

#endif // !ISCENE_H_

