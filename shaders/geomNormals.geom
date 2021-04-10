#version 330

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in vec3 norm[];

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(norm[index], 0.0) * 0.2;
    EmitVertex();
    EndPrimitive();
}

void main()
{
	GenerateLine(0);
	GenerateLine(1);
	GenerateLine(2);
}