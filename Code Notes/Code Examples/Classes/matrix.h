////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - matrix.h
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "vector3.h"

/**
* 4x4 right handed matrix class. 
* RH Matrix in form of OpenGL: 
* | 11 12 13 x || Right.x  Up.x  Forward.x  Pos.x |
* | 21 22 23 y || Right.y  Up.y  Forward.y  Pos.y |
* | 31 32 33 z || Right.z  Up.z  Forward.z  Pos.z |
* | 0  0  0  1 ||   0       0       0        1    |
*/
class Matrix
{
public:

    float m11, m12, m13, m14,
          m21, m22, m23, m24,
          m31, m32, m33, m34;

    /**
    * Default Constructor
    */
    Matrix()
    { 
        MakeIdentity(); 
    }

    /**
    * Constructor
    * @param forward/up/right The axis for the matrix
    * @param position The location for the matrix
    */
    Matrix(const Float3& forward, const Float3& up, 
           const Float3& right, const Float3& position)
    { 
        Set(forward, up, right, position); 
    }

    /**
    * Constructor
    * @param MXX Each component to be set
    */
    Matrix(float M11, float M12, float M13, float M14, 
           float M21, float M22, float M23, float M24, 
           float M31, float M32, float M33, float M34)
    { 
        Set(M11, M12, M13, M14, M21, M22,
            M23, M24, M31, M32, M33, M34); 
    }

    /**
    * @return The right axis for the matrix
    */
    Float3 Right() const    
    { 
        return Float3(m11, m21, m31); 
    }

    /**
    * @return The up axis for the matrix
    */
    Float3 Up() const       
    { 
        return Float3(m12, m22, m32); 
    }

    /**
    * @return The forward axis for the matrix
    */
    Float3 Forward() const   
    { 
        return Float3(m13, m23, m33);
    }

    /**
    * @return The position for the matrix
    */
    Float3 Position() const  
    { 
        return Float3(m14, m24, m34);
    }

    /**
    * Sets the position from components
    * @param x/y/z The components to use for the position
    */
    void SetPosition(float x, float y, float z)
    { 
        m14 = x;   
        m24 = y;   
        m34 = z;   
    }

    /**
    * Sets the position from a vector
    * @param vec The vector to use for the position
    */
    void SetPosition(const Float3& vec)           
    { 
        m14 = vec.x;  
        m24 = vec.y; 
        m34 = vec.z; 
    }

    /**
    * Sets the forward vector from components
    * @param x/y/z The components to use for the forward vector
    */
    void SetForward(float x, float y, float z) 
    { 
        m13 = x;  
        m23 = y;  
        m33 = z; 
    }

    /**
    * Sets the forward vector from a vector
    * @param vec The vector to use for the forward vector
    */
    void SetForward(const Float3& vec)
    { 
        m13 = vec.x; 
        m23 = vec.y;
        m33 = vec.z;
    }

    /**
    * Sets the up vector from components
    * @param x/y/z The components to use for the up vector
    */
    void SetUp(float x, float y, float z)  
    { 
        m12 = x;    
        m22 = y;   
        m32 = z;   
    }

    /**
    * Sets the up vector from a vector
    * @param vec The vector to use for the up vector
    */
    void SetUp(const Float3& vec)                 
    { 
        m12 = vec.x; 
        m22 = vec.y; 
        m32 = vec.z;
    }

    /**
    * Sets the right vector from components
    * @param x/y/z The components to use for the right vector
    */
    void SetRight(float x, float y, float z)   
    { 
        m11 = x; 
        m21 = y;  
        m31 = z;   
    }

    /**
    * Sets the right vector from a vector
    * @param vec The vector to use for the right vector
    */
    void SetRight(const Float3& vec)             
    { 
        m11 = vec.x; 
        m21 = vec.y; 
        m31 = vec.z; 
    }

    /**
    * Sets the scale of the matrix from components
    * @note should only be used on a matrix without rotation
    * @param x/y/z The components to use for scaling
    */
    void SetScale(float x, float y, float z)  
    { 
        m11 = x; 
        m22 = y; 
        m33 = z; 
    }

    /**
    * Sets the scale of the matrix from a vector
    * @note should only be used on a matrix without rotation
    * @param vec The vector to use for scaling
    */
    void SetScale(const Float3& vec)              
    { 
        m11 = vec.x;  
        m22 = vec.y; 
        m33 = vec.z; 
    }

    /**
    * Sets the uniform scale of the matrix from a component
    * @note should only be used on a matrix without rotation
    * @param scale The scale to set for all components
    */
    void SetScale(float scale)               
    { 
        m11 = scale;  
        m22 = scale;  
        m33 = scale;   
    }

    /**
    * Sets all the matrix components
    * @param mat A pointer to a buffer of 16 floats
    */
    void Set(const float* mat)
    {
        m11 = mat[0];   m21 = mat[1];   m31 = mat[2];   
        m12 = mat[4];   m22 = mat[5];   m32 = mat[6];   
        m13 = mat[8];   m23 = mat[9];   m33 = mat[10];  
        m14 = mat[12];  m24 = mat[13];  m34 = mat[14];
    }

    /**
    * Sets all the matrix components
    * @param forward/up/right The axis for the matrix
    * @param position The location for the matrix
    */
    void Set(const Float3& forward, const Float3& up,
        const Float3& right, const Float3& position)
    {
        m11 = right.x;  m12 = up.x;   m13 = forward.x;  m14 = position.y;
        m31 = right.z;  m32 = up.z;   m33 = forward.z;  m34 = position.z;
    }

    /**
    * Sets all the matrix components
    * @param MXX Each component to be set including position
    */
    void Set(float M11, float M12, float M13, float M14,
             float M21, float M22, float M23, float M24,
             float M31, float M32, float M33, float M34)
    {
        m11 = M11;  m12 = M12;  m13 = M13;  m14 = M14;
        m21 = M21;  m22 = M22;  m23 = M23;  m24 = M24;
        m31 = M31;  m32 = M32;  m33 = M33;  m34 = M34;
    }

    /**
    * @return The 3x3 Transpose of the matrix
    */
    Matrix GetTranspose3x3() const
    { 
        return Matrix(m11, m21, m31, 0.0f, m12, 
            m22, m32, 0.0f, m13, m23, m33, 0.0f); 
    }

    /**
    * Makes the matrix the indentiy matrix
    */
    void MakeIdentity()
    {
        m11 = 1.0f;  m21 = 0.0f;  m31 = 0.0f;
        m12 = 0.0f;  m22 = 1.0f;  m32 = 0.0f;
        m13 = 0.0f;  m23 = 0.0f;  m33 = 1.0f;
        m14 = 0.0f;  m24 = 0.0f;  m34 = 0.0f;
    }

    /**
    * @return Whether the matrix is the identity matrix
    */
    bool IsIdentity() const
    {
        return m11 == 1.0f && m12 == 0.0f && m13 == 0.0f && m14 == 0.0f &&
               m21 == 0.0f && m22 == 1.0f && m23 == 0.0f && m24 == 0.0f &&
               m31 == 0.0f && m32 == 0.0f && m33 == 1.0f && m34 == 0.0f;
    }

    /**
    * @param mat The matrix to test equality with
    * @return Whether the two matrices are equal
    */
    bool operator==(const Matrix& mat) const
    {
        return m11 == mat.m11 && m12 == mat.m12 && m13 == mat.m13 && 
               m14 == mat.m14 && m21 == mat.m21 && m22 == mat.m22 && 
               m23 == mat.m23 && m24 == mat.m24 && m31 == mat.m31 && 
               m32 == mat.m32 && m33 == mat.m33 && m34 == mat.m34;
    }

    /**
    * @param mat The matrix to test inequality with
    * @return Whether the two matrices are inequal
    */
    bool operator!=(const Matrix & mat) const
    {
        return !((*this) == mat);
    }

    /**
    * Matrix Multiplication: Float3 *= Matrix
    * @param vec the float3 vector to multiply with
    * @param mat The matrix to multiply with
    */
    friend void operator*=(Float3& vec, const Matrix& mat)
    {
        Float3 v = vec;
        vec.x = (mat.m11*v.x)+(mat.m12*v.y)+(mat.m13*v.z)+mat.m14;
        vec.y = (mat.m21*v.x)+(mat.m22*v.y)+(mat.m23*v.z)+mat.m24;
        vec.z = (mat.m31*v.x)+(mat.m32*v.y)+(mat.m33*v.z)+mat.m34;
    }

    /**
    * Matrix Multiplication: Matrix * Float3
    * @param vec The float3 vector to multiply with
    * @return A vector transformed by the matrix
    */
    Float3 operator*(const Float3& vec) const
    {
        return Float3((m11*vec.x)+(m12*vec.y)+(m13*vec.z)+m14,
                      (m21*vec.x)+(m22*vec.y)+(m23*vec.z)+m24,
                      (m31*vec.x)+(m32*vec.y)+(m33*vec.z)+m34);
    }

    /**
    * Matrix Multiplication: Float3 * Matrix
    * @param vec The float3 vector to multiply with
    * @param mat The matrix to multiply with
    * @return A vector transformed by the matrix
    */
    friend Float3 operator*(const Float3& vec, const Matrix& mat)
    {
        return mat*vec;
    }

    /**
    * Matrix Multiplication: [this][mat]
    * @param mat the Matrix to multiply with
    * @return The multiplied matrices
    */
    Matrix operator*(const Matrix& mat) const
    {
        return Matrix((m11*mat.m11)+(m12*mat.m21)+(m13*mat.m31),
                      (m11*mat.m12)+(m12*mat.m22)+(m13*mat.m32),
                      (m11*mat.m13)+(m12*mat.m23)+(m13*mat.m33),
                      (m11*mat.m14)+(m12*mat.m24)+(m13*mat.m34)+m14,
                      (m21*mat.m11)+(m22*mat.m21)+(m23*mat.m31),
                      (m21*mat.m12)+(m22*mat.m22)+(m23*mat.m32),
                      (m21*mat.m13)+(m22*mat.m23)+(m23*mat.m33),
                      (m21*mat.m14)+(m22*mat.m24)+(m23*mat.m34)+m24,
                      (m31*mat.m11)+(m32*mat.m21)+(m33*mat.m31),
                      (m31*mat.m12)+(m32*mat.m22)+(m33*mat.m32),
                      (m31*mat.m13)+(m32*mat.m23)+(m33*mat.m33),
                      (m31*mat.m14)+(m32*mat.m24)+(m33*mat.m34)+m34);
    }

    /**
    * Matrix Multiplication: [this] = [this][mat]
    * @param mat the Matrix to multiply with
    */
    void operator*=(const Matrix& mat)
    {
        Matrix tmat = *this;
        m11 = (tmat.m11*mat.m11)+(tmat.m12*mat.m21)+(tmat.m13*mat.m31);
        m12 = (tmat.m11*mat.m12)+(tmat.m12*mat.m22)+(tmat.m13*mat.m32);
        m13 = (tmat.m11*mat.m13)+(tmat.m12*mat.m23)+(tmat.m13*mat.m33);
        m14 = (tmat.m11*mat.m14)+(tmat.m12*mat.m24)+(tmat.m13*mat.m34)+tmat.m14;
        m21 = (tmat.m21*mat.m11)+(tmat.m22*mat.m21)+(tmat.m23*mat.m31);
        m22 = (tmat.m21*mat.m12)+(tmat.m22*mat.m22)+(tmat.m23*mat.m32);
        m23 = (tmat.m21*mat.m13)+(tmat.m22*mat.m23)+(tmat.m23*mat.m33);
        m24 = (tmat.m21*mat.m14)+(tmat.m22*mat.m24)+(tmat.m23*mat.m34)+tmat.m24;
        m31 = (tmat.m31*mat.m11)+(tmat.m32*mat.m21)+(tmat.m33*mat.m31);
        m32 = (tmat.m31*mat.m12)+(tmat.m32*mat.m22)+(tmat.m33*mat.m32);
        m33 = (tmat.m31*mat.m13)+(tmat.m32*mat.m23)+(tmat.m33*mat.m33);
        m34 = (tmat.m31*mat.m14)+(tmat.m32*mat.m24)+(tmat.m33*mat.m34)+tmat.m34;
    }

    /**
    * Matrix Multiplication: Matrix * Scalar
    * @param value The scalar to multiply the matrix by
    * @return The matrix multiplied by the value
    */
    Matrix operator*(float value) const
    {
        return Matrix(m11*value, m12*value, m13*value, m14*value,
                      m21*value, m22*value, m23*value, m24*value,
                      m31*value, m32*value, m33*value, m34*value);
    }

    /**
    * Matrix Multiplication: Matrix *= Scalar
    * @param value The scalar to multiply the matrix by
    */
    void operator*=(float value)
    {
        m11 *= value;   m12 *= value;   m13 *= value;   m14 *= value;
        m21 *= value;   m22 *= value;   m23 *= value;   m24 *= value;
        m31 *= value;   m32 *= value;   m33 *= value;   m34 *= value;
    }

    /**
    * Matrix Division: Matrix / Scalar
    * @param value The scalar to divide the matrix by
    * @return The matrix divided by the value
    */
    Matrix operator/(float value) const
    {
        return (*this) * (1.0f/value);
    }

    /**
    * Matrix Division: Matrix /= Scalar
    * @param value The scalar to divide the matrix by
    */
    void operator/=(float value) 
    {
        (*this) *= 1.0f/value;
    }

    /**
    * Matrix Addition: Matrix + Matrix
    * @param mat The matrix to add
    * @return A matrix with the combined matrices
    */
    Matrix operator+(const Matrix& mat) const
    {
        return Matrix(m11+mat.m11, m12+mat.m12, m13+mat.m13, m14+mat.m14,
                      m21+mat.m21, m22+mat.m22, m23+mat.m23, m24+mat.m24,
                      m31+mat.m31, m32+mat.m32, m33+mat.m33, m34+mat.m34);
    }

    /**
    * Matrix Addition: Matrix += Matrix
    * @param mat The matrix to add
    */
    void operator+=(const Matrix& mat)
    {
        m11 += mat.m11;   m12 += mat.m12;   m13 += mat.m13;   m14 += mat.m14;
        m21 += mat.m21;   m22 += mat.m22;   m23 += mat.m23;   m24 += mat.m24;
        m31 += mat.m31;   m32 += mat.m32;   m33 += mat.m33;   m34 += mat.m34;
    }

    /**
    * Matrix Subtraction: Matrix - Matrix
    * @param mat The matrix to subtract
    * @return A matrix with the subtracted matrices
    */
    Matrix operator-(const Matrix& mat) const
    {
        return Matrix(m11-mat.m11, m12-mat.m12, m13-mat.m13, m14-mat.m14,
                      m21-mat.m21, m22-mat.m22, m23-mat.m23, m24-mat.m24,
                      m31-mat.m31, m32-mat.m32, m33-mat.m33, m34-mat.m34);
    }

    /**
    * Matrix Subtraction: Matrix -= Matrix
    * @param mat The matrix to subtract
    */
    void operator-=(const Matrix& mat)
    {
        m11 -= mat.m11;   m12 -= mat.m12;   m13 -= mat.m13;   m14 -= mat.m14;
        m21 -= mat.m21;   m22 -= mat.m22;   m23 -= mat.m23;   m24 -= mat.m24;
        m31 -= mat.m31;   m32 -= mat.m32;   m33 -= mat.m33;   m34 -= mat.m34;
    }

    /**
    * Translates the position
    * @param x/y/z The components to translate along
    */
    void Translate(float x, float y, float z)   
    { 
        m14 += x;   
        m24 += y;  
        m34 += z;   
    }

    /**
    * Translates the position
    * @param vec The vector to translate along
    */
    void Translate(const Float3& vec)             
    { 
        m14 += vec.x; 
        m24 += vec.y; 
        m34 += vec.z; 
    }

    /**
    * Scales the matrix
    * @param x/y/z The components to scale by
    */
    void Scale(float x, float y, float z)       
    { 
        m11 *= x;   
        m22 *= y;  
        m33 *= z;  
    }

    /**
    * Scales the matrix
    * @param vec The vector to scale by
    */
    void Scale(const Float3& vec)                      
    { 
        m11 *= vec.x; 
        m22 *= vec.y; 
        m33 *= vec.z; 
    }

    /**
    * Scales the matrix uniformly
    * @param value The amount to scale the matrix by
    */
    void Scale(float value)                         
    { 
        m11 *= value;   
        m22 *= value;   
        m33 *= value;  
    }

    /**
    * Rotates around the global X axis
    * @param radians The angle in radians to rotate
    */
    void RotateX(float radians)
    {
        Matrix mat;
        float c = cos(radians);
        float s = sin(radians);
        mat.m22 = c;  
        mat.m23 = s;  
        mat.m32 = -s; 
        mat.m33 = c;  
        (*this) *= mat;
    }

    /**
    * Rotates around the global Y axis
    * @param radians The angle in radians to rotate
    */
    void RotateY(float radians)
    { 
        Matrix mat;
        float c = cos(radians);
        float s = sin(radians);
        mat.m11 = c;  
        mat.m13 = -s; 
        mat.m31 = s;  
        mat.m33 = c; 
        (*this) *= mat;
    }

    /**
    * Rotates around the global Z axis
    * @param radians The angle in radians to rotate
    */
    void RotateZ(float radians)
    { 
        Matrix mat;
        float c = cos(radians);
        float s = sin(radians);
        mat.m11 = c;  
        mat.m12 = s; 
        mat.m21 = -s; 
        mat.m22 = c; 
        (*this) *= mat;
    }

    /**
    * Creates an arbitrary rotation matrix and rotates around it
    * @param vec The vector to rotate around
    * @param radians The angle in radians to rotate
    */
    void RotateArbitrary(const Float3& vec, float radians)
    {
        Matrix mat;
        float c = cos(radians);
        float s = sin(radians);
        float cinv = 1.0f-cos(radians);
        mat.m11 = (cinv*(vec.x*vec.x)) + c;
        mat.m12 = (cinv*(vec.x*vec.y)) + (s*vec.z);
        mat.m13 = (cinv*(vec.x*vec.z)) - (s*vec.y);
        mat.m21 = (cinv*(vec.x*vec.y)) - (s*vec.z);
        mat.m22 = (cinv*(vec.y*vec.y)) + c;
        mat.m23 = (cinv*(vec.y*vec.z)) + (s*vec.x);
        mat.m31 = (cinv*(vec.x*vec.y)) + (s*vec.y);
        mat.m32 = (cinv*(vec.y*vec.z)) - (s*vec.x);
        mat.m33 = (cinv*(vec.z*vec.z)) + c;
        (*this) *= mat;
    }

    /**
    * Scales around the local origin
    * @param x/y/z The components to scale by
    */
    void ScaleLocal(float x, float y, float z)      
    {
        Float3 pos = Position();
        m11 = ((m11-pos.x)*x)+pos.x;    
        m22 = ((m22-pos.y)*y)+pos.y;    
        m33 = ((m33-pos.z)*z)+pos.z; 
    }

    /**
    * Scales around local origin
    * @param vec The vector to scale by
    */
    void ScaleLocal(const Float3& vec) 
    {
        ScaleLocal(vec.x, vec.y, vec.z); 
    }

    /**
    * Scales around local origin uniformly
    * @param value The amount to scale by
    */
    void ScaleLocal(float value)   
    { 
        ScaleLocal(value, value, value); 
    }

    /**
    * Rotates around the local X axis
    * @param radians The angle in radians to rotate
    */
    void RotateXLocal(float radians)
    {
        Matrix mat;
        Float3 savedPosition = Position();
        float c = cos(radians);
        float s = sin(radians);
        mat.m22 = c;  
        mat.m23 = s;  
        mat.m32 = -s; 
        mat.m33 = c; 
        SetPosition(0.0f, 0.0f, 0.0f);
        (*this) *= mat;
        Translate(savedPosition);
    }

    /**
    * Rotates around the local Y axis
    * @param radians The angle in radians to rotate
    */
    void RotateYLocal(float radians)
    { 
        Matrix mat;
        Float3 savedPosition = Position();
        float c = cos(radians);
        float s = sin(radians);
        mat.m11 = c;  
        mat.m13 = -s; 
        mat.m31 = s;  
        mat.m33 = c; 
        SetPosition(0.0f, 0.0f, 0.0f);
        (*this) *= mat;
        Translate(savedPosition);
    }

    /**
    * Rotates around the local Z axis
    * @param radians The angle in radians to rotate
    */
    void RotateZLocal(float radians)
    { 
        Matrix mat;
        Float3 savedPosition = Position();
        float c = cos(radians);
        float s = sin(radians);
        mat.m11 = c;  
        mat.m12 = s; 
        mat.m21 = -s; 
        mat.m22 = c; 
        SetPosition(0.0f, 0.0f, 0.0f);
        (*this) *= mat;
        Translate(savedPosition);
    }

    /**
    * Creates an arbitrary rotation matrix and rotates locally around it
    * @param vec The vector to rotate around
    * @param radians The angle in radians to rotate
    */
    void RotateArbitraryLocal(const Float3& vec, float radians)
    {
        Matrix mat;
        Float3 savedPosition = Position();
        float c = cos(radians);
        float s = sin(radians);
        float cinv = 1.0f-(cos(radians));
        mat.m11 = (cinv*(vec.x*vec.x)) + c;
        mat.m12 = (cinv*(vec.x*vec.y)) + (s*vec.z);
        mat.m13 = (cinv*(vec.x*vec.z)) - (s*vec.y);
        mat.m21 = (cinv*(vec.x*vec.y)) - (s*vec.z);
        mat.m22 = (cinv*(vec.y*vec.y)) + c;
        mat.m23 = (cinv*(vec.y*vec.z)) + (s*vec.x);
        mat.m31 = (cinv*(vec.x*vec.y)) + (s*vec.y);
        mat.m32 = (cinv*(vec.y*vec.z)) - (s*vec.x);
        mat.m33 = (cinv*(vec.z*vec.z)) + c;
        SetPosition(0.0f, 0.0f, 0.0f);
        (*this) *= mat;
        Translate(savedPosition);
    }

    /**
    * Creates a rotation matrix around the global X axis
    * @param radians The angle in radians to rotate
    * @return The rotation matrix
    */
    static Matrix CreateRotateX(float radians)
    {
        Matrix mat;
        float c = cos(radians);
        float s = sin(radians);
        mat.m22 = c;  
        mat.m23 = s;  
        mat.m32 = -s;
        mat.m33 = c;  
        return mat;
    }

    /**
    * Creates a rotation matrix around the global Y axis
    * @param radians The angle in radians to rotate
    * @return The rotation matrix
    */
    static Matrix CreateRotateY(float radians)
    { 
        Matrix mat;
        float c = cos(radians);
        float s = sin(radians);
        mat.m11 = c; 
        mat.m13 = -s; 
        mat.m31 = s; 
        mat.m33 = c; 
        return mat;
    }

    /**
    * Creates a rotation matrix around the global Z axis
    * @param radians The angle in radians to rotate
    * @return The rotation matrix
    */
    static Matrix CreateRotateZ(float radians)
    { 
        Matrix mat;
        float c = cos(radians);
        float s = sin(radians);
        mat.m11 = c;  
        mat.m12 = s; 
        mat.m21 = -s; 
        mat.m22 = c; 
        return mat;
    }

    /**
    * Creates a arbitrary rotation matrix
    * @param vec The vector to rotate around
    * @param radians The angle in radians to rotate
    * @return The arbitrary rotation matrix
    */
    static Matrix CreateRotateArbitrary(const Float3& vec, float radians)
    {
        Matrix mat;
        float c = cos(radians);
        float s = sin(radians);
        float cinv = 1.0f-c;
        mat.m11 = (cinv*(vec.x*vec.x)) + c;
        mat.m12 = (cinv*(vec.x*vec.y)) + (s*vec.z);
        mat.m13 = (cinv*(vec.x*vec.z)) - (s*vec.y);
        mat.m21 = (cinv*(vec.x*vec.y)) - (s*vec.z);
        mat.m22 = (cinv*(vec.y*vec.y)) + c;
        mat.m23 = (cinv*(vec.y*vec.z)) + (s*vec.x);
        mat.m31 = (cinv*(vec.x*vec.y)) + (s*vec.y);
        mat.m32 = (cinv*(vec.y*vec.z)) - (s*vec.x);
        mat.m33 = (cinv*(vec.z*vec.z)) + c;
        return mat;
    }

    /**
    * Allows output of the matrix to a standard stream
    * @param stream The stream to output in
    * @param mat The matrix to output
    * @return the stream to allow for chaining
    */
    friend std::ostream& operator<<(std::ostream& stream, const Matrix& mat)
    {
        stream << mat.m11 << " " << mat.m12 << 
            " " << mat.m13 << " " << mat.m14 << std::endl;

        stream << mat.m21 << " " << mat.m22 << 
            " " << mat.m23 << " " << mat.m24 << std::endl;

        stream << mat.m31 << " " << mat.m32 << 
            " " << mat.m33 << " " << mat.m34 << std::endl;

        return stream;
    }
};