/****************************************************************
* Kara Jensen (mail@karajensen.com) 
* Vector Class
*****************************************************************/
#pragma once

#include <cmath>

template<typename T>
class Vector3
{
public:

    T x,y,z;

    /**
    * Constructor
    * @param the components of the Vector3
    */
    Vector3(T X = T(0), T Y = T(0), T Z = T(0)) : 
        x(X), y(Y), z(Z) 
    {
    };

    /**
    * Testing equality for Vector3
    */
    bool operator==(const Vector3<T>& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    /**
    * Testing inequality for Vector3
    */
    bool operator!=(const Vector3& v) const
    {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }
    
    /**
    * Overloading negative sign to invert Vector3
    */
    Vector3<T> operator-() const
    {
        return Vector3<T>(-x,-y,-z);
    }
    
    /**
    * Allows for Vector3 * Scalar
    */
    Vector3<T> operator*(T a) const
    {
        return Vector3<T>(a*x, a*y, a*z); 
    }

    /**
    * Allows for Vector3 *= Scalar
    */
    void operator*=(T a)
    {
        x = x*a;
        y = y*a;
        z = z*a;
    }

    /**
    * Allows for Vector3 / Scalar
    */
    Vector3<T> operator/(T a) const
    {
        return Vector3<T>(x/a, y/a, z/a); 
    }

    /**
    * Allows for Vector3 /= Scalar
    */
    void operator/=(T a)
    {
        x = x/a;
        y = y/a;
        z = z/a;
    }

    /**
    * Vector3 addition
    */
    Vector3<T> operator+(const Vector3<T> & v) const
    {
        return Vector3<T>(x + v.x, y + v.y, z + v.z);
    }
    void operator+=(const Vector3<T> & v)
    {
        x = x + v.x;
        y = y + v.y;
        z = z + v.z;
    }

    /**
    * Vector3 subtraction
    */
    Vector3<T> operator-(const Vector3<T>& v) const
    {
        return Vector3<T>(x - v.x, y - v.y, z - v.z);
    }
    void operator-=(const Vector3<T>& v)
    {
        x = x - v.x;
        y = y - v.y;
        z = z - v.z;
    }

    /**
    * Vector3 Cross Product
    * @param the Vector3 to be crossed with 
    */
    Vector3<T> Cross(const Vector3<T>& v) const
    {
        return Vector3((y*v.z)-(z*v.y),(z*v.x)-(x*v.z),(x*v.y)-(y*v.x));
    }

    /**
    * Vector3 Dot Product
    * @param the Vector3 to be dotted with 
    */
    float Dot(const Vector3<T>& v) const
    {
        return static_cast<float>((v.x*x)+(v.y*y)+(v.z*z));
    }

    /**
    * Tests whether two Vector3s are perpendicular
    * @param the Vector3 to be tested against
    * @return whether the Vector3s are perpendicular
    */
    bool IsPerpendicular(const Vector3<T>& v) const
    {
        return (Dot(v) == T(0));
    }

    /**
    * Tests whether two Vector3s are parallel
    * @param the Vector3 to be tested against
    * @return whether the Vector3s are parallel
    */
    bool IsParallel(const Vector3<T>& v) const
    {
        float dot = Dot(v);
        return (dot == T(1)) || (dot == T(-1));
    }

    /**
    * Gets the angle between two Vector3 in radians
    * @return the angle in radians
    */
    float Angle(const Vector3<T>& v) const
    {
        float dot = Dot(v);
        return acos(dot/(v.Length()*Length()));
    }

    /**
    * @return the squared length of the Vector3
    */
    float SquaredLength() const
    {
        return static_cast<float>((x*x)+(y*y)+(z*z));
    }

    /**
    * @return the length of the Vector3
    */
    float Length() const
    {
        return static_cast<float>(std::sqrt(
            static_cast<double>((x*x)+(y*y)+(z*z))));
    }

    /**
    * Sets the Vector3
    * @param the Vector3 to set to
    */
    void Set(const Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    /**
    * Sets the Vector3
    * @param the components of the Vector3 to set
    */
    void Set(T X, T Y, T Z)
    {
        x = X;
        y = Y;
        z = Z;
    }

    /**
    * Normlizes the Vector3
    */
    void Normalize()
    {
        float length = Length();
        x = x/length;
        y = y/length;
        z = z/length;
    }

    /**
    * @return the normalized Vector3 without changing the actual Vector3
    */
    Vector3<T> GetNormalized() const
    {
        float length = Length();
        return Vector3(x/length, y/length, z/length);
    }

    /**
    * Sets the Vector3 to the zero Vector3
    */
    void SetToZero()
    {
        x = T(0);
        y = T(0);
        z = T(0);
    }
};

typedef Vector3<float> Float3;