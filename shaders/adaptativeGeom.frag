#version 330 core
layout (location  = 0) out vec4 outColor;
layout (location = 1)  out vec4 fragPos;

struct vertex
{
	vec3 pos;
	vec3 color;
	vec2 texCoord;
	vec3 norm;
};

in vertex gVertex;

void main()
{	
	outColor = vec4(gVertex.color, 1.0);
	fragPos = vec4(gVertex.pos,0.0);
}
