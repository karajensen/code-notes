////////////////////////////////////////////////////////////////////////////////////////////
//C#
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

//CONVERSIONS
int myInt = 2.0/4.0; //Downcasting: does not implicitly convert due to range not fitting into int
int myDouble = 1/2;  //Upcasting: implicitly converts due to range fitting into double
int myInt = int(myDouble);
int myInt = (int)myDouble;
string myString = myDouble.ToString(); //returns number as string
string myString = myBool.ToString(); //returns "True" or "False"
int x = Convert.ToInt32("10")
double myDouble = double.Parse("10.0"); //throws FormatException if failed
double.TryParse("10.0", out value) //converts string to doubles, returns false if failed

//OVERFLOW CHECKING
checked(a+b) //checks expression for overflow and throws System.OverflowException
checked{ /*do some calculations*/ }
unchecked(a+b) //don't check expression

//NOTATION
uint = 0xFF00FF00; //hex notation
var myVar = 1.0E-20f; //scientific notation

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
foreach (str in myStringArray)
foreach (int value in array)

////////////////////////////////////////////////////////////////////////////////////////////
//GENERICS
////////////////////////////////////////////////////////////////////////////////////////////

//TEMPLATED CLASS
public class MyTemplateClass<T>
{
    private T myObj;
    public MyTemplateClass(T obj)
    {
        myObj = obj;
    }

    //TEMPLATED METHODS
    public void MyTemplateMethod<S>()
        where S : MyBaseClass
    { 
        var Def = default(S); 
    }
}

//CONSTRAIN CONSTRUCTOR
//can only create instances of class with no arguments in contructor
public class MyTemplateClass<T> where T : new() {}

//CONSTRAIN INHERITANCE
//T must have base or be of type MyBaseClass/IMyBaseClass
public class MyTemplateClass<T> where T : MyBaseClass {}
public class MyTemplateClass<T> where T : IMyBaseClass {}

//CONSTRAIN REFERENCE
//T must be a reference-type variable
//allows T to be tested against null as value-types don't have null
public class MyTemplateClass<T> where T : class {}

//CONSTRAIN VALUE
//T must be a value-type variable
public class MyTemplateClass<T> where T : struct {}

//MULTIPLE CONSTRAINTS
//new() must be last, class/struct must be first
public class MyTemplateClass<T> where T : class, MyBaseClass, MyOtherBaseClass, new() {}

////////////////////////////////////////////////////////////////////////////////////////////
//GENERICS INHERITANCE
////////////////////////////////////////////////////////////////////////////////////////////

//BASE CLASS
public class Base<T>
{
    public Base(){}
};

//DERIVED CLASS
class D<T> : Base<T> //Type T is passed into Base
{
    public D() : base() {}
};

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