//////////////////////////////////////////////////////////////////////////////
//POINTERS
//////////////////////////////////////////////////////////////////////////////

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

*(myArray+3) /*or*/ myArray[3] /*or*/ 3[myArray] //to access elements
delete [] myArray; //free array

//////////////////////////////////////////////////////////////////////////////
//LAMBDAS
//////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////
//BINDING FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////
//FUNCTORS
//////////////////////////////////////////////////////////////////////////////

//Function with operator()
struct MyFunctor
{
    bool operator()(int x) { return x > 0; }
}

std::plus<double> add; //create a plus<double> object
std::plus<double>() //using as function
double y = add(2.2, 3.4); //using plus<double>::operator()()

template <class T> struct plus { T operator() (const T& x, const T& y) const {return x + y;} };
template <class T> struct minus { T operator() (const T& x, const T& y) const {return x - y;} };
template <class T> struct multiplies { T operator() (const T& x, const T& y) const {return x * y;} };
template <class T> struct negate { T operator() (const T& x) const {return -x;} };
template <class T> struct not_equal_to { bool operator() (const T& x, const T& y) const {return x != y;} };
template <class T> struct less_equal { bool operator() (const T& x, const T& y) const {return x<=y;} };
template <class T> struct less { bool operator() (const T& x, const T& y) const {return x<y;} };
template <class T> struct greater { bool operator() (const T& x, const T& y) const {return x > y;} };
template <class T> struct greater_equal { bool operator() (const T& x, const T& y) const {return x>=y;} };

//////////////////////////////////////////////////////////////////////////////
//FUNCTION POINTERS 
//////////////////////////////////////////////////////////////////////////////

//POINTER-TO-FUNCTION
typedef bool (*pFunction)(int x);
pFunction myFunction = &MyFunction; 
myFunction(5);

//POINTER-TO-MEMBER FUNCTIONS
class Test
{
public:
    
    typedef void(Test::*Action)();
    typedef void(Test::*ActionConst)() const;

    void DrawConst(){} const;
    void Draw(){}

    Action m_action;
    ActionConst m_actionconst;
};

m_action = &Test::Draw;
m_actionconst = &Test::DrawConst;

//////////////////////////////////////////////////////////////////////////////
//SMART POINTERS
//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////
//AUTO POINTER [DEPRECATED]
//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////
//DEBUGGING MEMORY
//////////////////////////////////////////////////////////////////////////////

//OVERLOADING NEW
void *operator new(size_t size)
{
    cout << "new used"; //give message
    return malloc(size);
}
void *operator new(size_t size, unsigned int lineNumber)
{
    cout << "new used at " << lineNumber; //give message
    return malloc(size);
}
void operator delete(void* p)
{
    cout << "delete used";  //give message
    free(p);
}

//OVERLOADING NEW ARRAY
void *operator new[](size_t size)
{
    cout << "new array used";
    return malloc(size);
}
void operator delete[](void* p)
{
    cout << "delete array used";
    free(p);
}

//////////////////////////////////////////////////////////////////////////////
//C-STYLE MEMORY ALLOCATION
//////////////////////////////////////////////////////////////////////////////
#include <malloc.h>

//Allocating memory
int* pPointer = (int*)malloc(allocationSizeInBytes);

//Freeing memory
free(pPointer);

//Resizing memory
int* pPointer = (int*)realloc(pPointer,numberOfExtraElements);

//Moving memory
int* pDestination = (int*)memmove(pDestination,pSource,SizeInBytes);

//Reallocating memory
int* pPointer = (int*)realloc(allocationSizeInBytes);

//////////////////////////////////////////////////////////////////////////////
//PLACEMENT NEW
//////////////////////////////////////////////////////////////////////////////
#include <new>

//PLACEMENT NEW
//places memory on stack rather than heap
char buffer[512];
int * p_buffer = new (buffer) int[SIZE]; 
                                                                 
//PLACEMENT NEW [CLASSES]
char* buffer = new char[512]; // get a block of memory
Testclass* p_class = new (buffer) Testclass("hello") //place object in buffer
p_class->~Testclass() //delete placement new 

//////////////////////////////////////////////////////////////////////////////
//SMART POINTERS CLASS EXAMPLE
//////////////////////////////////////////////////////////////////////////////

template <class T> class SmartPointer 
{
public: 

    //CONSTRUCTOR
    SmartPointer(T * ptr) 
    {
        ref = ptr;
        ref_count = (unsigned*)malloc(sizeof(unsigned));
        *ref_count = 1;
    }
    //COPY CONSTRUCTOR
    SmartPointer(SmartPointer<T> & sptr) 
    {
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++*ref_count;
    }
    //ASSIGNMENT OPERATOR
    SmartPointer<T> & operator=(SmartPointer<T> & sptr) 
    {
        if (this != &sptr) 
        {
            ref = sptr.ref;
            ref_count = sptr.ref_count;
            ++*ref_count;
        }
        return *this;
    }
    //DESTRUCTOR
    virtual ~SmartPointer() 
    {
        --*ref_count;
        if (*ref_count == 0) 
        {
            delete ref;
            free(ref_count);
            ref = nullptr;
            ref_count = nullptr;
        }
    }
    //GET VALUE
    T getValue() 
    { 
        return *ref; 
    }

protected:
    T * ref;
    unsigned * ref_count;
};