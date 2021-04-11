#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 4) out;

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
uniform sampler2D colorTex;
uniform float intensity;

void main()
{
	for(int i = 0; i < 3; ++i)
	{
		gVertex.texCoord = eVertex[i].texCoord;
		gVertex.pos = (modelViewProj * (vec4(eVertex[i].pos, 1.0) + vec4(eVertex[i].norm * intensity * texture(colorTex, gVertex.texCoord).rgb, 0.0))).rgb;
		gVertex.color = eVertex[i].color;
		gVertex.norm = (normal * normalize(vec4(eVertex[i].norm * -1, 0.0))).rgb;
		gl_Position = (modelViewProj * (vec4(eVertex[i].pos, 1.0) + vec4(eVertex[i].norm * intensity * texture(colorTex, gVertex.texCoord).rgb, 0.0)));

		EmitVertex();
	}

	EndPrimitive();
}