#version 450 core

layout(vertices = 4) out;

in vec3 vNorm[];

uniform float divs;

out vec3 tcNorm[];

void main()
{
	if(gl_InvocationID == 0){
		gl_TessLevelInner[0] = divs;
		gl_TessLevelInner[1] = divs;

		gl_TessLevelOuter[0] = divs;
		gl_TessLevelOuter[1] = divs;
		gl_TessLevelOuter[2] = divs;
		gl_TessLevelOuter[3] = divs;
	}

	tcNorm[gl_InvocationID] = vNorm[gl_InvocationID];
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

}