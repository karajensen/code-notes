//////////////////////////////////////////////////////////////////////////////
//INTEGRATION METHODS
//////////////////////////////////////////////////////////////////////////////
/*

EULER'S METHOD: 
 ----------------------------
| X(t + ∆t) = X(t) + X▪(t)∆t |
 ---------------------------------------------
| X(t + ∆t) = X(t) + X▪(t)∆t + (∆t²/2) X▪▪(t) |
 ---------------------------------------------
 
- a truncated version of Taylor's series
- Step size determines the size of the steps taken to reduce error towards 0

INCREASING ACCURACY
- Euler's method is accurate to ∆t
- next largest term in Taylor's series is (∆t²/2) X▪▪(t)
- ⁂ precision error is to the order of ∆t²; if step size is halfed, 
  error is reduced by four
- To increase accuracy, get estimate of X▪▪(t) using Midpoint Method

MIDPOINT METHOD
- Get X▪(t) at ∆t and t + ∆t and average them to find X▪▪(t)
- increases accuracy to (∆t²/2) but increases amount of computations

===========================================================================
EXPLICIT METHODS
===========================================================================
Use calculations from current time to estimate for the future
Underestimate curve: Curve will slowly expand and gain energy over time
Inexpensive per step but with limited accuracy

FORWARD EULER INTEGRATOR
X(t + ∆t) = X(t) + X▪(t)∆t 

4th ORDER RUNGE KUTTA
Bad for high impulses with high change of velocity
High accuracy but more computation
X(t + ∆t) = X(t) + ¹/₆k₁ + ¹/₃k₂ + ¹/₃k₃ + ¹/₆k₄

===========================================================================
IMPLICIT METHODS
===========================================================================
Use calculations from future with current time to estimate for the future
Overestimate curve: Curve will slowly collapse and lose energy over time
Higher accuracy but expensive per step

BACKWARD EULER INTEGRATOR
Uses a estimate of the velocity at the next timestep 
via an analytical function
X(t + ∆t) = X(t) + ∆tX▪(t + ∆t)


===========================================================================
SEMI-IMPLICIT METHODS
===========================================================================
No net energy loss/gain; curve won't collapse or expand

X(t + ∆t) = X(t) + ∆tX▪(t + ∆t)         IMPLICIT EULER METHOD
where X▪(t + ∆t) = X▪(t) + ∆tX▪▪(t)     EXPLICIT EULER METHOD


===========================================================================
VERLET INTEGRATION
===========================================================================
Good for position dependent forces (springs)
X(t + ∆t) = X(t) + X▪(t)∆t + (∆t²/2) X▪▪(t)
X(t - ∆t) = X(t) - X▪(t)∆t + (∆t²/2) X▪▪(t)
X(t + ∆t) + X(t - ∆t) = 2X(t) + ∆t²X▪▪(t)

⁂ X(t + ∆t) = 2X(t) - X(t - ∆t) + ∆t²X▪▪(t)


===========================================================================
STIFF EQUATIONS
===========================================================================
▪ Differential equation for which explicit integration is unstable unless 
  using extremely small timesteps
▪ Faster/more stable/more accurate to use implicit methods with larget 
  timestep than explicit with small timestep

Eg(1): FOR EQUATION: dx/dt = -kx

 USING EXPLICIT EULER                 USING IMPLICIT EULER
 as k∆t --> ∞ position becomes        as k∆t --> ∞ position gets
 unstable                             closer to zero which is accurate
 x(t+∆t) = x(t) + ∆tv(t)              x(t+∆t) = x(t) + ∆tv(t+∆t)
         = x(t) + ∆t(-kx(t))                  = x(t) + ∆t(-kx(t+∆t))
         = (1-k∆t)x(t)                        = x(t)/(1+k∆t)


