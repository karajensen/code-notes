//////////////////////////////////////////////////////////////////////////////
//STL NOTES
//////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////
//STL CONTAINERS
//////////////////////////////////////////////////////////////////////////////

ALLOCATORS
• Handle requests for allocation and deallocation of memory for a container
• Default ones use operator new/malloc for allocation
• Custom ones may improve performance/memory usage
• Useful if lots of small allocations for associative containers as default is slow

MEMORY POOL ALLOCATOR
• Custom allocator design where large block of memory is allocated beforehand
• Requests by container are from the pool and returned to the pool
• Pool is deallocated when lifetime of container ends

VECTOR<BOOL>
• Not a STL container and doesn't hold bools
• Each element occupies single bit and represents bitfields
• Can't create pointers/references to individual bits
• To counter this returns a proxy object instead
• vector<bool>::iterator is not random-access, forward or bi-directional
• deque<bool> actually contains bool; vector<bool> was an experiment


//////////////////////////////////////////////////////////////////////////////
//SEQUENCE CONTAINERS
//////////////////////////////////////////////////////////////////////////////

VECTOR
  - random access to elements
  - fast with adding/removing end (constant time)
  - slow with adding/removing/inserting to start or middle (linear time)
  - keeps values in one chunk of continuous memory

DEQUE
  - double ended queue with random access
  - constant time for removing/adding/inserting at end and beginning
  - slower than lists, faster than vectors for removing/adding/inserting
  - slower than vectors with accessing individual members
  - stores data in various chucks with pointers to keep track of next lot
  - not safe with pointer maths as memory not all in one piece

LIST/SLIST/FORWARD LIST
  - double/single linked list with no random access
  - constant time for removing/adding/inserting at end and beginning
  - constant time for resizing 
  - stores data all over the place
  - single list built on top of double list
  - not safe with pointer maths as memory not all in one piece
  - slow to search (must iterate through list)
        Single Linked List/Forward List: Can only go forwards
        Double Linked List: Can go backwards/forwards
        Double-ended List:  Can add to both front/back of list

STRING
  - Data for strings not guaranteed to be stored in continuous memory
  - Internal representation of string not guaranteed to end with null character

//////////////////////////////////////////////////////////////////////////////
//CONTAINER ADAPTERS
//////////////////////////////////////////////////////////////////////////////
Adaptions of sequence containers

QUEUE
  - first-in-first-out
  - queue without random access
  - no iteration
  - built on top of deque using inline functions

PRIORITY-QUEUE
  - first-in-first-out
  - queue without random access
  - no iteration
  - sorted in terms of most important using heap search
  - built on top of vector & heap structure using inline functions 

STACK
  - last-in-first-out
  - no random access
  - no iteration
  - built on top of deque using inline functions

HEAP
  - created using a vector/deque container
  - Element with highest value is always at top of heap
  - Fast insertion of new elements

//////////////////////////////////////////////////////////////////////////////
//ASSOCIATIVE CONTAINERS
//////////////////////////////////////////////////////////////////////////////

MAP
  - key type is different from the value type
  - elements sorted from lowest to highest with their key
  - uses a balanced binary tree to store values, has a O(logN) lookup/insert time
  - Multi map can have multiple values to the one key
  - Unordered map Not sorted at all, fast for accessing individual elements by key

SET
  - elements themselves are the keys
  - elements in a set are always sorted from lower to higher
  - multi set can have multiple values to the once key


//////////////////////////////////////////////////////////////////////////////
//STL ITERATORS
//////////////////////////////////////////////////////////////////////////////

INPUT ITERATOR
 • iterator that a program can use to read only
 • single pass, one way iterator; can't back up once incremented
 • each time one moves through container, different order of moving 
   through elements

OUTPUT ITERATOR
 • iterator that a program can use to write only
 • single pass, one way iterator; can't back up once incremented
 • each time one moves through container, different order of moving 
   through elements

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

//////////////////////////////////////////////////////////////////////////////
//ITERATOR/REFERENCE INVALIDATION
//////////////////////////////////////////////////////////////////////////////

====================================================================
VECTOR/PRIORITY-QUEUE
====================================================================
• INSERTION: Before point of insertion unaffected unless container size is 
  greather than previous capacity and vector needs to be recopied.

• ERASURE: All after point of erase are invalidated.

====================================================================
DEQUE/QUEUE/STACK
====================================================================
• INSERTION: All invalidated unless inserted member is at the front or back in
  which iterators are invalidated and references are not.

• ERASURE: All invalidated unless erased member is at the front or back in
  which only the member erased is invalidated.

====================================================================
LIST/MAP/SET
====================================================================
• INERSTION: All unaffected.
• ERASURE: Only the erased member is invalidated.

//////////////////////////////////////////////////////////////////////////////
//IOSTREAM (INPUT/OUTPUT)
//////////////////////////////////////////////////////////////////////////////

BUFFER
A block of memory used as an intermediate, temporary storage facility for the 
transfer of information from a device to a program or from a program to a 
device. Flushed when endl is reached, when full or when specified. Controls 
rate of stream of bytes to and from program

IOSTREAM CLASS
The ostream/istream class inherits from the ios class, which inherits from 
the ios_base class. The ios_base class stores information that describes 
the format state.

INCLUDING IOSTREAM
Creates 8 stream objects (four narrow/four wide character streams)
    • CIN/WCIN
    • COUT/WCOUT
    • CERR/WCERR (error stream unbuffered)
    • CLOG/WCLOG (error stream)

CREATING AN OBJECT
 • Opens an output/input stream and automatically creates a buffer and 
   associates it with the stream.
 • includes a pointer to a streambuf object that describes the buffer 
   it contains
 • a data member (inherited from the ios_base class) that describes 
   the stream state

REDIRECTION
Redirects the stream to either use a file for input or output to a file. 
This doesn't affect CERR or CLOG unless changed.

BITMASK TYPES    
-->FMTFLAGS: used in fmtflags setf(fmtflags), prototype that takes and 
             returns fmtflags, a typedef for a bitmask type

-->IOSTATE: A stream state contained in a cout/cin object
            Consists of the three ios_base elements:
                eofbit     Is set to 1 if end-of-file reached.
                badbit     Is set to 1 if the stream has file read error
                failbit    Is set to 1 if an input operation failed to 
                           read or write the expected characters

--> OPENMODE: bitmask type for setting the file mode


OSTREAM CLASS
• translates data as binary bit patterns to an output stream of char bytes
• ostream & operator<<(type); returns reference back to the ostream object
• all methods return ostream type allowing concatenation (cout.put(1).put(1))
• cout << "one" << endl; "one" sent to buffer, returns cout. 
  Endl reached, buffer flushes, inserts \n, no cout returned.

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