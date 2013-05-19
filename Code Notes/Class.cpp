//////////////////////////////////////////////////////////////////////////////
//WRITING CLASSES
//////////////////////////////////////////////////////////////////////////////

class Test
{
private:

    static const int m_testint = 20;
    static int teststatic; 
    const int testconstint; //initialise through initialisation list
    int testint;

    enum{ AMOUNT=3 };
    int myArray[AMOUNT];

public:

    virtual ~Test();
    Test(int n, int x, double y = 0); 
    Test(const Test & c);               //copy constructor
    Test(Test && c);                    //move constructor
    Test& operator=(const Test & x);    //assignnment operator
    Test& operator=(Test && x);         //move assignment operator
    operator double();                  //cast operator
    static int TestFunction(int x); 
    void TestFunction() const;
    explicit Test(float f);  //single argument constructor
};

//============================================================================
//STATIC MEMBERS
//============================================================================
int Test::teststatic = 0;
int Test::TestFunction(int x) //static method
{
    return Test::teststatic; //can only return static private members, 
}
//============================================================================
//CONSTRUCTOR
//============================================================================
Test::Test(int n, int x, double y = 0): 
    testconst1(x), 
    testconst2(y)
{}

//============================================================================
//DESTRUCTOR 
//============================================================================
Test::~Test(){}

//============================================================================
//COPY CONSTRUCTOR
//============================================================================
Test::Test(const Test & c)
{
    this.somevariable = c.somevariable; //copy over values
}

//============================================================================
//ASSIGNMENT OPERATOR
//============================================================================
Test & Test::operator=(const Test & x)
{
    if(&x == this){ return *this; }     //check not copying self
    this.somevariable = x.somevariable; //copy over values
    return *this;
}

//============================================================================
//SINGLE ARGUMENT CONSTRUCTOR
//============================================================================
//using explicit stop implicit conversions from taking place
//otherwise works similar to a cast operator
explicit Test(double x); 
Test::Test(double x) {} 

object.TestClass(4.3) /*or*/ TestClass object(4.3)
object = 4.3 /*or*/ object = TestClass(4.3)

//with explicit
object.TestClass(4.3) /*okay*/      
object = 4.3          /*okay but converts object to a double implicitly*/

//without explicit
object.TestClass(4.3) /*okay*/      
object = 4.3          /*prevented*/

//============================================================================
//MOVE CONSTRUCTOR
//============================================================================
//Uses Move Semantics; allows resources to transfer between objects
//Requires overloaded operators to allow temp objects
//Doesn't take const as it modifies rvalue passed in
Test::Test(Test && x):
    myPointer(std::move(x.myPointer),
    myInt(std::move(x.myInt)
{}

Test object(obj1 + obj2); //obj1+obj2 creates a temp r-value
Test object(std::move(obj1)); //converts obj1 to a r-value

//============================================================================
//MOVE ASSIGNMENT OPERATOR
//============================================================================
//Doesn't take const as it modifies rvalue passed in
Test & Test::operator=(Test && x)
{
    if(this == &x)
        return *this;
    delete [] myPointer; //delete any dynamic allocation for object
    myInt = x.myInt;
    x.myInt = 0;
    myPointer = x.myPointer; //steal the address
    x.myPointer = nullptr; //set to null
    return *this;
}
obj1 = obj2+obj3; //obj2+obj3 creates a temp r-value
obj1 = std::move(obj2); //converts obj2 to a r-value


//////////////////////////////////////////////////////////////////////////////
//CREATING OBJECTS 
//////////////////////////////////////////////////////////////////////////////

//DEFAULT CONSTRUCTOR PITFALL
ONE one(); //sees as function declaration, fixed by ONE one;

//CONSTRUCTOR INSIDE CONSTRUCTOR PITFALL
ONE one(TWO(x)); //can't be done; thinks it's a function declarion
ONE one(TWO(3)); //can be done; realises it's object creation
ONE one((TWO(x))); //can be done; realises it's object creation
ONE one(two); //where two = TWO(x) can be done


//////////////////////////////////////////////////////////////////////////////
//TYPES OF CLASSES
//////////////////////////////////////////////////////////////////////////////

//=========================================================================
//STRUCTURES
//=========================================================================
struct mystructure
{
    int x = 5;
    float y;
    mutable char charstruct[20];
}; 

//creating a new object from mystructure
mystructure test = {32, 23.1, "hello"}; 

//creating array of structures
mystructure arraytest[2] = 
{
    {32, 23.1, "hello"}, //initialise arraytest[0]
    {23, 34.1, "goodbye"} //initialise arraytest[1]
};

//=========================================================================
//AGGREGATES
//=========================================================================
//NO: Constructors, virtual, private/protected members
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
Aggregate a = {3}; //can be initialized with {}

//=========================================================================
//PLAIN OLD DATA (POD)
//=========================================================================
//NO: Constructors, virtual, private/protected members
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
Aggregate a = {3}; //can be initialized with {}


//////////////////////////////////////////////////////////////////////////////
//OVERLOADING/OPERATORS
//////////////////////////////////////////////////////////////////////////////

//USING OVERLOADS
class1*class2 /*->*/ class1.operator*(class2);
class1+class2 /*->*/ class1.operator+(class2);
class1[4]     /*->*/ class1.operator[](4) 
class1[0][1]  /*->*/ (class1[0].operator[](1)).operator[0];


//OVERLOAD DECLARATIONS
Date& operator++(); //prefix
Date& operator--(); //prefix
Date operator++(int unused); //postfix
Date operator--(int unused); //postfix
const TestClass operator+(const Testclass & x) const;
const TestClass operator*(const Testclass & x) const;
TestClass& operator[](const int i);
const TestClass& operator[](const int i) const;

void* operator new(std::size_t);                            //plain new
void* operator new(std::size_t, std::nothrow_t) throw();    //nothrow new
void* operator new(std::size_t, void*);                     //in-place new

//--------------------------------------------------------------------------
//OVERLOADS WITH DIFFERENT TYPES AS ARGUMENTS
//--------------------------------------------------------------------------

//USING FRIENDS COUPLED WITH OVERLOADED OPERATOR
A = B * 2.75 /*->*/ A = B.operator*(2.75);
const Testclass operator*(const double x) const;

A = 2.75 * B /*->*/ A = operator*(2.75, B); 
friend const Testclass operator*(const double x, const Testclass & t) const;

//--------------------------------------------------------------------------
//OVERLOADS COUT 
//--------------------------------------------------------------------------
friend std::ostream & operator<<(std::ostream & os, const Testclass & t); 
std::ostream & TestClass::operator<<(std::ostream & os, const Testclass & t)
{
    os << t.testint;
    return os;
}
cout << A << B;

//--------------------------------------------------------------------------
//CAST OPERATOR
//--------------------------------------------------------------------------
operator double(); //typecast prototype (must be method)
Testclass::operator double()
{
    return mydouble; //returns double even without return type
}
double x = class1; //implicitly
double x = double(class1); //explicitly

//CAST OPERATOR FOR CUSTOM TYPES
operator FLOAT3();
MATRIX::operator FLOAT3()
{
    return FLOAT3(1,2,4);
}
FLOAT3 vec = FLOAT3(mat);


//////////////////////////////////////////////////////////////////////////////
//FRIENDS
//////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
//FRIEND FUNCTIONS
//--------------------------------------------------------------------------
class B; //forward declaraction, lets compiler understand the B::amethod()

class A
{
private:
public:
    friend void B::amethod(); 
};

class B
{
private:
public:
    void B::amethod();
};
//--------------------------------------------------------------------------
//FRIEND CLASSES
//--------------------------------------------------------------------------
class A
{
private:
public:
    friend class B; //doesn't matter where defined- public/private/protected
};

class B
{
private:
public:
};

//////////////////////////////////////////////////////////////////////////////
//PREVENTING COPYING
//////////////////////////////////////////////////////////////////////////////

//MANUALLY: gives linker error if copying
class Game
{

private:

    //use declarations only
	Game(const Game); 
	Game& operator=(const Game);
};

//USING BOOST: gives compile error due to using base class
#include <boost/noncopyable.hpp>
class Game : boost::noncopyable //inherits privately
{ ... }


//////////////////////////////////////////////////////////////////////////////
//CLASS DYNAMIC MEMORY
//////////////////////////////////////////////////////////////////////////////

//USING THE COPY-SWAP IDIOM FOR DEEP COPYING
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
    friend void swap(Array& first, Array& second)
    {
        std::swap(first.size, second.size); 
        std::swap(first.arr, second.arr);
    }

    //ASSIGNMENT OPERATOR
    //take parameter by-val to use copy constructor
    Array& operator=(const Array other)
    {
        swap(*this, other);
        return *this;
    } 
};