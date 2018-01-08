///////////////////////////////////////////////////////////////////////////////////////////////////////
//ERROR HANDLING
///////////////////////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************************
NOEXCEPT FUNCTIONS
• If objects they work on throw, undefined behaviour
• All destructors automatically have noexcept keyword
• std::swap has noexcept keyword

EXCEPTIONS IN CONSTRUCTORS
• On exception construction has failed and the object never existed
• On exception the destructor does not need to be called
• On exception the try-catch block cannot suppress; implicitly rethrows if trying to suppress
• On exception any members requiring explicit cleanup in destructor will be leaked
• Cannot access any class members in catch block as out of scope

EXCEPTIONS IN DESTRUCTORS
• Destructors should never throw: if unwinding the stack from an 
  exception and a destructor throws the program is terminated

STANDARD LIBRARY EXCEPTIONS
• Exception neutral
• Mostly has strong exception guarantee with a few basic guarantees
• Multi-range insert(begin,begin,end) has basic guarantee
• Vector and Deque only: inserts or erases for multi or single objects are basic guarantee 
  if object constructor or assignment operator throws, otherwise strong guarantee  
*******************************************************************************************/

assert(myPtr != nullptr);                    // break if myPtr is null
assert(condition && "message");              // break with message
static_assert(myConstInt > 0, "MyMessage");  // must use constant values, asserts at compile time
throw std::exception("Message goes here");

try 
{ 
    myFunction();
} 
catch(const std::exception& e)
{
    // Always catch by const reference
    // Reference is used instead of pointer to reduce the need to manage any memory at the catch position
    // Allocating memory for an exception through a pointer may not work if the exception is out of memory.

    cout << e.what() << endl;

    throw e; // throws a copy of e, splices off any derived type
    throw; //original exception is thrown again
}
catch (...) //catches anything
{
}

//EXCEPTION SPECIFICATIONS
//If exception type not on list is thrown, calls unexpected()
void MyFn(); //can throw anything
void MyFn() throw(const char*, std::exception&); //can only throw string or std::exception
void MyFn() throw(); //Doesn't throw excpetions, not optimized: keeps unwindable stack state always
void MyFn() noexcept; //Doesn't throw exceptions, optimizes: doesn't keep unwindable stack state if exception propagates

//UNEXPECTED EXPECTION
//If type wasn't explicitly thrown or on expected list: unexpected()->terminate()->abort()
unexpected() //calls terminate()
set_unexpected([](){}); //takes in void MyFunction()

//UNCAUGHT EXCEPTION
//If type was known but not caught: terminate()->abort()
terminate() //calls abort()
set_terminate([](){}); //takes in void MyFunction()
 
//EXCEPTIONS IN CONSTRUCTORS
MyClass::MyClass()
try : A()
    , B()
{
}
catch (...) // can't access class members in catch block
{
}

//CREATING CUSTOM EXCEPTION
class MyClass: public std::exception
{
public:
    virtual const char* what() const override { return "bad arguments"; } 
};

try 
{
    throw MyClass();
}
catch(const std::exception& e)
{
    cout << e.what() << endl;
}
