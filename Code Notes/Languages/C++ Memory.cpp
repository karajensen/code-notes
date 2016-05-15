/////////////////////////////////////////////////////////////////////////////////////////////
//POINTERS/REFERENCES
/////////////////////////////////////////////////////////////////////////////////////////////

int* ptr = NULL;                 // 0 or 0L which zeros out pointer
int* ptr = nullptr;              // store null
int* ptr = &myInt;               // store address of variable
int* ptr = new int;              // finds empty memory location on heap and allocates
int* ptr = (int*)0xB8000000;     // explicitly store memory address
int* const ptr = &value;         // Constant int pointer (can't change what ptr points to)
const int* ptr = &value;         // Pointer to a constant int (can't change value)
const int* const ptr = &value    // can't change value or what pointer points to
int** ptr = &ptr2;               // pointer to pointer
int& ref = myInt;                // cannot be reassigned, cannot be null
int& const ref = myInt;          // Redundant as references automatically & const as cannot be reassigned

*myPointer = 4;                  // dereferencing accesses variable
myPointer->member;               // access member of object
(*myPointer)->member;            // access pointer to pointer
delete myPointer;                // frees the block of memory

//POINTER TO ARRAYS
int* myArray = new int[SIZE];
delete [] myArray;
*(myArray+3) /*or*/ myArray[3] /*or*/ 3[myArray]

//POINTER TO ARRAY OF POLYMORPHIC TYPES
//Avoid as pointer arithmatic on base class arrays of derived objects
//pointer arithmatic will use sizeof(Base) not sizeof(Derived)
Base* myArray = new Derived[2];
myArray[1] = *(myArray+1)        // BAD
delete [] myArray                // BAD, also uses pointer arithmatic

//ARRAY-TO-POINTER DECAY RULE
const char myArray[] = "Array";       // note not the same type as const char*
const char* pMyArray = myArray;       // character array decays to pointer
const char rMyArray (&)[5] = myArray; // actual type of array

//DISPLAY MEMORY LOCATION
std::stringstream ss;
ss << std::hex << &myVariable;

/////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTION OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////

//FUNCTION ADDRESSES
&MyFunction;                                 // address of non-class function
(void(*)(double))&MyFunction;                // address of non-class overloaded function
&MyClass::MyMethod                           // address of class method
(void(MyClass::*)(double))&MyClass::MyMethod // address of class overloaded function

//FUNCTION-TO-POINTER DECAY RULE
void MyFunction(int);                 // Not the same type as void(*)(int)
void(*pMyFunction)(int) = MyFunction; // function decays to pointer
void(&rMyFunction)(int) = MyFunction; // actual type of function

//POINTER-TO-FUNCTION
typedef bool(*MyFunctionPtr)(int, double); /*or*/ 
using MyFunctionPtr = bool(*)(int, double);
MyFunctionPtr myFunction = &MyFunction;
myFunction(5, 1.0);

//POINTER-TO-MEMBER FUNCTION
//Cannot cast to pointer-to-function as can be much larger storing inheritance information
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
//class with operator()
struct MyFunctor
{
    bool operator()(int x) { return x > 0; }
}

//LAMBDAS
//If inside a class, may become friends to access/capture internals
//Lamda creates a closure object which holds captured vars
auto myLambda = [](int x)->float {}  // specify return type, only need if multilined
auto myLambda = [&var](int x){}      // capture only myVar by reference
auto myLambda = [=var](int x){}      // capture only myVar by value
auto myLambda = [var](int x){}       // capture only myVar by value, doesn't work on member vars
auto myLambda = [&](int x){}         // capture all by ref
auto myLambda = [=](int x){}         // capture all non-static local variables (including this) by-val

//LAMBDA INIT/GENERALISED CAPTURE
//Allows creation of variables inside the closure
auto myLambda = [var = myVar](){}           // create var and copy-assign to it, works on member vars
auto myLambda = [var = MyClass()](){}       // create var of type MyClass
auto myLambda = [var = std::move(obj)](){}  // move obj to be only used inside closure
auto myLambda = [var = std::move(vec)](){}  // move vector of objects to use inside closure

//STD::FUNCTION
//Allows all function objects to be stored in single type
//Slower and bigger than using actual function object types (lambda, functors, pointers)
std::function<double(int)> myFn = [](int x){ return x+2.0; }
std::function<double(int)> myFn = &MyFunction;

/////////////////////////////////////////////////////////////////////////////////////////////
//BINDING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////
// Creates functor by capturing address and variables (by-ref)

using namespace std::placeholders; //for _1, _2..

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
auto memberFn = std::bind(&MyClass::MyMethod, _1, _2); //_1 is always object
auto memberFn = std::bind(&MyClass::MyMethod, this, _1);
memberFn(&myObject, 2);
memberFn(2) // object is bound with method

//BINDING OVERLOADED FUNCTIONS
void MyClass::MyMethod(int x);
void MyClass::MyMethod(double x);
std::bind((void(MyClass::*)(double))&MyClass::MyMethod, this, _1);

//BINDING LAMBDAS
std::bind([](int x){}, std::move(myInt)); // move construct myVar
std::bind([](int x){}, myInt); // copy construct myVar

/////////////////////////////////////////////////////////////////////////////////////////////
//SMART POINTERS
/////////////////////////////////////////////////////////////////////////////////////////////

if(myPtr) /*or*/ if(myPtr.get()) //true if valid, false if null
*myPtr                           //dereference pointer

//UNIQUE POINTER
auto unique(std::make_unique<MyClass>());        // can't use custom deleter or {}
std::unique_ptr<MyClass> unique(new MyClass());
std::unique_ptr<int[]> p(new int[10]);           // arrays only supported by unique_ptr, calls delete[]

//SHARED POINTER
auto shared(std::make_shared<MyClass>());        // creates a new control block, can't use custom deleter or {}
std::shared_ptr<MyClass> shared(new MyClass());  // creates new control block
std::shared_ptr<MyClass> shared(unique);         // creates new control block, unique_ptr becomes null
std::shared_ptr<MyClass> shared(shared2);        // shares control block
std::shared_ptr<MyClass> shared(weak);           // shares control block, throws exception if weak_ptr expired
shared.use_count()                               // get the current count
shared.swap(shared2)                             // swap what the shared_ptr look at
shared.unique()                                  // returns true if ref count = 1, false otherwise
shared.reset()                                   // decrements ref count

//WEAK POINTER
std::weak_ptr<MyClass> weak(shared);             // observing a shared pointer control block
weak.use_count()                                 // get the current count
weak.lock()                                      // returns a shared_ptr, if expired then null
weak.expired()                                   // returns true if object has been deleted, false if okay

//AUTO POINTER
//deprecated smart pointer
//can't point to arrays due to it calling delete and not delete []
//pass auto pointers by reference otherwise copied version takes ownership and sets original to null
auto_ptr<double> ap(new double) //only use for new
*ap = 3.2;      

//RESETTING SMART POINTERS
//Changing the initial smart pointer does not change others, only decrements count
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

//SHARED THIS
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
//C-STYLE MEMORY MANIPULATION
/////////////////////////////////////////////////////////////////////////////////////////////
#include <malloc.h>

// Will not call object constructor- if needed must use new or placement new
// Will not call object destructor- call explicitly
// Cannot mix malloc/free and new/delete

memcpy(dest, src, bytes)          // Binary copy of data from src to dest over n bytes
memmove(dest, src, bytes)         // Moves memory from src to dest over n bytes
void* ptr = alloca(bytes)         // Allocate n bytes on the stack, returns void*
void* ptr = malloc(bytes)         // Allocate n bytes on the heap, returns void*
void* ptr = malloc(n*sizeof(int)) // Allocate array of n ints
free(ptr);                        // Free any memory from malloc

/////////////////////////////////////////////////////////////////////////////////////////////
//PLACEMENT NEW
/////////////////////////////////////////////////////////////////////////////////////////////
#include <new>

// Won't allocate memory- only puts newed object into section of memory given
// Classes require destructor to be called explicitly before deletion
// Any allocated memory given to it must also be cleaned up

char* buffer = new char[sizeof(MyClass)];
MyClass* obj = new (buffer) MyClass;
obj->~MyClass();
delete [] buffer;




