//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADERS
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
-----------------------------------------------------------------------------------------------------
GLSL SHADER               HLSL SHADER    DESCRIPTION
-----------------------------------------------------------------------------------------------------
Vertex                    Vertex         Outputs data for each vertex in mesh
Tessellation Control  	  Hull           Outputs control point data for surfaces
Tessellation Evaluation   Domain         Outputs vertex data from tessellation generator/control points
Geometry                  Geometry       Takes in single primitive, outputs none or more primitives
Fragment                  Pixel          Outputs data for each pixel mesh may contribute to
Compute                   Compute        General-purpose data-parallel processing  

-----------------------------------------------------------------------------------------------------
GRAPHICS API   MODEL   FEATURES          
-----------------------------------------------------------------------------------------------------
DirectX 8.0    1.0    HLSL introduced
DirectX 9.0    2.0    Static flow control
DirectX 9.0c   3.0    Vertex texture lookup, Position/Face/Loop counter/Index input registers
DirectX 10.0   4.0    Geometry shaders, Bit operators, native integers
DirectX 11.0   5.0    Domain/Hull shaders, Compute shaders
OpenGL 2.1     120    GLSL introduced
OpenGL 3.2     150    Geometry shaders   
OpenGL 4.0     400    Both Tessellation shaders
OpenGL 4.3     430    Compute Shaders

-----------------------------------------------------------------------------------------------------
SHADER MODEL    ConstantReg.  TempReg.  InstructSlots  Textures
-----------------------------------------------------------------------------------------------------
HLSL vs1.0      96            12        128            -
HLSL vs2.0      256           12        256            -
HLSL vs3.0      256           32        512            
HLSL vs4.0      65536         4096      4096           
HLSL vs5.0      65536         4096      4096           
HLSL ps1.0      8             2         12             4-6
HLSL ps2.0      32            32        96             16
HLSL ps3.0      224           32        512            16
HLSL ps4.0      65536         4096      ∞              16
HLSL ps5.0      65536         4096      ∞              16

SWIZZLING: Using x/y/z/w to refer to each component
SWIZZLE MASK: Combining components (.xy, .xyz, .xx)
TESSELLATION: Converts low-detail subdivision surfaces into higher-detail primitives

//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADER COMPONENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////s
• CONSTANT REGISTERS: lower-latency access and more frequent updates from the CPU
• TEXTURE REGISTERS: perform better for arbitrarily indexed data
*/

//ASSEMBLY INSTRUCTIONS
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

//VERTEX INPUT REGISTERS
v0-v15     // Input register: sends vertex data (position,UVs,normals)
r0-r11     // Temp register: holds temporary data/results
c0-c255    // Constant float register: variables sent into the shader
a0         // Address register           
b0-b15     // Constant boolean register: store results of logic flow
i0-i15     // Constant integer register: used by loop/rep 
aL         // Loop counter register: store loop counter

//VERTEX OUTPUT REGISTERS                   
oPos       // Position register: outputs position
oFog       // Fog register: outputs fog value
oPts       // Point size register: determines how each reg behaves
oD0-oD1    // Color register: 0 is diffuse, 1 is specular output
oT0-oT8    // Tex coordinate register: outputs texture coordinates       

//PIXEL INPUT REGISTERS
v0-v1      // Input color register: vertex color passed in
r0-r12/32  // Temp register: holds temporary datas
c0-c255    // Constant float register: variables sent into the shader
b0-b15     // Constant boolean register: store results of logic flow
i0-i15     // Constant integer register: used by loop/rep 
t0-t07     // Tex coordinate register: contains texture coordinates
s0-s15     // Sampler register: stores texture file to sample
p0         // Predicate register

//PIXEL OUTPUT REGISTERS
oC0-3      // Output color register: determines which render target color outputs to
oDepth     // Output depth register: outputs a depth value used with testing

//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADER OPTIMIZATIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////

//PACKING ARRAYS AS FLOAT4
//arrays are always packed as float4 even if only using a float
//saves space but can have instruction cost accessing members
float4 myArray[25]; //float myARray[100];
float value = myArray[index/4][index%4];  // Accessing through computation
float value = myArray[index>>2][index&3];
float myArr[100] = (float[100])myArray;   // Does not cast: copies and ineffeciant!

//SAVING SPACE THROUGH CONSTANT CONTAINER
//commonly used constants can be cached
const float4 constants = float4(1.0, 0.0, 0.5, 0.2)

//SUMMING VECTOR COMPONENTS
float sum = myFlt.x + myFlt.y + myFlt.z + myFlt.w; // inefficient
const float4 allOne = vec4(1.0); // faster to use dot to sum
float sum = dot(myFlt4, allOne); 
float sum = dot(myFlt3, allOne.xyz);

//MAD (MULTIPLY THEN ADD)
//usually single-cyle and fast
float4 result = (value / 2.0) + 1.0; // divide may not be optimized to a mad
float4 result = (value * 0.5) + 1.0; // always use multiply in case
float result = 0.5 * (1.0 + value);  // add + multiply may not be optimized to a mad
float result = 0.5 + (0.5 * value);  // always use multiply first then add

//SWIZZLE MASKS
gl_Position.x = in_pos.x; 
gl_Position.y = in_pos.y;
gl_Position.xy = in_pos.xy; // faster than adding both seperately

//SETTING INDIVIDUAL COMPONENTS
float4 finalColour = myColor; //uses temporary float4
finalColour.a = 1.0;
gl_FragColor = finalColour; 
const float2 constants = float2(1.0, 0.0); //instead, use MAD, swizzling and constat container
gl_FragColor = (myColor.xyzw * constants.xxxy) + constants.yyyx;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//HLSL
//////////////////////////////////////////////////////////////////////////////////////////////////////

//VARIABLE TYPES
bool myBool;
int myInt;    //32-bit signed int
half myFlt;   //16-bit float
float myFlt;  //32-bit float
double myDbl; //64-bit double

//VECTOR TYPES
//From n2 to n4 where 'vector' defaults to 4
float4 myFlt /*or*/ float myFlt[4] /*or*/ vector<float,4> myFlt /*or*/ vector myFlt
bool3 myBool /*or*/ bool myBool[3] /*or*/ vector<bool,3> myBool

//MATRIX TYPES
//float nxn where n=[1,4]
float3x4 myMat; /*or*/ matrix<float,3,4>
float2x2 

//ACCESSING COMPONENTS
//Sections can be accessed via xyzw/rgba but not both
//ps2.0- does not have support for chained swizzing
float value = myFlt[0];
float2 value = myFlt.xy;

//INTRINSICS
mul()             // Multiplies two matrices
sin()             // Calculates sine of an angle (in radians).
cos()             // Calculates cosine of an angle (in radians).
pow(1.0f, 3.0f)   // Calculates 1³
normalize()       // Normalizes a vector
max(x,y)          // Selects max of x and y
reflect()         // Calculates the ref vector, based on the pos of the camera.
refract()         // Same as reflect, but bends the vector

//MODEL 3.0- CONSTANT REGISTER PACKING
float myFloat; //each register is a float4 (float, float2 etc will take up whole register)
float myArray[100] //to save space, pack arrays as float4

//MODEL 4.0+ CONSTANT REGISTER PACKING
//Uses cbuffer which automatically packs floats into float4 where possible
cbuffer
{
    float2 myFloat;
    float myFloat;
    //float padding
    float3 myFloat;
    float myArray[10]; //always assigns full float4 for arrays with last entry only float 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//HLSL SHADING
//////////////////////////////////////////////////////////////////////////////////////////////////////

//TEXTURING
//HLSL 3.0-: Textures/samplers bound to each other
//HLSL 4.0+: Textures/samplers seperate objects
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

//TANGENT SPACE NORMAL MAPPING (red/blue)
float3 bump = bumpdepth*(tex2D(BumpSampler, input.UV).rgb - 0.5)
input.Normal = normalize(input.Normal + bump.x*input.Tangent + bump.y*input.Binormal);

//OBJECT SPACE NORMAL MAPPING (rainbow)
float3 bump = bumpdepth*((tex2D(BumpSampler, input.UV).rgb * 2.0) - 1.0);
input.Normal = normalize(bump);             

//ATTENUATION
float d = length(LightPos);                
float4 Attenuation = (1.0 / (att0 + att1*d + att2*d*d));  

//DIFFUSE SHADING
float4 diffuse = (dot(input.LightVector, input.Normal) + 1.0) * 0.5; 
diffuse *= intensity * color * attenuation;   

//SPECULAR PHONG
//Size: Size of highlights (higher = smaller)
//Brightness: Brightness of the highlights (higher = brighter)
float3 reflectionVector = normalize(reflect(-input.LightVector, input.Normal));
float3 specular = specularIntensity * specularColor * 
                  (pow(saturate(dot(reflectionVector, input.CameraVector)), specularSize));
                                        
//SPECULAR BLINN-PHONG
float3 halfVector = normalize(input.LightVector + input.CameraVector); 
float3 specular = specularIntensity * specularColor * 
                  (pow(saturate(dot(input.Normal.rbg, halfVector)), specularSize));   

//REFLECTIONS
float3 ReflectionVector = reflect(-input.CameraVector, input.Normal)
float4 Reflection = texCUBE(EnvironSampler, ReflectionVector)       

//REFRACTIONS
float3 RefractionVector = refract(-input.CameraVector, input.Normal, RI)
float4 Refractions = texCUBE(EnvironSampler, RefractionVector)

//////////////////////////////////////////////////////////////////////////////////////////////////////
//HLSL BODY
//////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////
//GLSL
//////////////////////////////////////////////////////////////////////////////////////////////////////

//VARIABLE TYPES
//Sections can be accessed via xyzw/rgba but not both
float, int, vec2, vec3, vec4, mat3, mat4, half

//INTRINSICS
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
{
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
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//GLSL SHADING
//////////////////////////////////////////////////////////////////////////////////////////////////////

//TEXTURING
uniform sampler2D TextureSampler;
vec4 Texture = texture2D(TextureSampler, gl_TexCoord[0].st);

//TANGENT SPACE NORMAL MAPPING (red/blue)
vec3 bump = bumpdepth*(texture2D(BumpSampler, gl_TexCoord[0].st).xyz - 0.5);
vec3 normNormal = normalize(Normal + bump.x*Tangent + bump.y*Binormal);
                        
//SPECULAR BLINN-PHONG
//Size: Size of highlights (higher = smaller)
//Brightness: Brightness of the highlights (higher = brighter)
vec3 halfVector = normalize(lightVector + normalize(-WorldViewPos));
specular = pow(max(dot(normNormal, halfVector),0.0), specularSize); 
specular *= gl_LightSource[i].specular * specularTexture * attenuation;

//DIFFUSE SHADING
vec4 diffuse = (dot(lightVector, normNormal) + 1.0) * 0.5;
diffuse *= intensity * gl_LightSource[i].diffuse * attenuation; 

//////////////////////////////////////////////////////////////////////////////////////////////////////
//GLSL BODY
//////////////////////////////////////////////////////////////////////////////////////////////////////

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

