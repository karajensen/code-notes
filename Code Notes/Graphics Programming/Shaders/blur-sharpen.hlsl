//our global transform variables
float4x4 g_mWorld;
float4x4 g_mViewProj;
float4 g_vUserData;

sampler BaseSampler : register(s0);

struct VERTEX_INPUT
{
    float3 Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
};
struct VERTEX_OUTPUT
{
    float4 Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
    float Time : TEXCOORD1;
    float Size : TEXCOORD2;
};

VERTEX_OUTPUT vs_main(VERTEX_INPUT Input)
{
    VERTEX_OUTPUT Output;
    float4x4 mWVP = mul( g_mWorld, g_mViewProj );
    Output.Position = mul(float4(Input.Position, 1), mWVP);
    Output.TexCoord = Input.TexCoord;
    Output.Time = g_vUserData.x;
    Output.Size = g_vUserData.y;
    return Output;
}

float4 ps_main(VERTEX_OUTPUT Input) : COLOR
{
    //switch between blur/sharpen
    float4 vColor = tex2D(BaseSampler, Input.TexCoord);
    if(Input.Time < 0)
    {
        vColor *= (11.0f/3.0f);
        float xoffset = 1.0f/Input.Size;
        float yoffset = 1.0f/Input.Size;
        float4 p1 = tex2D(BaseSampler, Input.TexCoord + float2(0,yoffset));
        float4 p2 = tex2D(BaseSampler, Input.TexCoord + float2(0,-yoffset));
        float4 p3 = tex2D(BaseSampler, Input.TexCoord + float2(xoffset,0));
        float4 p4 = tex2D(BaseSampler, Input.TexCoord + float2(-xoffset,0));
        float factor = -2.0f/3.0f;
        vColor += (p1*factor);
        vColor += (p2*factor);
        vColor += (p3*factor);
        vColor += (p4*factor);
    }
    else
    {
        vColor *= 0.1f;
        for(int i = 1; i < 9; ++i)
        {
            float xoffset = 1.0f/Input.Size;
            float yoffset = 1.0f/Input.Size;
            float4 p1 = tex2D(BaseSampler, Input.TexCoord + float2(xoffset*i,0));
            float4 p2 = tex2D(BaseSampler, Input.TexCoord + float2(-xoffset*i,0));
            float4 p3 = tex2D(BaseSampler, Input.TexCoord + float2(0,-yoffset*i));
            float4 p4 = tex2D(BaseSampler, Input.TexCoord + float2(0,yoffset*i));
            vColor += (p1*(0.25f/8.0f));
            vColor += (p2*(0.25f/8.0f));
            vColor += (p3*(0.25f/8.0f));
            vColor += (p4*(0.25f/8.0f));    
        }
    }

    return vColor;
}