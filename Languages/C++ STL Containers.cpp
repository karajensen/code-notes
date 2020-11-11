/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STL CONTAINER OVERVIEW
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
SEQUENCE CONTAINERS
--------------------------------------------------------------------------------------------------------------
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
• Stored on the stack (Short String Optimization) if capacity <= 15 characters else on the heap
• Moving strings with SSO has no performance gain over copying them
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
**************************************************************************************************************/

/*************************************************************************************************************
CONTAINER ADAPTERS
--------------------------------------------------------------------------------------------------------------
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
**************************************************************************************************************/

/*************************************************************************************************************
ASSOCIATIVE CONTAINERS
--------------------------------------------------------------------------------------------------------------
• Default sort function is operator< and is auto sorted when new key is inserted
• Keys are const and should not be changed as this affects the sort order

MAP
• Based on balanced binary tree
• Sorted from lowest to highest with their key
• has a O(logN) lookup and insert time
• Multi map can have multiple values to the one key

UNORDERED MAP
• Based on hash table
• Not sorted
• Fast for accessing individual elements by key

SET
• Elements themselves are the keys
• Elements in a set are always sorted from lower to higher
• Multi set can have multiple values to the one key
**************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STRING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>

string str; // initialises to ""
string str("str"); 
string str(str2, 1, n) // from index 1 to 1+n, or until end. N default param is end (npos)
string str(n,'a'); // fill n times with 'a'
string str(char_array, n); // fill with char_array of n length
wstring wstr(L"wstr");
auto str = "str"s; // creates a std::string rather than literal string

str[0]
string::npos // maximum allowable size for string; maximum value of unsigned int
str.data() // returns a pointer to the first character of a string
str.empty() // returns true/false if empty (faster than size)
str.size() // number of elements
str.length() // same as str.size()
str.replace(i, n, "str") // replace over index i for n characteres
str.c_str() // returns pointer to const cstring
str.substr(i, n) // creates substring from index i with n characters
str.clear() // removes all from container
str.back() // returns reference to last element
str.front() // returns reference to first element
str.swap(str2) // swaps two of SAME containers around
str.erase(Begin(str),End(str)) // Erases the elements in the range
str.erase(it) // Erases at particular place
str.max_size() // returns maximum possible size
str.resize(x) // resizes container for x units
str.capacity() // returns number of elements vector can contain before more memory needed
str.reserve(100) // reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
str.insert(i, "str") // inserts before index i
str.insert(i, "str", j, n) // insert before index i starting at index j for n characters
str.insert(i, n,'a') // Inserts n references of a before index i
str.insert(str.begin(), 'a') // Inserts a before iterator
str.insert(str.begin(), n, 'a') // Inserts n references of a before iterator
str.insert(str.begin(), str2.begin(), str2.end()) // Insert copies of elements in the range before iterator
str.at(i) // returns character at index with bounds checking

// FIND METHODS
// returns index int or if not found
str.find(chararray, 2) // starts at position 2 and searches for the substring (cstring/string)
str.find("str", 2)  // returning first occurance's index or string::npos
str.rfind() // finds last occurance of substring
str.find_first_of("str") // returns index of first occurance of ANY character in substring
str.find_last_of("str") // returns index of last occurance of ANY character in substring
str.find_first_not_of("str") // returns index of first occurance of ANY character NOT in substring
str.find_last_not_of("str") // returns index of last occurance of ANY character NOT in substring

// ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STRING VIEW
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string_view>
    
// Slice in an existing string buffer, does not require a memory allocation
string_view view("str");
string_view view(array, sizeof(array)); // char array[3] = {'B', 'a', 'r'};
string_view view(&str[0], str.size());    

view[0]
string::npos // maximum allowable size for string; maximum value of unsigned int
view.empty(); // returns true/false if empty
view.data() // returns a pointer to the first character of a string
view.substr(i, n); // returns string_view from index i with n characters, O(1): faster than std::string substr
view.remove_prefix(n); // returns string_view removing n characters from start
view.remove_suffix(n); // returns string_view removing n characters from end
view.back() // returns reference to last element
view.front() // returns reference to first element
view.at(i) // returns character at index with bounds checking

// ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAY
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <array>

std::array<int, 40> arr; //fixed, continuous array stored on stack, n must be const

arr[i]
arr.assign(0) // assigns array with value
arr.fill(0)   // fills array with value
arr.empty()   // returns true/false if empty (faster than size)
arr.size()    // number of elements
arr.data()    // returns pointer to internal data
arr.clear()   // clears array
arr.front()   // get first element
arr.back()    // get last element

//ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VECTOR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>

vector<int> v;
vector<int> v(size);
vector<int> v(v2.begin(), v2.end());
vector<int> v = { 1 };
vector<int> v{ 1 };

v[i]                    // No bounds checking
v.at(0)                 // Bounds checking
v.empty()               // returns true/false if empty (faster than size)
v.size()                // number of elements
v.clear()               // removes all from container
v.back()                // returns reference to last element
v.front()               // returns reference to first element
v.swap(V2)              // swaps two of SAME containers around
v.erase(itr1, itr2)     // Erases the elements in the range
v.erase(itr)            // Erases at particular place
v.max_size()            // returns maximum possible size
v.resize(x)             // resizes container for x units
v.capacity()            // returns number of elements vector can contain before more memory needed
v.reserve(100)          // reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
v.pop_back()            // Deletes the element at the end of a list.
v.push_back(x)          // Adds an element to the end of a list.
v.emplace_back(2.0, 1)  // constructs directly into container; takes constructor arguments for type inside container
v.assign(n, value)                        // assigns value over first n elements, resizes if assigning more than capacity
v.assign(v2.begin(), v2.end())            // assigns values from another container, resizes if assigning more than capacity
v.insert(v.begin(), t)                    // Inserts a reference of t before iterator
v.insert(v.begin(), n, t)                 // Inserts n references of t before iterator
v.insert(v.begin(), v2.begin(), v2.end()) // Insert copies of elements in the range before iterator

//ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEQUE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <deque> 

deque<int> d;
deque<int> d;
deque<int> d(size);
deque<int> d(d2.begin(), d2.end());
deque<int> d = {1};
deque<int> d{1};

d[i]
d.empty()               // returns true/false if empty (faster than size)
d.size()                // number of elements
d.pop_back()            // Deletes the element at the end of a list.
d.pop_front()           // Deletes the element at the beginning of a list.
d.push_back(x)          // Adds an element to the end of a list.
d.push_front(x)         // Adds an element to the beginning of a list.
d.assign(n, value)      // assigns reference to value over first n elements
d.clear()               // removes all from container
d.back()                // returns reference to last element
d.front()               // returns reference to first element
d.swap(D2)              // swaps two of SAME containers around
d.erase(itr1, itr2)     // Erases the elements in the range
d.erase(itr)            // Erases at particular place
d.max_size()            // returns maximum possible size
d.resize(x)             // resizes container for x units
d.capacity()            // returns number of elements vector can contain before more memory needed
d.reserve(100)          // reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
d.insert(d.begin(), t)                      // Inserts a reference of t before iterator
d.insert(d.begin(), n, t)                   // Inserts n references of t before iterator
d.insert(d.begin(), d2.begin(), d2.end())   // Insert copies of elements in the range before iterator

//ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LIST
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <list> 
#include <forward_list>

list<int> l;
forward_list<int> fl; // only links forward, no reverse iteration

l.empty()                // returns true/false if empty (faster than size)
l.pop_front()            // Deletes the element at the beginning of a list.
l.push_front(x)          // Adds an element to the beginning of a list.
l.reverse()              // Reverses the order in which the elements occur in a list.
l.remove(x)              // Removes all elements with value x from list
l.remove_if(boolLambda)  // Removes all elements returning true from lamda
l.sort()                 // sorts using < in ascending order  speed: L(N*logN)  stable sort
l.merge(one)             // merges one into two, leaving one empty  assumes both are sorted
l.splice(l.begin(), l2)  // inserts L2 in front of L.begin(), leaving one empty
l.unique()               // removes duplicate values in list, assumes list is sorted
l.clear()                // removes all from container
l.front()                // returns reference to first element
l.swap(L2)               // swaps two of SAME containers around
l.erase(itr1, itr2)      // Erases the elements in the range  erase_after() for forward list
l.erase(itr)             // Erases at particular place  erase_after() for forward list
l.max_size()             // returns maximum possible size
l.resize(x)              // resizes container for x units

//LIST SPECIFIC METHODS
l.size()  // number of elements
l.pop_back() // Deletes the element at the end of a list.
l.push_back(x) // Adds an element to the end of a list.
l.back()  // returns reference to last element
l.capacity() // returns number of elements vector can contain before more memory needed
l.emplace_back(obj, 0, "arg2") // Creates element at end and calls constructor with given arguments (varadic)
l.emplace_front(obj, 0, "arg2") // Creates element at front and calls constructor with given arguments (varadic)
l.emplace(itr, obj, 0, "arg2") // Creates element before itr and calls constructor with given arguments (varadic)
l.insert(l.begin(), t) // Inserts a reference of t before iterator
l.insert(l.begin(), n, t) // Inserts n references of t before iterator 
l.insert(itr, l2.begin(), l2.end()) // Insert copies of elements in the range before itr

//FORWARD LIST SPECIFIC METHODS
fl.emplace_after(itr, obj, 0, "arg2") // Creates element at after itr and calls constructor with given arguments (varadic)
fl.insert_after(fl.begin(), t) // Inserts a reference of t after iterator 
fl.insert_after(fl.begin(), n, t) // Inserts n references of t after iterator
fl.insert_after(itr, fl2.begin(), fl2.end()) // Insert copies of elements in the range after itr

//ITERATORS
begin()   end()   cbegin()   cend()  // Both lists
rbegin()  rend()  crbegin()  crend() // List only

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAP
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <map> 
#include <unordered_map>

// ORDERED MAP
// Every entry is sorted according to a compare function std::function<bool(const T&, const T&)>
std::map<Key, T> m;
std::map<key, T, std::function<bool(const T&, const T&)>> m(comparisonFn);
std::map<Key, T, comparisonFunctor> m;
std::multi_map<Key, T> mm // can have multiple entries for the one key
std::map<Key, T>::iterator itr;   // iterator for map

// UNORDERED MAP (HASH TABLE)
// Organized into buckets depending on hash values to allow for fast access using keys
std::unordered_map<KeyType, ObjType> um;
std::unordered_multimap<KeyType, ObjType> umm;

// VALUE TYPE
// value_type is std::pair<const KeyType, ObjType>
// const Key is important when iterating
// If std::pair<Key,T> used will create temporary copy of pair
std::map<Key, T>::value_type; /*or*/ std::pair<const Key, T>
for (const std::pair<const Key, T>& pair : m){}
for (const auto& [key, value] : m) {}

// METHODS
m["Key"]        // returns object if key exists or creates through default contructor if doesn't exist 
m.at("Key")     // returns object at key or throws out_of_range exception if doesn't exist
m.empty();      // returns true/false if empty (faster than size)
m.size();       // number of element pairs
m.count("Key")  // returns number of items that have that key
m.erase("Key")  // removes element with matching key, returns number of elements removed or 0 if none
m.find("Key")   // returns MyMap.end() if not found or iterator MyMap::iterator if found
m.merge(m2)

// INSERTING ITEMS
// More effecient to use insert; operator[] creates default object then assigns if object doesn't exist 
m.insert(MyMap::value_type("Key",2.0)); // value_type is typedef for maps pair
m["Key"] = 2.0; // Adds entry if key doesn't exist otherwise overwrites

//ITERATORS
begin()   end()   cbegin()   cend() 
rbegin()  rend()  crbegin()  crend()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SET
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <set> 
#include <unordered_set>

set<int> s;

s.empty();   // returns true/false if empty (faster than size)
s.size();    // number of elements
s.clear();   // clear the container
s.insert(x); // Returns pair: itr to the inserted item or item that prevented insertion / bool if successful
s.find(x);   // return iterator to element position or S.end() if not found
s.erase(x);  // erase element
s.erase(itr) // erase element at iterator 
s.merge(s2)

//ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

//UNORDERED SET (HASH TABLE)
//Organized into buckets depending on hash values to allow for fast access using keys
std::unordered_set<int> us;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUEUE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <queue>

queue<int> q; //FIFO queue
priority_queue<int> pq; //largest is automatically sorted to front of queue using heap sort

q.empty()   // returns true/false if empty (faster than size)
q.size()    // number of elements
q.front()   // returns reference to element at front of queue
q.back()    // returns reference to element at back of the queue
q.push(x)   // inserts x at back
q.pop()     // removes element at front

// Clearing a queue
std::queue<int> empty; 
std::swap(q, empty);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STACK
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stack> 

stack<int> s; //LIFO stack

s.empty()   // returns true/false if empty (faster than size)
s.size()    // number of elements
s.top()     // returns reference to element at top of stack
s.push(x)   // inserts type int to top of the stack
s.pop()     // removes the element at top of stack

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BITSET
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <bitset>

bitset<n> b;          // Fills container with n zeroed bits, n must be constant, zero-based index
bitset<n> b(value)    // Takes integer type and flips required bits
bitset<n> b(0x080)    // Takes hex value and flips required bits
bitset<n> b("110101") // Takes binary string and flips requied bits starting from bit 0

b[1]           // access bit
b.test(1)      // returns true if bit 1 is set, does index bounds checking on n
b.size()       // size of array
b.any()        // returns true if any bit is set to true
b.none()       // returns true if no bits are set to true
b.set()        // sets all to true
b.set(1,true)  // set bit 1 to true
b.set(1)       // set bit 1 to true
b.reset()      // sets all to false
b.reset(1)     // set bit 1 to false
b.flip()       // flips all bits to opposite value
b.flip(1)      // flips bit 1 to opposite
b.count()      // returns number of true bits
b.to_ulong()   // converts bitset to unsigned long
b.to_string()  // returns a string representation (1101101)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITERATOR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iterator>

/*************************************************************************************************************
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

===============================================================================================================
ITERATOR TYPES
===============================================================================================================

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

===============================================================================================================
ITERATOR INVALIDATION
===============================================================================================================

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
**************************************************************************************************************/

std::end(c) // iterator pointing at one past end of container object
std::begin(c) // iterator pointing at beginning of container object
std::advance(itr, n) // advance iterator by n; Random access iterators use +=/-= else ++/-- 
std::distance(itr1, itr2) // returns int distance between 2 iterators, it2 must be after it1

//ITERATING OVER CONTAINER
auto endItr = c.end(); // to prevent recomputing each iteration
for (auto itr = c.begin(); itr != c; ++itr) {}

auto endItr = c.rend(); // to prevent recomputing each iteration
for (auto itr = c.rbegin(); itr != endItr; ++itr) {}

for (auto& item : c) {}
for (const auto& [key, value] : c) {}

//===============================================================================================================
// CONTAINER ITERATORS
//===============================================================================================================

// ITERATOR
vector<int>::iterator itr;
*itr // dereferencing gives the value of an element pointed to

// REVERSE ITERATOR
vector<int>::reverse_iterator rItr;
rItr.base() // returns normal iterator pointing to element one after rIt
*rItr // dereferencing gives the value of an element one before the pointed to element
O.erase(++rItr).base()); // erase element rIt holds

// CONST ITERATOR
vector<int>::const_iterator cItr;

// CONVERTING CONST ITR TO ITR
vector<int>::iterator itr(myVec.begin());
std::advance(itr, std::distance<vector<int>::const_iterator>(itr, cItr)); // move itr to where const itr is

//===============================================================================================================
// INSERT ITERATORS
//===============================================================================================================

// Algorithms that require a range to copy can insert instead
transform(vec.begin(), vec.end(), back_inserter(vec), doCopyLam); // insert at end rather than copying
transform(vec.begin(), vec.end(), front_inserter(vec), doCopyLam); // insert at front rather than copying
transform(vec.begin(), vec.end(), inserter(vec, vec.begin() + vec.size() / 2), doCopyLam); // insert in middle

//BACK INSERT ITERATOR
//inserts at back of container
back_insert_iterator<vector<int>> backIter; 
back_inserter(vec) // creates back_insert_iterator

//FRONT INSERT ITERATOR
//inserts at front of container
front_insert_iterator<vector<int>> frontIter; 
front_inserter(vec) // creates front_insert_iterator

//INSERT ITERATOR
//inserts at given position
insert_iterator<vector<int>> insertIter;
inserter(vec, vec.begin()) // creates insert_iterator

//===============================================================================================================
// STREAM ITERATORS
//===============================================================================================================

//OSTREAM ITERATOR
ostream_iterator<T,char> ostreamItr(cout, " "); //stream, seperator between each item
*out_iter++ = 15;  //works like cout << 15 << " ";
std::copy(vec.begin(), vec.end(), ostreamItr);
std::copy(vec.begin(), vec.end(), ostream_iterator<T>(cout, " "));

//ISTREAM ITERATOR
ifstream myFile("myFile.txt");
myFile.unset(ios::skipws); //disable skipping of whitespace (uses operator<< which skips by default)
std::string myString((istream_iterator<char>(myFile)), istream_iterator<char>());
