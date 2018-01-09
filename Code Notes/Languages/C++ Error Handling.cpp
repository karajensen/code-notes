///////////////////////////////////////////////////////////////////////////////////////////////////////
//ERROR HANDLING
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************************
EXCEPTION REASONS:
• Program accesses an invalid memory address (such as NULL pointer)
• Stack overflows due to infinite recursion
• Large block of data is written to a small buffer
• A pure virtual method of a C++ class is called
• Memory buffer can't be allocated (out of memory)
• Invalid parameter is passed to a C++ system function
• C run-time libraries detect an error and request program termination
*****************************************************************************************************/

assert(myPtr != nullptr);                    // break if myPtr is null
assert(condition && "message");              // break with message
static_assert(myConstInt > 0, "MyMessage");  // must use constant values, asserts at compile time

///////////////////////////////////////////////////////////////////////////////////////////////////////
//C++ EXCEPTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************************
C++ EXCEPTIONS:
• Used for STL and user exceptions
• Has different levels of exception guarantees
• When an exception occurs:
    - Copy of thrown variable is made as it needs it after function out of scope
    - Stack releases memory until reaching the corresponding try-catch block
    - Any destructors are called on way as objects go out of scope
    - Local pointers are destroyed without calling delete
   
CATCH BY CONST REFERENCE
• Const is used to prevent the exception from being modified and giving incorrect crash information
• Reference is used so the exception can be resolved polymorphically and so slicing does not happen
• Reference is used instead of pointer to reduce the need to manage any memory at the catch position
• Allocating memory for an exception through a pointer may not work if the exception is out of memory

EXCEPTION SAFETY
• Use RAII to auto cleanup resources if exception is thrown
• Only change state once any possible errors have been resolved
• Destructor/deallocation/swap functions should never throw as impossible to safely cleanup

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
*****************************************************************************************************/

try 
{ 
    throw std::exception("Message goes here");   // throw c++ exception
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
set_unexpected([](){ /** do something */ });

//UNCAUGHT EXCEPTION
//If type was known but not caught: terminate()->abort()
terminate() //calls abort()
set_terminate([](){ /** do something */ });
 
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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//STRUCTURED EXCEPTIONS (SEH)
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************************
SEH EXCEPTIONS:
• Used for CPU exceptions such as access violation, illegal instruction, divide by zero
• No exception guarantee; does not unwind the stack or call destructors
• Each thread has its own SEH exception handler callback function
• Can also catch C++ exceptions with error code 0xe06d7363
• Using __try will add a new EXCEPTION_REGISTRATION to the list
• When an exception occurs:
    - linked list of EXCEPTION_REGISTRATION structures is walked util one handles the exception
    - default EXCEPTION_REGISTRATION is always called last
    - once handled, the list is walked again but with EH_UNWINDING (value 2) set in the exception flags
    - EH_UNWINDING gives the oppotunity to do any cleanup
*****************************************************************************************************/
__try
{
}
__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
{  
}

int ExceptionFilter(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
    static DWORD EH_UNWINDING = 0x00000002;
    if (ep->ExceptionRecord->ExceptionFlags & EH_UNWINDING) 
    {
        // Do any cleanup
    }
    else
    {
        auto info = InfoFromSE::information(code, ep);
    }  
    return EXCEPTION_CONTINUE_SEARCH; // Continue to the next handler
}

class InfoFromSE
{
public:
   typedef unsigned int exception_code_t;

   static const char* opDescription(const ULONG opcode)
   {
      switch(opcode) 
      {
      case 0: return "read";
      case 1: return "write";
      case 8: return "user-mode data execution prevention (DEP) violation";
      default: return "unknown";
      }
   }

   static const char* seDescription(const exception_code_t& code)
   {
      switch(code)
      {
         case EXCEPTION_ACCESS_VIOLATION:         return "EXCEPTION_ACCESS_VIOLATION"         ;
         case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED"    ;
         case EXCEPTION_BREAKPOINT:               return "EXCEPTION_BREAKPOINT"               ;
         case EXCEPTION_DATATYPE_MISALIGNMENT:    return "EXCEPTION_DATATYPE_MISALIGNMENT"    ;
         case EXCEPTION_FLT_DENORMAL_OPERAND:     return "EXCEPTION_FLT_DENORMAL_OPERAND"     ;
         case EXCEPTION_FLT_DIVIDE_BY_ZERO:       return "EXCEPTION_FLT_DIVIDE_BY_ZERO"       ;
         case EXCEPTION_FLT_INEXACT_RESULT:       return "EXCEPTION_FLT_INEXACT_RESULT"       ;
         case EXCEPTION_FLT_INVALID_OPERATION:    return "EXCEPTION_FLT_INVALID_OPERATION"    ;
         case EXCEPTION_FLT_OVERFLOW:             return "EXCEPTION_FLT_OVERFLOW"             ;
         case EXCEPTION_FLT_STACK_CHECK:          return "EXCEPTION_FLT_STACK_CHECK"          ;
         case EXCEPTION_FLT_UNDERFLOW:            return "EXCEPTION_FLT_UNDERFLOW"            ;
         case EXCEPTION_ILLEGAL_INSTRUCTION:      return "EXCEPTION_ILLEGAL_INSTRUCTION"      ;
         case EXCEPTION_IN_PAGE_ERROR:            return "EXCEPTION_IN_PAGE_ERROR"            ;
         case EXCEPTION_INT_DIVIDE_BY_ZERO:       return "EXCEPTION_INT_DIVIDE_BY_ZERO"       ;
         case EXCEPTION_INT_OVERFLOW:             return "EXCEPTION_INT_OVERFLOW"             ;
         case EXCEPTION_INVALID_DISPOSITION:      return "EXCEPTION_INVALID_DISPOSITION"      ;
         case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "EXCEPTION_NONCONTINUABLE_EXCEPTION" ;
         case EXCEPTION_PRIV_INSTRUCTION:         return "EXCEPTION_PRIV_INSTRUCTION"         ;
         case EXCEPTION_SINGLE_STEP:              return "EXCEPTION_SINGLE_STEP"              ;
         case EXCEPTION_STACK_OVERFLOW:           return "EXCEPTION_STACK_OVERFLOW"           ;
         default: return "UNKNOWN EXCEPTION" ;
      }
   }

   static std::string information(exception_code_t code, struct _EXCEPTION_POINTERS* ep)
   {
      HMODULE hm;
      ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, static_cast<LPCTSTR>(ep->ExceptionRecord->ExceptionAddress), &hm);
      MODULEINFO mi;
      ::GetModuleInformation(::GetCurrentProcess(), hm, &mi, sizeof(mi));
      char fn[MAX_PATH];
      ::GetModuleFileNameExA(::GetCurrentProcess(), hm, fn, MAX_PATH);

      std::ostringstream oss;
      oss << "SE " << seDescription(code) << " at address 0x" << std::hex << ep->ExceptionRecord->ExceptionAddress << std::dec 
         << " inside " << fn << " loaded at base address 0x" << std::hex << mi.lpBaseOfDll << "\n"; 

      if (code == EXCEPTION_ACCESS_VIOLATION || code == EXCEPTION_IN_PAGE_ERROR))
      {
         oss << "Invalid operation: " << opDescription(ep->ExceptionRecord->ExceptionInformation[0]) 
             << " at address 0x" << std::hex << ep->ExceptionRecord->ExceptionInformation[1] << std::dec << "\n";
      }

      return oss.str();
   }
};
