#version 330 core

layout (location  = 0) in vec3 inPos;	
layout (location  = 1) in vec3 inColor;
layout (location  = 2) in vec2 inTexCoord;
layout (location  = 3) in vec3 inNormal;

uniform mat4 modelViewProj;

out struct vertex
{
	vec3 pos;
	vec3 color;
	vec2 texCoord;
	vec3 norm;
} vVertex;
	

void main()
{
	vVertex.pos		 = inPos;
	vVertex.color	 = inColor;
	vVertex.texCoord = inTexCoord;
	vVertex.norm	 = normalize(inNormal);
}
