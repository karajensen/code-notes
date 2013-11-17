////////////////////////////////////////////////////////////////////////////////////////////////////
//PROGRAMMING NOTES
////////////////////////////////////////////////////////////////////////////////////////////////////
/*

C++ VARIABLE               C# VARIABLE      BYTES     RANGE
bool                       bool             1         true/false
char                       ---              1         Signage Dependent on compiler
signed char                byte             1         0 to 255
unsigned char              sbyte            1         –128 to 127    
char16_t                   char             2         0 to 65535 (UTF-16 character representation)
short                      short            2         –32768 to 32767
unsigned short (U)         ushort           2         0 to 65535
int                        ---              2/4       Depends on machine, minimum size of short
unsigned int (U)           ---              2/4       Depends on machine, minimum size of short
long (L)                   int              4         -2,147,483,648 to 2,147,483,647                   
unsigned long (UL)         uint (U)         4         0 to 4,294,967,295  
long long (LL)             long (L)         8         -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
unsigned long long (ULL)   ulong (UL)       8         0 to 18,446,744,073,709,551,615
float (f)                  float (f)        4         3.4E +/- 38 (7 digits)   
double                     double           8         1.7E +/- 308 (15 digits)             
long double (L)            ---              8         Depends on machine, minimum size of double
---                        decimal (m)      12        28 digits
pointer/reference          object           4/8       Depends on whether 32/64 bit platform


BYTE: 8 bits (256 values; 2⁸)
WORD: 2 bytes
DOUBLE WORD: 2 words
QUAD WORD: 2 double words

HEXADECIMAL: 
1-F (1-15 where A = 10)
Two hex values = one byte
0xff = 0xffffffff = 255 = 11111111

VALUE TYPES: have automatic storage, stored on stack/register
REFERENCE TYPES: have dynamic storage, stored on heap
STATIC TYPES: have static storage, stored in fixed seperate memory/data segment

LOCAL SCOPE: Variable defined in a block
GLOBAL SCOPE: Variable defined outside a block, can be in a namespace
CLASS SCOPE: Member Variables in a class
FUNCTION PROTOTYPE SCOPE: Variables in function prototype

PUBLIC/EXTERNAL LINKAGE: Can be accessed accross files
PRIVATE/INTERNAL LINKAGE: Can only be accessed by file declared in

UNARY OPERATOR: Act on single values: - + ++ --
BINARY OPERATOR: Act on two values: - + * % / = += -= *= /=
TERNARY OPERATOR: Act on three values: ?: 

DEEP COPY: Underlying memory the reference/pointer points to is copied
SHALLOW COPY: Reference/pointer is copied and points to original data

DECLARING VARIABLES
• Determines how much memory is needed for a data object
• Determines how the bits in memory are interpreted 
 (bool and char use same amount of memory but shown differently)
• Determines what methods can be performed using the data object.

NAMING CONVENTION
• Characters usable: alphabet, numbers, underscore character
• The first character in a name cannot be a numeric digit.
• You can’t use a keyword for a name.
• Names beginning with __ or _ are reserved for use by the compiler
• Camel notation: myVariable
• Pascal notation: MyVariable

TYPE-SAFETY
• How much compiler will check that you don't mix incompatible variables
• Eg. C++ prevents floating point being added to string

TYPE-CAST/DOWNCASTING/EXPLICIT CONVERSION
• Data may be lost, done by user with cast operator
• base -> derived
• double -> float -> long -> int -> short
• unsigned -> signed

AUTOMATIC/IMPLICIT CONVERSION
• No data is lost, auto done by compiler
• derived -> base
• short -> int -> long -> float -> double
• signed -> unsigned

ORDER OF EXPRESSION EVALUATION
• Known as short-circuiting logical expressions
• Order is left to right where right is only done if left is true: if(left && right)

ESCAPED CHARACTERS
Newline = \n 
Horizontal tab = \t
Backspace = \b
Backslash  = \\
Single quote = \’
Double quote = \”
Return = \r
Null character = \0

////////////////////////////////////////////////////////////////////////////////////////////////////
//PROGRAM EXECUTION
////////////////////////////////////////////////////////////////////////////////////////////////////

1) PREPROCESSOR
• Accepts Source code, Outputs Source code
• Removes comments and # directives

2) COMPILER
• Accepts Source code, Outputs machine/assembly/object code

3) LINKER
• Accepts machine code, Outputs machine code in form of executable
• Links together your code with any external libraries

OPCODE: single executable machine language instruction
OPERANDS: arguments given after the opcode
MNEMONICS: set to equal an opcode or a series of opcodes/operands

COMPILE TIME: Action performed during compilation; uses no execution time.
RUN TIME: Action performed during program execution

////////////////////////////////////////////////////////////////////////////////////////////////////
//MEMORY REPRESENTATION
////////////////////////////////////////////////////////////////////////////////////////////////////

FLOATING POINT PRECISION: Binary cannot express some floating point values (0.1) exactly
ENDIAN-NESS: Ordering of bytes in memory of a data object

LITTLE ENDIAN (BACKWARDS)
• multi-byte values are written least significant byte first
• used by x86 architecture
• 0x12345678 is written in memory as 78 56 34 12    

BIG ENDIAN (FORWARDS)
• multi-byte values are written most significant byte first
• 0x12345678 is written in memory as 12 34 56 78

TWOS COMPLEMENT
• Standard way of representing negative integers in binary
• + sign is changed by inverting all of the bits and adding one

    Start:    0001  (decimal 1)
    Invert:   1110
    Add One:  1111  (decimal -1)

===============================================================================
RAM MEMORY LOCATIONS
===============================================================================

RANDOM ACCESS MEMORY (RAM)
• Physical Main memory where everything is held for execution
• Virtual memory is memory on hard drive extending RAM

SEGMENTS
• Sections of memory used for various purposes
• Segmentation Fault: Attempt to access RAM location that the CPU cannot physically access

INITIALIZED DATA SEGMENT
• Contains global/static/constant data

UNINITIALIZED DATA SEGMENT (BSS)
• Contains zero-initialised data

THE STACK
• LIFO Segment storing temporary/local/value-type variables and keeps track of program execution
• Each function called has a 'Stack Frame' containing local variables until the function returns
• Contains memory address of next instruction to execute after the called function returns
• Self manages memory; variables allocated and freed automatically, no fragmentation
• Has limit on size, Fast access

THE HEAP
• Segment storing dynamically allocated reference-type variables
• User allocates memory; memory may become fragmented
• Larger size than stack though slower as it uses pointers to access
• Doesn't actually use a heap structure, can be based off queue

===============================================================================
CPU MEMORY LOCATIONS
===============================================================================

REGISTERS
• Physical Temporary storage for processing data/calculations taken from cache
• ESP: STACK POINTER REGISTER: Always points to the top of the stack
• EBP: STACK BASE POINTER REGISTER: Pointer to data on the stack. 
• EAX: ACCUMULATOR REGISTER: Primarly used for mathematical operations
• EBX: BASE REGISTER: Pointer to data in a segment register
• ECX: COUNTER REGISTER: Counter for string and loop operations
• EDX: DATA REGISTER: Used in arithmetic operations and I/O operations
• ESI: SOURCE REGISTER: Used as a pointer to a source in stream operations
• EDI: DESTINATION REGISTER: Used as a pointer to a destination in stream operations
• FLAGS REGISTER: Reports on the status of the program being executed
• IP (INTRUCTION POINTER) REGISTER: Contains a pointer to the next intruction to be executed

CACHES
• Physical Temporary storage for frequently accessed data for rapid access, sends to registers
• No processing on data- must be moved to registers if this is needed
• Cache Miss: Failed attempt to read/write to the cache resulting in RAM access

////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////

FUNCTION DECLARATION/PROTOTYPE: Function header
FUNCTION DEFINITION: Function including body

AGGREGATE METHODS: Applies a function to each successive element
PREDICATE: Function that returns bool
PURE FUNCTION: Has no static variables, doesn't affect member variables
PURE VIRTUAL FUNCTION: abstract function, no implementation
VIRTUAL FUNCTION: function that can be overriden by a derived class
GENERATOR: called with no arguments.
UNARY FUNCTION: called with one argument.
BINARY FUNCTION: called with two arguments.
FRIEND FUNCTION: can see a class's private parts

FUNCTION CALLING
1) program places address of calling function on stack
2) any variables used locally are created as auto vars and placed on stack
3) if function calls another its information is placed on top of stack

RETURNING VALUES
1) Returns a value by copying the return value to a specified register/location
2) The calling function examines that location. Both the returning and 
   calling function have to agree on the type of data at that location. 

ARGUMENTS/PARAMETERS
Actual Argument/Parameter = The value passed to the function 
Formal Argument/Parameter = A variable that’s used to receive passed values
Argument = used to denote Actual Argument/Parameter
Parameter = used to denote Formal Argument/Parameter 

CDECL CALLING CONVENTION
• Arguments passed via stack. 
• Calling function cleans the stack
• allows variadic functions

STDCALL CALLING CONVENTION
• Arguments passed via stack. 
• Called function cleans the stack
• doesn't allow variadic functions

THISCALL CALLING CONVENTION
• Arguments passed via stack. 
• 'this' pointer passed in ecx register

FASTCALL CALLING CONVENTION
• First 2-3 small arguments are passed in registers
• Additional/large arguments passed via stack. 
• Calling function cleans the stack

////////////////////////////////////////////////////////////////////////////////////////////////////
//OBJECT ORIENTED PROGRAMMING
////////////////////////////////////////////////////////////////////////////////////////////////////

6 MOST IMPORTANT OOP FEATURES
    P • Polymorphism
    A • Abstraction
    I • Inheritance
    R • Reusability of code
    E • Encapsulation 
    D • Data hiding

POLYMORPHISM: 
When a function can operate with values of at least two distinct types and executes type-appropriate code

ABSTRACTION: 
Sectioning off variables/functions into private (IMPLEMENTATION) and public (INTERFACE) of a class
 
INHERITANCE:
Using previously written classes as a base for new classes.

RE-USABILITY:
Using inheritance/functions/templates to prevent code duplication.

DATA HIDING: 
The insulation of data from direct access by a program

ENCAPSULATION: 
The wrapping of data and functions with common features into a single class/structure

////////////////////////////////////////////////////////////////////////////////////////////////////
//CLASSES
////////////////////////////////////////////////////////////////////////////////////////////////////

AGGREGATE:
• Array/class/struct/union with no user-declared constructors, private and 
  protected non-static data members, base classes and virtual functions.
• Array is an aggregate even it is an array of non-aggregate class type.
• Doesn't matter what static members it has
• Can be initialized with {}

PLAIN-OLD-DATA (POD):
• An aggregate class with no user-declared assignment op/destructor,
  Non-static members have to be POD types, non-static arrays have to hold 
  POD types and references have to refer to POD types;
• Doesn't matter what static members it has

////////////////////////////////////////////////////////////////////////////////////////////////////
//INHERITANCE
////////////////////////////////////////////////////////////////////////////////////////////////////

COVARIANCE: Allows assinging MyClass or derived from it to MyClass object [polymorphism basis]
CONTRAVARIANCE: Allows assigning MyClass or what MyClass derived from to MyClass object 
INVARIANCE: Allows neither

STATIC BINDING: Uses pointer/ref type to determine function to call at compilation
DYNAMIC BINDING: Uses held object type to determine function to call at runtime

IS-A RELATIONSHIP
Class inherits an interface + implementation for non pure virtual functions
Eg. Public inheritance

HAS-A RELATIONSHIP
Class acquires implementation without the interface 
Interface can still be used within class methods, but not outside class
Eg. Containment/Composition/Layering, Private/Protected inheritance

////////////////////////////////////////////////////////////////////////////////////////////////////
//POLYMORPHISM
////////////////////////////////////////////////////////////////////////////////////////////////////

To exhibit polymorphism, f() must be able to operate with values of at least 
two distinct types finding and executing type-appropriate code.

1) PREPROCESSING (AD-HOC/PARAMETRIC)
   #define f(int x) ((x) += 2)
   #define f(double x) ((x) += 2)
   #define f(X) ((X) += 2)

2) OVERLOADING (AD-HOC)
   void f(int& x)    { x += 2; }
   void f(double& x) { x += 2; }

3) TEMPLATES (PARAMETRIC)
   template <typename T>
   void f(T& x) { x += 2; }

4) VIRTUAL METHODS (AD-HOC)
   BaseClass* pBase = &derivedObject;
   pBase->MyVirtualFunction();

AD-HOC POLYMORPHISM: object types are explicitly defined for overloading
PARAMETRIC POLYMORPHISM: object types aren't defined, any object can be used

///////////////////////////////////////////////////////////////////////////////////////////////////
//EXCEPTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////

1) THROW BY VALUE
• When exception is thrown, copy of thrown variable is made as it needs it after function out of scope
• Don't throw pointers, if absolutely needed, use a smart pointer

2) STACK UNWINDS
• Stack releases memory until reaching the corresponding try-catch block
• Any destructors are called on way- if exception is called in destructor, 
  it must resolve it otherwise two exceptions are occuring
• Pointers are destroyed without calling delete. Solved through smart pointers

3) CATCH BY REFERENCE
• Catch reference as used to allow inheritance with exception types 

EXCEPTION PATH
If Exception type wasn't explicitly thrown: unexpected()->terminate()->abort()
If Exception type was known but not caught: terminate()->abort()

///////////////////////////////////////////////////////////////////////////////////////////////////
//MULTITHREADING
///////////////////////////////////////////////////////////////////////////////////////////////////

• Threads within a program share same data space/information with main thread
• Thread has a beginning, execution sequence and conclusion
• Thread has instruction pointer- keeps track of where its currently running
• Threads can be interrupted and put to sleep while other threads are running

///////////////////////////////////////////////////////////////////////////////////////////////////
//DESIGN PATTERNS
///////////////////////////////////////////////////////////////////////////////////////////////////

==============================================================================================
CREATION PATTERNS
==============================================================================================
FACTORY: Creates groups of objects
BUILDER: Connects together components of the one object
PROTOTYPE: Copies from a set of base objects to create new objects
SINGLETON: Ensure a class only has one instance and allow anyone seeing that class to have access to it
                                                                             
==============================================================================================
STRUCTURAL PATTERNS                                                          
==============================================================================================

PIMPL: Allows changing the implementation without touching the interface
DECORATOR: Allows mixing/matching of classes without need for writing a subclass for each and every match
FLYWEIGHT: Use of an object to store common information for a class of objects
COMPOSITE: A class built ontop of an object class that manages groups of the objects
PROXY: Uses a pointer/reference/proxy object to send changes to the real object
FACADE: Wrapper class on top of a complicated class
ADAPTER: Wrapper class on top of unrelated classes
BRIDGE: Creates a bridge between a class and different ways of using that class
           
==============================================================================================
BEHAVIOURAL PATTERNS
==============================================================================================

MEMENTO: Allows object to restore to a previous state (undo/redo)
ITERATOR: Allows movement over range of elements in a container
INTERPRETER: Decodes each symbol in a string/sentence
TEMPLATE: Skeleton algorithm; changing a method won't change the overall algorithm
COMMAND: Functor/lambda holding a method, the object to call the method and any arguments
CHAIN OF RESPONSIBILITY: Passes a command through a series of objects until handled
STATE: Alters an object's behaviour when its state changes
STRATEGY: Allows choosing an algorithm at runtime
VISITOR: Seperates objects from their methods; calls custom methods in derived objects from base*
OBSERVER: Sends an event message when an object changes state to any observers
MEDIATOR: Talks between two classes without either having to know about the other

*///////////////////////////////////////////////////////////////////////////////////////////////////