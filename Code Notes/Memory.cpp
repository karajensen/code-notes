/////////////////////////////////////////////////////////////////////////////////////////////
//POINTERS
/////////////////////////////////////////////////////////////////////////////////////////////

int* myPoint = NULL; //0 or 0L which zeros out pointer
int* myPointer = nullptr; //store null
int* myPointer = &myInt;  //store address of variable
int* myPointer = new int; //finds empty memory location on heap and allocates
int* myPointer = (int*)0xB8000000; //explicitly store memory address

*myPointer = 4; //dereferencing accesses variable
&myPointer; //gives address of pointer
myPointer->member; //access member if object
delete myPointer; //frees the block of memory

//CONST POINTERS
const int* ptr = &value; //Pointer to a constant int (can't change value)
int* const ptr = &value; //Constant int pointer (can't change what ptr points to)
const int* const ptr = &value //can't change value or what pointer points to

//POINTER TO ARRAYS
int* myArray = new int[SIZE]; 
int** myArrayPointer = &myArray;
delete [] myArray; //free array
*(myArray+3) /*or*/ myArray[3] /*or*/ 3[myArray] //to access elements

//POINTER TO ARRAY OF POLYMORPHIC TYPES
//Avoid as pointer arithmatic on base class arrays of derived objects
//pointer arithmatic will use sizeof(Base) not sizeof(Derived)
Base* myArray = new Derived[2];
myArray[1] = *(myArray+1) //BAD
delete [] myArray //BAD, also uses pointer arithmatic

//ARRAY-TO-POINTER DECAY RULE
const char myArray[] = "Array";  // note not the same type as const char*
const char* pMyArray = myArray;  // character array decays to pointer
const char rMyArray (&)[5] = myArray; // actual type of array

/////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTION OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////

//FUNCTION ADDRESSES
&MyFunction;                                 // address of non-class function
(void(*)(double))&MyFunction;                // address of non-class overloaded function
&MyClass::MyMethod                           // address of class method
(void(MyClass::*)(double))&MyClass::MyMethod // address of class overloaded function

//FUNCTION-TO-POINTER DECAY RULE
void MyFunction(int);  // Not the same type as void(*)(int)
void(*pMyFunction)(int) = MyFunction; // function decays to pointer
void(&rMyFunction)(int) = MyFunction; // actual type of function

//POINTER-TO-FUNCTION
typedef bool(*MyFunctionPtr)(int, double); /*or*/ 
using MyFunctionPtr = bool(*)(int, double);

MyFunctionPtr myFunction = &MyFunction;
myFunction(5, 1.0);

//POINTER-TO-MEMBER FUNCTION
class MyClass
{
public:
    typedef void(MyClass::*MyMethodPtr)(); /*or*/ 
    using MyMethodPtr = void(MyClass::*)(void);

    MyMethodPtr m_methodFn;
};
m_methodFn = &MyClass::MyMethod;
(myObject.*m_methodFn)();
(myObjectPtr->*m_methodFn)();

//FUNCTOR
//Function with operator()
struct MyFunctor
{
    bool operator()(int x) { return x > 0; }
}

//LAMBDAS
//• Can't use auto with binding, must use std::function type
//• If inside a class, may become friends to access/capture internals
//• Lamda creates a closure object
auto myLambda = [](int x)->double {}      // specify return type, only need if multilined
auto myLambda = [&myVar](int x){}         // capture only myVar by reference
auto myLambda = [=myVar](int x){}         // capture only myVar by value
auto myLambda = [myVar](int x){}          // capture only myVar by value, doesn't work on member vars
auto myLambda = [&](int x){}              // capture all by ref
auto myLambda = [=](int x){}              // capture all non-static local variables (including this) by-val
auto myLambda = [myVar = myVar](int x){}  // Generalized capture: copy myVar into the closure, works on member vars

//STD::FUNCTION
//• Allows all function objects to be stored in single type
//• Slower and bigger than using actual function object types (lambda, functors, pointers)
std::function<double(int)> myFn = [](int x){ return x+2.0; }
std::function<double(int)> myFn = &MyFunction;

/////////////////////////////////////////////////////////////////////////////////////////////
//BINDING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////
// Creates functor by capturing address and variables

using namespace std::placeholders; //for _1, _2...
void MyFunction(int x, double y, float z);

//SETTING ALL ARGUMENTS
auto fullFn = std::bind(&MyFunction, 1, 10.0, 2.0);
fullFn();

//FULL BINDING
auto fullFn = std::bind(&MyFunction, _1, _2, _3); //_n maps to argument given
fullFn(1,10.0,2.0); //use same as MyFunction, passes by-val default
fullFn(1,10.0,std::cref(myFloat)); //pass in argument by-ref

//PARTIALLY BINDING
auto partialFn = std::bind(&MyFunction, _1, 10.0, _2); //map only two arguments
partialFn(1,2.0); //only requires two arguments, middle is auto given

//CHANGING ARGUMENT ORDER
auto orderChangedFn = std::bind(&MyFunction, _3, _1, _2); //rearranges order of arguments
orderChangedFn(1,10.0,2.0); //becomes MyFunction(2.0,1,10.0)

//BINDING CLASS FUNCTIONS
typedef std::function<void(int)> MyFn;
auto memberFn = std::bind(&MyClass::MyMethod, _1, _2); //_1 is always object
memberFn(&myObject, 2);

//BINDING CLASS OBJECT TO CLASS FUNCTION
typedef std::function<void(int)> MyFn;
auto memberFn = std::bind(&MyClass::MyMethod, this, _1);
auto memberFn = std::bind(&MyClass::MyMethod, &myObject, _1);
memberFn(2) // object is bound with method

//BINDING OVERLOADED FUNCTIONS
void MyClass::MyMethod(int x);
void MyClass::MyMethod(double x);
std::bind((void(MyClass::*)(double))&MyClass::MyMethod, this, _1);

/////////////////////////////////////////////////////////////////////////////////////////////
//SMART POINTERS
/////////////////////////////////////////////////////////////////////////////////////////////

if(myPtr) /*or*/ if(myPtr.get()) //true if valid, false if null
*myPtr                           //dereference pointer

//UNIQUE POINTER
auto unique(std::make_unique<MyClass>());        // can't use custom deleter or {}
std::unique_ptr<MyClass> unique(new MyClass());

//SHARED POINTER
auto shared(std::make_shared<MyClass>());        // creates a new control block, can't use custom deleter or {}
std::shared_ptr<MyClass> shared(new MyClass());  // creates new control block
std::shared_ptr<MyClass> shared(unique);         // creates new control block, unique_ptr becomes null
std::shared_ptr<MyClass> shared(myRawPtr);       // creates new control block
std::shared_ptr<MyClass> shared(shared2);        // shares control block
std::shared_ptr<MyClass> shared(weak);           // shares control block, throws exception if weak_ptr expired
shared.use_count()   // get the current count
shared.swap(sp2)     // swap sp1 and sp2
shared.unique()      // returns true if ref count = 1, false otherwise
shared.reset()       // decrements ref count to 0, deletes object

//WEAK POINTER
//observing a shared pointer
std::weak_ptr<MyClass> weak(shared);
weak.use_count()    //get the current count
weak.lock()         //returns a shared_ptr, if expired then null
weak.expired()      //returns true if object has been deleted, false if okay

//CASTING SMART POINTERS
std::shared_ptr<Base> ptr(new Derived());
std::shared_ptr<Derived> dptr = std::dynamic_pointer_cast<Base>(ptr) //returns null if unsuccessful

// RESETTING SMART POINTERS
// Changing the initial smart pointer does not change others
std::shared_ptr<double> shared1(new double(2.0));
std::shared_ptr<double> shared2(shared1);
std::weak_ptr<double> weak(shared1);
shared1.reset(new double(4.0));
double value = *shared1;         // return 4.0
double value = *shared2;         // return 2.0
double value = *weak.lock();     // return 2.0

//CREATING CUSTOM DELETERS
//Without a deleter, plain 'delete' is implicitely called
//Deleter becomes part of type for unique_ptr
auto Release = [](MyClass* obj){ obj->Release(); }
std::shared_ptr<MyClass> shared(&myObject, Release);
std::unique_ptr<MyClass, decltype(Release)> unique(&myObject, Release);

//CALLING PRIVATE DESTRUCTOR WITH DELETER
class MyClass
{
private:
    ~MyClass(){}

    class MyClassDeleter
    {
    public:
        void Release();
    };
    friend class MyClassDeleter;
};

//CYCLIC DEPENDENCIES
class WeakClass;
class SharedClass
{
public:
    std::shared_ptr<WeakClass> sp;
};
class WeakClass
{
public:
    //using another shared pointer creates a cyclic dependency where
    //the reference counter never reaches 0 and the object is not destroyed
    std::shared_ptr<SharedClass> sp;

    //using a weakpointer prevents this
    std::weak_ptr<SharedClass> wp;
};

//CREATING SHARED_PTR FROM THIS
//Used when storing this pointer both internally and externally as shared_ptr to prevent double deletion
//Looks up control block for object in first shared_ptr, throws exception if one not found
//Uses Curiously recurring template pattern (CRTP)
class MyClass : public std::enable_shared_from_this<MyClass>
{
    std::vector<std::shared_ptr<MyClass>> sm_vector;
    MyClass()
    {
        sm_vector.emplace_back(shared_from_this());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//AUTO POINTER [DEPRECATED]
/////////////////////////////////////////////////////////////////////////////////////////////

//pass auto pointers by reference otherwise takes ownership and sets to null
#include <memory>
auto_ptr<double> ap(new double) //only use for new
*ap = 3.2;                      

//LIMITATIONS
auto_ptr<int> pia(new int[20]); //can’t point to arrays due to it 
                                //calling delete and not delete []
int rigue = 7; 
auto_ptr<int> pr(&rigue); //can’t point to memory on the stack

auto_ptr<int> p1(p2); //ownership is passed to p1 and p2 is set to nullptr

/////////////////////////////////////////////////////////////////////////////////////////////
//C-STYLE MEMORY ALLOCATION
/////////////////////////////////////////////////////////////////////////////////////////////
#include <malloc.h>

int* pPointer = (int*)malloc(allocationSizeInBytes); //Allocating memory
free(pPointer); //Freeing memory
int* pPointer = (int*)realloc(pPointer,numberOfExtraElements); //Resizing memory
int* pDestination = (int*)memmove(pDestination,pSource,SizeInBytes); //Moving memory
int* pPointer = (int*)realloc(allocationSizeInBytes); //Reallocating memory

/////////////////////////////////////////////////////////////////////////////////////////////
//PLACEMENT NEW
/////////////////////////////////////////////////////////////////////////////////////////////
#include <new>

// PLACING OBJECT IN EXISTING MEMORY
// Puts newed object into section of memory given
// Auto deleted when goes out of scope
obj->~MyClass() // Classes require destructor to be called explicitly before goes out of scope

// Any new/malloc memory is guaranteed to be properly aligned for the chosen type
char* MyBuffer = new char[sizeof(MyClass)];
auto* obj = new (MyBuffer) MyClass;

// Buffers on stack have no guarantee and may not be aligned for MyClass
char MyBuffer[sizeof(MyClass)];
auto* obj = new (&MyBuffer[0]) MyClass; 