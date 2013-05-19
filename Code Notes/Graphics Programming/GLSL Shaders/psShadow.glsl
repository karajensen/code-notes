//=========================================================================
//NO LIGHTING, SHADOW PROJECTION PIXEL SHADER
//=========================================================================
uniform vec4 LightColor;
void main()
{
	vec4 col = LightColor;
	col.r = 0.0;
	col.g = 0.0;
	col.b = 0.0;
	col.a = 1.0;
	gl_FragColor = col;
}
