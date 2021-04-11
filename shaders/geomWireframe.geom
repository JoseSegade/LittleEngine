#version 330

layout(triangles) in;
layout(line_strip, max_vertices = 4) out;

uniform mat4 modelViewProj;

out vec4 color;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = modelViewProj * gl_in[i].gl_Position;
		color = vec4(1.0, 1.0, 0.0, 1.0);
		EmitVertex();
	}

	EndPrimitive();
}