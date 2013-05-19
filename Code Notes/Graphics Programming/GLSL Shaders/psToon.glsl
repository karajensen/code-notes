//================================================================================
//TOON BANDS PIXEL SHADER
//================================================================================

uniform sampler2D TexSampler;
varying vec2 UV;
varying vec3 VertexNormal;
varying vec3 LightVector;
varying vec4 DiffuseColor;

void main()
{
	//GET TEXTURE COLOR
	vec4 Texture = texture2D(TexSampler, UV);

	//NORMALISE NORMAL
	vec3 normalisedNormal = normalize(VertexNormal);

	//DIFFUSE LIGHTING
	float diffuseValue = (dot(LightVector,normalisedNormal) + 1.0)*0.5;

	//MAKE DISCRETE BANDS BASED ON DIFFUSE
	if (diffuseValue > 0.75)
	{
		Texture -= vec4(0.0,0.0,0.0,0.0); //light bands
	}
	else if (diffuseValue > 0.5)
	{
		Texture -= vec4(0.2,0.2,0.2,0.0); //light bands
	}
	else if (diffuseValue > 0.25)
	{
		Texture -= vec4(0.4,0.4,0.4,0.0); //light bands
	}
	else
	{
		Texture -= vec4(0.6,0.6,0.6,0.0); //light bands
	}

	//FINAL COLOR
	gl_FragColor = Texture;
}
