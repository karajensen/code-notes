/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com) 2012
* Vector Class
*****************************************************************/
#pragma once

#include <cmath>

class FLOAT3
{
public:

    float x,y,z; ///< Vector components

    /**
    * Constructor
    * @param the components of the vector
    */
    FLOAT3(): x(0.0f), y(0.0f), z(0.0f) {};
    FLOAT3(float X, float Y, float Z): x(X), y(Y), z(Z) {};


    /**
    * Testing equality/inequality for vector
    */
    bool operator==(const FLOAT3& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }
    bool operator!=(const FLOAT3& v) const
    {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }
    
    /**
    * Overloading negative sign to invert vector
    */
    FLOAT3 operator-() const
    {
        return FLOAT3(-x,-y,-z);
    }
    
    /**
    * Allows for Vector * Scalar
    */
    FLOAT3 operator*(float a) const
    {
        return FLOAT3(a*x, a*y, a*z); 
    }

    /**
    * Allows for Vector *= Scalar
    */
    void operator*=(float a)
    {
        x = x*a;
        y = y*a;
        z = z*a;
    }

    /**
    * Allows for Vector / Scalar
    */
    FLOAT3 operator/(float a) const
    {
        return FLOAT3(x/a, y/a, z/a); 
    }

    /**
    * Allows for Vector /= Scalar
    */
    void operator/=(float a)
    {
        x = x/a;
        y = y/a;
        z = z/a;
    }

    /**
    * Vector addition
    */
    FLOAT3 operator+(const FLOAT3 & v) const
    {
        return FLOAT3((x + v.x),(y + v.y),(z + v.z));
    }
    void operator+=(const FLOAT3 & v)
    {
        x = x + v.x;
        y = y + v.y;
        z = z + v.z;
    }

    /**
    * Vector subtraction
    */
    FLOAT3 operator-(const FLOAT3& v) const
    {
        return FLOAT3((x - v.x),(y - v.y),(z - v.z));
    }
    void operator-=(const FLOAT3& v)
    {
        x = x - v.x;
        y = y - v.y;
        z = z - v.z;
    }

    /**
    * Vector Cross Product
    * @param the vector to be crossed with 
    */
    FLOAT3 Cross(const FLOAT3& v) const
    {
        return FLOAT3((y*v.z)-(z*v.y),(z*v.x)-(x*v.z),(x*v.y)-(y*v.x));
    }

    /**
    * Vector Dot Product
    * @param the vector to be dotted with 
    */
    float Dot(const FLOAT3& v) const
    {
        return ((v.x*x)+(v.y*y)+(v.z*z));
    }

    /**
    * Tests whether two vectors are perpendicular
    * @param the vector to be tested against
    * @return whether the vectors are perpendicular
    */
    bool IsPerpendicular(const FLOAT3& v) const
    {
        return (Dot(v) == 0.0f);
    }

    /**
    * Tests whether two vectors are parallel
    * @param the vector to be tested against
    * @return whether the vectors are parallel
    */
    bool IsParallel(const FLOAT3 & v) const
    {
        float dot = Dot(v);
        return (dot == 1.0f) || (dot == -1.0f);
    }

    /**
    * Gets the angle between two vectors in radians
    * @return the angle in radians
    */
    float Angle(const FLOAT3& v) const
    {
        float dot = Dot(v);
        return acos(dot/(v.Length()*Length()));
    }

    /**
    * Gets the angle between two vectors in radians from the positive X axis
    * @return the angle in radians between 0->2PI
    */
    float AngleX() const
    {
        float angle = 0.0f;
        if(y < 0.0f)
        {
            angle = Angle(FLOAT3(1.0f,0.0f,0.0f));
            if(angle < 0.0f)
            { 
                angle *= -1.0f; 
            }
            angle += 3.14159265f; //180deg
        }
        else
        {
            angle = Angle(FLOAT3(-1.0f,0.0f,0.0f));
            if(angle < 0.0f)
            { 
                angle *= -1.0f; 
            }
        }
        return angle;
    }

    /**
    * @return the squared length of the vector
    */
    float SquaredLength() const
    {
        return ((x*x)+(y*y)+(z*z));
    }

    /**
    * @return the Manhattan distance of the vector
    */
    float ManhattanDistance() const
    {
        float X = x;    if(X < 0.0f){ X *= -1.0f; }
        float Y = y;    if(Y < 0.0f){ Y *= -1.0f; }
        float Z = z;    if(Z < 0.0f){ Z *= -1.0f; }
        return X+Y+Z;
    }

    /**
    * @return the length of the vector
    */
    float Length() const
    {
        return std::sqrt((x*x)+(y*y)+(z*z));
    }

    /**
    * Sets the vector
    * @param the vector to set to
    */
    void Set(const FLOAT3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    /**
    * Sets the vector
    * @param the components of the vector to set
    */
    void Set(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
    }

    /**
    * @return whether or not the vector is normalized
    */
    bool IsNormalized() const
    {
        return abs(1.0f-((x*x)+(y*y)+(z*z))) < 0.05f; // rounding error magin
    }

    /**
    * Normlizes the vector
    */
    void Normalize()
    {
        float length = this->Length();
        x = x/length;
        y = y/length;
        z = z/length;
    }

    /**
    * @return the normalized vector without changing the actual vector
    */
    FLOAT3 GetNormalized() const
    {
        float length = this->Length();
        return FLOAT3(x/length, y/length, z/length);
    }

    /**
    * Sets the vector to the zero vector
    */
    void SetToZero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    /**
    * Rounds the vector to the nearest whole number using decimal rounding
    */
    void MathRound()
    {
        if(x < 0.0f)  { x = static_cast<float>(static_cast<int>(x - 0.5f)); }
        else          { x = static_cast<float>(static_cast<int>(x + 0.5f)); }
    
        if(y < 0.0f)  { y = static_cast<float>(static_cast<int>(y - 0.5f)); }
        else          { y = static_cast<float>(static_cast<int>(y + 0.5f)); }

        if(z < 0.0f)  { z = static_cast<float>(static_cast<int>(z - 0.5f)); }
        else          { z = static_cast<float>(static_cast<int>(z + 0.5f)); }
    }

    /**
    * @return the distance between two vectors
    */
    float GetDistance(const FLOAT3& v) const
    {
        return (v-(*this)).Length();
    }


};
