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
//No set method auto makes it readonly

//GETTER/SETTER PROPERTIES
public int MyInt
{
    get { return myInt; }
    set { myInt = value; }
}

//INTERFACE PROPERTIES
//no body; indicates whether read/write only
int MyInt
{
    get;
    set;
}

//INDEXER PROPERTY (OVERLOADING [])
public string this[int index]
{
    get { return myStringArray[index]; }
    set { myStringArray[index] = value; }
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

////////////////////////////////////////////////////////////////////////////////////////////
//ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////////////////

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
//only used if DEFINED is defined; compiler will remove any method
//calls if not defined. Useful for doing diagnostics only in debug
[System.Diagnostics.Conditional("DEFINED1"), System.Diagnostics.Conditional("DEFINED2")]
public void myConditionalMethod(){}

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

