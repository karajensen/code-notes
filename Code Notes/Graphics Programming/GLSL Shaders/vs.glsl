varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 VertexNormal;
varying vec3 WorldViewPos;
void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    WorldViewPos = vec3(gl_ModelViewMatrix * gl_Vertex);
    gl_TexCoord[0] = gl_MultiTexCoord0;
    Normal = gl_NormalMatrix * gl_Normal;
    Tangent = gl_NormalMatrix * gl_MultiTexCoord1.xyz;
    Binormal = gl_NormalMatrix * gl_MultiTexCoord2.xyz;
}