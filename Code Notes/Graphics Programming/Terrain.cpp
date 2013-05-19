//////////////////////////////////////////////////////////////////////////////
//TERRAIN: MIDPOINT DISPLACEMENT ALGORITHM
//////////////////////////////////////////////////////////////////////////////
/*
- Start with basic four vertex shape and slip by adding vertex in middle
- Get x/z values of middle vertex from midpoint of surrounding vertices
- Get y value of middle vertex from a value between -d/2 and d/2
- Continue to split new four faces multiplying d by 2^-r each time
- Filter to remove sharp transitions
- Smaller R = rougher terrain

//////////////////////////////////////////////////////////////////////////////
//TERRAIN: FAULT FORMATION ALGORITHM
//////////////////////////////////////////////////////////////////////////////

- Starts with grid for terrain and creates random line accross the terrain
- Raise vertices on one side of the line and lower on other by amount d
- Create another line and repeat, reducing d each pass
- More passes = rougher terrain

//////////////////////////////////////////////////////////////////////////////
//TERRAIN: CLIP MAPPING ALGORITHM
//////////////////////////////////////////////////////////////////////////////

• Terrain geometry is cached in rings which are shifted as the viewer moves
• As viewer moves, clipmap rings are shifted and updated with new data in z 
  component from a large texture
• Transition area and Vertex/Pixel shaders help blend/hide transitions 
  from one ring to the next
• Only the required levels are rendered depending on the height of the camera

CLIPMAP RINGS/LEVELS:
• Each level/ring has its own elevation texture, normal texture and 
  shares the vertex/index buffer
• (x,y) coordinates are stored in a readonly constant vertex/index buffer
• (z) coordinate is stored in single channel 2D texture
• Elevation map is updated via lookups in the large texture as camera moves
• Elevation maps and shared buffers are stored in video memory
• Each ring is of size 2ᵏ-1 leaving one row/column unused
• Normal map is 32-bit buffer 

SHARED VERTEX/INDEX BUFFER:
• Each ring can be broken into 2D footprints or 'tetris blocks' (see image)
• Buffers hold data for one ring only and scale/translate it depending on 
  the ring position/size
• Any gaps (interior trim) that are between the rings are filled in

VERTEX SHADER:
- Converts local (x,y) coordinates from shared index/vertex buffer to world 
- Reads z value from Elevation map stored in a vertex texture 
- Blends geometry near the outer boundary of each level with that of 
  the next-coarser level

PIXEL SHADER:
- Uses Generated Normal map to shade the surface

ON UPDATE:
• Regions of each level/ring is updated as the camera moves
• Elevation/Normal textures written to using a pixel shader

*/////////////////////////////////////////////////////////////////////////////