///////////////////////////////////////////////////////////////////////////////////////
//STL NOTES
///////////////////////////////////////////////////////////////////////////////////////
/*

ATAN-ATAN2 DIFFERENCES:
ATAN2: Looks at 4 quadrants
ATAN: Looks at 2 quadrants
                                   +y
    atan(-x/+y) = +angle [0,-90]   |   atan(+x/+y) = +angle [0,90]
   atan2(-x,+y) = +angle [0,-90]   |   atan2(+x,+y) = +angle [0,90]
                                   |
                       -x----------|----------+x
                                   |
    atan(-x/-y) = +angle [0,-90]   |   atan(+x/-y) = -angle [0,90)
atan2(-x,-y) = +angle [-90,-180)   |   atan2(+x,-y) = +angle [90,180]
                                   -y

///////////////////////////////////////////////////////////////////////////////////////
//ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////

• Non-modifying: on const objects; Modifying: on non-const objects
• Preferable to use container's equivalent method for stability
• All ranges are [Start, End) with End non-inclusive
• Algorithms that copy over a range can be changed to insert with back/front insert iterators
• Comparison lambdas should always return false for equal values
• Functors used are passed by-val and copied
• In-build functors are faster than passing lambdas/function pointers due to them being inlined

SORT/SEARCHING
Sorting Fastest-slowest: Partitions, partial_sort, sort, stable_sort
Require sort ascending, Search speed O(logN): binary_search, lower_bound, upper_bound, equal_range
Don't require sorting, Search speed O(N): count, count_if, find, find_if
                    
CONDITION          UNSORTED      SORTED               SET/MAP         MULTI SET/MAP
does obj exist     std::find     std::binary_search  .count()        .find()
find obj           std::find     std::equal_range    .count()        .find()     
no. obj with val   std::count    std::equal_range    .count()        .count()
find all obj       std::find     std::equal_range    .equal_range()  .equal_range()
find obj if        std::find_if  std::lower_bound    .lower_bound()  .lower_bound()      

///////////////////////////////////////////////////////////////////////////////////////
//SEQUENCE CONTAINERS
///////////////////////////////////////////////////////////////////////////////////////

--------------------------------------------------------------------------
SINGLE DATA:
--------------------------------------------------------------------------
Push Front:      deque/list O(1)     < vector O(n)
Push Back:       vector O(1)         < deque O(1)      < list
Random Insert:   vector/deque        < list
Random Remove:   vector/deque        < list
std::sort:       vector              < deque           < list
std::find:       vector              < deque           < list
Iterating:       vector/deque        < list
Destruction:     vector/deque        < list
Random Access:   vector              < deque
--------------------------------------------------------------------------                
COMPLEX DATA:   
--------------------------------------------------------------------------
Push Front:      deque/list O(1)     < vector
Push Back:       vector/deque O(1)   < list
Random Insert:   list O(1)           < deque             < vector
Random Remove:   list O(1)           < deque  O(n/2)     < vector
std::sort:       list                < vector/deque
std::find:       deque               < vector            < list
Iterating:       vector/deque        < list
Destruction:     vector              < deque/list
Random Access:   vector              < deque

PERFORMANCE ISSUES
• Cache Misses when searching/iterating: vector < deque < list
• When a data is accessed, a line of data is fetched from the main memory to the cache
• Some of this data is unneeded in lists/deque as they're not continuous
• Bigger the data size the more cache misses as elements don't fit in cache lines

VECTOR
• random access to elements
• keeps values in one chunk of continuous memory

DEQUE
• double ended queue with random access
• stores data in various chucks with pointers to keep track of next lot
• not safe with pointer maths as memory not all in one piece

LIST/FORWARD LIST
• List: doubly-linked list with iteration in both directions
• Forward List: single-linked lists with iteration only forward
• Forward list smaller and more effecient
• not safe with pointer maths as memory not all in one piece
• no random access, must iterate through list
• search slow due to waiting for spread out data to be fetched into the cache
• Handles large, complex elements well

STRING
• Stored on the stack (SSO: short string optimization) if small or on the heap if large
• If on the stack and string grows can be moved to the heap
• Data for strings not guaranteed to be stored in continuous memory
• Internal representation of string not guaranteed to end with null character

VECTOR<BOOL>
• Not a STL container and doesn't hold bools
• Each element occupies single bit and represents bitfields
• Can't create pointers/references to individual bits so uses proxy
• vector<bool>::iterator is not random-access, forward or bi-directional
• deque<bool> actually contains bool; vector<bool> was an experiment
• Saves space but slower as requires going through proxy object
• Don't use auto when accessing members as type chosen is std::vector<bool>::reference

///////////////////////////////////////////////////////////////////////////////////////
//CONTAINER ADAPTERS
///////////////////////////////////////////////////////////////////////////////////////

QUEUE
• first-in-first-out
• no iteration/random access
• built on top of deque using inline functions

PRIORITY-QUEUE
• first-in-first-out
• no iteration/random access
• sorted in terms of most important using heap search
• built on top of vector & heap structure using inline functions 

STACK
• last-in-first-out
• no iteration/random access
• built on top of deque using inline functions

HEAP
• created using a vector/deque container
• Element with highest value is always at top of heap
• Fast insertion of new elements

///////////////////////////////////////////////////////////////////////////////////////
//ASSOCIATIVE CONTAINERS
///////////////////////////////////////////////////////////////////////////////////////

MAP
• Based on balanced binary tree
• Sorted from lowest to highest with their key
• has a O(logN) lookup and insert time
• Multi map can have multiple values to the one key
• Map iterators point to pairs where key is const to prevent breaking sorted order

UNORDERED MAP
• Based on hash table
• Not sorted
• Fast for accessing individual elements by key

SET
• elements themselves are the keys
• elements in a set are always sorted from lower to higher
• multi set can have multiple values to the one key
• If changing value in set using iterator, make sure set is resorted

///////////////////////////////////////////////////////////////////////////////////////
//ITERATOR CATEGORIES
///////////////////////////////////////////////////////////////////////////////////////

INPUT ITERATOR
• iterator that a program can use to read only
• single pass, one way iterator; can't back up once incremented
• each time one moves through container, different order of moving through elements

OUTPUT ITERATOR
• iterator that a program can use to write only
• single pass, one way iterator; can't back up once incremented
• each time one moves through container, different order of moving through elements

FORWARD ITERATOR
• Goes through sequence in same order each time
• Multi pass, can still access prior elements once incremented
• Read and write abilities

BIDIRECTIONAL ITERATOR
• Goes through sequence in same order each time
• Multi pass, Can increment and decrement
• Read and write abilities

RANDOM ACCESS ITERATOR
• Goes through sequence in same order each time
• Can jump to any element in container
• Multi pass, Can increment and decrement
• Read and write abilities

--------------------------------------------------------------------
Capability    Input   Output   Forward  Bidirectional Random Access
--------------------------------------------------------------------
Read          Yes     No       Yes      Yes           Yes
Write         No      Yes      Yes      Yes           Yes
Fixed order   No      No       Yes      Yes           Yes
++i/i++       Yes     Yes      Yes      Yes           Yes
--i/i--       No      No       No       Yes           Yes
i[n]          No      No       No       No            Yes
i+n, i-n      No      No       No       No            Yes
i+=n, i-=n    No      No       No       No            Yes

///////////////////////////////////////////////////////////////////////////////////////
//ITERATOR TYPES
///////////////////////////////////////////////////////////////////////////////////////

CONTAINER ITERATORS
• Vector/Array/Deque: Random Access Iterator
• List: Bidirectional Iterator
• Forward List: Forward Iterator
• Map: Bidirectional Iterator
• Queue/Stack: No Iteration

BACK INSERT ITERATOR
• Output iterator
• inserts items at the end of the container. 
• calls .push_back(), only used with containers that have it (vector, deque, string, list)
• For set/maps, only affects insertion performance as values are sorted

FRONT INSERT ITERATOR
• Output iterator
• inserts items at the front of the container.
• calls .push_front(), only used with containers that have it (deque, list)
• For set/maps, only affects insertion performance as values are sorted

INSERT ITERATOR
• Output iterator
• inserts items in front of the location specified as an argument
• For set/maps, only affects insertion performance as values are sorted

OSTREAM ITERATOR
• Output iterator
• ineffecient due to lots of error checking/formatting

OSTREAMBUF ITERATOR
• Output iterator
• Faster than ostream_iterator

ISTREAM ITERATOR
• Input iterator
• ineffecient due to lots of error checking/formatting

ISTREAMBUF ITERATOR
• Input iterator
• Faster than istream_iterator, doesn't skip over any character
• directly grabs what's next in stream buffer, no extra checking/formatting

///////////////////////////////////////////////////////////////////////////////////////
//ITERATOR/REFERENCE INVALIDATION
///////////////////////////////////////////////////////////////////////////////////////

VECTOR/PRIORITY-QUEUE
• Insertion: Before point of insertion unaffected unless container size is 
  greather than previous capacity and vector needs to be recopied.
• Erasure: All after point of erase are invalidated.

DEQUE/QUEUE/STACK
• Insertion: All invalidated unless inserted member is at the front or back in
  which iterators are invalidated and references are not.
• Erasure: All invalidated unless erased member is at the front or back in
  which only the member erased is invalidated.

LIST/MAP/SET
• Inerstion: All unaffected.
• Erasure: Only the erased member is invalidated.

///////////////////////////////////////////////////////////////////////////////////////
//EXCEPTIONS
///////////////////////////////////////////////////////////////////////////////////////

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

EXCEPTION SAFETY
• Use RAII to auto cleanup resources if exception is thrown
• Only change state once any possible errors have been resolved
• Destructor/deallocation/swap functions should never throw as impossible to safely cleanup

EXCEPTION NEUTRAL
• Exceptions thrown should be propagated unchanged to the objects's caller

ABRAHAMS GUARANTEE: BASIC
• Failures/exceptions might alter program state
• No leaks occur and affected objects are still usable but not in predictable state

ABRAHAMS GUARANTEE: STRONG
• Failures/exceptions guarantee program state is unchanged
• No leaks occur and objects and iterators not affected

ABRAHAMS GUARANTEE: NOTHROW
• Failure and exceptions do not happen

NON-THROWING METHODS
• If objects they work on throw, undefined behaviour
• All destructors auto have noexcept keyword
    - delete myPointer;
    - delete[] myArray;
    - std::swap
    - All destructors in std library

STANDARD LIBRARY EXCEPTIONS
• Exception safe (some areas only give basic guarantee) and exception neutral
• Have strong guarantee for all operations except two
• Multi-range insert(begin,begin,end) has basic guarantee
• Vector and Deque only: inserts or erases for multi or single objects are basic guarantee 
  if object constructor or assignment operator throws, otherwise strong guarantee

///////////////////////////////////////////////////////////////////////////////////////
//CONTAINER MEMORY ALLOCATION
///////////////////////////////////////////////////////////////////////////////////////

ALLOCATORS
• Handle requests for allocation and deallocation of memory for a container
• Default ones use operator new/malloc for allocation
• Custom ones may improve performance/memory usage
• Useful if lots of small allocations for associative containers as default is slow

MEMORY POOL ALLOCATOR
• Custom allocator design where large block of memory is allocated beforehand
• Requests by container are from the pool and returned to the pool
• Pool is deallocated when lifetime of container ends

///////////////////////////////////////////////////////////////////////////////////////
//IOSTREAM (INPUT/OUTPUT)
///////////////////////////////////////////////////////////////////////////////////////

BUFFER
• Bloack of memory for storage/transfer of information
• Flushed when endl, when full or when specified
• Controls rate of stream of bytes to/from buffer

BITMASK TYPES    
• OPENMODE: bitmask type for setting the file mode
• FMTFLAGS: Setting the formatting for the stream
• IOSTATE: A stream state contained in a cout/cin object
           eofbit  = Is set to 1 if end-of-file reached.
           badbit  = Is set to 1 if the stream has file read error
           failbit = Is set to 1 if an input operation failed to read/write expected characters

IOSTREAM
• Creates 8 stream objects (four narrow/four wide character streams)
  CIN/WCIN
  COUT/WCOUT
  CERR/WCERR (error stream unbuffered)
  CLOG/WCLOG (error stream)

FILESTREAM
• Redirects the input/output streams to either use a file instead of console
• This doesn't affect CERR or CLOG unless changed.

OSTREAM CLASS
• translates data as binary bit patterns to an output stream of char bytes
• ostream & operator<<(type); returns reference back to the ostream object
• all methods return ostream type allowing concatenation (cout.put(1).put(1))
• cout << "one" << endl; "one" sent to buffer, returns cout. 
• Endl reached, buffer flushes, inserts \n, no cout returned.

ISTREAM CLASS
• translates data as char from the input stream into binary bit patterns
• istream & operator>>(type &); returns reference back to the istream object
• all methods return istream type allowing concatenation

BINARY FILES
• Smaller, take up less room
• No hidden conversions; written in computer binary language
• More accurate as no conversion/round-off errors for numbers
• Risky as different computers have different internal representation

*/////////////////////////////////////////////////////////////////////////////