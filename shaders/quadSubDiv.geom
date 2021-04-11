#version 330

layout(triangles) in;
layout(line_strip, max_vertices = 4) out;

uniform mat4 modelViewProj;
uniform float zOffset;
uniform vec3 wireColor;

in vec3 teNorm[];

out vec4 color;

void main()
{
	for(int i = 0; i < 4; ++i)
	{
		gl_Position = modelViewProj * (gl_in[i % 3].gl_Position + vec4(teNorm[i % 3] * zOffset, 0.0));
		color = vec4(wireColor, 1.0);
		EmitVertex();
	}

	EndPrimitive();
}