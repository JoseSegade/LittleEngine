#version 330

layout (location  = 0) in vec3 inPos;
layout (location  = 3) in vec3 inNormal;

uniform mat4 modelViewProj;
uniform mat4 normal;

out vec3 norm;

void main()
{
	norm = normalize(vec3(normal * vec4(inNormal, 0.0)));
	gl_Position =  modelViewProj * vec4 (inPos,1.0);
}