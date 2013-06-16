//////////////////////////////////////////////////////////////////////////////
//MEMORY MANAGEMENT
//////////////////////////////////////////////////////////////////////////////

//ARRAY NAME: 
// • Array name is address of first element

//CSTRING/POINTER-TO-CHAR ARRAY/STRING LITERAL:
// • name gives string
// • &pointer gives address of pointer
// • &chararray gives address of first character
// • (void*)pointer gives address of string

//===========================================================================
//POINTERS
//===========================================================================

// p_updates = address
// *p_updates = value of updates
// & gives the address of the variable in hex
int updates = 6; 
int * p_updates = &updates;
                           
//converts the number into a memory location
p_updates =  (int*)0xB8000000 

//DYNAMIC POINTERS
int* p_new = new int //finds empty memory location for an int and allocates
*p_new = 5 //stores value 5
delete p_new //frees the block of memory

&(*p_new) //gives address of int
&p_new //gives address of pointer

//===========================================================================
//POINTER TO ARRAYS
//===========================================================================
int size;
int * p_darray = new int [size]
delete [] psome; //delete dynamic array
*(p_darray + 1)  /*or*/  p_darray[1] //to access array

double dblarray[3];
double * p_dbl = &dblarray[0];

//size of arrays
int * a = arr+size;
int * b = arr;
int size = a - b;

//===========================================================================
//POINTER TO ARRAY OF POINTERS
//===========================================================================
char ** p_charpointer = new char * [size];

//must point each pointer in array to char block of memory before use
for (int i = 0; i < size; i++)
    p_charpointer[i] = new char [];

//must delete array members
for (int i = 0; i < size; i++)
    delete [] p_charpointer[i];
delete [] p_charpointer;
    
//===========================================================================
//POINTER TO STRUCTURES
//===========================================================================
struct teststruct //structure
{
    int good;
    int bad;
};
teststruct me = {3, 453}; //create a new instance of structure
teststruct * p_me = &me; //assign its address to p_me
teststruct * p_me = new teststruct;

//to access members:
&p_me->good //gives address of member
p_me->good //gives value of member
(*p_me).good  /*or*/ p_me[0].good //for struct arrays

//////////////////////////////////////////////////////////////////////////////
//SMART POINTERS
//////////////////////////////////////////////////////////////////////////////

if(ptr) //true if valid, false if null
*ptr    //dereference pointer

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
//only one of a kind
std::unique_ptr<MyClass> up(new MyClass);

//USING WITH POLYMORPHISM
std::shared_ptr<Base> ptr(new Derived);

//CASTING BASE TO DERIVED
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