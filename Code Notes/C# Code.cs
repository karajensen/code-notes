////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLESs
////////////////////////////////////////////////////////////////////////////////////////////

//VALUE-TYPE VARIABLES
short myShort;
int myInt;
long myLong = 2L;
uint myUnInt = 2U;
ushort myUnShort;
ulong myUnLong = 2UL;
byte myByte;
sbyte mySByte;
float myFloat = 2.0f;
double myDouble = 2.0D;
decimal myDecimal = 2.0M; //long double
bool myBool = true; //does not accept number
BigInteger myBInt = 2.0; //grows as needed to accomadate size, no overflow
MyStruct myStruct;

//REFERENCE-TYPE VARIABLES
object myObj = null;
MyClass myObj = new MyClass();

//VARIABLE USAGE
var myVar = "same as auto"
int myInt = 1, myOtherInt = 2;
myInt = myShort = 2;
myInt++;
++myInt;
2 + 3; //expressions must be assigned to something (okay in C++)

//DEFAULT VARIABLE VALUES
default(int) //returns default value for that type
bool = false
numbers = 0
objects = null

//NULLABLE VALUE-TYPES
int? myint = null; //allows null to be assigned to value-type
int myInt2 = (int)myint; //requires cast to convert

//SCOPE
int myInt = 2;  { int myInt = 1; } //if in parent scope cannot be redeclared (okay in C++)
{ int myInt = 2; }{ int myInt = 1; } //okay

//OVERFLOW CHECKING
checked(a+b) //checks expression for overflow and throws System.OverflowException
checked{ /*do some calculations*/ }
unchecked(a+b) //don't check expression

//NOTATION
uint = 0xFF00FF00; //hex notation
var myVar = 1.0E-20f; //scientific notation

////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLE MODIFIERS
////////////////////////////////////////////////////////////////////////////////////////////

public readonly int myConst; // Const, initialised once at runtime.
public const int myConst = 1; // Const, initialised at compile time
public static int myStaticInt; // static class/struct variable
public int myInt; // Accessible everywhere
protected int myInt; // Accessible only to derived classes
protected internal in myint; // Accessible to derived classes/classes inside assembly(exe/dll)
private int myInt; // Accessible only inside the class/struct
internal int myInt; // Accessible only inside the assembly(exe/dll)
public volatile int myInt; // Not optimized for accessing regularly in multiple threads

////////////////////////////////////////////////////////////////////////////////////////////
//NAMESPACES
////////////////////////////////////////////////////////////////////////////////////////////

namespace {} //BAD: Namespaces can't be anonymous
namespace ns { myInt = 2; } //BAD: Namespaces can't contain vars/functions

// Creating a typedef
using MyTypedef = System.Drawing.Graphics;
MyTypedef obj = CreateGraphics();


////////////////////////////////////////////////////////////////////////////////////////////
//CONVERSIONS
////////////////////////////////////////////////////////////////////////////////////////////

//Downcasting: does not implicitly convert due to range not fitting into int
int myInt = (int)2.0/4.0; 

 //Upcasting: implicitly converts due to range fitting into double
int myDouble = 1/2; 

//Reference type conversions
//doesn't work with value types as returns null if conversion unsuccessful
Object obj = myClass as Object

//Converting to string
string myString = myDouble.ToString(); //returns number as string
string myString = myBool.ToString(); //returns "True" or "False"

//Converting from string
int x = Convert.ToInt32("10")
double myDouble = double.Parse("10.0"); //throws FormatException if failed
double.TryParse("10.0", out value) //converts string to doubles, returns false if failed

//Getting type of object
typeof(myInt) //return int
typeof(myObject) //return class
System.Type type = obj.GetType()
bool isObject = myClass is Object; 
bool isInt = myint is int;

////////////////////////////////////////////////////////////////////////////////////////////
//WEAK REFERENCES
////////////////////////////////////////////////////////////////////////////////////////////

//allows reference to object but doesn't count as a strong reference for the gc
var myWeakRef = new WeakReference<MyClass>(myObj1)

//returns false if myObj1 has been collected else true
//stores strong reference into myObj2 if returns true
MyClass myObj2;
bool isAlive = myWeakRef.TryGetTarget(out myObj2) 

////////////////////////////////////////////////////////////////////////////////////////////
//ENUMS
////////////////////////////////////////////////////////////////////////////////////////////

//ENUM
public enum MyEnum
{
    ONE = 1,
    TWO = 5,
    THREE //will equal 6
}
int x = (int)MyEnum.ONE;

//32-BIT FLAGS, maximum 32 flags
[System.Flags]
public enum MyEnum
{
  A = 0x001, // or = 1
  B = 0x002, // or = 2
  C = 0x004, // or = 4
}

//64-BIT FLAGS, maximum 64 flags
[System.Flags]
public enum MyEnum : long
{
  A = 0x001, // or = 1
  B = 0x002, // or = 2
  C = 0x004, // or = 4
}

////////////////////////////////////////////////////////////////////////////////////////////
//LOOPING/LOGIC
////////////////////////////////////////////////////////////////////////////////////////////

//IF-ELSE STATEMENTS
if (myNumber){} //BAD: cannot use if(myNumber) to test if != 0 (C++ can)
else if (myBool && myNumber != 0){}
else if (myObj != null || !myBool){}
else {}

//TERNARY OPERATORS
myInt = myBool ? 0 : 10;
myInt = myObj == null ? 0 : 10

//NULL COALESCING OPERATOR
int y = myint ?? -1; //if myInt != null, return myInt else -1 where int? myInt;
myString = str ?? ""; //if str is null, use default value provided otherwise use str
myObj2 = myObj ?? new MyClass();

//SWITCH STATEMENTS
//can use int, string, char or enum
//can't fall through the next case, must use break, return or goto
switch(myString)
{
case "one":
    goto case "two";
case "two":
    break;
default:
    break;
}

//WHILE-LOOPS
while(!okay){ break; }
do { continue; } while(!okay)

//FOR LOOPS
for (int i = 0; i < count; ++i){}

//FOR-EACH LOOPS
//cannot modify collection
//uses explicit cast for each item
foreach (str in myStringArray)
foreach (int value in array)

////////////////////////////////////////////////////////////////////////////////////////////
//UNSAFE CODE/POINTERS
////////////////////////////////////////////////////////////////////////////////////////////

int* myPointer 
int** myPointer
int*[] myPointer //array of pointers to ints
char* myPointer //pointer to a char
void* myPointer

//POINTER TO STRUCTS
MyStruct* myPointer;
myPointer->member;

//UNSAFE CODE
//Pointers can only be used in this
unsafe static void MyUnsafeFn(int* p)
{
    *p = 2; //dereferencing

    //FIXING VARIABLES
    //prevents garbage collector from changing address of a variable
    //can only use in unsafe context
    MyClass obj = new MyClass();
    fixed (int* x = &obj.x)
    {
        *x = 1;
    }  
}

int myInt = 1;
MyUnsafeFn(&myInt); //obtain address

////////////////////////////////////////////////////////////////////////////////////////////
//PREPROCESSOR
////////////////////////////////////////////////////////////////////////////////////////////

//must be defined before any other code
//can't be used to define a variable/expression

#define DEFINED
#undef DEFINED
#if DEBUG
#elif DEFINED
#endif
#error send this error to the compiler
#warning send this warning to the compiler
#pragma warning disable 168