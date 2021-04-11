#pragma once
#ifndef QUAD_H_
#define QUAD_H_

namespace LittleEngine
{
	struct Quad
	{
		int a;
		int b;
		int c;
		int d;

		Quad() : a(-1), b(-1), c(-1), d(-1) {}

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
			else if (d < 0)
			{
				d = vertexIndex;
			}
		}
	};
}

#endif // !QUAD_H_