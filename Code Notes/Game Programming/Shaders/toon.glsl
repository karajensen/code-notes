/****************************************************************
* Vertex Shader Toon
*****************************************************************/

uniform vec3 LightPos;
uniform vec4 LightColor;
varying vec2 UV;
varying vec3 VertexNormal;
varying vec3 LightVector;
varying vec4 DiffuseColor;
void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vec4 WorldViewPos = gl_ModelViewMatrix * gl_Vertex;
    VertexNormal = gl_NormalMatrix * gl_Normal;
    LightVector = normalize(LightPos - vec3(WorldViewPos));
    DiffuseColor = LightColor;
    UV = gl_MultiTexCoord0.xy;
}

/****************************************************************
* Fragment Shader Toon
*****************************************************************/

uniform sampler2D TexSampler;
varying vec2 UV;
varying vec3 VertexNormal;
varying vec3 LightVector;
varying vec4 DiffuseColor;
void main()
{
    vec4 Texture = texture2D(TexSampler, UV);
    vec3 normalisedNormal = normalize(VertexNormal);
    float diffuseValue = (dot(LightVector,normalisedNormal) + 1.0)*0.5;

    // Create bands of color depending on angle to light
    if (diffuseValue > 0.75)
    {
        Texture -= vec4(0.0,0.0,0.0,0.0); 
    }
    else if (diffuseValue > 0.5)
    {
        Texture -= vec4(0.2,0.2,0.2,0.0);
    }
    else if (diffuseValue > 0.25)
    {
        Texture -= vec4(0.4,0.4,0.4,0.0);
    }
    else
    {
        Texture -= vec4(0.6,0.6,0.6,0.0);
    }
    gl_FragColor = Texture;
}

/****************************************************************
* Vertex Shader Post
*****************************************************************/

varying vec2 UV;
void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    UV = gl_MultiTexCoord0.xy;
}

/****************************************************************
* Fragment Shader Post
*****************************************************************/

uniform sampler2D TexSampler;
uniform sampler2D NormalSampler;
varying vec2 UV;
void main()
{
    float offset = 0.0009;

    //sample normals of four corners around pixel
    vec4 scene = texture2D(TexSampler, UV);
    vec4 n1 = texture2D(NormalSampler, UV + vec2(-offset, -offset));
    vec4 n2 = texture2D(NormalSampler, UV + vec2( offset,  offset));
    vec4 n3 = texture2D(NormalSampler, UV + vec2(-offset,  offset));
    vec4 n4 = texture2D(NormalSampler, UV + vec2( offset, -offset));
    
    //determine the estimated difference between the pixel normal and surrounding
    vec4 diagonal1 = abs(n1 - n2);
    vec4 diagonal2 = abs(n3 - n4);
    vec4 diagonalDelta = diagonal1 + diagonal2;
    float edgeAmount = clamp(length(diagonalDelta), 0.0, 1.0);

    scene *= 1.0 - edgeAmount;
    gl_FragColor = scene;
}
