#version 330

layout(triangles) in;
layout(line_strip, max_vertices = 4) out;

struct vertex
{
	vec3 pos;
	vec3 color;
	vec2 texCoord;
	vec3 norm;
};

in  vertex eVertex[];
out vertex gVertex;

uniform mat4 modelViewProj;
uniform mat4 normal;

void main()
{
	for(int i = 0; i < 4; ++i)
	{
		gVertex.pos = (modelViewProj * vec4(eVertex[i % 3].pos, 1.0)).rgb;
		gVertex.color = eVertex[i % 3].color;
		gVertex.texCoord = eVertex[i % 3].texCoord;
		gVertex.norm = (normal * vec4(eVertex[i % 3].norm, 0.0)).rgb;
		gl_Position = modelViewProj * vec4(eVertex[i % 3].pos, 1.0);
		EmitVertex();
	}

	EndPrimitive();
}