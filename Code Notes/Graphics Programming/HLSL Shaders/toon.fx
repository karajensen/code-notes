//===============================================================================
//								 = TOON SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//		- Toonbands depending on light
//		- Toonlines
//		- Texture reduction
//===============================================================================

float4x4 World 					: World;
float4x4 WorldViewProjection 	: WorldViewProjection;
float4x4 WorldInvTrans 			: WorldInverseTranspose;

float3 LightPos;			float LightOn;
float DiffuseIntensity;		float4 DiffuseColor;

Texture texColor; //COLOR
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; };

float4 LineColor = float4(0, 0, 0, 1);
float4 LineThickness = .09;

	
//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_INPUT
{
	float4 Pos		: POSITION;
	float3 Normal	: NORMAL;
	float2 UV		: TEXCOORD0;
};
											
struct VS_OUTPUT //and PS_INPUT
{
    float4 Pos 			: POSITION; 
    float2 UV			: TEXCOORD0;
	float3 Normal		: TEXCOORD1;
	float3 LightVector 	: TEXCOORD2;
};


//===============================================================================
//OUTLINE VERTEX SHADER
//===============================================================================

VS_OUTPUT OutlineVShader(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
 
	//TRANSFORM VERTEX
	output.Pos = mul(input.Pos, WorldViewProjection);
    
	//CONVERT NORMALS
	output.Normal = normalize(mul(input.Normal,WorldInvTrans).xyz);
 
    //EXPAND ORIGINAL POSITION TO SCALE MESH UNIFORMLY
    output.Pos = output.Pos + (mul(LineThickness, output.Normal));
 
    return output;
}


//===============================================================================
//OUTLINE PIXEL SHADER
//===============================================================================

float4 OutlinePShader(VS_OUTPUT input) : COLOR0
{
	return LineColor;
}


//===============================================================================
//CEL VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader(VS_INPUT input)

{
    VS_OUTPUT output = (VS_OUTPUT)0;
	
	//TRANSFORM VERTEX
	float3 PosWorld = mul(input.Pos, World);
    output.Pos = mul(input.Pos, WorldViewProjection);
    
	//CONVERT NORMALS
	output.Normal = normalize(mul(input.Normal,WorldInvTrans).xyz);
	
	//CREATE LIGHT VECTOR
	output.LightVector = normalize(LightPos - PosWorld);
	
    //UV COORDINATES
    output.UV = input.UV;

    return output;
	
}

//===============================================================================
//CEL PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{
	float4 Color;

	//DIFFUSE LIGHT
	float Diffuse = saturate(DiffuseIntensity * dot(input.LightVector, input.Normal));
	
	//TEXTURE
	Color = tex2D(ColorSampler, input.UV);
	float alpha = Color.a;

	//REMOVE TEXTURE DETAIL
	float3 detail = 4.0f;
	Color.r = round(Color.r*detail.x)/detail.x;
	Color.g = round(Color.g*detail.y)/detail.y;
	Color.b = round(Color.b*detail.z)/detail.z;

	//MAKE DISCRETE BANDS BASED ON DIFFUSE
	if (Diffuse > 0.95)
	{
		Color -= float4(0.0,0.0,0.0,0.0); //light bands
		//Color = float4(1.0,1,1,1.0) * Color; //texture washing
	}
	else if (Diffuse > 0.5)
	{
		Color -= float4(0.2,0.2,0.2,0.0); //light bands
		//Color = float4(0.7,0.7,0.7,1.0) * Color; //texture washing
	}
	else if (Diffuse > 0.25)
	{
		Color -= float4(0.4,0.4,0.4,0.0); //light bands
		//Color = float4(0.35,0.35,0.35,1.0) * Color; //texture washing
	}
	else
	{
		Color -= float4(0.6,0.6,0.6,0.0); //light bands
		//Color = float4(0.1,0.1,0.1,1.0) * Color; //texture washing
	}

	//FINAL COLOR
	Color.a = alpha;
	return Color;
}

//===============================================================================
//TECHNIQUES
//===============================================================================

technique MAIN
{
	//First pass draws larger version of model colored in black for toon outlines
    pass Pass0
    {		
        VertexShader = compile vs_3_0 OutlineVShader();
        PixelShader = compile ps_3_0 OutlinePShader();
        CullMode = CW;
    }
 
	//Second pass draws over the top using colors from model
 	pass Pass1
    {
		LIGHTING = TRUE;
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