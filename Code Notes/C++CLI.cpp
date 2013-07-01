//////////////////////////////////////////////////////////////////////////////
//C++/CLI NOTES
//////////////////////////////////////////////////////////////////////////////
/*

VALUE-TYPE VARIABLES
• Can be both class/struct, stored on stack/registers
• Can't have user-defined destructors, constructors, ass.operators
• Can't define default constructor- values zero-ed automatically
• Auto inherits System::ValueType and cannot inherit any other base, can derive multiple interfaces

REFERENCE-TYPE VARIABLES
• Can be both class/struct, stored on heap
• Support all contructors including static constructors
• Auto derives from System::object if no other base given, can derive multiple interfaces

HANDLES
• Native equivalent is pointer (*)
• Uses ^ to point to managed objects on CLI heap
• Uses gcnew(), doesn't need delete as garbage collection takes care of it
• If object is moved by garbage collection, address referred to is changed to stay with object
• Can't convert to or from void^
• No handle arithmatic
• Dereferences using * and ->

TRACKING REFERENCES
• Native equivalent is reference/address-of operator (&)
• Uses % to refer to managed objects on CLI heap
• Uses % to get address of the object to store into handle
• If object is moved by garbage collection, address referred to is changed to stay with object

GCNEW
• Returns handle ^ to newly created object on CLR heap
• Has no array or placement form
• Can't be overloaded
• Throws System::OutOfMemoryException if can't allocate
• Creates two objects; one on managed stack and one on managed heap
• If storing a value-type, will go through C# Boxing

*/
//////////////////////////////////////////////////////////////////////////////
//CLASSES
//////////////////////////////////////////////////////////////////////////////

ref class MyClass //implicitly inherits System.Object
{
public:

    void MyFunction();

private:
    int m_myInt;
};

//REFERENCE TYPES
ref class MyClass {};   //Methods default to private
ref struct MyStruct {}; //Methods default to public

//VALUE TYPES
value class MyClass {};   //Methods default to private
value struct MyStruct {}; //Methods default to public

//INTERFACE TYPES
interface class MyClass {};   //Methods default public
interface struct MyStruct {}; //Methods default public

//ABSTRACT CLASS
//Doesn't require abstract functions to be abstract
//Must mark class as abstract if has any abstract methods
ref class MyClass abstract
{
public:
    virtual void Func() abstract;
};

//SEALED CLASS
//Stops class from being derived from
//Statically resolves any virtual methods as no derived classes
ref class MyClass sealed
{
};

//STATIC CLASS
ref class MyClass abstract sealed
{
public:
    static void Func();
}

//////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//MAIN ENTRY POINT
int main(array<System::String^> ^args){}

//DEFAULT CONSTRUCTOR
//Implicitly created for ref/value types
MyClass();

//STATIC CONSTRUCTOR
//Ref classes/structs only, no parameters, 
//work on static members, Private and auto called
static MyClass();

//COPY CONSTRUCTOR
//Not implicitly created
MyClass^ obj1 = gcnew MyClass(%obj2); //visible to native/managed
MyClass(const MyClass^ o);

MyClass^ obj1 = gcnew MyClass(obj2); //only visible to native
MyClass(const MyClass% o);

//ASSIGNMENT OPERATOR
//Not implicitly created, only visible to native
MyClass% operator=(const MyClass% o)
{
    this->x = o.x; //copy values from o to this
    return *this;
}

//////////////////////////////////////////////////////////////////////////////
//INHERITANCE
//////////////////////////////////////////////////////////////////////////////
//• No support for Multiple Inheritance; use multiple interfaces instead

//REF TYPES
//can inherit one base or System::Object by default
ref class Derived : Base {}; //defaults to public
ref class Derived : public Base {};
ref class Derived : public IBase {};

//VALUE TYPES
//inherits from System::ValueType
value class Derived : IBase {};

//////////////////////////////////////////////////////////////////////////////
//HANDLE/REFERENCES
//////////////////////////////////////////////////////////////////////////////

//HANDLES
//equivalent to pointer *
System::String^ str = "hello";        //Handle to string object on CLI heap
MyClass^ myHandle = nullptr;          //Set to null, don't use 0 as it implicitly boxes to int^ 
MyClass^ myHandle = gcnew MyClass();  //Create new object (don't need delete)
myHandle->MyFunction();               //Calling function
*myHandle                             //dereferences the handle

//TRACKING REFERENCE
//equivalent to reference &
MyClass^ myHandle = %myObject;        //used as address-of operator
MyClass% myReference = myObject;      //get reference to object
MyClass^% myHandleRef = myHandle;     //Tracking-reference to a handle