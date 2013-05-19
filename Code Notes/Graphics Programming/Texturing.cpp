//////////////////////////////////////////////////////////////////////////////
//TEXTURING
//////////////////////////////////////////////////////////////////////////////
/*
HUE = Particular colour in rainbow
SATURATION = How rich a colour is
VALUE = How much Black/White a colour has
TINTS = Saturation decreases
SHADES = Value decreases
TONES = Saturation/Value decreases

TGA = Targa
PNG = Portable Network Graphics
JPEG = Joint Photography Experts Group
BMP = Bitmap
GIF = Graphics Interchange Format

HSB (Hue/Saturation/Brightness)        Cylindrical colour representation
CMYK (Cyan/Magenta/Yellow/Key[Black])  Subtractive colour model
RGB (Red/Green/Blue)                   Additive colour model
 
8bit   RGB: Only 256 colors to use
24bit  RGB: Each channel has 8bits (256 colors)
32bit ARGB: Each channel has 8bits (256 colors) including 8bit alpha channel

TEXTURE MAPPING: UV coordinates for 2D image
CUBE MAPPING: UVW coordinates for 3D cube image

//////////////////////////////////////////////////////////////////////////////
//TEXTURE FILTERING
//////////////////////////////////////////////////////////////////////////////

3 TYPES OF TEXTURE FILTERING:
 • Point: Nearest Neighbour/Box Filtering
 • Linear: Bilinear/Trilinear
 • Anisotropic (Most consuming)

POINT: 
No filtering applied
Nearest texel is chosen to the given UV coordinates
If coordinates are on texel border, UVs are rounded

LINEAR: 
Looks at 2x2 texels surrounding the UVs and calculates color using weights
If UVs totally in one texel: 100% that texel
If UVs on border between two texels: 50% each
If UVS on border between four texels: 25% each
Trilinear: Fixes artifact occurs when stitching various mipmap levels together

ANISOTROPIC: 
Avoids blur at sharp angles/distances
Prevents distortion when angle between camera forward vector and poly 
normal is large

MIPMAP: 
Mip = multum in parvo; 'many things in a small place'
Series of power of 2 texture created from original texture

MIPMAP FILTERS:
NONE: Disables mipmapping
POINT: Choose mipmap level that is closest in size to geometry and filter
LINEAR: Choose Two mipmap levels that are closest in size to geometry then
        filter both and lineraly combine them

sampler TexS = sampler_state
{
      Texture = <gTex>;
      MinFilter = LINEAR;   //texture filter used when shrinking textures
      MagFilter = LINEAR;   //texture filter used when magnifying textures
      MipFilter = LINEAR;   //type of mipmap filter
};

//////////////////////////////////////////////////////////////////////////////
//DETAIL MAPPING
//////////////////////////////////////////////////////////////////////////////

INTERPOLATED NORMAL: 
Normal in pixel shader for specific pixel of surface; makes surface smooth

ALPHA MAP: 
Stores transparency information

BUMP MAP: 
Created from height map/grayscale image (no additional geometry)

NORMAL MAP: 
Created from difference of high/low res mesh (no additional geometry)

PARALLAX MAP:
Displaces texture UV coordinates 

DISPLACEMENT MAP: 
Displaces vertices and/or creates additional geometry from height map


//////////////////////////////////////////////////////////////////////////////
//BUMP MAPPING
//////////////////////////////////////////////////////////////////////////////

BUMP MAPPING: 
Changes interpolated normal of vertex for pixel according to height 
map/grayscale image

OBJECT SPACE BUMP MAPPING: 
map is unique to specific object (rainbow)

TANGENT SPACE BUMP MAPPING: 
map can be reused (purple/blue/red)

//////////////////////////////////////////////////////////////////////////////
//NORMAL MAPPING
//////////////////////////////////////////////////////////////////////////////

NORMAL MAP: 
Created from difference of high/low res mesh (no additional geometry)
Uses same method as Tangent Space Bump mapping

MAP CREATION:
- Rays are cast ffrom each low-res vertex in the direction of that vertex's 
  interpolated normal
- Ray is intersected against the high-res model to find the point of 
  intersection
- The normal at the point of intersection is the stored in the normal map
- The position of the stored normal in the normal map is determined by the 
  low-res model's UV coordinate

NEEDS FOR CREATION: 
 • Low-resolution model
 • High-resolution model
 • Smooth normal vectors for each vertex of the low-resolution model
 • Smooth normal vectors for each vertex of the high-resolution model
 • UV texture coordinates for the low-resolution model

//////////////////////////////////////////////////////////////////////////////
//PARALLAX MAPPING
//////////////////////////////////////////////////////////////////////////////

PARALLAX MAP: Creates illusion of depth by displacing UV coordinates

PIXEL SHADER PIPELINE:
- Find view angle (angle relative to the surface normal) and value from a 
  height map using UV coordinates
- Use both to calculate new UV coordinates to access tex2D information
- Steeper view-angles = more displacement giving illusion of depth as the 
  view changes

NEEDS FOR PROCESS: 
  • A height map
  • A bump or normal map
  • Any other decals or textures the material uses

//////////////////////////////////////////////////////////////////////////////
//DISPLACEMENT MAPPING
//////////////////////////////////////////////////////////////////////////////

DISPLACEMENT MAPPING: 
Direction vector read from displacement map and added to vertex position
moving it to another place


//////////////////////////////////////////////////////////////////////////////
//PROJECTIVE TEXTURING
//////////////////////////////////////////////////////////////////////////////

• Method of projecting a texture into a 3D scene
• Transform local position of vert by light's worldViewProj matrix
• Pass position to pixel shader
• Position will be in homogenous clip space so divide by w
• Scale the position from [-1,1] to [0,1] for proper texture coords
• Sample the texture to be projected 

VERTEX SHADER:
outVS.projTex = mul(float4(localposition, 1.0f), gLightWVP);

PIXEL SHADER:
projTex.xy /= projTex.w;
projTex.x =  0.5f*projTex.x + 0.5f;
projTex.y = -0.5f*projTex.y + 0.5f;
float4 texColor = tex2D(TexS, projTex.xy);


//////////////////////////////////////////////////////////////////////////////
//COMPRESSION
//////////////////////////////////////////////////////////////////////////////

LOSSY COMPRESSION: Filesize over quality
LOSSLESS COMPRESSION: Quality over filesize
NORMAL COMPRESSION: Compressions not recommended since compressing normal 
                    maps can un-normalize normals

-------------------------------------------------------------------------
RUN LENGTH ENCODING: 
-------------------------------------------------------------------------
- lossless encoding
- aaabbccc ==> a3b2c3
- problem is lots of 1 values and encoding doubles the size
- solved by using a marker to indicate where encoding has happened
- close colored pixels can be merged into the one color and counted in run

-------------------------------------------------------------------------
HUFFMAN ENCODING:
-------------------------------------------------------------------------
- lossless encoding
- uses binary tree/priority queue

1) Find frequency of every character used
2) Create a node for every character used and store in a priority queue
3) Each node is sorted due to it's frequency number (least to greatest)
4) The top two nodes with the smallest frequency are removed and put as 
   children to a new node
5) This new node is given a frequency that equals the combined children's 
   frequency
6) The new node is inserted into the priority queue
7) Continue this until there is one large node left in the queue creates 
   the tree
8) Traverse through the graph (left gives 0, right gives 1) and store the 
   path taken to get to the correct letter
9) Create a Huffman table (array) to store the path information

*/////////////////////////////////////////////////////////////////////////////