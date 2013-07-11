//////////////////////////////////////////////////////////////////////////////
//C++/CLI NOTES
//////////////////////////////////////////////////////////////////////////////
/*

NATIVE/MANAGED
� C# can see C++/CLI code, Pure C++ cannot and needs a native interface
� C# include as reference, Pure C++ include native header and ensure dll is in exe directory

VALUE-TYPES
� Can be both class/struct, stored on stack/registers
� Can't have user-defined destructors, constructors, ass.operators
� Can't define default constructor- values zero-ed automatically
� Auto inherits System::ValueType and cannot inherit any other base, can derive multiple interfaces

REFERENCE-TYPES
� Can be both class/struct, stored on heap
� Support all contructors including static constructors
� Auto derives from System::object if no other base given, can derive multiple interfaces

CLASSES/STRUCTS
� Can be both value-type and reference-type
� Implicit members: default/static constructor, finaliser, System.Object members, operator==(Class Only)
� Struct members default is public, Class members default is private, overall default visibility is internal
� No friend functions allowed (includes c++ lambdas)
� No support for Multiple Inheritance; use multiple interfaces instead

CLASS OBJECT CREATION:
1) Derived Initialisation List
2) Base Initialisation List
3) Base Constructor Body
4) Derived Constructor Body
5) Derived Destructor or Derived Finaliser
6) Base Desctructor or Base Finaliser

HANDLES
� Can be used by native/managed code
� Native equivalent is pointer (*)
� Uses ^ to point to managed objects on CLI heap
� Uses gcnew(), doesn't need delete as garbage collection takes care of it
� If object is moved by garbage collection, address referred to is changed to stay with object
� Can't convert to or from void^
� No handle arithmatic
� Dereferences using * and ->

TRACKING REFERENCES
� Can be used by native code
� Native equivalent is reference/address-of operator (&)
� Uses % to refer to managed objects on CLI heap
� Uses % to get address of the object to store into handle
� If object is moved by garbage collection, address referred to is changed to stay with object

GCNEW
� Returns handle ^ to newly created object on CLR heap
� Has no array or placement form
� Can't be overloaded
� Throws System::OutOfMemoryException if can't allocate
� If used on a value-type, will create object on stack, box it and return hangle to boxed object on heap

FUNCTION OVERLOADING
Order of preference:
1) Exact match to passed in type
2) Where passed in type can be implicitly cast
3) Where passed in type is implicitly boxed

*/
//////////////////////////////////////////////////////////////////////////////
//VARIABLES/PREPROCESSOR
//////////////////////////////////////////////////////////////////////////////

#ifdef _MANAGED 
#endif

Console::Write("MyString");
Console::Write("{0}",myNumber);

using namespace System; //including managed libraries
#include <iostream> //including native libraries
class MyClass; //forward declaration
namespace /*allows anon*/ {}

//VARIABLES
//auto-initialised to zero unless in block scope
int myGlobal; //globals allowed in anon namespace
int* myPointer; //native pointer
void (*pFunction)(void) //native function pointer
delegate void MyDelegate(void) //managed delegate

//CONSTANTS
literal int myInt; //Compile-time constant (c# const)
initonly int myInt; //Runtime constant (c# readonly)

//OBJECTS
MyClass^ myObj; //C++/CLI or managed object on heap
MyClass myObj; //C++/CLI or native object on stack
MyClass* myObj; //Native object on heap
MyStruct myObj; //Managed/Native value type on stack

//LOOPS
for(int i = 0; i < myInt; ++i){}
for each(int value in myArray){}
for each(MyClass^% item in myArray){} //use only MyClass^ for read only looping

//SWITCH STATEMENT
switch(myInt)
{
case 1:
case 2:
    break;
default:
}

//ENUMS
enum MyNativeEnum
{
    ONE,
    TWO
};
private enum class MyManagedEnum
{
    ONE,
    TWO
};

//////////////////////////////////////////////////////////////////////////////
//CASTING
//////////////////////////////////////////////////////////////////////////////

//SAFE CAST
//will throw System::InvalidCastException if conversion fails
safe_cast<Derived^>(myBase);
safe_cast<double>(myFloat);
int myInt = *safe_cast<int^>(boxedInt); //use for unboxing

//DYNAMIC CAST
//returns nullptr if conversion fails, for pointers/handles only
dynamic_cast<Derived^>(myBase)

//SAFE CAST
//no checking is done
static_cast<double>(myFloat);

//////////////////////////////////////////////////////////////////////////////
//C++/CLI ARRAY
//////////////////////////////////////////////////////////////////////////////

//inherits from System::Array
//can only store managed types/native pointers (doesn't call delete)
cli::array<int>^ myArray = gcnew cli::array<int>(4) //value-type array
cli::array<MyClass^>^ myArray = gcnew cli::array<MyClass^>(4) //reference-type array
cli::array<String^> myArray; //sits on the stack

myArray[0];
myArray->Length //number of elements

System::Array::Sort(myArray);
System::Array::BinarySeach(myArray, 2);

//////////////////////////////////////////////////////////////////////////////
//HANDLE/REFERENCES
//////////////////////////////////////////////////////////////////////////////

//HANDLES
//can be used by native/managed
//equivalent to pointer *
System::String^ str = "hello";        //Handle to string object on CLI heap
MyClass^ myHandle = nullptr;          //Set to null, don't use 0 as it implicitly boxes to int^ 
MyClass^ myHandle = gcnew MyClass();  //Create new object (don't need delete)
myHandle->MyFunction();               //Calling function
*myHandle                             //dereferences the handle

//TRACKING REFERENCE
//can be used by native
//equivalent to reference &
MyClass^ myHandle = %myObject;        //used as address-of operator
MyClass% myReference = myObject;      //get reference to object
MyClass% myReference = *myHandle;     //get reference to object
MyClass^% myHandleRef = myHandle;     //Tracking-reference to a handle

//BOXING
//storing a value-type into a reference-type
System::Object^ boxedInt = 10; //implicit boxings
int myInt = *safe_cast<int^>(boxedInt); //explicit unboxing 

//CONVERTING TO NATIVE POINTER
cli::pin_ptr<MyClass> pinned = &myObject; //prevent gc from moving/deleting object
cli::pin_ptr<int> pinned = &myArray[0];  //prevent gc from moving/deleting array
int* native = pinned;
int* lastElement = native + myArray->Length

//////////////////////////////////////////////////////////////////////////////
//CLASSES
//////////////////////////////////////////////////////////////////////////////
//overall class/struct visibility defaults to internal

//REFERENCE TYPES
public ref class MyClass {};   //Methods default to private
public ref struct MyStruct {}; //Methods default to public

//VALUE TYPES
public value class MyClass {};   //Methods default to private
public value struct MyStruct {}; //Methods default to public

//INTERFACE TYPES
interface class MyClass {};   //Methods default public
interface struct MyStruct {}; //Methods default public

//ABSTRACT CLASS
//Doesn't require abstract functions to be abstract
//Any abstract methods require keyword for class
ref class MyClass abstract
{
public:
    virtual void Func() abstract; //virtual required for abstract methods
};

//SEALED CLASS
//Stops class from being derived from
//Statically resolves any virtual methods as no derived classes
ref class MyClass sealed
{
};

//STATIC CLASS
//only static members
ref class MyClass abstract sealed
{
}

//////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//MAIN ENTRY POINT
int main(array<System::String^> ^args){}

//PASSING BY-REFERENCE
//Passing value-types will
System::Object% MyFunction(System::Object% obj); //can't be used on value types
System::Object^ MyFunction(System::Object^ obj); //will box value types

//PASSING ARRAYS
void MyFunction(cli::array<MyClass^>^% myArray);
void MyFunction(System::Array^ myArray);

//VARIADIC FUNCTION
//using a parameter array
void MyFunction(...array<int>^ myArray)
{
    for(int i = 0; i < myArray->Length; ++i)
    {
        Console::Write("{0}",myArray[i]);
    }
}
MyFunction(0,1,4,3);

//DEFAULT CONSTRUCTOR
//Implicitly created for ref/value types
MyClass();
MyClass::MyClass() : 
    m_int(0)
{
}

//STATIC CONSTRUCTOR
//Ref classes/structs only, no parameters, 
//work on static members, Private and auto called
//Auto created with a static class member
//Don't use initialisation list and requires static keyword
static MyClass();
static MyClass::MyClass()
{ 
    m_myInt = 0; 
}

//COPY CONSTRUCTOR
//Not implicitly created
MyClass(const MyClass^ o);
MyClass^ obj1 = gcnew MyClass(%obj2); 

MyClass(const MyClass% o);
MyClass^ obj1 = gcnew MyClass(obj2);

//ASSIGNMENT OPERATOR
//Not implicitly created
MyClass% operator=(const MyClass% o)
{
    if(%o == this)
    {
        return *this;
    }
    this->x = o.x; //copy values from o to this
    return *this;
}

//////////////////////////////////////////////////////////////////////////////
//PROPERTIES
//////////////////////////////////////////////////////////////////////////////

//TRIVIAL PROPERTY
//auto creates simple public get/set method for MyDouble
//auto creates private variable '<backing_store>MyDouble' with the quotes
property double MyDouble; 

//SCALAR PROPERTY
//converts name to get_MyInt/set_MyInt which cannot be used
//internal visibility can't be more visible than outside
int m_myInt;
property int MyInt
{
    int get(){ return m_myInt; } //public by default
private:
    void set(int x){ m_myInt = x; }
}

//STATIC PROPERTIES
//only on static members
static property int MyStaticInt
{
public:
    int get(){ return m_staticInt; }
    void set(int x){ m_staticInt = x; }
}

//INDEXER PROPERTY
property float MyArray[int]
{
    int get(int index){ return m_myArray[index]; }
    void set(int index, float value){ m_myArray[index] = value; }
}
myObj->MyArray[i] //usage

//INDEXER PROPERTY (OVERLOADING [])
property float default[int]
{
    int get(int index){ return m_myArray[index]; }
    void set(int index, float value){ m_myArray[index] = value; }
}
myObj[i] //usage

//VIRTUAL PROPERTIES
virtual property int BaseInt
{
    int get(){ return m_baseInt; } //implicitly virtual
    void set(int x){ m_baseInt = x; } //implicitly virtual
}
virtual property int DerivedInt
{
    int get() override { return m_deriInt; } //override required
    void set(int x) override { m_deriInt = x; } //override required
}

//////////////////////////////////////////////////////////////////////////////
//INHERITANCE
//////////////////////////////////////////////////////////////////////////////

// Virtual Methods can have any visibility
// Private virtual must be sealed otherwise warning 
// Derived must have same or higher visibility than base
// Destructors are always virtual
ref class Base
{
public:
    virtual void MyFunction(){}
};

ref class Derived : public Base
{
public:
    virtual void MyFunction() override {}
};

//REF TYPES
//can inherit one base or System::Object by default
ref class Derived : Base {}; //defaults to public
ref class Derived : public Base {};
ref class Derived : public IBase {};

//VALUE TYPES
//inherits from System::ValueType
value class Derived : IBase {};

//////////////////////////////////////////////////////////////////////////////
//CALLBACKS
//////////////////////////////////////////////////////////////////////////////

//Prevent delegate from being moved/deleted by garbage collector
Action^ myDelegate = myFunction();
GCHandle delegateHandle = System::Runtime::InteropServices::GCHandle::Alloc(myDelegate);

//Converting managed delegate to native
System::IntPtr ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(myDelegate);
typedef void (*VoidFn)(void); //cannot use std::function as considered friend function (not allowed)
VoidFn callback = static_cast<VoidFn>(ptr.ToPointer()); //ToPointer() returns void* 
std::function<void(void)> nativeCallback = callback; //convert to std::function in native class

//Free handle to delegate for garbage collector to reclaim
if(delegateHandle.IsAllocated)
{
    delegateHandle.Free();
}

//////////////////////////////////////////////////////////////////////////////
//DESTRUCTION
//////////////////////////////////////////////////////////////////////////////

//DESTRUCTOR
//Destructor called by Dispose()/delete or object on stack going out of scope
//if implemented, class inherits IDisposable and overrides Dispose() which calls ~MyClass()
~MyClass()
{
    //will suppress GC call of finalisation implicitly (GC.SuppressFinalize(this))
    //'this' important otherwise seen as ! operator
    this->!MyClass(); 
}

//FINALISER
//Finaliser called by GC if on the heap and destructor hasn't been called
//implicit finaliser inherited from System.Object
//will always be non-public even if under public section
//warning given if implementing without creating a destructor
!MyClass()
{
    if(myNativeObj)
    {
        delete myNativeObj;
        myNativeObj = nullptr;
    }
}

MyClass^ obj = gcnew MyClass; //C++/CLI: calls finaliser
MyClass obj = new MyClass; //C#: calls finaliser
MyClass^ obj = gcnew MyClass; delete obj; //C++/CLI: calls destructor
MyClass obj = new MyClass; obj.Dispose(); //C#: calls destructor
MyClass obj; //C++/CLI: calls destructor