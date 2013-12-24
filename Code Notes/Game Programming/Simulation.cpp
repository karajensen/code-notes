//////////////////////////////////////////////////////////////////////////////
//INTEGRATION METHODS
//////////////////////////////////////////////////////////////////////////////
/*

LINEAR INTERPOLATION: Line between two points used to approximate the curve 
SPHERICAL INTERPOLATION: Smoothly interplates between two values 

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

//////////////////////////////////////////////////////////////////////////////
//STATE SPACE MODELS
//////////////////////////////////////////////////////////////////////////////

LINEAR SYSTEM:      X▪(t) = AX(t) + Bu(t)  Use matrix A/B every timestep
NON-LINEAR SYSTEM:  X▪(t) = f(X(t),u(t))   Use integration methods every timestep

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

//////////////////////////////////////////////////////////////////////////////
//CLOTH SIMULATION
//////////////////////////////////////////////////////////////////////////////

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

BUOYANCY EFFECT:
SINK: Object Density > Liquid Density
FLOAT: Object Density < Liquid Density

--------------------------------
| DENSITY = MASS / VOLUME(m³) |
--------------------------------
Increasing Mass increases Density

////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME THEORY
////////////////////////////////////////////////////////////////////////////////////////////////////////

GAME THEORY: Study of choice of strategies by interacting agents
ZERO-SUM GAMES: Payoff for players always adds to zero; one player wins what the other loses
NON ZERO-SUM GAMES: Players payoff relational to how much they win/lose
PERFECT INFORMATION: No element of random chance affecting possible moves that can be done (chess)
IMPERFECT INFORMATION: Element of random chance avaliable (trouble)

===============================================================================================
GAME STRATEGIES
===============================================================================================
COOPERATIVE SOLUTION: All players agree to a particular strategy choice
NON-COOPERATIVE SOLUTION: No enforced agreements to choices
DOMINANT STRATEGY: A strategy which provides a higher payoff no matter the choice of the other player
DOMINANT STRATEGY EQUILIBRIUM: All players have a dominant strategy and select it

SOCIAL DILEMMA [Dominant Strategy, Cooperative Solution]
PRISONER'S DILEMMA [Dominant Strategy, Non-Cooperative]
NASH EQUILIBRIUM [Non-Dominant, Non-Cooperative]
    Each player chooses the best strategy in response to the strategies chosen by other players
    There is no choice which will be better no matter what the other player chooses. 
    The player can either risk getting 2 or none, or settle for a guaranteed one no matter the other players choice.
    Eg. Rock/Paper/Scissors

===============================================================================================
EMBODIED AGENTS (AI)
===============================================================================================

EMBODIED AGENT: 
- Subsystem of a domain (Agent + Environment = Domain)
- Entity that percieves its environment through sensors and acts upon that environment through actuators

EMBODIED AGENT INFORMATION CYCLE:
 1) PERCIEVES its environment and itself
 2) REASONS about these perceptions and prior knowledge
 3) ACTS in response to reasons and with purpose

RATIONAL AGENT: selects an action that is expected to maximize its performance given what information it has been given
AUTONOMOUS AGENT: acts in a meaningful manner given its perceptions and reasoning (Perception->Reasoning->Action)

REACTIVE SYSTEM (PROCEDURAL): 
 - Uses no world model or reasoning; does constant action towards stimulus
 - BENEFIT: Fast response to stimuli, smaller computations needed                
 - DISADVANTAGE: No guarantee of reaching goal, can result in cyclic behaviour/failure
 - STATE MACHINES: Encodes how to behave in every situation encountered

DELIBERATIVE SYSTEM (DECLARATIVE): 
 - Uses world model; reasons actions and chooses a meaningful one       
 - BENEFIT: Can avoid fatal failures, intelligent and optimal behaviour
 - DISADVANTAGE: Computational cost, slower, requires knowledge of the world around, difficult to deal with uncertainty
 - PLANNING SYSTEM: allows agents to select actions to achieve its goals from its current state

////////////////////////////////////////////////////////////////////////////////////////////////////////
//REACTIVE SYSTEMS: STATE MACHINES
////////////////////////////////////////////////////////////////////////////////////////////////////////

STATE MACHINES DISADVANTAGES:
 - become bloated with lots of states, difficult to manage/debug
 - states difficult to reuse in different contexts
 - only one state active at one time
 - can cycle between states (eg. Line of sight for enemy cycles in/out)

MAIN DIFFERENCES:
 - State Machine outputs if a transition to a new state occurs (Mealy) or currently in a state (Moore)
 - State Automata outputs if the final state occurs after series of transitions

-----------------------------------------------------------------------------------------------------------
FINITE STATE MACHINE:
-----------------------------------------------------------------------------------------------------------
 - Keeps track of the set of possible states, what is required to transition between them, which state it is in
 - At each iteration (frame) the state machines update function is called to see if any transition is triggered
 - if transition is triggered, transition actions are carried out
 - Function returns symbols for what action is to be carried out in the new state
 - Has no terminal states; can be initialised in any state

MEALY MACHINE: Emit signals upon transition
MOORE MACHINE: Emit symbols in each state

-----------------------------------------------------------------------------------------------------------
FINITE STATE AUTOMATA:
-----------------------------------------------------------------------------------------------------------
 - Consumes a sequence of input signals one at a time
 - Has a unique starting state, one or more accepting states and final state
 - If the sequence of inputs causes transitions that result in the final state, output occurs
 - Game Application: Sequence of keys results in attack occuring

-----------------------------------------------------------------------------------------------------------
IMPLEMENTING STATE MACHINES:
-----------------------------------------------------------------------------------------------------------

POLLLING AGENTS: 
  Continually query the game world to determine input for state transitions
  ADVANTAGE: Only queries game world for information when it is needed
  DISADVANTAGE: Constantly asks “are we there yet”

EVENT-DRIVEN AGENTS: 
  Objects in game broadcast messages which the agent picks up when close enough and filter according to importance of agent
  ADVANTAGE: Responds only to messages it finds important, abstracts agent away from generating information; agent only consumes
  DISADVANTAGE: More overhead, harder to code

////////////////////////////////////////////////////////////////////////////////////////////////////////
//DELIBERATIVE SYSTEMS: PLANNING
////////////////////////////////////////////////////////////////////////////////////////////////////////

PLAN: Sequence of actions that moves from initial state to goal state
PROGRESSION PLANNING: Forward search from initial state
REGRESSION PLANNING: Backward search from goal

SITUATIONAL PLANNING (State Space Search)
- Gather series of actions based on the situation player is in to get to the goal
- Includes PathFinding to a goal

PARTIAL PLANNING (Plan Space Search)
- Start with empty/partially empty sequence of actions (plan)
- When executing plan, consider ways of expanding the plan looking through all possible plans in the plan space
- Continue until final plan is complete and solves the problem (goal reached)

CONDITIONAL PLANNING (Probability)
 - Probability is used when not all information is known about environment/other agents


*/////////////////////////////////////////////////////////////////////////////