//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADERS
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
-----------------------------------------------------------------------------------------------------
GLSL SHADER               HLSL SHADER    DESCRIPTION
-----------------------------------------------------------------------------------------------------
Vertex                    Vertex         Outputs data for each vertex in mesh
Tessellation Control      Hull           Outputs control point data for surfaces
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
HLSL vs2.0      256           12        256            16
HLSL vs3.0      256           32        512            16
HLSL vs4.0      65536         4096      4096           
HLSL vs5.0      65536         4096      4096           
HLSL ps2.0      32            32        96             16
HLSL ps3.0      224           32        512            16
HLSL ps4.0      65536         4096      ∞              
HLSL ps5.0      65536         4096      ∞              

UNIFORM INPUT: Does not change per-vertex or per-pixel, readonly to shader
VARYING INPUT: Change per-vertex/per-pixel
ATTRIBUTES: 'in' values passed to vertex shader; default to varying but can use uniform keyword
CONSTANT TABLE: Holds uniform name, register and size with $ before any uniform attributes
CONSTANT REGISTERS: lower-latency access and more frequent updates from the CPU
TEXTURE REGISTERS: perform better for arbitrarily indexed data

SWIZZLING: Using x/y/z/w to refer to each component
SWIZZLE MASK: Combining components (.xy, .xyz, .xx)
TESSELLATION: Converts low-detail subdivision surfaces into higher-detail primitives

FLOW CONTROL: Use of branching instructions to change the flow of code execution
STATIC FLOW CONTROL: Choose path based on constant variable that cannot be modified during execution
DYNAMIC FLOW CONTROL: Choose path based on dynamic variable that can change during execution
                      Costly as both branches may need to be evaluated and the unused one discarded

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADER ASSEMBLY
//////////////////////////////////////////////////////////////////////////////////////////////////////

//Reference: Learn vertex and pixel shader programming with DX9
GPUShaderAnalyzer.exe ./Input.hlsl -I ./Output.txt -ASIC D3D -profile vs_4_0 -function VShader
GPUShaderAnalyzer.exe ./Input.hlsl -I ./Output.txt -ASIC D3D -profile ps_4_0 -function PShader
GPUShaderAnalyzer.exe ./Input.vert -I ./Output.txt -ASIC IL -profile glsl_vs -function main
GPUShaderAnalyzer.exe ./Input.frag -I ./Output.txt -ASIC IL -profile glsl_fs -function main

_gt // a > b
_ge // a >= b
_eq // a == b
_ne // a != b
_le // a <= b
_lt // a < b

abs                         // Make absolute
add                         // Addition
break_comp                  // Conditinoal break out of loop
break_pred                  // Predicate break out of loop
call                        // Call a function
callnz                      // Function call if doesn't equal zero
callnz_pred                 // Function call if predicate doesn't equal zero
crs                         // Cross product
dcl_2d s0                   // Declare a pixel shader sampler.
dcl_position v0             // Passing in vertex position
dcl_texcoord v1             // Passing in vertex textcoord
dcl t0.xy                   // Retrieving UVs in pixel shader
def c0, 1.0, 2.0, 3.0, 4.0  // Sets c0 with a const float vector
defb b0, true               // Sets b0 with a const boolean
defi i0, 1, 2, 3, 4         // Sets i0 with a const int vector
dp3 dest, src0, src01       // float3 Dot product
dp4 dest, src0, src01       // float4 Dot product
dst                         // Distance vector
exp                         // Exponential full precision
expp                        // Exponential partial
frc dest, src               // Fractional portion of float
if_comp                     // if(comparison)
if_pred                     // if(predicate)
label                       // Address location to jump to
lit                         // Lighting
log                         // Logarithm full precision
logp                        // Logarithm partial
lrp                         // Linear interpolation
mad                         // Multiply then add
max                         // Maximum
min                         // Minimum
mov dest, src               // Copy source register to destination register
mov oC0, r0                 // Send final color in pixel shader
mov oT0.xy, v1              // Saving UVs in vertex shader
mova a0, c0                 // Copy float-pt register to address register and rounds to int
mul                         // multiply
nop                         // No operation
nrm                         // Normalize
pow                         // Power of
rep                         // start re-endrep block (while loop)
ret                         // Return from function
rcp                         // Reciprocal (1/x)
rsq                         // Reciprocal square root
sge dest, a, b              // Set: dest = a >= b ? 1.0 : 0.0
sgn                         // Sign
sincos                      // Sine and cosine
slt dest, a, b              // Set: dest = a < b ? 1.0 : 0.0
sub                         // Subtraction
texldl                      // Sample from texture with mipmaps
texld dst, src0, src1       // Sample from texture
vs.2.0                      // Version and main shader entry point

//VERTEX INPUT REGISTERS
v0-v15     // Input register: sends vertex attributes (position, UVs, normals)
r0-r11     // Temp/scratch register: holds temporary vertex data/results
c0-c255    // Constant float register: variables sent into the shader       
b0-b15     // Constant boolean register: quad boolean vectors, store results of logic flow
i0-i15     // Constant integer register: quad integer vectors, used by loop/rep 
aL         // Loop counter register: store loop counter

//VERTEX OUTPUT REGISTERS                   
a0         // Write-only Address register used as index offset into table of registers
oPos       // Position register: outputs position
oFog       // Fog register: outputs fog value
oPts       // Point size register
oD0-oD1    // Color register: 0 is diffuse, 1 is specular output
oT0-oT8    // Texture coordinate register

//PIXEL INPUT REGISTERS
v0-v1      // Input color register: vertex color passed in (diffuse = 0, specular = 1)
vFace      // Face register
vPos       // Position register
r0-r12/32  // Temp/scratch register: holds temporary pixel data/results
t0-t07     // Tex coordinate register: contains texture coordinates
s0-s15     // Sampler register: readonly, stores texture file to sample

//PIXEL OUTPUT REGISTERS
oC0-3      // Output color register: determines which render target color outputs to
oDepth     // Output depth register: outputs a depth value used with testing

//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADER OPTIMIZATIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////

//• Floats faster for calculations, integers faster for indexing
// • Use half instead of float where strict precision isn't important
//• Compiler may optimize isnan() and isfinite() calls
//• NaN * 0 = 0 not NaN except with precise keyword
//• Use of static keyword for global bools only evaluates the one path instead of both
//• If missing components in vertex stream, auto sets z/y to 0.0 and w to 1.0
//• Normalize normals in pixel shader as may not be still normalized after vertex shader interpolation
//• Texture read is fastest when accessing adjacent pixels due to cache
//• Code that doesn't rely on texture read can be auto moved by compilier in front of a read to parallelize

//PACKING ARRAYS/VALUES AS FLOAT4
//arrays are always packed as float4 even if only using a float
//saves space but can have instruction cost accessing members
float4 myArray[25]; //float myARray[100];
float value = myArray[index/4][index%4];  //Accessing through computation
float value = myArray[index>>2][index&3];
float myArr[100] = (float[100])myArray;   //Does not cast: copies and ineffeciant!
const float4 constants = float4(1.0, 0.0, 0.5, 0.2) //commonly used constants can be cached

//VECTORISE OPERATIONS
float a,b,c,d;
a = x + 1;            
b = x + 2;     =>     float4 vec;
c = x + 3;            vec = x + float4(1,2,3,4)
d = x + 4;

//SUMMING VECTOR COMPONENTS
float sum = a + b + c + d; //inefficient
float sum = myFlt.x + myFlt.y + myFlt.z + myFlt.w; //inefficient
float sum = dot(myFlt4, vec4(1.0)); //faster to use dot to sum
float sum = dot(myFlt3, vec4(1.0).xyz);
float sum = dot(vec4(a,b,c,d), vec4(1.0));

//SETTING VECTOR LENGTH
50.0 * normalize(vec)  =>  vec * (50.0 * rsqrt(dot(vec, vec))) //uses less instructions

//MAD (MULTIPLY THEN ADD)
//usually single-cyle and fast
(x / 2.0) + 1.0        =>  (x * 0.5) + 1.0 //divide may not be optimized, use multiply if possible
x * (1.0 - x)          =>  -(x * x) + x //expand out brackets that require add before mul
(x + a) / b            =>  x * (1.0 / b) + (a / b) //expand out brackets
x += (a * b) + (c * d) =>  x += a * b; x += c * b //move to seperate lines

//BUILT-IN-FUNCTIONS
a / (x * b)       =>  rcp(x) * a / b //a / b implemented as a * rcp(b) but not always.
(x + a) / x       =>  a * rcp(x) + 1 //Check if explicitly using rcp gives better results
1.0 / sqrt(x)     =>  rsqrt(x) //1.0/sqrt(x) maps to rcp(sqrt(x)): instead use single instruction
abs(x * y)        =>  abs(x) * abs(y)  //use abs() on input or it forces an extra MOV 
-(x * y)          =>  -x * y //use - on input or it forces an extra MOV 
1.0 - saturate(x) =>  saturate(1.0 - x) //use saturate() on output or it forces an extra MOV
min(x) or max(x)  =>  saturate(x) //saturate() cheaper than min or max
step() or sign()  =>  if {} else {} //conditional assigment faster

//SWIZZLE MASKS
gl_Position.x = in_pos.x; 
gl_Position.y = in_pos.y;
gl_Position.xy = in_pos.xy; //faster than adding both seperately

//SETTING INDIVIDUAL COMPONENTS
//uses temporary float4
float4 finalColour = myColor; 
finalColour.a = 1.0;
gl_FragColor = finalColour; 
//instead, use MAD, swizzling and constant container
const float2 constants = float2(1.0, 0.0); 
gl_FragColor = (myColor.xyzw * constants.xxxy) + constants.yyyx;


//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADING EQUATIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////

vertToLight     // vector from vertex to position (point light) or light direction (direction light)
vertToCamera    // vector from vertex to camera position

//TANGENT SPACE NORMAL MAPPING (red/blue)
float3 bump = bumpdepth*(tex2D(BumpSampler, uvs).rgb - 0.5);
normal = normalize(normal + bump.x * tangent + bump.y * binormal);

//OBJECT SPACE NORMAL MAPPING (rainbow)
float3 bump = bumpdepth*((tex2D(BumpSampler, uvs).rgb * 2.0) - 1.0);
normal = normalize(bump);             

//ATTENUATION
float d = length(lightPosition);                
float attenuation = (1.0 / (att0 + att1*d + att2*d*d));  

//DIFFUSE SHADING
float3 diffuse = (dot(vertToLight, normal) + 1.0) * 0.5; 

//SPECULAR PHONG
//Size: Size of highlights (higher = smaller)
//Brightness: Brightness of the highlights (higher = brighter)
float3 reflection = normalize(reflect(-vertToLight, normal));
float3 specular = intensity * colour * (pow(saturate(dot(reflection, vertToCamera)), size));
                                        
//SPECULAR BLINN-PHONG
float3 halfVector = normalize(vertToLight + vertToCamera); 
float3 specular = intensity * colour * (pow(saturate(dot(normal, halfVector)), size));   

//REFRACTIONS
float3 refraction = refract(-vertToCamera, normal, RI);
float4 refract = texCUBE(EnvironmentSampler, refraction);

//REFLECTIONS
//Schlick's Fresnal Approximation: max(0, min(1, bias + scale * pow(1.0 + dot(I,N))))
//Bias should be small, power around 5
float fresnal = saturate(bias + scale * pow(1.0 + dot(-vertToCamera, normal), power));
float3 reflection = reflect(-vertToCamera, normal);
float4 reflect = texCUBE(EnvironmentSampler, reflection) * intensity * fresnal;

//FINAL COLOUR
float4 colour = saturate((diffuse * attenuation) + (specular * attenuation) + reflect);

//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADER SYNTAX/LANGUAGES
//////////////////////////////////////////////////////////////////////////////////////////////////////

//===================================================================================================
//GLSL BASIC TYPES                  HLSL BASIC TYPES
//===================================================================================================
bool                                bool
float                               float/float1            //32-bit float  
mediump float                       half                    //16-bit float
double                              double                  //64-bit double
int                                 int                     //32-bit signed int
uint                                uint                    //unsigned integer
++myInt                             ++myInt                 //supports pre/post increment
float(x)                            (float)x                //May copy instead of cast
struct MyStruct {};                 struct MyStruct {};

// VECTORS ------------------------------------------------------------------------------------------
vec2 / vec3 / vec4                  float2 / float3 / float4
ivec2 / ivec3 / ivec4               int2 / int3 / int4
uvec2 / uvec3 / uvec4               uint2 / uint3 / uint4
bvec2 / bvec3 / bvec4               bool2 / bool3 / bool4
vec3 vec = vec3(0,0,0);             float3 vec = float3(0,0,0);
----                                float3 vec = {0,0,0};
vec4 vec = vec4(vec, 0);            float4 vec = float4(vec, 0);

// ARRAYS -------------------------------------------------------------------------------------------
float vec[3]; / float[3] vec;       float vec[3]; / vector<float,3> vec;
float vec[3] = float[](0,0,0);      float vec[3] = {0,0,0};
vec[0] = 0;                         vec[0] = 0;
vec2 a = b.xy;                      float2 a = b.xy;  //sections can be accessed via xyzw/rgba/stpq but can't be mixed

// MATRICES -----------------------------------------------------------------------------------------
mat3 / mat4 / mat3x4                float3x3 / float4x4 / float3x4 / matrix<float,3,4> mat;
mat2x2 mat = mat2x2(0,0,0,0);       float2x2 mat = float2x2(0,0,0,0);
----                                float2x2 mat = {0,0,0,0};
float value = mat[0][1];            float value = mat[0][1];
----                                float value = mat.m00;
----                                float value = mat._11;
----                                float2 value = mat._11_22;

//===================================================================================================
//GLSL INTRINSICS      HLSL INTRINSICS
//===================================================================================================
matrix * matrix       mul(matrix, matrix)
vector * matrix       mul(vector, matrix)
inversesqrt(x)        rsqrt(x)              // Returns 1 / sqrt(x)
mix(x,y,s)            lerp(x,y,s)           // linear interpolation: x*(1-s) + y*s, s == 0 then x, s == 1 then y
dFdx(x)               ddx(x)                // Returns the partial derivative of x with respect to the screen-space x-coordinate
dFdy(x)               ddy(x)                // Returns the partial derivative of x with respect to the screen-space y-coordinate
clamp(x, 0, 1)        saturate(x)           // clamps value between 0 and 1, HLSL version works on vectors
-                     isfinite(x)           // returns true if x is a finite number
-                     mad(a,b,c)            // Performs mad assembly operation: a * b + c (SM5)
-                     abort()               // Terminates the current draw or dispatch call being executed (SM4+)
roundEven(x)         -                      // rounds to nearest integer, 0.5 rounds to nearest even int

//===================================================================================================
//SHARED INTRINSICS
//===================================================================================================
abs(a)                  // magnitude of value
all(v)                  // returns true if all components in vector are true
any(v)                  // return true if any component is true
cross(a,b)              // Crosses two vector
clamp(x, min, max)      // returns clamped value
ceil(x)                 // rounds upwards to nearest int
determinant(mat)        // returns determinant of matrix
degrees(rad)            // converts rad to degrees
dot(a,b)                // dots two vectors
distance(a,b)           // distance between two points
floor(x)                // rounds downwards to nearest int
fract(x)                // returns fractional part of x
fwidth(a)               // Returns abs(ddx(x)) + abs(ddy(x))
isinf(x)                // return true if pos or neg infinity
isnan(x)                // return true if not a number
inverse(mat)            // returns inverse of matrix
length(x)               // Length of a vector
max(x,y)                // returns maximum value
min(x,y)                // returns minimum value
modf(x, intPart)        // returns fractional part, stores int part
normalize(x)            // Returns the normalized vector
pow(1.0f, 3.0f)         // Calculates 1³
radians(deg)            // converts degrees to radians
reflect(x, norm)        // reflects vector along normal
round(x)                // rounds to nearest integer
sign(x)                 // Returns the sign of x
step(a,b)               // a > b ? 0.0 : 1.0
smoothstep(min,max,x)   // clamp((x-min)/(max-min), 0.0, 1.0)
sqrt(x)                 // Square root
trunc(x)                // removes the fractional part of x
transpose(mat)          // creates transpose of matrix
sin(angle)              // angle in radians
cos(angle)              // angle in radians
tan(angle)              // angle in radians
asin(x)
acos(x)
atan(y,x) /*or*/ atan(y/x)

//===================================================================================================
//VARIABLE PREFIXES
//===================================================================================================

// HLSL PREFIXES
float myGlobalFlt;       // global variable defaults to uniform/extern
const float myFlt = 4;   // variable cannot be modified by shader (can be modfied by application if visible)
static float myGlobal;   // outside main(): variable will not be exposed outside shader
static float myLocal;    // inside main(): value will persist across multiple calls to the shader
extern float myGlobal;   // variable is exposed outside shader
uniform                  // Does not change per-vertex or per-pixel, links to outside application, readonly
shared                   // allows variable to be accessed accross mutliple .fx files
volatile                 // hints that it will be modified often, only global variables

//GLSL PREFIXES
const float myFlt = 4;  // variable cannot be modified
uniform                 // Does not change per-vertex or per-pixel, links to outside application, readonly
varying                 // Changes per-vertex/per-pixel

//////////////////////////////////////////////////////////////////////////////////////////////////////
//HLSL SHADERS
//////////////////////////////////////////////////////////////////////////////////////////////////////

//SHADER MODEL 3.0- SAMPLERS
Texture DiffuseTexture;
sampler ColorSampler = sampler_state 
{ 
    texture = <DiffuseTexture>; 
    magfilter = LINEAR; 
    minfilter = LINEAR; 
    mipfilter = LINEAR; 
    AddressU = WRAP;  //can have CLAMP
    AddressV = WRAP; 
};

//SHADER MODEL 4.0+ SAMPLERS
SamplerState MySampler;
Texture2D MyTexture;
float4 value = MyTexture.Sample(MySampler, input.uvs);

//SHADER MODEL 4.0+ MULTI-SAMPLERS
Texture2DMS<float4,SAMPLES> MySampler : register(t0);
int3 uvs = int3(input.uvs.x * WINDOW_WIDTH, input.uvs.y * WINDOW_HEIGHT, 0);
float4 value = float4(0.0, 0.0, 0.0, 0.0);
for (int i = 0; i < SAMPLES; ++i)
{
    value += MySampler.Load(uvs, i);
}
value *= (1.0 / SAMPLES);

//==============================================================================
// SHADER BODY
//==============================================================================

//SHADER MODEL 3.0- CONSTANTS
float myFloat; //each register is a float4 (float, float2 etc will take up whole register)
float myArray[100] //to save space, pack arrays as float4
float4x4 World                  : World;
float4x4 WorldViewProjection    : WorldViewProjection;
float4x4 WorldInvTrans          : WorldInverseTranspose;
float3 CameraPosition;
float3 LightPosition;

//SHADER MODEL 4.0+ CONSTANTS
//can be used by both vertex/pixel shader
//automatically packs floats into float4 where possible
cbuffer ConstantBuffer
{
    float4x4 viewProjection;
    float4x4 viewInvTranspose;
    float3 lightPosition;
    //float padding
    float myArray[10]; //always assigns full float4 for arrays with last entry only float 
}

struct VS_OUTPUT
{
    float4 Position      : POSITION;    // SHADER MODEL 3.0-
    float4 Position      : SV_POSITION; // SHADER MODEL 4.0+
    float2 UV            : TEXCOORD0;
    float3 Normal        : TEXCOORD1;
    float3 VertToLight   : TEXCOORD2;
    float3 VertToCamera  : TEXCOORD3;
    float3 Tangent       : TEXCOORD4;
    float3 Binormal      : TEXCOORD5;
    float3 PositionWorld : TEXCOORD6;
    float4 Colour        : COLOR;
};

struct PS_OUTPUT // Optional for multiple render targets
{
    float4 colour1 : SV_TARGET0;
    float4 colour2 : SV_TARGET1;
};

VS_OUTPUT VShader(float4 inPos      : POSITION, 
                  float3 inNormal   : NORMAL,
                  float2 inUV       : TEXCOORD0,
                  float3 inTangent  : TANGENT0,
                  float3 inBinormal : BINORMAL0 )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Position = mul(inPos, WorldViewProjection); 
    output.PositionWorld = mul(inPos, World); 
    output.Normal = mul(inNormal, WorldInvTrans);
    output.Tangent = mul(inTangent, WorldInvTrans);
    output.Binormal = mul(inBinormal, WorldInvTrans);
    output.VertToLight = LightPosition - output.PositionWorld;
    output.VertToCamera = CameraPosition - output.PositionWorld;
    output.UV = inUV;
    return output;
}

float4 PShader(VS_OUTPUT input) : COLOR0    // SHADER MODEL 3.0-
float4 PShader(VS_OUTPUT input) : SV_TARGET // SHADER MODEL 4.0+
PS_OUTPUT PShader(VS_OUTPUT input)          // SHADER MODEL 4.0+ MRT
{ 
    float4 texture = tex2D(ColorSampler, input.UV); //SHADER MODEL 3.0-
    float4 cubemap = texCUBE(EnvironmentSampler, reflection); //SHADER MODEL 3.0-

    float4 texture = DiffuseTexture.Sample(Sampler, input.UV); //SHADER MODEL 4.0+
    float4 cubemap = EnvironmentTexture.Sample(Sampler, reflection); //SHADER MODEL 4.0+

    return texture;
    /*or*/
    PS_OUTPUT output;
    output.colour = texture;
    return output;
}

// Directx 10- only
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
        AlphaBlendEnable = TRUE;    
        SrcBlend = SrcAlpha;        
        DestBlend = InvSrcAlpha;    
                                
        VertexShader = compile vs_3_0 VShader();
        PixelShader = compile ps_3_0 PShader();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//GLSL SHADERS
//////////////////////////////////////////////////////////////////////////////////////////////////////

//INBUILT VERTEX VARIABLES
vec4 gl_Colour                 //Input
vec3 gl_Normal                 //Input
vec4 gl_Vertex                 //Input
vec4 gl_MultiTexCoord0         //Input from 0 to 7
float gl_FogCoord              //Input
vec4 gl_Position               //Output
vec4 gl_TexCoord[]             //Output
float gl_FogFragCoord;         //Output
gl_ModelViewMatrix             // 4x4 world-view matrix.
gl_ModelViewProjectionMatrix   // 4x4 world-view-projection matrix.
gl_NormalMatrix                // 3x3 inverse transpose world-view matrix

//INBUILT FRAGMENT VARIABLES
vec4 gl_FragCoord;        //Input
bool gl_FrontFacing;      //Input
float gl_ClipDistance[];  //Input
vec2 gl_PointCoord;       //Input
vec4 gl_FragColor         //Output
float gl_FragDepth        //Output

//INBUILT PRE-DEFINED VARIABLES
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

// 2D TEXTURES
uniform sampler2D mySampler;
float4 value = texture2D(mySampler, inUVs) // inUVs is vec2

// 2D MULTI-SAMPLED TEXTURES
uniform sampler2DMS mySampler;
ivec2 uvs = ivec2(inUVs.x * WINDOW_WIDTH, inUVs.y * WINDOW_HEIGHT);
float4 value = vec4(0.0, 0.0, 0.0, 0.0);
for (int i = 0; i < SAMPLES; ++i)
{
    value += texelFetch(mySampler, uvs, i);
}
value *= (1.0 / SAMPLES);

//==============================================================================
// SHADER BODY
//==============================================================================

#version 150

//OPENGL 2.0- VERTEX SHADER
varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 WorldViewPos;

//OPENGL CORE 3.0+ VERTEX SHADER
in vec3 in_Position;
in vec2 in_UVs;
in vec3 in_Normal;
in vec3 in_Tangent;
in vec3 in_Bitangent;
out vec2 ex_UVs;
out vec3 ex_PositionWorld;
out vec3 ex_VertToCamera;
out vec3 ex_Normal;
uniform vec3 LightPosition;
uniform mat4 World;
uniform mat4 WorldViewProjection;
uniform mat4 WorldViewInvTranpose;

void main()
{
    //OPENGL 2.0-
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    WorldViewPos = vec3(gl_ModelViewMatrix * gl_Vertex);
    gl_TexCoord[0] = gl_MultiTexCoord0;
    Normal = gl_NormalMatrix * gl_Normal;
    Tangent = gl_NormalMatrix * gl_MultiTexCoord1.xyz;
    Binormal = gl_NormalMatrix * gl_MultiTexCoord2.xyz;

    //OPENGL CORE 3.0+
    gl_Position = worldViewProjection * in_Position;
    ex_UVs = in_UVs;
    ex_PositionWorld = in_Position.xyz;
    ex_Normal = (worldViewInvTranpose * vec4(in_Normal, 1.0)).xyz;
    ex_VertToCamera = CameraPosition - in_Position.xyz;
}

//OPENGL 2.0- FRAGMENT SHADER
uniform sampler2D Sampler0;
varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 WorldViewPos;

//OPENGL CORE 3.0+ FRAGMENT SHADER
in vec2 ex_UVs;
in vec3 ex_PositionWorld;
in vec3 ex_VertToCamera;
in vec3 ex_Normal;
out vec4 out_Color; /*or*/ out vec4 out_Color[1];
uniform sampler2D DiffuseSampler;
uniform samplerCube EnvironmentSampler;

void main()
{
    //OPENGL 2.0-
    float4 texture = texture2D(Sampler, gl_TexCoord[0].st); 
    gl_FragColor = float4(1.0, 0.0, 0.0, 1.0);

    //OPENGL CORE 3.0+
    float4 texture = texture(DiffuseSampler, ex_UVs);
    float4 cubemap = texture(EnvironmentSampler, reflection);

    out_Color = float4(1.0, 0.0, 0.0, 1.0); 
    /*or*/
    out_Color[0] = float4(1.0, 0.0, 0.0, 1.0); 
}

