//////////////////////////////////////////////////////////////////////////////
//DEPTH OF FIELD
//////////////////////////////////////////////////////////////////////////////

//note: depth is from 0->1.0 (near->farplane)
float offset = 1.0f/1024.0f;
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

float value = 0;
float dofstart = 0.3f;	//how far from camera the blurring gradient starts
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

//////////////////////////////////////////////////////////////////////////////
//SHARPENING
//////////////////////////////////////////////////////////////////////////////

float4 vColor = tex2D(BaseSampler, Input.TexCoord);
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

//////////////////////////////////////////////////////////////////////////////
//FOG
//////////////////////////////////////////////////////////////////////////////	
//note: depth is from 0->1.0 (near->farplane)

float fog = 0;
float fogstart = 0.8f;	//how far from camera the blurring gradient starts
float fogend = 1.0f;	//gradient from normal->blurred, higher = quicker
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

//////////////////////////////////////////////////////////////////////////////
//ANTIALIASING
//////////////////////////////////////////////////////////////////////////////
/*
 -------------------------------------------------------------
| FINAL PIXEL += WEIGHTING * SAMPLED PIXEL AROUND FINAL PIXEL |
 -------------------------------------------------------------

===========================================================================
SUPERSAMPLING TECHNIQUES
===========================================================================

DOWNSAMPLING/FULL SCENE ANTIALIASING (FSAA): 
• Renders at an increased resolution and resizes down
• By doubling screen size you get 4 samples per pixel

ACCUMULATION BUFFER METHOD
• Screen is rendered 4 times each with view moved by half a pixel in x/y
• Screens summed up in accumulation buffer and averaged (/4)

MULTISAMPLING
• Optimized supersampling where some components are not supersampled
• Downside is edges of alpha objects are still aliased

===========================================================================
ANTIALIASING SAMPLING PATTERNS
===========================================================================

ADAPTIVE SAMPLING: 
each pixel is averaged with the pixel's around it

GRID SAMPLING: 
use on final texture and blur pixels with sharp changes from neighbours

RANDOM SAMPLING: 
randomly samples pixels around center pixel; some areas too little/too much this way

POISSON DISC SAMPLING: 
random sampling with additional checks to whether samples are too close to each other
