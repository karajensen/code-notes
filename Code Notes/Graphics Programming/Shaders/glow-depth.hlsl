
float4x4 g_mWorld;
float4x4 g_mViewProj;
float4x4 g_mView;
float2 g_mFrustum;

sampler GlowSampler : register(s0);

struct VERTEX_INPUT
{
    float3 Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
};
struct VERTEX_OUTPUT
{
    float4 Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
    float4 PosWorld : TEXCOORD1;
};

VERTEX_OUTPUT vs_main(VERTEX_INPUT Input)
{
    VERTEX_OUTPUT Output;
    float4x4 mWVP = mul(g_mWorld, g_mViewProj);
    float4x4 mWV = mul(g_mWorld, g_mView);
    Output.Position = mul(float4(Input.Position, 1), mWVP);
    Output.PosWorld = mul(float4(Input.Position, 1), mWV);
    Output.TexCoord = Input.TexCoord;
    return Output;
}

float4 ps_main(VERTEX_OUTPUT Input) : COLOR
{
    float4 color = tex2D(GlowSampler, Input.TexCoord);
    color.a = (((Input.PosWorld.z-g_mFrustum.x)*((1.0f)/(g_mFrustum.y-g_mFrustum.x))));
    return color;
}