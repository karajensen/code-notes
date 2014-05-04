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

UNIFORM INPUT: Does not change per-vertex or per-pixel, readonly to shader
VARYING INPUT: Change per-vertex/per-pixel
ATTRIBUTES: 'in' values passed to vertex shader; default to varying but can use uniform keyword
CONSTANT TABLE: Holds uniform name, register and size with $ before any uniform attributes
CONSTANT REGISTERS: lower-latency access and more frequent updates from the CPU
TEXTURE REGISTERS: perform better for arbitrarily indexed data

SWIZZLING: Using x/y/z/w to refer to each component
SWIZZLE MASK: Combining components (.xy, .xyz, .xx)
TESSELLATION: Converts low-detail subdivision surfaces into higher-detail primitives

DYNAMIC FLOW CONTROL/BRANCHING: Choose path based on dynamic variable that can change during execution
STATIC FLOW CONTROL/BRANCHING: Choose path based on constant variable that cannot be modified during execution

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADER ASSEMBLY
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Reference: Learn vertex and pixel shader programming with DX9

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
//• Compiler may optimize isnan() and isfinite() calls
//• NaN * 0 = 0 not NaN except with precise keyword
//• Use of static keyword for global bools only evaluates the one path instead of both
//• If missing components in vertex stream, auto sets z/y to 0.0 and w to 1.0

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
//HLSL
//////////////////////////////////////////////////////////////////////////////////////////////////////

//VARIABLE TYPES
bool myBool;
int myInt;    //32-bit signed int
half myFlt;   //16-bit float
float myFlt;  //32-bit float
double myDbl; //64-bit double

//VECTOR/ARRAY TYPES
//Sections can be accessed via xyzw/rgba but not both
//ps2.0- does not have support for chained swizzing
float4 myFlt /*or*/ float myFlt[4] /*or*/ vector<float,4> myFlt /*or*/ vector myFlt
bool3 myBool /*or*/ bool myBool[3] /*or*/ vector<bool,3> myBool
int2 myint   /*or*/ int myInt[2]   /*or*/ vector<int,2> myInt
float3 myFlt = { 1.0f, 2.0f, 3.0f };
float4 myFlt = float4(myFlt3, 1.0f);
float value = myFlt[0];
float2 value = myFlt.xy;

//MATRIX TYPES
//float nxn where n=[1,4]
float3x4 myMat; /*or*/ matrix<float,3,4>
float2x2 myMat = { 1.0f, 2.0f, 3.0f, 4.0f };
float value = myMat[0][1];    //from 0 to 3
float value = myMat.m00;      //from m00 to m33
float value = myMat._11;      //from _11 to _44
float2 value = myMat._11_22;

//STRUCTURES
struct MyStruct
{
};

//VARIABLE PREFIXES
typedef float MyFloat;
float myGlobalFlt;       // global variable defaults to uniform/extern
const float myFlt = 4;   // variable cannot be modified by shader (can be modfied by application if visible)
static float myGlobal;   // outside main(): variable will not be exposed outside shader
static float myLocal;    // inside main(): value will persist across multiple calls to the shader
extern float myGlobal;   // variable is exposed outside shader
uniform                  // Does not change per-vertex or per-pixel, links to outside application, readonly
shared                   // allows variable to be accessed accross mutliple .fx files
volatile                 // hints that it will be modified often, only global variables

//CASTING
//Copies instead of converts
float4x4 myMat = (float4x4)myFlt;
float myFlt = (float)myInt;

//PREPROCESSOR
#include "myshader.fx"
#define MYDEFINE
#undef MYDEFINE
#ifdef MYDEFINE
#ifndef MYDEFINE
#elif MYDEFINE
#else
#endif

//INTRINSICS
abs(x)              // return absolute value
all(vec)            // boolean, int, float vector, returns true if all components are true
any(vec)            // boolean, int, float vector, returns true if any component is true
abort()             // Terminates the current draw or dispatch call being executed (SM4+)
cross(a,b)          // crosses two vectors
clamp(x,min,max)    // returns clamped value
ceil(x)             // rounds upwards to nearest int
degrees(rad)        // converts rad to degrees
determinant(mat)    // returns determinant of matrix
dot(a,b)            // dots two vectors
distance(a,b)       // returns distance between two points
ddx(x)              // Returns the partial derivative of x with respect to the screen-space x-coordinate
ddy(x)              // Returns the partial derivative of x with respect to the screen-space y-coordinate
floor(x)            // rounds downwards to nearest int
frac(x)             // returns fractional part of x
fwidth(x)           // Returns abs(ddx(x)) + abs(ddy(x))
isfinite(x)         // returns true if x is a finite number
isinf(x)            // return true if pos or neg infinity
isnan(x)            // return true if not a number
length(a)           // return length of a vector
lerp(x,y,s)         // linear interpolation: x*(1-s) + y*s
max(x,y)            // Selects max of x and y
min(x,y)            // Selects min of x and y
mad(a,b,c)          // Performs mad assembly operation: a * b + c (SM5)
modf(x, intPart)    // returns fractional part, stores int part
mul(matA, matB)     // Matrix multiplication
normalize(vec)      // Normalizes a vector
pow(1.0f, 3.0f)     // Calculates 1³
radians(deg)        // converts degrees to rad
reflect(vec, norm)  // reflects vector along the normal
rsqrt(x)            // Returns 1 / sqrt(x)
round(x)            // returns rounded to the nearest integer
transpose(mat)      // creates transpose of matrix
trunc(x)            // removes the fractional part of x
saturate(x)         // clamps value between 0 and 1
sqrt(x)             // Square root
step(a,b)           // a > b ? 0.0 : 1.0
sign(x)             // Returns the sign of x
sin(angle)          // Calculates sine of an angle (in radians).
cos(angle)          // Calculates cosine of an angle (in radians).
tan(angle)          // Angle in radians
acos(x)
asin(x)
atan(x/y) /*or*/ atan2(x,y)
        
//VERTEX INPUTS             VERTEX OUTPUTS   PIXEL INPUTS    PIXEL OUTPUTS
POSITION0  TANGENT0         POSITION         COLOR0          COLOR0
NORMAL0    BINORMAL0        PSIZE            TEXCOORD0       DEPTH
PSIZE0     TESSFACTOR0      FOG
COLOR0     BLENDINDICES0    COLOR0
TEXCOORD0  BLENDWEIGHT0     TEXCOORD0

//////////////////////////////////////////////////////////////////////////////////////////////////////
//HLSL SHADING
//////////////////////////////////////////////////////////////////////////////////////////////////////

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

//SHADER MODEL 3.0- CONSTANTS
float myFloat; //each register is a float4 (float, float2 etc will take up whole register)
float myArray[100] //to save space, pack arrays as float4
float4x4 World                  : World;
float4x4 WorldViewProjection    : WorldViewProjection;
float4x4 WorldInvTrans          : WorldInverseTranspose;
float3 CameraPos;
float3 LightPos;

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

struct VS_OUTPUT
{
    float4 Pos           : POSITION;    // SHADER MODEL 3.0-
    float4 Pos           : SV_POSITION; // SHADER MODEL 4.0+
    float2 UV            : TEXCOORD0;
    float3 Normal        : TEXCOORD1;
    float3 LightVector   : TEXCOORD2;
    float3 CameraVector  : TEXCOORD3;
    float3 Tangent       : TEXCOORD4;
    float3 Binormal      : TEXCOORD5;
    float4 Colour        : COLOR;
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
    output.LightVector = normalize(LightPos - PosWorld);
    output.CameraVector = CameraPos - PosWorld;
    output.UV = inUV;
    return output;
}

float4 PShader(VS_OUTPUT input) : COLOR0    // SHADER MODEL 3.0-
float4 PShader(VS_OUTPUT input) : SV_TARGET // SHADER MODEL 4.0+: can output only float3
{ 
    //Do in pixel shader as after intepolation, normal may not be normalised anymore
    normalize(input.Normal);

    float4 Texture = tex2D(ColorSampler, input.UV); //SHADER MODEL 3.0-

    return Texture;
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
bool myBool;
int myInt;      //signed integer
uint myInt;     //unsigned integer
half myFlt;     //16-bit float
float myFlt;    //32-bit float
++myFlt;        //supports pre/post fix

//VECTOR TYPES
//Sections can be accessed via xyzw/rgba/stpq but can't be mixed
vec2, vec3, vec4     //floating point vector
bvec2, bvec3, bvec4  //boolean vector
ivec2, ivec3, ivec4  //signed int vector
uvec2, uvec3, uvec4  //unsigned int vector

//ARRAYS
float[3] myArray /*or*/ float myArray[3];
myArray[0]

//MATRIX TYPES
mat2    //2x2 matrix
mat3    //3x3 matrix
mat4    //4x4 matrix
matnxn  //where n=[2,4]

//STRUCTURES
struct MyStruct
{
};

//VARIABLE PREFIXES
const float myFlt = 4;  // variable cannot be modified
uniform                 // Does not change per-vertex or per-pixel, links to outside application, readonly
varying                 // Changes per-vertex/per-pixel

//PREPROCESSOR
#version 150  //shader model to use, must be before anything else
#include "myshader.fx"
#define MYDEFINE
#undef MYDEFINE
#ifdef MYDEFINE
#ifndef MYDEFINE
#elif MYDEFINE
#else
#endif

//INTRINSICS
abs(a)                    // magnitude of value
all(boolVec)              // takes in boolean vec, return true if all components are true
any(boolVec)              // takes in boolean vec, return true if any component is true
cross(a,b)                // Crosses two vector
clamp(x, min, max)        // returns clamped value
ceil(x)                   // rounds upwards to nearest int
determinant(mat)          // returns determinant of matrix
distance(vecA, vecB)      // distance between two points
dot(a,b)                  // Dots two vectors
degrees(rad)              // converts radians to degrees
dFdx(a)                   // derivative in x, a=float or vector, only in pixel shader
dFdy(a)                   // derivative in y, a=float or vector, only in pixel shader
floor(x)                  // rounds downwards to nearest int
fract(x)                  // x - floor(x)
fwidth(a)                 // return = abs(dFdx (p)) + abs(dFdy (p)), only in pixel shader
inverse(mat)              // returns inverse of matrix
isinf(x)                  // return true if pos or neg infinity
isnan(x)                  // return true if not a number
length(myVec)             // Length of a vector
pow(1.0f, 3.0f)           // Calculates 1³
normalize(myVec)          // Normalizes a vector
mix(a,b,c)                // c == 0 ? a : b, interpolates for other values
max(x,y)                  // returns maximum value
min(x,y)                  // returns minimum value
modf(x, intPart)          // returns fractional part, stores int part
reflect(vec, norm)        // reflects vector along normal
round(x)                  // rounds to nearest integer
roundEvent(x)             // rounds to nearest integer, 0.5 rounds to nearest even int
radians(deg)              // converts degrees to radians
step(a,b)                 // a > b ? 0.0 : 1.0
transpose(mat)            // returns transposed matrix
sin(angle)                // angle in radians
cos(angle)                // angle in radians
tan(angle)                // angle in radians
asin(x)
acos(x)
atan(y,x) /*or*/ atan(y/x)

//VERTEX VARIABLES
vec4 gl_Colour            //Input
vec3 gl_Normal            //Input
vec4 gl_Vertex            //Input
vec4 gl_MultiTexCoord0    //Input from 0 to 7
float gl_FogCoord         //Input
vec4 gl_Position          //Output
vec4 gl_TexCoord[]        //Output
float gl_FogFragCoord;    //Output

//FRAGMENT VARIABLES
vec4 gl_FragCoord;        //Input
bool gl_FrontFacing;      //Input
float gl_ClipDistance[];  //Input
vec2 gl_PointCoord;       //Input
vec4 gl_FragColor         //Output
float gl_FragDepth        //Output

//PRE-DEFINED VARIABLES
gl_ModelViewMatrix             // 4x4 world-view matrix.
gl_ModelViewProjectionMatrix   // 4x4 world-view-projection matrix.
gl_NormalMatrix                // 3x3 inverse transpose world-view matrix
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

//SAMPLERS
sample1D, sampler2D, sampler3D      // access 1D, 2D, 3D texture
samplerCube                         // access cube mapped texture
sampler2DRect                       // access rectangular texture
sampler1DArray, sampler2DArray      // access 1D, 2D array texture
samplerBuffer                       // access buffer texture
texture2D(mySampler, uvs)           // Query from a texture, vec2 uvs

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

//OPENGL 2.0- VERTEX SHADER
varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 VertexNormal;
varying vec3 WorldViewPos;

//OPENGL CORE 3.0+ VERTEX SHADER
in vec3 in_Position;
in vec2 in_UVs;
in vec3 in_Normal;
out vec3 VertToLight;
out vec3 Normal;
uniform vec3 lightPosition;
uniform mat4 world;
uniform mat4 worldViewProjection;
uniform mat4 worldViewInvTranpose;

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
	gl_Position = worldViewProjection * vec4(in_Position, 1.0);
	Normal = (worldViewInvTranpose * vec4(in_Normal, 1.0)).xyz;
	gl_TexCoord[0].st = in_UVs;
    vec4 worldViewPos = world * vec4(in_Position, 1.0);
	vec4 lightViewPos = worldViewInvTranpose * vec4(lightPosition, 1.0);
	VertToLight = normalize((lightViewPos - worldViewPos).xyz);
}

//OPENGL 2.0- FRAGMENT SHADER
uniform sampler2D Sampler0;
varying vec3 Normal;
varying vec3 Binormal;
varying vec3 Tangent;
varying vec3 WorldViewPos;

//OPENGL CORE 3.0+ FRAGMENT SHADER
in vec3 Normal;
in vec4 Color;
out vec4 out_Color;

void main()
{
    //Do in pixel shader as after intepolation, normal may not be normalised anymore
    normalize(Normal);

    //OPENGL 2.0-
    gl_FragColor = texture2D(Sampler0, gl_TexCoord[0].st); 

    //OPENGL CORE 3.0+
    out_Color = ex_Color;
}

