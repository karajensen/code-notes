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

PHOTONS = Transfer energy, Scene lighting/colour
		  Light ---> Scene ---> Camera
		  USED: Global Illumination/Caustics

RAYS = Transfer energy, Scene lighting/colour
	   Points/Particles ---> Scene ---> Original Points/Particles
	   USED: Final Gathering, Irradiance Particles

IMPORTONS = Scene lighting/colour only
			Camera ---> Scene ---> Light
			USED: Importons


ANTIALIASING QUALITY
-----------------------------------------------------------------------------------
	RAYTRACE/SCANLINE QUALITY:
		SAMPLING: Level of AA; Smoothing noise/speckled areas

RAYTRACING
-----------------------------------------------------------------------------------
	REFLECTIONS: Number of times rays will bounce to calculate reflections
	REFRACTIONS: Number of times rays will continue through an object with refractive properties
	MAX TRACE DEPTH: Reflections + Refractions to achieve all reflections/refractions
	SHADOWS: Number of shadow rays
	


///////////////////////////////////////////////////////////////////////////////////////////////////////
//PRE-RENDERED SCENE SETUP
///////////////////////////////////////////////////////////////////////////////////////////////////////


=============================================================================
DEPTH OF FIELD CONTROL:
=============================================================================
LIGHT:	Smaller iris opening in camera = less exposure and light entering = more depth of field
		Larger iris opening in camera = more exposure and light entering = less depth of field
	
FOCAL LENGTH: Wide angle/short focal length lens = greater DOF
			  Narrow angle/long focal length lens = smaller DOF

CAMERA-TO-SUBJECT DISTANCE: Subject far away = greater DOF
							Subject up close = smaller DOF


=============================================================================
3 POINT DIRECT LIGHTING SETUP:
=============================================================================
KEY LIGHT: light source the scheme is built around; main provider of light
		   Placed 45 degrees horizontally/vertically to camera above subject's head
		   USE: Directional Light

FILL LIGHT: Helps control contrast by filling in dark shadows created by key light
			USE: 
	
BACK LIGHT: Defines the edge around the subject and seperates them from background
			USE:


=============================================================================
ENVIRONMENT/HDRI MAPS
=============================================================================
	- Poly Sphere with SURFACE SHADER and HDRI image around scene
	- IBL Mental Ray object with HDRI image around scene


=============================================================================
PASS/RENDER LAYERS
=============================================================================
RENDER LAYER: Renders seperately each layer; extra time added
			  Create 2 layers: Main and Occlusion

RENDER PASS: Splits buffers to create seperate passes; no extra time
			 Works with all Maya nodes, MR nodes with passes in name
			 May not work with photons; see video 17 in MR basics if not

CONTRIBUTION MAP: Render passes splitting objects up
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

TO USE: Turn on GI in MR Features and Indirect Lighting
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

TO USE: Object needs Refractive properties in material
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

FG: Final Gathering Points are placed around the scene
	Each sends out rays to sample surrounding environment
	Return information back to Points and filter/blend accross neighbours

TO USE: Turn on FG in MR Features and Indirect Lighting

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

IMPORTONS:  Cast from camera to points of importance in scene that camera can see
			Bounce around scene gathering colour/lighting/shading information
			Move from Camera towards Light in Raycasting fasion

IRRADIANCE PARTICLES: Created where Importons were from the information gathered
					  Send out rays from each particle to sample surrounding environment
					  Return information back to particle and filter/blend accross neighbours

TO USE: Cannot be used with GI/Final Gathering


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
//DISPLACEMENT IN MENTAL RAY
///////////////////////////////////////////////////////////////////////////////////////////////////////

--------------------------------------------
MAYA DISP. IMAGE COLOR BALANCE FIXES:
--------------------------------------------
Z-BRUSH 32bit TIFF
	Alpha Gain: 2.2
	Alpha Offset: -1.1

MUDBOX

--------------------------------------------
MENTAL RAY DISPLACEMENT OVERRIDES:
--------------------------------------------

MR APPROXIMATION EDITOR
Create new SUBDIVISION and assign Approx. to desired objects

	PARAMETRIC (Absolute Subdivision)
		SUBDIVISION: Number of times mesh is devided

	LENGTH,DISTANCE,ANGLE (Relative Subdivision)
		MIN/MAX SUBDIVISION: Devision Cap
		VIEW DEPENDENT: OFF(Object space measurement) ON(Pixel measurement) 
		LENGTH(0.1): Subdivide until no edges are longer than x length
			  (0.5): Subdivide until no edges are larger than x pixels

