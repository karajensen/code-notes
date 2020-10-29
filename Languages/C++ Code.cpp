/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C++ CODE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
C++11: Lambdas, move semantics
C++14: Generic lambdas
C++17: Fold expressions, structured bindings
C++20: Ranges, concepts
*************************************************************************************************************/

unsigned char              BYTE        ---
short                      ---         short int / signed short / signed short int
unsigned short (U)         WORD        unsigned short int
int                        INT/BOOL    signed 
unsigned int (U)           UINT        unsigned
long (L)                   ---         long int / signed long / signed long int
unsigned long (UL)         ULONG       unsigned long int
long long (LL)             ---         long long int / signed long long / signed long long int
unsigned long long (ULL)   DWORD       unsigned long long int
float                      FLOAT       ---
long double (L)            ---         ---

// CSTRINGS
char cstring = 'C';                        // content modifiable, single character
char cstring[256];                         // content modifiable, character buffer
char cstring[] = "string literal";         // content modifiable, \0 auto added
char cstring[] = {'h','i','\0'};           // content modifiable
char* str = "string literal";              // content/pointer modifiable, \0 auto added
char* const str ="string literal";         // content modifiable, pointer constant, \0 auto added
const char* str = "string literal";        // pointer modifiable, content constant, \0 auto added
const char* const str = "string literal";  // content/pointer constant, \0 auto added
constexpr char* str                        // Same as char* const
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

// NAMESPACES
namespace /*anon*/ {}
namespace A {}
namespace A::B {} // same as namespace A { namespace B {} }
using namespace MySpace;
::myInt // Allows access to global variables when shadowed by local variables

// VARIABLE ALIASES
typedef int myType;
typedef decltype(x) myType;
using myType = int;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLE MODIFIERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
CONST VARIABLES
• String constants and floating point constants are stored in static memory in optimized code
• Integer constants are usually included as part of the instruction code
• If type unknown or is refered to, may be stored in fixed seperate memory/data segment
• Variable const-casted remains in same location but cannot change values
• Cannot use move operations on const variables (will copy them instead)

STATIC VARIABLES
• Variables with static storage duration:
   - Global variables: Doesn't require 'static' keyword
   - Class member variables: Require 'static' keyword
   - Local variables: Require 'static' keyword
**************************************************************************************************************/

register    // May store variable in register, not on stack, no address and can't be global
mutable     // Value changes ignored for bitwise const checking; used to show internal synchronization
volatile    // Don't cache or optimize value, can prevent cache race conditions
const       // Can store variable in read-only memory or value repaced at compile time
constexpr   // Evaluates at compile time, will store in read-only memory
inline      // Ensures there is only one definition even if included in multiple places
static      // Variables with static storage duration
extern      // References (in .h) or declares (in .cpp) an externally linked global variable    
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLE INITIALISATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
Direct initialization: Type x{}
Copy initialization: Type x = {}

STATIC-INITIALIZATION
• All static variables zero-initialisated or initialised to constant before main() called
• If dynamic initialisation is required, can be initialised any time between main() 
  and first use of variable (or object if class member)

ZERO-INITIALISATION
Auto initializes to 0 (false / nullptr) for:
• All Static variables before main()
• Aggregates (array, struct, class, pair, tuple) after default constructor is called
• Aggregates type members that are not user initialised in {}
**************************************************************************************************************/
    
Type x                      // Default constructor
Type x(y) / Type x = y      // Copy constructor
Type x(5) / Type x = 5      // Conversion constructor (second not possible with explicit keyword)
Type x{5} / Type x = {5}    // List constructor, Conversion constructor or Aggregate init
Type x{}  / Type x = {}     // Default constructor or Aggregate init
Type x = Type()             // Default constructor or Aggregate init
Type[5] x = {}              // Default constructor or Aggregate init
Type x({})                  // Default constructor, requires user-defined default constructor else compile error
Type x()                    // Most vexing parse: compiles as function declaration
Type x(Type2(y))            // Most vexing parse: compiles as function declaration
Type x((Type2(y)))          // Extra () shows not function declaration
Type x(Type2(5))            // Using temp var shows not function declaration
    
// AGGREGATE INITIALISATION
// Aggregates types only (array, struct, class, pair, tuple)
Type x{}  / Type x = {}      // All members zero initialized
Type x{5} / Type x = {5}     // Other members zero initialized
Type[5] x = {}               // All members zero initialized
Type[5] x = {5}              // Other members zero initialized
Type* x = new Type()         // All members zero initialized
Type* x = new Type{}         // All members zero initialized
Type* x = new Type{5}        // Other members zero initialized
Type x = Type()              // All members zero initialized
Type x{{"a", true}, 5};      // Initialize base members in inner {}
Type x{"a", true, 5};        // Inner {} not required
Type x{{}, 5};               // Default init base members
Type x{{}, {}, 5};           // Default init multiple inheritance base members

// AUTO INITIALISATION
// Type determined differs using copy/direct initialization
auto a{42};                  // initializes an int
auto c = {42};               // initializes a std::initializer_list<int> 
auto d = {1,2,3};            // initializes a std::initializer_list<int>

// STRUCTURED BINDINGS
// Aggregates types only (array, struct, class, pair, tuple)
// All members must be public (including those from inheritance) and in brackets
struct { int x; const char arr[3]; } obj;
auto [a, b] = obj;           // Creates hidden copy of obj, x/y types stay the same (no decay)
auto& [a, b] = obj;          // Creates hidden reference to obj
auto [a, b, c] = obj.arr;    // Copies array, cannot be decayed array pointer or dynamic array
auto [a, b] {obj};
auto [a, b] (obj);
auto [a, b] = obj{};
for (const auto& [key, value] : map) {}

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

// UNDERLYING TYPE ENUMS
// Enums without fixed underlying type can only be cast to values between min->max of enum
// Enums with fixed underlying type can only be cast to values between min->max of type
auto value = static_cast<MyEnum>(-1); // Undefined for enums without fixed underlying type
MyEnum myEnum{5} // Underlyng type enums can only use, but cannot use = {5}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BRANCHING / LOOPING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SHORT CIRCUITING EVALUATION
if(myObj && myObj.Fn() == 2) // checks first and only checks next if first is true
if(myObj || myObj.Fn() == 2) // checks first, if not true will check second else not check second

// IF-THEN-ELSE
if (myBool) {} else if (myBool2) {} else {}
if (auto x = fn()) {} else {} // result scoped to if only, needs to eval to bool
if (auto x = fn(), y = 0; x == y) {} else {} // result scoped to whole block, same as 'for' syntax
if (std::lock_guard<std::mutex> lg{mutex}; str.empty()) {}

// COMPILE-TIME-IF
// During compilation unused branches discarded
// Doesn't short circuit, all conditions evaluated
if constexpr(myBool) {} else if constexpr(auto x = fn()) {} else {}

// TERNARY OPERATOR
int value = (a < b) ? a : b;
obj->Exists() ? obj->DoSomething() : throw ("exception");
(a == 0 ? a : b) = 1; // if(a == 0) a = 1 else b = 1

// SWITCH STATEMENTS
// can have nothing inside the switch statement or just default
// break is needed to stop switch from executing code after each case
// CAN'T DO: Ranges, floating points, comparing two variables
switch(choice)
switch(auto x = fn(); x.choice) // result scoped to whole block, same as 'for' syntax
{
case 1: 
    break;
case 'a': 
case 'A': // do something for case 'a' and 'A'
    break;
case red: // can use enum names which are converted to ints
    break;
default:
};

// GOTO
goto label;
label:  //do something

// FOR LOOP
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
// FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RETURN VALUE OPTIMIZATION(RVO)
// If possible, a returned local var is constructed in memory allocated for function's return value
// If not possible, a returned local var is treated as rvalue (automatically uses std::move)
// Using std::move / std::foward explicitly will prevent RVO for ever occuring
// Only use std::move / std::foward on return if returning by-value a T&& (or else copy will occur)
int MyFn() { int x;  return x; }

// DEFAULT VALUES
void MyFn(int x, int y = 0);        // constant, parameters must be right to left
void MyFn(int x = Fn(5));           // Non-member function with constant arguments
void MyFn(int x = Fn(global));      // Non-member function with global variable
void MyFn(int x = Fn(m_static));    // Non-member function with static member variable
void MyFn(int x = StaticFn());      // Static member function
void MyFn(int x = (global==0?1:2)   // Ternary expressions
void MyFn(int x = m_member)         // CANT DO: can't use non-static class members
          
// TRAILING RETURN TYPE
// shifts the return type to after the function arguments
double MyFn(int x, int y) {} /*or*/
auto MyFn(int x, int y) -> double {}
auto MyFn(int x, int y) -> decltype(x) {} // make return type same as x
auto MyFn(MyCallback fn, int x) -> decltype(fn(x)) { return fn(x)); }

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
// Ensures there is only one definition: Any internal static members shared between files
// Suggestion to expand in-place, ultimately up to compilier
// May increase program size unless a very small inlined function
// Increases build time as all uses need to be recompiled rather than just relinked
inline void MyFn(int x) {}

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

// CONSTEXPR FUNCTIONS
// All arguments constexpr then computed at compile time, else computed at runtime
// Used if only literal types, no static variables, no virtual, no try/catch, no new/delete
constexpr int MyFn(int x) { return x; }
MyFn(2); // computed at compiletime
MyFn(y); // computed at runtime unless y is constexpr
          
// MAIN ENTRY FUNCTION
// argc is number of arguments, including the string used to invoke the program
// argv is array of arguments, including the string used to invoke the program
// must be called main or winmain
int main(int argc, char* argv[]){ /*no return auto returns 0 (success)*/ }
          
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION OVERLOADING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
Functions can be overloaded by
• Type of parameters
• Number of parameters
• Const or non-const reference/pointers

FUNCTION OVERLOAD RESOLUTION ORDER
• Template functions never implicitly cast
• Prefer exact non-template type over template
• Implicit casting always last priority, never explicitly casts
• Uses SFINAE: substitution failure is not an error where the compilier
  can reject template types without throwing any errors
**************************************************************************************************************/

fn(1.0f, 1.0f)
1) Non-template Exact type                        void fn(float x, float y)
2) Template Explicit Specialization Exact type    template <> void fn(float x, float y) [requires 3]
3) Template Overloads with Exact type             template <typename T> void fn(T x, float y)
OR Template Overload                              template <typename T> void fn(T x, T y)
5) Primary Template                               template <typename T, typename S> void fn(T x, S y)
6) Non-template with Implicit conversion          void fn(float x, double y)

fn<float>(1.0f, 1.0f)
1) Template Explicit Specialization Exact type    template <> void fn(float x, float y) [requires 2]
2) Template Overloads with Exact type             template <typename T> void fn(T x, float y)
OR Template Overload                              template <typename T> void fn(T x, T y)
3) Primary Template                               template <typename T, typename S> void fn(T x, S y)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ORDER OF EVALUATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
SEQUENCE POINTS
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

// INCREMENTING
b = ++a;   // increment a and then use it (before anything else)
b = a++;   // use a and then increment it (after everything including assigment)
++++++i;   // OKAY: parsed as (++(++(++i)))

// COMMA-SEPERATION
int x = a, b;      // a assigned to x, b assigned to nothing
int x = (a, b);    // a assigned to nothing, b assigned to x
int x = a, y = b;  // a assigned to x, b assigned to y (both new vars)

// ORDER OF EVALUATON
// a is guaranteed to be evaluated before b c++17 only
a[b]         a.b          a.*b         
a->*b        a << b       a >> b 
b = a        b += a       b *= a       
new Type(e) // Memory allocation guaranteed to happen before e c++17

// FUNCTION ORDER OF EVALUATION
// Compilier specific, callFunc(getA(), getB()); can either be:
int a = getA();           int b = getB();
int b = getB();  /*OR*/   int a = getA();
callFunc(a, b);           callFunc(a, b);

// INITIALISER LIST ORDER OF EVALUATION
// In order, callFunc({getA(), getB()}); will be:
int a = getA();
int b = getB();
callFunc({a, b});

// BAD SEQUENCE POINTS
i++ * ++i; // BAD: i is modified more than once
i = ++i;   // BAD: i is modified more than once
++i = 2;   // BAD: i is modified more than once
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES / FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Defined outside function or class scope
• Have static storage duration
• Variables auto have static unless extern / inline used
• Functions auto have extern unless inline used
**************************************************************************************************************/

// STATIC GLOBAL
// Header: creates copy for every #include (avoid)
// Cpp: creates only one
// Internal Linkage, single usage
int x;
static int x;
constexpr int x;

// EXTERN GLOBAL
// Header: references definition in cpp
// Cpp: Definition
// External Linkage, shared use
extern int x; 
void fn();

// INLINE GLOBAL
// Inline ensures there is only one definition, may expand in-place if simple fn
// Header: creates only one for every #include
// External Linkage, shared use
inline int x;
inline constexpr int x;
inline void fn() {};
constexpr void fn() {};  // Auto adds inline

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MOVE SEMANTICS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Allows resources to transfer between objects rather than copying
• Don't use with const objects: move becomes copy operation

             Expression can be
            /                 \
         glvalue             rvalue
  (Generalized lvalue)    (Right value)
      /            \       /          \
   lvalue           xvalue          prvalue
(Left value)   (Expiring value)   (Pure rvalue)
 
LVALUE: name of variable, function args, string literal, result of *ptr, function return by-ref (type&)
PRVALUE: literal value, nullptr, result of &var, result of x+y etc, function return by-val, lambdas, temporaries
XVALUE: function return by type&&, result of std::move
GLVALUE: xvalue or lvalue
RVALUE: xvalue or prvalue

TEMPORARY VARIABLES
• Move semantics reduces creation of temp variables
• Value-typed variables auto created on the stack during:
   - reference initialization
   - expression evaluation
   - automatic type conversion
   - function passing/returning if no move constructor   
**************************************************************************************************************/

4;               // prvalue
x;               // lvalue
std::move(x);    // xvalue
int&             // lvalue reference
int&&            // rvalue reference
auto&&           // universal reference
std::move        // unconditional cast to an r-value ref
std::forward     // conditional cast to an r-value reference

// PASSING ARGS
void fn(const int&);     // accepts any types
fn(x);                   // passes a modifiable lvalue
fn(constX);              // passes a non-modifiable lvalue

void fn(int&&);          // accepts prvalues and xvalues only
void fn(const int&&);    // possible to do but not generally used
fn(x());                 // passes a prvalue
fn(10);                  // passes a prvalue
fn(std::move(x));        // passes an xvalue
fn(std::move(constX));   // will do a copy despite move
          
void MyFn(std::string&& str) // str is lvalue inside function scope
{ 
    // use std::move to convert to rvalue to pass on
    myVec.push_back(std::move(str));
}

// AUTOMATIC MOVES
MyFn("str");                             // Passing rvalue to by-val function argument
std::string x = MyFn()                   // Returning local by-val unless Return Value Optimization occurs
string MyFn(std::string x){ return x; }  // Returning function argument by-val 
myVec.emplace_back("str")                // Emplacing rvalue/unique_ptr into container

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BIT MANIPULATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Bits go from least significant (b0) to most significant (bn-1) for n bits
• Bits read from left to right (little endian)
• Signed integers use most significant bit for +/-

BITWISE OPERATORS
~   bitwise NOT   Flips every bit                                   ~00000011 = 11111100
|   bitwise OR    For every bit if a or b have 1 then use 1         00000011 | 00000100 = 00000111
&   bitwise AND   For every bit if a and b have 1 then use 1        00000011 & 11111101 = 00000001
^   bitwise XOR   If a or b (but not both) have 1 then use 1        00000011 ^ 00000001 = 00000010
<<  left shift    Moves all bits to the left, adds 0 to the start   10000011 << 3 = 00011000
>>  right shift   Moves all bits to the right, adds 0 to the end    10000011 >> 3 = 00010000
**************************************************************************************************************/

x = ∼x + 1                   // Negate a number (two's component)
x = ~x                       // Flip all bits in a number
on = x & (1 << b)            // Test if nth bit is on, b = n-1
x = x | (1 << b)             // Set the nth bit on, b = n-1
x = x & ~(1 << b)            // Set the nth bit off, b = n-1
x = x ^ (1 << b)             // Toggle the nth bit on/off, b = n-1
odd = x & 1                  // Test if x is even or odd number
pow2 = x && !(x & (x - 1))   // Test if x is a power of 2 number

// XOR PROPERTIES
a ^ b = c
c ^ a = b                    // Get access to b again
c ^ b = a                    // Get access to a again
a ^ a = 0
a ^ 0 = a
a ^ b ^ a = b

// BIT SHIFTING
1 << 3                       // Gives 2³
value <<= 3                  // Multiply value by 2³
value >>= 3                  // Divide value by 2³

// PACKING BITS
int i = (s1 << 16) | s2      // Storing 2 shorts in an int
short s1 = i >> 16           // Retrieve short 1
short s2 = i & 0xFFFF        // Retrieve short 2

// BITWISE WITH BOOL
bool b = bool1 & bool2       // Both are true
bool b = bool1 | bool2       // Either are true
bool b = bool1 ^ bool2       // Either are true but not both 
success &= HasSucceeded();   // Init success to true, will lock in false if something fails
success |= HasSucceeded();   // Init success to false, will lock in true if something succeeds

// BIT MASKING
value = value & ~Mask1       // Removing a mask
value = value | Mask1        // Adding a mask
value = value ^ Mask1        // Adding a mask
value & Mask1                // If true then has the mask (C++ only as non-zero integers auto convert to true)
(value & Mask1) == Mask1     // If true then has the mask

// BIT MASK VALUES
// If flags go above 1 << 30, must use unsigned int as underlying type and do 1U << 31
NoMask = 0     0x000    0x00000000    00000000    
Mask1  = 1     0x001    0x00000001    00000001    1 << 0    b0
Mask2  = 2     0x002    0x00000002    00000010    1 << 1    b1
Mask3  = 4     0x004    0x00000004    00000100    1 << 2    b2
Mask4  = 8     0x008    0x00000008    00001000    1 << 3    b3
Mask5  = 16    0x010    0x00000010    00010000    1 << 4    b4
Mask6  = 32    0x020    0x00000020    00100000    1 << 5    b5
Mask7  = 64    0x040    0x00000040    01000000    1 << 6    b6
Mask8  = 128   0x080    0x00000080    10000000    1 << 7    b7

// BIT FIELDS
// Can be tightly packed if declared together
// Type of a bit field can only be integral or enumeration type
// Cannot be a static member
struct
{
    unsigned char x : 3;  // 3-bits, allowed values 2^3 (0-7)
    unsigned char x : 6;  // 6-bits, allowed values 2^6 (0-31)
    unsigned char : 2;    // nameless means next 2-bits are padding
    unsigned char : 0;    // start a new byte (any remaining bits are padding)
};

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

// ATTRIBUTES
// Suggestion only
[[nodiscard]] int* fn() { return new int; }           // Function return value should be used
[[noreturn]] void fn() { throw; }                     // Function always throws an exception
[[deprecated]] void fn() {};                          // Function should be avoided                  
void fn([[maybe_unused]] int x)                       // Prevent warning if x is unused
switch (x) { case 0: [[fallthrough]] case 1: break; } // Show fallthrough case is intended
