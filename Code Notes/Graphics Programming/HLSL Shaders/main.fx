//===============================================================================
//								= MAIN SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//		- Diffuse/ambient lighting
//		- No texturing
//===============================================================================

float4x4 World 					: World;
float4x4 WorldViewProjection 	: WorldViewProjection;
float4x4 WorldInvTrans 			: WorldInverseTranspose;

float3 LightPos;
float AmbientIntensity;		float4 AmbientColor;
float DiffuseIntensity;		float4 DiffuseColor;
float att0,att1,att2;


//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_OUTPUT
{
    float4 Pos 			: POSITION;
    float3 Normal		: TEXCOORD0;
    float3 LightVector	: TEXCOORD1;
};


//===============================================================================
//VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader(	float4 inPos : POSITION, 
					float3 inNormal : NORMAL )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection); 
    float3 PosWorld = mul(inPos, World); 
   
	//NORMAL
	output.Normal = mul(inNormal,WorldInvTrans);
	
	//LIGHT VECTOR
	output.LightVector = LightPos - PosWorld;
    return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{	
	input.LightVector = normalize(input.LightVector);
	input.Normal = normalize(input.Normal);
	
	//DIFFUSE LIGHT
	float4 Diffuse = (dot(input.LightVector, input.Normal)+1)*0.5; //Brings into range 0-1
	Diffuse = Diffuse * DiffuseIntensity * DiffuseColor;
	
	//AMBIENT LIGHT
	float4 Ambient = (AmbientIntensity * AmbientColor);
	
	return (Diffuse + Ambient);
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
        CULLMODE = CW;

        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();

    }
}
