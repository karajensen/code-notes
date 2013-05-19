//===============================================================================
//								= BOUNDS SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//		- No lighting/texturing
//		- Creates red transparent
//===============================================================================

float4x4 WorldViewProjection 	: WorldViewProjection;


//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_OUTPUT
{
    float4 Pos 			: POSITION;
};

//===============================================================================
//VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader(float4 inPos : POSITION)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection);

    return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{	
	return float4(1.0,0,0,0.2);
}


//===============================================================================
//TECHNIQUES
//===============================================================================

technique MAIN
{
    pass Pass0
    {
        LIGHTING = FALSE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CULLMODE = CCW;
        
        AlphaBlendEnable = true; 
		SrcBlend = SrcAlpha; 
		DestBlend = InvSrcAlpha;
		FillMode = Solid;

        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();

    }
}
