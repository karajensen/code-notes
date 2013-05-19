//===============================================================================
//                                = BASIC SHADOW SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//
//===============================================================================


#define SMAP_SIZE 512
#define SHADOW_EPSILON 0.00005f

float4x4 World                    :World;
float4x4 WorldViewProjection    :WorldViewProjection;
float4x4 WorldInvTrans             : WorldInverseTranspose;
float4x4 LightViewProj; 

float3 LightPos;            float LightOn;
float AmbientIntensity;        float4 AmbientColor;
float DiffuseIntensity;        float4 DiffuseColor;
float att0,att1,att2;


Texture texColor; //COLOR
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; };

Texture texShadow; //SHADOW
sampler2D ShadowSampler = sampler_state 
{texture = (texShadow); magfilter = POINT; minfilter = POINT; mipfilter = POINT; AddressU = CLAMP; AddressV = CLAMP; };


//===============================================================================
//SHADOW CALCULATIONS [Referenced from DirectX Sample]
//===============================================================================
float4 GetShadowValue(float4 posinlightvp, float4 diffuse)
{
    float4 Shadow = float4(0,0,0,0);
    
    //transform to texture space.
    float2 ShadowTexC = 0.5 * posinlightvp.xy / posinlightvp.w + float2( 0.5, 0.5 );
    ShadowTexC.y = 1.0f - ShadowTexC.y;
    
    //find depths
    float currentDepth = posinlightvp.z/posinlightvp.w;
    float mappedDepth = tex2D( ShadowSampler, ShadowTexC );
    
     //CHECK IF IN SHADOW
    if(currentDepth > (mappedDepth+SHADOW_EPSILON))
    {
        //IN SHADOW HENCE PCF ALGORITHM
        //transform to texel space
        float2 texelpos = SMAP_SIZE * ShadowTexC;
        
        //Determine the lerp amounts           
        float2 lerps = frac( texelpos );

        //read in bilerp stamp, doing the shadow checks
        float sourcevals[4];
        sourcevals[0] = (tex2D( ShadowSampler, ShadowTexC ) + SHADOW_EPSILON < currentDepth)? 0.0f: 1.0f;  
        sourcevals[1] = (tex2D( ShadowSampler, ShadowTexC + float2(1.0/SMAP_SIZE, 0) ) + SHADOW_EPSILON < currentDepth)? 0.0f: 1.0f;  
        sourcevals[2] = (tex2D( ShadowSampler, ShadowTexC + float2(0, 1.0/SMAP_SIZE) ) + SHADOW_EPSILON < currentDepth)? 0.0f: 1.0f;  
        sourcevals[3] = (tex2D( ShadowSampler, ShadowTexC + float2(1.0/SMAP_SIZE, 1.0/SMAP_SIZE) ) + SHADOW_EPSILON < currentDepth)? 0.0f: 1.0f;  
            
        //lerp between the shadow values to calculate our light amount
        float LightAmount = lerp( lerp( sourcevals[0], sourcevals[1], lerps.x ),
                            lerp( sourcevals[2], sourcevals[3], lerps.x ),
                            lerps.y );
        //FINAL SHADOW
        LightAmount -= 0.05;
        Shadow = (LightAmount*diffuse);
        Shadow.a = 1.0f;
    }
    else
        Shadow = diffuse;
    return Shadow;
}


//===============================================================================
//STRUCTURES
//===============================================================================
                                            
struct VS_OUTPUT
{
    float4 Pos        : POSITION;
    float2 Tex        : TEXCOORD0;
    float3 Normal    : TEXCOORD2;
    float4 PosInLightVP : TEXCOORD3; //position of vertex in light view projection
    float3 LightVector     : TEXCOORD4;
};


//===============================================================================
//VERTEX SHADER
//===============================================================================
VS_OUTPUT VShader(    float4 inPos : POSITION,
                    float3 inNormal : NORMAL,
                    float2 inTex : TEXCOORD0)
{
    
    VS_OUTPUT output = (VS_OUTPUT)0; //initialise struct
    
    //TRANSFORM
    output.Pos = mul(inPos, WorldViewProjection); 
    float4 PosWorld = mul(inPos, World); 
   
    //NORMAL
    output.Normal = mul(inNormal,WorldInvTrans);
    
    //CREATE LIGHT VECTOR
    output.LightVector = normalize(LightPos - PosWorld);


    //POSITION OF VETEX IN LIGHT SPACE
    output.PosInLightVP = mul(inPos, World);
    output.PosInLightVP = mul(output.PosInLightVP, LightViewProj);
    
    output.Tex = inTex;
    
    return output;
}

//===============================================================================
//PIXEL SHADER
//===============================================================================
float4 PShader(VS_OUTPUT input) : COLOR
{
    //NORMAL
    input.Normal = normalize(input.Normal);
    
    //DIFFUSE LIGHTING
    float4 Diffuse = saturate(DiffuseIntensity * DiffuseColor * dot(input.LightVector, input.Normal));
    
    //AMBIENT LIGHT
    float4 Ambient = AmbientIntensity * AmbientColor;
    Ambient += 0.1;
    
    //SHADOW
    float4 Shadow = GetShadowValue(input.PosInLightVP, Diffuse);
        
    //TEXTURE
    float4 Texture = tex2D(ColorSampler, input.Tex);
    
    //FINAL COLOR
    float4 Color = saturate(Texture*(Shadow + Ambient + (Diffuse/1.5)));
    Color.a = Texture.a;
    return Color;
}


//===============================================================================
//TECHNIQUES
//===============================================================================
technique MAIN
{
    pass p0
    {
        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();
    }
}