//////////////////////////////////////////////////////////////////////////////
//VARIABLES
//////////////////////////////////////////////////////////////////////////////

Edit.ConvertTabsToSpaces

//GLOBAL VARIABLES
int pub; //static duration, external linkage
static int priv; //static duration, internal linkage
const int constint; //static duration
extern int externalVar; //accesses public variables from another file

//OTHER VARIABLES
static int staticint; //keeps a local variable in memory even when func. exits
register int regint; //may store variable in register not on stack: NO address
::pub; //accesses global variables when shadowed by local variables

//AUTO VARIABLES
auto x = 0  //automatically chooses 'int' for x
auto iterator = myVectorArray.begin() //auto chooses correct iterator 
auto ptr = &someRandomVar  //auto chooses correct pointer type
auto ptr = &someFunction  //auto chooses correct function pointer
decltype(y) val; //make val the same type as y
decltype(x + y) val = x + y; //choose the type of combined x+y
decltype(myFnt(y)) val; //make val same type as return of myFnt(y)

//TYPEDEF
typedef decltype(x) myType; //can use decltype with typedef
typedef int Item; //creates a new type of variable object of type int 
typedef bool Item; //bool will use 4 bytes if typedefined to something else

//SIMPLE VARIABLES
long double testldbl = 22.2;
unsigned short testshort = 34; //can never be negative- increases range
long testlong = 0x16; //0x at beginning means hexadecimal
char testchar = 'M' //testchar stores value for M and can be put into an int
2+4; //okay without assignment

//VARIABLE SIZES
sizeof(testint) //gives size of testint in bytes
sizeof(testarray) //gives size of whole array rather than first element
sizeof(chararray) //size of whole char array
sizeof(p_updates) //Gives the size of the pointer

//VARIABLE INCREMENTING
b = ++a //increment a and then use it in expression; b = new value of a
b = a++ //use a in expression then increment it after; b = old value of a
++++++i;   // OKAY: parsed as (++(++(++i)))
i++ * ++i; // BAD: i is modified more than once
i = ++i    // BAD: i is modified more than once
++i = 2;   // BAD: i is modified more than once
i = ++i +1 // BAD: i is modified more than once

//////////////////////////////////////////////////////////////////////////////
//REFERENCES
//////////////////////////////////////////////////////////////////////////////

int x //L-VALUES: Persisting variable on left side of assignment expression    
3+1   //R-VALUES: Temporary variable on right side of assignment expression

//STORING R-VALUES INTO L-VALUES
//3+1 creates temp value, temp is assigned to x, temp is deleted
int x = 3+1; int & x = 3+1;
//3+1 creates temp value, x references temp
int && x = 3+1; 
//t is initialised with r-value but is l-value itself
void foo(int&& t);

//FUNCTION RETURNS
int   prvalue();
int&  lvalue();
int&& xvalue();

//////////////////////////////////////////////////////////////////////////////
//CONSTNESS
//////////////////////////////////////////////////////////////////////////////

const int* pv = &v; //Pointer to a constant int (can't change value)
int* const pv = &v; //Constant int pointer (can't change what ptr points to)
const int * const pv = &value //can't change value or what pointer points to

//lets compiler know not to cache the value; to check actual value each 
//time its asked for IE. time modified by the hardware
volatile int volint; 

//ignores var changes when checking for bitwise const
//allows var changes when object is const and var is public
mutable int m_myVar; 

//const version for normal and const objects, makes 'this' pointer constant
const int & testclass::function() const;

//normal version for only normal objects
int & testclass::function();        
            
//////////////////////////////////////////////////////////////////////////////
//CSTRINGS
//////////////////////////////////////////////////////////////////////////////

char C; //single character; can read/write
char C[256]; //character buffer, can read/write
char* C; //Constant string literal, read only (use strcpy to write)

//CONSTANT STRING LITERALS
//Think of char * not as char* but as a unique data typ
char * testchar = "An array";
char * temp = testchar;
testchar //gives string
testchar[0] //gives 'A', can't write to it
(void*)testchar //gives address of char array (char*)
&testchar //gives address of pointer to the char array (char**)

//////////////////////////////////////////////////////////////////////////////
//ARRAYS
//////////////////////////////////////////////////////////////////////////////

const int i = 4; //must use const when using for arrays
int intarray[i] = {1} //0-based array with elements 0 to 3; 
                      //sets first value to 1, rest to 0

char chararray2 [] = "vatani" //the \0 is done automatically
char chararray1 [] = {'v','a','t','a','n','i','\0'};

//2D ARRAYS
int intarray[2][4] // creates an arrow with 2 rows, 4 columns
int maxtemps[4][5] = // Initializing
{
    {94, 98, 87, 103, 101}, // values for maxtemps[0]
    {98, 99, 91, 107, 105}, // values for maxtemps[1]
    {93, 91, 90, 101, 104}, // values for maxtemps[2]
    {95, 100, 88, 105, 103} // values for maxtemps[3]
};

//////////////////////////////////////////////////////////////////////////////
//UNIONS
//////////////////////////////////////////////////////////////////////////////

union myunion 
{
    long unionlong;
    int unionint;
};
//==> One var at a time; shares same memory location
//==> the size of that spot is determined by the largest variable (ie. long)
//==> using another var from the union kills the first one  
    
myunion test;
test.unionint = 15;

//////////////////////////////////////////////////////////////////////////////
//ENUMERATIONS
//////////////////////////////////////////////////////////////////////////////

//compiler replaces name with value when encountering it
//Can't dereference it to get the intial word
//Only use ints
    
//red = 0, orange = 100, yellow = 101, green = 0
enum myenum {red, orange = 100, yellow, green = 0}; 

//redifining despite new name not possible
enum myenum2 {red, orange, yellow, green}; 

//used as a constant
int myInt = red;

//declaring an enmun instance
myenum e;
e = red;
e = myenum(2);
myenum nextEnum = static_cast<myenum>(e+1);


//////////////////////////////////////////////////////////////////////////////
//CASTING
//////////////////////////////////////////////////////////////////////////////

//C-style casting
long(testint)
(int)22.3 

//converts explicitly safely; only pointers of classes with virtual functions
//returns 0 if the conversion failed; slowest
testfloat = dynamic_cast<float>(testint) 
if(pClass1 = dynamic_cast<Class1>(pClass2){ pClass1->DoClass2Method(); }

//converts explicitly unsafely [only pointers]
testfloat = reinterpret_cast<float>(testint) 

//converts implicitly (standard casting)
double d;
float f = static_cast<float>(d)

//converts const to non-const [only pointers]
//bad if var is stored in read-only memory
//use only if know underlying type is non-const
int * p_int2= const_cast<int*>(p_int1);


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
int i, j;
for (int i = 0, int j = 2; i < j; i = i + 15, j-- ){}

//WHILE LOOP
int i = 0;
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
int c = a > b ? a : b; //produces the same result as the following statements:
int c;
if (a > b)
    c = a;
else
    c = b;

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
inline double testinline(double x) { return x*x } 
class MyClass
{
public:
    int MyMethod(){ return 0; } //implicitely declares as inline for a class
};
                                                  
//DEFAULT VALUES 
//must provide default values for parameters right to left
int MyMethod(int a, int b = 2);
int MyClass::MyMethod(int a, int b){} //don't need default for definition
                                         
//TEMPLATE FUNCTION PROTOTYPE
template <class MyClass> void Swap(MyClass &a, MyClass &b);

//PRIVATE (internal linkage) FUNCTIONS
//Functions have external linkage by default. Use static to change
static int MyFunction(int& arg);

//FUNCTION OVERLOADING  
void MyFunction(int & x, double y)
void MyFunction(const int & x, double y)
void MyFunction(int & x, short y)

//VARIADIC FUNCTION
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

//Defining in Header
namespace testspace
{
    int testint; //variables, structs, other namespaces
    double testfunct(void); //function declaration
    using std::cout; //namespace definitions
};

//Adding to namespace
namespace testspace
{
    //more stuff
};

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