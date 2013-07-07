////////////////////////////////////////////////////////////////////////////////////////////
//C# NOTES
////////////////////////////////////////////////////////////////////////////////////////////
/*

CLI: COMMON LANGUAGE INFRASTUCTURE
.NET Framework is a version of this; contains CLR and BCL

CLR: COMMON LANGUAGE RUNTIME
Core of the .NET Framework. Includes Virtual Execution System (VES), 
Just in Time Compiler (JIT), Garbage Collector

BCL: BASE CLASS LIBRARY
Set of .NET classes used by .NET Languages (C#, VB.NET, C++/CLI)

JIT: JUST-IN-TIME COMPILER
Source code is compiled into an intermediate language (MSIL), 
at runtime this is compiled into native code

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
• Structs and basic data types, doesn't use new to create new objects
• variable exists on stack or register
• values are copied deeply
• Passed by-val
• Equality: If both are same type and have same contents

REFERENCE-TYPE VARIABLES
• Classes, uses new to create new objects
• object it refers to exists on the heap
• memory auto deleted once no other references for the object exist
• values are copied shallow
• Reference itself passed by-val, object it points to stays the same
• Equality: If both refer to the same interal object

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

CONST/READONLY VARIABLE DIFFERENCES:
• Const compile time and faster; Readonly runtime and slower
• Const can be declared inside methods; Readonly only as static member variable
• Const replaces value during compilation; Readonly becomes const after contructor called
• Const only used with numbers and strings; Readonly used with everything
• Const can't be initialised with 'new'; Readonly can be initialised with 'new'

VARIABLE INITIALISATION
• Class members and local variables at start of method and not within block scope auto-initialised
• Must explicitly initialise variables in block scope or error

////////////////////////////////////////////////////////////////////////////////////////////
//CLASS
////////////////////////////////////////////////////////////////////////////////////////////

INTERFACES
• No contructors/destructors allowed
• No Definitions or visibility accessors allowed
• Methods cannot be virtual
• Can't create object directly from interface
• Can be inherited by structs though returns boxed struct 

ABSTRACT CLASS
• Can't create object directly from abstract class
• Can create abstract class without defining any abstract methods
• If abstract methods are defined, must have abstract class

CLASS CONSTRUCTION
• Do not call abstract/virtual methods in constructor; undefined behaviour; calls Derived version
• If no static constructor: static members initialised anytime before first instance created
  If static constructor: called just before first instance created or static method called

1) Derived member Field Initialisaters called
2) Base member Field Initialisaters called
3) Base Constructor Body called
4) Derived Constructor Body called
5) Derived Destructor called
6) Base Desctructor called

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
//BOXING
////////////////////////////////////////////////////////////////////////////////////////////

• Boxing allows variable of type System.Object to refer to a System.ValueType
• System.Object only capable of holding reference on heap; System.ValueType may be on stack/register
• Boxing auto happens when converting value-type to object- Copies value into a new object on the heap
• New boxed object remembers what type it was created from and will only unbox if cast to correct type
• Boxing is implicit, Unboxing is reverse and explicit
• Ineffecient as Garbage Collected needs to remove new boxed object
• If nullable value-type is null, returns null before doing any boxing

////////////////////////////////////////////////////////////////////////////////////////////
//OBJECT LIFETIME
////////////////////////////////////////////////////////////////////////////////////////////

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
• No heap compaction occurs due to cost of copying large objects

HEAP GENERATIONS
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

////////////////////////////////////////////////////////////////////////////////////////////
//UNSAFE CODE/POINTERS
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

