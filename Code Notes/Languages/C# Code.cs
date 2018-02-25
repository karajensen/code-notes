/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C# NOTES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
.NET FRAMEWORK
• Development framework for creating windows applications
• Used by languages C#, VB.NET, C++/CLI
• A type of COMMON LANGUAGE INFRASTRUCTURE (CLI)
    |  
    |__ COMMON TYPE SYSTEM (CTS)
    |   • Shared basic data types used by .NET languages
    |   
    |__ BASE/FRAMEWORK CLASS LIBRARY (BCL/FCL)
    |   • Shared classes used by .NET languages
    |   
    |__ COMMON LANGUAGE RUNTIME (CLR)
        • Responsible for .NET program execution
        • Contains Virtual Execution System, Garbage Collector, JIT Compiler, Managed Heap
            |   
            |__ VIRTUAL EXECUTION SYSTEM (VES)
            |   • Environment for executing managed code
            |   
            |__ JUST-IN-TIME COMPILER (JIT)
                • Source code is compiled into Common Intermediate Language (CIL)
                • Microsoft Intermediate Language (MSIL) is another name for CIL
                • CIL is stored in an assembly and converted to native code at runtime

ASSEMBLIES
• Exe/dll that contain metadata about the information inside and optional resources (images, sound)
• Dll only loaded if required. Can use two versions of same assembly in single application
• Share assemblies between applications using Global Assembly Cache
• Assemblies must be strong named; guaranteed uniqueness
• Assemblies contain modules. Modules contain classes.
**************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
VALUE-TYPE VARIABLES
• Structs, enums, nullable/basic data types, reference/pointer used to store a reference variable
• Variable exists on stack or register, passed by-val and are copied deeply
• Memory auto deleted by stack when out of scope
• Equality: If both are same type and have same contents
• Sealed: can't inherit anything or be derived from

REFERENCE-TYPE VARIABLES
• Classes, arrays, boxed value-types
• Variable exists in the heap with a value-type object refering to it, copied shallow
• Memory auto deleted by garbage collector when reference count equals zero
• Equality: If both have the same memory address
• Can inherit one class and be derived from

ARRAYS
• All arrays are reference even if elements are value-types
• Inherit System.Array

STRINGS
• String literals are interned so that for each occurrence of a particular
  string only occurs once in memory and can be referenced by multiple variables

VARIABLE INITIALISATION
• Class members and local variables at start of method and not within block scope auto-initialised
• Must explicitly initialise variables in block scope or error
**************************************************************************************************************/

sbyte     System.SByte         byte    System.Byte
short     System.Int16         ushort  System.UInt16
int       System.Int32         uint    System.UInt32
long      System.Int64         ulong   System.UInt64
float     System.Single        double  System.Double
decimal   System.Decimal       bool    System.Boolean

// VALUE-TYPE VARIABLES
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

// REFERENCE-TYPE VARIABLES
object myObj = null;
MyClass myObj = new MyClass();

// VARIABLE USAGE
var myVar = "same as auto"
int myInt = 1, myOtherInt = 2;
myInt = myShort = 2;
myInt++;
++myInt;
2 + 3; //expressions must be assigned to something (okay in C++)

// DEFAULT VARIABLE VALUES
default(int) //returns default value for that type
default(bool) //false
default(number) //0
default(objects) //null
default(String) //null
default(enum) //0

// VARIABLE CONSTANTS
float.PositiveInfinity
float.NegativeInfinity
int.MaxValue
int.MinValue
double.PositiveInfinity
double.NegativeInfinity
bool.FalseString
bool.TrueString

// NULLABLE VALUE-TYPES
int? myint = null; //allows null to be assigned to value-type
int myInt2 = (int)myint; //requires cast to convert

// OVERFLOW CHECKING
checked(a+b) //checks expression for overflow and throws System.OverflowException
checked{ /*do some calculations*/ }
unchecked(a+b) //don't check expression

// NOTATION
uint = 0xFF00FF00; //hex notation
var myVar = 1.0E-20f; //scientific notation

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLE MODIFIERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
CONST/READONLY VARIABLE DIFFERENCES:
• Const compile time and faster; Readonly runtime and slower
• Const can be declared inside methods; Readonly only as member variable
• Const replaces value during compilation; Readonly becomes const after contructor called
• Const only used with inbuilt numbers/strings; Readonly used with everything
• Const can't be initialised with 'new'; Readonly can be initialised with 'new'
• Const can never be changed. Readonly objects only make the reference to the object 
  constant, not the object itself. The reference can also be hacked through reflection.
**************************************************************************************************************/

public readonly int myConst; // Const, initialised once at runtime.
public const int myConst = 1; // Const, initialised at compile time
public static int myStaticInt; // static class/struct variable
public int myInt; // Accessible everywhere
protected int myInt; // Accessible only to derived classes
protected internal in myint; // Accessible to derived classes/classes inside assembly(exe/dll)
private int myInt; // Accessible only inside the class/struct
internal int myInt; // Accessible only inside the assembly(exe/dll)
public volatile int myInt; // Not optimized for accessing regularly in multiple threads

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NAMESPACE/SCOPE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace { } //BAD: Namespaces can't be anonymous
namespace ns { myInt = 2; } //BAD: Namespaces can't contain vars/functions

//TYPEDEFINE
using MyTypedef = System.Drawing.Graphics;
MyTypedef obj = CreateGraphics();

//SCOPE
int myInt = 2;  { int myInt = 1; } //if in parent scope cannot be redeclared (okay in C++)
{ int myInt = 2; }{ int myInt = 1; } //okay

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONVERSIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENUMS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ENUM
//implicitly have zero entry
//can use byte, sbyte, short, ushort, int, uint, long, and ulong (not char)
public enum MyEnum //defaults to int
{
    ZERO = 0,
    ONE = 1,
    TWO = 5,
    THREE = 5,
    FOUR //will equal 6
}

(int)MyEnum.ONE                             // Convert to int
MyEnum.ZERO.ToString()                      // Get string description
System.Enum.GetName(typeof(MyEnum), 1)      // Get string description from value (ONE) or null
System.Enum.GetNames(typeof(MyEnum)).Length // Get name count (5)
System.Enum.GetValues(typeof(MyEnum)).Cast<MyEnum>().Distinct().Count(); // Get value count (4)

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LOOPING/LOGIC
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PREPROCESSOR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DELEGATES/EVENTS/LAMBDAS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
DELEGATES
• Reference to a method or lambda deriving from System.Delegate
• Sealed; cannot be derived from

ANONYMOUS DELEGATES
• Can't use goto/break/continue to move outside delegate block
• Auto captures a reference to any variables used within block
• Until delegate lifetime is over these variables remain in memory
• Cannot capture any ref/out variables from parent scope
• Cannot use pointer or access unsafe code

EVENTS
• Holds delegates for publishers/subscribers
• Publisher: class that sends the event
• Subscriber: class that recieves/handles the event
• Events that have no subscribers are never called

LAMBDAS
• A captured variable will not be garbage-collected until the lamda goes out of scope
• Variables inside lambda are not visible outside
• Lambda cannot directly capture a ref/out parameter from the parent method
• Cannot contain goto, break, containue that moves to outside lambda
**************************************************************************************************************/

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

//===============================================================================================================
// DELEGATE INHERITANCE
//===============================================================================================================

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OBJECT LIFETIME
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
ROOT: Memory address for object on heap or null

CLR HEAP
• Reference-types live on heap; Value-types live in heap, register or stack
• Constructing object through new adds block to the heap
• Garbage collector removes the memory at intervals
• Each block has a header; includes object type, and information for hash generation
• 32-bit system, header is +8 bytes, 64-bit system, header is +16 bytes per object

GARBAGE COLLECTION
• When object is out of scope/not being used anymore, marked as dead by Garbage Collection
• Garbage collection monitors own performance and adjusts settings as needed
• Forcing garbage collection is not good; it can't tune itself properly

LARGE OBJECT HEAP
• Large objects greater than certain byte amount are stored on Large Object Heap
• No heap relocation/compaction occurs due to cost of copying large objects

HEAP GENERATIONS
• When Generation 0 runs out of memory, does a collection and moves objects to next gen
• The longer the object stays alive the more expensive it is to delete
    Generation 0: Hasn't survived a garbage collection yet
    Generation 1: Recently created object that's survived
    Generation 2: Oldest generation for long lived objects
• GC most effecient for objects with long or short lives.
• GC least effecient for deleting objects just entering Generation 2
  knowledge of this section will need to be rebuilt, may not be in the cache

HEAP COMPACTION
• As objects destroyed, heap becomes fragmented
• Moving remaining objects together and then adding to heap is cheaper than slotting into the gaps
• Older the generation, less heap compaction occurs
• Careful when refering to direct addresses of objects as they will move around after compaction
•
PINNING MEMORY BLOCKS
• Pinning a block sets a flag to disallow moving by the garbage collector
• Calls to unmanaged code that requires pointers will auto pin/unpin the block
• Causes more fragmentation and effeciancy issues to CLR heap, none to Large Object Heap

WEAK REFERENCES
• Short Weak Reference: Tells when object is unreachable or fully removed by GC
• Long Weak Reference: Tells when object is fully removed by GC

BOXING
• Process of converting a value type to a System.Object reference type
• Copy of the value-type is wrapped in System.Object and put on the heap
• This boxed object remembers what the original type was and will only unbox if cast correctly
• Unboxing copies the boxed value to another value-type variable
• Boxing is implicit, Unboxing is reverse and explicit
• Ineffecient as copying required and Garbage Collected needs to remove new boxed object
• If nullable value-type is null, returns null before doing any boxing
**************************************************************************************************************/

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNSAFE CODE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
POINTERS
• Works on sbyte, byte, short, ushort, int, uint, long, ulong, char, float, double, decimal, bool
• Works on void, enum and structs with value-types only
• Cannot point to reference as garbage collector doesn't keep track of pointers
• Do not inherit from System.Object- No conversions exist between pointers/object
• Boxing/Unboxing not supported

UNSAFE CODE
• Methods, types, and code blocks can be defined as unsafe
• Can increase performance by removing bounds/runtime checks
• Required when calling native functions that require pointers
• /unsafe must be set to compile
**************************************************************************************************************/

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