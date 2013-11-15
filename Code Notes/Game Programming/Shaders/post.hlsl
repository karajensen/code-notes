
float4x4 g_mWorld;
float4x4 g_mViewProj;

sampler BaseSampler : register(s0);
sampler GlowSampler : register(s1);
sampler DepthSampler : register(s2);
sampler PortalGlowSampler : register(s3);
sampler PortalSampler : register(s4);

struct VERTEX_INPUT
{
    float3 Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
};
struct VERTEX_OUTPUT
{
    float4 Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
};

VERTEX_OUTPUT vs_main(VERTEX_INPUT Input)
{
    VERTEX_OUTPUT Output;
    float4x4 mWVP = mul(g_mWorld, g_mViewProj);
    Output.Position = mul(float4(Input.Position, 1), mWVP);
    Output.TexCoord = Input.TexCoord;
    return Output;
}

float4 ps_main(VERTEX_OUTPUT Input) : COLOR
{
    float4 color = tex2D(BaseSampler, Input.TexCoord);
    float4 normal = tex2D(DepthSampler, Input.TexCoord);
    float4 colordof = color*float4(0.1,0.1,0.1,1.0);
    float depth = normal.a;
    float invdepth = 1.0f-depth;
    float offset = 1.0f/1024.0f;    

    //ANTIALIAS THE GLOW MAP
    float4 glow = tex2D(GlowSampler, Input.TexCoord)*float4(0.1,0.1,0.1,1.0);
    for(int i = 1; i < 4; i++)
    {
        glow += tex2D(GlowSampler, Input.TexCoord + float2(offset,0));
        glow += tex2D(GlowSampler, Input.TexCoord + float2(-offset,0));
        glow += tex2D(GlowSampler, Input.TexCoord + float2(0,offset));
        glow += tex2D(GlowSampler, Input.TexCoord + float2(0,-offset));
    }
    float alpha = glow.a;

    //BLUR THE GLOW
    if((glow.x == 0) && (glow.y == 0) && (glow.z == 0)) //if not doing mesh glow
    {
        float4 coord;
        float factor = 1.0/(4.0*3.0); //(tex lookups * loops)
        float spread = invdepth*6;
        float v = 1;
        float a = 1;
        float o;
        for(int i = 1; i < 4; i++)
        {
            o = offset*v;
            coord = tex2D(GlowSampler, Input.TexCoord + float2(o,0));
            if(coord.a <= depth){ glow += (coord*factor); }
            coord = tex2D(GlowSampler, Input.TexCoord + float2(-o,0));
            if(coord.a <= depth){ glow += (coord*factor); }
            coord = tex2D(GlowSampler, Input.TexCoord + float2(0,-o));
            if(coord.a <= depth){ glow += (coord*factor); }
            coord = tex2D(GlowSampler, Input.TexCoord + float2(0,o));
            if(coord.a <= depth){ glow += (coord*factor); }
            v += spread;
        }
        glow *= 1.5f; //halo glow intensity
    }
    else
    {
        glow *= 0.4f; //model glow intensity
    }

    //BLUR THE MAIN MAP
    float4 colordof = color*float4(0.1,0.1,0.1,1.0);
    float doffactor = (1.0f/4.0f)/8.0f; //(1/number of lookups per loop)/number of loops
    float o;
    for(int i = 1; i < 9; i++)
    {
        o = offset*i;
        colordof += (tex2D(BaseSampler, Input.TexCoord + float2(o,0))*doffactor);
        colordof += (tex2D(BaseSampler, Input.TexCoord + float2(-o,0))*doffactor);
        colordof += (tex2D(BaseSampler, Input.TexCoord + float2(0,-o))*doffactor);
        colordof += (tex2D(BaseSampler, Input.TexCoord + float2(0,o))*doffactor);
    }

    //DEPTH OF FEILD
    //(((value-currentRangeInner)*((newRangeOuter-newRangeInner)/(currentRangeOuter-currentRangeInner)))+newRangeInner);
    float value = 0;
    float dofstart = 0.4f;    //how far from camera the blurring gradient starts
    float dofclosestart = 0.1f;
    if(depth >= dofstart)
    {
        //move from 0.5->1.0 to 0->1.8
        float dofend = 3.0f;
        value = (((depth-dofstart)*((dofend-0.0)/(1.0-dofstart)))+0.0); 
        if(value > 1.0f){ value = 1.0f; }
    }
    else if(depth <= dofclosestart)
    {
        //want to move values from 0->0.1 to 0->1.0 and then 1.0->0
        float dofcloseend = 5.0f;
        value = (((depth-0)*((dofcloseend-0.0)/(dofclosestart-0)))+0);
        if(value > 1.0f){ value = 1.0f; }
        value = 1.0f-value; 
    }

    //value is now between 0->1
    color += glow;
    color = (color*(1-value))+(colordof*value);

    //FOG
    float fog = 0;
    float fogstart = 0.5f;    //how far from camera the blurring gradient starts
    float fogend = 1.0f;    //gradient from normal->blurred, higher = quicker
    if(depth >= fogstart)
    {
        //move from fogstart->1.0 to 0->fogend
        fog = (((depth-fogstart)*((fogend-0.0)/(1.0-fogstart)))+0.0);
        if(fog > 1.0f)
        {
            fog = 1.0f;
        }
    }    
    fog = (1-fog);


    float4 final = color*fog;
    final.w = 1.0f;
    return final;
}