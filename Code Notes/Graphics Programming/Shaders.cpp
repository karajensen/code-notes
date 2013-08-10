//////////////////////////////////////////////////////////////////////////////
//SHADER VARIABLES
//////////////////////////////////////////////////////////////////////////////

//GLSL VARIABLE TYPES
//Sections can be accessed via xyzw/rgba
float, int
vec2, vec3, vec4
mat3, mat4

//HLSL VARIABLE TYPES
//Sections can be accessed via xyzw/rgba
float, int
float2, float3, float4 
float4x4

//////////////////////////////////////////////////////////////////////////////
//GLSL SHADER INTRINSICS
//////////////////////////////////////////////////////////////////////////////

mix(a,b,c)              // c == 0 ? a : b, interpolates for other values
step(a,b)               // a > b ? 0.0 : 1.0
length(vector)          // Length of a vector
texture2D(Sampler, uvs) // Query from a texture
normalize(vector)       // Normalizes a vector
pow(1.0f, 3.0f)         // Calculates 1³
max(a,b)                // Chooses max of a and b
dot(a,b)                // Dots two vectors

gl_TexCoord[0]
gl_Position
gl_Vertex                      // 4D vertex position
gl_Normal                      // 3D vertex normal
gl_Color                       // 4D vertex color
gl_ModelViewMatrix             // 4x4 world-view matrix.
gl_ModelViewProjectionMatrix   // 4x4 world-view-projection matrix.
gl_NormalMatrix                // 3x3 inverse transpose world-view matrix
gl_MultiTexCoord0              // Can go up to x
gl_FragColor                   // 4D final color values
gl_FragDepth                   // float with final depth value

//Internal Light Array
gl_LightSource[i]
vec4 ambient;             
vec4 diffuse;             
vec4 specular;            
vec4 position;            
vec3 spotDirection;       
float spotExponent;       
float spotCutoff;         
float spotCosCutoff; // cos(spotCutoff)
float constantAttenuation; 
float linearAttenuation;   
float quadraticAttenuation;

//////////////////////////////////////////////////////////////////////////////
//HLSL SHADER INTRINSICS
//////////////////////////////////////////////////////////////////////////////

mul()           // Multiplies two matrices
sin()           // Calculates sine of an angle (in radians).
cos()           // Calculates cosine of an angle (in radians).
pow(1.0f, 3.0f) // Calculates 1³
normalize()     // Normalizes a vector
max(x,y)        // Selects max of x and y
reflect()       // Calculates the ref vector, based on the pos of the camera.
refract()       // Same as reflect, but bends the vector

float4x4 World                 : World;
float4x4 WorldViewProjection   : WorldViewProjection;
float4x4 WorldInvTrans         : WorldInverseTranspose;

//////////////////////////////////////////////////////////////////////////////
//TEXTURING
//////////////////////////////////////////////////////////////////////////////

//HLSL
Texture DiffuseTexture;
sampler TextureSampler = sampler_state 
{ 
    texture = <DiffuseTexture>; 
    magfilter = LINEAR; 
    minfilter = LINEAR; 
    mipfilter = LINEAR; 
    AddressU = WRAP; 
    AddressV = WRAP; 
};
float4 Texture = tex2D(TextureSampler, input.UV);

//GLSL:
uniform sampler2D TextureSampler;
vec4 Texture = texture2D(TextureSampler, gl_TexCoord[0].st);

//////////////////////////////////////////////////////////////////////////////
//NORMAL MAPPING
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------
//TANGENT SPACE NORMAL MAPPING
//----------------------------------------------------------------
//Change range (0,1) to (-0.5,0.5) 
//Stored in red/blue channels

 //HLSL:
 float3 bump = bumpdepth*(tex2D(BumpSampler, input.UV).rgb - 0.5)
 input.Normal = normalize(input.Normal + bump.x*input.Tangent + bump.y*input.Binormal);

 //GLSL:
 vec3 bump = bumpdepth*(texture2D(BumpSampler, gl_TexCoord[0].st).xyz - 0.5);
 vec3 normNormal = normalize(Normal + bump.x*Tangent + bump.y*Binormal);

//----------------------------------------------------------------
//OBJECT SPACE NORMAL MAPPING
//----------------------------------------------------------------
//Change range (0,1) to (-1,1)
//Stored in red/blue/green channels

 //HLSL:
 float3 bump = bumpdepth*((tex2D(BumpSampler, input.UV).rgb * 2.0) - 1.0);
 input.Normal = normalize(bump);                                     

//////////////////////////////////////////////////////////////////////////////
//ATTENUATION
//////////////////////////////////////////////////////////////////////////////

//Value between 0 and 1 represents how light loses intensity over distance
//Multiply by Specular/Diffuse models
//LightRange: Smaller is brighter, larger is darker, att0,att1,att2
//LightDistance(d): Length of LightVector

 //HLSL:
 float d = input.LightVectorLength;                  
 float4 Attenuation = (1.0 / (att0 + att1*d + att2*d*d));  

 //GLSL:
 float d = gl_LightSource[i].constantAttenuation + 
      gl_LightSource[i].linearAttenuation * lightDist +
      gl_LightSource[i].quadraticAttenuation * lightDist * lightDist;
 att = mix(1.0/(d+0.00001), 1.0, step(d,0.0));  //Step = d > 0.0 ? 0.0 : 1.0

//////////////////////////////////////////////////////////////////////////////
//DIFFUSE
//////////////////////////////////////////////////////////////////////////////

 //HLSL:
 float4 diffuse = (dot(input.LightVector, input.Normal) + 1.0) * 0.5; 
 diffuse *= intensity * color * attenuation;   

 //GLSL
 vec4 diffuse = (dot(lightVector, normNormal) + 1.0) * 0.5;
 diffuse *= intensity * gl_LightSource[i].diffuse * attenuation;

//////////////////////////////////////////////////////////////////////////////
//SPECULAR
//////////////////////////////////////////////////////////////////////////////
//Size: Size of highlights (higher = smaller)
//Brightness: Brightness of the highlights (higher = brighter)
   
//HLSL PHONG:
float3 reflectionVector = normalize(reflect(-input.LightVector, input.Normal));
float3 specular = specularIntensity * specularColor * 
                  (pow(saturate(dot(reflectionVector, input.CameraVector)), specularSize));
specular *= attenuation                                               

//HLSL BLINN-PHONG:
float3 halfVector = normalize(input.LightVector + input.CameraVector); 
float3 specular = specularIntensity * specularColor * 
                  (pow(saturate(dot(input.Normal.rbg, halfVector)), specularSize));
specular *= attenuation;       

//GLSL BLINN-PHONG:
vec3 halfVector = normalize(lightVector + normalize(-WorldViewPos));
specular = pow(max(dot(normNormal, halfVector),0.0), specularSize); 
specular *= gl_LightSource[i].specular * specularTexture * attenuation;

//////////////////////////////////////////////////////////////////////////////
//REFLECTIONS/REFRACTIONS
//////////////////////////////////////////////////////////////////////////////

//HLSL:
float3 ReflectionVector = reflect(-input.CameraVector, input.Normal)
float4 Reflection = texCUBE(EnvironSampler, ReflectionVector)       
float3 RefractionVector = refract(-input.CameraVector, input.Normal, RI)
float4 Refractions = texCUBE(EnvironSampler, RefractionVector)           

//////////////////////////////////////////////////////////////////////////////
//GLSL SHADER BODY
//////////////////////////////////////////////////////////////////////////////

//VERTEX SHADER
//uniform = specific to vertex
//varying = has another declaration in fragment shader
varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 VertexNormal;
varying vec3 WorldViewPos;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    WorldViewPos = vec3(gl_ModelViewMatrix * gl_Vertex);
    gl_TexCoord[0] = gl_MultiTexCoord0;
    Normal = gl_NormalMatrix * gl_Normal;
    Tangent = gl_NormalMatrix * gl_MultiTexCoord1.xyz;
    Binormal = gl_NormalMatrix * gl_MultiTexCoord2.xyz;
}

//FRAGMENT SHADER
//uniform = specific to fragment
//varying = has another declaration in vertex shader
uniform sampler2D Sampler0;
uniform sampler2D Sampler1;
uniform sampler2D Sampler2;
varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 WorldViewPos;

void main()
{
    vec4 finalColor = vec4(0,0,0,0);

    // normal texture
    float bumpdepth = 1.0;
    vec3 bump = bumpdepth*(texture2D(Sampler1, gl_TexCoord[0].st).xyz-0.5);
    vec3 normNormal = normalize(Normal + bump.x*Tangent + bump.y*Binormal);

    // diffuse texture
    vec4 texture = texture2D(Sampler0, gl_TexCoord[0].st);

    // specular texture
    vec4 specularTexture = texture2D(Sampler2, gl_TexCoord[0].st);

    float att;
    float specular;
    float diffuse;
    float lightDist;
    vec3 lightVector;
    vec3 halfVector;    

    // for each light
    for(int i = 0; i < MAX_LIGHTS; ++i)
    {
        lightVector = gl_LightSource[i].position.xyz - WorldViewPos;
        lightDist = length(lightVector);
        lightVector = normalize(lightVector);

        // attenuation
        // Step = d > 0.0 ? 0.0 : 1.0
        float d = gl_LightSource[i].constantAttenuation + 
            gl_LightSource[i].linearAttenuation * lightDist +
            gl_LightSource[i].quadraticAttenuation * lightDist * lightDist;
        att = mix(1.0/(d+0.00001), 1.0, step(d,0.0));
        
        // diffuse
        diffuse = (dot(lightVector,normNormal) + 1.0) * 0.5;
        finalColor += diffuse * gl_LightSource[i].diffuse * att;
        
        // specular
        halfVector = normalize(lightVector + normalize(-WorldViewPos));
        specular = pow(max(dot(normNormal,halfVector),0.0),5.0); //gl_FrontMaterial.shininess
        finalColor += specular * gl_LightSource[i].specular * specularTexture * att;
    }

    gl_FragColor = finalColor*texture;
    gl_FragColor.a = texture.a;
}

//////////////////////////////////////////////////////////////////////////////
//HLSL SHADER BODY
//////////////////////////////////////////////////////////////////////////////

float4x4 World                  : World;
float4x4 WorldViewProjection    : WorldViewProjection;
float4x4 WorldInvTrans          : WorldInverseTranspose;

float BumpDepth;
float3 CameraPos;
float3 LightPos;
float AmbientIntensity;     
float4 AmbientColor;
float DiffuseIntensity;     
float4 DiffuseColor;
float SpecularIntensity;    
float4 SpecularColor;       
float SpecularSize;

Texture DiffuseTexture;
sampler ColorSampler = sampler_state 
{ 
    texture = <DiffuseTexture>; 
    magfilter = LINEAR; 
    minfilter = LINEAR; 
    mipfilter = LINEAR; 
    AddressU = WRAP; 
    AddressV = WRAP; 
};

Texture BumpTexture;
sampler BumpSampler = sampler_state 
{ 
    texture = <BumpTexture>; 
    magfilter = LINEAR; 
    minfilter = LINEAR; 
    mipfilter = LINEAR; 
    AddressU = WRAP; 
    AddressV = WRAP; 
};

Texture EnvTexture;
sampler EnvSampler = sampler_state 
{ 
    texture = <EnvTexture>; 
    magfilter = LINEAR; 
    minfilter = LINEAR; 
    mipfilter = LINEAR; 
    AddressU = CLAMP; 
    AddressV = CLAMP; 
};
struct VS_OUTPUT
{
    float4 Pos           : POSITION; 
    float2 UV            : TEXCOORD0;
    float3 Normal        : TEXCOORD1;
    float3 LightVector   : TEXCOORD2;
    float3 CameraVector  : TEXCOORD3;
    float3 Tangent       : TEXCOORD4;
    float3 Binormal      : TEXCOORD5;
};

//VERTEX SHADER
VS_OUTPUT VShader(float4 inPos      : POSITION, 
                  float3 inNormal   : NORMAL,
                  float2 inUV       : TEXCOORD0,
                  float3 inTangent  : TANGENT0,
                  float3 inBinormal : BINORMAL0 )
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    output.Pos = mul(inPos, WorldViewProjection); 
    float3 PosWorld = mul(inPos, World); 
  
    output.Normal = mul(inNormal,WorldInvTrans);
    output.Tangent = mul(inTangent,WorldInvTrans);
    output.Binormal = mul(inBinormal,WorldInvTrans);
    output.LightVector = LightPos - PosWorld;
    output.CameraVector = CameraPos - PosWorld;
    output.UV = inUV;

    return output;
}

//PIXEL SHADER
float4 PShader(VS_OUTPUT input) : COLOR0
{ 
    float2 bump = BumpDepth * (tex2D(BumpSampler, input.UV).xy - 0.5);
    input.Normal = normalize(input.Normal + bump.x * input.Tangent + bump.y * input.Binormal);

    input.LightVector = normalize(input.LightVector);
    input.CameraVector = normalize(input.CameraVector);
    
    float3 halfVector = -normalize(input.LightVector + input.CameraVector);                                         
    float3 specular = SpecularIntensity * SpecularColor * 
        (pow(saturate(dot(input.Normal.rbg, halfVector)), SpecularSize));

    float3 diffuse = DiffuseIntensity * DiffuseColor.rgb * 
        (dot(input.LightVector, input.Normal.xyz)+1)*0.5; //Brings into range 0-1

    float4 color = tex2D(ColorSampler, input.UV);
    float3 ambient = AmbientIntensity * AmbientColor;

    float3 reflection = texCUBE(EnvironSampler, -reflect(input.CameraVector, input.Normal.xyz)).rgb;

    return float4(float3(color.rgb*reflection.rgb* (ambient + diffuse + specular))), color.a);
}

technique MAIN
{
    pass Pass0
    {
        LIGHTING = TRUE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CULLMODE = NONE; //Can have: CCW,CW,NONE     

        //alpha blending
        AlphaBlendEnable = TRUE;    
        SrcBlend = SrcAlpha;        
        DestBlend = InvSrcAlpha;    
                                
        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();
    }
}

//////////////////////////////////////////////////////////////////////////////
//VERTEX SHADER ASSEMBLY
//////////////////////////////////////////////////////////////////////////////

//INPUT REGISTERS
v0-v15    INPUT REGISTER             //sends vertex data (position,UVs,normals)
r0-r11    TEMP REGISTER              //holds temporary data/results
c0-c255   CONSTANT FLOAT REGISTER    //variables sent into the shader
a0        ADDRESS REGISTER           
b0-b15    CONSTANT BOOLEAN REGISTER  //store results of logic flow
i0-i15    CONSTANT INTEGER REGISTER  //used by loop/rep 
aL        LOOP COUNTER REGISTER      //store loop counter
                                     
//OUTPUT REGISTERS                   
oPos      POSITION REGISTER          //outputs position
oFog      FOG REGISTER               //outputs fog value
oPts      POINT SIZE REGISTER        //determines how each reg behaves
oD0-oD1   COLOR REGISTER             //0 is diffuse, 1 is specular output
oT0-oT8   TEX COORDINATE REGISTER    //outputs texture coordinates
                                      
//VERTEX INSTRUCTIONS
dp4 dest, src0, src01 //float4 dot product
mov dest, src //move source to destination

//Passing in vertex data
dcl_position v0
dcl_texcoord v1

//Multiplying world matrix with position
dp4 oPos.x, c0, v0
dp4 oPos.y, c1, v0
dp4 oPos.z, c2, v0
dp4 oPos.w, c3, v0

//Saving UVs
mov oT0.xy, v1

//////////////////////////////////////////////////////////////////////////////
//PIXEL SHADER ASSEMBLY
//////////////////////////////////////////////////////////////////////////////

//INPUT REGISTERS
v0-v1      INPUT COLOR REGISTER        //vertex color passed in
r0-r12/32  TEMP REGISTER               //holds temporary datas
c0-c255    CONSTANT FLOAT REGISTER     //variables sent into the shader
b0-b15     CONSTANT BOOLEAN REGISTER   //store results of logic flow
i0-i15     CONSTANT INTEGER REGISTER   //used by loop/rep 
t0-t07     TEX COORDINATE REGISTER     //contains texture coordinates
s0-s15     SAMPLER REGISTER            //stores texture file to sample
p0         PREDICATE REGISTER

//OUTPUT REGISTERS
oC0-3   OUTPUT COLOR REGISTER  //determines which render target color outputs to
oDepth  OUTPUT DEPTH REGISTER  //outputs a depth value used with testing

//PIXEL INSTRUCTIONS
dcl_2d s0 //Declare a pixel shader sampler.
texld dst, src0, src1 //Sample from a texture

//Retrieving UV coordinates
dcl t0.xy 

//Sample from a texture
dcl_2d s0
texld r0, t0, s0

//Send final color
mov oC0, r0