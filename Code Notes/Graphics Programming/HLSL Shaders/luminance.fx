//===============================================================================
//                                = LUMINANCE SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//        - Converts textured sprite/mesh to grayscale
//        - Intended for post processing
//
//===============================================================================

float4x4 WorldViewProjection : WorldViewProjection;

Texture texColor; 
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; };


//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_OUTPUT
{
    float4 Pos        : POSITION;    
    float2 UV        : TEXCOORD0;
};

//===============================================================================
//VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader(    float4 inPos : POSITION, 
                    float2 inUV : TEXCOORD0 )
{
    VS_OUTPUT output = (VS_OUTPUT)0; //initialise struct
    
    output.Pos = mul(inPos, WorldViewProjection);
    output.UV = inUV;
    
    return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{    
    float3 lumConst = float3(0.30, 0.59, 0.11);
    float3 Texture = tex2D(ColorSampler, input.UV);
    float Gray = dot(Texture,lumConst);
    
    //FINAL COLOR
    return float4(Gray,Gray,Gray,1.0);

}

//===============================================================================
//TECHNIQUES
//===============================================================================

technique MAIN
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();
    }
}