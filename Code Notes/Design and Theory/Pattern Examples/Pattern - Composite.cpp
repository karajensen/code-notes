////////////////////////////////////////////////////////////////////////////////////////////////////////
//COMPOSITE PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Structural
USE: Class with methods that treat individual or multiple or composited objects the same
     Eg(1) Moving a mesh involves moving components verts/edges/polys
     Eg(2) Moving a square is same as moving an entire scene
     Eg(3) Pokemonbox class manages all pokemon
-------------------------------------------------------------------------------------------*/

class Component
{
public:
    Component component;
    void draw(); //draw stuff
};

class Composite
{
public:
    
    //array of components
    vector<Component> components;

    //every method the component class has, composite class has a matching method
    void draw() 
    {
       //Iterate over the components
       for(unsigned int i = 0; i < components.size(); ++i) 
          components[i].draw();   //Call components draw method
    }
};