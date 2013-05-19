////////////////////////////////////////////////////////////////////////////////////////////////////////
//DECORATOR PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Structural
USE: Given a set of classes, allows them to be mixed and matched without each combination
     having been written in advance as a subclass
-------------------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

//----------------------------------------------------------------
//BASE OBJECT
//----------------------------------------------------------------
class BaseObject 
{
public:
    virtual ~BaseObject(){}
    virtual void Draw() = 0;
};

//--------------------------------------------------------
//DERIVED OBJECT/DERIVED OBJECT DECORATOR
//--------------------------------------------------------
//Derived Object and it's decorator inherit the base object
class DerivedObject: public BaseObject 
{
public:
    virtual ~DerivedObject() { cout << "DerivedObject Destructor" << endl; }
    virtual void Draw()         { cout << "D"; }
};

class DecoraterObject: public BaseObject
{
private:
    BaseObject* p_inner;
public:
    DecoraterObject(BaseObject* inner) { p_inner = inner; }
    virtual ~DecoraterObject()           { delete p_inner; }
    virtual void Draw()                   { p_inner->Draw(); }
};
//----------------------------------------------------------------
//DERIVED OBJECT ADD-ONS
//----------------------------------------------------------------
class X: public DecoraterObject
{
public:
    X(BaseObject* inner): DecoraterObject(inner){}
    virtual ~X() { cout << "X destructor" << endl; }
    virtual void Draw() { DecoraterObject::Draw(); cout << 'X'; }
};

class Y: public DecoraterObject 
{
public:
    Y(BaseObject* inner): DecoraterObject(inner){}
    virtual ~Y() { cout << "Y destructor" << endl; }
    virtual void Draw() { DecoraterObject::Draw(); cout << 'Y'; }
};

class Z: public DecoraterObject
{
public:
    Z(BaseObject* inner): DecoraterObject(inner){}
    virtual ~Z() { cout << "Z destructor" << endl; }
    virtual void Draw() { DecoraterObject::Draw(); cout << 'Z'; }
};

//----------------------------------------------------------------
//MAIN
//----------------------------------------------------------------
int main() 
{ 
    //CREATING COMBINATIONS OF OBJECTS
    //Memory is allocated for each pointer before any constructors are called
    //Contructors are called from right to left, returning a pointer to the new object
    //Each contructor takes the next pointer returned and stores it in it's own decorator object as a base class pointer
    //Creation order can be variable
    BaseObject* x = new X(new DerivedObject);
    BaseObject* xy = new Y(new X(new DerivedObject));
    BaseObject* xyz = new X(new Z(new Y(new DerivedObject)));

    //CALL OBJECT METHODS
    //Will call in a chain all the draw methods for all object add-ons in order of right->left creation
    x->Draw();
    cout << endl;
    xy->Draw();
    cout << endl;
    xyz->Draw(); 
    cout << endl << endl;

    //DELETE OBJECTS
    delete x;
    cout << endl;
    delete xy;
    cout << endl;
    delete xyz;
    cout << endl;

  cin.get();
}