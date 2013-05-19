//===============================================================================
//								= WATER SHADER =
//===============================================================================
//===============================================================================
//FEATURES:
//		- NVIDIA's Ocean shader
//===============================================================================

float4x4 World					: World;
float4x4 WorldInvTrans 			: WorldInverseTranspose;
float4x4 WorldViewProjection	: WorldViewProjection;

float Timer : TIME;
float3 CameraPos;

float3 LightPos;			float LightOn;
float AmbientIntensity;		float4 AmbientColor;
float DiffuseIntensity;		float4 DiffuseColor;
float att0,att1,att2;

Texture texColor; //COLOR
sampler ColorSampler = sampler_state 
{texture = (texColor); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; };

Texture texBump; //BUMP
sampler BumpSampler = sampler_state 
{texture = <texBump>; magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = WRAP; AddressV = WRAP; }; 

Texture texEnviron; //ENVIRON
sampler EnvironSampler = sampler_state 
{texture = (texEnviron); magfilter = LINEAR; minfilter = LINEAR; mipfilter = LINEAR; AddressU = CLAMP; AddressV = CLAMP; AddressW = CLAMP; };

//===============================================================================
//WATER
//===============================================================================

float BumpDepth;
float TexReptX = 8.0;
float TexReptY = 4.0;
float BumpSpeedX = -0.05;
float BumpSpeedY = 0.0;
float FresnelBias = 0.1;
float FresnelExp = 4.0;
float HDRMultiplier = 3.0;
float3 DeepColor = {0.0f, 0.0f, 0.1f};
float3 ShallowColor = {0.0f, 0.5f, 0.5f};
float3 ReflTint = {0, 0.5f, 1.0f};
float Kr = 1.0f;
float KWater = 1.0f;
float WaveAmp = 0.05;
float WaveFreq = 3.0;

//===============================================================================
//STRUCTURES
//===============================================================================

struct OceanVertOut {
    float4 HPosition  : POSITION;  // in clip space
    float2 UV  : TEXCOORD0;
    float3 T2WXf1 : TEXCOORD1; // first row of the 3x3 transform from tangent to cube space
    float3 T2WXf2 : TEXCOORD2; // second row of the 3x3 transform from tangent to cube space
    float3 T2WXf3 : TEXCOORD3; // third row of the 3x3 transform from tangent to cube space
    float2 bumpUV0 : TEXCOORD4;
    float2 bumpUV1 : TEXCOORD5;
    float2 bumpUV2 : TEXCOORD6;
    float3 WorldView  : TEXCOORD7;
};

struct VS_OUTPUT
{
    float4 Pos 			: POSITION;
    float3 Normal		: TEXCOORD0;
    float3 LightVector	: TEXCOORD1;
};


//===============================================================================
//WAVE FUNCTIONS
//===============================================================================

struct Wave {
  float freq;  // 2*PI / wavelength
  float amp;   // amplitude
  float phase; // speed * 2*PI / wavelength
  float2 dir;
};

#define NWAVES 2
Wave wave[NWAVES] = {
	{ 1.0, 1.0, 0.5, float2(-1, 0) },
	{ 2.0, 0.5, 1.3, float2(-0.7, 0.7) }	
};

float evaluateWave(Wave w, float2 pos, float t)
{
  return w.amp * sin( dot(w.dir, pos)*w.freq + t*w.phase);
}

// derivative of wave function
float evaluateWaveDeriv(Wave w, float2 pos, float t)
{
  return w.freq*w.amp * cos( dot(w.dir, pos)*w.freq + t*w.phase);
}

// sharp wave functions
float evaluateWaveSharp(Wave w, float2 pos, float t, float k)
{
  return w.amp * pow(sin( dot(w.dir, pos)*w.freq + t*w.phase)* 0.5 + 0.5 , k);
}

float evaluateWaveDerivSharp(Wave w, float2 pos, float t, float k)
{
  return k*w.freq*w.amp * pow(sin( dot(w.dir, pos)*w.freq + t*w.phase)* 0.5 + 0.5 , k - 1) * cos( dot(w.dir, pos)*w.freq + t*w.phase);
}

//===============================================================================
//VERTEX SHADER [OCEAN]
//===============================================================================

OceanVertOut OceanVS(float4 inPos : POSITION,
    				float2 inUV : TEXCOORD0,
    				float3 inTangent  : TEXCOORD1,
    				float3 inBinormal : TEXCOORD2,
    				float3 inNormal   : NORMAL) 
{
    OceanVertOut OUT = (OceanVertOut)0;
	
    wave[0].freq = WaveFreq;
    wave[0].amp = WaveAmp;
    wave[1].freq = WaveFreq*2.0;
    wave[1].amp = WaveAmp*0.5;
    
	float4 Po = float4(inPos.xyz,1.0);
    
	// sum waves	
    Po.y = 0.0;
    float ddx = 0.0, ddy = 0.0;
    for(int i=0; i<NWAVES; i++) 
	{
	Po.y += evaluateWave(wave[i], Po.xz, Timer);
	float deriv = evaluateWaveDeriv(wave[i], Po.xz, Timer);
	ddx += deriv * wave[i].dir.x;
	ddy += deriv * wave[i].dir.y;
    }
	
    // compute tangent basis
    float3 B = float3(1, ddx, 0);
    float3 T = float3(0, ddy, 1);
    float3 N = float3(-ddx, 1, -ddy);
    OUT.HPosition = mul(Po,WorldViewProjection);
	
    // pass texture coordinates for fetching the normal map
    float2 TextureScale = float2(TexReptX,TexReptY);
    float2 BumpSpeed = float2(BumpSpeedX,BumpSpeedY);
    OUT.UV = inUV.xy*TextureScale;
    float cycle = fmod(Timer, 100.0);
    OUT.bumpUV0.xy = inUV.xy*TextureScale + cycle*BumpSpeed;
    OUT.bumpUV1.xy = inUV.xy*TextureScale*2.0 + cycle*BumpSpeed*4.0;
    OUT.bumpUV2.xy = inUV.xy*TextureScale*4.0 + cycle*BumpSpeed*8.0;

    // compute the 3x3 tranform from tangent space to object space
    float3x3 objToTangentSpace;
	
    // first rows are the tangent and binormal scaled by the bump scale
    objToTangentSpace[0] = BumpDepth * normalize(T);
    objToTangentSpace[1] = BumpDepth * normalize(B);
    objToTangentSpace[2] = normalize(N);

    OUT.T2WXf1.xyz = mul(objToTangentSpace,World[0].xyz);
    OUT.T2WXf2.xyz = mul(objToTangentSpace,World[1].xyz);
    OUT.T2WXf3.xyz = mul(objToTangentSpace,World[2].xyz);

    // compute the eye vector (going from shaded point to eye) in cube space
    float3 Pw = mul(Po,World).xyz;
    OUT.WorldView = CameraPos - Pw; // view inv. transpose contains eye position in world space in last row
    return OUT;
}

//===============================================================================
//PIXEL SHADER [OCEAN]
//===============================================================================

float4 OceanPS(OceanVertOut IN) : COLOR
{
    // sum normal maps
    float4 t0 = tex2D(BumpSampler, IN.bumpUV0)*2.0-1.0;
    float4 t1 = tex2D(BumpSampler, IN.bumpUV1)*2.0-1.0;
    float4 t2 = tex2D(BumpSampler, IN.bumpUV2)*2.0-1.0;
    float3 Nt = t0.xyz + t1.xyz + t2.xyz;
    //    float3 Nt = t1.xyz;

    float3x3 m; // tangent to world matrix
    m[0] = IN.T2WXf1;
    m[1] = IN.T2WXf2;
    m[2] = IN.T2WXf3;
    float3 Nw = mul(m,Nt);
    float3 Nn = normalize(Nw);

	// reflection
    float3 Vn = normalize(IN.WorldView);
    float3 R = reflect(-Vn, Nn);

    float4 reflection = texCUBE(EnvironSampler, R);
    // hdr effect (multiplier in alpha channel)
    reflection.rgb *= (1.0 + reflection.a*HDRMultiplier);

    float facing = 1.0 - max(dot(Vn, Nn), 0);
    float fres = Kr*(FresnelBias+(1.0-FresnelBias)*pow(facing,FresnelExp));

    float3 waterColor = KWater * lerp(DeepColor, ShallowColor, facing);
    float3 result = waterColor + (fres * reflection.rgb * ReflTint);
    return float4(result.rgb,0.8f);
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
        CULLMODE = NONE;
		ZFunc = LessEqual;
		
		AlphaBlendEnable = true; 
		SrcBlend = SrcAlpha; 
		DestBlend = InvSrcAlpha;	
		
		VertexShader = compile vs_3_0 OceanVS();
        PixelShader = compile ps_3_0 OceanPS();
    }
}