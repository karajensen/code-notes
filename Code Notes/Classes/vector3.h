////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - vector3.h
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cmath>
#include <ostream>

/**
* Template class for creating vectors in 2D/3D space
*/
template<typename T> class Vector3
{
public:

    T x,y,z; ///< Vector components

    /**
    * Constructor
    * @param x/y/z The components of the Vector3
    */
    explicit Vector3(T X = T(0), T Y = T(0), T Z = T(0)) : 
        x(X), 
        y(Y),
        z(Z) 
    {
    };

    /**
    * Testing equality for two vectors
    * @param vec The vector to test equality against
    * @return Whether the two vectors are equal
    */
    bool operator==(const Vector3<T>& vec) const
    {
        return x == vec.x && y == vec.y && z == vec.z;
    }

    /**
    * Testing inequality for two vectors
    * @param vec The vector to test inequality against
    * @return Whether the two vectors are inequal
    */
    bool operator!=(const Vector3& vec) const
    {
        return x != vec.x || y != vec.y || z != vec.z;
    }
    
    /**
    * Inverts all components of the vector
    * @return A new vector from the vector inverted
    */
    Vector3<T> operator-() const
    {
        return Vector3<T>(-x,-y,-z);
    }
    
    /**
    * Multiplication against a scalar
    * @param value Scalar to multiply against
    * @return A new vector from the vector multiplied by scalar
    */
    Vector3<T> operator*(T value) const
    {
        return Vector3<T>(value*x, value*y, value*z); 
    }

    /**
    * Multiplication against a scalar
    * @param value Scalar to multiply against
    */
    void operator*=(T value)
    {
        x = x*value;
        y = y*value;
        z = z*value;
    }

    /**
    * Division against a scalar
    * @param value Scalar to divide against
    * @return A new vector from the vector divided by scalar
    */
    Vector3<T> operator/(T value) const
    {
        return Vector3<T>(x/value, y/value, z/value); 
    }

    /**
    * Division against a scalar
    * @param value Scalar to divide against
    */
    void operator/=(T value)
    {
        x = x/value;
        y = y/value;
        z = z/value;
    }

    /**
    * Vector3 addition with another vector
    * @param vec The vector to add
    * @return A new vector from the two added vectors
    */
    Vector3<T> operator+(const Vector3<T> & vec) const
    {
        return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);
    }
    
    /**
    * Vector3 addition with another vector
    * @param vec The vector to add
    */    
    void operator+=(const Vector3<T> & vec)
    {
        x = x + vec.x;
        y = y + vec.y;
        z = z + vec.z;
    }

    /**
    * Vector3 subtraction with another vector
    * @param vec The vector to subtract
    * @return A new vector from the two subtracted vectors
    */
    Vector3<T> operator-(const Vector3<T>& vec) const
    {
        return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);
    }
    
    /**
    * Vector3 subtraction with another vector
    * @param vec The vector to subtract
    */    
    void operator-=(const Vector3<T>& vec)
    {
        x = x - vec.x;
        y = y - vec.y;
        z = z - vec.z;
    }

    /**
    * Cross Product
    * @param vec The vector to be crossed with 
    * @return The vector perpendicular to the given vectors
    */
    Vector3<T> Cross(const Vector3<T>& vec) const
    {
        return Vector3((y*vec.z)-(z*vec.y),(z*vec.x)-(x*vec.z),(x*vec.y)-(y*vec.x));
    } 

    /**
    * Vector Dot Product
    * @param vec The vector to be dotted with 
    * @return The dot product between the vectors
    */
    float Dot(const Vector3<T>& vec) const
    {
        return static_cast<float>((vec.x*x)+(vec.y*y)+(vec.z*z));
    }

    /**
    * Tests whether two vectors are perpendicular
    * @param vec The vector to be tested against
    * @return Whether the vectors are perpendicular
    */
    bool IsPerpendicular(const Vector3<T>& vec) const
    {
        return Dot(vec) == T(0);
    }

    /**
    * Gets the angle between two vectors in radians
    * @param vec The vector to get the angle between
    * @return The angle in radians
    */
    float Angle(const Vector3<T>& vec) const
    {
        float dot = Dot(vec);
        return acos(dot/(vec.Length()*Length()));
    }

    /**
    * @return The squared length of the vector
    */
    float SquaredLength() const
    {
        return static_cast<float>((x*x)+(y*y)+(z*z));
    }

    /**
    * @return The length of the vector
    */
    float Length() const
    {
        return static_cast<float>(std::sqrt(
            static_cast<double>((x*x)+(y*y)+(z*z))));
    }

    /**
    * Sets the vector from another vector
    * @param vec The vector to use when setting
    */
    void Set(const Vector3& vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    /**
    * Sets the vector from the given components
    * @param x/y/z The components to use when setting
    */
    void Set(T X, T Y, T Z)
    {
        x = X;
        y = Y;
        z = Z;
    }

    /**
    * Normlizes into a unit vector
    */
    void Normalize()
    {
        float length = Length();
        x = x/length;
        y = y/length;
        z = z/length;
    }

    /**
    * @return A copy of the vector normalized
    */
    Vector3<T> GetNormalized() const
    {
        float length = Length();
        return Vector3(x/length, y/length, z/length);
    }

    /**
    * Sets all components to zero
    */
    void SetToZero()
    {
        x = T(0);
        y = T(0);
        z = T(0);
    }

    /**
    * Allows output of the vector to a standard stream
    * @param stream The stream to output in
    * @param vec The vector to output
    * @return the stream to allow for chaining
    */
    friend std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
    {
        stream << vec.x << ", " << vec.y << ", " << vec.z;
        return stream;
    }
};

typedef Vector3<float> Float3;