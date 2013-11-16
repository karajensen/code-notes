////////////////////////////////////////////////////////////////////////////////////////////
//C# NOTES
////////////////////////////////////////////////////////////////////////////////////////////
/*

.NET FRAMEWORK
• Development framework for creating windows applications
• Used by languages C#, VB.NET, C++/CLI
• A type of CLI (Common Language Infrastructure) which contains:
    | 
    |  CLR: Common Language Runtime
    |  • Virtual Execution System (VES)
    |  • Garbage Collector
    |  • Just In Time Compiler
    |  • Managed Heap
    |  
    |  BCL/FCL: Base/Framework Class Library
    |  • Shared .NET classes used by .NET languages

VES: VIRTUAL EXECUTION SYSTEM
• Environment for executing managed code

JIT: JUST-IN-TIME COMPILER
• Source code is compiled into Microsoft intermediate language (MSIL)
• MSIL is converted to native code at runtime

ASSEMBLY/MODULES
• Exe/dll that contain metadata that describe internal version number/data details
• Only loaded if required. Can use two versions of same assembly in single application
• Share assemblies between applications using Global Assembly Cache
• Assemblies must be strong named; guaranteed uniqueness
• Assemblies contain modules. Modules contain classes.

////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLES
////////////////////////////////////////////////////////////////////////////////////////////

VALUE-TYPE VARIABLES
• Structs, enums, nullable/basic data types, reference/pointer used to store a reference variable
• Variable exists on stack or register, passed by-val and are copied deeply
• Memory auto deleted by stack when out of scope
• Equality: If both are same type and have same contents
• Sealed: can't inherit anything or be derived from

REFERENCE-TYPE VARIABLES
• Classes, arrays, boxed value-types
• Variable exists in the heap with a value-type object refering to it, copied shallow
• Memory auto deleted by garbage collector when reference count equals zero
• Equality: If both have the same memory address
• Can inherit one class and be derived from

ARRAYS
• All arrays are reference even if elements are value-types
• Inherit System.Array

STRINGS
• String literals are interned so that for each occurrence of a particular
  string only occurs once in memory and can be referenced by multiple variables

CONST/READONLY VARIABLE DIFFERENCES:
• Const compile time and faster; Readonly runtime and slower
• Const can be declared inside methods; Readonly only as member variable
• Const replaces value during compilation; Readonly becomes const after contructor called
• Const only used with inbuilt numbers/strings; Readonly used with everything
• Const can't be initialised with 'new'; Readonly can be initialised with 'new'
• Const can never be changed. Readonly objects only make the reference to the object 
  constant, not the object itself. The reference can also be hacked through reflection.

VARIABLE INITIALISATION
• Class members and local variables at start of method and not within block scope auto-initialised
• Must explicitly initialise variables in block scope or error

////////////////////////////////////////////////////////////////////////////////////////////
//CLASS/STRUCT/FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////

ORDER OF ARGUMENT EVALUATION
• Always evaluated left to right in expressions and argument passing

STRUCTS [VALUE-TYPE]
• All variables not explicitly initialised are set to default
• struct auto defaults to public, methods default to private
• Can't create user-defined constructor/destructors
• Auto creates default constructor/destructor, System.Object methods

CLASSES [REF-TYPE]
• All variables not explicitly initialised are set to default
• class auto defaults to internal, methods default to private
• Default constructor/destructor only generated if none provided
• Auto creates default constructor/destructor, System.Object methods, operator==

ABSTRACT CLASS
• Can't create object directly from abstract class, can be casted to
• Partial Implementation- Don't have to override virtual non-abstract methods
• No inheritance by structs
• Must used abstract keyword for methods and class
• Can inherit one class and implement multiple interfaces

INTERFACES
• Can't create object directly from interface, can be casted to
• No Partial Implementation- Have to implement all methods
• Can be inherited by structs though returns boxed struct
• Methods are auto abstract that derived class can only override unless derived uses virtual 
• Can extend multiple interfaces through inheritance. Can not inherit classes.
• No constructors/finalisers allowed
• No member variables, only properties which only create the variable when implemented
• No visibility accessors allowed in interface, derived defines them
• Methods can be use Implicit or Explicit Implementation
    - Implicit can only be used on one method definition
    - Explicit required if interfaces inherited have same members to avoid conflicts
    - Explicit can't use visibility, abstract, virtual keywords
    - Explicit can only be accessed if casted to interface implemented from

CLASS CONSTRUCTION
• Do not call abstract/virtual methods in constructor; undefined behaviour; calls Derived version
• If no static constructor: static members initialised anytime before first instance created
  If static constructor: called just before first instance created or static method called

1) Derived member Field Initialisaters
2) Base member Field Initialisaters
3) Base Constructor Body
4) Derived Constructor Body
5) Derived Dispose or Derived Finaliser
6) Base Dispose or Base Finaliser

OBJECT DESTRUCTION
Destructor: obtained through inheriting IDisposable, called explicitly to clean up unmanaged objects
Finaliser: called when object is garbage collected, implement for cleaning managed objects (c++ destructor syntax)

CLASS VISIBILITY
• Visibility levels: Public -> Internal -> Protected Internal -> Protected -> Private
• First-level class in namespace can only be public/internal; subclasses can be anything
• Class cannot be more visible than its base class (base interfaces excluded)
• Interface cannot be more visible than its base interface
• Virtual/Abstract methods cannot be private
• Virtual/Abstract methods must have same visibility between Base/Derived classes

PROPERTIES
• Method that doesn't use () when called
• No 'set' entry automatically makes the property readonly
• Accessed syntactically the same as member variable but involve different instructions

INDEXER/PROPERTY DIFFERENCES
• Indexer accessed through index and [], Properties accessed as though member variable
• Indexer cannot be static, Properties can be static
• Indexer passes in index value, Properties don't pass in anything, both have 'value' keyword

ATTRIBUTES
• Hidden objects at runtime that contain metadata- information about the class
• Use reflection to access

////////////////////////////////////////////////////////////////////////////////////////////
//INHERITANCE
////////////////////////////////////////////////////////////////////////////////////////////

STRUCTS: Inherit no classes, multiple interfaces, auto inherits System.ValueType
CLASSES: Inherit one class, multiple interfaces, auto inherits System.Object if none specified
INTERFACES: Inherit no classes, multiple interfaces

SYSTEM.OBJECT
• All reference/value types ultimately derive from System.Object
• Classes auto inherit System.Object if no base class specified
• Has Static Members ReferenceEquals()/Equals()
• Includes methods: 
    Equals()
    Finalize()
    GetHashCode()
    GetType()
    MemberwiseClone()
    ToString()

SYSTEM.VALUETYPE
• All value types (struct,enum,bool,int etc.) ultimately derive from System.ValueType
• System.ValueType itself derives from System.Object
• Can't directly derive from it; must derive from struct
• Overrides methods:
    Equals()
    GetHashCode()
    ToString()

IENUMERABLE<T>
• All containers derive from it, allows iteration with foreach

////////////////////////////////////////////////////////////////////////////////////////////
//OPERATOR OVERLOADING
////////////////////////////////////////////////////////////////////////////////////////////

OVERLOAD RESOLUTION
1) Normal methods
2) Generic methods

---------------------------------------------------------------------------
ASSIGNMENT OVERLOADS
---------------------------------------------------------------------------
Can be defined: 
!   ~  ++  --  true  false

Can be defined; x= can't be defined and is auto-defineds:
+(+=)  -(-=)   *(*=)   /(/=)   %(%=)   &(&=)(&&)   |(|=)(||)  ^(^=)  >>(>>=)   <<(<<=) 

---------------------------------------------------------------------------
COMPARISON OVERLOADS
---------------------------------------------------------------------------
Must be defined in pairs:
==  != 
<  >
<=  >=

---------------------------------------------------------------------------
CAN'T BE OVERLOADED
---------------------------------------------------------------------------
 =  .  ?:   ->   new   is   sizeof   typeof

() can't be overloaded but can use conversion function
[] can't be overloaded but can use indexer property

////////////////////////////////////////////////////////////////////////////////////////////
//DELEGATES/EVENTS/LAMBDAS
////////////////////////////////////////////////////////////////////////////////////////////

DELEGATES
• Derives from System.Delegate
• Reference to a method or lambda
• Sealed; cannot be derived from

ANONYMOUS DELEGATES
• Can't use goto/break/continue to move outside delegate block
• Auto captures a reference to any variables used within block
• Until delegate lifetime is over these variables remain in memory
• Cannot capture any ref/out variables from parent scope
• Cannot use pointer or access unsafe code

EVENTS
• Publisher: class that sends the event
• Subscriber: class that recieves/handles the event
• Events that have no subscribers are never called.
• Events are based on the EventHandler delegate and the EventArgs base class

LAMBDAS
• A captured variable will not be garbage-collected until the lamda goes out of scope
• Variables inside lambda are not visible outside
• Lambda cannot directly capture a ref/out parameter from the parent method
• Cannot contain goto, break, containue that moves to outside lambda

////////////////////////////////////////////////////////////////////////////////////////////
//OBJECT LIFETIME
////////////////////////////////////////////////////////////////////////////////////////////

ROOT: Memory address for object on heap or null

CLR HEAP
• Reference-types live on heap; Value-types live in heap, register or stack
• Constructing object through new adds block to the heap
• Garbage collector removes the memory at intervals
• Each block has a header; includes object type, and information for hash generation
• 32-bit system, header is +8 bytes, 64-bit system, header is +16 bytes per object

GARBAGE COLLECTION
• When object is out of scope/not being used anymore, marked as dead by Garbage Collection
• Garbage collection monitors own performance and adjusts settings as needed
• Forcing garbage collection is not good; it can't tune itself properly

LARGE OBJECT HEAP
• Large objects greater than certain byte amount are stored on Large Object Heap
• No heap relocation/compaction occurs due to cost of copying large objects

HEAP GENERATIONS
• When Generation 0 runs out of memory, does a collection and moves objects to next gen
• The longer the object stays alive the more expensive it is to delete
    Generation 0: Hasn't survived a garbage collection yet
    Generation 1: Recently created object that's survived
    Generation 2: Oldest generation for long lived objects
• GC most effecient for objects with long or short lives.
• GC least effecient for deleting objects just entering Generation 2
  knowledge of this section will need to be rebuilt, may not be in the cache

HEAP COMPACTION
• As objects destroyed, heap becomes fragmented
• Moving remaining objects together and then adding to heap is cheaper than slotting into the gaps
• Older the generation, less heap compaction occurs
• Careful when refering to direct addresses of objects as they will move around after compaction

PINNING MEMORY BLOCKS
• Pinning a block sets a flag to disallow moving by the garbage collector
• Calls to unmanaged code that requires pointers will auto pin/unpin the block
• Causes more fragmentation and effeciancy issues to CLR heap, none to Large Object Heap

WEAK REFERENCES
• Short Weak Reference: Tells when object is unreachable or fully removed by GC
• Long Weak Reference: Tells when object is fully removed by GC

BOXING
• Process of converting a value type to a System.Object reference type
• Copy of the value-type is wrapped in System.Object and put on the heap
• This boxed object remembers what the original type was and will only unbox if cast correctly
• Unboxing copies the boxed value to another value-type variable
• Boxing is implicit, Unboxing is reverse and explicit
• Ineffecient as copying required and Garbage Collected needs to remove new boxed object
• If nullable value-type is null, returns null before doing any boxing

////////////////////////////////////////////////////////////////////////////////////////////
//UNSAFE CODE
////////////////////////////////////////////////////////////////////////////////////////////

POINTERS
• Works on sbyte, byte, short, ushort, int, uint, long, ulong, char, float, double, decimal, bool
• Works on void, enum and structs with value-types only
• Cannot point to reference as garbage collector doesn't keep track of pointers
• Do not inherit from System.Object- No conversions exist between pointers/object
• Boxing/Unboxing not supported

UNSAFE CODE
• Methods, types, and code blocks can be defined as unsafe
• Can increase performance by removing bounds/runtime checks
• Required when calling native functions that require pointers
• /unsafe must be set to compile

////////////////////////////////////////////////////////////////////////////////////////////
//REFLECTION
////////////////////////////////////////////////////////////////////////////////////////////

Used For:
• Accessing attributes of a class/method
• Examining and instantiating types in an assembly
• Building new types at runtime (Reflection.Emit)
• Creating compilers


*///////////////////////////////////////////////////////////////////////////////////////////

