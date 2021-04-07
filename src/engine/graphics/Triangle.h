#pragma once
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

namespace LittleEngine
{
	struct Triangle
	{
		int a;
		int b;
		int c;

		Triangle() : a(-1), b(-1), c(-1) {}

		void addVertexIndex(int vertexIndex) 
		{
			if (a < 0)
			{
				a = vertexIndex;
			}
			else if (b < 0)
			{
				b = vertexIndex;
			}
			else if (c < 0)
			{
				c = vertexIndex;
			}
		}
	};
}

#endif // !TRIANGLE_H_

