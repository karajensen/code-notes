//===============================================================================
//								= DEPTH SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//		- For rendering depth information used in shadow mapping
//===============================================================================


float4x4 WorldViewProjection 	: WorldViewProjection;


//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_OUTPUT
{
    float4 Pos 			: POSITION;
    float2  Depth		: TEXCOORD0;
};

//===============================================================================
//VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader(	float4 inPos : POSITION )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection);
    
    //DEPTH INFORMATION
    output.Depth.xy = output.Pos.zw;

    return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{
	float d = input.Depth.x / input.Depth.y;
    return float4(d,d,d,1.0f);
}


//===============================================================================
//TECHNIQUES
//===============================================================================

technique MAIN
{
    pass Pass0
    {   
        VertexShader = compile vs_2_0 VShader();
        PixelShader = compile ps_2_0 PShader();
        
        LIGHTING = TRUE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CULLMODE = CCW;
    }
}