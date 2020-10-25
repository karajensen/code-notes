/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C++ CODE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
C++11: Lambdas, move semantics
C++14: Generic lambdas
C++17: Fold expressions, structured bindings
C++20: Ranges, concepts
*************************************************************************************************************/

unsigned char         BYTE        ---
short                 ---         short int / signed short / signed short int
unsigned short        WORD        unsigned short int
int                   INT/BOOL    signed 
unsigned int          UINT        unsigned
long                  ---         long int / signed long / signed long int
unsigned long         ULONG       unsigned long int
long long             ---         long long int / signed long long / signed long long int
unsigned long long    DWORD       unsigned long long int
float                 FLOAT       ---

// CSTRINGS
char cstring = 'C';                        // content modifiable, single character
char cstring[256];                         // content modifiable, character buffer
char cstring[] = "string literal";         // content modifiable, \0 auto added
char cstring[] = {'h','i','\0'};           // content modifiable
char* str = &cstring;                      // content/pointer modifiable
char* const str = &cstring;                // content modifiable, pointer constant
const char* str = "string literal";        // pointer modifiable, content constant, \0 auto added
const char* const str = "string literal";  // content/pointer constant, \0 auto added
constexpr char* str                        // Same as char* const, Error
constexpr const char*                      // Same as const char* const str
    
// STRING LITERAL MODIFIERS
const auto* str = R"(Raw string literal)" // anything between the() doesn't need to be escaped
const auto* str = u8"UTF-8 string literal"
const auto* str = u"UTF-16 string literal"
const auto* str = U"UTF-32 string literal"
const auto* str = L"Wide-string literal"

// ARRAYS
// Must be constant size, initialises first two values, sets rest to 0
int myArray[9] = { 1, 2 };

// 2D ARRAYS
// Must be constant size, 2 rows, 2 columns
// Memory layout is row-major: [1 | 2 | 3 | 4] in continuous block
int myArray[2][2] = {{1, 2}, {3, 4}};

// SIZES
sizeof(myInt)                 // gives size of myInt in bytes
sizeof(myObj)                 // gives size of class in bytes
sizeof(myArray)               // gives number of elements for array
sizeof(myCString)             // gives characters in string + \0
sizeof("string literal")      // gives characters in string + \0, if const* used, gives size of pointer
sizeof(myPointer)             // gives size of the pointer in bytes
sizeof(myRef)                 // gives size of object referenced in bytes
extent<int[3]>::value         // gives number of elements 3
extent<decltype(arr)>::value  // gives number of elements for array

// INCREMENTING
b = ++a    // increment a and then use it (before anything else)
b = a++    // use a and then increment it (after everything including assigment)
++++++i;   // OKAY: parsed as (++(++(++i)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLE MODIFIERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
CONST VARIABLES
• String constants and floating point constants are stored in static memory in optimized code
• Integer constants are usually included as part of the instruction code
• If type unknown or is refered to, may be stored in fixed seperate memory/data segment
• Variable const-casted remains in same location but cannot change values
• Cannot use move operations on const variables
**************************************************************************************************************/

register    // May store variable in register, not on stack, no address and can't be global
volatile    // Don't cache or optimize value, can prevent cache race conditions
mutable     // Value changes ignored for bitwise const checking; used to show internal synchronization
const       // Can store variable in read-only memory or value repaced at compile time
constexpr   // Evaluates at compile time, will store in read-only memory
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLE INITIALISATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
ZERO-INITIALISATION
• All Static variables before main()
• POD types after default constructor is called
    - MyPOD obj = {};
    - MyPOD[2] array = {};
    - MyPOD* obj = new MyPOD{};
    - MyPOD obj = MyPOD();
    - MyPOD* obj = new MyPOD();
• POD type members that are not user initialised in {}
    - MyPOD obj = { 5 };
    - MyPOD[2] array = { 5 };
    - MyPOD* obj = new MyPOD{ 5 };
**************************************************************************************************************/

Type x                        // Default constructor
Type x(y) /*or*/ Type x = y   // Copy constructor
Type x(5) /*or*/ Type x = 5   // Conversion constructor (second not possible with explicit keyword)
Type x{5} /*or*/ Type x = {5} // List constructor else conversion constructor; POD: auto initialises other members to 0
Type x{}  /*or*/ Type x = {}  // Default constructor; POD: auto initialises all members to 0
Type x = Type()               // Default constructor; POD: auto initialises all members to 0
Type[5] x = {}                // Default constructor; POD: auto initialises all members to 0
Type x({})                    // Default constructor; Requires user-defined default constructor else compile error
Type x()                      // Most vexing parse: compiles as function declaration
Type x(Type2(y))              // Most vexing parse: compiles as function declaration
Type x((Type2(y)))            // Extra () shows not function declaration
Type x(Type2(5))              // Using temp var shows not function declaration
5 + 1;                        // Temporary value on left side allowable but doesn't do anything

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SEQUENCE POINTS / ORDER OF EVALUATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Undefined behaviour when changing a variable and reading it again without a sequence point.
• After a function's returned object has been copied back to the caller
• After evaluation of all a function's parameters when the function is called
• After the initialization of each base and member for an object
;       int x = 0;
,       f(x,y) 
||      x || y 
&&      x && y 
?:      x ? y : 0 
**************************************************************************************************************/

// BAD SEQUENCE POINTS
i++ * ++i; // BAD: i is modified more than once
i = ++i    // BAD: i is modified more than once
++i = 2;   // BAD: i is modified more than once

// COMMA-SEPERATION
int x = a, b;      // a assigned to x, b assigned to nothing
int x = (a, b);    // a assigned to nothing, b assigned to x
int x = a, y = b;  // a assigned to x, b assigned to y (both new vars)

// FUNCTION PARAMETERS
// Compilier specific, callFunc(getA(), getB()); can either be:
int a = getA();           int b = getB();
int b = getB();  /*OR*/   int a = getA();
callFunc(a, b);           callFunc(a, b);

// INITIALISER LIST
// In order, callFunc({getA(), getB()}); will be:
int a = getA();
int b = getB();
callFunc({a, b});

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CASTING
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MOVE SEMANTICS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
TEMPORARY VARIABLES
• Move semantics reduces creation of temp variables
• Value-typed variables auto created on the stack during:
   - reference initialization
   - expression evaluation
   - automatic type conversion
   - function passing/returning if no move constructor

• Allows resources to transfer between objects rather than copying
• Automatically done if object has a valid move assignment/constructor
• All function parameters are lvalue even if initialised with an rvalue
• Don't use with const objects: move becomes copy operation
**************************************************************************************************************/

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
// STRUCTURED BINDINGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Can't be used with unions
• Can be used with c-array, struct, class, std::pair, std::tuple, std::array
• All members must be public and in brackets, works with public inheritance
**************************************************************************************************************/
struct MyStruct { int x; const char y[3]; };
auto [x, y] = myStruct; // creates hidden copy of myStruct, x/y types stay the same (no decay)
auto& [x, y] = myStruct; // creates hidden reference to myStruct
auto [a, b, c] = myStruct.y; // Copies array, cannot be decayed array pointer or dynamic array
auto [x, y] {myStruct};
auto [x, y] (myStruct);
auto [x, y] = MyStruct{};
for (const auto& [key, value] : myMap) {}
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Only hold one variable type at a time; shares same memory location
// The size of that spot is determined by the largest variable
// Can be used to access a variable in multiple ways
// Cannot use inheritance, virtual functions

union MyUnion
{
    //can have user defined constructor
    MyUnion() : myInt(0) { }

    //can have member functions
    Void MyFn() { }
    
    unsigned int myInt;
    double myDouble;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENUMERATIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MyEnum                 // Unscoped enum, type chosen by compilier 
enum MyEnum : int           // Unscoped enum with fixed underlying type
enum class MyEnum           // Scoped Enum with auto fixed underlying type as int
enum class MyEnum : short   // Scoped Enum with fixed underlying type
{
    ONE,           // Value = 0
    TWO = 100,     // Value = 100
    THREE,         // Value = 101
    FOUR = 0,      // Value = 0
    FIVE           // Value = 1
}

// SCOPED/UNSCOPED ENUM
double ONE = 2.0;  // Error for unscoped enum as it pollutes the namespace
auto value = static_cast<MyEnum>(2); // Both require cast from int to enum
int value = myEnum; // Unscoped auto cases from enum to int, scoped requires static cast

// FIXED UNDERLYING TYPE ENUMS
// Enums without fixed underlying type can only be cast to values between min->max of enum
// Enums with fixed underlying type can only be cast to values between min->max of type
auto value = static_cast<MyEnum>(-1); // Undefined for enums without fixed underlying type
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BIT FIELDS
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
// LOOPING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FOR LOOP
// Never use unsigned int when looping backwards to 0
// unsigned int overflow wraps to 0, signed int overflow is undefined
// When decrementing past zero the unsigned int will cycle over
// All except the initial assigment will recompute each iteration
for (int i = 0; i < 5; ++i){}
for (int i = 0, int j = 2; i < j; i = i + 15, j-- ){}

//FOR EACH LOOP
// Only computes expression after : once
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
// BRANCHING/LOGIC
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
// FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RETURN VALUE OPTIMIZATION(RVO)
// If possible, a returned local var is constructed in memory allocated for function's return value
// If not possible, a returned local var is treated as rvalue (automatically uses std::move)
// Using std::move / std::foward explicitly will prevent RVO for ever occuring
// Only use std::move / std::foward on return if returning by - value a T && (or else copy will occur)
MyClass MyFn() { MyClass obj;  return obj; }

// MAIN ENTRY FUNCTION
// argc is number of arguments, including the string used to invoke the program
// argv is array of arguments, including the string used to invoke the program
// must be called main or winmain
int main(int argc, char* argv[]){ /*no return auto returns 0 (success)*/ }

// PASSING C-STRING
// Use strlen to get the length of string up to '\0'
void MyFn(const char* str);

// PASSING C-ARRAYS
// int arr[x] is a suggestion, the x isn't enforced and arr[3] could be passed to an arr[6]
// Use pass-by-ref to enforce array size, otherwise require size to be parameter
// if arr[] decays to a int*, sizeof(arr) gives size of the pointer, not array
void MyFn(int arr[6])    /*==*/  void MyFn(int arr[]) // decays to pointer
void MyFn(int arr[2][3]) /*==*/  void MyFn(int arr[][]) // decays to pointer
void MyFn(int(&arr)[6])  /*OR*/  void MyFn(int arr(&)[6])
template<int n> void MyFn(char(&arr)[n]) // array of any size
void MyFn(int* arr, int size) // decays to pointer

// INLINE FUNCTIONS
// Function call is replaced by function body
// Compiler ultimately decides what is inlined
// If in.h any internal static members are shared between files
// May increase program size unless a very small inlined function
// Large inlined functions used alot can increase execution time due to caching
// Increases build time as all uses need to be recompiled rather than just relinked
inline void MyFn(int x){}

// C-VARIADIC FUNCTION
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

// DEFAULT VALUES
void MyFn(int x, int y = 0);        // constant, parameters must be right to left
void MyFn(int x = Fn(5));           // Non-member function with constant arguments
void MyFn(int x = Fn(global));      // Non-member function with global variable
void MyFn(int x = Fn(m_static));    // Non-member function with static member variable
void MyFn(int x = StaticFn());      // Static member function
void MyFn(int x = (global==0?1:2))  // Ternary expressions
void MyFn(int x = m_member)         // CANT DO: can't use non-static class members

// CONTEXPR FUNCTIONS
// All arguments constexpr then computed at compile time, else computed at runtime
constexpr int MyFn(int x){ return x; }
MyFn(2); //computed at compiletime
MyFn(y); //computed at runtime unless y is constexpr

// TRAILING RETURN TYPE
// shifts the return type to after the function arguments
double MyFn(int x, int y) {} /*or*/
auto MyFn(int x, int y) -> double {}
auto MyFn(int x, int y) -> decltype(x) {} // make return type same as x
auto MyFn(MyCallback fn, int x) -> decltype(fn(x)) { return fn(x)); }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION OVERLOADING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
REQUIRES SIGNATURE DIFFERENCE
• Type of parameters
• Number of parameters
• Const or non-const reference/pointers

OVERLOAD RESOLUTION ORDER
• Template functions never implicitly cast
• Prefer exact non-template type over template
• Implicit casting always last priority, never explicitly casts
• Uses SFINAE: substitution failure is not an error where the compilier
  can reject template types without throwing any errors
**************************************************************************************************************/

FN(1.0F, 1.0F)
1) Non-template Exact type                        void Fn(float x, float y)
2) Template Explicit Specialization Exact type    template <> void Fn(float x, float y) [requires 3]
3) Template Overloads with Exact type             template <typename T> void Fn(T x, float y)
OR Template Overload                              template <typename T> void Fn(T x, T y)
5) Primary Template                               template <typename T, typename S> void Fn(T x, S y)
6) Non-template with Implicit conversion          void Fn(float x, double y)

FN<FLOAT>(1.0F, 1.0F)
1) Template Explicit Specialization Exact type    template <> void Fn(float x, float y) [requires 2]
2) Template Overloads with Exact type             template <typename T> void Fn(T x, float y)
OR Template Overload                              template <typename T> void Fn(T x, T y)
3) Primary Template                               template <typename T, typename S> void Fn(T x, S y)
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NAMESPACES / ALIASES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace /*anon*/ {}
namespace MySpace {}
MySpace::MyVariable = 3;
using namespace MySpace;
using namespace MySpace::MyFunction();

//ALIAS DECLARATION
typedef int myType;
typedef decltype(x) myType;
using myType = int;

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
// STATIC / GLOBAL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
STATIC VARIABLES
• Variables with static storage duration:
    - Global variables: Doesn't require 'static' keyword
    - Class member variables: Require 'static' keyword
    - Local variables: Require 'static' keyword
• All static variables zero-initialisated or initialised to constant before main() called
• If dynamic initialisation is required, can be initialised any time between main() 
  and first use of variable (or object if class member)

GLOBAL VARIABLES
• Defined outside function or class scope
• Have static storage duration
• Automatically has 'static' keyword unless 'extern' keyword is used, can't have both
• If same named non-extern static and extern variable exist then error
          -------------------------------------------
          | static int x      |                     |
          | int x             | extern int x        |
-----------------------------------------------------
|         | creates copy for  | References extern   |
| .H      | every #include    | version in .cpp     |
|         |                   |                     |
| .CPP    | creates only one  | Definition for any  |
|         | for .cpp use      | .h extern versions  |
|         |                   |                     |
| Linkage | Internal          | External            |
|         | Single use        | Shared use          |
-----------------------------------------------------
**************************************************************************************************************/

static      // Makes static storage, can be used on local, global or class member variable
extern      // References (in .h) or declares (in .cpp) an externally linked global variable    
::myInt     // Allows access to global variables when shadowed by local variables

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PREPROCESSOR MACROS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream> 
#include "header.h" // using "", compiler searches in same location as source first

// INCLUDE GUARDS
#ifdef DEFINED
#if defined(DEFINED) || defined(MYCLASS_H_)
#ifndef MYCLASS_H_
#define MYCLASS_H_
#define MACRO(A) ((A)+(A)) //use parathesis around any parameters 
#endif
#pragma once //Alternative to include guards      

// DISABLE WARNINGS
#pragma warning(push)           
#pragma warning(disable:4512)
#pragma warning(pop)       

// DISABLE OPTIMIZATION
#pragma optimize("", off)
#pragma optimize("", on)

// MACROS OVER MULTIPLE LINES
// Proper way: doesn't break if user does if-else without {}
#define MYMACRO(a, b) \
    do { 
        statement1; \
        statement2; \
    } while (false) //intentially don't put ; so it can be used anywhere

// CHANGING PACKING OF STRUCT
// changes amount of bytes allocated at a time (ie, default 4 to 1)
#pragma pack(push,1) 
struct CStruct
{
    char c;
    int i;
    bool b;
};
#pragma pack(pop)

// CHANGE STATIC INIT ORDER
#pragma init_seg(lib) // Any statics in file will be initialised first

// TRIGRAPH
// Replaced at preprocessor stage, disabled VS, deprecated c++17
??=  /*replaced with*/  #
??/  /*replaced with*/  \
??’  /*replaced with*/  ^
??(  /*replaced with*/  [
??)  /*replaced with*/  ]
??!  /*replaced with*/  |
??<  /*replaced with*/  {
??>  /*replaced with*/  }
??-  /*replaced with*/  ˜
