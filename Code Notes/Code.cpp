//////////////////////////////////////////////////////////////////////////////
//VARIABLES
//////////////////////////////////////////////////////////////////////////////

Edit.ConvertTabsToSpaces

int localVariable;
static int localStatic; //Local static: keeps variable in memory even when function exits
register int regInt; //may store variable in register not on stack: NO address, can't be global
volatile int volInt; //don't cache value, check actual value each time its asked for
mutable int mutInt; //value changes ignored for bitwise const checking, allows changes for const objects/methods

//GLOBAL VARIABLES
int myGlobalInt; //Global static: external linkage  (can be accessed via extern)
static int myGlobalInt; //Global static: internal linkage (can't be accessed via extern)
extern int myExternInt; //accesses global variables from another file
::myGlobalInt; //accesses global variables when shadowed by local variables

//AUTO VARIABLES
auto x = 0  //automatically chooses 'int' for x
decltype(y) myValue; //make myValue the same type as y
decltype(myFnt(y)) myValue; //make myValue same type as return of myFnt(y)

//TYPEDEF
typedef decltype(x) myType; //can use decltype with typedef
typedef int Item; //creates a new type of variable object of type int 
typedef bool Item; //bool will use 4 bytes if typedefined to something else

//VARIABLE SIZES
sizeof(myInt) //gives size of myInt in bytes
sizeof(myArray) //gives size of whole array rather than first element
sizeof(myCString) //size of whole char array
sizeof(myPointer) //Gives the size of the pointer

//VARIABLE INCREMENTING
b = ++a //increment a and then use it in expression; b = new value of a
b = a++ //use a in expression then increment it after; b = old value of a
++++++i;   // OKAY: parsed as (++(++(++i)))
i++ * ++i; // BAD: i is modified more than once
i = ++i    // BAD: i is modified more than once
++i = 2;   // BAD: i is modified more than once

//////////////////////////////////////////////////////////////////////////////
//REFERENCES
//////////////////////////////////////////////////////////////////////////////

int x //L-VALUES: Persisting variable on left side of assignment expression    
3+1   //R-VALUES: Temporary variable on right side of assignment expression
3+1   //Temporary value on left side allowable but doesn't do anything

//STORING R-VALUES INTO L-VALUES
int x = 3+1; int & x = 3+1; //3+1 creates temp value, temp is assigned to x, temp is deleted
int && x = 3+1; //3+1 creates temp value, x references temp
void foo(int&& t); //t is initialised with r-value but is l-value itself

//FUNCTION RETURNS
int   prvalue();
int&  lvalue();
int&& xvalue();

//////////////////////////////////////////////////////////////////////////////
//C-STYLE ARRAYS/STRINGS
//////////////////////////////////////////////////////////////////////////////

//CSTRINGS
char cstring = 'C'; //single character; can read/write
char cstring[256]; //character buffer, can read/write
char* cstring = "mystring" //Constant string literal, read only, \0 automatic
char cstring[] = "mystring" //the \0 is done automatically
char cstring[] = {'v','a','t','a','n','i','\0'};

//ARRAYS
//must be constant size input
//initialises first two values, sets rest to 0
int intarray[9] = { 1, 2 }; 

//2D ARRAYS
//creates an arrow with 2 rows, 4 columns
int intarray[2][4] 
{
    {94, 98, 87, 103}, // values for intarray[0]
    {98, 99, 91, 107}, // values for intarray[1]
};

//////////////////////////////////////////////////////////////////////////////
//CASTING
//////////////////////////////////////////////////////////////////////////////

//C-style casting
long(myInt)
(int)myInt 

//C++ Style casting
float myFloat = static_cast<float>(myDouble)

//converts explicitly safely; only pointers of classes with virtual functions
//returns 0 if the conversion failed; slowest
MyClass1* ptr1 = dynamic_cast<MyClass2>(ptr2) 

//converts explicitly unsafely [only pointers]
MyClass1* ptr1 = reinterpret_cast<MyClass2>(ptr2) 

//converts const to non-const [only pointers]
//bad if var is stored in read-only memory
//use only if know underlying type is non-const
MyClass1* ptr1 = const_cast<MyClass2>(ptr2);

//////////////////////////////////////////////////////////////////////////////
//UNIONS
//////////////////////////////////////////////////////////////////////////////

//Only hold one var at a time; shares same memory location
//the size of that spot is determined by the largest variable (ie. long)
//can be used to access a variable in multiple ways (ie. for colors)
union MyColor
{
    unsigned int color;
    struct
    {
        unsigned char r, g, b, a;
    };
};

//////////////////////////////////////////////////////////////////////////////
//ENUMERATIONS
//////////////////////////////////////////////////////////////////////////////
//compiler replaces name with integer value when encountering it

enum myenum {red, orange = 100, yellow, green = 0}; //red = 0, orange = 100, yellow = 101, green = 0
enum myenum2 {red, orange, yellow, green}; //redifining despite new name not possible in VS

//DECLARING AN ENMUN INSTANCE
myenum e;
e = red;
e = myenum(2);
myenum nextEnum = static_cast<myenum>(e+1);

//ENUM FOR BIT FLAGS
enum MASKS
{
    NO_FLAG = 0,  // 0x000
    MASK1 = 1,    // 0x001
    MASK2 = 2,    // 0x002
    MASK3 = 4,    // 0x004
    MASK4 = 8,    // 0x008
    MASK5 = 16,   // 0x010
    MASK6 = 32,   // 0x020
    MASK7 = 64,   // 0x040
    MASK8 = 128   // 0x080
}

//Operators work on bool/integers/chars
//Amount of bytes minimally guaranteed determines amount of bit flags can be stored
unsigned char //Can have 8 (bytes) flags maximum
unsigned short //Can have 16 (bytes) flags maximum
unsigned int //Can have 16 (bytes) flags maximum 
unsigned long //Can have 32 (bytes) flags maximum


//////////////////////////////////////////////////////////////////////////////
//LOOPING
//////////////////////////////////////////////////////////////////////////////

//FOR LOOP
for (int i = 0; i < 5; i++){}

//FOR EACH LOOP
for (double x : myDoubleArray){ x += 1.0; }  //by-val
for (double &x : myDoubleArray){ x += 1.0; } //by-ref
for (auto x : myVectorArray){ DoSomething(x); } //with stl containers
for (int x : {0,4,3,5,2,0}){ cout << x; } //using initialisation list

//DOUBLE FOR LOOP
for (int i = 0, int j = 2; i < j; i = i + 15, j-- ){}

//WHILE LOOP
while (name[i] != '\0') { i++; }

//DO WHILE LOOP
do { cin << n;}
while (n != 7);

break; //stops the loop
continue; //skips rest of loop and starts the next iteration

//////////////////////////////////////////////////////////////////////////////
//BRANCHING/LOGIC
//////////////////////////////////////////////////////////////////////////////

if(myObj && myObj.Fn() == 2) // checks first and only checks next if first is true
if(myObj || myObj.Fn() == 2) // checks first, if not true will check second else not check second

//IF-ELSE
if (testint == 2) {}
else if (testint == 3) {}
else {}

//TERNARY OPERATOR
int value = (a < b) ? a : b;
obj->Exists() ? obj->DoSomething() : obj->DoSomethingElse();

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

//////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//PASSING ARRAYS/C-STRING
//pass array name (pointer to first member) and number of elements
void MyFunction(const char* myCString, n);
void MyFunction(const int myArray[], n);
MyFunction(myArray, n);

//PASSING 2D ARRAY
//my2DArray points to first element which points to array of col ints
//Only pass number of rows, passing pointer to a pointer
void MyFunction(int my2DArray[][cols],rows);
int my2DArray[rows][cols];
MyFunction(my2DArray, rows)

//INLINE FUNCTIONS
//function body replaced by function call in body
inline void MyFunction(int x){ x += 2; }
                                                  
//DEFAULT VALUES 
//must provide default values for parameters right to left
int MyFunction(int a, int b = 2);
int MyClass::MyMethod(int a, int b){} //don't need default for definition

//PRIVATE (INTERNAL LINKAGE) FUNCTIONS
//Functions have external linkage by default. Use static to change
static int MyFunction(int& arg);

//FUNCTION OVERLOADING  
void MyFunction(int & x, double y)
void MyFunction(const int & x, double y)
void MyFunction(int & x, short y)

//TRAILING RETURN TYPE
//shifts the return type to after the function arguments
double MyFunction(int x, int y) {} /*or*/
auto MyFunction(int x, int y) -> double {}
auto MyFunction(int x, int y) -> decltype(x) {} //make return type same as x

//C-VARIADIC FUNCTION
MyFunction("This is a %i %f test",2,3.0f);
void MyFunction(char* text, ...)
{
    char buffer[256];
    va_list arguments;
    va_start(arguments, text);  //Parse the string for variables
    vsprintf_s(buffer, text, arguments); //Convert argument symbols to text
    va_end(arguments); //Store results in text
    cout << buffer;
}

//////////////////////////////////////////////////////////////////////////////
//NAMESPACES
//////////////////////////////////////////////////////////////////////////////

namespace /*anon*/
{
}

namespace testspace
{
    int testint; //variables, structs, other namespaces
    double testfunct(void); //function declaration
    using std::cout; //namespace definitions
}

//Adding to namespace
namespace testspace
{
    //more stuff
}

//Using namespace
testspace::testint = 4; //name with a namespace = qualified name
using testspace::testfunct();  //using declaration
using namespace testspace; //using directive

//adding namespace alias
namespace alongtitle { ... };
namespace a = alongtitle;

//////////////////////////////////////////////////////////////////////////////
//PREPROCESSOR MACROS (COMPILER SPECIFIC)
//////////////////////////////////////////////////////////////////////////////

#include <iostream>  //includes code from class
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
    } while (false) //intentially don't put ;

//The ; gets added when using the macro
if (whatever)
    MYMACRO(foo, bar);
else 
    int x = 0;

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

//PREPROCESSOR CONSTANTS
_DEBUG
_MANAGED

//VISUAL STUDIO CONSTANTS
__FILE__    //name of file
__LINE__    //current line number
__TIME__    //time file was compiled
__DATE__    //date file was compiled