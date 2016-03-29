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
default(bool) //false
default(number) //0
default(objects) //null
default(String) //null
default(enum) //0

//VARIABLE CONSTANTS
float.PositiveInfinity
float.NegativeInfinity
int.MaxValue
int.MinValue
double.PositiveInfinity
double.NegativeInfinity
bool.FalseString
bool.TrueString

//NULLABLE VALUE-TYPES
int? myint = null; //allows null to be assigned to value-type
int myInt2 = (int)myint; //requires cast to convert

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
//NAMESPACE/SCOPE
////////////////////////////////////////////////////////////////////////////////////////////

namespace {} //BAD: Namespaces can't be anonymous
namespace ns { myInt = 2; } //BAD: Namespaces can't contain vars/functions

//TYPEDEFINE
using MyTypedef = System.Drawing.Graphics;
MyTypedef obj = CreateGraphics();

//SCOPE
int myInt = 2;  { int myInt = 1; } //if in parent scope cannot be redeclared (okay in C++)
{ int myInt = 2; }{ int myInt = 1; } //okay

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
string myString = myDouble.ToString("0.00"); //returns number as string with precision
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
bool hasInterface = myClass is IMyClass;

////////////////////////////////////////////////////////////////////////////////////////////
//ENUMS
////////////////////////////////////////////////////////////////////////////////////////////

//ENUM
//implicitly have zero entry
//can use byte, sbyte, short, ushort, int, uint, long, and ulong (not char)
public enum MyEnum //defaults to int
{
    ZERO = 0,
    ONE = 1,
    TWO = 5,
    THREE //will equal 6
}
int x = (int)MyEnum.ONE;
string zero = MyEnum.ZERO.ToString() //gives ZERO

//32-BIT FLAGS, maximum 32 flags
[System.Flags]
public enum MyEnum
{
    NO_FLAG = 0, // 0x000
    MASK1 = 1,   // 0x001
    MASK2 = 2,   // 0x002
    MASK3 = 4    // 0x004
}

//64-BIT FLAGS, maximum 64 flags
[System.Flags]
public enum MyEnum : long 
{
    NO_FLAG = 0, // 0x000
    MASK1 = 1,   // 0x001
    MASK2 = 2,   // 0x002
    MASK3 = 4    // 0x004
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
foreach (int item in myIEnum)
foreach (int value in Enumerable.Range(0, 100)) //Enumerable requires LINQ

//GOTO
goto myLabel;
myLabel:

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

////////////////////////////////////////////////////////////////////////////////////////////
//DELEGATES
////////////////////////////////////////////////////////////////////////////////////////////

Func<int, double> myFn; //Takes in int, returns double
Action<int> myFn; //Takes in int, no return value
Action<int, double> myFn; //Multiple arguments, no return value
Action myFn; //No params/return value
delegate void MyDelegate(int x) //custom delegate signature

//CREATING DELEGATES
//Outside variables are auto captured if used
MyDelegate myDel = null;
MyDelegate myDel = MyFunction;
MyDelegate myDel = new MyDelegate(MyFunction);
MyDelegate myDel = delegate(int x){ myOutsideInt += x; }
myDel(); //calling delegate

//STATIC FUNCTIONS
public static void MyStaticFunction(int x){}
MyDelegate myDel = MyClass.MyStaticFunction;

//MEMBER FUNCTIONS
public void MyMemberFunction(int x){}
MyDelegate myDel = this.MyMemberFunction; //auto binds object calling
MyDelegate myDel = obj.MyMemberFunction;

//ANONYMOUS METHODS
//Canot use unsafe code
//Cannot access the ref or out parameters of an outer scope
MyDelegate myDel = delegate(int x){ myOutsideInt += x; }
MyDelegate myDel = x => myOutsideInt += x; //Lamda method

//LAMDA METHODS
x => (double)x * 2;            //Takes in int, returns double
x => myOutsideInt += x;        //Takes in int, no return value
(int x) => x*x                 //explicitly specifying argument type
(x,y) => x*y                   //multiple arguments
() => { i += 2.0; i += 3.0; }  //no auto return for multiple lines
() => { return i+j; }          //explicitly returning

//MULTI-CASTING DELEGATES
MyDelegate multiDel = myDel1 + myDel2; //methods are called one after each other in list
multiDel -= myDel2; //can also remove
multiDel.GetInvocationList().GetLength(0); //get int number of delegates in list

//DELEGATE TEMPLATES
public delegate void MyDelegate<T>(T item);
public void MyFunction(int i) {}
MyDelegate<int> myDel = new MyDelegate<int>(MyFunction); /*or*/
MyDelegate<int> myDel = MyFunction;

//===========================================================================================
//DELEGATE INHERITANCE
//===========================================================================================

public class Base {}
public class Derived : Base {}

//COVARIANCE IN DELEGATES
//• Allows delegate to accept a method which returns a higher derived type than delegate defines

public delegate Base MyDelegate(); //Delegate signature
public static void Derived MyFunction();
MyDelegate myDel = MyFunction; //Accepts despite requiring return to be Base

//CONTRAVARIANCE IN DELEGATES
//• Allows delegate to accept a method which has parameters of a lower derived type than delegate defines

public delegate void MyDelegate(Derived d); //Delegate signature
public static void MyFunction(Base b);
MyDelegate myDel = MyFunction; //Accepts despite requiring derived as a parameter

////////////////////////////////////////////////////////////////////////////////////////////
//OBJECT LIFETIME
////////////////////////////////////////////////////////////////////////////////////////////

//IDISPOSABLE
//class that inherits IDisposable contains a destructor, use using() to ensure its called
using(MyDisposable myDis = new MyDisposable())
{
    myDis.DoSomething();
}

//BOXING
object boxed = 10; //occurs implicitly for value-types
int unBoxed = boxed as int; //occurs explicitly for value-types

//WEAK REFERENCES
//allows reference to object but doesn't count as a strong reference for the gc
var myWeakRef = new WeakReference<MyClass>(myObj1)

//returns false if myObj1 has been collected else true
//stores strong reference into myObj2 if returns true
MyClass myObj2;
bool isAlive = myWeakRef.TryGetTarget(out myObj2)

////////////////////////////////////////////////////////////////////////////////////////////
//UNSAFE CODE
////////////////////////////////////////////////////////////////////////////////////////////

//POINTERS
//Pointers can only be used in unsafe code
int* myPointer = &myInt; 
int** myPointer
int*[] myPointer //array of pointers to ints
char* myPointer //pointer to a char
void* myPointer
MyStruct* myPointer
*myPointer = 2; //dereferencing

unsafe static void MyUnsafeFn(int* p)
{    
    //PINNING VARIABLES
    //prevents garbage collector from changing address of a variable
    //can only use in unsafe context
    MyClass obj = new MyClass();
    fixed (int* x = &obj.x)
    {
        *x = 1;
    }  
}

//DISPOSING OF UNMANAGED RESOURCES
class MyClass : public IDisposable
{
    bool isDisposed = false;

    //Implementation of IDisposable.Dispose
    public virtual void Dispose() override
    {
        if(!isDisposed)
        {
            //Free any unmanaged/managed resources here
            //prevent finalise from being called as Dispose will do the destructors job
            GC.SuppressFinalize(this);
            isDisposed = true; 
        }
    }
    public void MyFunction()
    {   
        //if implementing, must check if object has been disposed
        if(isDisposed)
        {
            throw new ObjectDisposedException("MyClass","Called MyFunction() on disposed object");
        }
    }
    ~MyClass()
    {
        Dispose();
    }
};