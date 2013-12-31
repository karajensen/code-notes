///////////////////////////////////////////////////////////////////////////////////////////////////
//COLOUR AND TEXTURING
///////////////////////////////////////////////////////////////////////////////////////////////////
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

PAL:  25fps     576 pixel lines  720 × 576
NTSC: 29.97fps  525 pixel lines  720 × 486
INTERLACE: for tvs to prevent shuttering artifacts, frame is split into two fields
PROGRESSIVE: frame is drawn top to bottom

///////////////////////////////////////////////////////////////////////////////////////////////////
//TEXTURE FILTERING
///////////////////////////////////////////////////////////////////////////////////////////////////

MINFILTER: Texture filter used when shrinking textures
MAGFILTER: Texture filter used when magnifying textures

POINT: 
• Nearest Neighbour/Box Filtering
• Nearest texel is chosen to the given UV coordinates
• If coordinates are on texel border, UVs are rounded

LINEAR:
• Bilinear/Trilinear filtering
• Looks at 2x2 texels surrounding the UVs and calculates color using weights
• If UVs totally in one texel: 100% that texel
• If UVs on border between two texels: 50% each
• If UVS on border between four texels: 25% each
• Trilinear: Fixes artifact occurs when stitching various mipmap levels together

ANISOTROPIC: 
• Most consuming of all filters
• Avoids blur at sharp angles/distances
• Prevents distortion when angle between camera forward vector and poly normal is large

///////////////////////////////////////////////////////////////////////////////////////////////////
//MIPMAPPING
///////////////////////////////////////////////////////////////////////////////////////////////////

MIPMAP:
Mip = multum in parvo; 'many things in a small place'
Series of power of 2 texture created from original texture

MIPFILTER:
• None disables mipmapping
• Point chooses mipmap level that is closest in size to geometry and filter
• Linear shooses Two mipmap levels that are closest in size to geometry then
  filter both and lineraly combine them

///////////////////////////////////////////////////////////////////////////////////////////////////
//DETAIL MAPPING
///////////////////////////////////////////////////////////////////////////////////////////////////

DETAIL MAPPING: Changes interpolated normal depending on map
INTERPOLATED NORMAL: Normal in pixel shader for specific pixel of surface; makes surface smooth
OBJECT SPACE MAPPING: Map is unique to specific object (rainbow)
TANGENT SPACE MAPPING: Map can be reused (purple/blue/red)

BUMP MAP
• Created from height map/grayscale image (no additional geometry)

NORMAL MAP
• Created from difference of high/low res mesh (no additional geometry)

PARALLAX MAP
• Creates illusion of depth by displacing UV coordinates
• Find view angle (angle relative to the surface normal) and value from a height map using UV coordinates
• Use both to calculate new UV coordinates to access tex2D information
• Steeper view-angles = more displacement giving illusion of depth as the view changes

DISPLACEMENT MAP
• Direction vector read from displacement map and added to vertex position moving it to another place

///////////////////////////////////////////////////////////////////////////////////////////////////
//PROJECTIVE TEXTURING
///////////////////////////////////////////////////////////////////////////////////////////////////

• Method of projecting a texture into a 3D scene
• Transform local position of vert by light's worldViewProj matrix
• Pass position to pixel shader
• Position will be in homogenous clip space so divide by w
• Scale the position from [-1,1] to [0,1] for proper texture coords
• Sample the texture to be projected 

///////////////////////////////////////////////////////////////////////////////////////////////////
//TRANSPARENCY
///////////////////////////////////////////////////////////////////////////////////////////////////

• Render non-transparent objects first in any order
• Render transparent objects back to front according to depth
• Alpha blending: blends alpha pixel into buffer using a set formula
• Alpha testing: tests whether alpha pixel contributes to the colour buffer

COLOR COMPONENT BLENDING
AlphaBlendEnable = true
SrcBlend = SrcAlpha         (output.rgb * output.a)
DestBlend = InvSrcAlpha     (dest.rgb * (1-output.a))
BlendOp = Add

ALPHA COMPONENT BLENDING
SrcBlendAlpha = One         (output.a * 1)
DestBlendAlpha = One        (dest.a * 1)
BlendOpAlpha = Add

ALPHA TESTING
AlphaTestEnable = true;
AlphaFunc = GreaterEqual;
AlphaRef = 220;

==============================================================================
ALPHA BLENDING FACTORS
==============================================================================

D3DBLEND_ZERO           (0, 0, 0, 0)
D3DBLEND_ONE            (1, 1, 1, 1)
D3DBLEND_SRCCOLOR       (Rˢ, Gˢ, Bˢ, Aˢ)
D3DBLEND_INVSRCCOLOR    (1-Rˢ, 1-Gˢ, 1-Bˢ, 1-Aˢ)
D3DBLEND_SRCALPHA       (Aˢ, Aˢ, Aˢ, Aˢ)
D3DBLEND_INVSRCALPHA    (1-Aˢ, 1-Aˢ, 1-Aˢ, 1-Aˢ)
D3DBLEND_DESTALPHA      (Aᵈ, Aᵈ, Aᵈ, Aᵈ)
D3DBLEND_INVDESTALPHA   (1-Aᵈ, 1-Aᵈ, 1-Aᵈ, 1-Aᵈ)
D3DBLEND_DESTCOLOR      (Rᵈ, Gᵈ, Bᵈ, Aᵈ)
D3DBLEND_INVDESTCOLOR   (1-Rᵈ, 1-Gᵈ, 1-Bᵈ, 1-Aᵈ)
D3DBLEND_SRCALPHASAT    (f, f, f, 1) where f = min(Aˢ,1-Aᵈ)

Default Source Blend Factor: D3DBLEND_SRCALPHA
Default Dest Blend Factor: D3DBLEND_INVSRCALPHA

==============================================================================
ALPHA BLENDING OPERATIONS
==============================================================================

D3DBLENDOP_ADD:
OutputPixel = SourcePixel*SourceBlendFactor + DestPixel*DestBlendFactor 
• good for glow effects; doesn't require sorting; can saturate objects easily

D3DBLENDOP_SUBTRACT:
OutputPixel = SourcePixel*SourceBlendFactor - DestPixel*DestBlendFactor 

D3DBLENDOP_REVSUBTRACT: 
OutputPixel = DestPixel*DestBlendFactor - SourcePixel*SourceBlendFactor 

D3DBLENDOP_MIN:
OutputPixel = min(SourcePixel*SourceBlendFactor, DestPixel*DestBlendFactor)

D3DBLENDOP_MAX:
OutputPixel = max(SourcePixel*SourceBlendFactor, DestPixel*DestBlendFactor)

==============================================================================
ALPHA TESTING
==============================================================================

if(Aˢ [Operation] ref == true) { accept pixel into buffer }

D3DCMP_NEVER:           Alpha test always fails
D3DCMP_ALWAYS:          Alpha test always succeeds
D3DCMP_LESS:            <
D3DCMP_EQUAL:           ==
D3DCMP_LESSEQUAL:       <=
D3DCMP_GREATER:         >
D3DCMP_NOTEQUAL:        !=
D3DCMP_GREATEREQUAL:    >=

///////////////////////////////////////////////////////////////////////////////////////////////////
//ANTIALIASING
///////////////////////////////////////////////////////////////////////////////////////////////////

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
• Each pixel is averaged with the pixel's around it

GRID SAMPLING: 
• Use on final texture and blur pixels with sharp changes from neighbours

RANDOM SAMPLING: 
• Randomly samples pixels around center pixel; some areas too little/too much this way

POISSON DISC SAMPLING: 
• Random sampling with additional checks to whether samples are too close to each other

///////////////////////////////////////////////////////////////////////////////////////////////////
//COLOR CORRECTION
///////////////////////////////////////////////////////////////////////////////////////////////////

GAMMA CORRECTION
• the relationship between a pixel's numerical value and its actual luminance

SRGB COLOR SPACE
• Texture blending operations are done in linear space
• sRGB format is gamma corrected color which produce incorrect results in linear space

///////////////////////////////////////////////////////////////////////////////////////////////////
//COMPRESSION
///////////////////////////////////////////////////////////////////////////////////////////////////

LOSSY COMPRESSION: Filesize over quality
LOSSLESS COMPRESSION: Quality over filesize
NORMAL COMPRESSION: Compressions not recommended since compressing normal 
                    maps can un-normalize normals

===========================================================================
RUN LENGTH ENCODING: 
===========================================================================
• lossless encoding
• aaabbccc ==> a3b2c3
• problem is lots of 1 values and encoding doubles the size
• solved by using a marker to indicate where encoding has happened
• close colored pixels can be merged into the one color and counted in run

===========================================================================
HUFFMAN ENCODING:
===========================================================================
• lossless encoding
• uses binary tree/priority queue

1) Find frequency of every character used
2) Create a node for every character used and store in a priority queue
3) Each node is sorted due to it's frequency number (least to greatest)
4) The top two nodes with the smallest frequency are removed and put as children to a new node
5) This new node is given a frequency that equals the combined children's frequency
6) The new node is inserted into the priority queue
7) Continue this until there is one large node left in the queue creates the tree
8) Traverse through the graph (left gives 0, right gives 1) and store the path taken to the correct letter
9) Create a Huffman table (array) to store the path information

*////////////////////////////////////////////////////////////////////////////////////////