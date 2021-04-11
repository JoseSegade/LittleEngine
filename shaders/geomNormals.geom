#version 330

layout(triangles) in;
layout(line_strip, max_vertices = 8) out;

uniform mat4 modelViewProj;
uniform float normalSize;

in vec3 norm[];

out vec4 color;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = modelViewProj * gl_in[i].gl_Position;
		color = vec4(1.0, 1.0, 0.0, 1.0);
		EmitVertex();
		gl_Position = modelViewProj * (gl_in[i].gl_Position + vec4(norm[i] * normalSize, 0.0));
		color = vec4(1.0, 1.0, 0.0, 1.0);
		EmitVertex();
		EndPrimitive();
	}

	// Generate triangle
	vec3 a = gl_in[0].gl_Position.xyz;
	vec3 b = gl_in[1].gl_Position.xyz;
	vec3 c = gl_in[2].gl_Position.xyz;

	vec3 u = a - b;
	vec3 v = a - c;

	vec4 normalTri = vec4(normalize(cross(u, v)), 0.0);
	vec4 center = vec4((a + b + c) / 3.0, 1.0);

	gl_Position = modelViewProj * center;
	color = vec4(1, 0, 0, 1);
	EmitVertex();

	gl_Position = modelViewProj * (center + normalTri * normalSize);
	color = vec4(1, 0, 0, 1);
	EmitVertex();

	EndPrimitive();
}