//===============================================================================
//								= TEXTURE SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//		- Diffuse/ambient lighting
//		- Texturing
//===============================================================================

float4x4 World 					: World;
float4x4 WorldViewProjection 	: WorldViewProjection;
float4x4 WorldInvTrans 			: WorldInverseTranspose;

float3 CameraPos;

float3 LightPos;			float LightOn;
float AmbientIntensity;		float4 AmbientColor;
float DiffuseIntensity;		float4 DiffuseColor;
float SpecularIntensity;	float4 SpecularColor;	float SpecularSize;
float att0,att1,att2;

Texture texColor; //COLOR
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; };

float BumpDepth;
Texture texBump; //BUMP
sampler BumpSampler = sampler_state 
{texture = <texBump>; magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; }; 



//===============================================================================
//STRUCTURES
//===============================================================================


struct VS_OUTPUT
{
    float4 Pos 			: POSITION; 
    float2 UV			: TEXCOORD0;
	float3 Normal		: TEXCOORD1;
	float3 LightVector 	: TEXCOORD2;
	float3 Tangent		: TEXCOORD3;
	float3 Binormal 	: TEXCOORD4;
};	

struct VS_OUTPUT_SPEC
{
    float4 Pos 			: POSITION; 
    float2 UV			: TEXCOORD0;
	float3 Normal		: TEXCOORD1;
	float3 LightVector 	: TEXCOORD2;
	float3 Tangent		: TEXCOORD3;
	float3 Binormal 	: TEXCOORD4;
	float3 CameraVector : TEXCOORD5;
};	


//===============================================================================
//VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader(	float4 inPos		: POSITION, 
					float3 inNormal		: NORMAL,
					float2 inUV			: TEXCOORD0,
					float3 inTangent	: TANGENT0,
					float3 inBinormal	: BINORMAL0 )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection); 
    
    if(LightOn >= 1.0f)
    {
		float3 PosWorld = mul(inPos, World); 
   
		//CONVERT NORMALS
		output.Normal = mul(inNormal,WorldInvTrans);
		output.Tangent = mul(inTangent,WorldInvTrans);
		output.Binormal = mul(inBinormal,WorldInvTrans);
	
		//LIGHT VECTOR
		output.LightVector = normalize(LightPos - PosWorld);
	
		//UV
		output.UV = inUV;
	}

    return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{	
	float4 Color;
	
	if(LightOn >= 1.0f)
    {
		//BUMP
		float3 bump = BumpDepth * (tex2D(BumpSampler, input.UV).rgb - float3(0.5,0.5,0.5));
		input.Normal = input.Normal + bump.x*input.Tangent + bump.y*input.Binormal;
		input.Normal = normalize(input.Normal);

		//DIFFUSE LIGHT
		input.Normal = normalize(input.Normal);
		float4 Diffuse = DiffuseIntensity * DiffuseColor * dot(input.LightVector, input.Normal);
		
		//AMBIENT LIGHT
		float4 Ambient = (AmbientIntensity * AmbientColor) + 0.2;
		
		//TEXTURE
		float4 Texture = tex2D(ColorSampler, input.UV);
		
		//FINAL COLOR
		Color = saturate(Texture*(Diffuse + Ambient));
		Color.a = Texture.a;
	}
	
	return Color;
}

//===============================================================================
//VERTEX SHADER [SPEC]
//===============================================================================

VS_OUTPUT_SPEC VShaderSpec(	float4 inPos		: POSITION, 
							float3 inNormal		: NORMAL,
							float2 inUV			: TEXCOORD0,
							float3 inTangent	: TANGENT0,
							float3 inBinormal	: BINORMAL0 )
{
    VS_OUTPUT_SPEC output = (VS_OUTPUT_SPEC)0;
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection); 
    
    if(LightOn >= 1.0f)
    {
		float3 PosWorld = mul(inPos, World); 
	   
		//CONVERT NORMALS
		output.Normal = mul(inNormal,WorldInvTrans);
		output.Tangent = mul(inTangent,WorldInvTrans);
		output.Binormal = mul(inBinormal,WorldInvTrans);
		
		//LIGHT VECTOR
		output.LightVector = normalize(LightPos - PosWorld);
		
		//CREATE Camera VECTOR
		output.CameraVector = normalize(CameraPos - PosWorld);
		
		//UV
		output.UV = inUV;
	}
    
    return output;
}

//===============================================================================
//PIXEL SHADER [SPEC]
//===============================================================================

float4 PShaderSpec(VS_OUTPUT_SPEC input) : COLOR0
{	

	float4 Color;
	
	if(LightOn >= 1.0f)
    {
		//BUMP
		float3 bump = BumpDepth * (tex2D(BumpSampler, input.UV).rgb - float3(0.5,0.5,0.5));
		input.Normal = input.Normal + bump.x*input.Tangent + bump.y*input.Binormal;
		input.Normal = normalize(input.Normal);

		//DIFFUSE LIGHT
		input.Normal = normalize(input.Normal);
		float4 Diffuse = DiffuseIntensity * DiffuseColor * dot(input.LightVector, input.Normal);
	
		//AMBIENT LIGHT
		float4 Ambient = (AmbientIntensity * AmbientColor) + 0.2;
	
		//SPECULAR
		float3 HalfVector = normalize(input.LightVector + input.CameraVector);
		float4 Specular = SpecularIntensity * SpecularColor * (pow(saturate(dot(input.Normal, HalfVector)), SpecularSize));
	
		//TEXTURE
		float4 Texture = tex2D(ColorSampler, input.UV);
		
		//FINAL COLOR
		Color = saturate(Texture*(Diffuse + Ambient + Specular));
		Color.a = Texture.a;
	}
	
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
technique BUMP_BLEND_NOCULL
{
    pass Pass0
    {
        LIGHTING = TRUE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CULLMODE = NONE;
        
        AlphaBlendEnable = true; 
		SrcBlend = SrcAlpha; 
		DestBlend = InvSrcAlpha;

        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();

    }
}
technique BUMP_SPEC
{
    pass Pass0
    {
        LIGHTING = TRUE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CULLMODE = CCW;
		
        VertexShader = compile vs_3_0 VShaderSpec();
        PixelShader = compile ps_3_0 PShaderSpec();
    }
}