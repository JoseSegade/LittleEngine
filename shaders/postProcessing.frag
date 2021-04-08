#version 430 core
//Color de salida
out vec4 outColor;

//Variables Variantes
in vec2 texCoord;

//Textura
uniform sampler2D colorTex;
uniform sampler2D posTex;

// shader
uniform float focalDistance;
uniform float maxDistanceFactor;

uniform float f;
uniform float n;

//const float focalDistance = -25;
//const float maxDistanceFactor = 1.0 / 5.0;

//#define MASK_SIZE 9u
/*const vec2 texIdx[MASK_SIZE] = vec2[](
	vec2(-1.0,1.0), vec2(0.0,1.0), vec2(1.0,1.0),
	vec2(-1.0,0.0), vec2(0.0,0.0), vec2(1.0,0.0),
	vec2(-1.0,-1.0), vec2(0.0,-1.0), vec2(1.0,-1.0));

const float maskFactor = float (1.0/15.0);
const float mask[MASK_SIZE] = float[](
	float (1.0*maskFactor), float (2.0*maskFactor), float (1.0*maskFactor),
	float (2.0*maskFactor), float (3.0*maskFactor), float (2.0*maskFactor),
	float (1.0*maskFactor), float (2.0*maskFactor), float (1.0*maskFactor));*/

/*const float maskFactor = float (1);
const float mask[MASK_SIZE] = float[](
	float (0.0*maskFactor), float (1.0*maskFactor), float (0.0*maskFactor),
	float (1.0*maskFactor), float (-4.0*maskFactor), float (1.0*maskFactor),
	float (0.0*maskFactor), float (1.0*maskFactor), float (0.0*maskFactor));*/

// shader
#define MASK_SIZE 25u
uniform float mask[MASK_SIZE];

const vec2 texIdx[MASK_SIZE] = vec2[](
	vec2(-2.0,2.0), vec2(-1.0,2.0), vec2(0.0,2.0), vec2(1.0,2.0), vec2(2.0,2.0),
	vec2(-2.0,1.0), vec2(-1.0,1.0), vec2(0.0,1.0), vec2(1.0,1.0), vec2(2.0,1.0),
	vec2(-2.0,0.0), vec2(-1.0,0.0), vec2(0.0,0.0), vec2(1.0,0.0), vec2(2.0,0.0),
	vec2(-2.0,-1.0), vec2(-1.0,-1.0), vec2(0.0,-1.0), vec2(1.0,-1.0), vec2(2.0,-1.0),
	vec2(-2.0,-2.0), vec2(-1.0,-2.0), vec2(0.0,-2.0), vec2(1.0,-2.0), vec2(2.0,-2.0));



float profundidad(float tex) 
{
	return (-n*f) / (f + tex * (n - f));
}

void main()
{
	//Ser�a m�s r�pido utilizar una variable uniform el tama�o de la textura.
	vec2 ts = vec2(1.0) / vec2 (textureSize (colorTex,0));

	float dof = abs(profundidad(texture(posTex,texCoord).x) -focalDistance)
			* maxDistanceFactor;

	dof = clamp (dof, 0.0, 1.0);
	dof *= dof;

	vec4 color = vec4 (0.0);
	for (uint i = 0u; i < MASK_SIZE; i++)
	{
		vec2 iidx = texCoord + ts * texIdx[i]*dof;
		color += texture(colorTex, iidx,0.0) * mask[i];
	}
	outColor = color;
}
