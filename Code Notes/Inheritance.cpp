//////////////////////////////////////////////////////////////////////////////
//PUBLIC INHERITANCE
//////////////////////////////////////////////////////////////////////////////

class Base
{
public: 
    Base(int x); //constructors can't be virtual
    virtual ~Base(); //put as virtual only if want to derive from it
    virtual ~Base()=0; //used if needing abstract class but all methods implemented
    virtual void MyMethod()=0; //pure virtual method, no objects of Base can be created
};

class Derived : public Base //compilier assumes private if public not specified
{
public: 
    Derived(int x, int y);
    virtual void MyMethod() override; //virtual/override not required but important
};

//CONSTRUCTORS
//Base object is created first in initialisation list
//Default Base constructor used if not specified
Derived::Derived(int x, int y) : Base(x) {}

//DESTRUCTORS
//Object destroyed in opposite direction of creation, base->derived
Derived::~Derived(){}

//DERIVED CLASS METHOD
Derived::MyMethod()
{
    Base::MyMethod(); //Calling Base method
};

//////////////////////////////////////////////////////////////////////////////
//CONTAINMENT
//////////////////////////////////////////////////////////////////////////////

class Containment
{
private:
    MyClass m_myClassObject;
}

//////////////////////////////////////////////////////////////////////////////
//PRIVATE INHERITANCE
//////////////////////////////////////////////////////////////////////////////
//Same as containment but uses a 'hidden' object of base 
//Derived object cannot be cast to its base class
//Base class members become derived class private members

class Base
{
public:
    virtual ~Base();
    virtual void MyMethod();
};

class Derived : private Base 
{
public:
    virtual void MyMethod() override;
};

//Can be called inside derived
void Derived::MyMethod()
{
    Base::MyMethod(); 
}

//Can't be called by derived object
derived->MyMethod();
derived->Base::MyMethod()

//////////////////////////////////////////////////////////////////////////////
//PROTECTED INHERITANCE
//////////////////////////////////////////////////////////////////////////////
//Same as containment but uses a 'hidden' object of base 
//Derived object cannot be cast to its base class
//Base class members become derived class protected members

class Base
{
protected:
    virtual void MyMethod(); 
};
class Derived : protected Base
{
public:
    virtual void MyMethod() override;
};

//Can be called inside derived
void Derived::MyMethod()
{
    Base::MyMethod(); 
}

//Can't be called by derived object
derived->MyMethod();
derived->Base::MyMethod()

//////////////////////////////////////////////////////////////////////////////
//VIRTUAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

class Base
{
public:
    virtual void MyVirtual();
    void MyMethod();
};
class Derived : public Base
{
public:
    virtual void MyVirtual() override;
    void MyMethod();
    void MyDerived();
};

//OBJECTS
//Calls function based on object type
derived.MyMethod()     //uses Derived::MyMethod()
base.MyMethod()        //uses Base::MyMethod()
derived.MyVirtual()    //uses Derived::MyVirtual()
base.MyVirtual()       //uses Base::MyVirtual()

//POINTER/REFERENCES
//Virtual: Calls function based on underlying object type
//Non-virtual: Calls function based on ref/pointer type
Derived* deriPtr = &derivedObject;
Base* basePtr = &derivedObject;

deriPtr->MyVirtual();        //uses Derived::MyVirtual()
deriPtr->MyMethod();         //uses Derived::MyVirtual()
deriPtr->MyDerived();        //uses Derived::MyDerived()
deriPtr->Base::MyVirtual();  //uses Base::MyVirtual()

basePtr->MyVirtual();        //uses Derived::MyVirtual()
basePtr->MyMethod();         //uses Base::MyMethod()
basePtr->Base::MyVirtual();  //uses Base::MyVirtual()
basePtr->MyDerived();        //ERROR!

//ARRAYS AND POLYMORPHIM
//Avoid as pointer arithmatic on base class arrays of derived objects
//pointer arithmatic will use sizeof(Base) not sizeof(Derived)
Base* myArray = new Derived[2];
myArray[1] = *(myArray+1)
delete [] myArray //delete [] also uses pointer arithmatic

//////////////////////////////////////////////////////////////////////////////
//VIRTUAL FUNCTION VISIBILITY
//////////////////////////////////////////////////////////////////////////////

//PLACEMENT OF VIRTUAL FUNCTIONS
//Base/Derived method visibility doesn't have to match
class Base
{
public:
    virtual void Show();
}
class Derived : public Base
{
private:
    virtual void Show() override;
}

Base* base = &derived; //will use base class visibility for Show()
Derived* deri = &derived; //will use derived class visibility for Show()

//NON-VIRTUAL INTERFACE IDIOM
//virtual functions in derived/base don't have to be both public
//if virtual base function shouldn't be called outside, make it private
class Base
{
public:
    void BaseShow();
private:
    virtual void Show();
}
class Derived : public Base
{
public:
    virtual void Show();
}
//Non-virtual method calls the private virtual method
void Base::BaseShow()
{
    Show();
}
//virtual derived method calls the base method
void Derived::Show()
{
    BaseShow();
}

//////////////////////////////////////////////////////////////////////////////
//INHERITING DEFAULT VARIABLES
//////////////////////////////////////////////////////////////////////////////

//never redefine default variables from the base class
//base class pointers will always use base class default values
class Base
{
public:
    virtual void MyMethod(int x = 10) = 0;
};
class Derived : public Base
{
public:
    virtual void MyMethod(int x = 2);
};

//calls derived method
basePtr->MyMethod(2); 

//calls derived method but uses base class default value
basePtr->MyMethod();

//////////////////////////////////////////////////////////////////////////////
//DATA HIDING
//////////////////////////////////////////////////////////////////////////////

//HIDING A METHOD
[BASE] virtual void MyMethod(int x); //Hidden
[DERI] virtual void MyMethod(double y);

//HIDING AN OVERLOADED METHOD
[BASE] virtual void MyMethod(int x); //Not hidden, can be called via Base::show
[BASE] virtual void MyMethod(char * x); //Hidden
[DERI] virtual void MyMethod(int x); 

//Difference in return type doesn't hide 
virtual Base& MyMethod(int x); //Not hidden
virtual Derived& MyMethod(int x);

//Methods are hidden but still accessible if type is cast to Base
static_cast<Base*>(derivedObj)->MyMethod(10); //can use base class version

//To prevent any data hiding of base class
class Derived: public Base 
{
public:
  using Base::MyMethod; //inherit all base show methods
}

//////////////////////////////////////////////////////////////////////////////
//CONVERTING BETWEEN BASE/DERIVED OBJECTS
//////////////////////////////////////////////////////////////////////////////

//CASTING DERIVED TO BASE
//can assign derived object to baseclass without typecast
Base& rBase = derivedObj 
Base* pBase = &derivedObj 

//CASTING BASE TO DERIVED
//only possible with typecast
Derived& rDerived = Derived(baseObj) 
Derived* pDerived = (Derived*)&baseObj

//ASSIGN/COPY DERIVED TO BASE
//implicitly converted
Base obj = derivedObj //sliced: loses derived information by-val
Base& obj = derivedObj //keeps derived information

//ASSIGN/COPY BASE TO DERIVED
//no implicit conversion; use single argument constructor/ass.op
Derived obj = BaseObj //conversion determined by derived class
Derived& obj = BaseObj //conversion determined by derived class
Derived(const Base& obj); 
Derived& operator=(const Base& obj); 

//////////////////////////////////////////////////////////////////////////////
//RUN-TIME TYPE INDENTIFICATION (RTTI)
//////////////////////////////////////////////////////////////////////////////

//DYNAMIC CAST POINTERS
Base* base;
Derived* derived = dynamic_cast<Derived*>(base);
if(d != nullptr){}

//DYNAMIC CAST REFERENCES
try 
{
    Base base;
    Derived& derived = dynamic_cast<Derived&>(base);
}
catch(bad_cast &)
{
};

//TYPE ID
//test for null pointer- typeid throws bad_typeid otherwise
#include <typeinfo>
Derived* someobject;
if(typeid(Derived) == typeid(*someobject))
{
    cout << typeid(*someobject).name();
}

//////////////////////////////////////////////////////////////////////////////
//PURE VIRTUAL FUNCTIONS / ABSTRACT BASE CLASSES
//////////////////////////////////////////////////////////////////////////////

//Pure virtual function creates an abstract base class/Pure virtual class
class ABC 
{
private:
public:
    virtual ~ABC(); 
    virtual double MyMethod() const = 0; 
};

class Derived : public ABC
{
public:
    virtual double MyMethod() const override; //must redefine a pure virtual function 
};

//////////////////////////////////////////////////////////////////////////////
//MULTIPLE INHERITANCE
//////////////////////////////////////////////////////////////////////////////

//MULTIPLE INHERITANCE
//Call each inherited class in constructor
class One {};
class Two {};
class MI : public One, public Two {};

MI::MI() :
    One(), 
    Two()
{
}

//VIRTUAL BASE CLASSES
//Use when inherited classes have same base class
//doesn't matter order of virtual/public
//stops inherited classes from calling their shared base class constructor
class Base {};
class One: virtual public Base {};
class Two: public virtual Base {};
class MI : public One, public Two {};

MI::MI() :
    One(), 
    Two(),
    Base()
{
}