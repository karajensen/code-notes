//================================================================================
//NO LIGHTING WITH TEXTURE PIXEL SHADER
//================================================================================
uniform sampler2D TexSampler;
varying vec2 UV;
void main()
{
    vec4 Texture = texture2D(TexSampler, UV);
    gl_FragColor = Texture;
}
