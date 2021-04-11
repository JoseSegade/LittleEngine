#version 450 core

layout(vertices = 3) out;

struct vertex
{
	vec3 pos;
	vec3 color;
	vec2 texCoord;
	vec3 norm;
};

in  vertex vVertex[];
out vertex cVertex[];

uniform float divs;


void main()
{
	if(gl_InvocationID == 0){
		gl_TessLevelInner[0] = divs;
		gl_TessLevelOuter[0] = divs;
		gl_TessLevelOuter[1] = divs;
		gl_TessLevelOuter[2] = divs;
	}
	cVertex[gl_InvocationID].pos	     = vVertex[gl_InvocationID].pos;
	cVertex[gl_InvocationID].color	     = vVertex[gl_InvocationID].color;
	cVertex[gl_InvocationID].texCoord    = vVertex[gl_InvocationID].texCoord;
	cVertex[gl_InvocationID].norm        = vVertex[gl_InvocationID].norm;

}