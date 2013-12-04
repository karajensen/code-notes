/****************************************************************
* Kara Jensen (mail@karajensen.com) 
* Collision bounds shadder
*****************************************************************/

float4x4 WorldViewProjection : WorldViewProjection;
float3 Color;

struct VS_OUTPUT
{
    float4 Pos : POSITION;
};

//Vertex Shader
VS_OUTPUT VShader(float4 inPos : POSITION)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul(inPos, WorldViewProjection);
    return output;
}

//Pixel Shader
float4 PShader(VS_OUTPUT input) : COLOR0
{   
    return float4(Color.r, Color.g, Color.b, 0.2);
}

//Techniques
technique Main
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

        VertexShader = compile vs_2_0 VShader();
        PixelShader = compile ps_2_0 PShader();
    }
}
