/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com) 
* Basic color class
*****************************************************************/
#pragma once

class Color
{
public:

    union
    {
        unsigned int color;
        struct
        {
            unsigned char r, g, b, a;
        };
    };

    /**
    * Default Constructor sets as white
    */
    Color()
    { 
        Set(255,255,255,255); 
    }

    /**
    * Constructor 
    * @param color coponents as integers from 0->255
    */
    Color(int R, int G, int B, int A)
    { 
        Set(R,G,B,A); 
    }

    /**
    * Constructor 
    * @param color as an unsigned integer in the form of 0xRRGGBBAA
    */
    Color(unsigned int c)
    { 
        Set(c); 
    }

    /**
    * Sets the colour as a whole
    * @param color coponents as integers from 0->255
    */
    void Set(int R, int G, int B, int A) 
    {
        r = R; 
        g = G; 
        b = B; 
        a = A; 
    }

    /**
    * Sets the colour as a whole
    * @param color as an unsigned integer in the form of 0xRRGGBBAA
    */
    void Set(unsigned int c)
    { 
        color = c; 
    }

    /**
    * Sets the colour as a whole
    * @param another color object
    */
    void Set(const Color& c){ color = c.color; }

    /**
    * Get the color component as a float 
    */
    float rFloat() const { return static_cast<float>(r)/255.0f; }
    float gFloat() const { return static_cast<float>(g)/255.0f; }
    float bFloat() const { return static_cast<float>(b)/255.0f; }
    float aFloat() const { return static_cast<float>(a)/255.0f; }

    /**
    * Set the color component as a float 
    */
    float rFloat(float R){ r = static_cast<unsigned char>(ClampColor(R)*255.0f); }
    float gFloat(float G){ g = static_cast<unsigned char>(ClampColor(G)*255.0f); }
    float bFloat(float B){ b = static_cast<unsigned char>(ClampColor(B)*255.0f); }
    float aFloat(float A){ a = static_cast<unsigned char>(ClampColor(A)*255.0f); }

    /**
    * Clips the bounds of the color to 0.0->1.0
    * @param c the colour component to be passed in
    * @return the clipped color component
    */
    float ClampColor(float c)
    {
        if(c < 0.0f)
        {
            c = 0.0f;
        }
        if(c > 1.0f)
        {
            c = 1.0f;
        }
        return c;
    }

    /**
    * Add to a particular colour component
    * Prevents going beyond the bounds of 0->255 and 0.0->1.0
    * @param amount the amount to add to the component
    */
    void AddR(float amount)
    {
         AddToComponent(amount,&r);
    }
    void AddG(float amount)
    {
        AddToComponent(amount,&g);
    }
    void AddB(float amount)
    {
        AddToComponent(amount,&b);
    }
    void AddA(float amount)
    {
        AddToComponent(amount,&a);
    }

    /**
    * Adds an amount and prevents going beyond the bounds of 0->255 and 0.0->1.0
    * @param component the color component to add to
    * @param amount the amount to add to the component
    */
    void AddToComponent(float amount, unsigned char* component)
    {
        float newamount = static_cast<float>(*component)+amount;
        if(newamount < 0)
        { 
            *component = 0; 
        }
        else if(newamount > 255)
        { 
            *component = 255; 
        }
        else
        { 
            *component = char(newamount); 
        }
    }

    /**
    * Tests whether the alpha component is less than a specific amount
    * @param amount an amount to test between 0.0->1.0
    * @param whether or not the alpha is less than the amount
    */
    bool IsAlphaLessThan(float amount) const
    {
        if(aFloat() < amount)
        {
            return true;
        }
        return false;
    }

    /**
    * Tests whether the alpha component is less than a specific amount
    * @param amount an amount to test between 0->255
    * @param whether or not the alpha is less than the amount
    */
    bool IsAlphaLessThan(char amount) const
    {
        if(a < amount)
        {
            return true;
        }
        return false;
    }

    /**
    * Tests equality between colors
    */
    bool operator==(Color & c) const
    {
        if(c.color == color)
        {
            return true;
        }
        return false;
    }

    /**
    * Tests inequality between colors
    */
    bool operator!=(Color & c) const
    {
        if(c.color != color)
        {
            return true;
        }
        return false;
    }

    /**
    * Tests equality between colors
    */
    void ChangeBrightness(float amount)
    {
        r = static_cast<unsigned char>(ClampColor(r*amount)*255.0f);
        g = static_cast<unsigned char>(ClampColor(g*amount)*255.0f);
        b = static_cast<unsigned char>(ClampColor(b*amount)*255.0f);
        a = static_cast<unsigned char>(ClampColor(a*amount)*255.0f);
    }

};
