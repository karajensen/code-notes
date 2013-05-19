//////////////////////////////////////////////////////////////////////////////
//CLOTH SIMULATION
//////////////////////////////////////////////////////////////////////////////
/*
    |     |
  --▪-----▪--
    |\   /|     Stretch/Compression: Horizontal/Vertical springs
    | \▪/ |     Shear: Diagonal springs
    | / \ |     Bending: Structural contraints or link every second horizontal
    |/   \|              and vertical vertex
  --▪-----▪--
    |     |

 SINGLE SPRING MODEL:
 --------------------------------------------------------------------
    r        Fˢ(t) = -kˢx(t)     
 ▪ᵃ~~~▪ᵇ     Fᵈ(t) = -kᵈv(t)
             F(t) = Fˢ(t) + Fᵈ(t) + mg
             a(t) = (¹/m)F(t)
 --------------------------------------------------------------------
 Fˢ(t) = Force due to spring compression/extension
 Fᵈ(t) = Force used to dampen the spring and stop is oscillating
 x(t) = (∆length of spring)̂x = (‖r‖ - l₀)x̂ = (‖r‖ - l₀)x̂ = (‖x(t)-x(0)‖ - l₀)x̂
 v(t) = vᵇ(t) - vᵃ(t)

 F(t) = Fˢ(t) + Fᵈ(t) + mg
 a(t) = (1/m)(Fˢ(t) + Fᵈ(t) + mg)


//////////////////////////////////////////////////////////////////////////////
//PARTICLES/FLUID SIMULATION
//////////////////////////////////////////////////////////////////////////////

VISCOSITY = Thickness, internal friction and resistance to flow
SURFACE TENSION = Resistance of external objects/forces
BUOYANCY = Upward acting force by water on objects
WAVE DAMPENING = Wave aging
INTERNAL PRESSURE = Pressure each particle exerts on the others to deform
EXTERNAL PRESSURE = Pressure daemons/emitters exert on particles to deform
WATER DENSITY = 1000

==================================================================
BUOYANCY EFFECT
==================================================================

SINK: Object Density > Liquid Density
FLOAT: Object Density < Liquid Density

--------------------------------
| DENSITY = MASS / VOLUME(m³) |
--------------------------------
Increasing Mass increases Density

*//////////////////////////////////////////////////////////////////////////////
