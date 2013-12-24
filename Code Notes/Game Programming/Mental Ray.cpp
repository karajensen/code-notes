///////////////////////////////////////////////////////////////////////////////////////////////////////
//MENTAL RAY: RAY-TRACER
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*

GLOBAL ILLUMINATION: sends photons from light source into scene
CAUSTICS: sends photons from light souce into scene to create light bands
FINAL GATHERING: sends rays from final gather points into scene and back
IMAGE BASED LIGHTING: uses HDRI image to simulate multiple directional lights
PHYSICAL SUN/SKY: Simulates outdoor lighting with Final Gathering
LENS SHADERS: Post processing effects on camera

FG/GI IN COMBINATION:
 - Final gathering less accurate, smoother results, quicker
 - Global Illumination more accurate, rougher results, slower
 - Used together the FG will smooth out the G

PHOTONS :
 - Transfer energy, Scene lighting/colour
 - Light ---> Scene ---> Camera
 - Used: Global Illumination/Caustics

RAYS:
 - Transfer energy, Scene lighting/colour
 - Points/Particles ---> Scene ---> Original Points/Particles
 - Used: Final Gathering, Irradiance Particles

IMPORTONS:
 - Scene lighting/colour only
 - Camera ---> Scene ---> Light
 - Used: Importons

REFLECTIONS: Number of times rays will bounce to calculate reflections
REFRACTIONS: Number of times rays will continue through an object with refractive properties
MAX TRACE DEPTH: Reflections + Refractions to achieve all reflections/refractions
SHADOWS: Number of shadow rays
 
///////////////////////////////////////////////////////////////////////////////////////////////////////
//PASS/RENDER LAYERS
///////////////////////////////////////////////////////////////////////////////////////////////////////

RENDER LAYER:
Renders seperately each layer; extra time added
Create 2 layers: Main and Occlusion

RENDER PASS: 
Splits buffers to create seperate passes; no extra time
Works with all Maya nodes, MR nodes with passes in name
May not work with photons; see video 17 in MR basics if not

CONTRIBUTION MAP: 
Render passes splitting objects up
Create new map, add objects to map
Create render passes using MapName_ in prefix
Choose Associated Pass Contribution Map and drop desired passes in

PASSES TO CHOOSE IF USING MIA_MATERIAL:
    - Beauty
    - Indirect
    - Diffuse
    - Reflection
    - Refraction
    - Specular
    - Translucence

///////////////////////////////////////////////////////////////////////////////////////////////////////
//GLOBAL ILLUMINATION 
///////////////////////////////////////////////////////////////////////////////////////////////////////

TO USE: 
Turn on GI in MR Features and Indirect Lighting
Turn on GI for the light to emit photons
Use seperate light for emitting photons

----------------------------------------------------------------------------
LIGHT ATTRIBUTES
----------------------------------------------------------------------------
PHOTON INTENSITY(2000): Light intensity of each photon sent out
EXPONENT(2): How fast photons lose energy after release
GLOBAL ILLUM. PHOTONS(10000): Total number of photons released

----------------------------------------------------------------------------
RENDER SETTINGS
----------------------------------------------------------------------------
ACCURACY(1000)
 - Maximum number of photons per sample
 - Increase = less noisy, more blurry, greater rendering time

RADIUS(5)
 - Size of the photos
 - Default value = takes the radius of 1/10 of the scene size for each photon

MERGE DISTANCE(0.2)
 - Merge nearby photons below distance specified
 - Higher value = smoother, less detailed photon map using less memory
 - Default value = off

FILTER
 - Increasing helps reduce unnateral bright/dark areas and evens out lighting

///////////////////////////////////////////////////////////////////////////////////////////////////////
//CAUSTICS
///////////////////////////////////////////////////////////////////////////////////////////////////////

TO USE: 
Object needs Refractive properties in material
Turn on Caustics in MR Features and Indirect Lighting
Turn on Raytracing in MR Quality
RT Refractions needs to have a high enough level to pass through object(s)
Turn on Caustics for light to emit photons
Use seperate light to Global Illumination light (spot light for focused objects)
If using MIA set Advanced Refraction to Use Caustics

----------------------------------------------------------------------------
LIGHT ATTRIBUTES
----------------------------------------------------------------------------
PHOTON INTENSITY(3000) = light intensity of each photon sent out
EXPONENT(2) = how fast photons lose energy after release
CAUSTIC PHOTONS(100000-500000) = total number of photons released, higher for sharper effects

----------------------------------------------------------------------------
RENDER SETTINGS
----------------------------------------------------------------------------
RADIUS(0.1-0.01)
 - Size of the photons
 - Small value helps sharp effects

ACCURACY(100)
 - Higher = more photons will blur/blend together
 - Lower = helps sharp effects

MERGE DISTANCE(0)
 - Merge nearby photons below distance specified
 - Default value helps sharp effects

///////////////////////////////////////////////////////////////////////////////////////////////////////
//FINAL GATHERING
///////////////////////////////////////////////////////////////////////////////////////////////////////

TO USE: 
Turn on FG in MR Features and Indirect Lighting
Final Gathering Points are placed around the scene
Each sends out rays to sample surrounding environment
Return information back to Points and filter/blend accross neighbours

----------------------------------------------------------------------------
RENDER SETTINGS
----------------------------------------------------------------------------
ACCURACY(200)
 - Number of rays per final gather point cast

POINT DENSITY(1)
 - Number of final gather points in scene

POINT INTERPOLATION(30)
 - Number of final gather point considered for smoothing
 - Higher = smoother shading, more computation

DIFFUSE SCALE(1)
 - Amount of FG used after the calculations

SECONDARY DIFFUSE BOUNCES(1)
  - Number of bounces rays will go through scene
  - Used to better simulation GI effects

///////////////////////////////////////////////////////////////////////////////////////////////////////
//IRRADIANCE PARTICLES/IMPORTONS
///////////////////////////////////////////////////////////////////////////////////////////////////////

TO USE: Cannot be used with GI/Final Gathering

IMPORTONS:  
Cast from camera to points of importance in scene that camera can see
Bounce around scene gathering colour/lighting/shading information
Move from Camera towards Light in Raycasting fasion

IRRADIANCE PARTICLES: 
Created where Importons were from the information gathered
Send out rays from each particle to sample surrounding environment
Return information back to particle and filter/blend accross neighbours

----------------------------------------------------------------------------
IMPORTONS RENDER SETTINGS
----------------------------------------------------------------------------
DENSITY(0.02)
 - Places x importons for every pixel of image, resolution dependent

MAX DEPTH(3)
 - Number of bounces importon goes through before reaching light source
 - Keep value under 5 otherwise high render times

----------------------------------------------------------------------------
IRRADIANCE RENDER SETTINGS
----------------------------------------------------------------------------
RAYS(256)
 - Number of rays emitted from each irradiance particles

INDIRECT PASSES(2)
 - Number of secondary bounces rays achieve when hitting objects

INTERPOLATE(always)
 - Always = blending between points
 - Never = no blending, more noise
 - Secondary = only interpolate secondary rays produced

INTERPOINTS
 - Number of neighbouring points used to smooth each point

ENVIRON. RAYS(256)
 - Set to same number of normal rays

///////////////////////////////////////////////////////////////////////////////////////////////////////
//IMAGE BASED LIGHTING
///////////////////////////////////////////////////////////////////////////////////////////////////////

QUALITY: Amount of lights in IBL 
SAMPLES: The amount of lights used in calculations for shadows (horizontal, vertical)
VARY FOCUS: Randomises shadow rays and helps reduce shadow banding 
COLOR GAIN: Intensity of lights in IBL

///////////////////////////////////////////////////////////////////////////////////////////////////////
//PHYSICAL SUN/SKY SHADER
///////////////////////////////////////////////////////////////////////////////////////////////////////

ADDS: Final Gathering
      Lens shader to camera
      Directional Light; rotation controls time of day

INDOORS: Area light in front of window area
         Custom Shaders -> Light Shader -> MIA_PORTAL_LIGHT
         Area Light -> Use Light Shape/Visible ticked
         Increase Accuracy and Point interpolation for FG
         Increase Portal Light Intensity
         RGB Unit Convesion: 0.318 for Lens shader to work
         Add custom Lens Shader to camera: MIA EXPOSURE PHOTOGRAPHIC

====================================================================
PHYSICAL SKY
====================================================================
    
MULTIPLIER: Intensity of Sky effect
RGB CONVERSION: Intensity of color values; adjust if using photographic exposure node
HAZE: Amount of dust in environment, scattering of light, gives slight red hue
RED/BLUE SHIFT: Positive shifts to red, Negative shifts to blue
SATURATION: Saturation of sky
HORIZON HEIGHT: Cutoff point where sky meets ground
HORIZON BLUR: Blur between ground and horizon
GROUND COLOR: Color of ground
SUN DIRECTION: Determines time of day
SUN DISK INTENSITY: Visibility/Intensity of Sun circle
SUN GLOW INTENSTIY: Intensity of surrounding glow of Sun circle
USE BACKGROUND: Allows use of background image, none specified gives alpha background

====================================================================
PHYSICAL SUN
====================================================================

SHADOW SOFTNESS: Softness of shadows
SAMPLES: Number of samples for shadows


///////////////////////////////////////////////////////////////////////////////////////////////////////
//MENTAL RAY SHADERS
///////////////////////////////////////////////////////////////////////////////////////////////////////

SHADOW SHADER: Overrides Shadow of shader
PHOTONIC SHADER: Overrides Caustic/GI photons of shader

COOK-TORRANCE SHADER [mib_illum_cooktorr]: Phong shader variation with roughness
WARD SHADER [mib_illum_ward]: Controls placement of specular highlights
CARD OPACITY [mip_card_opacity]: Allows opacity of textured planes to show in depth/vector blur map renders

=========================================================================
DIELECTRIC MATERIAL SHADER [dielectric_material]
=========================================================================
Used for glass and water shading, particular water in a glass

OUTSIDE COLOR/IOR: Used for dialetric-to-dialetric interactions
COL: Color of material
PHONG COEFFIENT: Specular highlights

=========================================================================
GLOSSY REFLECTION SHADER [mib_glossy_reflection]
=========================================================================
Creates blurred reflections

MAX DISTANCE: Distance reflections are from casting object
FALLOFF: Rate at which reflections go from sharp to blurred to disappeared
BASE MATERIAL: Plug in any other material to combine

=========================================================================
DGS MATERIAL SHADER [dgs_material]
=========================================================================
Diffuse, Glossy and Specular Shader used for combining blurred and sharp reflections

GLOSSY: blurred reflections
SPECULAR: sharp reflections
SHINY: less shiny = more blurred
SHINY U/V: Controls shape of highlight, make shiny = 0 to use

=========================================================================
SUBSURFACE SCATTERING SHADER [misss_fast_shader]
=========================================================================
FRONT SSS: Light from front of object partially penetrates surface and moves towards camera
BACK SSS: Light from back of object penetrates surface, moves through it and towards the camera
    
FRONT/BACK SSS RADIUS: how far penetrated into surface
WEIGHTS: Sum of Front SSS/Diffuse Weight < 1 
BACK SSS DEPTH: Set same as radius

=========================================================================
SUBSURFACE SKIN SHADER [misss_fast_skin_maya]
=========================================================================
MR Texture plugs into LM section in shader
misss_fast_lmap_maya plugs into LM port in shading group
MR Texture plugs into LM Write in LM shader

LIGHTMAP: Create new MR texture, width/height same size as render
SCALE CONVERSION: Higher level = less light able to pass through skin

=========================================================================
CAR PAINT SHADER [mi_car_paint_phen]
=========================================================================
Flake size is connected to object scale. Freeze transforms before applying shader

EDGE COLOR: Color around edges of car; darker version of base color
LIT COLOR: Area facing light source
FLAKE WEIGHT: Intensity of flakes
FLAKE STRENGTH: Higher amount of scattering of flakes
FLAKE SCALE: Flake size
FLAKE DECAY: Flake number dies out as car gets further away than x distance

=========================================================================
MIA MATERIAL SHADER [mia_material_]
=========================================================================

REFLECTION GLOSS: Blurred Reflection for lower values
REFLECTION FALLOFF: Anything outside x units from object isn't reflected
REFRACTION GLOSS: Blurred Refractions for lower values
REFRACTION FALLOFF: Anything outside x units from object isn't refracted
ANISOTROPHY: Shape of highlight 

=========================================================================
RAYSWITCH NODE [mip_rayswitch_] HIDDEN PRODUCTION SHADER
=========================================================================
Used for changing the results of the rays which hit a particlar surface

EYE: Shader applied to
ANY SECONDARY: All rays above (reflection, FG, refraction etc.)

///////////////////////////////////////////////////////////////////////////////////////////////////////
//MENTAL RAY TEXTURES
///////////////////////////////////////////////////////////////////////////////////////////////////////

TEXTURE LOOKUP [mib_texture_lookup]: Connect lookup to shader's diffuse slot
TEXTURE REMAP [mib_texture_remap]: Connect into vector coordinates; allows texture transforms, repeats
TEXTURE VECTOR [mib_texture_vector]: Connect into vector coordinates; sends UV information into shader

AMBIENT OCCLUSION [mib_amb_occlusion]: Set high samples(64) and set max distance(10)
FAST AMBIENT OCCLUSION [mib_fast occlusion]: Uses final gather

PROCEEDURAL TEXTURES: 
Connect Texture Vector into Coordinate slot, connect into Diffuse slot of shader
 - POLKADOT [mib_texture_polkadot]
 - WAVE [mib_texture_wave]

ROUND CORNERS NODE  Plug into Bump->Overall Bump slot in MR MIA material shader
[mia_roundcorners]: Set Radius in world space units to get bevel
                    Will merge seperate objects with same MIA material into one
                    To stop blend, use different MIA material or click allow different materials
                    Make sure normals are set to hard for edges
                    Doess not add new geometry; bends normals only

///////////////////////////////////////////////////////////////////////////////////////////////////////
//VOLUMETRIC MATERIALS
///////////////////////////////////////////////////////////////////////////////////////////////////////

VOLUME SHADER [mib_volume]: Max Distance pushes fog back

=========================================================================
PARTICIPATING VOLUME [parti_volume]
=========================================================================
Fills fog within geometry; Plug into shading group Volume Shader
For shadows/light streaks through fog plug MR light into light shader node for Maya lights

SCATTER: Color of fog
EXTINCTION: How far light is able to pass through fog
NONUNIFORM: Variation/cloudiness in light streaks passing through fog
MIN STEP LENGTH(0.01): Quality of fog 
MAX STEP LENGTH(0.1): Quality of fog

///////////////////////////////////////////////////////////////////////////////////////////////////////
//LENSES
///////////////////////////////////////////////////////////////////////////////////////////////////////

RENDER SUBSET [mip_render_subset]: Used to render specific objects from a scene that are not in any reflections
GAMMA GAIN [mip_gamma_gain]: Simplified version of mia_exposure_simple

=========================================================================
EXPOSURE PHOTOGRAPHIC [mia_exposure_photographic]
=========================================================================
FILM ISO(300)
- Film Speed; higher value makes film more sensitive to light
- Higher value = lighter result

CAMERA SHUTTER(100)
- Shutter speed; how fast shutter opens/closes
- Higher value = darker result

F NUMBER(16)
- Controls size of aparture
- Higher value = darker result

VIGNETTING(1)
- Higher value = darker at specific angles (ie room corners)

BURN HIGHLIGHTS(0.2)
- Intensity of bright hotspots

CRUSHED BLACKS(0.25)
- Intensity of dark areas

=========================================================================
DEPTH OF FIELD [physical_lens_dof]
=========================================================================
PLANE: Objects -x distance away from camera will be in focus
RADIUS: Strength of DOF, smaller is more focus, larger is less of scene in focus

=========================================================================
LENS BOKEH [mia_lens_bokeh]
=========================================================================
PLANE: Objects -x distance away from camera will be in focus
RADIUS: Strength of DOF, smaller is more focus, larger is less of scene in focus
SAMPLES: Smooth out DOF areas
BIAS: Changes shift from DOF to focused areas

///////////////////////////////////////////////////////////////////////////////////////////////////////
//OUTPUT SHADERS
///////////////////////////////////////////////////////////////////////////////////////////////////////

=========================================================================
MOTION BLUR NODE [mip_motionblur] HIDDEN PRODUCTION SHADER
=========================================================================
Creates render-time friendly motion blur

TO USE: 
Connect mip_motionblur message to camera, mr, miOutputShader in Hypershade
Render Settings: Motion Blur to Full, Shutter open/close both to 0
Camera Legacy Output Shaders: Turn on Color, Depth, Motion Vectors

SHUTTER(0.6): Strength of motion blur
FALLOFF(4.5): How rapidly the transition is from motion blurred to non blurred
BLUR ENVIRONMENT: Blurs any environments connected to camera
GAMMA(1): Transparency of motion blurred areas, must be 1 for .EXR or .HDR
PIXEL THRESHHOLD(4): Min distance pixel must move before MB applied
DEPTH WEIGHTING: Blurs objects closer more than objects further from camera
BACKGROUND DEPTH: How far furthest object is from camera
    
FINDING OBJECT FURTHEST FROM CAMERA:
    1) Create Locator at object's position
    2) Heads up display -> Turn on object details

=========================================================================
MOTION VECTOR NODE [mip_motion_vector] HIDDEN PRODUCTION SHADER
=========================================================================
Saves motion blur data into a color pass to use with compositing software

MOTION VECTOR PASS:
Describes the amount of pixel movement that's happening in a scene. 
Uses two LUMINANCE maps and combines them into one image using red/green
Amount of motion blur is determined by these amounts
X Translation: mapped into red channel where 0.5 is no movement
Y Translation: mapped into green channel where 0.5 is no movement

///////////////////////////////////////////////////////////////////////////////////////////////////////  
//MAYA OCEAN SHADER
///////////////////////////////////////////////////////////////////////////////////////////////////////  

==============================================================================
OCEAN ATTRIBUTES
==============================================================================
SCALE: Size of texture; smaller scale means smaller portion of texture used
TIME: Animation of waves
WIND UV: Wind direction in x/z axis
WAVE SPEED: How fast waves are going
NUM FREQUENCIES(15): Higher is more chaotic/noise in waves
WAVE DIR SPREAD(0.2): Changes randomness of min/max waves
WAVE LENGTH MIN(0.1): Min length of the waves
WAVE LENGTH MAX(10): Max length of the waves
FOAM EMISSION: Intensity of foam used
FOAM THRESHHOLD: Area of foam over waves
BUMP BLUR: Smooth out bump on waves
HORIZON FILTER: Blurs ocean further away near horizon; can create artifacts

==============================================================================
WAVE HEIGHT
==============================================================================
Smaller wave height gives more detail; Larger wave height gives less detail
BOX LEFT->RIGHT = Waves sorted by smallest to largest wavelength
BOX BOTTOM->TOP = Wave Height, 0 is flat

==============================================================================
WAVE TURBULENCE
==============================================================================
Controls amount of chaos in winds direction
BOX LEFT->RIGHT = Waves sorted by smallest to largest wavelength
BOX BOTTOM->TOP = Regularity/chaos of waves

==============================================================================
WAVE PEAKING
==============================================================================
Sharpness of the waves; pinches the tops of waves
BOX LEFT->RIGHT = Waves sorted by smallest to largest wavelength
BOX BOTTOM->TOP = Level of pinching of waves

==============================================================================
MATERIAL ATTRIBUTES
==============================================================================
TRANSPARENCY: Overall transparency of water
INCANDESCENCE: Water emits light
TROUGH SHADOWING: Darkens lowest areas of water
TRANSLUCENCE:
TRANSLUCENCE FOCUS:
TRANSLUCENCE DEPTH:

==============================================================================
SPECULAR SHADING
==============================================================================
SPECULARITY: Intensity of specular highlights
ECCENTRICITY: Area amount of specular highlights
REFLECTIVITY: Amount of reflectivity

*//////////////////////////////////////////////////////////////////////////////////////////////////////