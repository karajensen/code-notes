//===============================================================================
//                                = PURE REFLECTION SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//        - Reflection from surrounding scene only
//
//===============================================================================

float4x4 World                    : World;
float4x4 WorldViewProjection    : WorldViewProjection;
float4x4 WorldInvTrans            : WorldInverseTranspose;

float3 LightPos;            float LightOn;
float AmbientIntensity;        float4 AmbientColor;
float DiffuseIntensity;        float4 DiffuseColor;
float SpecularIntensity;    float4 SpecularColor;    float SpecularSize;
float att0,att1,att2;

float3 CameraPos;

Texture texColor; //COLOR
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; };

Texture texEnviron; //ENVIRON
sampler EnvironSampler = sampler_state 
{texture = (texEnviron); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = CLAMP; AddressV = CLAMP; };


//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_OUTPUT_REFLECT
{
    float4 Pos                 : POSITION;
    float3 ReflectionVector    : TEXCOORD0;
};

struct VS_OUTPUT_REFLECTSHADE
{
    float4 Pos                        : POSITION;
    float3 Normal                    : TEXCOORD0;
    float3 LightVector                : TEXCOORD1;
    float3 CameraVector                : TEXCOORD2;
};

//===============================================================================
//VERTEX SHADER [REFLECT]
//===============================================================================

VS_OUTPUT_REFLECT VShaderReflect(float4 inPos        : POSITION, 
                                 float3 inNormal    : NORMAL )
{
    VS_OUTPUT_REFLECT output = (VS_OUTPUT_REFLECT)0; 
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection); 
    float3 PosWorld = mul(inPos, World); 
   
    //NORMAL
    inNormal = normalize(mul(inNormal,WorldInvTrans)); 
    
    //CREATE REFLECTION VECTOR
    float3 CameraVector = CameraPos-PosWorld;
    output.ReflectionVector = reflect(-CameraVector, inNormal);

    return output;
}

//===============================================================================
//PIXEL SHADER [REFLECT]
//===============================================================================

float4 PShaderReflect(VS_OUTPUT_REFLECT input) : COLOR0
{    
    //REFLECTION
    float4 Reflection = texCUBE(EnvironSampler, input.ReflectionVector);
    
    //FINAL COLOR
    float4 Color = Reflection;
    Color.a = 1.0f;
    return Color;
}


//===============================================================================
//VERTEX SHADER [REFLECT_SHADED]
//===============================================================================

VS_OUTPUT_REFLECTSHADE VShaderReflectShaded( float4 InPos  : POSITION,
                                             float3 InNormal : NORMAL )
{ 
    VS_OUTPUT_REFLECTSHADE output = (VS_OUTPUT_REFLECTSHADE)0;

    //TRANSFORMATIONS
    output.Pos  = mul(InPos, WorldViewProjection);
    float3 PosWorld = mul(InPos, World);
  
    //NORMAL
    output.Normal = mul(InNormal, WorldInvTrans);

    //CREATE Camera VECTOR
    output.CameraVector = normalize(CameraPos-PosWorld);
    
    //CREATE LIGHT VECTOR
    output.LightVector = normalize(LightPos-PosWorld);
    
    return output;
}

//===============================================================================
//PIXEL SHADER [REFLECT_SHADED]
//===============================================================================

float4 PShaderReflectShaded(VS_OUTPUT_REFLECTSHADE input) : COLOR0
{
    
    input.Normal = normalize(input.Normal);
    
    //CREATE REFLECTION VECTORS
    float3 LightReflectionVector = normalize(-reflect(input.LightVector, input.Normal)); 
    float3 CamReflectionVector = -reflect(input.CameraVector, input.Normal);
    
    //SPECULAR 
    float4 Specular = SpecularIntensity * SpecularColor * pow(saturate(dot(LightReflectionVector, input.CameraVector)), SpecularSize);
    
    //DIFFUSE
    float4 Diffuse = DiffuseColor*(((dot(input.LightVector, input.Normal)*0.5)+ Specular + 0.4)*1.7);
    
    //REFLECTION
    float4 Reflection = texCUBE(EnvironSampler, CamReflectionVector); 
   
    //FINALISE COLOR
    float4 Color = saturate((Reflection*Diffuse) + (Specular/2));
    Color.a = 1.0f;
    return Color;
}


//===============================================================================
//TECHNIQUES
//===============================================================================

technique MAIN
{
    pass Pass0
    {
        LIGHTING = TRUE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CULLMODE = CCW;

        VertexShader = compile vs_3_0 VShaderReflect();
        PixelShader = compile ps_3_0 PShaderReflect();

    }
}

technique REFLECT_SHADED
{
    pass Pass0
    {
        LIGHTING = TRUE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CULLMODE = CCW;

        VertexShader = compile vs_3_0 VShaderReflectShaded();
        PixelShader = compile ps_3_0 PShaderReflectShaded();

    }
}