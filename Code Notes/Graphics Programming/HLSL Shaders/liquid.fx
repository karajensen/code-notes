
//===============================================================================
//								 = LIQUID SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//		- Reflections
//		- Specular/Diffuse/Ambient lighting
//		
//===============================================================================


float4x4 World 					: World;
float4x4 WorldViewProjection 	: WorldViewProjection;
float4x4 WorldInvTrans 			: WorldInverseTranspose;


float3 LightPos;			float LightOn;
float AmbientIntensity;		float4 AmbientColor;
float DiffuseIntensity;		float4 DiffuseColor;
float SpecularIntensity;	float4 SpecularColor;	float SpecularSize;
float att0,att1,att2;

float3 CameraPos;

Texture texColor; //COLOR
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; };


//===============================================================================
//STRUCTURES
//===============================================================================

struct VS_OUTPUT
{
    float4 Pos						: POSITION;
    float3 Normal					: TEXCOORD0;
    float3 LightVector				: TEXCOORD1;
    float3 CameraVector				: TEXCOORD2;
    float3 CamReflectionVector		: TEXCOORD3;
};

//===============================================================================
//VERTEX SHADER
//===============================================================================

VS_OUTPUT VShader( float4 InPos		: POSITION,
			       float3 InNormal	: NORMAL )
{ 
    VS_OUTPUT output = (VS_OUTPUT)0;

	//TRANSFORMATIONS
	output.Pos  = mul(InPos, WorldViewProjection);
    float3 PosWorld = mul(InPos, World).xyz;
  
	//NORMAL
    output.Normal = normalize(mul(InNormal, WorldInvTrans));

	//CREATE Camera VECTOR
	output.CameraVector = normalize(CameraPos-PosWorld);
	output.CamReflectionVector = -reflect(output.CameraVector, output.Normal);
	
	//CREATE LIGHT VECTOR
	output.LightVector = normalize(LightPos-PosWorld);
	
    
	return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================

float4 PShader(VS_OUTPUT input) : COLOR0
{
    
	//CREATE REFLECTION VECTOR
	float3 LightReflectionVector = normalize(-reflect(input.LightVector, input.Normal)); 
    
    //SPECULAR (specular highlights in response to light)
    float3 Specular = SpecularIntensity * SpecularColor * pow(saturate(dot(LightReflectionVector, input.CameraVector)), SpecularSize);
        
    //REFLECTION HIGHLIGHTS (specular highlights in response to Camera)
    float3 SpecularCam = pow(saturate(dot(input.CamReflectionVector, CameraPos.xyz)), 10)*0.05;    
    
    //DIFFUSE LIGHT
	float3 Diffuse = DiffuseColor*((dot(input.LightVector, input.Normal)*0.5)+ Specular + 0.3);
	
    //REFLECTION 
    float3 Reflection = texCUBE(ColorSampler, input.CamReflectionVector);
   
	//FINALISE COLOR
	float4 Color;
	Color.rgb  = Reflection*Diffuse;
	Color.rgb += SpecularCam;
	Color.rgb += Specular;	
	Color.a = 1.0;

    return Color;
}

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
