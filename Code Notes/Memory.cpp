/////////////////////////////////////////////////////////////////////////////////////////////
//POINTERS
/////////////////////////////////////////////////////////////////////////////////////////////

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

//Avoid as pointer arithmatic on base class arrays of derived objects
//pointer arithmatic will use sizeof(Base) not sizeof(Derived)
Base* myArray = new Derived[2];
myArray[1] = *(myArray+1)
delete [] myArray //delete [] also uses pointer arithmatic

//FUNCTION ADDRESSES
&MyClass::MyMethod //address of member function
(void(MyClass::*)(double))&MyClass::MyMethod //address of overloaded function

/////////////////////////////////////////////////////////////////////////////////////////////
//LAMBDAS
/////////////////////////////////////////////////////////////////////////////////////////////
//• Can't be templated
//• Can't use auto with binding, must use std::function type
//• If inside a class, may become friends

//LAMBDA SYNTAX
auto myLamda = [](int x) { return 3*2; } //if only one line, can omit trailing return
auto myLamda = [](int x)->double { return 3*2; }
auto myLamda = &MyFunction; //storing pointer to function
auto myLamda = MyFunctor; //storing functor object
std::function<double(int)> myLamda = [](int x){ return x+2.0; }

//CAPTURING OUTSIDE VARIABLES
//Can also capture member vars, functions etc.
auto myLambda = [&myVar](int x){ myVar += 10; } //by reference
auto myLambda = [myVar](int x){ myVar += 10; }  //by value
auto myLambda = [&](int x){ myVar += 10; }      //use all vars in scope by ref
auto myLambda = [=](int x){ myVar += 10; }      //use all vars in scope by val
auto myLambda = [&](int x){ MyClassFunction(x); m_myMember += 1; }

/////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTION OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////

//FUNCTOR
//Function with operator()
struct MyFunctor
{
    bool operator()(int x) { return x > 0; }
}

//POINTER-TO-FUNCTION
typedef bool(*pFunction)(int x, double y);
pFunction myFunction = &MyFunction; 
myFunction(5, 1.0);

//POINTER-TO-MEMBER FUNCTION
class MyClass
{
public:
    
    typedef void(MyClass::*MyMethodFn)();
    void MyMethod(){}
    MyMethodFn m_myMethodFn;
};

m_myMethodFn = &MyClass::MyMethodFn;
(myObject.*m_myMethodFn)();
(myObject->*m_myMethodFn)();

/////////////////////////////////////////////////////////////////////////////////////////////
//BINDING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////

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

if(SmartPtr) //true if valid, false if null
*SmartPtr    //dereference pointer

//SHARED POINTER
//multiple objects have references
std::shared_ptr<MyClass> sp(new MyClass);
std::shared_ptr<MyClass> sp(myRawPointer);

sp.get()       //gets a raw pointer or null
sp.use_count() //get the current count
sp.swap(sp2)   //swap sp1 and sp2
sp.unique()    //returns true if ref count = 1, false otherwise
sp.reset()     //decrements ref count to 0, deletes object

//WEAK POINTER
//observing a shared pointer
std::weak_ptr<MyClass> sp1(new MyClass);

wp.use_count()  //get the current count
wp.lock()       //returns a shared_ptr of same type, use instead of .get()
wp.expired()    //returns true if object has been deleted, false if okay

//UNIQUE POINTER
//requires contructor/destructor even if empty implementation
class MyClass
{
public:
    class ForwardDec;
    std::unique_ptr<ForwardDec> test;
    MyClass();
    ~MyClass();
};
#include "ForwardDec.h"
MyClass::MyClass(){}
MyClass::~MyClass(){}

//USING WITH POLYMORPHISM
std::shared_ptr<Base> ptr(new Derived);
std::shared_ptr<Derived> dptr = std::dynamic_pointer_cast<Base>(ptr) //returns null if unsuccessful

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

//CREATING CUSTOM DELETERS
//Without a deleter, plain 'delete' is implicitely called
auto release = [](MyClass* obj)
{
    if(obj)
    {
        obj->release();
    }
};
std::shared_ptr<MyClass> ptr(&myObject, release);
std::unique_ptr<MyClass, decltype(release)> ptr(&myObject, release);

//CALLING PRIVATE DESTRUCTOR
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

//PLACEMENT NEW
//places memory on stack rather than heap
char buffer[512];
int * p_buffer = new (buffer) int[SIZE]; 
                                                                 
//PLACEMENT NEW [CLASSES]
char* buffer = new char[512]; // get a block of memory
Testclass* p_class = new (buffer) Testclass("hello") //place object in buffer
p_class->~Testclass() //delete placement new 
