/////////////////////////////////////////////////////////////////////////////////////
//CLASSES
/////////////////////////////////////////////////////////////////////////////////////

class MyClass /*doesn't require name*/
{
public:

    int MyMethod(){ return 0; }  // inline member
    void MyMethod() const;       // uses const 'this' pointer
                                                
    //IMPLICIT MEMBERS                          
    MyClass();                               // default constructor
    ~MyClass();                              // default destructor
    MyClass(const MyClass& obj);             // copy constructor
    MyClass(MyClass && obj);                 // move constructor
    MyClass& operator=(const MyClass& obj);  // copy assignnment operator
    MyClass& operator=(MyClass && obj);      // move assignment operator
    unsigned int MyClass::operator&();       // address operator
    MyClass() = delete;                      // don't create a default constructor

    //DESTRUCTOR
    virtual ~MyClass(){} // virtual destructor required for inheritance
    delete this; // calls destructor

    //CONSTRUCTOR
    //initialisation list must be in same order defined in class
    //single argument constructor: use explicit to stop implicit conversions from taking place
    //myObj = 4.3f; without explicit acts as cast operator
    explicit MyClass(float myFloat) :
        m_constMember(0),
        m_refMember(ref)
    {
    }

    //INITIALIZER LIST CONSTRUCTOR
    MyClass(std::initializer_list<float> list) :
        myVector(list)
    {
    }

    //MOVE CONSTRUCTOR
    //Doesn't take const objects as it modifies rvalue passed in
    MyClass(MyClass && obj):
        m_pointer(std::move(obj.myPointer),
        m_member(std::move(obj.m_member)
    {
    }

    //COPY CONSTRUCTOR
    MyClass::MyClass(const MyClass& obj)
    {
        this.m_member = obj.m_member;
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
    MyClass& operator=(MyClass && obj)
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

    //STATIC METHODS
    //cannot use const keyword
    static void StaticMethod()  
    {
        //only access static members and have friendship with class
        m_singleton->m_constMember = x;
    }

    //CAST OPERATOR
    //definition: MyClass::operator double(){ return 2.0 }
    //returns double even without return type in signature
    //can be used for custom types: operator Vector3();
    operator double();
    double myDouble = obj; //called implicitly
    double myDouble = double(obj); //called explicitly
                                                  
private:

    //Prevent copying, no declaration required
    //Important if dynamic allocation occurs in class
    MyClass(const MyClass); 
    MyClass& operator=(const MyClass);

    const int m_constMember; //Must be initialised in initialisation list
    const int& m_refMember; //Must be initialised in initialisation list
    static const int STATIC = 20; //Only const int can be defined in class header
    MyClass* m_singleton; 
};

//STRUCTURES
//Class with members public by default
struct MyStruct /*doesn't require name*/
{
    float x;
    float y;
}; 

/////////////////////////////////////////////////////////////////////////////////////
//CREATING OBJECTS 
/////////////////////////////////////////////////////////////////////////////////////

//USING INITIALIZER LIST
MyStruct obj = {32, 23.1}; 

//DEFAULT CONSTRUCTOR PITFALL
ONE one(); //sees as function declaration, fixed by ONE one;

//CONSTRUCTOR INSIDE CONSTRUCTOR PITFALL
ONE one(TWO(x)); //can't be done; thinks it's a function declarion
ONE one(TWO(3)); //can be done; realises it's object creation
ONE one((TWO(x))); //can be done; realises it's object creation
ONE one(two); //where two = TWO(x) can be done

/////////////////////////////////////////////////////////////////////////////////////
//CLASS TYPES
/////////////////////////////////////////////////////////////////////////////////////

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
Aggregate obj = {3}; //can be initialized with {}

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
POD obj = {3}; //can be initialized with {}

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
void* operator new(std::size_t);                         //plain new
void* operator new(std::size_t, std::nothrow_t) throw(); //nothrow new
void* operator new(std::size_t, void*);                  //in-place new

//USING FRIENDS COUPLED WITH OVERLOADED OPERATOR
A = B * 2.0 /*->*/ A = B.operator*(2.0);
const MyClass operator*(const double val) const;

A = 2.0 * B /*->*/ A = operator*(2.0, B); 
friend const MyClass operator*(const double val, const MyClass& obj) const;

//OVERLFOADING STD::COUT 
friend std::ostream & operator<<(std::ostream& os, const MyClass& obj); 
std::ostream & TestClass::operator<<(std::ostream & os, const MyClass& obj)
{
    os << obj.m_member;
    return os;
}
std::cout << obj;

/////////////////////////////////////////////////////////////////////////////////////
//FRIENDS
/////////////////////////////////////////////////////////////////////////////////////

//FRIEND FUNCTIONS
class A
{
public:
    class B; //forward declaraction
    friend void B::MyMethod(); 
};

class B
{
public:
    void B::MyMethod(); //method can access privates of A
};

//FRIEND CLASSES
class A
{
public:
    //auto forward declares
    //doesn't matter where defined- public/private/protected
    friend class B; 
};

class B
{
public: //class can access privates of A
};

/////////////////////////////////////////////////////////////////////////////////////
//COPY-SWAP IDIOM 
/////////////////////////////////////////////////////////////////////////////////////

//Using the copy-swap idiom for deep copying
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
    virtual void MyMethod()=0; //pure virtual method, no objects of Base can be created
};

// PUBLIC INHERITANCE
class Derived : public Base //compilier assumes private if public not specified
{
public: 
    Derived(int x, int y) : Base(x) {} //Default Base constructor used if not specified
    virtual void MyMethod() override //virtual/override not required but important
    {
        Base::MyMethod(); 
    }

private:
    Base m_myObject; //Containment
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

/////////////////////////////////////////////////////////////////////////////////////
//VIRTUAL FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////

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

//NON-VIRTUAL INTERFACE IDIOM
//virtual functions in derived/base don't have to match
//Chosen visibility determined from type of pointer/reference used
//if virtual base function shouldn't be called, make it private
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

Base* base = &derived; //Uses base class visility: Cannot call MyMethod()
Derived* deri = &derived; //Uses derived class visibility: Can call MyMethod()

/////////////////////////////////////////////////////////////////////////////////////
//INHERITING DEFAULT VARIABLES
/////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////
//DATA HIDING
/////////////////////////////////////////////////////////////////////////////////////

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