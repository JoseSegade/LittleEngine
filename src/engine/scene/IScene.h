#pragma once
#ifndef ISCENE_H_
#define ISCENE_H_

namespace LittleEngine 
{
	struct IScene
	{
		virtual void resize	      (int widht, int height) = 0;
		virtual void load	      ()                      = 0;
		virtual void render	      ()                      = 0;
		virtual void update	      (double deltaTime)      = 0;
		virtual void updateCamera (double deltaTime)      = 0;
	};
}

#endif // !ISCENE_H_

