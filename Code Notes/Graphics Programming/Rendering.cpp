//////////////////////////////////////////////////////////////////////////////
//RENDERING SYSTEMS
//////////////////////////////////////////////////////////////////////////////
/*
RAYTRACING      [PRE-RENDER]        Casts rays from light to scene to view
RAYCASTING      [REALTIME-RENDER]   Casts rays from view to scene to light
RASTERIZATION   [REALTIME-RENDER]   Projects to plane using proj matrix

------------------------------------------------------------------------------
FORWARD RAY-TRACING [RAY TRACING]
------------------------------------------------------------------------------
 - Rays traced from light into 3D scene
 - Calculates new direction of rays when hitting surface
 - Ideal for reflections/refractions
 - Quality increases with more rays
 - DISADVANTAGE: hard to optimise, not possible in real time
 - DISADVANTAGE: lots of wasted rays that won't hit objects

------------------------------------------------------------------------------
BACKWARD RAY-TRACING [RAY CASTING]
------------------------------------------------------------------------------
 - Rays traced from camera into 3D scene
 - Does not compute new direction a ray takes after reflections/refractions
 - Ray sent for each pixel; number of rays depends on screen resolution
 - Every pixel will always be shaded; less rays/faster than raytracing

------------------------------------------------------------------------------
SCANLINE RENDERING [RASTERIZATION]
------------------------------------------------------------------------------
Algorithm for determining which models are visible. 
It goes row by row for pixels rather than look at each polygon.
Polygons are sorted by their y coordinate and then intersected with a scanline
Polygons obstructed by others are discards as the line advances down the image
Only vertices needed for current scanline are worked on, speeding up process

------------------------------------------------------------------------------
PATH TRACING [RAY TRACING]
------------------------------------------------------------------------------
Extends rays tracing where new rays are created and traced for any points of 
intersection of objects. Takes into account indirect lighting/global 
illumination 


//////////////////////////////////////////////////////////////////////////////  
//REAL-TIME RENDERING / RASTERIZATION RENDER PIPELINES
//////////////////////////////////////////////////////////////////////////////  

TEXEL: One unit of a texture
PIXEL: One unit of the screen
FRAGMENT: Potential pixel. Each fragment has a pixel location, 
          a depth value, color/texture values

One pixel can be formed from many texels if image is shrunk
One texel can be shared by many texels if image is enlarged
Texels and pixels can map one-to-one when rendering to a quad

=========================================================================
SCENE RENDERING:
=========================================================================

1) FRUSTUM CULLING
List of scene meshes inside view frustum are compiled an culled based
On the view frustum

2) VERTEX SHADER
Positions transformed by wvp matrix into homogeneous clip space
(screen space multiplied by 'w')

3) GEOMETRY SHADER
Any additional geometry is created in geometry shader

4) BACKFACE CULLING
Backface culling occurs depending on vert winding order

5) CLIPPING
Clips any vertices outside the screen
If x,y is in range [-w,w] and z is in range [0,w] then okay

6) SCREEN MAPPING
Homogenous clip space transformed into screen space
To get final coordinate, divide by w (which is screen space z)

-----------------------------------------------------------------
RASTERIZATION

7) TRIANGLE TRAVERSAL
2D shape fitted into pixels. If the center of pixel is enclosed in shape, 
pixel is fully filled. This creates a stepping, aliased effect. 
2D object may visibly shift in position during this process

   PIXELS IN SCREEN:
   (-0.5,-0.5)
       o--o--o--o
       |◄►|◄►|◄►|  ◄► = center of pixel (0,0) (1,0) (2,0)
       o--o--o--o                       (0,1) (1,1) (2,1)             
       |◄►|◄►|◄►|
       o--o--o--o 
             (1.5,2.5)

8) FRAGMENT GENERATION
Every pixel covered by shape is a Fragment. Fragment values are 
interpolated from the 2D triangles they're made up of
-----------------------------------------------------------------

9) PIXEL SHADING
Fragments sent to pixel shader and get texture/lighting applied

10) COMPOSITION
Depth/stencil buffers decide pixel's contribution to render target
Alpha testing/blending is done if transparency

=========================================================================
RENDERING WITH TRANSPARENCY
=========================================================================
1) Render opaque in any order
2) Render transparent objects back-to-front over top of opaque objects
   Order important or else pixels that should be written to buffer are not

=========================================================================
FORWARD SHADING
=========================================================================
* Easy to render transparency
* Expensive to do post effects
* Are limited in amount of lights

1) Render the scene with any lights that affect it to a single color buffer
2) Render the scene again outputting any information needed for post effects
3) Perform any post effects and present final image to the back buffer

=========================================================================
DEFERRED SHADING
=========================================================================
* Difficult to render transparecy
* Cheap to do post effects
* Can have many multiple lights

1) Render the scene once sending attributes to a G-buffer
   Attributes include: Normals, Depth, Diffuse, Specular, Ambient etc.
2) Render all lights as geometry with attenuation/intensity
   Point light: Sphere, Spot light: Cone, Directional light: Full screen quad
3) Combine the lighting texture with the G-buffer calculating the color 
   contribution of the light to the final pixel
4) Perform any post effects with the ability to use the G-buffer


////////////////////////////////////////////////////////////////////////////// 
//TRANSFORMATIONS
////////////////////////////////////////////////////////////////////////////// 

------------------------------------------------------------------
OPENGL: Column Major Matrix / Right Handed Coordinate System
------------------------------------------------------------------
Trans * Rot * Scale = LocalWorld
ParentWorld * LocalWorld = World
Proj * Veiw * World * Vertex = FinalVertex in screenspace

| Right.x  Up.x  For.x  Pos.x |    UP: +Y
| Right.y  Up.y  For.y  Pos.y |    RIGHT: +X
| Right.z  Up.z  For.z  Pos.z |    FORWARD: -Z
|   0       0       0     1   |

------------------------------------------------------------------
DIRECTX: Row Major Matrix / Left Handed Coordinate System
------------------------------------------------------------------
Scale * Rot * Trans = LocalWorld
LocalWorld * ParentWorld = World
Vertex * World * View * Proj = FinalVertex in screenspace

| Right.x  Right.y   Right.z  0 |   UP: +Y
| Up.x     Up.y      Up.z     0 |   RIGHT: +X
| For.x    For.y     For.z    0 |   FORWARD: +Z
| Pos.x    Pos.y     Pos.z    1 |


==============================================================================
VIEW MATRIX
Inverse of the Camera World Matrix
changes the world scene basis so the camera is at the origin
==============================================================================

(Method only works with camera matrices do to orthogonality)
matView._11 = right.x;	matView._12 = up.x;	  matView._13 = forward.x;
matView._21 = right.y;	matView._22 = up.y;   matView._23 = forward.y;
matView._31 = right.z;	matView._32 = up.z;   matView._33 = forward.z; 
matView._41 = -D3DXVec3Dot(&pos,&right); 
matView._42 = -D3DXVec3Dot(&pos,&up);
matView._43 = -D3DXVec3Dot(&pos,&forward);

==OR==

D3DXMatrixLookAtLH(&matView, &LookAtPosition, &Forward, &Up)

==============================================================================
PROJECTION MATRICES
Projects the final scene onto the screen (Screen space)
==============================================================================

VIEW FRUSTUM:
Pyramid volume from camera to world, has near and front clipping planes

ORTHOGONAL PROJECTION MATRIX:
objects remain same size regardless of depth

PERSPECTIVE PROJECTION MATRIX:
objects different sizes according to depth, uses horizon as vanishing point 

D3DXMatrixPerspectiveFovLH(&projectionMatrix,
                           D3DX_PI/2,    //field of view (α)
                           Width/height  //aspect ratio (R)
                           10.0f,        //z-value of the near view-plane (n)
                           1000.0f);     //z-value of the far view-plane (f)

PROJECTING VERTS INTO SCREEN SPACE:
For view space coordinates x,y positions need to be between [-1,1]
For view space coordinate z, depth needs to be between [0,-1]

tan(b/2) = R*tan(α/2)
tan(b/2)*n = W/2
tan(α/2)*n = H/2

 A = 1/(R*tan(α/2))
 B = 1/(R*tan(b/2))
 C = f/(f-n)
 D = -fn/(f-n)

         | A 0 0 0 |
[x y z 1]| 0 B 0 0 | = [Ax By (Cz+D)  z]
         | 0 0 C 1 |   HOMOGENEOUS CLIP SPACE
         | 0 0 D 0 |
         PROJ MATRIX

In homogeneous clip space: culling/clipping
If x,y is in range [-w,w] and z is in range [0,w] then okay
To get final coordinate, divide by w (which is screen space z)

[x' y' z' 1] = [Ax/z  By/z  C+(D/z)  1]
 --------------------------------------
| x' = x/(zRtan(α/2))        = Ax/z    |
| y' = y/(ztan(α/2))         = By/z    |
| z' = (f/f-n)-(fn/(z(f-n))) = C+(D/z) |
 --------------------------------------

//////////////////////////////////////////////////////////////////////////////  
//GRAPHICS BUFFERS
//////////////////////////////////////////////////////////////////////////////  

FORMAT: Describes the layout of the resource’s data in memory
PAGE FLIPPING: Double buffering to prevent tearing
FRAMEBUFFER/RASTER: Array of memory addresses representing pixels
DEFAULT BACK/FRONT BUFFERS: 32bit color buffer

DEPTH/Z BUFFER
• Saves projected depths of models from viewer (0.0->1.0)
• Discards the incoming fragment if a depth comparison fails
• Needs to be same size or larger than connected color buffer

DEPTH BUFFER ACCURACY
• Inaccuracy causes z-fighting where triangles have same value in buffer
• Accuracy dependent on:
    - Buffer storage size (32 or 16 bits)
    - Distance between near/far planes
    - Distance between near/origin
• Near getting closer to origin gives less accuracy to values close to far plane
• Near-far distance increasing gives less accuracy to values close to far plane
• Objects together close to far plane z values may be rounded as same value since more 
  of buffer is used for objects closer to near due to non-linear scaling into the buffer
    
STENCIL BUFFER
• masks areas during rendering; specifies what's hidden/shown
• Holds on/off flag

ATTRIBUTE BUFFER
• Buffer of integers
• Used to specify which triangles belong to each subset of a mesh with 
  multiple parts (01120 means triangle 1 belongs to subset 0, triangle 
  2 belongs to subset 1 etc.)

RENDER TARGETS
• Comprised of a color buffer and a depth/stencil buffer 


//////////////////////////////////////////////////////////////////////////////
//TRANSPARENCY
//////////////////////////////////////////////////////////////////////////////

• Render non-transparent objects first in any order
• Render transparent objects back to front according to depth
• Alpha blending: blends alpha pixel into buffer using a set formula
• Alpha testing: tests whether alpha pixel contributes to the colour buffer


IMPORTANT: Render non-transparent objects first
           Render transparent from back to front according to depth 

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

//////////////////////////////////////////////////////////////////////////////
//STENCILING
//////////////////////////////////////////////////////////////////////////////

FOR MAIN SCENE RENDER TARGET
1) Render scene as normal with without portal/mirror geometry

FOR PORTAL/MIRROR RENDER TARGET
1) Clear stencil buffer to 0, color buffer to full alpha
2) Disable writes to the depth and color buffer
3) Render the portal/mirror geometry only from main scene
4) Re-enable dpeth/color buffer writes
5) Render the second scene using the stencil buffer tests with the new stencil

POST-PROCESSING
1) Take both textures rendered and blend together

==============================================================================
STENCIL COMPARISON
==============================================================================
Uses bit manipulation:
if(ref & mask [operator] value & mask == true) { accept pixel }

STENCIL REFERENCE VALUE:
gd3dDevice->SetRenderState(D3DRS_STENCILREF, 0x1);

STENCIL MASK:
Default is 0xffffffff which doesn't mask any bits
gd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0x0000ffff);

COMPARISON OPERATION:
D3DCMP_NEVER:           Stencil test always fails
D3DCMP_ALWAYS:          Stencil test always succeeds
D3DCMP_LESS:            <
D3DCMP_EQUAL:           ==
D3DCMP_LESSEQUAL:       <=
D3DCMP_GREATER:         >
D3DCMP_NOTEQUAL:        !=
D3DCMP_GREATEREQUAL:    >=
gd3dDevice->SetRenderState(D3DRS_STENCILFUNC, operation);                        

==============================================================================
STENCIL BUFFER WRITING/UPDATING
==============================================================================

//Operation to perform is Stencil test fails
gd3dDevice->SetRenderState(D3DRS_STENCILFAIL, StencilOperation);

//Operation to perform if Depth test fails
gd3dDevice->SetRenderState(D3DRS_STENCILZFAIL, StencilOperation);

//Operation to perform if Stencil test and Depth test passes
gd3dDevice->SetRenderState(D3DRS_STENCILPASS, StencilOperation);

D3DSTENCILOP_KEEP: Keep value currently in stencil buffer
D3DSTENCILOP_ZERO: Specifies to set the stencil buffer entry to zero.
D3DSTENCILOP_REPLACE: Replace the buffer entry with stencil-reference value
D3DSTENCILOP_INCRSAT: Increment the stencil buffer entry, clamps to max
D3DSTENCILOP_DECRSAT: Decrement the stencil buffer entry, clamps to 0
D3DSTENCILOP_INVERT: Invert the bits of the buffer entry
D3DSTENCILOP_INCR: Increment the buffer entry, wraps to 0 if goes over max 
D3DSTENCILOP_DECR: Decrement the buffer entry, wraps to max if goes under 0

//Stencil write mask
gd3dDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0x0000ffff);
NewValue = Value & WriteMask


//////////////////////////////////////////////////////////////////////////////  
//CAMERAS
//////////////////////////////////////////////////////////////////////////////  

----------------
|  YAW:    Y   |
|  PITCH:  X   |
|  ROLL:   Z   |
----------------

FIXED POSITION: No movement of camera
FIRST PERSON: Player is camera
THIRD PERSON: Camera floats above player
LOOK-AT POSITION: Position of target object
DESIRED POSITION: Position where camera intends to move to
ORIENTATION: Current direction in world space; Yaw, pitch, roll

=============================================================================
GIMBAL LOCK
=============================================================================
A set of three gimbals mounted together to allow three degrees of freedom
If the middle gimbal is rotated greater than 90, the top and bottle gimbals 
are aligned and in gimbal lock losing a degree of freedom. 

MATRICES: 
- Suffer from gimbal lock
- More storage space needed (12 values)

QUATERNIONS: 
- Fix gimbal lock
- Less storage space needed (4 values, 1 scale, 3 translation = 8)
- Have to compute a final matrix from them anyway

            
////////////////////////////////////////////////////////////////////////////// 
//CULLING/SCENE OPTIMISATION
////////////////////////////////////////////////////////////////////////////// 

LINEAR INTERPOLATION: Line between two points used to approximate the curve 
SPHERICAL INTERPOLATION: Smoothly interplates between two values 
BRUTE FORCE RENDERING: Rendering out entire mesh without any optimization

1)	FAR PLANE CULLING
2)  FRUSTUM CULLING
3)	FRONT/BACKFACE CULLING
4)  CLIPPING
5)	OCCULSION CULLING

FARPLANE CULLING
• Any objects past the farplane are culled
• Limitation is if plane is too close objects seen disappearing
• This can be fixed by using fog to hide far distances

FRUSTUM CULLING
• Only objects in frustum are drawn. 
• If Polygon outside it's not visible and hence discarded
• If partially inside its clipped so outside parts are removed

FRONT/BACKFACE CULLING
• Winding order of vertices indicates which way polygon is facing
	- Clockwise (DirectX)
	- Counter clockwise (OpenGL)

CLIPPING
• Any screen space coordinates outside [–1,–1,0] to [1,1,1] culled

OCCLUSION CULLING
• Identifies parts of the scene visible/not visible to the viewer
• Objects behind other objects are discarded
• Can use a plane to represent occluder *similar to frustum culling)
• Can use potential visible sets

    POTENTIAL VISIBLE SETS
    - The list a node keeps of which other nodes it can potentially see
    - Pre-computed data which is then indexed at run time to quickly 
      obtain an estimate of the visible geometry. 
    - The camera view-space is subdivided into convex regions
    - PVS is computed for each region.
    - Convex areas are called SECTORS. 
    - Adjacent sectors are linked to one another via PORTALS
    - Best for indoor games with doors/windows for portals
    - Well suited for recursive functions.

    PVS PIPELINE:
	1) Subdivide scene into convex regions called sectors
	2) Calculate what other sectors can be seen by each one
	3) Render scene from viewer's position with a viewing frustum
	4) If a portal is seen into another sector clip the frustum using 
       the portal as a guide for dimensions
	5) Connecting sector is rendered but using the new frustum

//////////////////////////////////////////////////////////////////////////////  
//PRIMITIVES
//////////////////////////////////////////////////////////////////////////////  

POINT LISTS:  .    .    . .   .
LINE LIST: ._________________. 
LINE STRIP: ._______._______.___._______._____.

TRIANGLE LISTS:
	 __
	|\ | Triangle1 {1,2,3} Limitation is no sharing of vertices
	|_\| Triangle2 {3,4,1} which increases vertex count

TRIANGLE STRIPS: 
	 ___
	|\ |\  Specify first four points then one
	|_\|_\ point for every new triangle in strip

TRIANGLE FANS:
	 ____
	|\  /| All triangles connect
	| \/ | to a common point
	| /\ |
	|/__\|

CONVEX POLYGONS: line between two points in polygon never crosses border 
CONCAVE POLYGONS: line between two points in polygon can cross border
