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
Rays traced from light into 3D scene
Calculates new direction of rays when hitting surface
Ideal for reflections/refractions
Quality increases with more rays
Disadvantage: hard to optimise, not possible in real time
Disadvantage: lots of wasted rays that won't hit objects

------------------------------------------------------------------------------
BACKWARD RAY-TRACING [RAY CASTING]
------------------------------------------------------------------------------
Rays traced from camera into 3D scene
Does not compute new direction a ray takes after reflections/refractions
Ray sent for each pixel; number of rays depends on screen resolution
Every pixel will always be shaded; less rays/faster than raytracing

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
intersection of objects. Takes into account indirect lighting/global illumination 

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
//TRANSFORMATIONS
////////////////////////////////////////////////////////////////////////////// 

----------------
|  YAW:    Y   |
|  PITCH:  X   |
|  ROLL:   Z   |
----------------

EULER ANGLES
• Set of pitch, roll, yaw combined to form a matrix
• Suffer from gimbal lock
• Less storage space needed (3 values)

MATRICES: 
• Suffer from gimbal lock if used with Euler Angles
• More storage space needed (12 values)
• Slow, rounding errors

QUATERNIONS: 
• No Gimbal lock
• Less storage space needed (4 values)
• Fast, less rounding errors

GIMBAL LOCK
• A set of three gimbals mounted together to allow three degrees of freedom
• If the middle gimbal is rotated greater than 90, the top and bottle gimbals 
  are aligned and in gimbal lock losing a degree of freedom. 

==============================================================================
VIEW MATRIX
Inverse of the Camera World Matrix
changes the world scene basis so the camera is at the origin
==============================================================================

FLY-CAMERA
Assumes orthogonality with view matrix
matView._11 = right.x;    matView._12 = up.x;   matView._13 = forward.x;
matView._21 = right.y;    matView._22 = up.y;   matView._23 = forward.y;
matView._31 = right.z;    matView._32 = up.z;   matView._33 = forward.z; 
matView._41 = -D3DXVec3Dot(&pos,&right); 
matView._42 = -D3DXVec3Dot(&pos,&up);
matView._43 = -D3DXVec3Dot(&pos,&forward);

LOOKAT-CAMERA
D3DXMatrixIdentity(&m_world);
m_world._41 = pos.x;
m_world._42 = pos.y;
m_world._43 = pos.z;
D3DXMATRIX matRX, matRY, matRZ;
D3DXMatrixRotationX(&matRX, m_pitch); 
D3DXMatrixRotationY(&matRY, m_yaw);
D3DXMatrixRotationZ(&matRZ, m_roll);
m_world *= matRZ * matRX * matRY;
D3DXMatrixInverse(m_view.MatrixPtr(), nullptr, &m_world.GetMatrix());

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

///////////////////////////////////////////////////////////////////////////////////////
//OPTIMISATION
///////////////////////////////////////////////////////////////////////////////////////

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

Potential Visible Sets:
- The list a node keeps of which other nodes it can potentially see
- Pre-computed data which is then indexed at run time to quickly 
  obtain an estimate of the visible geometry. 
- The camera view-space is subdivided into convex regions
- PVS is computed for each region.
- Convex areas are called SECTORS. 
- Adjacent sectors are linked to one another via PORTALS
- Best for indoor games with doors/windows for portals
- Well suited for recursive functions.

1) Subdivide scene into convex regions called sectors
2) Calculate what other sectors can be seen by each one
3) Render scene from viewer's position with a viewing frustum
4) If a portal is seen into another sector clip the frustum using 
   the portal as a guide for dimensions
5) Connecting sector is rendered but using the new frustum

OPTIMIZATION TIPS
• Don’t allocate stencil if you don’t use it
• R5G6B5 color sufficient for dynamic reflection maps
• Use low resolution (<256x256) 8-bit normalization cube-maps
• Use half instead of float where strict precision isn't important
• Render a depth-only pass before color pass to reduce pixel shader use

///////////////////////////////////////////////////////////////////////////////////////
//PRIMITIVES
///////////////////////////////////////////////////////////////////////////////////////

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

*/////////////////////////////////////////////////////////////////////////////