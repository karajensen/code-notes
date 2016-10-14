/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static      // Makes static storage, can be used on local, global or class member variable
extern      // References (in .h) or declares (in .cpp) an externally linked global variable
register    // May store variable in register, not on stack, no address and can't be global
volatile    // Don't cache or optimize value, can prevent cache race conditions
mutable     // Value changes ignored for bitwise const checking; used to show internal synchronization
const       // Can store variable in read-only memory or value repaced at compile time
constexpr   // Evaluates at compile time, will store in read-only memory
::myInt     // Allows access to global variables when shadowed by local variables

//INITIALISING VARIABLES
Type x;                         // Default constructor
Type x = 5;                     // Conversion constructor
Type x(5);                      // User constructor
Type x(y); /*or*/ Type x = y;   // Copy constructor
Type x{5}; /*or*/ Type x = {5}; // Class Types: List constructor or Type(5) if can't implicitly convert
Type x{5}; /*or*/ Type x = {5}; // POD Types: auto initialises other members to 0
Type x{};  /*or*/ Type x = {};  // Default constructor; POD: auto initialises all members to 0
Type x = Type();                // Default constructor; POD: auto initialises all members to 0
Type[5] x = {};                 // Default constructor; POD: auto initialises all members to 0
Type x({});                     // Default constructor; requires defined constructor
Type x();                       // BAD: 'Most vexing parse' seen as function declaration
Type x(Type2(y));               // BAD: 'Most vexing parse' seen as function declaration
Type x((Type2(y)));             // Extra () shows not function declaration
Type x(Type2(5));               // Using temp var shows not function declaration
5 + 1;                          // Temporary value on left side allowable but doesn't do anything

//ALIAS DECLARATION
typedef int myType;   
typedef decltype(x) myType;
using myType = int;

//VARIABLE SIZES
sizeof(myInt)                 // gives size of myInt in bytes
sizeof(myObj)                 // gives size of class in bytes
sizeof(myArray)               // gives number of elements for array
sizeof(myCString)             // gives numbers of characters for string
sizeof(myPointer)             // gives size of the pointer in bytes
sizeof(myRef)                 // gives size of object referenced in bytes
extent<int[3]>::value         // gives number of elements 3
extent<decltype(arr)>::value  // gives number of elements for array

//VARIABLE INCREMENTING
b = ++a    // increment a and then use it (before anything else)
b = a++    // use a and then increment it (after everything including assigment)
++++++i;   // OKAY: parsed as (++(++(++i)))
i++ * ++i; // BAD: i is modified more than once
i = ++i    // BAD: i is modified more than once
++i = 2;   // BAD: i is modified more than once

//CSTRINGS
//Can change individual chars
char cstring = 'C';               // single character; can read/write
char cstring[256];                // character buffer, can read/write
char cstring[] = "mystring"       // the \0 is done automatically
char cstring[] = {'h','i','\0'};

//STRING LITERALS
//Constant string literal, read only, \0 automatic
//Cannot change individual chars
char* str = "mystring"
auto* str = R"(Raw string literal)" //anything between the() doesn't need to be escaped
auto* str = u8"UTF-8 string literal"
auto* str = u"UTF-16 string literal"
auto* str = U"UTF-32 string literal"
auto* str = L"Wide-string literal"

//ARRAYS
//must be constant size input
//initialises first two values, sets rest to 0
int myArray[9] = { 1, 2 };

//2D ARRAYS
//creates an arrow with 2 rows, 2 columns
//memory layout is row-major: [1 | 2 | 3 | 4] in continuous block
int myArray[2][2] 
{
    {1, 2},
    {3, 4}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MOVE SEMANTICS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int x =         // L-VALUES: Persisting variable on left side of assignment expression    
= 3;            // R-VALUES: Temporary variable on right side of assignment expression
int& x = y;     // L-VALUE REFERENCE
int&& x = y;    // R-VALUE REFERENCE
auto&& x = y;   // UNIVERSAL REFERENCE: requires type deduction, can bind to both rvalues/lvalue references
int&& MyFn()    // X-VALUE: R-Value reference function return
int MyFn()      // PR-VALUE: Non-reference function return

// PASSING AS ARGUMENTS
// Moving values should not be const or copy is made
void MyFn(std::string&& str)
{ 
    // str becomes an lvalue as a function argument even if initialised as rvalue
    // use std::move to convert to rvalue to pass on
    myVec.push_back(std::move(str));
}

// AUTOMATIC USES
MyFn("str");                            // Passing rvalue to by-val function argument
std::string x = MyFn()                  // Returning local by-val unless Return Value Optimization occurs
string MyFn(std::string x){ return x; } // Returning function argument by-val 
myVec.emplace_back("str")               // Emplacing rvalue/unique_ptr into container

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONVERSIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//C++ CAST                C-STYLE CAST
std::dynamic_cast         No equalivant
std::static_cast          (int)x   /*or*/ int(x)
std::reinterpret_cast     (int*)&x
std::const_cast           (int*)&cx

//SAFE CASTING
//dynamic_cast only pointers/references of classes with virtual functions; slowest cast
auto* myPtr = dynamic_cast<MyDerived*>(myBasePtr) // returns 0 if fail
auto& myObj = dynamic_cast<MyDerived&>(myBaseObj) // throws std::bad_cast if fail
auto* myPtr = static_cast<MyClass*>(myVoidPtr)    // use static for void*

//UNSAFE CASTING
auto* myPtr = reinterpret_cast<MyDerived>(myBasePtr) // only for pointers
auto* myPtr = static_cast<MyDerived*>(myBasePtr)
auto& myObj = static_cast<MyDerived&>(myBaseObject)

//REMOVING CONST
//converts const to non-const [only pointers]
//bad if variable is stored in read-only memory- use only if underlying type is non-const
auto* myPtr = const_cast<MyClass>(myPtr);

// STRING TO NUMBER
atoi("3")   //converts cstring to int
atof("3.0") //converts cstring to float

// NUMBER TO STRING
// Only for integers and floating types
// Gives large precision with no control
to_string(value);
to_wstring(value);

// NUMBER TO STRING: PRINTF/WPRINTF
// Can have buffer overruns, difficult to use with templates
char buffer[256];
std::sprintf(buf, "%d", myInt)
std::sprintf(buf, "%u", myUint) 
std::sprintf(buf, "%f", myDbl) 
std::sprintf(buf, "%f", myFloat) 

// STD::STRING TO CHAR*:
std::string str = "test";
std::vector<char> vec(str.size() + 1);
std::copy(str.begin(), str.end(), vec.begin());
vec[vec.size()-1] = '\0';
char* myCStr = &vec[0];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//UNIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Only hold one variable type at a time; shares same memory location
// The size of that spot is determined by the largest variable
// Can be used to access a variable in multiple ways
// Cannot use inheritance, virtual functions

union MyUnion
{
    MyUnion() : myInt(0) //can have user defined constructor
    {
    }

    unsigned int myInt;
    double myDouble;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ENUMERATIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// compiler replaces name with integer value when encountering it
enum class MyEnum
{
    ONE,           // Value = 0
    TWO = 100,     // Value = 100
    THREE,         // Value = 101
    FOUR = 0,      // Value = 0
    FIVE           // Value = 1
}

// UNSCOPED ENUM
// Underlying type chosen by compiler
double ONE = 2.0;                           // CAN'T DO: Pollutes namespace
MyEnum myEnum = static_cast<MyEnum>(myInt); // requires cast from int to enum
int myInt = myEnum;                         // auto casts from enum to int

// SCOPED (CLASS) ENUM
// Underlying type always int
// Has operator=, operator==, operator<
// can add own methods
double ONE = 2.0;                           // CAN DO: Does not pollute namespace
MyEnum myEnum = static_cast<MyEnum>(2);     // requires cast from int to enum
int myInt = static_cast<int>(myEnum)        // requires cast from enum to int

// UNDERLYING TYPE
// Can change for both scoped/unscoped
// Choose underlying type from #include <stdint.h>
enum MyEnum : std::uint8_t { ONE };
enum class MyEnum : std::uint32_t { ONE }; 

// SHARING NAMES
enum MyEnum1 { ONE };
enum MyEnum2 { ONE };
int x = MyEnum2::ONE; // Requires type only if enums clash

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BIT FIELDS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//• Can be tightly packed if declared together
//• Type of a bit field can only be integral or enumeration type
//• Cannot be a static member
struct
{
    unsigned char x : 3;  // 3-bits, allowed values 2^3 (0-7)
    unsigned char x : 6;  // 6-bits, allowed values 2^6 (0-31)
    unsigned char : 2;    // nameless means next 2-bits are padding
    unsigned char : 0;    // start a new byte (any remaining bits are padding)
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LOOPING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FOR LOOP
// Never use unsigned int when looping backwards to 0
// unsigned int overflow wraps to 0, signed int overflow is undefined
// When decrementing past zero the unsigned int will cycle over
// All except the initial assigment will recompute each iteration
for (int i = 0; i < 5; ++i){}
for (int i = 0, int j = 2; i < j; i = i + 15, j-- ){}

//FOR EACH LOOP
for (double x : myDoubleArray){ x += 1.0; }     //by-val
for (double &x : myDoubleArray){ x += 1.0; }    //by-ref
for (auto x : myVectorArray){ DoSomething(x); } //with stl containers
for (int x : {0,4,3,5,2,0}){ cout << x; }       //using initialisation list

//WHILE LOOP
while (name[i] != '\0') { i++; }

//DO WHILE LOOP
do { cin << n;} while (n != 7);

break;    //stops the loop
continue; //jumps to loop conditional- while, for etc.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BRANCHING/LOGIC
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SHORT CIRCUITING EVALUATION
if(myObj && myObj.Fn() == 2) // checks first and only checks next if first is true
if(myObj || myObj.Fn() == 2) // checks first, if not true will check second else not check second

//IF-ELSE
if (testint == 2) {}
else if (testint == 3) {}
else {}

//TERNARY OPERATOR
int value = (a < b) ? a : b;
obj->Exists() ? obj->DoSomething() : throw ("exception");
(a == 0 ? a : b) = 1; //if(a == 0) a = 1 else b = 1

//SWITCH STATEMENTS
//can have nothing inside the switch statement or just default
//break is needed to stop switch from executing code after each case
//CAN'T DO: Ranges, floating points, comparing two variables
switch(choice)
{
case 1 : 
    break;
case 'a' : 
case 'A' : //do something for case 'a' and 'A'
    break;
case red : //can use enum names which are converted to ints
    break;
default :
};

//GOTO
goto label;
label:  //do something

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//MAIN ENTRY FUNCTION
//argc is number of arguments, including the string used to invoke the program
//argv is array of arguments, including the string used to invoke the program
//must be called main or winmain
int main(int argc, char* argv[]){ /*no return auto returns 0 (success)*/ }

//PASSING C-STRING
//Use strlen to get the length of string up to '\0'
void MyFn(const char* str);

//PASSING C-ARRAYS
// int arr[x] is a suggestion, the x isn't enforced and arr[3] could be passed to an arr[6]
// Use pass-by-ref to enforce array size, otherwise require size to be parameter
// if arr[] decays to a int*, sizeof(arr) gives size of the pointer, not array
void MyFn(int arr[6])    /*==*/  void MyFn(int arr[])
void MyFn(int arr[2][3]) /*==*/  void MyFn(int arr[][])
void MyFn(int(&ref)[6])  /*OR*/  void MyFn(int ref(&)[6])
void MyFn(int* arr)

//INLINE FUNCTIONS
//Function call is replaced by function body
//If in .h any internal static members are shared between files
inline void MyFn(int x){}

//C-VARIADIC FUNCTION
MyFn("This is a %i %f test",2,3.0f);
void MyFn(char* text, ...)
{
    char buffer[256];
    va_list arguments;
    va_start(arguments, text);  //Parse the string for variables
    vsprintf_s(buffer, text, arguments); //Convert argument symbols to text
    va_end(arguments); //Store results in text
    cout << buffer;
}

//DEFAULT VALUES
void MyFn(int x, int y = 0);        // constant, parameters must be right to left
void MyFn(int x = Fn(5));           // Non-member function with constant arguments
void MyFn(int x = Fn(global));      // Non-member function with global variable
void MyFn(int x = Fn(m_static));    // Non-member function with static member variable
void MyFn(int x = StaticFn());      // Static member function
void MyFn(int x = (global==0?1:2))  // Ternary expressions
void MyFn(int x = m_member)         // CANT DO: can't use non-static class members

//CONTEXPR FUNCTIONS
//All arguments constexpr then computed at compile time, else computed at runtime
constexpr int MyFn(int x){ return x; }
MyFn(2); //computed at compiletime
MyFn(y); //computed at runtime unless y is constexpr

//TRAILING RETURN TYPE
//shifts the return type to after the function arguments
double MyFn(int x, int y) {} /*or*/
auto MyFn(int x, int y) -> double {}
auto MyFn(int x, int y) -> decltype(x) {} // make return type same as x
auto MyFn(MyCallback fn, int x) -> decltype(fn(x)) { return fn(x)); }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NAMESPACES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace /*anon*/ {}
namespace MySpace {}

MySpace::MyVariable = 3;
using namespace MySpace;
using namespace MySpace::MyFunction();

// ADDING NAMESPACE ALIAS
namespace MyAlias = MySpace;

// KOENIG LOOKUP
// When a function argument of class type (A::) is supplied
// complier will auto look at namespace of class type for matches
namespace A
{
    class MyClass;
    void MyFn(int x);
    void MyFn(MyClass& x);
}
namespace B
{
    void MyFn(int x){ MyFn(x); }                     // Will call itself as namespace A not in scope
    void MyFn(int x){ using namespace A; MyFn(x); }  // Error: ambiguous requires :: to set which one to call
    void MyFn(A::MyClass& x){ MyFn(x); }             // Error: auto adds 'using namespace A' when A::MyClass is added
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PREPROCESSOR MACROS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream> 
#include "header.h" //"" compiler searches in same location as source first
extern "C" { #include "header.h" }; //compile in C only

#ifdef DEFINED
#ifndef MYCLASS_H_
#define MYCLASS_H_
#define MACRO(A) ((A)+(A)) //use parathesis around any parameters 
#endif

#pragma once //Alternative to include guards      

//DISABLE WARNINGS
#pragma warning(push)           
 #pragma warning(disable:4512)
#pragma warning(pop)            

//MACROS OVER MULTIPLE LINES
//Proper way: doesn't break if user does if-else without {}
#define MYMACRO(a, b) \
    do { 
        statement1; \
        statement2; \
    } while (false) //intentially don't put ; so it can be used anywhere

//CHANGING PACKING OF STRUCT
//changes amount of bytes allocated at a time (ie, default 4 to 1)
#pragma pack(push,1) 
struct CStruct
{
    char c;
    int i;
    bool b;
};
#pragma pack(pop)

//VISUAL STUDIO CONSTANTS
_DEBUG
_MANAGED
__FILE__    //name of file
__LINE__    //current line number
__TIME__    //time file was compiled
__DATE__    //date file was compiled

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ERROR HANDLING
///////////////////////////////////////////////////////////////////////////////////////////////////////

assert(myPtr != nullptr); // break if myPtr is null
static_assert(myConstInt > 0, "MyMessage"); // must use constant values, asserts at compile time
throw("Message goes here");
exit(EXIT_FAILURE);

try 
{ 
    myFunction();
} 
catch(const std::exception& e)
{
    // Always catch by const reference
    // Reference is used instead of pointer to reduce the need to manage any memory at the catch position
    // Allocating memory for an exception through a pointer may not work if the exception is out of memory.

    cout << e.what() << endl;

    throw e; // throws a copy of e, splices off any derived type
    throw; //original exception is thrown again
}
catch (...) //catches anything
{
}

//EXCEPTION SPECIFICATIONS
//If exception type not on list is thrown, calls unexpected()
void MyFn(); //can throw anything
void MyFn() throw(const char*, std::exception&); //can only throw string or std::exception
void MyFn() throw(); //Doesn't throw excpetions, not optimized: keeps unwindable stack state always
void MyFn() noexcept; //Doesn't throw exceptions, optimizes: doesn't keep unwindable stack state if exception propagates

//UNEXPECTED EXPECTION
//If type wasn't explicitly thrown or on expected list: unexpected()->terminate()->abort()
unexpected() //calls terminate()
set_unexpected([](){}); //takes in void MyFunction()

//UNCAUGHT EXCEPTION
//If type was known but not caught: terminate()->abort()
terminate() //calls abort()
set_terminate([](){}); //takes in void MyFunction()
 
//EXCEPTIONS IN CONSTRUCTORS
MyClass::MyClass()
try : A()
    , B()
{
}
catch (...) // can't access class members in catch block
{
}

//CREATING CUSTOM EXCEPTION
class MyClass: public std::exception
{
public:
    virtual const char* what() const override { return "bad arguments"; } 
};

try 
{
    throw MyClass();
}
catch(const std::exception& e)
{
    cout << e.what() << endl;
}
