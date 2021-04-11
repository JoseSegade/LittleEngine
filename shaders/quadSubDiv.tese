#version 450 core


layout(quads, equal_spacing, ccw) in;

uniform mat4 modelViewProj;

in vec3 tcNorm[];
out vec3 teNorm;

vec3 interpolation(vec3 p0, vec3 p1, vec3 p2, vec3 p3)
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    return (p0 * (1 - u) * (1 - v) + p1 * u * (1 - v) + p2 * u * v + p3 * v * (1 - u));
}

void main()
{ 
    gl_Position = vec4(interpolation
    (gl_in[0].gl_Position.rgb,
     gl_in[1].gl_Position.rgb,
     gl_in[2].gl_Position.rgb,
     gl_in[3].gl_Position.rgb), 1.0);

     teNorm = interpolation
    (tcNorm[0],
     tcNorm[1],
     tcNorm[2],
     tcNorm[3]);
}