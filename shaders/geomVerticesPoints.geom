#version 330

layout(triangles) in;
layout(points, max_vertices = 4) out;

uniform mat4 modelViewProj;
uniform float zOffset;
uniform vec3 wireColor;

in vec3 norm[];

out vec4 color;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = modelViewProj * (gl_in[i].gl_Position + vec4(norm[i] * zOffset, 0.0));
		color = vec4(wireColor, 1.0);
		EmitVertex();
	}

	EndPrimitive();
}