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

VALUE TYPES: have automatic storage, stored on stack/register
REFERENCE TYPES: have dynamic storage, stored on heap, accessed through references/pointers
STATIC TYPES: have static storage, stored in fixed seperate memory/data segment
OBJECTS: Instances of a class

LOCAL SCOPE: Variable defined in a block
GLOBAL SCOPE: Variable defined outside a block, can be in a namespace
CLASS SCOPE: Member Variables in a class
FUNCTION PROTOTYPE SCOPE: Variables in function prototype
PUBLIC/EXTERNAL LINKAGE: Can be accessed accross files
PRIVATE/INTERNAL LINKAGE: Can only be accessed by file declared in

UNARY OPERATOR: Act on single values
BINARY OPERATOR: Act on two values
TERNARY OPERATOR: Act on three values

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

AUTOMATIC/UPCASTING/IMPLICIT CONVERSION
• Bool is converted to int internally
• No data is lost, auto done by compiler
• derived -> base
• short -> int -> long -> float -> double
• signed -> unsigned

ORDER OF EXPRESSION EVALUATION
• Known as short-circuiting logical expressions
• Order is left to right where right is only done if left is true: if(left && right)
• Doesn't work with bitwise operators

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

COMPILE TIME: Action performed during compilation; uses no execution time.
RUN TIME: Action performed during program execution

OPCODE: single executable machine language instruction
OPERANDS: arguments given after the opcode
MNEMONICS: set to equal an opcode or a series of opcodes/operands
ENDIAN-NESS: Ordering of bytes in memory of a data object

LITTLE ENDIAN (BACKWARDS)
• multi-byte values are written least significant byte first
• used by x86 architecture
• 0x12345678 is written in memory as 78 56 34 12    

BIG ENDIAN (FORWARDS)
• multi-byte values are written most significant byte first
• 0x12345678 is written in memory as 12 34 56 78

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

STATIC BINDING: Uses pointer/ref type to determine function to call at compilation
DYNAMIC BINDING: Uses internal held object type to determine function to call at runtime

ARGUMENTS/PARAMETERS
Actual Argument/Parameter = The value passed to the function 
Formal Argument/Parameter = A variable that’s used to receive passed values
Argument = used to denote Actual Argument/Parameter
Parameter = used to denote Formal Argument/Parameter 

FUNCTION CALLING
• Copy required registers/argments to the stack
• Push the return address
• Any variables used locally are placed on the stack
• Jump to the function's address- This is hardcoded in the binary unless virtual. If virtual:
    - Get the vtable pointer
    - Find the correct address from the vtable and jump to that address
• Get the return value from a predefined location and restore registers

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
//CLASSES
////////////////////////////////////////////////////////////////////////////////////////////////////

DESTRUCTOR: Called when out of scope, delete used or explicitly
FINALISER: Called when object is garbage collected

AGGREGATE:
• Array/class/struct/union
• No user-declared constructors
• No private/protected non-static members
• No Base classes or virtual functions
• Array is an aggregate even it is an array of non-aggregate class type.
• Can be initialized with {}
• Doesn't matter what static members it has

PLAIN-OLD-DATA (POD):
• Aggregate class with extra requirements
• No user-declared assignment operator/destructor
• Non-static members must be POD types
• Non-static arrays/references/pointers must hold POD types

////////////////////////////////////////////////////////////////////////////////////////////////////
//OBJECT ORIENTED PROGRAMMING
////////////////////////////////////////////////////////////////////////////////////////////////////

POLYMORPHISM: Implementing the same methods in different ways
ABSTRACTION: Providing an interface for commonly used actions (eg. IMyClass, =0)
INHERITANCE: Using previously written classes as a base for new classes
RE-USABILITY: Preventing code duplication (eg. templates, shared functions/classes)
DATA HIDING: Type of encapsulation- hiding members from view (eg. Pimpl)
ENCAPSULATION: Hiding private implementation details behind a public interface/class (eg. private/public)

===============================================================================
INHERITANCE
===============================================================================
COVARIANCE: Allows assinging MyClass or derived from it to MyClass object [polymorphism basis]
CONTRAVARIANCE: Allows assigning MyClass or what MyClass derived from to MyClass object 
INVARIANCE: Allows neither

IS-A RELATIONSHIP
Class inherits an interface + implementation for non pure virtual functions
Eg. Public inheritance

HAS-A RELATIONSHIP
Class acquires implementation without the interface 
Interface can still be used within class methods, but not outside class
Eg. Containment/Composition/Layering, Private/Protected inheritance

===============================================================================
POLYMORPHISM
===============================================================================
AD-HOC POLYMORPHISM: object types are explicitly defined for overloading
PARAMETRIC POLYMORPHISM: object types aren't defined, any object can be used

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
//BIT MANIPULATION
///////////////////////////////////////////////////////////////////////////////////////////////////

BYTE: 8 bits
WORD: 2 bytes
DOUBLE WORD: 2 words
QUAD WORD: 2 double words
RADIX: Number base for a counting system (Decimal:10, Binary:2)

STRUCTURE OF A BYTE
Most values a byte can have: 0 -> (128+64+32+16+8+4+2+1) = 0 -> 255 = 256
 2⁷  2⁶  2⁵  2⁴  2³  2²  2¹  2°
128  64  32  16  8   4   2   1

HEXADECIMAL
1-F (1-15 where A = 10)
Two hex values = one byte
0xff = 0xffffffff = 255 = 11111111

FLOATING POINT PRECISION: Binary cannot express some floating point values (0.1) exactly
COUNTING IN BINARY: 0000  0001  0010  0011  0100  0101  0110  0111  1000
BINARY-TO-DECIMAL: 1101 = 1x2³ + 1x2² + 0x2¹ + 1x2° = 13
HEX-TO-DECIMAL: A3F = 10x16² + 3x16¹ + 15x16° = 2623
HEX-TO-BINARY: 0xC2 = binaryC binary2 = 1100 0010 = 11000010 (use image table)
BINARY-TO-HEX: 11000010 = 1100 0010 = 0xC2 (use image table)

TWOS COMPLEMENT
• Standard way of representing negative integers in binary
• −x is defined as ∼x + 1
  Start:    0001  (decimal 1)
  Invert:   1110
  Add One:  1111  (decimal -1)

BITWISE OPERATORS
• Can be used with boolean, intergers and char
• Bools are converted to ints holding true: 0x00000001, 0001, 1 and false: 0x00000000, 0000, 0

~     bitwise NOT    Returns all bits flipped
|     bitwise OR     Returns 1/true if either or both are 1/true
&     bitwise AND    Returns 1/true if both are 1/true
^     bitwise XOR    Returns 1/true if either but not both are 1/true
<<    left shift     Moves all bits to the left, drops the last 0 or 1 and adds 0 to the start
>>    right shift    Moves all bits to the right, drops the first 0 or 1 and adds 0 to the end

USING WITH BOOL
bool ifBothAreTrue   = myBool1 & myBool2
bool ifEitherAreTrue = myBool1 | myBool2
bool ifEitherAreTrue = myBool1 ^ myBool2
bool failed |= HasCallFailed()

USING  WITH BITS
Flipping bits:     ~00000011 = 11111100
Checking bits on:  if 00000011 & 00000010 == 00000010 then on
Turning bits on:   00000011 | 00000100 = 00000111 turning bit 2 on
Turning bits off:  00000011 & 11111101 = 00000001 turning bit 1 off
Toggling bits:     00000011 ^ 00000001 = 00000010 and back to 000000011 if called again
Shifting left:     10000011 << 3 = 00011000 (new values may not be zeroed)
Shifting right:    10000011 >> 3 = 00010000 (new values may not be zeroed)

USING WITH VALUES/MASKS 
Adding two masks: value = MASK1 | MASK2 
Turn off a mask:  value &= ~MASK1
Add a mask:       value |= MASK1
Test if masked:   if value & MASK1 == MASK1 then has mask
Multiply by 2ˣ:   value <<= 3 is same as value *= 2³
Divide by 2ˣ:     value >>= 3 is same as value /= 2³

///////////////////////////////////////////////////////////////////////////////////////////////////
//CONCURRENCY
///////////////////////////////////////////////////////////////////////////////////////////////////

MULTITHREADING
• Threads within a program share same data space/information with main thread
• Thread has a beginning, execution sequence and conclusion
• Thread has instruction pointer- keeps track of where its currently running
• Threads can be interrupted and put to sleep while other threads are running

AMDAHLS LAW
• Used to find the maximum expected improvement to an overall system when part of the system is improved
• Used in parallel computing to predict the maximum speed increase using multiple processors

*///////////////////////////////////////////////////////////////////////////////////////////////////