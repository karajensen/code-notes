////////////////////////////////////////////////////////////////////////////////////////////
//C# NOTES
////////////////////////////////////////////////////////////////////////////////////////////
/*

.NET LANGUAGES: C#, VB.NET, C++/CLI

CLI: COMMON LANGUAGE INFRASTUCTURE
.NET Framework is a version of this; contains CLR and BCL

CLR: COMMON LANGUAGE RUNTIME
Includes Virtual Execution System (VES), Just in Time Compiler (JIT), Garbage Collector

BCL: BASE CLASS LIBRARY
Set of .NET classes used by .NET Languages

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
• Doesn't use new to create new objects
• may exist on the stack, register or heap
• values are copied deeply
• Passed by-val

REFERENCE-TYPE VARIABLES
• Uses new to create new objects
• object it refers to exists in seperate memory on heap
• memory auto deleted once no other references for the object exist
• values are copied shallow
• Reference itself passed by-val, object it points to stays the same

STRUCTS [VALUE-TYPE]
• All variables not explicitly initialised are set to default
• class auto defaults to public, methods default to private
• Default constructor/destructor auto generated and required
• Auto creates: default constructor/destructor

COVARIANCE: Allows assinging MyClass or derived from it to MyClass object [polymorphism basis]
CONTRAVARIANCE: Allows assigning MyClass or what MyClass derived from to MyClass object 
INVARIANCE: Allows neither

////////////////////////////////////////////////////////////////////////////////////////////
//CLASS
////////////////////////////////////////////////////////////////////////////////////////////

CLASSES [REF-TYPE]
• All variables not explicitly initialised are set to default
• class auto defaults to internal, methods default to private
• Default constructor/destructor only generated if none provided
• Auto creates: default constructor/destructor, operator==

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

INDEXER/PROPERTY DIFFERENCES
• Indexer accessed through index and [], Properties accessed as though member variable
• Indexer cannot be static, Properties can be static
• Indexer passes in index value, Properties don't pass in anything, both have 'value' keyword

////////////////////////////////////////////////////////////////////////////////////////////
//INHERITANCE
////////////////////////////////////////////////////////////////////////////////////////////

• Inheriting classes: Structs: none, Classes: one, Interfaces: Multiple
• Inheriting interfaces: Structs, classes, interfaces: Multiple
• If no base class specified, class/struct auto inherits System.Object
• Interfaces don't auto inherit but an interface object can be converted to 
  System.Object as all interface objects must be created from a class/struct

SYSTEM.OBJECT
• All reference/value types ultimately derive from System.Object
• Classes auto inherit System.Object if no base class specified

SYSTEM.VALUETYPE
• All value types (struct,enum,bool,int etc.) ultimately derive from System.ValueType
• System.ValueType itself derives from System.Object
• Can't directly derive from it; must derive from struct


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
//DELEGATES/EVENTS
////////////////////////////////////////////////////////////////////////////////////////////

DELEGATES
• Derives from System.Delegate
• Reference to a method
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

////////////////////////////////////////////////////////////////////////////////////////////
//BOXING
////////////////////////////////////////////////////////////////////////////////////////////

object boxed = 10;
int unBoxed = boxed as int;

• Value-types ultimately derive from System.ValueType which derives from System.Object
• System.Object only capable of holding reference on heap; value-types may be on stack/register
• Boxing allows variable of type System.Object to refer to a value type
• Not effecient as GC has to clean up all new objects; new objects copy value from original

CREATING BOXES
• Auto happens when converting value-type to object; Creates new boxed object on heap with a copy of the value
• New boxed object remembers what type it was created from
• Requires explicity casting back to object. If casted to correct type, returns copy of value back

BOXING NULLABLE VALUE-TYPES
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


*///////////////////////////////////////////////////////////////////////////////////////////

