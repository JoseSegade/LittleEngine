#version 330 core
layout (location  = 0) out vec4 outColor;
layout (location = 1)  out vec4 fragPos;

struct vertex
{
	vec3 pos;
	vec3 color;
	vec2 texCoord;
	vec3 norm;
};

in vertex gVertex;

uniform sampler2D colorTex;
uniform sampler2D emiTex;

//Propiedades del objeto
vec3 Ka;
vec3 Kd;
vec3 Ks;
vec3 N;
float alpha = 500.0;
vec3 Ke;

//Propiedades de la luz
vec3 Ia = vec3 (0.3);
vec3 Id = vec3 (1.0);
vec3 Is = vec3 (0.7);
vec3 lpos = vec3 (0.0); 
float lpower = 5.0;

vec3 shade();

void main()
{
	Ka = texture(colorTex, gVertex.texCoord).rgb;
	Kd = texture(colorTex, gVertex.texCoord).rgb;
	//Ke = texture(emiTex, texCoord).rgb;
	Ks = vec3 (1.0);

	N = gVertex.norm;
	
	outColor = vec4(shade(), 1.0);
	fragPos = vec4(gVertex.pos,0.0);
}

vec3 shade()
{	
	vec3 c = vec3(0.0);
	c = Ia * Ka;

	vec3 L = normalize (lpos - gVertex.pos);
	vec3 diffuse = Id * Kd * dot (L,N) * (lpower / length(lpos - gVertex.pos));
	c += clamp(diffuse, 0.0, 1.0);
	
	vec3 V = normalize (-gVertex.pos);
	vec3 R = normalize (reflect (-L,N));
	float factor = max (dot (R,V), 0.5);
	vec3 specular = Is*Ks*pow(factor,alpha) * (lpower / length(lpos - gVertex.pos));
	c += clamp(specular, 0.0, 1.0);

	//c+=Ke;
	
	return c;
}
