//================================================================================
//TOON LINES PIXEL SHADER
//================================================================================

varying float alpha;
varying vec3 VertexNormal;

void main()
{
	vec3 Norm = normalize(VertexNormal);
	vec4 DiffuseColor;
	DiffuseColor.r = Norm.x;
	DiffuseColor.g = Norm.y;
	DiffuseColor.b = Norm.z;
	DiffuseColor.a = alpha;
	gl_FragColor = DiffuseColor;
}
