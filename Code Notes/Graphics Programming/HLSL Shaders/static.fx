//===============================================================================
//                                = STATIC SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//        - Diffuse/ambient lighting
//        - Texturing
//===============================================================================

float4x4 WorldViewProjection     : WorldViewProjection;

Texture texColor; //COLOR
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; };

float offset;

//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_OUTPUT
{
    float4 Pos                 : POSITION;
    float2 UV                : TEXCOORD1;
};

//===============================================================================
//VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader(    float4 inPos    : POSITION, 
                    float2 inUV        : TEXCOORD0 )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection); 
    
    //UV
    output.UV = inUV;

    return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{    
    //TEXTURE
    float2 amount;
    amount = input.UV + offset;
    float4 Texture = tex2D(ColorSampler, amount);
    
    //FINAL COLOR
    float4 Color = saturate(Texture);
    Color.a = Texture.a;
    
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

        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();

    }
}