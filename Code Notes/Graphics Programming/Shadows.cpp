//////////////////////////////////////////////////////////////////////////////
//SHADOWS
//////////////////////////////////////////////////////////////////////////////
/*

OCCLUDER: Any object in scene that casts shadows
UMBRA: Region that is completely in shadow and fully occluded
PENUMBRA: Area outside the umbra that gradually softens with distance

//////////////////////////////////////////////////////////////////////////////
//SHADOW MAPPING
//////////////////////////////////////////////////////////////////////////////

CREATING SHADOW MAP
• Look at scene from point of view of light source 
• Create shadow map via writing scene depth to rendertarget from the 
  light's perspective

USING SHADOW MAP
• Transform vertex by light view projection matrix to get position 
  in light space
• If depth in shadow map is /w, make sure /w for position in pixel shader
• Compare this to the position saved in the shadow map (also in light space)
• If depth is further away than the depth in shadow map the object is 
  in shadow of another object

ADVANTAGES:
 Cheaper to use
 Easy to blur and make into soft shadows

DISADVANTAGES:  
 Dependent on size/depth of shadow map
 Suffers from artefacts/aliasing problems
 STITCHING ARTIFACTS:
    Occurs when depth value of shadow is close to surface
    Solved by offsetting the shadow depth value retrieved by an amount
    Solved by turning on front-face cull when creating shadow map

//////////////////////////////////////////////////////////////////////////////
//SHADOW PROJECTION
//////////////////////////////////////////////////////////////////////////////

Shadow-projection matrix is created to scale anything rendered with it into 
a flat shape. Light direction is used to control direction from which shadows 
appear once rendered. The object is projected onto a plane then rendered 
as a separate primitive.

SHADOW IMPOSTER: 
Use of rendering simple object underneath model to represent shadow

ADVANTAGES:     
 Easy to implement
 Doesn't require any hardware support such as shadow mapping
 Shadows can be created out of any object or an imposter can be used

DISADVANTAGES:  
 Doesn’t work well on specular surfaces 
 Difficult with non-flat surfaces, stencil buffer fixes this
 Can’t render self shadows
 Difficult to make into soft shadows
 Not a good representation of object
 Z-FIGHTING: 
  close coplanar planes confuses the depth buffer for what to render first
  Fixed by rendering at an offset or enabling hardware to take care of offset

//////////////////////////////////////////////////////////////////////////////
//SHADOW VOLUMES
//////////////////////////////////////////////////////////////////////////////

Project the outline of an object into the scene based on the light position. 
New geometry is created using this silhouette.

PIPELINE:
- Find the edges of an object that define the silhouette and create edge list
- Calculate new geometry from the edge list and the light vector and store 
  into its own vertex buffer
- Create a counter that will increment/decrement for every surface rendered 
  to the stencil buffer
- Render scene with back-face culling on; increment for every surface rendered
- Render with front-face culling on; decrement for every surface rendered
- If an object is within a shadow volume after two stencil tests the stencil 
  buffer will have 1, if not, 0
- Clear the screen to black
- Render scene normally using results to only render to screen pixels set to 
  0, leaving sections with 1 black

CARMAK'S REVERSE:
 If camera is inside a shadow volume counting for stencil buffers can be 
 incorrect. Pixels that should not be in shadow are considered in shadow. 
 Solution:  
    - Render with front-face culling first and increment stencil buffer 
      whenever depth test fails
    - Render with back-face culling second and decrement stencil buffer 
      whenever depth test fails


ADVANTAGES:     
 No aliasing/artefact problems
 Can self shadow
 More accurate representation of model

DISADVANTAGES:  
 Geometry dependent/expensive
 Requires additional data for quick determination of silhouette 
 (object edge list)
 Difficult to make into soft shadows
 
//////////////////////////////////////////////////////////////////////////////
//SOFT SHADOWS
//////////////////////////////////////////////////////////////////////////////

SHADOW MAP: 
    - Render only shadows from the shadow map onto a surface and blur using 
      a bloom filter
    - Scene rendered again blending the soft shadows into the scene

SHADOW PROJECTION/VOLUME:
    - Jittering: Render the shadow more than once, each time in a different 
      position and blend with previous renders
    - Use two objects: One for the umbra and one for penumbra, 
      fading out penumbra 

*//////////////////////////////////////////////////////////////////////////////