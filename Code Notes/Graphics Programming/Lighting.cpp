//////////////////////////////////////////////////////////////////////////////
//LIGHTING TYPES
//////////////////////////////////////////////////////////////////////////////
/*
---------------------------------------------------------------
DIRECTIONAL LIGHTS [Direction only]
---------------------------------------------------------------
Used to represent broad light source at a distance, illuminating whole scene
Light moves in one direction, hitting surfaces, no attenuation used
Not affected by attenuation and range

---------------------------------------------------------------
POINT/OMNI LIGHTS [Position only]
---------------------------------------------------------------
Emits light from all directions
Affected by attenuation and range

---------------------------------------------------------------
SPOT LIGHTS [Direction and Position]
---------------------------------------------------------------
Emits light in one direction that spreads out as distance increases
Affected by falloff, attenuation, and range and uses theta/phi values
Vertex position within inner or outer cone is determined to determine 
the brightness

THETA VALUE: Radian angle of the spotlight's inner cone (brightest)
PHI VALUE: Radian angle for the outer cone of light
FALLOFF: Controls how light intensity decreases between the outer and inner 
         cones; set as 1 for even

---------------------------------------------------------------
BLOOM LIGHTS
---------------------------------------------------------------
Glow around an object that resembles a halo
Occurs when eyes/camera suddenly views a very bright object

    1) Render main scene to render target
    2) Draw down-sampled version of scene to second rendertarget, blurring 
       only the brightest pixels
    3) Blend both together

---------------------------------------------------------------
LENS FLARE
---------------------------------------------------------------
Scattered light reflected from within the cameras lens

---------------------------------------------------------------
LIGHT SHAFTS
---------------------------------------------------------------
Light scatters off‘particles’ suspended in the media (Dust, water vapour)
Occurs when light enters/exits materials such as a window
Draw polygons emitting from light source and use additive blending
As polygon's vertices become more distant from light they become more 
transparent

//////////////////////////////////////////////////////////////////////////////
//DIRECT LIGHTING
//////////////////////////////////////////////////////////////////////////////

EMISSIVE
How much light is emitted from object

ATTENUATION
How much light fades into distance

DIFFUSE
The amount of light hitting a given point on a surface depends on the position
of the lights around the surface and the direction the surface is facing.

SPECULAR
Light reflecting near/exactly in the opposite direction of incoming light

REFLECTION
Rasterization uses reflection vector as set of coordinates to get colour from 
cube map. Ray tracing uses primary ray which is reflected and used to trace 
the scene and see what objects the ray hits. Colour chosen is combined with 
color of original object that was reflected

REFRACTION
When light passes through two different materials of different densities the 
light direction changes. RI = Refractive index of material passing into


//////////////////////////////////////////////////////////////////////////////
//INDIRECT LIGHTING
//////////////////////////////////////////////////////////////////////////////

GLOBAL ILLUMINATION/INDIRECT LIGHTING: 
Surfaces illuminated by light reflected off other surfaces
Often stored in light maps due to being expensive to calculate

---------------------------------------------------------------
INDIRECT LIGHTING EFFECTS FROM MATERIALS
---------------------------------------------------------------
If a light bounces off a diffuse surface a color-bleeding happens.
If a light bounces off a specular surface a caustics reflection happens. 
If a light travels through a refracted surface a refracted caustics happens.
If a light is absorbed by a surface and leaves from the opposite direction, 
subsurface scattering happens. 

COLOR/LIGHT BLEEDING: 
Light that has reflected off one surface to another bringing with it some of 
its color which is seen on the second surface

CAUSTICS: 
Reflection of light off a shiny object or focusing of light through a 
transparent object to produce bright highlights on another object

SUBSURFACE SCATTERING: 
Light enters, scatters around and leaves at a different point

AMBIENT
Light spread equally in all directions without falloff, constant value

---------------------------------------------------------------
AMBIENT OCCLUSION
---------------------------------------------------------------
- Used to define the occlusion amount of a point in the scene 
  (vertex or pixel depending on precision)
- Each point sends multiple rays into the scene and tests for intersection 
  against all geometry
- Or can send out rays to test against itself for self shadowing
- Ratio of hits/misses is added and average float is found for that point
- Average multiplied by ambient light

---------------------------------------------------------------
RADIOSITY
---------------------------------------------------------------
- Considers everything a light source, and every surface can potentially light
  another surface
- The scene is divided up into patches and a view factor/form factor is 
  computed for each one in relation to the others
- Form factor describes how well patches can see each other; far away or 
  obstructed means smaller factor
- Form factor used to generate the radiosity/brightness of each patch taking 
  into account diffuse/reflections/shadows etc.


//////////////////////////////////////////////////////////////////////////////
MATERIALS
//////////////////////////////////////////////////////////////////////////////

GOURAUD SHADING [DIFFUSE]: 
Per-vertex diffuse lighting using linear interpolation of colour between verts

BLINN-PHONG SHADING [SPECULAR]: 
Uses half-vector for specular calcuation

PHONG SHADING [SPECULAR]: 
Uses reflection-vector for specular calcuation

BIDIRECTIONAL REFLECTANCE DISTRIBUTION FUNCTION (BRDF):
Describes how an object reflects/absorbs light from different angles

CONDUCTIVE MATERIALS (metals)                    
Reflections are tinted

DIELECTRICS (non-metals)
Reflections are always white except when abosorption/transmission of light 
occurs, tinting the light (ie. subsurface scattering)
 
FRESNAL RULE
Gives the ratio of reflected/absorbed light for a surface