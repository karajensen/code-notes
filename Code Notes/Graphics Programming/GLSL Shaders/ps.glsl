uniform sampler2D Sampler0;
uniform sampler2D Sampler1;
uniform sampler2D Sampler2;
varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 WorldViewPos;

void main()
{
	vec4 finalColor = vec4(0,0,0,0);

	// NORMAL TEXTURE
	float bumpdepth = 1.0;
	vec3 bump = bumpdepth*(texture2D(Sampler1, gl_TexCoord[0].st).xyz-0.5);
	vec3 normNormal = normalize(Normal + bump.x*Tangent + bump.y*Binormal);

	// DIFFUSE TEXTURE
	vec4 texture = texture2D(Sampler0, gl_TexCoord[0].st);

	// SPECULAR TEXTURE
	vec4 specularTexture = texture2D(Sampler2, gl_TexCoord[0].st);

	float att;
	float specular;
	float diffuse;
	float lightDist;
	vec3 lightVector;
	vec3 halfVector;	

	// FOR EACH LIGHT
	for(int i = 0; i < MAX_LIGHTS; ++i)
	{
		lightVector = gl_LightSource[i].position.xyz - WorldViewPos;
		lightDist = length(lightVector);
		lightVector = normalize(lightVector);

		// ATTENUATION
		// Step = d > 0.0 ? 0.0 : 1.0
		float d = gl_LightSource[i].constantAttenuation + 
			gl_LightSource[i].linearAttenuation * lightDist +
			gl_LightSource[i].quadraticAttenuation * lightDist * lightDist;
		att = mix(1.0/(d+0.00001), 1.0, step(d,0.0));
		
		// DIFFUSE
		diffuse = (dot(lightVector,normNormal) + 1.0) * 0.5;
		finalColor += diffuse * gl_LightSource[i].diffuse * att;
		
		// SPECULAR
		halfVector = normalize(lightVector + normalize(-WorldViewPos));
		specular = pow(max(dot(normNormal,halfVector),0.0),5.0); //gl_FrontMaterial.shininess
		finalColor += specular * gl_LightSource[i].specular * specularTexture * att;
	}

	gl_FragColor = finalColor*texture;
	gl_FragColor.a = texture.a;
}
