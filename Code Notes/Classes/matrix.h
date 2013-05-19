/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com) 20.0f12
* 4x4 right handed matrix class
 RH MATRIX IN FORM OF [OPENGL]:
 | 11 12 13 x |  | Right.x  Up.x  Forward.x  Pos.x |
 | 21 22 23 y |  | Right.y  Up.y  Forward.y  Pos.y |
 | 31 32 33 z |  | Right.z  Up.z  Forward.z  Pos.z |
 | 0  0  0  1 |  |   0       0       0        1    |
*****************************************************************/
#pragma once

#include "float3.h"

class MATRIX
{
public:

    float m11, m12, m13, m14,
          m21, m22, m23, m24,
          m31, m32, m33, m34;

    /**
    * Gets various vectors associated with the matrix
    */
    FLOAT3 Right() const          { return FLOAT3(m11,m21,m31); }
    FLOAT3 Up() const             { return FLOAT3(m12,m22,m32); }
    FLOAT3 Forward() const        { return FLOAT3(m13,m23,m33); }
    FLOAT3 Position() const       { return FLOAT3(m14,m24,m34); }
    FLOAT3 GetRight() const       { return FLOAT3(m11,m21,m31); }
    FLOAT3 GetUp() const          { return FLOAT3(m12,m22,m32); }
    FLOAT3 GetForward() const     { return FLOAT3(m13,m23,m33); }
    FLOAT3 GetPosition() const    { return FLOAT3(m14,m24,m34); }

    /**
    * Sets the position
    */
    void SetPosition(float x, float y, float z) { m14 = x;    m24 = y;    m34 = z;   }
    void SetPosition(const FLOAT3& v)           { m14 = v.x;  m24 = v.y;  m34 = v.z; }

    /**
    * Sets the forward vector
    */
    void SetForward(float x, float y, float z)  { m13 = x;    m23 = y;    m33 = z;   }
    void SetForward(const FLOAT3& v)             { m13 = v.x;  m23 = v.y;  m33 = v.z; }

    /**
    * Sets the up vector
    */
    void SetUp(float x, float y, float z)       { m12 = x;    m22 = y;    m32 = z;   }
    void SetUp(const FLOAT3& v)                 { m12 = v.x;  m22 = v.y;  m32 = v.z; }

    /**
    * Sets the right vector
    */
    void SetRight(float x, float y, float z)    { m11 = x;    m21 = y;    m31 = z;   }
    void SetRight(const FLOAT3& v)              { m11 = v.x;  m21 = v.y;  m31 = v.z; }

    /**
    * Sets the scale of the matrix
    */
    void SetScale(float x, float y, float z)    { m11 = x;    m22 = y;    m33 = z;   }
    void SetScale(const FLOAT3& v)              { m11 = v.x;  m22 = v.y;  m33 = v.z; }
    void SetScale(float a)                      { m11 = a;    m22 = a;    m33 = a;   }

    /**
    * Sets all matrix components
    * @param the value to set all components to
    */
    void Set(float a)
    {
        m11 = m22 = m33 = m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = a;
    }

    /**
    * Sets all the matrix components
    * @param a pointer to a buffer of 16 floats
    * @param whether or not the buffer is right/left handed
    */
    void Set(const float* a, bool RH)
    {
        if(RH)
        {
            m11 = a[0];   m21 = a[1];   m31 = a[2];   
            m12 = a[4];   m22 = a[5];   m32 = a[6];   
            m13 = a[8];   m23 = a[9];   m33 = a[10];  
            m14 = a[12];  m24 = a[13];  m34 = a[14];
        }
        else
        {
            m11 = a[0];   m12 = a[1];   m13 = a[2];   m14 = a[3];
            m21 = a[4];   m22 = a[5];   m32 = a[6];   m24 = a[7];
            m31 = a[8];   m32 = a[9];   m33 = a[10];  m34 = a[11];
        }
    }

    /**
    * Sets all the matrix components
    * @param the forward, up, right and position vectors
    */
    void Set(const FLOAT3& Forward, const FLOAT3& Up, const FLOAT3& Right, const FLOAT3& Position)
    {
        m11 = Right.x;  m12 = Up.x;   m13 = Forward.x;  m14 = Position.x;
        m21 = Right.y;  m22 = Up.y;   m23 = Forward.y;  m24 = Position.y;
        m31 = Right.z;  m32 = Up.z;   m33 = Forward.z;  m34 = Position.z;
    }

    /**
    * Sets all the matrix components
    * @param each component to be set
    */
    void Set(float M11,float M12,float M13,float M14,float M21,float M22,float M23,float M24,float M31,float M32,float M33,float M34)
    {
        m11 = M11;  m12 = M12;  m13 = M13;  m14 = M14;
        m21 = M21;  m22 = M22;  m23 = M23;  m24 = M24;
        m31 = M31;  m32 = M32;  m33 = M33;  m34 = M34;
    }

    /**
    * Sets all the matrix components
    * @param each component to be set except position
    */
    void Set(float M11,float M12,float M13,float M21,float M22,float M23,float M31,float M32,float M33)
    {
        m11 = M11;  m12 = M12;  m13 = M13;
        m21 = M21;  m22 = M22;  m23 = M23;
        m31 = M31;  m32 = M32;  m33 = M33;
    }

    /**
    * Makes the matrix the indentiy
    */
    void MakeIdentity()
    {
        m11 = m22 = m33 = 1.0f;
        m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = 0.0f;
    }

    /**
    * Makes the 3x3 matrix the indentiy; position remains the same
    */
    void MakeIdentity3x3()
    {
        m11 = m22 = m33 = 1.0f;
        m12 = m13 = m21 = m23 = m31 = m32 = 0.0f;
    }

    /**
    * Default Constructor
    */
    MATRIX()
    { 
        MakeIdentity(); 
    }

    /**
    * Constructor
    * @param the forward, up, right and position vectors
    */
    MATRIX(const FLOAT3& Forward, const FLOAT3& Up, const FLOAT3& Right, const FLOAT3& Position)
    { 
        Set(Forward,Up,Right,Position); 
    }

    /**
    * Constructor
    * @param each component to be set
    */
    MATRIX(float M11,float M12,float M13,float M14,float M21,float M22,float M23,float M24,float M31,float M32,float M33,float M34)
    { 
        Set(M11,M12,M13,M14,M21,M22,M23,M24,M31,M32,M33,M34); 
    }

    /**
    * Constructor
    * @param a pointer to a buffer of 16 floats
    * @param whether or not the buffer is right/left handed
    */
    MATRIX(const float * a, bool RH)
    { 
        Set(a,RH); 
    }

    /**
    * Matrix Multiplication: FLOAT3 *= MATRIX
    */
    friend void operator*=(FLOAT3& v, const MATRIX& M)
    {
        FLOAT3 t = v;
        v.x = (M.m11*t.x)+(M.m12*t.y)+(M.m13*t.z)+(M.m14*1);
        v.y = (M.m21*t.x)+(M.m22*t.y)+(M.m23*t.z)+(M.m24*1);
        v.z = (M.m31*t.x)+(M.m32*t.y)+(M.m33*t.z)+(M.m34*1);
    }

    /**
    * Matrix Multiplication: MATRIX * FLOAT3
    */
    FLOAT3 operator*(const FLOAT3 & v) const
    {
        return(FLOAT3((m11*v.x)+(m12*v.y)+(m13*v.z)+(m14*1),
                      (m21*v.x)+(m22*v.y)+(m23*v.z)+(m24*1),
                      (m31*v.x)+(m32*v.y)+(m33*v.z)+(m34*1)));
    }

    /**
    * Matrix Multiplication: FLOAT3 * MATRIX
    */
    friend FLOAT3 operator*(const FLOAT3 & v, const MATRIX & M)
    {
        return(M*v);
    }

    /**
    * Matrix Multiplication: [THIS][M]
    */
    MATRIX operator*(const MATRIX& M) const
    {
        return (MATRIX( (m11*M.m11)+(m12*M.m21)+(m13*M.m31)+(m14*0.0f),
                        (m11*M.m12)+(m12*M.m22)+(m13*M.m32)+(m14*0.0f),
                        (m11*M.m13)+(m12*M.m23)+(m13*M.m33)+(m14*0.0f),
                        (m11*M.m14)+(m12*M.m24)+(m13*M.m34)+(m14), //*1.0f
                        (m21*M.m11)+(m22*M.m21)+(m23*M.m31)+(m24*0.0f),
                        (m21*M.m12)+(m22*M.m22)+(m23*M.m32)+(m24*0.0f),
                        (m21*M.m13)+(m22*M.m23)+(m23*M.m33)+(m24*0.0f),
                        (m21*M.m14)+(m22*M.m24)+(m23*M.m34)+(m24), //*1.0f
                        (m31*M.m11)+(m32*M.m21)+(m33*M.m31)+(m34*0.0f),
                        (m31*M.m12)+(m32*M.m22)+(m33*M.m32)+(m34*0.0f),
                        (m31*M.m13)+(m32*M.m23)+(m33*M.m33)+(m34*0.0f),
                        (m31*M.m14)+(m32*M.m24)+(m33*M.m34)+(m34))); //*1.0f
    }

    /**
    * Matrix Multiplication: [THIS] = [THIS][M]
    */
    void operator*=(const MATRIX& M)
    {
        MATRIX T = (*this);
        m11 = (T.m11*M.m11)+(T.m12*M.m21)+(T.m13*M.m31)+(T.m14*0.0f);
        m12 = (T.m11*M.m12)+(T.m12*M.m22)+(T.m13*M.m32)+(T.m14*0.0f);
        m13 = (T.m11*M.m13)+(T.m12*M.m23)+(T.m13*M.m33)+(T.m14*0.0f);
        m14 = (T.m11*M.m14)+(T.m12*M.m24)+(T.m13*M.m34)+(T.m14); //*1.0f
        m21 = (T.m21*M.m11)+(T.m22*M.m21)+(T.m23*M.m31)+(T.m24*0.0f);
        m22 = (T.m21*M.m12)+(T.m22*M.m22)+(T.m23*M.m32)+(T.m24*0.0f);
        m23 = (T.m21*M.m13)+(T.m22*M.m23)+(T.m23*M.m33)+(T.m24*0.0f);
        m24 = (T.m21*M.m14)+(T.m22*M.m24)+(T.m23*M.m34)+(T.m24); //*1.0f
        m31 = (T.m31*M.m11)+(T.m32*M.m21)+(T.m33*M.m31)+(T.m34*0.0f);
        m32 = (T.m31*M.m12)+(T.m32*M.m22)+(T.m33*M.m32)+(T.m34*0.0f);
        m33 = (T.m31*M.m13)+(T.m32*M.m23)+(T.m33*M.m33)+(T.m34*0.0f);
        m34 = (T.m31*M.m14)+(T.m32*M.m24)+(T.m33*M.m34)+(T.m34); //*1.0f
    }

    /**
    * Matrix Multiplication: MATRIX * Scalar
    */
    MATRIX operator*(float a) const
    {
        return (MATRIX(m11*a, m12*a, m13*a, m14*a,
                       m21*a, m22*a, m23*a, m24*a,
                       m31*a, m32*a, m33*a, m34*a));
    }

    /**
    * Matrix Multiplication: MATRIX *= Scalar
    */
    void operator*=(float a)
    {
        m11 *= a;   m12 *= a;   m13 *= a;   m14 *= a;
        m21 *= a;   m22 *= a;   m23 *= a;   m24 *= a;
        m31 *= a;   m32 *= a;   m33 *= a;   m34 *= a;
    }

    /**
    * Matrix Multiplication: MATRIX / Scalar
    */
    MATRIX operator/(float a) const
    {
        return((*this)*(1/a));
    }

    /**
    * Matrix Multiplication: MATRIX /= Scalar
    */
    void operator/=(float a) 
    {
        (*this)*=(1/a);
    }

    /**
    * Matrix Addition: MATRIX + MATRIX
    */
    MATRIX operator+(const MATRIX& M) const
    {
        return (MATRIX(m11+M.m11, m12+M.m12, m13+M.m13, m14+M.m14,
                       m21+M.m21, m22+M.m22, m23+M.m23, m24+M.m24,
                       m31+M.m31, m32+M.m32, m33+M.m33, m34+M.m34));
    }

    /**
    * Matrix Addition: MATRIX += MATRIX
    */
    void operator+=(const MATRIX& M)
    {
        m11 += M.m11;   m12 += M.m12;   m13 += M.m13;   m14 += M.m14;
        m21 += M.m21;   m22 += M.m22;   m23 += M.m23;   m24 += M.m24;
        m31 += M.m31;   m32 += M.m32;   m33 += M.m33;   m34 += M.m34;
    }

    /**
    * Matrix Subtraction: MATRIX - MATRIX
    */
    MATRIX operator-(const MATRIX& M) const
    {
        return (MATRIX(m11-M.m11, m12-M.m12, m13-M.m13, m14-M.m14,
                       m21-M.m21, m22-M.m22, m23-M.m23, m24-M.m24,
                       m31-M.m31, m32-M.m32, m33-M.m33, m34-M.m34));
    }

    /**
    * Matrix Subtraction: MATRIX -= MATRIX
    */
    void operator-=(const MATRIX& M)
    {
        m11 -= M.m11;   m12 -= M.m12;   m13 -= M.m13;   m14 -= M.m14;
        m21 -= M.m21;   m22 -= M.m22;   m23 -= M.m23;   m24 -= M.m24;
        m31 -= M.m31;   m32 -= M.m32;   m33 -= M.m33;   m34 -= M.m34;
    }

    /**
    * @return the 3x3 Trace of the matrix
    */
    float GetTrace3x3() const
    { 
        return (m11+m22+m33); 
    }

    /**
    * @return the 3x3 Transpose of the matrix
    */
    MATRIX GetTranspose3x3() const
    { 
        return MATRIX(m11,m21,m31,0.0f,m12,m22,m32,0.0f,m13,m23,m33,0.0f); 
    }

    /**
    * Normalizes the 3x3 matrix
    */
    void Normalize3x3()
    {
        SetRight(Right().GetNormalized());
        SetForward(Forward().GetNormalized());
        SetUp(Up().GetNormalized());
    }

    /**
    * Translates the position
    * @param components to translate along the x/y/z axis
    */
    void Translate(float x, float y, float z)   
    { 
        m14 += x;   
        m24 += y;  
        m34 += z;   
    }

    /**
    * Translates the position
    * @param components to translate along the x/y/z axis
    */
    void Translate(const FLOAT3& v)             
    { 
        m14 += v.x; 
        m24 += v.y; 
        m34 += v.z; 
    }

    /**
    * Scales the matrix
    * @param components to scale along the x/y/z axis
    */
    void Scale(float x, float y, float z)       
    { 
        m11 *= x;   
        m22 *= y;  
        m33 *= z;  
    }

    /**
    * Scales the matrix
    * @param components to scale along the x/y/z axis
    */
    void Scale(const FLOAT3& v)                      
    { 
        m11 *= v.x; 
        m22 *= v.y; 
        m33 *= v.z; 
    }

    /**
    * Scales the matrix
    * @param the amount to scale it by
    */
    void Scale(float a)                         
    { 
        m11 *= a;   
        m22 *= a;   
        m33 *= a;  
    }

    /**
    * Rotates around X axis
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    void RotateX(float radians)
    {
        MATRIX M;
        float c = cos(radians);
        float s = sin(radians);
        M.m22 = c;  M.m23 = s;  
        M.m32 = -s; M.m33 = c;  
        (*this) *= M;
    }

    /**
    * Rotates around Y axis
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    void RotateY(float radians)
    { 
        MATRIX M;
        float c = cos(radians);
        float s = sin(radians);
        M.m11 = c;  M.m13 = -s; 
        M.m31 = s;  M.m33 = c; 
        (*this) *= M;
    }

    /**
    * Rotates around Z axis
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    void RotateZ(float radians)
    { 
        MATRIX M;
        float c = cos(radians);
        float s = sin(radians);
        M.m11 = c;  M.m12 = s; 
        M.m21 = -s; M.m22 = c; 
        (*this) *= M;
    }

    /**
    * Creates an arbitrary rotation matrix and rotates around it
    * @param the vector to rotate around
    * @param the angle in radians to rotate
    * @return the arbitrary rotation matrix
    */
    void RotateArbitrary(FLOAT3 & v, float radians)
    {
        MATRIX M;
        float c = cos(radians);
        float s = sin(radians);
        float t = 1-(cos(radians));
        M.m11 = (t*(v.x*v.x)) + c;
        M.m12 = (t*(v.x*v.y)) + (s*v.z);
        M.m13 = (t*(v.x*v.z)) - (s*v.y);
        M.m21 = (t*(v.x*v.y)) - (s*v.z);
        M.m22 = (t*(v.y*v.y)) + c;
        M.m23 = (t*(v.y*v.z)) + (s*v.x);
        M.m31 = (t*(v.x*v.y)) + (s*v.y);
        M.m32 = (t*(v.y*v.z)) - (s*v.x);
        M.m33 = (t*(v.z*v.z)) + c;
        (*this) *= M;
    }

    /**
    * Translates the position from the local origin
    * @param components to translate along the x/y/z axis
    */
    void TranslateLocal(float x, float y, float z)  
    { 
        FLOAT3 p = Position();
        m14 = ((m14-p.x)+x)+p.x;   
        m24 = ((m24-p.y)+y)+p.y;   
        m34 = ((m34-p.z)+z)+p.z; 
    }

    /**
    * Translates the position from the local origin
    * @param components to translate along the x/y/z axis
    */
    void TranslateLocal(const FLOAT3& v) 
    { 
        TranslateLocal(v.x,v.y,v.z); 
    }

    /**
    * Scales around local origin
    * @param components to scale along the x/y/z axis
    */
    void ScaleLocal(float x, float y, float z)      
    {
        FLOAT3 p = Position();
        m11 = ((m11-p.x)*x)+p.x;    
        m22 = ((m22-p.y)*y)+p.y;    
        m33 = ((m33-p.z)*z)+p.z; 
    }

    /**
    * Scales around local origin
    * @param components to scale along the x/y/z axis
    */
    void ScaleLocal(const FLOAT3& v) 
    {
        ScaleLocal(v.x,v.y,v.z); 
    }

    /**
    * Scales around local origin
    * @param the amount to scale
    */
    void ScaleLocal(float a)   
    { 
        ScaleLocal(a,a,a); 
    }

    /**
    * Rotates around local origin in X direction
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    void RotateXLocal(float radians)
    {
        MATRIX M;
        FLOAT3 savedPosition = Position();
        float c = cos(radians);
        float s = sin(radians);
        M.m22 = c;  M.m23 = s;  
        M.m32 = -s; M.m33 = c; 
        SetPosition(FLOAT3(0.0f,0.0f,0.0f));
        (*this) *= M;
        Translate(savedPosition);
    }

    /**
    * Rotates around local origin in Y direction
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    void RotateYLocal(float radians)
    { 
        MATRIX M;
        FLOAT3 savedPosition = Position();
        float c = cos(radians);
        float s = sin(radians);
        M.m11 = c;  M.m13 = -s; 
        M.m31 = s;  M.m33 = c; 
        SetPosition(FLOAT3(0.0f,0.0f,0.0f));
        (*this) *= M;
        Translate(savedPosition);
    }

    /**
    * Rotates around local origin in Z direction
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    void RotateZLocal(float radians)
    { 
        MATRIX M;
        FLOAT3 savedPosition = Position();
        float c = cos(radians);
        float s = sin(radians);
        M.m11 = c;  M.m12 = s; 
        M.m21 = -s; M.m22 = c; 
        SetPosition(FLOAT3(0.0f,0.0f,0.0f));
        (*this) *= M;
        Translate(savedPosition);
    }

    /**
    * Creates an arbitrary rotation matrix and rotates locally around it
    * @param the vector to rotate around
    * @param the angle in radians to rotate
    * @return the arbitrary rotation matrix
    */
    void RotateArbitraryLocal(const FLOAT3& v, float radians)
    {
        MATRIX M;
        FLOAT3 savedPosition = Position();
        float c = cos(radians);
        float s = sin(radians);
        float t = 1.0f-(cos(radians));
        M.m11 = (t*(v.x*v.x)) + c;
        M.m12 = (t*(v.x*v.y)) + (s*v.z);
        M.m13 = (t*(v.x*v.z)) - (s*v.y);
        M.m21 = (t*(v.x*v.y)) - (s*v.z);
        M.m22 = (t*(v.y*v.y)) + c;
        M.m23 = (t*(v.y*v.z)) + (s*v.x);
        M.m31 = (t*(v.x*v.y)) + (s*v.y);
        M.m32 = (t*(v.y*v.z)) - (s*v.x);
        M.m33 = (t*(v.z*v.z)) + c;
        SetPosition(FLOAT3(0.0f,0.0f,0.0f));
        (*this) *= M;
        Translate(savedPosition);
    }


    /**
    * Tests whether matrix is the identity
    */
    bool IsIdentity() const
    {
        if((m11 == 1.0f) && (m12 == 0.0f) && (m13 == 0.0f) && (m14 == 0.0f))
        {
            if((m21 == 0.0f) && (m22 == 1.0f) && (m23 == 0.0f) && (m24 == 0.0f))
            {
                if((m31 == 0.0f) && (m32 == 0.0f) && (m33 == 1.0f) && (m34 == 0.0f))
                {
                    return true;
                }
            }
        }
        return false;
    }

    /**
    * Tests equality of two matrices
    */
    bool operator==(const MATRIX& M) const
    {
        if((m11 == M.m11) && (m12 == M.m12) && (m13 == M.m13) && (m14 == M.m14))
        {
            if((m21 == M.m21) && (m22 == M.m22) && (m23 == M.m23) && (m24 == M.m24))
            {
                if((m31 == M.m31) && (m32 == M.m32) && (m33 == M.m33) && (m34 == M.m34))
                {
                    return true;
                }
            }
        }
        return false;
    }

    /**
    * Tests inequality of two matrices
    */
    bool operator!=(const MATRIX & M) const
    {
        return !((*this) == M);
    }
    
    /**
    * Creates a Skew Symmetric Matrix
    * @param the vector to create the matrix with
    * @return the skew symmetric matrix
    */
    static MATRIX CreateSkewSymmetric(const FLOAT3& v)                   
    { 
        return(MATRIX(0.0f,-v.x,v.y,0.0f,v.x,0.0f,-v.z,0.0f,-v.y,v.z,0.0f,0.0f)); 
    }

    /**
    * Creates a Skew Symmetric Matrix
    * @param the components to create the matrix with
    * @return the skew symmetric matrix
    */
    static MATRIX CreateSkewSymmetric(float x, float y, float z)    
    { 
        return(MATRIX(0.0f,-x,y,0.0f,x,0.0f,-z,0.0f,-y,z,0.0f,0.0f)); 
    }

    /**
    * Creates a tensor product matrix from two vectors
    * @param the vectors to create the matrix with
    * @return the tensor product matrix
    */
    static MATRIX CreateTensor(const FLOAT3& a, const FLOAT3& b)
    {
        return(MATRIX(b.x*a.x, b.x*a.y, b.x*a.z, 0.0f,
                      b.y*a.x, b.y*a.y, b.y*a.z, 0.0f,
                      b.z*a.x, b.z*a.y, b.z*a.z, 0.0f));
    }

    /**
    * Creates a rotation matrix around the X axis
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    static MATRIX CreateRotateX(float radians)
    {
        MATRIX M;
        float c = cos(radians);
        float s = sin(radians);
        M.m22 = c;  M.m23 = s;  
        M.m32 = -s; M.m33 = c;  
        return M;
    }

    /**
    * Creates a rotation matrix around the Y axis
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    static MATRIX CreateRotateY(float radians)
    { 
        MATRIX M;
        float c = cos(radians);
        float s = sin(radians);
        M.m11 = c;  M.m13 = -s; 
        M.m31 = s;  M.m33 = c; 
        return M;
    }

    /**
    * Creates a rotation matrix around the Z axis
    * @param the angle in radians to rotate
    * @return the rotation matrix
    */
    static MATRIX CreateRotateZ(float radians)
    { 
        MATRIX M;
        float c = cos(radians);
        float s = sin(radians);
        M.m11 = c;  M.m12 = s; 
        M.m21 = -s; M.m22 = c; 
        return M;
    }

    /**
    * Creates a arbitrary rotation matrix
    * @param the vector to rotate around
    * @param the angle in radians to rotate
    * @return the arbitrary rotation matrix
    */
    static MATRIX CreateRotateArbitrary(const FLOAT3& v, float radians)
    {
        MATRIX M;
        float c = cos(radians);
        float s = sin(radians);
        float t = 1-(cos(radians));
        M.m11 = (t*(v.x*v.x)) + c;
        M.m12 = (t*(v.x*v.y)) + (s*v.z);
        M.m13 = (t*(v.x*v.z)) - (s*v.y);
        M.m21 = (t*(v.x*v.y)) - (s*v.z);
        M.m22 = (t*(v.y*v.y)) + c;
        M.m23 = (t*(v.y*v.z)) + (s*v.x);
        M.m31 = (t*(v.x*v.y)) + (s*v.y);
        M.m32 = (t*(v.y*v.z)) - (s*v.x);
        M.m33 = (t*(v.z*v.z)) + c;
        return M;
    }
};