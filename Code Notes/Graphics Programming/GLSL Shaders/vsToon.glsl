//================================================================================
//TOON BANDS VERTEX SHADER
//================================================================================
uniform vec3 LightPos;
uniform vec4 LightColor;
varying vec2 UV;
varying vec3 VertexNormal;
varying vec3 LightVector;
varying vec4 DiffuseColor;
void main()
{

	//TRANSFORM VERTEX
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	vec4 WorldViewPos = gl_ModelViewMatrix * gl_Vertex;

	//TRANSFORM NORMAL
	VertexNormal = gl_NormalMatrix * gl_Normal;

	//TRANSFORM LIGHT POSITION
	LightVector = normalize(LightPos - vec3(WorldViewPos));

	//PASS LIGHT
	DiffuseColor = LightColor;

	//PASS UVS
	UV = gl_MultiTexCoord0;
}
