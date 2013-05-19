////////////////////////////////////////////////////////////////////////////////////////////
//C# CLASS/INHERITANCE
////////////////////////////////////////////////////////////////////////////////////////////

//VARIABLE MODIFIERS
public readonly int myConst; ///< Const, initialised once at runtime. Can be bypassed
public const int myConst = 1; ///< Const, initialised at compile time
public static int myStaticInt; ///< static class/struct variable
public int myInt; ///< Accessible everywhere
protected int myInt; ///< Accessible only to derived classes
protected internal in myint; ///< Accessible to derived classes/classes inside assembly(exe/dll)
private int myInt; ///< Accessible only inside the class/struct
internal int myInt; ///< Accessible only inside the assembly(exe/dll)

//NAMESPACES
namespace {} //BAD: Namespaces can't be anonymous
namespace ns { myInt = 2; } //BAD: Namespaces can't contain vars/functions

////////////////////////////////////////////////////////////////////////////////////////////
//METHODS
////////////////////////////////////////////////////////////////////////////////////////////

//PASSING BY-REF
//must assign something to all out/ref vars unless exception explicitly thrown
//out is write only and doesn't need to be initialised, ref is read/write
obj.MyMethod(ref myFloat, out myInt);
public void MyMethod(ref float myFloat, out int myInt);

//DEFAULT VALUES
//defined in order of right to left
public void MyMethod(string myString = "hello");

//SPECIFYING ARGUMENT NAME
obj.MyMethod(myFloat: 2.0f);
public void MyMethod(float myFloat);

//CONDITIONAL CLASS METHOD
//only used if DEFINED is defined; compiler will remove any method
//calls if not defined. Useful for doing diagnostics only in debug
[System.Diagnostics.Conditional("DEFINED")]
public void myConditionalMethod(){}
        
//OPERATOR OVERLOAD ++
public static MyClass operator++(MyClass c)
{
    c.myInt += 1;
    return c;
}

//CONVERSION FUNCTIONS
//explicit makes it require cast (int)myObj
//implicit makes it not require cast
public static explicit operator int(MyClass value)
{
    return value.myint;
}

//PARAMS VARIADIC FUNCTION
//creates array from extra arguments and substities int {}
MyMethod("{0} This is {1} a test {2}{3}", 2,3,4,4);
public void MyMethod(string format, params object[] arg);

////////////////////////////////////////////////////////////////////////////////////////////
//PROPERTIES
////////////////////////////////////////////////////////////////////////////////////////////
//Method that doesn't use () when called

//GETTER/SETTER PROPERTIES
public int MyInt
{
    get { return myInt; }
    set { myInt = value; }
}

//INDEXER PROPERTY (OVERLOADING [])
public string this[int index]
{
    get { return myStringArray[index]; }
}

////////////////////////////////////////////////////////////////////////////////////////////
//STRUCTS [VALUE-TYPE]
////////////////////////////////////////////////////////////////////////////////////////////

public struct MyStruct
{
    //CONSTRUCTOR
    //Can only declare contructor with arguments. Default constructor auto generated
    MyStruct(int x){} 

    //OPERATOR OVERLOAD ==
    //Structs don't auto create == 
    public static bool operator==(MyStruct a, MyStruct b)
    {
        return a.myVar == b.myVar;
    }

    //OPERATOR OVERLOAD !=
    //Must create matching != or error
    public static bool operator!=(MyStruct a, MyStruct b)
    {
        return a.myVar != b.myVar;
    }

    //OVERRIDE EQUALS
    //Required if overloading ==/!= otherwise compiler warning
    public override bool Equals(object obj)
    {
        return (obj is MyStruct ? this.myVar == ((MyStruct)obj).myVar : false);
    }

    //OVERRIDE GETHASHCODE
    //Required if redefining Equals, a unique index for the object
    public override int GetHashCode()
    {
        return myVar;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//CLASSES [REFERENCE-TYPE]
////////////////////////////////////////////////////////////////////////////////////////////

namespace MyNamespace
{
    public class MyClass : Control
    {
        //Member variables can be initialised only with static 
        //methods as object is not complete when initialised
        public int myInt = MyStaticMethod();

        #region myRegion
        #endregion

        /// <summary> MySummary </summary>
        /// <param> a value the method takes in </param>
        /// <returns> a value the method takes in </returns>

        //CONSTRUCTOR
        public MyClass() : this(10) //invoke another constructor
        {}
        public MyClass(int myInt)
        {
            self.myInt = myInt; //access via self or without
        }

        //STATIC CONSTRUCTOR
        //called once sometime before class is used
        //initialises static members, cannot take arguments
        static MyClass()
        {}

        //DESCTRUCTOR
        ~MyClass(){} //no visibility allowed

        //STATIC METHOD
        //only deals with static variables
        static public void MyStaticMethod(){}

        //PRIVATE SUB-CLASS
        internal class MyPrivateClass
        {
        };
    };
}

////////////////////////////////////////////////////////////////////////////////////////////
//STATIC CLASS
////////////////////////////////////////////////////////////////////////////////////////////

//Used for global vars; vars cannot be declared without class
public static class MyStaticClass
{
    public static int myInt;
}   
//Used for main entry point
public static class Program
{
    static void Main(){}
}

MyStaticClass.myInt; //using static members

////////////////////////////////////////////////////////////////////////////////////////////
//INTERFACE CLASS
////////////////////////////////////////////////////////////////////////////////////////////

public interface IMyClass()
{
    int MyMethod1(); //accessor determine by derived class
    float MyMethod2();
};

public class MyClass() : IMyClass
{
    public int MyMethod1() { return 10; } //implemented method
    float IMyClass.MyMethod2() {} //non-implemented method, cannot be used by object itself
};

////////////////////////////////////////////////////////////////////////////////////////////
//ABSTRACT CLASS
////////////////////////////////////////////////////////////////////////////////////////////

public abstract class MyABC
{
    public void MyMethod(){} //normal method with definition
    public abstract void MyAbstractMethod(); //abstract methods can't be private
}
public class MyClass : MyABC
{
    //override and provide a definition
    public override void MyAbstractMethod(){} 
}
public abstract class MyClass : IMyInt
{
    //any method don't want to implement from interface can declare as abstract
    public abstract void MyIntMethod();
}

////////////////////////////////////////////////////////////////////////////////////////////
//INHERITANCE
////////////////////////////////////////////////////////////////////////////////////////////

public class Base
{
    protected int myInt;
    public virtual void MyVirtualMethod(){} //virtual members can't be private
}

//STRUCT: Can inherit multiple interfaces, no classes/structs
public struct Derived : IBase {}

//INTERFACE: Can inherit multiple classes/interfaces
public interface Derived : Base, IBase {}

//CLASS: Can inherit only one class, multiple interfaces; class must be first in list
public class Derived : Base, IBase
{   
    //call base constructor, interfaces don't have constructors
    public Derived() : base() {}

    //override virtual method; must have same visibility as base class
    public override void MyVirtualMethod(){ base.myInt = 3; } //can access using base

    //DATA HIDING
    //If base version exists; base hidden, derived version is used in place
    //All methods that don't use 'override' have newslot flag turned on by default
    public void MyVirtualMethod(){} //gives warning
    public new void MyVirtualMethod(){ base.MyVirtualMethod(); } //explicitly hide; no warning
}

////////////////////////////////////////////////////////////////////////////////////////////
//POLYMORPHISM
////////////////////////////////////////////////////////////////////////////////////////////

Base baseObj = new Derived(); //stores derived object in base class reference
baseObj.MyVirtualMethod(); //calls Derived::MyVirtualMethod()

//DOWNCAST TO DERIVED
//cast back to derived object; if conversion fails throws InvalidCastException
Derived derivedObj = (Derived)baseObj; 

//SAFE DOWNCAST TO DERIVED
//convert baseObj to Derived, returns null if conversion fails
Derived derivedObj = baseObj as Derived; 

//CHECKING TYPE OF OBJECT
if(baseObj is Derived) //if baseObj can be implicitly converted to (is a type of) Derived
object.ReferenceEquals(baseObj, derivedObj) //return true if two objs have the same address

////////////////////////////////////////////////////////////////////////////////////////////
//SEALING
////////////////////////////////////////////////////////////////////////////////////////////

public class Base
{
    public virtual void MyVirtualMethod(){}
}

//SEALING CLASSES
//Can seal whole class to prevent it being inherited from
public sealed class Derived : Base
{
    //SEALING METHODS
    //All methods are sealed by default except those with virtual/override
    //Can seal individual methods to prevent them from being further overridden
    public sealed override void MyVirtualMethod(){}
}