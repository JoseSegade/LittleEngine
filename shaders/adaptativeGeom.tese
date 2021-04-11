#version 450 core

layout(triangles, equal_spacing, ccw) in;

struct vertex
{
	vec3 pos;
	vec3 color;
	vec2 texCoord;
	vec3 norm;
};

in  vertex cVertex[];
out vertex eVertex;

vec2 interpolateVec2(vec2 p0, vec2 p1, vec2 p2)
{
    float u = gl_TessCoord[0];
    float v = gl_TessCoord[1];
    float w = gl_TessCoord[2];

    return u * p0 + v * p1 + w * p2;
}

vec3 interpolate(vec3 p0, vec3 p1, vec3 p2)
{
    float u = gl_TessCoord[0];
    float v = gl_TessCoord[1];
    float w = gl_TessCoord[2];

    return u * p0 + v * p1 + w * p2;
}

void main()
{
    eVertex.pos = interpolate
            (cVertex[0].pos,
             cVertex[1].pos,
             cVertex[2].pos);

     eVertex.color = interpolate
            (cVertex[0].color,
             cVertex[1].color,
             cVertex[2].color);

     eVertex.texCoord = interpolateVec2
            (cVertex[0].texCoord,
             cVertex[1].texCoord,
             cVertex[2].texCoord);

     eVertex.norm = interpolate
            (cVertex[0].norm,
             cVertex[1].norm,
             cVertex[2].norm);
}