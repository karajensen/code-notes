/****************************************************************
* Kara Jensen (mail@karajensen.com) 
* Generic world shader
*****************************************************************/

float4x4 World                 : World;
float4x4 WorldViewProjection   : WorldViewProjection;
float4x4 WorldInvTrans         : WorldInverseTranspose;

float3 LightPos;
float AmbientIntensity;     
float4 AmbientColor;
float DiffuseIntensity;     
float4 DiffuseColor;
float4 MeshColor;

struct VS_OUTPUT
{
    float4 Pos          : POSITION;
    float3 Normal       : TEXCOORD0;
    float3 LightVector  : TEXCOORD1;
};                      
                        
// Vertex Shader
VS_OUTPUT VShader(float4 inPos    : POSITION, 
                  float3 inNormal : NORMAL)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    output.Pos = mul(inPos, WorldViewProjection); 
    output.Normal = mul(inNormal,WorldInvTrans);
    output.LightVector = LightPos - mul(inPos, World);

    return output;
}

//Pixel Shader
float4 PShader(VS_OUTPUT input) : COLOR0
{   
    input.LightVector = normalize(input.LightVector);
    input.Normal = normalize(input.Normal);
    
    // bring diffuse into range of 0.4->1.0
    float inner = 0.4;
    float4 diffuse = ((dot(input.LightVector, input.Normal)
        +1.0)*((1.0-inner)/(2.0)))+inner;

    diffuse *= DiffuseIntensity * DiffuseColor;
    float4 ambient = AmbientIntensity * AmbientColor;
    return MeshColor * (diffuse + ambient);
}

//Techniques
technique Main
{
    pass Pass0
    {
        LIGHTING = TRUE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CULLMODE = CCW;

        VertexShader = compile vs_2_0 VShader();
        PixelShader = compile ps_2_0 PShader();
    }
}