/****************************************************************
* Vertex Shader 
*****************************************************************/
varying vec3 Normal;
varying float WorldViewPosZ;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    WorldViewPosZ = (gl_ModelViewMatrix * gl_Vertex).z;
    Normal = gl_NormalMatrix * gl_Normal;
}

/****************************************************************
* Fragment Shader 
*****************************************************************/


uniform float FrustumNear;
uniform float FrustumFar;
varying vec3 Normal;
varying float WorldViewPosZ;

void main()
{
    gl_FragColor.rgb = normalize(Normal);

    float cappedZ = max(min(WorldViewPosZ, FrustumFar),0.0);
    gl_FragColor.a = (cappedZ*((FrustumFar-FrustumNear)/FrustumFar))+FrustumNear;
}