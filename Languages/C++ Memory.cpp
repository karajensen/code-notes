
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEMORY ALLOCATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
VARIABLES / OBJECTS: &name gives address of object
C - STYLE ARRAY: name gives address of first element
CSTRING / STRING LITERAL: name gives string, &name gives address of first character

POINTERS / REFERENCES DIFFERENCES
• Pointers hold a memory address; reference is another name for variable.
• Pointer must be dereferenced, reference just uses name
• References can't change once initialised. Pointers can change what they point to.s
• References can't easily be nullptr or void, pointers can
• Pointers use -> for classes / structures while references use .

NEW AND DELETE
• Don’t use delete to free memory that new didn’t allocate.
• Don’t use delete to free the same block of memory twice in succession.
• Use delete[] if you used new[] to allocate an array.
• Use delete (no brackets) if you used new to allocate a single entity.
• It’s safe to apply delete to the null pointer(nothing happens).

MEMSET
• memset used to zero out memory or wipe sensitive data
• Can be optimised out by compilier if deemed not affecting program
• Dangerous to use on non - POD types due to wiping hidden members(vptr etc)
• memset_s never optimised

RESOURCE ACQUISITION IS INITIALIZATION(RAII)
• Aquiring and owning a resource means cleaning that resource up properly
• If an exception is thrown or return happens, 'delete' may never be called
• Resource cleaning needs to be tied to the lifespace of objects for automatic allocation / deletion
• Vital for exception and thread safe code
**************************************************************************************************************/

// POINTERS/REFERENCES
int* ptr = NULL;                 // 0 or 0L which zeros out pointer
int* ptr = nullptr;              // store null of type std::nullptr_t
int* ptr = &myInt;               // store address of variable
int* ptr = new int;              // finds empty memory location on heap and allocates
int* ptr = (int*)0xB8000000;     // explicitly store memory address
int* const ptr = &value;         // Constant int pointer (can't change what ptr points to)
const int* ptr = &value;         // Pointer to a constant int (can't change value)
const int* const ptr = &value;   // can't change value or what pointer points to
int** ptr = &ptr2;               // pointer to pointer
int& ref = myInt;                // cannot be reassigned, cannot be null
int& const ref = myInt;          // Redundant as references automatically & const as cannot be reassigned
void* ptr = &myInt;              // Typeless pointer, only safe to cast to and from original pointer type

*myPointer = 4;                  // dereferencing accesses variable
myPointer->member;               // access member of object
(*myPointer)->member;            // access pointer to pointer
delete myPointer;                // frees the block of memory

// POINTER TO ARRAYS
int* myArray = new int[SIZE];
delete [] myArray;
*(myArray+3) /*or*/ myArray[3] /*or*/ 3[myArray]

// POINTER TO ARRAY OF POLYMORPHIC TYPES
// Avoid as pointer arithmatic on base class arrays of derived objects
// pointer arithmatic will use sizeof(Base) not sizeof(Derived)
Base* myArray = new Derived[2];
myArray[1] = *(myArray+1)        // BAD
delete [] myArray                // BAD, also uses pointer arithmatic

// ARRAY-TO-POINTER DECAY RULE
const char myArray[] = "Array";       // note not the same type as const char*
const char* pMyArray = myArray;       // character array decays to pointer
const char rMyArray (&)[5] = myArray; // actual type of array

// DISPLAY MEMORY LOCATION
std::stringstream ss;
ss << std::hex << static_cast<void*>(&myVariable)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION ADDRESSES
&MyFunction;                                 // address of non-class function
(void(*)(double))&MyFunction;                // address of non-class overloaded function
&MyClass::MyMethod                           // address of class method
(void(MyClass::*)(double))&MyClass::MyMethod // address of class overloaded function

// FUNCTION-TO-POINTER DECAY RULE
void MyFunction(int);                 // Not the same type as void(*)(int)
void(*pMyFunction)(int) = MyFunction; // function decays to pointer
void(&rMyFunction)(int) = MyFunction; // actual type of function

// POINTER-TO-FUNCTION
typedef bool(*MyFunctionPtr)(int, double); /*or*/ 
using MyFunctionPtr = bool(*)(int, double);
MyFunctionPtr myFunction = &MyFunction;
myFunction(5, 1.0);

// POINTER-TO-MEMBER FUNCTION
// Cannot cast to pointer-to-function as can be much larger storing inheritance information
// Cannot take address of contructor
class MyClass
{
public:
    typedef void (MyClass::*MyConstMethodPtr)() const;
    typedef void(MyClass::*MyMethodPtr)();
    using MyMethodPtr = void(MyClass::*)(void);
    
    MyMethodPtr m_methodFn;
};
m_methodFn = &MyClass::MyMethod;
(myObject.*m_methodFn)();
(myObjectPtr->*m_methodFn)();

// FUNCTOR
// class with operator()
struct MyFunctor
{
    bool operator()(int x) { return x > 0; }
}

// STD::FUNCTION
// Allows all function objects to be stored in single type
// Slower and bigger than using actual function object types (lambda, functors, pointers)
std::function<double(int)> fn = [](int x){ return x+2.0; }
std::function<double(int)> fn = &MyFunction;
std::function<double(int)> fn = myLambda; // Copies the lambda
std::function<double(int)> fn = std::ref(myLambda); // Assigns lambda without copy
typedef double(MyFnType)(int); // Typedef for function return/params
typedef std::function<MyFnType> MyFn; // Typedef for std::function

// LAMBDAS
// If inside a class, may become friends to access/capture internals
// Implicitly constexpr where possible (c++17)
// Lamda creates a closure object which holds captured vars, byval captured 'const' unless 'mutable' used
auto fn = []{}                             // Only need () with arguments, only need -> if multilined
auto fn = [](int x) ->float {}             // specify return type
auto fn = [&y](int x){}                    // capture only y by reference
auto fn = [&y = as_const(y)](int x) {}     // same as &y but const
auto fn = [=y](int x){}                    // capture only y by value, = optional, doesn't work on class members
auto fn = [y] mutable (int x){}            // capture by-val but allow modifying the values
auto fn = [&](int x){}                     // capture all by ref
auto fn = [=](int x){}                     // capture all non-static local variables (including this) by-val
auto fn = [](int x) constexpr {}           // Forces constexpr with error if not
constexpr auto fn = [](int x) constexpr {} // Make init of fn also constexpr

// LAMBDA CAPTURE THIS
auto fn = [this](int x) {}                 // Capture this pointer by-value
auto fn = [*this](int x) {}                // Same as self = *this, but without having to do self.value
auto fn = [this, *this](int x) {}          // Error

// LAMBDA GENERALISED CAPTURE
// Allows creation of variables inside the closure
auto fn = [var = myVar](){}           // create var and copy-assign to it, works on member vars
auto fn = [var = MyClass()](){}       // create var of type MyClass
auto fn = [var = std::move(obj)](){}  // move obj to be only used inside closure

// LAMBDA RECURSION
std::function<int(int)> fn;
fn = [&fn](int value)->int 
{
    return value < 0 ? fn(--value) : 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BINDING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creates functor by capturing address and variables (by-ref)

using namespace std::placeholders; // for _1, _2..

// SETTING ALL ARGUMENTS
auto fullFn = std::bind(&MyFunction, 1, 10.0, 2.0);
fullFn();

// FULL BINDING
auto fullFn = std::bind(&MyFunction, _1, _2, _3); // _n maps to argument given
fullFn(1,10.0,2.0); // use same as MyFunction, passes by-val default
fullFn(1,10.0,std::cref(myFloat)); // pass in argument by-ref

// PARTIALLY BINDING
auto partialFn = std::bind(&MyFunction, _1, 10.0, _2); // map only two arguments
partialFn(1,2.0); // only requires two arguments, middle is auto given

// CHANGING ARGUMENT ORDER
auto orderChangedFn = std::bind(&MyFunction, _3, _1, _2); // rearranges order of arguments
orderChangedFn(1,10.0,2.0); // becomes MyFunction(2.0,1,10.0)

// BINDING CLASS FUNCTIONS
auto memberFn = std::bind(&MyClass::MyMethod, _1, _2); // _1 is always object
auto memberFn = std::bind(&MyClass::MyMethod, this, _1);
memberFn(&myObject, 2);
memberFn(2) // object is bound with method

// BINDING OVERLOADED FUNCTIONS
void MyClass::MyMethod(int x);
void MyClass::MyMethod(double x);
std::bind((void(MyClass::*)(double))&MyClass::MyMethod, this, _1);

// BINDING LAMBDAS
std::bind([](int x){}, std::move(myInt)); // move construct myVar
std::bind([](int x){}, myInt); // copy construct myVar

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SMART POINTERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
UNIQUE/SCOPED POINTER
• Has sole ownership of memory allocated, can only be moved
• By default are same size as raw pointers and call 'delete' on destruction
• Deleter is part of unique_ptr type and can change its size
• Has version for pointer and version for array
• Can be converted to shared_ptr
• If type is forward declared, implicit methods (ie. destructor) inlined 
  in .h may use static_assert which require the full type. Declare these 
  functions =default in the .cpp file (MyClass::~MyClass() = default;)

SHARED POINTER
• Reference counted shared ownership of memory allocated, can be copied/moved
• Hold two raw pointers: one to memory, one to control block
• Control block dynamically allocated only once on first pointer creation
• Control block holds holds reference count, weak count, deleter, memory allocator
• Control block uses virtual inheritance
• Modifying reference count is thread-safe atomic operation (slower)
• Deleter is not part of type and does not require full type for implicit methods
• Has only version for pointer (doesn't support arrays)
• Can't detect cyclic dependencies
• Can't be converted to unique_ptr
• new allocates memory twice while make_shared allocates memory for control block and object together
• When reference count is 0, memory/control block deleted unless weak count > 0 then 
  holds onto control block (and object memory if allocated together)

WEAK POINTER
• Non-owning observers of an object owned by shared_ptr
• Hold two raw pointers: one to memory, one to control block
• Creates shared_ptr when using
• Only contribute to weak count which may prevent releasing of object memory
• When object is deleted, all pointers are marked as invalid
• Useful when having cyclic dependencies and in place of raw pointers

INTRUSIVE POINTER
• Shared pointer where reference counting is not done by the pointer object
• Helper function is used which is defined by the object that is pointed to

AUTO POINTER
• Deprecated smart pointer
• Has sole ownership of the object which is passed if the pointer is copied
• Pass auto pointers by reference otherwise copied version takes ownership and sets original to null
• Can't point to arrays due to it using delete, not delete []
• Can't point to memory on the stack
• Can't be used in STL containers due to it's transfer ownership property

ARRAY POINTERS
• boost scoped_array; Simple sole ownership of arrays. Noncopyable.
• boost shared_array; Array ownership shared among multiple pointers.

SMART POINTER DESTRUCTION
• Calls delete by default (unless deleter given) on loss of scope/reference count 0
• If local in a noexcept function which throws may not be destroyed
• If std::abort, std::exit, std::quick_exit is called will not be destroyed
**************************************************************************************************************/

*myPtr
if(myPtr) /*or*/ if(myPtr.get())                 // true if valid, false if null
std::dynamic_pointer_cast<MyClass>(ptr);         // returns cast or null from base to derived class
std::static_pointer_cast<MyClass>(ptr);

// UNIQUE POINTER
auto unique(std::make_unique<MyClass>());        // can't use custom deleter or {}
std::unique_ptr<MyClass> unique(new MyClass());
std::unique_ptr<int[]> p(new int[10]);           // arrays only supported by unique_ptr, calls delete[]
unique.reset()                                   // releases and deletes the memory
unique.release();                                // releases and doesn't delete the memory, returns a raw pointer

// SHARED POINTER
auto shared(std::make_shared<MyClass>());        // creates a new control block, can't use custom deleter or {}
std::shared_ptr<MyClass> shared(new MyClass());  // creates new control block
std::shared_ptr<MyClass> shared(unique);         // creates new control block, unique_ptr becomes null
std::shared_ptr<MyClass> shared(shared2);        // shares control block
std::shared_ptr<MyClass> shared(weak);           // shares control block, throws exception if weak_ptr expired
shared.use_count()                               // get the current count
shared.swap(shared2)                             // swap what the shared_ptr look at
shared.unique()                                  // returns true if ref count = 1, false otherwise
shared.reset()                                   // decrements ref count

// WEAK POINTER
std::weak_ptr<MyClass> weak(shared);             // observing a shared pointer control block
weak.use_count()                                 // get the current count
weak.lock()                                      // returns a shared_ptr, if expired then null
weak.expired()                                   // returns true if object has been deleted, false if okay

// AUTO POINTER
auto_ptr<double> ap(new double) //only use for new
*ap = 3.2;

// CREATING CUSTOM DELETERS
// Without a deleter, plain 'delete' is implicitely called
// Deleter becomes part of type for unique_ptr
auto Release = [](MyClass* obj){ obj->Release(); }
std::shared_ptr<MyClass> shared(&myObject, Release);
std::unique_ptr<MyClass, decltype(Release)> unique(&myObject, Release);

// CYCLIC DEPENDENCIES
class WeakClass;
class SharedClass
{
public:
    std::shared_ptr<WeakClass> sp;
};
class WeakClass
{
public:
    // using another shared pointer creates a cyclic dependency where
    // the reference counter never reaches 0 and the object is not destroyed
    std::shared_ptr<SharedClass> sp;

    // using a weakpointer prevents this
    std::weak_ptr<SharedClass> wp;
};

// SHARED THIS
// Used when storing this pointer both internally and externally as shared_ptr to prevent double deletion
// Looks up control block for object in first shared_ptr, throws exception if one not found
// Uses Curiously recurring template pattern (CRTP)
class MyClass : public std::enable_shared_from_this<MyClass>
{
    std::vector<std::shared_ptr<MyClass>> sm_vector;
    MyClass()
    {
        sm_vector.emplace_back(shared_from_this());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C-STYLE MEMORY MANIPULATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <malloc.h>

// Will not call object constructor- if needed must use new or placement new
// Will not call object destructor- call explicitly
// Cannot mix malloc/free and new/delete
        
memset(dest, '\0', bytes)         // Fill memory over bytes with value
memcpy(dest, src, bytes)          // Binary copy of data from src to dest over n bytes
memmove(dest, src, bytes)         // Moves memory from src to dest over n bytes
void* ptr = alloca(bytes)         // Allocate n bytes on the stack, returns void*
void* ptr = malloc(bytes)         // Allocate n bytes on the heap, returns void*
void* ptr = malloc(n*sizeof(int)) // Allocate array of n ints
free(ptr);                        // Free any memory from malloc

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLACEMENT NEW
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <new>

// Won't allocate memory- only puts newed object into section of memory given
// Classes require destructor to be called explicitly before deletion
// Any allocated memory given to it must also be cleaned up

char* buffer = new char[sizeof(MyClass)];
MyClass* obj = new (buffer) MyClass;
obj->~MyClass();
delete [] buffer;

