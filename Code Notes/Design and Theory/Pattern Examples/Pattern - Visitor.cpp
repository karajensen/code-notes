////////////////////////////////////////////////////////////////////////////////////////////////////////
//VISITOR PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioural
USE: Seperates the objects from its methods 
     Allows creating new methods without changing the object class
     Good if derived classes have extra functionality dependent on their type
     Calls custom methods in derived classes using a base class *
-------------------------------------------------------------------------------------------*/

//VISITOR
class Object1;
class Object2;
class Visitor
{
  public:
    //need an overloaded function for each derived object type
    virtual void Visit(Object1* o) = 0;
    virtual void Visit(Object2* o) = 0;
};
class MakeGreen : public Visitor
{
    virtual void Visit(Object1* o){ o->Object1Method(); }
    virtual void Visit(Object2* o){ o->Object2Method(); }
};
class RemoveHands : public Visitor
{
    virtual void Visit(Object1* o){ /*do something*/ }
    virtual void Visit(Object2* o){ /*do something else*/ }
};


//OBJECTS
class BaseObject
{
public:
    virtual void Accept(Visitor* v)=0;
};

class Object1: public BaseObject
{
public:
    void Object1Method();
    virtual void Accept(Visitor* v){ v->Visit(this); } //passes derived type to visitor
};

class Object2: public BaseObject
{
public:
    void Object2Method();
    virtual void Accept(Visitor* v){ v->Visit(this); } //passes derived type to visitor
};

//USAGE
int main()
{
    BaseObject* obj1 = new Object1();
    BaseObject* obj2 = new Object2();

    //create a series of different methods that can work on the objects
    Visitor* makegreen = new MakeGreen();
    Visitor* removehands = new RemoveHands();

    //Accept function on base* calls the derived function
    obj1->Accept(makegreen);
    obj2->Accept(removehands);
}



