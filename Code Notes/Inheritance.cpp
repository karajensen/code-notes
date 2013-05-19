//////////////////////////////////////////////////////////////////////////////
//IS-A INHERITANCE: PUBLIC INHERITANCE
//////////////////////////////////////////////////////////////////////////////

class Base
{
public: 
    virtual ~Base();  //put as virtual only if want to derive from it
    virtual void show()=0; //pure virtual method
    friend std::ostream & operator<<(std::ostream & os, const Base & x);
};

class Derived : public Base //compilier assumes private if public not specified
{
public: 
    Derived(int x, int y, bool z); 
    Derived(int y, Base & bo); 
    void show(); //virtual implicitely taken from base class virtual
    friend std::ostream & operator<<(std::ostream & os, const Derived & x);
};

//--------------------------------------------------------------------------
//CONSTRUCTORS
//--------------------------------------------------------------------------
//Base object is created first in initialisation list
//Default Base constructor used if not specified
Derived::Derived(int x, int y, bool z) : Base(x,z) {}
Derived::Derived(int y, Base & bo) : Base(bo) {}

//--------------------------------------------------------------------------
//DESTRUCTORS
//--------------------------------------------------------------------------
//Object destroyed in opposite direction of creation, base->derived
//For a pure virtual destructor, requires definition in cpp
Derived::~Derived(){}

//--------------------------------------------------------------------------
//DERIVED CLASS METHOD
//--------------------------------------------------------------------------
Derived::Show()
{
    //Calling Base method
    //Base:: important otherwise compiler thinks you're calling Derived::show()
    Base::Show(); 
};

//--------------------------------------------------------------------------
//DERIVED CLASS FRIENDS
//--------------------------------------------------------------------------
std::ostream & Derived::operator<<(std::ostream & os, const Derived & x)
{
    //Calling Base friend method
    //typecast DerivedObject to BaseClassObject to use overload<< from Base
    os << (const Base &) x;
    os << dynamic_cast<const Base&>(x);
    return os;                   
}

//////////////////////////////////////////////////////////////////////////////
//HAS-A INHERITANCE: PRIVATE, PROTECTED, CONTAINMENT
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------
//CONTAINMENT
//----------------------------------------------------------------
class Containment
{
private:
    MyClass m_myClassObject;

}
//----------------------------------------------------------------
//PRIVATE INHERITANCE
//----------------------------------------------------------------
//Same as containment but uses a 'hidden' object of base 
//Derived object cannot be cast to its base class

//Base class
class Base
{
public:
    virtual void show(); //derived class inherits as private
};
//Derived class
class Derived : private Base 
{
public:
    virtual void show() override;
};
//Methods and usage
void Derived::show()
{
    Base::show(); //okay
}
int main()
{
    derived->show();      //okay
    derived->Base::show() //not okay
}

//----------------------------------------------------------------
//PROTECTED INHERITANCE
//----------------------------------------------------------------
//Same structure as private until a second derived class
//Derived object cannot be cast to its base class

//Base class
class Base
{
protected:
    virtual void show(); //derived class inherits as protected
};
//First Derived Class
class Derived : protected Base
{
public:
    virtual void show();
};
//Second Derived Class
class Derived2 : protected Derived
{
public:
    virtual void show() override;
}
//Methods and usage
void Derived::show()
{
    Base::show(); //okay
}
void Derived2::show()
{
    Derived::show(); //okay
    Base::show(); //okay
}
int main()
{
    derived2->show();      //okay
    derived2->Base::show(); //not okay
    derived2->Derived::show(); //not okay
}

//////////////////////////////////////////////////////////////////////////////
//VIRTUAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

class Base
{
public:
    virtual void virtShow();
    void show();
}
class Derived : public Base
{
public:
    virtual void virtShow() override;
    void show();
    void deriFunct();
}

//OBJECTS
derived.show()     //uses Derived::show()
base.show()        //uses Base::show()
derived.virtShow() //uses Derived::virtShow()
base.virtShow()    //uses Base::virtShow()

//POINTER/REFERENCES
Derived * deriPtr = &derivedObject;
Base * basePtr = &derivedObject;

deriPtr->virtShow();       //uses Derived::virtShow()
deriPtr->show();           //uses Derived::show()
deriPtr->deriFunct();      //uses Derived::deriFunct()
deriPtr->Base::virtShow(); //uses Base::virtShow()

basePtr->virtShow();      //uses Derived::virtShow()
basePtr->show();          //uses Base::show()
basePtr->deriFunct();     //ERROR!

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
    virtual void draw(int x = 10) = 0;
};
class Derived : public Base
{
public:
    virtual void draw(int x = 2);
};

//calls derived method
basePtr->draw(2); 

//calls derived method but uses base class default value
basePtr->draw();

//////////////////////////////////////////////////////////////////////////////
//DATA HIDING
//////////////////////////////////////////////////////////////////////////////

//HIDING A METHOD
[BASE] virtual void show(int x); //Hidden
[DERI] virtual void show(double y);

//HIDING AN OVERLOADED METHOD
[BASE] virtual void show(int x); //Not hidden, can be called via Base::show
[BASE] virtual void show(char * x); //Hidden
[DERI] virtual void show(int x); 

//Difference in return type doesn't hide 
virtual Base& show(int x); //Not hidden
virtual Derived& show(int x);

//Methods are hidden but still accessible if type is cast to Base
static_cast<Base*>(derivedObj)->show(10); //can use base class version

//To prevent any data hiding of base class
class Derived: public Base 
{
public:
  using Base::show; //inherit all base show methods
  ...
}

//////////////////////////////////////////////////////////////////////////////
//CONVERTING BETWEEN BASE/DERIVED OBJECTS
//////////////////////////////////////////////////////////////////////////////

//CASTING DERIVED TO BASE
//can assign derived object to baseclass without typecast
BaseClass& r_baseclass = derivedObject 
BaseClass* p_baseclass = &derivedObject 

//CASTING BASE TO DERIVED
//only possible with typecast
DerivedClass& r_derivedclass = DerivedClass(baseObject) 
DerivedClass* p_derivedclass = (DerivedClass*)&baseObject

//ASSIGN/COPY DERIVED TO BASE
//implicitly converted
BaseClass obj = DerivedObj //sliced: loses derived information by-val
BaseClass& obj = DerivedObj //keeps derived information

//ASSIGN/COPY BASE TO DERIVED
//no implicit conversion; use single argument constructor/ass.op
DerivedClass obj = BaseObj //conversion determined by derived class
DerivedClass& obj = BaseObj //conversion determined by derived class
DerivedClass(const BaseClass& bo); 
DerivedClass& operator=(const BaseClass& bo); 

//////////////////////////////////////////////////////////////////////////////
//RUN-TIME TYPE INDENTIFICATION (RTTI)
//////////////////////////////////////////////////////////////////////////////

//DYNAMIC CAST POINTERS
Base* base;
Derived* d = dynamic_cast<Derived*>(base);
if(d != nullptr){}

//DYNAMIC CAST REFERENCES
try 
{
    Base base;
    Derived & d = dynamic_cast<Derived&>(base);
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

//ABSTRACT BASE CLASS
class ABC 
{
private:
public:
    virtual ~ABC();                  //Must have a pure virtual function
    virtual double Area() const = 0; //disallows creation of ABC objects
}

//DERIVED CLASS
class DerivedABC : public ABC
{
public:
    virtual double Area() const; //must redefine a pure virtual function 
};

//////////////////////////////////////////////////////////////////////////////
//INHERITANCE AND DYNAMIC MEMORY
//////////////////////////////////////////////////////////////////////////////

class BaseClass
{
private:
    char * b_pointer;
public:
    BaseClass(const char * p); //constructor using new
    BaseClass(const BaseClass & o); //copy constructor using new
    virtual ~BaseClass(); //destructor using delete
    BaseClass & operator=(const BaseClass & o); //assigment operator using new
};


//CASE 1: BASECLASS USES NEW, DERIVED DOESN'T
//Constructors, destructor, =operator called implictly after Derived 
//versions to deal with BaseClass part
class DerivedClass
{
private:
public: 
    DerivedClass(); 
    virtual ~DerivedClass();
    //implicit copy constructor/assignment operator
};

//Default BaseClass constructor called implicitly
DerivedClass::DerivedClass()
{
};


//CASE 2: BASECLASS USES NEW, DERIVED DOES
//Constructors, destructor, =operator called explicitly after Derived 
//versions to deal with BaseClass part
class DerivedClass
{
private:    
    char * d_pointer;
public: 
    DerivedClass(const char * p); //constructor using new
    DerivedClass(const DerivedClass & o); //copy constructor using new
    virtual ~DerivedClass(); //destructor using delete
    DerivedClass & operator=(const DerivedClass & o);
};

//Copy Constructor
DerivedClass::DerivedClass(const DerivedClass & o) : BaseClass(o) 
{
    int len = strlen(o.b_pointer); //copy Derived portion
    d_pointer = new char[len+1];
    strcpy(d_pointer, b_pointer);
}
//Assignment Operator
DerivedClass & DerivedClass::operator=(const DerivedClass & o)
{
    if (this == &o)
        return *this;
    BaseClass::operator=(o); //copy Base portion
    int len = strlen(o.b_pointer); //copy Derived portion 
    delete [] d_pointer;
    d_pointer = new char[len+1]
    strcpy(d_pointer, b_pointer);
    return *this;
}


//////////////////////////////////////////////////////////////////////////////
//MULTIPLE INHERITANCE
//////////////////////////////////////////////////////////////////////////////

//Multiple inheritance = deriving from more than one base class

//MULTIPLE INHERITANCE
Class BaseClass
{
};
Class one: public BaseClass
{
};
Class two: public BaseClass
{
};
class MI : public one, public two 
{
    //MI, one, two, x2 baseClass
};


//VIRTUAL BASE CLASSES
Class VBaseClass
{
};
//adding virtual makes BaseClass a Virtual Base Class
Class Vone: virtual public VBaseClass
{
};
Class Vtwo: public virtual VBaseClass
{
};
class VMI : public Vone, public Vtwo 
{
    //VMI, Vone, Vtwo, x1 VbaseClass with virtual
};

//CONSTRUCTORS
//Derivedclasses can only call constructors from immediate class they inherit 
//from, which in turn calls constructor from what baseclass they inherit from
//except in case of Virtual Base Classes

//MI: class one will call constructor from BaseClass for its BaseClass 
//portion and class will do the same
MI::MI(const BaseClass & o) : one(o), two(o)
{
};

//VBC: class Vone and Vtwo both will call constructor for single VBaseClass 
//portion hence this is disabled; call base class as well
VMI::VMI(const VBaseClass & o) : VBaseClass(o), Vone(o), Vtwo(o) 
{
};

//CALLING METHODS

VMI VMIobj;
VMIobj.Vtwo::show(); //uses show() from Vtwo class

void VMI::show() //VMI class method
{
    VBaseClass::show();
    Vone::show();
    Vtwo::show();
};
VMIobj.show()

