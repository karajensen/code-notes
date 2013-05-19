//================================================================================
//NO LIGHTING WITH TEXTURE PIXEL SHADER
//================================================================================
varying vec2 UV;
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	UV = gl_MultiTexCoord0.xy;
}
