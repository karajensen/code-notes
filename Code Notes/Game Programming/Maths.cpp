//////////////////////////////////////////////////////////////////////////////
//MATHS
//////////////////////////////////////////////////////////////////////////////
/*
-------------------------------------------------------------------------
UNITS
-------------------------------------------------------------------------
m = milli = 10¯³    k = kilo = 10³
µ = micro = 10¯⁶    M = mega = 10⁶
n = nano = 10¯⁹     G = giga = 10⁹

-------------------------------------------------------------------------
DERIVATIVES/ANTI-DIFFERENTIATION
--------------------------------------------------------------------------
f(x) = axⁿ          f'(x) = axⁿ
f'(x) = anx¯¹       f(x) = axⁿ⁺¹/n+1

--------------------------------------------------------------------------
COORDINATES
--------------------------------------------------------------------------
   Z                   Z
   ▲                   ▲                  3 FINGER RULE:
   |                   |                  Second Finger = X
   ▪----► Y            ▪----► X           Middle Finger = Y
  /  RH COODINATE     /  LH COODINATE     Thumb = Z
 ▼   SYSTEM          ▼   SYSTEM
X                   Y

//////////////////////////////////////////////////////////////////////////////
//VECTORS
//////////////////////////////////////////////////////////////////////////////

SET: Collection of elements selected based on common properties
VECTOR: quantity with magnitude and direction (no position)

VECTOR BASIS: 
Set of linerly independent vectors which spans/creates a vector space

VECTOR SPACE: 
Set of all vectors created by linera combinations of the vector basis
Continas: Zero vector
          Sum of any two vectors (closure)
          Additive inverse of any vector
          Scalar multiplication of any vector (multiplicative closure)

LINEAR INDEPENDENCE: 
Obtained if a vector cannot be written in terms of other vectors in the set
    
    eg(1):  Basis Vectors               S = {v₀,v₁,V₂...vⁿ}
            Resulting/Spanned Vectors   T = {V₀,V₁,V₂...Vⁿ}
            Where                       V = a₀v₀ + a₁v₁ + a₂v₂ + ... + aⁿvⁿ

LINEAR SPACE: Vector space with inner/dot product and norm
EUCLIDEAN SPACE: Linear space using real numbers for scalars
STANDARD EUCLIDEAN SPACE: Basis set {i,j,k} with extra features
                            - Orthonormal (dot product=0 between all vectors)
                            - Unit length
                            - Linearly independent

VECTOR IDENTITY ELEMENT = 0 vector
SCALAR IDENTITY ELEMENT = 1 scalar
ADDITIVE INVERSE: a + (-a) = 0 vector
MULTIPLICATIVE INVERSE: k(1/k) = 1 scalar

=============================================================================
DOT/INNER PRODUCT
=============================================================================
 -------------------
| cosƟ = a.b/‖a‖‖b‖ |
 --------------------------
| a.b = aˣbˣ + aʸbʸ + aᶻbᶻ |
 --------------------------
a.b > 0     Ɵ < 90 between both vectors
a.b < 0     Ɵ > 90 between both vectors
a.b = 0     Ɵ = 90 vectors are ⊥ to each other

DOT PRODUCT RULES:
  a.b = b.a
  (a+b).c = a.c + b.c
  k(a.b) = ka.b = a.kb

=============================================================================
NORMS
=============================================================================
 -----------------------------------
| ‖a‖ = √(a.a) = √(ax² + ay² + az²) |
 -----------------------------------
| â = a/‖a‖ |
 ------------

‖ka‖ = |k|‖a‖
‖a+b‖ ≤ ‖a‖+‖b‖

=============================================================================
CROSS/OUTER PRODUCT
=============================================================================
 ----------------------------------------------------------
| u X v = (uʸvᶻ - uᶻvʸ)i - (uˣvᶻ - uᶻvˣ)j + (uˣvʸ - uʸvˣ)k |
 ----------------------------------------------------------
| ‖u X v‖ = ‖u‖‖v‖sin0 = square area between u and v |
 -----------------------------------------------------

CROSS PRODUCT RULES:
  u.(u X v) = v.(u X v) = 0         u X u = 0
  (u+v) X w = (u X w) + (v X w)     u X v = -v X u
  a(u X w) = au X w = u X aw        u X 0 = 0 X u = 0

COLLINEAR POINTS: cross product = 0
PARALLEL VECTORS: cross product = 0

3 FINGER RULE:
  Second Finger = u
  Middle Finger = v
  Thumb = u X v

=============================================================================
TRIPLE PRODUCT
=============================================================================
 -----------------------------------
| u.(v X w) = volume of parallopied |
 -----------------------------------
  a X (b X c) = b(a.c) - c(a.b)
 -a X (b X c) = c(a.b) - b(a.c)


=============================================================================
VECTOR PROJECTION
=============================================================================
     /|                 compᵦa = a.b̂ = ‖a‖cosƟ
    / |                 projᵦa = (a.b̂)b̂ = (compᵦa)b̂
 a /  | perpᵦa          perpᵦa = a - projᵦa
  /   | 
 /____|_____________    projᵦa = projection of a onto b
 projᵦa      b          projₐb = projection of b onto a
 <---->
 compᵦa

 for â.b̂ the number (-1->1) gives the % along b the perpᵦa reaches
 for a.b̂ the number gives the distance along b the perpᵦa reaches


//////////////////////////////////////////////////////////////////////////////
//POINTS
//////////////////////////////////////////////////////////////////////////////

POINT: element of a set where the value depends on the coordinate system 
       relative to a fixed member in the set
ORIGIN: fixed member in the set
COORDINATE SYSTEM: System with basis vector/origin
AFFINE SPACE: Vector space with a set of points where every pair of points 
              has a unique vector
 
 ------------        -----------
|v = P₀ - P₁ |      | v = Q - P |
 ------------        -----------
  P₀      P₁          P       Q
  ▪=======>▪          ▪=======>▪
      v                   v

AFFINE INDEPENDENCE: 
For P = P₀ + a₁v₁ + a₂v₂ + ... + aⁿvⁿ if vectors {v₁,v₂...vⁿ} are linearly 
independent then set of points {P₀,P₁...Pⁿ} will be linearly independent

SIMPLEX: Set of points of minimal size with affine independence that 
         spans a space of points
                  ▪
       ▪         /|\
      / \       / | \   
     /   \     ▪--|--▪
    ▪-----▪     \ | /
      2D         \▪/  3D

CONVEX: shape where line between 2 points doesn't cross border
CONVEX HULL: Smallest convex set
    For a line: segment of line between 2 points
    For a simplex: space inside 3 points
BARYCENTRIC COORDINATES: coordinates used when describing points in relation 
                         to a simplex

=============================================================================
AFFINE COMBINATION
=============================================================================

P = a₀P₀ + a₁P₁ + a₂P₂ + ... + aⁿPⁿ     
Point P is a combination of points P₀,P₁...Pⁿ 
where constraint a₀ + a₁ + a₂ + ... + aⁿ = 1

using the constraint, sub into equation
a₀ = 1 - a₁ - a₂ - ... - aⁿ 
P = (1 - a₁ - a₂ - ... - aⁿ)P₀ + a₁P₁ + a₂P₂ + ... + aⁿPⁿ
P = P₀ + a₁(P₁-P₀) + ... + aⁿ(Pⁿ-P₀)
P = P₀ + a₁v₁ + a₂v₂ + ... + aⁿvⁿ

eg(1)
  P = a₀P₀ + a₁P₁ + a₂P₂
  a₀ = 1 - a₁ - a₂
  ⁂ P = (1 - a₁ - a₂)P₀ + a₁P₁ + a₂P₂
  ⁂ P = P₀ - a₁P₀ - a₂P₀ + a₁P₁ + a₂P₂
  ⁂ P = P₀ + a₁(P₁-P₀) + a₂(P₂-P₀)
  ⁂ P = P₀ + a₁v₁ + a₂v₂
  where v₁ = P₁-P₀ and v₂ = P₂-P₀

=============================================================================
POLAR COORDINATES
=============================================================================
 ---------------------------
| radians x 180/∏ = degrees |
 ---------------------------

FOR 3D: using elevation angle       FOR 2D:
-----------------------------       ------------------
‖r‖ = √(x² + y² + z²)               r = √(x² + y²)
Ɵ = tan¯¹(y/x)                      Ɵ = tan¯¹(y/x)
ɸ = sin¯¹(z/‖r‖)
                            
x = ‖r‖cosɸcosƟ                     x = ‖r‖cosƟ 
y = ‖r‖cosɸsinƟ                     y = ‖r‖sinƟ
z = ‖r‖sinɸ


//////////////////////////////////////////////////////////////////////////////
//LINES
//////////////////////////////////////////////////////////////////////////////

LINE: Set of points where coordinates of all points satisfies f(x) = y
      Set of points spanned by affine combinations of simplex {P₀,P₁}

RAY: P(t) = P₀ + td where t ≥ n
SEGMENTS: P(t) = P₀ + td where m ≤ t ≤ n 

 ---------------------                   --------------
| n̂.(P-P₀) = distance |                 | n.(P-P₀) = 0 |
 ---------------------                   --------------
for points above/below line/plane       for all points on line/plane
-distance = below                       doesn't have to be normalized
+distance = above

COLLINEAR: 
3+ points lie in same line
To test take cross product of 2 vector formed by the three points 
and if 0, collinear

COPLANAR:
4+ points line in same plane; use triple scalar product
if u.(v X w) = 0 then coplanar as u.(v X w) = volume of parralopied
    P₁-P₀ = u
    P₂-P₀ = v   
    P₃-P₀ = w   

=============================================================================
LINE PARAMETRIC EQUATION
=============================================================================
 
 P = a₀P₀ + a₁P₁    where a₀ + a₁ = 1
 P = (1-t)P₀ + tP₁  where a₁ = t
 ----------------
| P(t) = P₀ + td |
 ----------------
 t = Barycentric coordinate
 d = vector along line (p1-po)
 P(t) = coordinate on line
 P₀ = Point on line

 Can be split into 3 equations:
 x = P₀ˣ + tdˣ
 y = P₀ʸ + tdʸ
 z = P₀ᶻ + tdᶻ

=============================================================================
LINE LINEAR EQUATION
=============================================================================

 Using the normal equation:
 n.(P-P₀) = 0 where n = (a,b)
 (a,b).(x-x₀,y-y₀) = 0
  ----------------- 
 | ax + by + c = 0 | where c = -(ax₀ + by₀)
  -----------------

 rearrange to get y:
 y = -(ax + c)/b
 y = -(a/b)x -(c/b)  let m = -(a/b) and C = -(c/b)
  ------------
 | y = mx + c |
  ------------

=============================================================================
PLANE PARAMETRIC EQUATION
=============================================================================
 
 P = a₀P₀ + a₁P₁ + a₂P₂      where a₀ + a₁ + a₂ = 1
 P = (1-t-s)P₀ + tP₁ + sP₂   where a₁ = s and a₂ = t
 -----------------------
| P(t) = P₀ + su₁ + tu₂ |
 -----------------------
 s,t = Barycentric coordinate
 d = vectors along line stemming from Po
 P(t) = coordinate on plane
 P₀ = Point on plane

 Can be split into 3 equations:
 x = P₀ˣ + su₁ˣ + tu₂ˣ
 y = P₀ʸ + su₁ʸ + tu₂ʸ
 z = P₀ᶻ + su₁ᶻ + tu₂ᶻ

=============================================================================
PLANE LINEAR EQUATION
=============================================================================

 Using the normal equation:
 n.(P-P₀) = 0 where n = (a,b,c)
 (a,b,c).(x-x₀,y-y₀,z-z₀) = 0
  ---------------------- 
 | ax + by + cz + d = 0 | where d = -(ax₀ + by₀ + cz₀)
  ----------------------


//////////////////////////////////////////////////////////////////////////////
//CIRCLES
//////////////////////////////////////////////////////////////////////////////

2D CIRCLE EQUATION: 
(x-center.x)² + (y-center.y)² = r²  [on circle]
(x-center.x)² + (y-center.y)² < r²  [inside]
(x-center.x)² + (y-center.y)² > r²  [outside]

3D CIRCLE EQUATION: 
(x-center.x)² + (y-center.y)² + (z-center.z)² = r²  [on circle]
(x-center.x)² + (y-center.y)² < (z-center.z)² = r²  [inside]
(x-center.x)² + (y-center.y)² > (z-center.z)² = r²  [outside]




//////////////////////////////////////////////////////////////////////////////
//MATRICES
//////////////////////////////////////////////////////////////////////////////

DIAGONAL MATRIX                 IDENTITY MATRIX
| a 0 0 |                       | 1 0 0 | 
| 0 b 0 |                       | 0 1 0 |
| 0 0 c |                       | 0 0 1 |

SYMMETRIC MATRIX (A = Aᵀ)       SKEW SYMMETRIC MATRIX (-A = Aᵀ)
| a b c |                       | 0 -a  b | 
| b d e |                       | a  0 -c |
| c e a |                       |-b  c  0 |

UPPER TRIANGULAR MATRIX         LOWER TRIANGULAR MATRIX
| a b c |                       | a 0 0 | 
| 0 d e |                       | b d 0 |
| 0 0 f |                       | c e f |

INVERSE MATRIX
 ----------
| AA¯¹ = I |
 ----------

ORTHOGONAL MATRIX
Rows/Columns are unit length
Rows are orthogonal to each other
Columns are orthogonal to each other
To test AAᵀ or AA¯¹ = I
 ----------
| A¯¹ = Aᵀ |
 ----------

MATRIX RULES:
AI = IA = A             (B + C)A = BA + CA
A-A = 0                 (A + B) + C = A + (B + C)
A + B = B + A           (AB)C = A(BC)
A(B + C) = AB + AC      a(AB) = aA(B) = A(aB)

(A¯¹)¯¹ = A             det(AB) = det(A)det(B)
I¯¹ = I                 det(Aᵀ) = det(A)
(Aᵀ)¯¹ = (A¯¹)ᵀ         det(A¯¹) = det(A)¯¹
(AB)¯¹ = B¯¹A¯¹    
(cA)¯¹ = c¯¹A¯¹   

==============================================================================
VECTOR NOTATION
==============================================================================
    |b₁|
B = |b₂| = |B₁| = column vector 
    |b₃|

A = |a₁ a₂ a₃| = |A₍₁₎| = row vector

==============================================================================
MATRIX MULTIPLICATION
==============================================================================
Inner two numbers must conform to multiply: NxM & MxP = NxP
| a b c || j |   | aj + bk + cl |
| d e f || k | = | dj + ek + fl |
| g h i || l |   | gj + hk + il |
   3x3     3x1   =      3x1

==============================================================================
TRANSPOSE OF A MATRIX
==============================================================================
 --------------
| (AB)ᵀ = BᵀAᵀ |
 --------------
    | a b |         | a c e | 
A = | c d |    Aᵀ = | b d f |
    | e f |     

==============================================================================
TRACE OF A MATRIX
==============================================================================
Sum of the main diagonal elements

    | a b c |
A = | d e f |  Tr(A) = a + e + i
    | g h i |

==============================================================================
DOT PRODUCT
==============================================================================
For two row vectors a and b:
 -----------------------
| a.b = b.a = AᵀB = BᵀA |
 -----------------------

          |b₁|
|a₁ a₂ a₃||b₂| = a₁b₁ + a₂b₂ + a₃b₃
          |b₃|

==============================================================================
TENSOR PRODUCT
==============================================================================
For two row vectors a and b:
 -------------------------------------------
| ABᵀ= BAᵀ = a⊗b = b⊗a = nxn square matrix |
 -------------------------------------------
| trace(a⊗b) = sum of diagonal of c = a.b | 
 ------------------------------------------
| (u.v)w = (w⊗v)u |
 -----------------

|b₁|             |b₁+a₁ b₁+a₂ b₁+a₃|
|b₂||a₁ a₂ a₃| = |b₂+a₁ b₂+a₂ b₂+a₃|
|b₃|             |b₃+a₁ b₃+a₂ b₃+a₃|

==============================================================================
PROJECTION
==============================================================================
For two row vectors a and b:

SCALAR PROJECTION:  a.b̂ = trace(a⊗b̂)
VECTOR PROJECTION:  (a.b̂)b̂ = (b̂⊗b̂)a
                    (a.b̂)b̂ = trace(a⊗b̂)b̂

==============================================================================
CROSS PRODUCT
==============================================================================

SKEW SYMMETRIC MATRIX
    | 0  -uᶻ  uʸ |          | 0  -uᶻ  uʸ || vˣ |
u = | uᶻ  0  -uˣ |  u X v = | uᶻ  0  -uˣ || vʸ |
    |-uʸ  uˣ  0  |          |-uʸ  uˣ  0  || vᶻ |

DETERMINANT METHOD
        | i  j  k  |
a X b = | aˣ aʸ aᶻ | = (-1)¹⁺¹|aʸ aᶻ| + (-1)¹⁺²|aˣ aᶻ| + (-1)¹⁺³|aˣ aʸ|
        | bˣ bʸ bᶻ |          |bʸ bᶻ|          |bˣ bᶻ|          |bˣ bʸ|

==============================================================================
TRIPLE PRODUCTS
==============================================================================
        
TRIPLE SCALAR PRODUCT
                              | aˣ aʸ aᶻ |
det = volume(V) = a.(b X c) = | bˣ bʸ bᶻ |
                              | cˣ cʸ cᶻ |
        
==============================================================================
DETERMINANT
==============================================================================

2X2 DETERMINANT
 ----------------------------
| det(A) = | a b | = ad - bc |
|          | c d |           |
 ----------------------------
 For two vectors a and b 
 det = area of rectangle formed from both vectors
 | aˣ aʸ |   
 | bˣ bʸ |


3X3 DETERMINANT: LAPLACE EXPANSION METHOD
| a₁₁ a₁₂ a₁₃ |
| a₂₁ a₂₂ a₂₃ |
| a₃₁ a₃₂ a₃₃ |

Using any row/column:
    det(A) = a₁₁cof(a₁₁) + a₁₂cof(a₁₂) + a₁₃cof(a₁₃)
    cof(a₁₁) = (-1)¹⁺¹M
    M = | a₂₂ a₂₃ |
        | a₃₂ a₃₃ |

==============================================================================
INVERSE (CRAMER'S METHOD)
==============================================================================
 ------------------------
| A¯¹ = (1/det(A))ADJ(A) |
 ------------------------

       | c(a₁₁) c(a₁₂) c(a₁₃) |T
 ADJ = | c(a₂₁) c(a₂₂) c(a₂₃) |
       | c(a₃₁) c(a₃₂) c(a₃₃) |

 cof(aⁱʲ) = (-1)ⁱ⁺ʲM


//////////////////////////////////////////////////////////////////////////////
//TRANFORMATIONS
//////////////////////////////////////////////////////////////////////////////

RELATION: Maps set of values from one set (domain/x) to another (range/y)
FUNCTION: Relation where each value in domain maps to one in a range
TRANSFORMATION: Function that maps one space to another

LINEAR TRANSFORMATION:  a function that maps one vector space into another; 
                        a change of basis
                        Tr(ax + y) = aTr(x) + Tr(y)

v = xi + yj + zk    Tr(i) = a, Tr(j) = b, Tr(k) = c
v' = Tr(v) = Tr(xi + yj + zk) = xTr(i) + yTr(j) + zTr(k) = xa + yb + zc


TRANSFORMING LOCALLY:
    1. Translate the system so that point P is at the origin 
       (temp remove current translation)
    2. Apply the transformation about the origin
    3. Add the old tranlation to the matrix


COMPOSITION OF TRANSFORMS
 --------------------
| (T o S)v = T(S(v)) |
 --------------------

POINTS                          VECTORS
| A y || x | = | ax + y |       | A y || x | = | ax |
| 0 1 || 1 |   |    1   |       | 0 1 || 0 |   | 0  |
 
v  = (x, y, z)
v' = (x*w, y*w, z*w, w)

==============================================================================
TRANSLATION
==============================================================================

| 1 0 0 a₁ || P₁ |   | P₁ + a₁ |
| 0 1 0 a₂ || P₂ | = | P₂ + a₂ |
| 0 0 1 a₃ || P₃ |   | P₃ + a₃ |
| 0 0 0 1  || 1  |   |    1    |

==============================================================================
SCALING
==============================================================================

| a₁ 0 0 0 || P₁ |   | a₁P₁ |
| 0 a₂ 0 0 || P₂ | = | a₂P₂ |
| 0 0 a₃ 0 || P₃ |   | a₃P₃ |
| 0 0 0  1 || 1  |   |  1   |

==============================================================================
ROTATION
==============================================================================

     Z AXIS[LH]               X AXIS [LH]             Y AXIS [LH] 
| cosƟ -sinƟ  0  0 |    |  1   0     0    0 |    | cosƟ  0  sinƟ  0 |
| sinƟ  cosƟ  0  0 |    |  0  cosƟ -sinƟ  0 |    |  0    1   0    0 |
|  0     0    1  0 |    |  0  sinƟ  cosƟ  0 |    |-sinƟ  0  cosƟ  0 |
|  0     0    0  1 |    |  0   0     0    1 |    |  0    0   0    1 |

     Z AXIS[RH]               X AXIS [RH]             Y AXIS [RH] 
|  cosƟ  sinƟ  0  0 |   |  1   0    0     0 |    | cosƟ  0 -sinƟ  0 |
| -sinƟ  cosƟ  0  0 |   |  0  cosƟ  sinƟ  0 |    |  0    1   0    0 |
|   0     0    1  0 |   |  0 -sinƟ  cosƟ  0 |    | sinƟ  0  cosƟ  0 |
|   0     0    0  1 |   |  0   0     0    1 |    |  0    0   0    1 |

==============================================================================
ROTATION AROUND ARBITARY AXIS
==============================================================================

c = cos(Ɵ)
s = sin(Ɵ)
t = 1-cos(Ɵ)
u = (x,y,z) = arbitary axis

              LEFT HANDED                       
| (tx² + c)    (txy - sz)    (txz + sy)   0 |   
| (txy + sz)   (ty² + c)     (tyz - sx)   0 |   
| (txz - sy)   (tyz + sx)    (tz² + c)    0 |   
|     0            0              0       1 |   

                  RIGHT HANDED
 | (tx² + c)    (txy + sz)   (txz - sy)   0 |
 | (txy - sz)   (ty² + c)    (tyz + sx)   0 |
 | (txz + sy)   (tyz - sx)   (tz² + c)    0 |
 |     0           0              0       1 |


        ▲
     u /  b               Rotate point P around arbitary axis u by Ɵ amount 
      ▪-----►▪P(x,y,z)    
     /                    1) Create a basis B={â,b̂,ĉ} using u, b and u X b
  a /                           a = -projᵤw      a = norm(a)
   /     w   ▲                  b = w - projᵤw   b̂ = norm(b)    
  ▼          |ĉ                 c = a X b        ĉ = norm(c)
 C▪          ▪---►b̂                                     
/          a/             2) Find vector w in terms of new basis
           ▼                    w = P - C = b + a = (wˣ,wʸ,wᶻ)
                                wᵦ = ‖a‖̂a + ‖b‖̂b + 0̂c = (wᵦˣ,wᵦʸ,wᵦᶻ)
                                   
  3) Rotate wᵦ around a by Ɵ using rotation matrix where wᵦ' is rotated vector

        |  1   0     0    0 || wᵦˣ |   | wᵦ'ˣ |
        |  0  cosƟ -sinƟ  0 || wᵦʸ | = | wᵦ'ʸ | 
        |  0  sinƟ  cosƟ  0 || wᵦᶻ |   | wᵦ'ᶻ |
        |  0     0    0   1 || 0   |   |  0   | 

        wᵦ' = (wᵦ'ˣ,wᵦ'ʸ,wᵦ'ᶻ) = wᵦ'ˣ̂a + wᵦ'ʸ̂b + wᵦ'ᶻ̂c 
        
   4) Sub in a,b,c in terms of i,j,k to find final rotated point P'

        w' = (wᵦ'ˣ)a + (wᵦ'ʸ)b + (wᵦᶻ)c
           = (wᵦ'ˣ)(-projᵤw) + (wᵦ'ʸ)(w - projᵤw) + (wᵦᶻ)(a X b)

        P' = C + w' as P = C + w
    
==============================================================================
PROJECTION INTO A PLANE
==============================================================================

Point in plane: Po(a,b,c)
Point to project into plane: P(x,y,z)
Final point projected into plane: P'
Plane Basis: {u,v}

Projection Matrix (Q): | u v || uᵀ |
(tensor product)              | vᵀ |

 -------------------
| P' = Po + Q(P-Po) |
 -------------------

==============================================================================
REFLECTIONS IN THE PLANE
==============================================================================

v = vector in plane
v' = reflection of v in the plane
n = unit normal vector of plane

 proj a onto b = (a.b̂)b̂ = (b̂⊗b̂)a
 ------------------
| v' = v - 2(v.n)n |
 ------------------
| v' = v - 2(n⊗n)v |
 ------------------


==============================================================================
DESCRIBING IN A DIFFERENT BASIS
==============================================================================

A point/vector moves if a transform is applied
The coordinates a point/vector has depends on the basis it's described in
Changing the basis doesn't change where the object is in space
It just changes how it's expressed

---------------------------------------------------------------------
eg(1) DESCRIBING IN A DIFFERENT BASIS USING VECTORS
---------------------------------------------------------------------

u = (5,8) find coordinates in space with basis {vo:(1,2) and v1:(4,7)}

u = 5i + 8j 
  = avo + bv1 = a(1,2) + b(4,7) 
  = (a,2a) + (4b,7b)

As (5,8) = (a+4b,2a+7b)
5 = a + 4b and 8 = 2a + 7b
Substitute and solve for a,b to find new coordinates in {vo,v1} basis
(a,b) = (-3,2)

---------------------------------------------------------------------
eg(2) DESCRIBING IN A DIFFERENT BASIS USING MATRICES
---------------------------------------------------------------------

Express from local into external
Vᵉˣᵗ = AVˡᵒᶜ

Express from external into local
Vˡᵒᶜ = A¯¹Vᵉˣᵗ

Where A is the transformation matrix that transforms the object's basis 
vectors from their initial starting position of aligned with world basis


//////////////////////////////////////////////////////////////////////////////
//TRIGONOMETRY
//////////////////////////////////////////////////////////////////////////////

       /|                /|         sinƟ = O/C
    a / |             C / |         cosƟ = A/C  
     /  | ‖a‖sinƟ      /  | O       tanƟ = O/A
    /Ɵ  |             /Ɵ  |
    ----              ----
   ‖a‖cosƟ              A


SIN WAVE: 
To combine waves, just add each equation to each other
To get circular waves, use radius r as x
 -------------------
| y = asin(kx-wt+ɸ) |
 -------------------
 a = amplitude; height of sine wave
 k = angular wave number; number of wavelengths to reach 2∏
 t = time
 w = speed
 ɸ = initial shift of the wave


//////////////////////////////////////////////////////////////////////////////
//SYSTEMS OF LINEAR EQUATIONS
//////////////////////////////////////////////////////////////////////////////

USED: Finding common points in a series of planes/lines

A Series of plane equations can be written:
ax + by + cz = d    | a b c || x |   | d |
ex + fy + gz = h    | e f g || y | = | h |  or Av = w
ix + jy + kz = l    | i j k || z |   | l |

We want v which is the intersection of all three equations
 ----------
| v = A¯¹w |
 ----------

ROW REDUCTION: 
Aim is to get Augmented matrix into Row/Row reduced Echelon form

AUGMENTED MATRIX:       ROW ECHELON FORM:       ROW REDUCED ECHELON FORM:
| a b c | d |           | 1 t s | q |           | 1 0 0 | m |
| e f g | h |     =>    | 0 1 u | r |     or    | 0 1 0 | n |
| i j k | l |           | 0 0 1 | p |           | 0 0 1 | p |

SOLUTIONS: P(m,n,p) is the common point for all three equations

ROW REDUCTION OPERATIONS:
(1) Swap Rows
(2) Times a row by a scalar
(3) Add a row to another

ROW REDUCED WHEN:
(1) Reading left->right, first non-zero is a 1
(2) Any column containing 1, rest is 0
(3) Rows of all zero are at the bottom
(4) All 1s descent left to right down the matrix

RANK(R): Number of nonzero rows in upper triangular form
UNKNOWNS(N): Number of x,y,z to find

INCONSISTANT SYSTEM: 
NO SOLUTIONS Has row | 0 0 ... 0 | a | 

CONSISTANT SYSTEM: 
SOLUTIONS Has rows | 1 0 ... 0 | a | or | 0 0 ... 0 | 0 |
-> UNDER-DETERMINED: Infinitely Many Solutions when R < N 
-> OVER-DETERMINED: One Unique Solution but too many equations when R > N 
-> EXACT: One solution with exact number of equations when R = N

----------------------------------------------------------------
Eg(1): Find Intersection of Plane and Line
----------------------------------------------------------------
Given Po and P1 are on the line P(t) = Po + t(P1-Po)
    x = xo + t(x1-xo)
    y = yo + t(y1-yo)
    z = zo + t(z1-zo)

Rearrange ot make t the subject:
    t = (x-xo)/(x1-xo) = (y-yo)/(y1-yo) = (z-zo)/(z1-zo)
    let ∆x = x1-xo, ∆y = y1-yo, ∆z = z1-zo

EQUATIONS:
    ax + by + cz = d
    ∆yx -∆xy = ∆yxo - ∆xyo
    ∆yz - ∆zy = ∆yzo - ∆zyo

AUGMENTED MATRIX:
|  a   b   c |      d      |        
| ∆y -∆x   0 | ∆yxo - ∆xyo |
|  0 -∆z  ∆y | ∆yzo - ∆zyo |


//////////////////////////////////////////////////////////////////////////////
//PROBABILITY 
//////////////////////////////////////////////////////////////////////////////

LIMITING FREQUENCY: proportion of occurance of value after number of trials
PROBABILITY: limiting frequence over infinate number of trials

USED FOR: Imperfect information
RISK AVERSE: Choose guaranteed payoff over the game if guaranteed payoff 
             is ≤ expected value of game
RISK TAKING: Choose guaranteed payoff over the game if guaranteed payoff is 
             ≥ expected value of game
RISK NEUTRAL: Always select strategy with highest expected payoff

Pr[X & Y] = Pr[X|Y]Pr[Y]    Probability of Y and X occuring after Y
Pr[X & Y] = Pr[X]Pr[Y]      Probability of X and Y together (in no order)
Pr[X|Y]                     Probability of X occuring after Y

ExpectedValue = Pr(x1)*v1 + Pr(x2)*v2 + ...
Pr(x) = probability of x happening
v = value recieved if x happens


//////////////////////////////////////////////////////////////////////////////
//IMAGINARY NUMBERS
//////////////////////////////////////////////////////////////////////////////

====================================================================
IMAGINARY NUMBERS [i]
====================================================================

i = √(-1)   i° = 1
i¹ = i      i² = -1
i³ = -i

====================================================================
COMPLEX NUMBERS [a + bi]
====================================================================

CONJUGATES: 

  v = a + bi    
  v = a - bi
  v = a + bi

CONJUGATE RULES:
   ___             __             ___
   v+w = v + w     vw = v w       v/w = v / w

   vv = (a - bi)(a + bi) = (a² + b²)  (as i² = -1)

EXTRACTING REAL/IMAG PARTS:

  Real(v) = ¹/₂(v + v)
  Imag(v) = ¹/₂ᵢ(v - v)

COMPLEX RULES: 
  
  (a + bi) + (c + di) = (a+c) + (b+d)i
  (a + bi) - (c + di) = (a-c) + (b-d)i

  (a + bi)(c + di) = (ac + adi + cbi + bdi²) = (ac - bd) + (ad + cb)i 

  (a + bi)     (a + bi)(c - di)     (ac + bd) + (cb - ad)i   
  --------  =  ----------------- =  -----------------------  
  (c + di)     (c + di)(c - di)           (c² + d²)          

  
     (ac + bd)     (cb - ad) 
  =  ---------  +  --------- i  (use conjugate to divide)
     (c² + d²)      (c² + d²)
  



====================================================================
POLAR FORM [r(cosƟ + isinƟ)]
====================================================================

CONVERTING TO/FROM POLAR FORM:

    for v = x + yi:
    r = ‖v‖ = √(x² + y²)
    x = ‖r‖cosƟ 
    yi = i‖r‖sinƟ

         -----------------------------------
    ⁂  | x + yi = r(cosƟ + isinƟ) = r cis Ɵ |
         -----------------------------------

//////////////////////////////////////////////////////////////////////////////
//QUATERNION/ROTATIONS
//////////////////////////////////////////////////////////////////////////////

 ----------------------
| q = w + xi + yj + zk |
 ----------------------
CONTAINS:
  - i,j,k are all imaginary
  - x,y,z component; axis which the rotation goes around
  - w componenent; amount of rotation around the axis

================================================================
MULTIPLYING
================================================================

q₁ = (w₁,x₁,y₁,z₁)
q₂ = (w₂,x₂,y₂,z₂)
 ---------------------
| q₁ * q₂ !=  q₂ * q₁ |
 ---------------------

 (q₁*q₂).w = w₁w₂ - x₁x₂ - y₁y₂ - z₁z₂
 (q₁*q₂).x = w₁x₂ + x₁w₂ + y₁z₂ - z₁y₂
 (q₁*q₂).y = w₁y₂ - x₁z₂ + y₁w₂ + z₁x₂
 (q₁*q₂).z = w₁z₂ + x₁y₂ - y₁x₂ + z₁w₂

================================================================
NORMALISING
================================================================

‖q‖ = √(w² + x² + y² + z²)
q̂ = q/‖q‖
magnitude of 1 like normal vectors

================================================================
ROTATIONS
================================================================
 
 ------------------------
| Q = local_rotation * Q |
 ------------------------
where Q is stored for the object and local_rotation is the amount
of rotation to be added/subtracted from the rotation quarternion Q
both quaternions should be unit and result in a unit quaternion

CREATING THE LOCAL ROTATION
    local_rotation.w  = cosf( Ɵ/2 )
    local_rotation.x = axis.x * sinf( Ɵ/2 )
    local_rotation.y = axis.y * sinf( Ɵ/2 )
    local_rotation.z = axis.z * sinf( Ɵ/2 )
    where axis is a unit vector the rotation will occur around
    Ɵ is the amount of rotation to occur
    creates a unit quaternion

GENERATE A MATRIX TO ROTATE POINTS

| (w²+x²-y²-z²)  (2xy-2wz)      (2xz+2wy)      0 | 
| (2xy+2wz)      (w²-x²+y²-z²)  (2yz+2wx)      0 | 
| (2xz-2wy)      (2yz-2wx)      (w²-x²-y²+z²)  0 |  
|     0              0              0          1 | 

simplifies to:

| (1-2y²-2z²)  (2xy-2wz)    (2xz+2wy)      0 | 
| (2xy+2wz)    (1-2x²-2z²)  (2yz+2wx)      0 | 
| (2xz-2wy)    (2yz-2wx)    (1-2x²-2y²)    0 |  
|     0             0            0         1 | 

*/////////////////////////////////////////////////////////////////////////////