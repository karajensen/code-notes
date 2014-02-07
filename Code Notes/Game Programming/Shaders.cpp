////////////////////////////////////////////////////////////////////////////////////////////
//SHADERS
////////////////////////////////////////////////////////////////////////////////////////////

//GLSL VARIABLE TYPES
//Sections can be accessed via xyzw/rgba
float, int, vec2, vec3, vec4, mat3, mat4, half

//HLSL VARIABLE TYPES
//Sections can be accessed via xyzw/rgba
float, int, float2, float3, float4, float4x4, half

//SHADER REGISTERS
//Constant registers: lower-latency access and more frequent updates from the CPU
//Texture registers: perform better for arbitrarily indexed data
//shader model 2.0 allows 256 constant registers. Application itself will use some of these
float myFloat; //each register is a float4 (float, float2 etc will take up whole register)
float myArray[100] //to save space, pack arrays as float4
float4 myArray[25]; float data = myArray[index/4][index%4];

////////////////////////////////////////////////////////////////////////////////////////////
//OPTIMISATIONS
////////////////////////////////////////////////////////////////////////////////////////////









////////////////////////////////////////////////////////////////////////////////////////////
//GLSL SHADER INTRINSICS
////////////////////////////////////////////////////////////////////////////////////////////

mix(a,b,c)              // c == 0 ? a : b, interpolates for other values
step(a,b)               // a > b ? 0.0 : 1.0
length(vector)          // Length of a vector
texture2D(Sampler, uvs) // Query from a texture
normalize(vector)       // Normalizes a vector
pow(1.0f, 3.0f)         // Calculates 1³
max(a,b)                // Chooses max of a and b
dot(a,b)                // Dots two vectors
abs(a)                  // magnitude of value

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

////////////////////////////////////////////////////////////////////////////////////////////
//HLSL SHADER INTRINSICS
////////////////////////////////////////////////////////////////////////////////////////////

mul()             // Multiplies two matrices
sin()             // Calculates sine of an angle (in radians).
cos()             // Calculates cosine of an angle (in radians).
pow(1.0f, 3.0f)   // Calculates 1³
normalize()       // Normalizes a vector
max(x,y)          // Selects max of x and y
reflect()         // Calculates the ref vector, based on the pos of the camera.
refract()         // Same as reflect, but bends the vector

float4x4 World                 : World;
float4x4 WorldViewProjection   : WorldViewProjection;
float4x4 WorldInvTrans         : WorldInverseTranspose;

////////////////////////////////////////////////////////////////////////////////////////////
//TEXTURING
////////////////////////////////////////////////////////////////////////////////////////////

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

//GLSL
uniform sampler2D TextureSampler;
vec4 Texture = texture2D(TextureSampler, gl_TexCoord[0].st);

////////////////////////////////////////////////////////////////////////////////////////////
//NORMAL MAPPING
////////////////////////////////////////////////////////////////////////////////////////////

//HLSL TANGENT SPACE NORMAL MAPPING (red/blue)
float3 bump = bumpdepth*(tex2D(BumpSampler, input.UV).rgb - 0.5)
input.Normal = normalize(input.Normal + bump.x*input.Tangent + bump.y*input.Binormal);

//HLSL OBJECT SPACE NORMAL MAPPING (rainbow)
float3 bump = bumpdepth*((tex2D(BumpSampler, input.UV).rgb * 2.0) - 1.0);
input.Normal = normalize(bump);             

//GLSL TANGENT SPACE NORMAL MAPPING (red/blue)
vec3 bump = bumpdepth*(texture2D(BumpSampler, gl_TexCoord[0].st).xyz - 0.5);
vec3 normNormal = normalize(Normal + bump.x*Tangent + bump.y*Binormal);
                        
////////////////////////////////////////////////////////////////////////////////////////////
//ATTENUATION
////////////////////////////////////////////////////////////////////////////////////////////

//HLSL
float d = length(LightPos);                
float4 Attenuation = (1.0 / (att0 + att1*d + att2*d*d));  

////////////////////////////////////////////////////////////////////////////////////////////
//DIFFUSE
////////////////////////////////////////////////////////////////////////////////////////////

 //HLSL
 float4 diffuse = (dot(input.LightVector, input.Normal) + 1.0) * 0.5; 
 diffuse *= intensity * color * attenuation;   

 //GLS
 vec4 diffuse = (dot(lightVector, normNormal) + 1.0) * 0.5;
 diffuse *= intensity * gl_LightSource[i].diffuse * attenuation;

////////////////////////////////////////////////////////////////////////////////////////////
//SPECULAR
////////////////////////////////////////////////////////////////////////////////////////////
//Size: Size of highlights (higher = smaller)
//Brightness: Brightness of the highlights (higher = brighter)
   
//HLSL PHONG
float3 reflectionVector = normalize(reflect(-input.LightVector, input.Normal));
float3 specular = specularIntensity * specularColor * 
                  (pow(saturate(dot(reflectionVector, input.CameraVector)), specularSize));
                                         

//HLSL BLINN-PHONG
float3 halfVector = normalize(input.LightVector + input.CameraVector); 
float3 specular = specularIntensity * specularColor * 
                  (pow(saturate(dot(input.Normal.rbg, halfVector)), specularSize));   

//GLSL BLINN-PHONG
vec3 halfVector = normalize(lightVector + normalize(-WorldViewPos));
specular = pow(max(dot(normNormal, halfVector),0.0), specularSize); 
specular *= gl_LightSource[i].specular * specularTexture * attenuation;

////////////////////////////////////////////////////////////////////////////////////////////
//REFLECTIONS/REFRACTIONS
////////////////////////////////////////////////////////////////////////////////////////////

//HLSL
float3 ReflectionVector = reflect(-input.CameraVector, input.Normal)
float4 Reflection = texCUBE(EnvironSampler, ReflectionVector)       
float3 RefractionVector = refract(-input.CameraVector, input.Normal, RI)
float4 Refractions = texCUBE(EnvironSampler, RefractionVector)           

////////////////////////////////////////////////////////////////////////////////////////////
//GLSL SHADER BODY
////////////////////////////////////////////////////////////////////////////////////////////

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
varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 WorldViewPos;

void main()
{
    gl_FragColor = texture2D(Sampler0, gl_TexCoord[0].st);
}

////////////////////////////////////////////////////////////////////////////////////////////
//HLSL SHADER BODY
////////////////////////////////////////////////////////////////////////////////////////////

float4x4 World                  : World;
float4x4 WorldViewProjection    : WorldViewProjection;
float4x4 WorldInvTrans          : WorldInverseTranspose;

float3 CameraPos;
float3 LightPos;

Texture DiffuseTexture;
sampler ColorSampler = sampler_state 
{ 
    texture = <DiffuseTexture>; 
    magfilter = LINEAR; 
    minfilter = LINEAR; 
    mipfilter = LINEAR; 
    AddressU = WRAP;  //CLAMP
    AddressV = WRAP; 
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

float4 PShader(VS_OUTPUT input) : COLOR0
{ 
    return tex2D(ColorSampler, input.UV);
}

technique MAIN
{
    pass Pass0
    {
        LIGHTING = TRUE;
        ZENABLE = TRUE;
        ZWRITEENABLE = TRUE;
        CullMode = NONE; //CCW,CW,NONE     

        DepthBias = 0.0001; //between -1.0 to 1.0 for offsetting shadows/wireframe/decals
        SlopeScaleDepthBias = 0.0;
        FillMode = Wireframe;

        //alpha blending
        AlphaBlendEnable = TRUE;    
        SrcBlend = SrcAlpha;        
        DestBlend = InvSrcAlpha;    
                                
        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//SHADER ASSEMBLY
////////////////////////////////////////////////////////////////////////////////////////////

//VERTEX INPUT REGISTERS
v0-v15    // INPUT REGISTER: sends vertex data (position,UVs,normals)
r0-r11    // TEMP REGISTER: holds temporary data/results
c0-c255   // CONSTANT FLOAT REGISTER: variables sent into the shader
a0        // ADDRESS REGISTER           
b0-b15    // CONSTANT BOOLEAN REGISTER: store results of logic flow
i0-i15    // CONSTANT INTEGER REGISTER: used by loop/rep 
aL        // LOOP COUNTER REGISTER: store loop counter

//PIXEL INPUT REGISTERS
v0-v1      // INPUT COLOR REGISTER: vertex color passed in
r0-r12/32  // TEMP REGISTER: holds temporary datas
c0-c255    // CONSTANT FLOAT REGISTER: variables sent into the shader
b0-b15     // CONSTANT BOOLEAN REGISTER: store results of logic flow
i0-i15     // CONSTANT INTEGER REGISTER: used by loop/rep 
t0-t07     // TEX COORDINATE REGISTER: contains texture coordinates
s0-s15     // SAMPLER REGISTER: stores texture file to sample
p0         // PREDICATE REGISTER

//VERTEX OUTPUT REGISTERS                   
oPos       // POSITION REGISTER: outputs position
oFog       // FOG REGISTER: outputs fog value
oPts       // POINT SIZE REGISTER: determines how each reg behaves
oD0-oD1    // COLOR REGISTER: 0 is diffuse, 1 is specular output
oT0-oT8    // TEX COORDINATE REGISTER: outputs texture coordinates          

//PIXEL OUTPUT REGISTERS
oC0-3      // OUTPUT COLOR REGISTER: determines which render target color outputs to
oDepth     // OUTPUT DEPTH REGISTER: outputs a depth value used with testing

//INSTRUCTIONS
dp4 dest, src0, src01   // float4 dot product
mov dest, src           // move source to destination
dcl_2d s0               // Declare a pixel shader sampler.
texld dst, src0, src1   // Sample from a texture
dcl_position v0         // Passing in vertex position
dcl_texcoord v1         // Passing in vertex textcoord
mov oT0.xy, v1          // Saving UVs in vertex shader
dcl t0.xy               // Retrieving UVs in pixel shader
texld r0, t0, s0        // Sample from a texture
mov oC0, r0             // Send final color in pixel shader