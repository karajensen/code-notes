//////////////////////////////////////////////////////////////////////////////
//STATE SPACE MODELS
//////////////////////////////////////////////////////////////////////////////
/*

LINEAR SYSTEM:      X▪(t) = AX(t) + Bu(t)  Use matrix A/B every timestep
NON-LINEAR SYSTEM:  X▪(t) = f(X(t),u(t))   Use integration methods every 
                                           timestep

USER INPUT: u(t) = g(Y(t))      
    u(t): inputs into system
    Y(t): user observations about surroundings
    g:    function mapping observations into inputs
    

STATE SPACE MODEL
Orientation of body doesn't change:

    X = |x1| = |x(t)|
        |x2|   |v(t)|

    X▪ = d |x1| = |v(t)|
         dt|x2|   |a(t)|

ORIENTATION STATE SPACE MODEL [1 DIMENSIONAL]
Orientation of body does change; Using an angle change from a specified vector

    X = |x1| = |x(t)| 
        |x2|   |ɸ(t)|
        |x3|   |v(t)|
        |x4|   |w(t)|

    X▪  = d |x1| = |v(t)| 
          dt|x2|   |w(t)|
            |x3|   |a(t)|
            |x4|   |α(t)|

ORIENTATION STATE SPACE MODEL [3 DIMENSIONAL]
Orientation of body does change; Using basis of object:

    X = |x1| = |x(t) | or |x(t)|
        |x2|   |B(t) |    |B(t)|
        |x3|   |v(t) |    |p(t)|
        |x4|   |B▪(t)|    |L(t)|

    X▪  = d |x1| = |v(t)  | or |v(t) | 
          dt|x2|   |B▪(t) |    |p(t) |
            |x3|   |a(t)  |    |p▪(t)|
            |x4|   |B▪▪(t)|    |L▪(t)|

    B(t) = Orientation of basis
    B▪(t) = Rate of change of orientation

    OBJECT FRAME:
    {r,f,u} are the basis vectors for the object
    Origon Or is at the center of mass of object
    B(t) =  | rx  fx  ux |
            | ry  fy  uy |
            | rz  fz  uz |


-----------------------------------------------------------
eg(1) OBTAINING VALUES FOR LINEAR STATE SPACE MODELS
-----------------------------------------------------------
RELATING X and X▪:

    X▪(t) = |v(t)| and X(t) = |x(t)|
            |a(t)|            |v(t)|

    USING a(t) = -kx(t)/m - µv(t)/m + u(t)/m from springs

⁂   X▪(t) = |  0    1   || x(t) | + |  0  |u(t) 
            |-k/m  -µ/m || v(t) |   | 1/m |

⁂   X▪(t) = AX(t) + Mu(t)


     For linear systems:
     -----------------------
    | X▪(t) = AX(t)         | if no user input
    | X▪(t) = AX(t) + Bu(t) | if user input
     -----------------------

    FINDING MATRIX A
    A will be constant if angular velocity w(t) is constant

    POSITION                            
    | v(t) | = | a1 a2 || x(t) |        
    | a(t) |   | a3 a4 || v(t) |        

    v(t) = a1x(t) + a2v(t)              
    a(t) = a3x(t) + a4v(t)              

    STRAPDOWN EQUATION:
    B▪(t) = w(t) X B(t) = ΩB(t)
    v(t) = w(t) X x(t) = Ωx(t)
    aᶜ(t) = w(t) X v(t) = Ωv(t) 

    ---------------------------------------------------
    w is expressed as Cross Product Matrix:
      Ω  =  | 0  -wx  wy |
            | wx  0  -wz |
            |-wy  wz   0 |
    ---------------------------------------------------

    If no other forces involved:         
    a(t) = aᶜ(t) = Ωv(t)

    If Other Forces Involved:
    a(t) = Ωv(t) + g + (1/m)Fᵤ                                              


//////////////////////////////////////////////////////////////////////////////
//ERROR FEEDBACK CONTROL
//////////////////////////////////////////////////////////////////////////////

For state space model:
X(t) = |Ɵ(t)|   X▪(t) = |w(t)|  
       |w(t)|           |α(t)|

∆T = timestep
Ɵ'(t) = Desired angle
Ɵ(t) = Current angle
w'(t) = Desired angular velocity
w(t) = Current angular velocity
τ(t) = Torque

Ɵ'(t)                 w'(t)                  τ(t)                   
->|eᶿ(t)|->|POSITION  |->|eʷ(t)|->|VELOCITY  |->|INTEGRATE|->|INTEGRATE|->Ɵ(t)
     ^     |CONTROLLER|     ^     |CONTROLLER|  |VELOCITY |  |POSITION |         
     |                      |                         |            |
     |                      |_w(t)____________________|            |
     |_Ɵ(t)________________________________________________________|

ERRORS
eᶿ(t) = Ɵ'(t) - Ɵ(t)
eʷ(t) = w'(t) - w(t) 

INTEGRATE POSITION              INTEGRATE VELOCITY
Ɵ(t+1) = Ɵ(t) + w(t)∆T          w(t+1) = w(t) + α(t)∆T

POSITION CONTROLLER             VELOCITY CONTROLLER
w'(t) = Kᶿŵ                     τ(t) = Kʷ(t)ŵ

K = Kpᶿeᶿ(t) + Kdᶿeᶿ▪(t) + Kiᶿʃeᶿ(t)
Increase in K:
    - decrease time taken to get error to 0 by reducing error by larger values
    - can overshoot/undershoot 0 however and create oscillations
    - fix by using 2 of 3 values of K


/////////////////////////////////////////////////////////////////////////////////
//STEERING BEHAVIOURS
/////////////////////////////////////////////////////////////////////////////////

===> www.red3D.com for reference

HIERARCHY OF CONTROL
  Action Selection; strategy, goals, planning
  Steering; path determination
  Locomotion; animation, articulation

-----------------------------------------------------------------------
IMPLEMENTING STEERING BEHAVIOURS
-----------------------------------------------------------------------
  STATE SPACE MODEL:
  X(t) = |x(t)| X▪(t) = |v(t)|  
         |v(t)|         |a(t)|

  OBJECT FRAME:
  {r,f,u} are the basis vectors for the vehicle
  forward vector for vehicle always aligned to velocity
  B(t) =  | rx  fx  ux |
          | ry  fy  uy |
          | rz  fz  uz |

-----------------------------------------------------------------------
FOR EACH TIMESTEP UPDATE
-----------------------------------------------------------------------
  SEMI-IMPLICIT EULER SCHEME:
  v(t+∆t) = truncate(v(t) + a(t)∆t, vᵐᵃˣ)
          = truncate(v(t) + (¹/m)F(t)∆t, vᵐᵃˣ)
  x(t+∆t) = x(t) + v(t+∆t)∆t

  STEERING FORCE:
  F(t) = truncate(m(v'(t)-v(t)), Fᵐᵃˣ)

  UPDATING BASIS ORIENTATION:
  want forward vector to always be aligned to velocity vector
  u(temp) = uᵗ/‖uᵗ‖
  f(t+∆t) = v(t+∆t)/‖(t+∆t)‖
  r(t+∆t) = f(t+∆t) X u(temp)
  u(t+∆t) = r(t+∆t) X f(t+∆t)
  B(t+∆t) = -sin¯¹(fˣ(t+∆t))  used for switching between external/local frame

-----------------------------------------------------------------------
USER INPUTS: v'(t)
-----------------------------------------------------------------------
Pᵗ = Target Position
Pᵛ = Vehicle Position
R  = Radial Vector from vehicle to target
v' = Desired Velocity

SEEK/FLEE BEHAVIOUR: 
Use vector from vehicle to target as direction of velocity
 ------------------------------------
| R̂(t) = Pᵗ(t)-Pᵛ(t) / ‖Pᵗ(t)-Pᵛ(t)‖ |
 ------------------------------------

PURSUE/EVADE BEHAVIOUR: 
Look at future position of target and seek/flee from this position
 ------------------------------------------
| Pᵗ(t+∆t) = Pᵗ(t) + vᵗ(t)                 |
| R̂(t) = Pᵗ(t+∆t)-Pᵛ(t) / ‖Pᵗ(t+∆t)-Pᵛ(t)‖ |
 ------------------------------------------

MOVE TOWARDS TARGET         MOVE AWAY FROM TARGET
v'(t) = (vᵐᵃˣ)R̂(t)          v'(t) = -(vᵐᵃˣ)R̂(t)


-----------------------------------------------------------------------
COMPLEX STEERING BEHAVIOURS
-----------------------------------------------------------------------

PRIORITY STEERING: Deal with the largest force first 
Problems include fighting if forces are close and keep changing
Vehicle may do illogical behaviours; 
move away from target to avoid obstacle
 ---------------------
| F = max(F₁,F₂...Fⁿ) |
 ---------------------

WEIGHTED STEERING: Final force is weighted sum of all forces
Problems include choosing the weights
 -----------------------------
| F = (Fᵐᵃˣ/‖∑F‖)(F₁,F₂...Fⁿ) |
 -----------------------------

ORDERED STEERING: Design based ordering
Problems include management as behaviours increase
 -----------------------------------------
| behaviour1 < behaviour2 < behaviour3... |
 -----------------------------------------
