#version 450 core


layout(triangles, equal_spacing, ccw) in;

uniform mat4 modelViewProj;

in vec3 tcNorm[];
out vec3 teNorm;

void main()
{ 
    gl_Position = 
    (gl_TessCoord[0] * gl_in[0].gl_Position +
     gl_TessCoord[1] * gl_in[1].gl_Position +
     gl_TessCoord[2] * gl_in[2].gl_Position);

     teNorm = 
    (gl_TessCoord[0] * tcNorm[0] +
     gl_TessCoord[1] * tcNorm[1] +
     gl_TessCoord[2] * tcNorm[2]);
}