#version 430 

layout (location = 0) in vec4 inPos;
layout (location = 1) in vec4 inVel;
layout (location = 2) in vec4 inCol;
layout (location = 3) in vec4 inLif;

uniform mat4 viewProj;

out vec4 vColor;

void main()
{
	vColor = inCol;
	gl_Position = viewProj * inPos;
}