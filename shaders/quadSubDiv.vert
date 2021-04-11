#version 450 core

layout (location  = 0) in vec3 inPos;
layout (location  = 3) in vec3 inNormal;

out vec3 vNorm;

void main()
{
	vNorm = normalize(inNormal);
	gl_Position = vec4(inPos, 1.0);
}