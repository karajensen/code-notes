/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS/STRUCT/METHODS NOTES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
ORDER OF ARGUMENT EVALUATION
• Always evaluated left to right in expressions and argument passing

STRUCTS [VALUE-TYPE]
• All variables not explicitly initialised are set to default
• struct auto defaults to public, methods default to private
• Can't create user-defined constructor/destructors
• Auto creates default constructor/destructor, System.Object methods
• Can't use member initialisation unless const/static, Struct can't be static

CLASSES [REF-TYPE]
• All variables not explicitly initialised are set to default
• class auto defaults to internal, methods default to private
• Default constructor/destructor only generated if none provided
• Auto creates default constructor/destructor, System.Object methods, operator==
• Can use member initialisation, class can be static

ABSTRACT CLASS
• Can't create object directly from abstract class, can be casted to
• Partial Implementation- Don't have to override virtual non-abstract methods
• No inheritance by structs
• Must used abstract keyword for methods and class
• Can inherit one class and implement multiple interfaces

INTERFACES
• Can't create object directly from interface, can be casted to
• No Partial Implementation- Have to implement all methods
• Can be inherited by structs though returns boxed struct
• Methods are auto abstract that derived class can only override unless derived uses virtual 
• Can extend multiple interfaces through inheritance. Can not inherit classes.
• No constructors/finalisers allowed
• No member variables, only properties which only create the variable when implemented
• No visibility accessors allowed in interface, derived defines them
• Methods can be use Implicit or Explicit Implementation
    - Implicit can only be used on one method definition
    - Explicit required if interfaces inherited have same members to avoid conflicts
    - Explicit can't use visibility, abstract, virtual keywords
    - Explicit can only be accessed if casted to interface implemented from

CLASS CONSTRUCTION
• Do not call abstract/virtual methods in constructor; undefined behaviour; calls Derived version
• If no static constructor: static members initialised anytime before first instance created
  If static constructor: called just before first instance created or static method called

1) Derived member Field Initialisaters
2) Base member Field Initialisaters
3) Base Constructor Body
4) Derived Constructor Body
5) Derived Dispose or Derived Finaliser
6) Base Dispose or Base Finaliser

OBJECT DESTRUCTION
Destructor: obtained through inheriting IDisposable, called explicitly to clean up unmanaged objects
Finaliser: called when object is garbage collected, implement for cleaning managed objects (c++ destructor syntax)

CLASS VISIBILITY
• Visibility levels: Public -> Internal -> Protected Internal -> Protected -> Private
• First-level class in namespace can only be public/internal; subclasses can be anything
• Class cannot be more visible than its base class (base interfaces excluded)
• Interface cannot be more visible than its base interface
• Virtual/Abstract methods cannot be private
• Virtual/Abstract methods must have same visibility between Base/Derived classes

PROPERTIES
• Method that doesn't use () when called
• No 'set' entry automatically makes the property readonly
• Accessed syntactically the same as member variable but involve different instructions

INDEXER/PROPERTY DIFFERENCES
• Indexer accessed through index and [], Properties accessed as though member variable
• Indexer cannot be static, Properties can be static
• Indexer passes in index value, Properties don't pass in anything, both have 'value' keyword

ATTRIBUTES
• Hidden objects at runtime that contain metadata- information about the class
• Use reflection to access

PARTIAL CLASSES
• Class can be defined over multiple files
• Must have same visibility and all use partial keyword
• Any part that declares abstract, sealed or inherits does it for all

PARTIAL METHODS
• Must be part of a partial class
• Can have ref but not out parameters
• Must be void- if definition not given, all mention of function is removed
• Are implicitly private- cannot be public
**************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASSES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//STRUCTS [VALUE-TYPE]
public struct MyStruct
{
    public int myInt; // value-types can't use member initialisation
}

//CLASSES [REFERENCE-TYPE]
namespace MyNamespace
{
    public class MyClass
    {
        //Member variables can be initialised only with static 
        //methods as object is not complete when initialised
        public int myInt = MyStaticMethod();

        #region myRegion
        #endregion

        /// <summary> MySummary </summary>
        /// <param name="value"> a value the method takes in </param>
        /// <returns> a value the method takes in </returns>

        //PRIVATE SUB-CLASS
        internal class MyPrivateClass
        {
        };
    };
}

//STATIC CLASS
//Used for global vars; vars cannot be declared without class
public static class MyStaticClass
{
    public static int myInt;
} 
MyStaticClass.myInt; //using static members

//INTERFACE CLASS
//No implementation for methods/properties
//No member variables, only properties
interface IMyClass()
{
    int MyInt { get; set; }
    int MyMethod1(); // visibility determined by derived class
    float MyMethod2();
};

public class MyClass() : IMyClass, IMyClass2
{
    public int MyInt { get { m_myint; } set { m_myint = value; }}

    public int MyMethod1() { return 10; } // Implemented method
    int IMyClass.MyMethod1() { throw NotImplementedException(); } // Explicit Implementation for Non-implemented method
    float IMyClass2.MyMethod2() {}; // Explicit Implementation for conflicts
    public float MyMethod2() {} // Implicit Implementation for conflicts
};

//ABSTRACT BASE CLASS
//class keyword is required for any abstract methods or compiler warning
//abstract methods are auto made virtual (can't be private)
public abstract class MyABC
{
    public void MyMethod(){} //normal method with definition still allowed
    public abstract void MyAbstractMethod();
}
public class MyClass : MyABC
{
    public override void MyAbstractMethod(){} //override and provide a definition
}

//PARTIAL CLASSES
//Class can be defined over multiple files
public partial class MyClasss
{
    private void MyMethod1()
    {
    }
}
public partial class MyCLass
{
    public void MyMethod2()
    {
    }
}

//APPLICATION ENTRY POINT
class Program
{
    static void Main(string[] args)
    {
        System.Console.WriteLine("Hello World!");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// METHODS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//CONVERSION FUNCTIONS
//explicit makes it require cast (int)myObj
//implicit makes it not require cast
public static implicit operator int(MyClass value)
public static explicit operator int(MyClass value)
{
    return value.myint;
}

//PARAMS VARIADIC FUNCTION
//also used for passing generic arrays
ShowParams(10, typeof(int), "hello", 123);
public void ShowParams(params object[] objects)
{
    foreach (object obj in objects)
    {
    }
}

//CONSTRUCTOR
//Structs: can only declare contructor with arguments. Default constructor auto generated
public MyClass() : this(10) //invoke another constructor (constructor chaining)
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

//FINALISER
//no visibility allowed, always virtual, can't be called expliclitly
~MyClass(){} 

//STATIC METHOD
//only deals with static variables
static public void MyStaticMethod(){}

//TO-STRING OVERRIDE
public override string ToString()
{
    return "A readable representation of myObject";
}

//PARTIAL METHODS
partial void MyMethod();     //declartion in one file
partial void MyMethod() {}   //definition in another file

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// METHOD OVERLOADING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
OVERLOAD RESOLUTION
1) Normal methods
2) Generic methods

---------------------------------------------------------------------------
ASSIGNMENT OVERLOADS
---------------------------------------------------------------------------
Can be defined: 
!   ~  ++  --  true  false

Can be defined; x= can't be defined and is auto-defineds:
+(+=)  -(-=)   *(*=)   /(/=)   %(%=)   &(&=)(&&)   |(|=)(||)  ^(^=)  >>(>>=)   <<(<<=) 

---------------------------------------------------------------------------
COMPARISON OVERLOADS
---------------------------------------------------------------------------
Must be defined in pairs:
==  != 
<  >
<=  >=

---------------------------------------------------------------------------
CAN'T BE OVERLOADED
---------------------------------------------------------------------------
=  .  ?:   ->   new   is   sizeof   typeof

() can't be overloaded but can use conversion function
[] can't be overloaded but can use indexer property
**************************************************************************************************************/

//OPERATOR OVERLOAD
public static MyClass operator ++(MyClass c)
{
c.myInt += 1;
return c;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROPERTIES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SCALAR PROPERTY
public int MyInt
{
get { return myInt; } //property field
private set { myInt = value; } //can change internal visibility
}

//TRIVIAL PROPERTY
public int MyInt { get; set; } //auto creates private variable with public setter/getters

//INTERFACE PROPERTIES
int MyInt { get; set; } //indicates whether read/write only, not allowed bodies

//INDEXER PROPERTY (OVERLOADING [])
public string this[int index]
{
get { return myStringArray[index]; }
set { myStringArray[index] = value; }
}

//2D INDEXER PROPERTY
public string this[int x, int y]
{
get { return myStringArray[y*(columns)+x]; }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INHERITANCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
STRUCTS: Inherit no classes, multiple interfaces, auto inherits System.ValueType
CLASSES: Inherit one class, multiple interfaces, auto inherits System.Object if none specified
INTERFACES: Inherit no classes, multiple interfaces

SYSTEM.OBJECT
• All reference/value types ultimately derive from System.Object
• Classes auto inherit System.Object if no base class specified
• Has Static Members ReferenceEquals()/Equals()
• Includes methods: 
Equals()
Finalize()
GetHashCode()
GetType()
MemberwiseClone()
ToString()

SYSTEM.VALUETYPE
• All value types (struct,enum,bool,int etc.) ultimately derive from System.ValueType
• System.ValueType itself derives from System.Object
• Can't directly derive from it; must derive from struct
• Overrides methods:
Equals()
GetHashCode()
ToString()

IENUMERABLE<T>
• All containers derive from it, allows iteration with foreach

SEALING
• Statically resolves any virtual methods as no derived classes
• Can seal whole class to prevent it being inherited from
• All methods are sealed by default except those with virtual/override
• Can seal individual methods to prevent them from being further overridden
**************************************************************************************************************/

public class Base
{
    protected int myInt;
    public virtual void MyMethod(){} //virtual members can't be private
    public virtual int MyProperty { get { return 0; } } //property fields can't be virtual
}
public class Derived : Base, IBase
{
    //call base constructor, interfaces don't have constructors
    public Derived() : base() {}

    //override virtual method; must have same visibility as base class
    public override void MyMethod(){ base.myInt = 3; } //can access using base

    //DATA HIDING
    //If base/interface version exists; base hidden, derived version is used in place
    //All methods that don't use 'override' have new flag turned on by default
    public void MyMethod(); //gives warning
    public new void MyMethod(); //explicitly hide; base.MyMethod() to call base method
}

//STRUCT: Can inherit multiple interfaces, no classes/structs
public struct Derived : IBase {}

//INTERFACE: Can inherit multiple classes/interfaces
public interface Derived : Base, IBase {}

//CLASS: Can inherit only one class, multiple interfaces; class must be first in list
public class Derived : Base, IBase {}

//SEALING CLASSES
//Prevents class from being derived from
public sealed class Derived : Base
{
}

//SEALING METHODS    
//Can seal individual methods to prevent them from being further overridden
public sealed override void MyVirtualMethod(){}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POLYMORPHISM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ATTRIBUTES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CREATING CUSTOM ATTRIBUTES
[System.AttributeUsage(System.AttributeTargets.Class|System.AttributeTargets.Struct, AllowMultiple = true)]
public class MyAttribute : System.Attribute
{
    private string type; //positional parameter
    public double version; //named parameter, can be explicitly set

    public MyAttribute(string type)
    {
        this.type = type;
        version = 1.0;
    }
    public MyAttrMethod(){}
}
[MyAttribute("One", version = 1.1)] //explicitly state a named parameter
[MyAttribute("Two")] //allowMultiple usage
class MyClass {}

//ACCESSING ATTRIBUTES THROUGH REFLECTION
[MyAttribute("Three")]
public class MyClass {}

System.Attribute[] attributes = System.Attribute.GetCustomAttributes(typeof(MyClass));
foreach (System.Attribute attr in attributes)
{
    if (attr is MyClass)
    {
        MyClass myClassAttr = (MyClass)attr;
        myClassAttr.MyAttrMethod();
    }
}

//SERIALIZABLE ATTRIBUTE
[System.Serializable]
public class SampleClass {}

//CONDITIONAL ATTRIBUTE
//only used if DEFINED is defined; compiler will remove any calls if not defined
//must have return type void, can't be used in interfaces/abstract classes
[System.Diagnostics.Conditional("DEFINED1"), System.Diagnostics.Conditional("DEFINED2")]
public void myConditionalMethod(){}

//CONDITIONAL DEBUG ATTRIBUTE
[Conditional("DEBUG")]
private void CheckState(){}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EQUALITY OVERLOADS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Always Overload equality for Value-types as default uses reflection
//If overloading: must also overload
operator ==(): operator!=(), Equals()
Equals():     GetHashCode(), IEquatable<T>

public class MyClass : IEquatable<MyClass>
{
    //NON-STATIC EQUALS 
    //Value-types: default compares object type/values using reflection
    //Reference-types: default compares hash codes
    public override bool Equals(object obj)
    {
        if (object.ReferenceEquals(obj, null))
            return false;
        if (object.ReferenceEquals(this, obj))
            return true;
        if (this.GetType() != obj.GetType())
            return false;
        return this.Equals(obj as MyClass);
    }

    //HASH CODE
    //returns hash int value for equality testing/indexing in a collection
    public override int GetHashCode()
    {
        return base.GetHashCode();
    }

    //OPERATOR ==/!=
    //Default version only in classes
    public static bool operator==(MyClass obj1, MyClass obj2)
    {
        if(obj1 == null || obj2 == null)
            return false;
        return obj1.Equals(obj2);
    }
    public static bool operator!=(MyClass obj1, MyClass obj2)
    {
        return !(obj1 == obj2);
    }

    //IEQUATABLE<T>
    //Used by containers
    public bool Equals(MyClass obj)
    {
        //For reference types:
        return obj.GetHashCode() == this.GetHashCode();

        //for value types:
        return (m_int == obj.m_int && m_float == obj.m_float);
    }
}

//STATIC REFERENCE EQUALITY TESTING [NEVER REDEFINE]
//Tests if both objects refer to the same internal object by comparing hash codes
//Always returns false for value-types due to boxing
public static bool ReferenceEquals(object left, object right)

//STATIC REFERENCE/VALUE-TYPE EQUALITY TESTING [NEVER REDEFINE]
//Calls ReferenceEquals() and if returns false, calls non-static Equals()
public static bool Equals(object left, object right)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GENERICS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GENERICS INHERITANCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

