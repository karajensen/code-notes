/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASSES / STRUCTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
STRUCTURE/CLASS DIFFERENCES
• Class members/inheritance is private by default
• Struct members/inheritance is public by default

RULE OF THREE
• If you define a destructor, copy constructor or assignment 
  operator, it's likely you need to define the other two

BITWISE CONST CHECKING
• Occurs if function doesn't modify any class non-static members 
• Doesn't include what a member pointer points to or returned values
• Compilers check for this in functions to determine if function meets constness

CLASS CONSTRUCTION
• References must be initialised through the initialisation list
• Don't call virtual methods in constructor/destructor; undefined behaviour; calls Base version
• Initialisation list doesn't reflect order of construction
• Static member variables initialised before program begins
• Order of construction:
    1) Base class(es) Initialisation List called
    2) Base class(es) Constructor Body called
    3) Derived Initialisation List called
    4) Derived Constructor Body called
    5) Derived Destructor called
    6) Base Desctructor called
• Order of base class construction:
    1) Virtual base classes, depth first, left to right ordering
    2) Normal base classes in order of declaration
**************************************************************************************************************/

class MyClass /*doesn't require name*/
{
public:
};

//STRUCTURES
//Class with members public by default
struct MyStruct /* doesn't require name */
{
};
struct /* create a new struct */
{
} m_struct;

//LOCAL CLASS/STRUCTURES
//Cannot define static member variables
//Can't access nonstatic local variables to MyFn
void MyFn()
{
    class MyClass {};
    MyClass myobj;
}

//AGGREGATES
//NO: Constructors, virtual methods, private/protected non-static data members
class Aggregate
{
public:
    int member;
    Aggregate& operator=(const Aggregate&);
    static int pubStaticMember;
    static void staticFunction();
    ~Aggregate();

private:
    void privateFunction();
    static int privStaticMember;
};
Aggregate obj = { 3 }; //can be auto initialized with {}

//PLAIN OLD DATA (POD)
//NO: Constructors, virtual methods, private/protected non-static data members
//NO: Destructors, assignment operators
class POD
{
public:
    int member;
    static int pubStaticMember;
    static void staticFunction();

private:
    void privateFunction();
    static int privStaticMember;
};
POD obj = { 3 }; //can be auto initialized with {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS MEMBERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CLASS METHODS                   
int MyMethod(){ return 0; }       // inline member
void MyMethod(int x = 0);         // default values only needed in declaration, not definition
void MyMethod() const;            // uses const 'this' pointer
MyClass() = default;              // create a default constructor inline in .h
MyClass::MyClass() = default;     // create a default constructor in .cpp (requires normal declaration in .h)
MyClass() = delete;               // don't create a default constructor
void MyFunction(int x) = delete;  // don't allow overload with this signature
void MyClass::Set(Subclass& obj); // Subclass as parameter doesn't require namespace
MyClass::Subclass& Get();         // Subclass as return value requires namespace
    
// STATIC METHODS
// cannot use const keyword
static void StaticMethod()  
{
    //only access static members and have friendship with class
    sm_singleton->m_member = x;
}

// CAST OPERATOR
// converts class type to another type
explicit operator double() { return 2.0; } //definition: MyClass::operator double(){}
explicit operator bool() const { return true; } //allows using in if(obj)
double myDouble = obj; //called implicitly if explicit is not used
double myDouble = double(obj); //called explicitly

// REFERENCE QUALIFIERS
void MyFunction() &;    // used when calling object is an lvalue: myObj.MyFunction()
void MyFunction() &&;   // used when calling object is an rvalue: MyClass().MyFunction()

// MEMBER INITIALISATION
// Overridden by value set in initialisation lists
float m_member = 3.0f;
float m_member{ 3.0f };
static float sm_member = 3.0f;
const int m_constMember = 2; //If not initialised in-place, must be in initialisation list
const int& m_refMember; //Must be in initialisation list

// PREVENT COPYING
// Important if dynamic allocation occurs in class
// delete preferred over no definition as compiler error 
// occurs rather than linker error when trying to use the method
MyClass(const MyClass&) = delete;
MyClass& operator=(const MyClass&) = delete;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLICIT CLASS MEMBERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Are generated inline in class header
• To generate in .cpp, delcare in header and use =default on definition
• =default generates implicit version and is not considered user-defined
• Templates never suppress generation of implicit member functions

ALL METHOD REQUIREMENTS:
• Create if function is required for usage of the class
• Create if no user version of function exists (=default okay)
• Create if function doesn't have =delete

COPY METHOD REQUIREMENTS:
• Does memberwise shallow copy of non-static data members
• Create if all members can be copy-assigned/copied automatically
• Create if no move-assignment or move constructor defined
• Will create if one needed and matching copy method is user-defined

MOVE METHOD REQUIREMENTS:
• Does memberwise moving of non-static data members
• Create if all members can be move-assigned/moved automatically
• Create if no destructor, copy-assignment, copy constructor defined
• Will NOT create if one needed and matching move method is user-defined
**************************************************************************************************************/

MyClass();                               // Default constructor
~MyClass();                              // Default destructor
MyClass(const MyClass& obj);             // Copy constructor
MyClass(MyClass&& obj);                  // Move constructor
MyClass& operator=(const MyClass& obj);  // Copy assignnment operator
MyClass& operator=(MyClass&& obj);       // Move assignment operator
unsigned int MyClass::operator&();       // Address operator

// DESTRUCTOR
// All are implicitly noexcept
// Derived are implicitly virtual if virtual base destructor
virtual ~MyClass(){} 
delete this; // calls destructor

// DEFAULT CONTRUCTOR
// initialisation list must be in same order defined in class
// Cannot be called explicitly unless in initialisation list
MyClass() :
    MyClass(x), // call another constructor (Delegating Constructor)
    m_constMember(0),
    m_refMember(ref)
{
}

// COPY CONSTRUCTOR
MyClass(const MyClass& obj)
{
    this.m_member = obj.m_member;
}

// MOVE CONSTRUCTOR
// Doesn't take const objects as it modifies rvalue passed in
MyClass(MyClass&& obj):
    m_pointer(std::move(obj.myPointer),
    m_member(std::move(obj.m_member))
{
}

// CONSTEXPR CONSTRUCTOR
// when members are known at compile time will create a literal object (can be used in constexpr functions)
constexpr MyClass(int x = 0, int y = 0) : X(x), Y(x) {}

// INITIALIZER LIST CONSTRUCTOR
// Take priority in overload when {} are used and implicit conversion can happen
MyClass(std::initializer_list<double> x) 
{
    m_myVector.resize(x.size());
    std::copy(x.begin(), x.end(), m_myVector);
}
MyClass obj{1, true}    // Uses MyClass(std::initializer_list<double> x) and converts arguments
MyClass obj{2.0L}       // Uses MyClass(double long x) as cannot convert implicitly
MyClass obj(1, true)    // Uses MyClass(int x, bool y)

// CONVERSION CONSTRUCTOR
// single argument constructor
// use explicit to stop implicit conversions from taking place
// myObj = 4.3f; without explicit acts as cast operator
explicit MyClass(float myFloat) {}

// COPY ASSIGNMENT OPERATOR
MyClass& operator=(const MyClass& obj)
{
    if(&obj == this) //check not copying self
    { 
        return *this;
    } 
    delete[] m_pointer; //delete any dynamic allocation for object
    m_pointer = new int(); //allocate new memory for deep copy
    *m_pointer = *obj.m_pointer; //copy over values
    return *this;
}

// MOVE ASSIGNMENT OPERATOR
// Doesn't take const objects as it modifies rvalue passed in
MyClass& operator=(MyClass&& obj)
{
    if(this == &obj)
    {
        return *this;
    }
    delete [] m_pointer; //delete any dynamic allocation for object
    m_pointer = obj.m_pointer; //steal the address
    obj.myPointer = nullptr; //set to null
    return *this;
}

// COPY - SWAP IDIOM
// Allows assignment operator not duplicating copy constructor, useful for deep copying
// Used for exception safty in assignment operator when allocating new memory
// Requires non - throwing swap function, copy constructor and destructor
// Passes argument in by - val; if construction fails, 'this' never used in body which gives strong exception guarantee
// Take parameter by-val to use copy constructor
MyClass& operator=(const MyClass obj)
{
    std::swap(*this, obj);
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OPERATOR OVERLOADING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
OPERATOR OVERLOADING RESTRICTIONS
• Must have one argument as an object
• Can't change precedence
• Can't create new symbols

CAN'T BE OVERLOADED
.         The membership operator
.*        The pointer-to-member operator
::        The scope-resolution operator
?:        The conditional operator
sizeof    The sizeof operator

ONLY OVERLOADED BY CLASS
=         Assignment operator
()        Function call operator
[]        Subscripting operator
->        Class member access by pointer operator

CAN BE OVERLOADED
+       -       *       /       %       ^
&       |       ~=      !       =       <
>       +=      -=      *=      /=      %=
^=      &=      |=      <<      >>      >>=
<<=     ==      !=      <=      >=      &&
||      ++      --      ,       ->*     ->
()      []      new     delete  new[]   delete[]
**************************************************************************************************************/

//USING OVERLOADS
obj1*obj2  /*->*/  obj1.operator*(obj2);
obj1+obj2  /*->*/  obj1.operator+(obj2);
obj1[4]    /*->*/  obj1.operator[](4) 
obj1[0][1] /*->*/  (obj1[0].operator[](1)).operator[0];

//OVERLOAD DECLARATIONS
MyClass operator++(int unused); //postfix: returns copy of value, then increments
MyClass operator--(int unused); //postfix: returns copy of value, then decrements
MyClass& operator++(); //prefix: increments, then returns reference to value
MyClass& operator--(); //prefix: decrements, then returns reference to value
const MyClass operator+(const MyClass& x) const;
const MyClass operator*(const MyClass& x) const;
MyClass& operator[](const int i);
const MyClass& operator[](const int i) const;

//NEW/DELETE OVERLOADING
//User defined new/delete must be in done in pairs
//Both automatically static even without keyword
static void* operator new(std::size_t); 
static void operator delete(void*);     

//OVERLOADING FOR A*B ONLY
A * B /*->*/ A.operator*(B);
const MyClass operator*(const MyClass& x) const;

//OVERLOADING FOR A*B AND B*A
B * A /*->*/ operator*(B, A); 
friend const MyClass operator*(const MyClass& x1, const MyClass& x2) const;

//OVERLFOADING STD::COUT 
friend std::ostream & operator<<(std::ostream& os, const MyClass& obj)
{
    os << obj.m_member;
    return os;
}
std::cout << obj;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FRIENDS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Doesn't matter where defined inside class (public/private/protected)
// Allows method/class access to private/protected members of A
// Are not inherited
class A
{
public:
    friend void B::MyMethod(); // friend only a method
    friend class B; // friend a class, 'class' auto forward declares if needed
    friend void MyFunction(const MyClass& x1, const MyClass& x2){} // create inline method
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INHERITANCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
--------------------------------------------------------
FUNCTION      INHERITED    IMPLICIT  VIRTUAL  RETURNS
--------------------------------------------------------
Constructors  No           Yes        No      No
Destructor    No           Yes        Yes     No
Operator=     No           Yes        Yes     Yes
Operator&     Yes          Yes        Yes     Yes
Operator[]    Yes          No         Yes     Yes
Conversion    Yes          No         Yes     Yes
Friends       No           No         Yes     -
            
PUBLIC INHERITANCE
• Allows derived cast to base
• Base protected/public members can be accessed by derived class
• Base public members can be accessed by everything

PROTECTED INHERITANCE
• Doesn't allow derived cast to base
• Base public members cannot be accessed outside derived class
• Base protected/public members can be accessed by derived class
• Base protected/public members can be accessed by further derived classes 

PRIVATE INHERITANCE
• Doesn't allow derived cast to base
• Base public members cannot be accessed outside derived class
• Base protected/public members can be accessed by derived class
• Base protected/public members cannot be accessed by further derived classes

VIRTUAL FUNCTIONS:
• Function that can be redefined in a derived class to provide a different implementation
• Pointers/references will call virtual functions based on underlying object type stored
• Pointers/references will call non-virtual functions based on the type of pointer
• Virtual destructor required if using base pointer holding derived type else base destructor not called
• Protected non-virtual destructor prevents deleting base pointer holding derived type 
• Slower than normal functions as additional requirement to access vtbl/compiler cannot optimize (eg. inline)
• Can't be a template function as once the run-time system figured out it would need to call a templatized 
  virtual function, compilation is all done and the compiler cannot generate the appropriate instance anymore

VIRTUAL FUNCTION REQUIREMENTS:
• Virtual keyword on base class function
• Matching function signatures including constness on all overriding functions
• Matchine refence qualifiers on all overriding functions
• Compatible return type and exception specifications

NON-VIRTUAL INTERFACE IDIOM:
• Virtual function visibility in derived/base don't have to match
• Chosen visibility determined from type of pointer/reference used
• If virtual base function shouldn't be called, make it private

V-TABLE VIRTUAL FUNCTION TABLE:
• Vtbl is array of function addresses for a class that has virtual functions in the static data segment
• Usually stored as a static array at compile-time though exact implementation compiler specific
• One hidden vptr per class hierarchy is created
• When virtual function called, vtble used to find the correct address
• Stores the classes's type_info object used for RTTI

RUN-TIME TYPE INDENTIFICATION (RTTI)
• Allows determining type of derived class from a base class *
• Only works on classes that use virtual methods as type_info stored in vtbl
• Sometimes turned off- must enable run time type info setting

PURE VIRTUAL CLASS/ABSTRACT BASE CLASS
• Base class where a method is declared but not defined; pure virtual method

VIRTUAL BASE CLASS
• Creates a shared base class if more than two of the same base class exist
• Number of times virtual inheritance is used in hierarchy is number of hidden pointers created
• Constructor of virtual base classes called by most derived class first

-----------------------------------------------------------------------------
                         +Object size    +Class size    Prevents inlining
-----------------------------------------------------------------------------
Virtual Functions            Yes             Yes             Yes 
Multiple Inheritance         Yes             Yes             No 
Virtual Base Classes         Yes             Yes             No 
RTTI                         No              Yes             No 
**************************************************************************************************************/

// ABSTRACT BASE CLASS/PURE VIRTUAL CLASS
class Base
{
public: 
    Base(int x); //constructors can't be virtual
    virtual void MyMethod() = 0; //pure virtual method, no objects of Base can be created
    virtual void MyMethod() = 0 {} //pure virtual method with body, no objects of Base can be created
    virtual ~Base(); //virtual destructor required if we want polymorphic inheritance
    virtual ~Base() = 0 {} //if destructor pure virtual must have body
protected:
    ~Base() {} // non-virtual protected destructor prevents polymorphic inheritance and plain Base objects
};

// PUBLIC INHERITANCE
// final stops class from being further derived
class Derived final : public Base 
{
public: 

    Derived(int x, int y) : Base(x) {} 

    //Inheriting constructors, no need for constructor to specify base constructor
    using Base::Base;

    //Only requires signature to match virtual base method- override, virtual, final optional
    virtual void MyMethod(int x) override final
    {
        Base::MyMethod(x); //Call base version
    }
};

// PROTECTED INHERITANCE
class Derived : protected Base
{
    void DerivedMethod(){ MyMethod(); } //internal visibility retained
};
myDerived->MyMethod(); //cannot be called as seen as protected with outside use

// PRIVATE INHERITANCE
class Derived : private Base
{
    void DerivedMethod(){ MyMethod(); } //internal visibility retained
};
myDerived->MyMethod(); //cannot be called as seen as private with outside use

// VIRTUAL FUNCTION OBJECTS
// Derived and base are objects of respective types
// Note base class methods are hidden from derived objects
derived.MyMethod(x)   // calls Derived::MyMethod()
derived.MyVirtual(x)  // calls Derived::MyVirtual()
base.MyMethod(x)      // calls Base::MyMethod()
base.MyVirtual(x)     // calls Base::MyVirtual()

// VIRTUAL FUNCTION POINTER/REFERENCES
// Derived and base both hold pointer to derived object
derived->MyVirtual();          // calls Derived::MyVirtual()
derived->MyMethod();           // calls Derived::MyMethod()
derived->Base::MyVirtual();    // calls Base::MyVirtual()           
base->MyVirtual();             // calls Derived::MyVirtual()
base->MyMethod();              // calls Base::MyMethod()
base->Derived::MyDerived();    // ERROR!

// NON-VIRTUAL INTERFACE IDIOM
// Visibility determined by type of pointer used, not type of object pointed to
class Base
{
private:
    virtual void MyMethod();
}
class Derived : public Base
{
public:
    virtual void MyMethod() override;
}

basePtr->MyMethod(); // Uses base class visility: Cannot call MyMethod()
deriPtr->MyMethod() // Uses derived class visibility: Can call MyMethod()

//INHERITING DEFAULT VALUES
//Default value used determined by type of pointer used, not type of object pointed to
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
basePtr->MyMethod();    //calls derived method but uses base class default value
derivedPtr->MyMethod(); //calls derived method and uses derived default value

//CASTING DERIVED TO BASE
Base& base = derivedObj 
Base* base = &derivedObj
Base base = derived; // causes slicing

//CASTING BASE TO DERIVED
Derived* derived = dynamic_cast<Derived*>(base); //returns nullptr if cannot be converted
Derived& derived = dynamic_cast<Derived&>(base); //throw bad_cast if cannot be converted
Derived& derived = Derived(baseObj) 
Derived* derived = (Derived*)&base
Derived derived = base; // only possible if derived has copy constructor for Base&

//MULTIPLE INHERITANCE
//Call each inherited class in constructor in order of inheritance
class One {};
class Two {};
class MI : public One, public Two {};
MI::MI() :
    One(), 
    Two()
{
}

//VIRTUAL INHERITANCE
//Use when inherited classes have same base class
//Any class inherited virtually become part of most derived class initialisation list
//Doesn't matter order of virtual/public
//Number of times virtual is used in hierarchy is number of hidden pointers created
class Base {};
class One: virtual public Base {}; // adds +1 hidden pointer to hierarchy
class Two: public virtual Base {}; // adds +1 hidden pointer to hierarchy
class MI : public One, public Two {};
MI::MI() :
    Base(), //Base constructor called implicitly by MI first
    One(), 
    Two()
{
}
