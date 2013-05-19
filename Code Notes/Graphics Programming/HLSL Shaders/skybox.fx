//===============================================================================
//                                = SKYBOX SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//        - No lighting
//        - No Z-buffering
//        - Texturing
//===============================================================================

float4x4 WorldViewProjection;

Texture texColor; //COLOR
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = CLAMP; AddressV = CLAMP; };


//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_OUTPUT
{
    float4 Pos         : POSITION;
    float2 UV        : TEXCOORD0;
};

//===============================================================================
//VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader(    float4 inPos : POSITION,
                    float2 inUV : TEXCOORD0 )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection); 

    //TEXTURE
    output.UV = inUV;

    return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{    
    //TEXTURE
    float4 Texture = tex2D(ColorSampler, input.UV);
    
    //FINAL COLOR
    float4 Color = Texture;
    Color.a = Texture.a; //alpha
    return Color;
}

//===============================================================================
//TECHNIQUES
//===============================================================================

technique MAIN
{
    pass Pass0
    {
        LIGHTING = FALSE;
        ZENABLE = FALSE;
        ZWRITEENABLE = FALSE;
        CULLMODE = CCW;

        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();

    }
}