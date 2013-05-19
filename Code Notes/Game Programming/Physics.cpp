//////////////////////////////////////////////////////////////////////////////
//GAME PHYSICS
//////////////////////////////////////////////////////////////////////////////
/*

KINEMATICS: 
the study of the motion of objects without regard to the causes of this motion
DYNAMICS: 
the study of the affect of forces and torques applied to objects having mass

KE  KINEMATIC ENERGY: energy due to motion
GPE GRAVITATIONAL POTENTIAL ENERGY: Energy stored due to height of object
SPE SPRING POTENTIAL ENERGY: 0 in perfectly elastic collisions
TE  THERMAL ENERGY: energy due to friction

Q  HEAT: Energy released due to heating of system
W  WORK: Energy gained due to force applied over a given distance
Pᵂ POWER: Work done per second

x  DISPLACEMENT
d  DISTANCE
ɸ  ANGULAR DISPLACEMENT
Ɵ  ROTATION ANGLE: amount rotated around axis

v  LINEAR VELOCITY: Time rate of change of displacement
w  ANGULAR VELOCITY: Speed at which object is rotating
vᵀ TANGENTIAL VELOCITY: velocity tangent to the path taken due to rotation
vᵗ TRANSLATIONAL VELOCITY: velocity in direction of movement of whole body due 
                           to translation

a  LINEAR ACCELERATION: Time rate of change of velocity
aᶜ CENTRIPETAL ACCELERATION: Linear acceleration directed towards origon
α  ANGULAR ACCELERATION: acceleration of rotating

F  FORCE
Fr FRICTION
Fᶜ CENTRIPETAL FORCE: parallel force to centripetal acceleration
P  TOTAL MOMEMTUM: total momemtum of a system
p  MOMENTUM: change in inertia; amount an object will resist changes to vel
J  IMPULSE: Force applied over a set time
L  ANGULAR MOMENTUM
τ  TORQUE: Rotational Force 
i  MOMENT OF INERTIA: measure of an object's resistance to changes to its 
                      rotation (given 3x3 matrix)

B(t)  ORIENTATION MATRIX
X(t)  STATE SPACE MODEL
X▪(t) DERIVATIVE STATE SPACE MODEL

POSITION DERIVATIVES:
--->  x -> v -> a 
--->  p -> F 

ROTATION DERIVATIVES:
--->  ɸ -> w -> α
--->  L -> τ

Deriving notes:
dv = ∆v = vᶠ-v° (average velocity)
v = dx/dt       (instantaneous velocity)

=============================================================================
NEWTON'S LAWS
=============================================================================
1) Every body remains in a state of rest or uniform motion(constant velocity) 
   unless it is acted upon by an external unbalanced force.

2) A body of mass subject to a force undergoes an acceleration that has the 
   same direction as the force [F = ma]

3) The mutual forces of action and reaction between two bodies are equal, 
   opposite and collinear.

=============================================================================
KINEMATIC EQUATIONS
=============================================================================
Can be used in 1D/2D/3D problems with components
Can only be used when accerlation (a/aᶜ/α) is constant

vᶠ = v° + at
x = v°t + (¹/₂)at²
vᶠ² = v°² + 2ax
x = (¹/₂)(v° + vᶠ)t

vᶠ  velocity
v°  initial velocity
a   acceleration
t   time
x   displacement

i:(1,0), j:(0,1) then g is -
i:(1,0), j:(0,-1) then g is +

=============================================================================
FORCE(F)
=============================================================================
F = ma          forces acting on object
Fᶜ = maᶜ        centripetal force
N = mgcosƟ      force from surface onto object
Fr = µN         friction acting on object

∑F = F + Fr + mgcosƟ

=============================================================================
ENERGY(E)
=============================================================================
NON-ISOLATED SYSTEM:
 ∆E = W + Q 
 W = ∆KE + ∆GPE + ∆SPE + ∆TE

ISOLATED SYSTEM: 
 ∆E = W = ∆KE + ∆GPE + ∆SPE + ∆TE = 0
 ∆KE = ¹/₂m(v(f)² - v(0)²)

KE = ¹/₂mv²
GPE = mgh
SPE = Spring Potential energy (will be 0 in perfectly elastic collisions)
TE = Thermal energy due to friction
Q = Energy due to heating of system

----------------------------------------------------------------------------
ENERGY TRANSFER: WORK(W)
----------------------------------------------------------------------------
Energy is transferred from the environment into the system
W = τƟ
W = F.d             when d is alligned with force
W = ‖F‖‖d‖cosƟ      when d isn't alligned with force; want component of 
                    force in direction of d

W(overall) = ∆E
W(KE) = ∆KE
W(GPE) = ∆GPE

----------------------------------------------------------------------------
ENERGY TRANSFER: HEAT(Q)
----------------------------------------------------------------------------
Energy is transferred from the system back into the environment


=============================================================================
MOMENTUM(p)
=============================================================================
p = mv

force is rate of change of momentum:
    F = ma = m(dv/dt) = d(mv)/dt = dp/dt

MULTIPLE OBJECTS/PARTICLES IN SYSTEM:
P = overall momemtum of whole system
P = p₁ + p₂ + ...

∆p₁/∆p₂ = change of momentum of indivdual object after the collision
∆P = ∆p₁ + ∆p₂ = 0 overall momentum in system doesn't change

--------------------------------------------
    P = Pᶠ = P° as ∆P = 0
⁂  m₁v₁(f) + m₂v₂(f) = m₁v₁(0) + m₂v₂(0)
--------------------------------------------

EG(1):
Perfectly elastic collision where initial momemtum P of whole system is 0
Object 1 hits object 2 which is stationary. Define one direction as positive

Before Collsion       After Collision
p₁(0) = x             p₁(f) = 0
p₂(0) = 0             p₂(f) = x

Due to perfectly elastic collision, all momemtum is transferred from one
object to another during collision. If both objects are moving, add one
object's momemtum to other to make one object virtually start from rest

∆p₁ = -x
∆p₂ = x
where  ∆P = ∆p₁ + ∆p₂ = 0
Impulse from 1 onto 2 = ∆p₂ = x
Impulse from 2 onto 1 = ∆p₁ = -x

The impulse put on an object is equal to ∆p of the object

=============================================================================
IMPULSE(J)
=============================================================================
J = F.dt = dp = ∆p = pᶠ-p° = m∆v = m(vᶠ-v°)

    F = dp/dt
⁂   dp = F.dt
⁂   J = dp = ∆p

=============================================================================
TORQUE(τ)
=============================================================================
F = Force applied to point
R = vector from Point to origon of object
α = angular acceleration produced by torque
i = moment of inertia of the point

τ = iα

=============================================================================
ANGULAR MOMENTUM(L)
=============================================================================
p = momentum
R = vector from Point to origon of object
i = moment of inertia of the point
w = Angular velocity

L = R X p = iw

torque is rate of change of angular momentum:
    τ = iα = i(dw/dt) = d(iw)/dt = dL/dt

=============================================================================
ANGULAR VELOCITY(w) / ANGULAR ACCERLATION(α)
=============================================================================
s = speed of rotation
Ɵ = amount rotated around axis
n̂ = axis of rotation/normal to the area of the rotation

ɸ = Ɵn̂
w = sŵ = sn̂ = dƟ/dt
α = dw/dt = d²Ɵ/dt²


//////////////////////////////////////////////////////////////////////////////
//POSITIONAL PHYSICS
//////////////////////////////////////////////////////////////////////////////

-----------------------------------------------------------------------------
MOTION
-----------------------------------------------------------------------------
For a block sliding down a hill with a pushing force:
  F = ma
  N = mgcosƟ
  Fr = µN
  where ∑F = F + mgsinƟ + Fr

-----------------------------------------------------------------------------
SPRINGS: HOOKE'S LAW
-----------------------------------------------------------------------------
The force on m, due to the spring:              Fs(t) = -kx(t)
The force on m, due to friction and surface:    Fr(t) = -µv(t)
Total force on m:                               F(t) = Fs(t) + Fr(t)

If there is outside input:                      u(t)
Total force on m:                               F(t) = Fs(t) + Fr(t) + u(t)

u(t): user input force
v(t): velocity of mass
x(t): displacement from initial displacement Xo
k: spring constant
µ: friction coeffeciant

-----------------------------------------------------------------------------
BALLISTICS/PROJECTILES
-----------------------------------------------------------------------------
A projectile is shot at angle Ɵ where up is positive j, right positive i
No air resistance so i component of velocity doesn't change

  v = initial speed
  a = 0i - 9.8j
  v(0) = vcosƟi + vsinƟj
  v(f) = vcosƟi - vsinƟj
  v(f/2) = vcosƟi + 0j
  d = dˣi + dʸj

  at t = 0 and t = f: dʸ = 0 as the projectile is on the ground
  at t = f/2 the projectile is at it's highest height but slowest speed

  d = v(0)t + (1/2)at²
    = t(v(0) + (1/2)at)  let d = 0 using y components

  ⁂ 0 = t(vʸ(0) + (1/2)(-9.8)t)
  ⁂ 0 = t /or/ 0 = vʸ(0) + (1/2)(-9.8)t
  ⁂ t(0) = 0 /or/ t(f) = 2vʸ(0)/9.8

  to find total distance travelled (dˣ) sub t(f) into:
  dˣ = v(0)ˣt + (1/2)aˣt² 


//////////////////////////////////////////////////////////////////////////////
//ROTATIONAL PHYSICS
//////////////////////////////////////////////////////////////////////////////

ANGULAR VELOCITY = w
LINEAR VELOCITY = v
TANGENTIAL VELOCITY = vᵀ
TRANSLATIONAL VELOCITY = vᵗ

Angular velocity is velocity around the rotation axis
Tangential velocity is velocity in direction of rotation circle
Linear velocity is sum of tangential velocity (if rotating) and translational 
velocity of whole body (if translating)

RIGHT-HAND RULE:
Curl fingeres in direction object is rotating
Stick thumb up; Thumb is in direction of w

POINT/BODY ROTATING AROUND AN AXIS: no change in body's orientation
    2D RELATIONS: when axis of rotation is about i,j or k
     -------------------
    | vᵀ(t) = w(t)x(t)  |
    | aᶜ(t) = w(t)vᵀ(t) |
     -------------------

     3D RELATIONS: when axis of rotation is about arbitary axis
     ----------------------
    | vᵀ(t) = w(t) X x(t)  |    
    | aᶜ(t) = w(t) X vᵀ(t) |
     ----------------------

     where ŵ,v̂,âᶜ make up the basis at point P 
     Point P rotates around an axis with center Or
     x(t) is the radius vector from Or to point P
     w(t) = sŵ where s = Speed (radians per sec)


POINT FIXED TO A ROTATING BODY: change in body's orientation
    A force F is applied to Point P on an object which results in a torque
    that rotates the whole body's orientation around the axis R X F
    with an angular accerlation α

    α = angular acceleration produced by toque
    i = moment of inertia of the point

     --------
    | τ = iα |
     --------

*/////////////////////////////////////////////////////////////////////////////