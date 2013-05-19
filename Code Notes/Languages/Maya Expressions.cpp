///////////////////////////////////////////////////////////////////////////////////////////////////////
//MAYA EXPRESSIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//RUNTIME EXPRESSION: Used frame-by-frame 
//CREATION EXPRESSION: Used only once when particle first appears in scene

//PER-PARTICLE ATTRIBUTE: For each individual particle
//PER-OBJECT ATTRIBUTE: for all particles as a whole

//==============================================================================
//PER-PARTICLE ATTRIBUTES
//==============================================================================

pShape.velocity = <<x,y,z>>; //VELOCITY
pShape.lifespanPP = $seconds; //LIFESPAN
pShape.rgbPP = <<r,g,b>>; //RGBPP [COLOR DYNAMIC ATTR]
pShape.radiusPP = $myFloat; //RADIUSPP [GENERAL DYNAMIC ATTR]

//LINKING ATTRIBUTES
pShape.velocity = pShape.radiusPP;
pShape.velocity = <<0,(pShape.radiusPP*2),0>>;
