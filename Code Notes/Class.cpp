/////////////////////////////////////////////////////////////////////////////////////
//CLASS METHODS
/////////////////////////////////////////////////////////////////////////////////////
                              
//IMPLICIT MEMBERS    
//created inline in header file
MyClass();                               // default constructor
~MyClass();                              // default destructor
MyClass(const MyClass& obj);             // copy constructor
MyClass(MyClass&& obj);                  // move constructor
MyClass& operator=(const MyClass& obj);  // copy assignnment operator
MyClass& operator=(MyClass&& obj);       // move assignment operator
unsigned int MyClass::operator&();       // address operator

//DESTRUCTOR
//All are implicitly noexcept
//Derived are implicitly virtual if virtual base destructor
virtual ~MyClass(){} 
delete this; // calls destructor

//CONSTRUCTOR
//initialisation list must be in same order defined in class
MyClass() :
    m_constMember(0),
    m_refMember(ref)
{
}

//COPY CONSTRUCTOR
MyClass::MyClass(const MyClass& obj)
{
    this.m_member = obj.m_member;
}

//MOVE CONSTRUCTOR
//Doesn't take const objects as it modifies rvalue passed in
MyClass(MyClass&& obj):
    m_pointer(std::move(obj.myPointer),
    m_member(std::move(obj.m_member)
{
}

//COPY ASSIGNMENT OPERATOR
MyClass& MyClass::operator=(const MyClass& obj)
{
    if(&obj == this) //check not copying self
    { 
        return *this;
    } 
    this->m_member = obj.m_member; //copy over values
    return *this;
}

//MOVE ASSIGNMENT OPERATOR
//Doesn't take const objects as it modifies rvalue passed in
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

//CONSTEXPR CONSTRUCTOR
//when members are known at compile time will create a literal object (can be used in constexpr functions)
constexpr MyClass(int x = 0, int y = 0) : X(x), Y(x) {}

//INITIALIZER LIST CONSTRUCTOR
MyClass(std::initializer_list<double> list) 
{
    m_myVector.resize(list.size());
    std::copy(list.begin(), list.end(), m_myVector);
}

//CONVERSION CONSTRUCTOR
//single argument constructor
//use explicit to stop implicit conversions from taking place
//myObj = 4.3f; without explicit acts as cast operator
explicit MyClass(float myFloat)
{
}

//CAST OPERATOR
//converts class type to another type
explicit operator double() { return 2.0; } //definition: MyClass::operator double(){}
double myDouble = obj; //called implicitly if explicit is not used
double myDouble = double(obj); //called explicitly

//STATIC METHODS
//cannot use const keyword
static void StaticMethod()  
{
    //only access static members and have friendship with class
    sm_singleton->m_constMember = x;
}

//CLASS METHODS
int MyMethod(){ return 0; }      // inline member
void MyMethod(int x = 0);        // default values only needed in declaration, not definition
void MyMethod() const;           // uses const 'this' pointer
MyClass() = default;             // create a default constructor inline in .h
MyClass::MyClass() = default;    // create a default constructor in .cpp (requires non default declaration in .h)
MyClass() = delete;              // don't create a default constructor
void MyFunction(int x) = delete; // don't allow overload with this signature
    
//REFERENCE QUALIFIERS
void MyFunction() &;    // used when calling object is an lvalue: myObj.MyFunction()
void MyFunction() &&;   // used when calling object is an rvalue: MyClass().MyFunction()

//MEMBER INITIALISATION
//Overridden by value set in initialisation lists
float m_member = 3.0f;
static float sm_member = 3.0f;
const int m_constMember = 2; //If not initialised in-place, must be in initialisation list
const int& m_refMember; //Must be in initialisation list

//PREVENT COPYING
//Important if dynamic allocation occurs in class
//delete preferred over no definition as compiler error 
//occurs rather than linker error when trying to use the method
MyClass(const MyClass) = delete;
MyClass& operator=(const MyClass) = delete;

/////////////////////////////////////////////////////////////////////////////////////
//CLASSES
/////////////////////////////////////////////////////////////////////////////////////

class MyClass /*doesn't require name*/
{
public:
};

//STRUCTURES
//Class with members public by default
struct MyStruct /*doesn't require name*/
{
    float x;
    float y;
}; 

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
Aggregate obj = {3}; //can be auto initialized with {}

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
POD obj = {3}; //can be auto initialized with {}

/////////////////////////////////////////////////////////////////////////////////////
//OPERATOR OVERLOADING
/////////////////////////////////////////////////////////////////////////////////////

//USING OVERLOADS
obj1*obj2  /*->*/  obj1.operator*(obj2);
obj1+obj2  /*->*/  obj1.operator+(obj2);
obj1[4]    /*->*/  obj1.operator[](4) 
obj1[0][1] /*->*/  (class1[0].operator[](1)).operator[0];

//OVERLOAD DECLARATIONS
MyClass& operator++(); //prefix
MyClass& operator--(); //prefix
MyClass operator++(int unused); //postfix
MyClass operator--(int unused); //postfix
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

/////////////////////////////////////////////////////////////////////////////////////
//FRIENDS
/////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////
//COPY-SWAP IDIOM
/////////////////////////////////////////////////////////////////////////////////////

// Using the copy-swap idiom for deep copying and 
// implementing assingment operator from copy constructor
class Array
{
public:

    int* arr;
    int size;

    //CONSTRUCTOR
    Array(int x = 0) 
      : size(x), 
        arr(new int[size]())
    {}

    //COPY-CONSTRUCTOR
    Array(const Array& other)
      : size(other.size),
        arr(new int[other.size]())
    {
        //Non-throwing due to type used
        std::copy(other.arr, other.arr + other.size, arr);
    }

    //DESTRUCTOR
    ~Array()
    {
        delete [] arr;
    }

    //SWAP FUNCTION
    friend void Swap(Array& first, Array& second)
    {
        std::swap(first.size, second.size); 
        std::swap(first.arr, second.arr);
    }

    //ASSIGNMENT OPERATOR
    //take parameter by-val to use copy constructor
    Array& operator=(const Array other)
    {
        Swap(*this, other);
        return *this;
    } 
};

/////////////////////////////////////////////////////////////////////////////////////
//INHERITANCE
/////////////////////////////////////////////////////////////////////////////////////

// ABSTRACT BASE CLASS/PURE VIRTUAL CLASS
class Base
{
public: 
    Base(int x); //constructors can't be virtual
    virtual ~Base(); //put as virtual only if want to derive from it
    virtual ~Base()=0; //used if needing abstract class but all methods implemented
    virtual void MyMethod(int x)=0; //pure virtual method, no objects of Base can be created
};

// PUBLIC INHERITANCE
// compilier assumes private if public not specified
// sealed stops class from being further derived
class Derived sealed : public Base 
{
public: 

    Derived(int x, int y) : Base(x) 
    {} 

    //Inheriting constructors, no need for constructor to specify base constructor
    using Base::Base;

    //Only requires signature to match virtual base method
    //override and virtual are optional, final prevents further overriding
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
//derived and base are objects of respective types
//Note base class methods are hidden from derived objects
derived.MyMethod(x)   // calls Derived::MyMethod()
derived.MyVirtual(x)  // calls Derived::MyVirtual()
base.MyMethod(x)      // calls Base::MyMethod()
base.MyVirtual(x)     // calls Base::MyVirtual()

// VIRTUAL FUNCTION POINTER/REFERENCES
//derived and base both hold pointer to derived object
derived->MyVirtual();          // calls Derived::MyVirtual()
derived->MyMethod();           // calls Derived::MyMethod()
derived->Base::MyVirtual();    // calls Base::MyVirtual()           
base->MyVirtual();             // calls Derived::MyVirtual()
base->MyMethod();              // calls Base::MyMethod()
base->Derived::MyDerived();    // ERROR!

// NON-VIRTUAL INTERFACE IDIOM
// Visibility of virtual functions in derived/base don't have to match
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
//Never redefine default values in derived as value chosen based 
//on pointer type not underlying object
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
basePtr->MyMethod(0);   //calls derived method
basePtr->MyMethod();    //calls derived method but uses base class default value
derivedPtr->MyMethod(); //calls derived method and uses derived default value

/////////////////////////////////////////////////////////////////////////////////////
//BASE-DERIVED CONVERSION
/////////////////////////////////////////////////////////////////////////////////////

Derived* derived = dynamic_cast<Derived*>(base); //returns nullptr if cannot be converted
Derived& derived = dynamic_cast<Derived&>(base); //throw bad_cast if cannot be converted

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

/////////////////////////////////////////////////////////////////////////////////////
//MULTIPLE INHERITANCE
/////////////////////////////////////////////////////////////////////////////////////

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
class Base {};
class One: virtual public Base {}; //doesn't matter order of virtual/public
class Two: public virtual Base {};
class MI : public One, public Two {};

MI::MI() :
    One(), 
    Two(),
    Base() //base must be explicitly called as One/Two cannot call theirs
{
}