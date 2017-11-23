///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//STRING
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>

string str; //initialises to ""
string str("str"); 
string str(str2, 1, n) //from index 1 to 1+n, or until end. N default param is end (npos)
string str(n,'a'); //fill n times with 'a'
string str(char_array, n); //fill with char_array of n length
wstring wstr(L"wstr");
auto str = "str"s; //creates a std::string rather than literal string

str[0]
string::npos //maximum allowable size for string; maximum value of unsigned int
str.empty() //returns true/false if empty (faster than size)
str.size() //number of elements
str.length() //same as str.size()
str.replace(4, n, "hello") //replace over index 4 for n characteres
str.c_str() //returns pointer to cstring with strings contents
str.substr(2, n) //creates substring from index 2 with n characters
str.clear() //removes all from container
str.back() //returns reference to last element
str.front() //returns reference to first element
str.swap(str2) //swaps two of SAME containers around
str.erase(Begin(str),End(str)) //Erases the elements in the range
str.erase(it) //Erases at particular place
str.max_size() //returns maximum possible size
str.resize(x) //resizes container for x units
str.capacity() //returns number of elements vector can contain before more memory needed
str.reserve(100) //reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
str.insert(4, "hello") //inserts before index 4
str.insert(4, "hello", 1, n) //inserts 'ello' before index 4 where n is length of substring
str.insert(4, n,'a') //Inserts n references of a before index 4
str.insert(str.begin(), 'a') //Inserts a before iterator
str.insert(str.begin(), n, 'a') //Inserts n references of a before iterator
str.insert(str.begin(), str2.begin(), str2.end()) //Insert copies of elements in the range before iterator

// FIND METHODS
// returns index int or if not found
str.find(chararray, 2) //starts at position 2 and searches for the substring (cstring/string)
str.find("hello", 2)  // returning first occurance's index or string::npos
str.rfind() //finds last occurance of substring
str.find_first_of("hello") //returns index of first occurance of ANY character in substring
str.find_last_of("hello") //returns index of last occurance of ANY character in substring
str.find_first_not_of("hello") //returns index of first occurance of ANY character NOT in substring
str.find_last_not_of("hello") //returns index of last occurance of ANY character NOT in substring

// CONVERTING WSTRING AND STRING
string str(wstr.begin(),  wstr.end());
wstring wstr(str.begin(), str.end());
str = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wstr);
wstr = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);

// ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ARRAY
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <array>

std::array<int, 40> myArray; //fixed, continuous array stored on stack, n must be const

myArray[i]
myArray.assign(0) // assigns array with value
myArray.fill(0)   // fills array with value
myArray.empty()   // returns true/false if empty (faster than size)
myArray.size()    // number of elements
myArray.data()    // returns pointer to internal data
myArray.clear()   // clears array
myArray.front()   // get first element
myArray.back()    // get last element

//ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VECTOR
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>

vector<int> V;
vector<int> V(size);
vector<int> V(O.begin(), O.end());
vector<int> V = { 1 };
vector<int> V{ 1 };

V[i]                     // No bounds checking
V.at(0)                  // Bounds checking
V.empty()                // returns true/false if empty (faster than size)
V.size()                 // number of elements
V.assign(n, value)       // assigns reference to value over first n elements
V.clear()                // removes all from container
V.back()                 // returns reference to last element
V.front()                // returns reference to first element
V.swap(V2)               // swaps two of SAME containers around
V.erase(itr1, itr2)      // Erases the elements in the range
V.erase(itr)             // Erases at particular place
V.max_size()             // returns maximum possible size
V.resize(x)              // resizes container for x units
V.capacity()             // returns number of elements vector can contain before more memory needed
V.reserve(100)           // reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
V.pop_back()             // Deletes the element at the end of a list.
V.push_back(x)           // Adds an element to the end of a list.
V.emplace_back(2.0, 1)   // constructs directly into container; takes constructor arguments for type inside container
V.insert(Begin(V),t)                   // Inserts a reference of t before iterator
V.insert(Begin(V),n,t)                 // Inserts n references of t before iterator
V.insert(Begin(V),V2.begin(),V2.end()) // Insert copies of elements in the range before iterator

//ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DEQUE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <deque> 

deque<int> D;
deque<int> D;
deque<int> D(size);
deque<int> D(O.begin(), O.end());
deque<int> D = { 1 };
deque<int> D{ 1 };

D[i]
D.empty()           // returns true/false if empty (faster than size)
D.size()            // number of elements
D.pop_back()        // Deletes the element at the end of a list.
D.pop_front()       // Deletes the element at the beginning of a list.
D.push_back(x)      // Adds an element to the end of a list.
D.push_front(x)     // Adds an element to the beginning of a list.
D.assign(n,value)   // assigns reference to value over first n elements
D.clear()           // removes all from container
D.back()            // returns reference to last element
D.front()           // returns reference to first element
D.swap(D2)          // swaps two of SAME containers around
D.erase(itr1, itr2) // Erases the elements in the range
D.erase(itr)        // Erases at particular place
D.max_size()        // returns maximum possible size
D.resize(x)         // resizes container for x units
D.capacity()        // returns number of elements vector can contain before more memory needed
D.reserve(100)      // reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)

D.insert(D.begin(),t)                   // Inserts a reference of t before iterator
D.insert(D.begin(),n,t)                 // Inserts n references of t before iterator
D.insert(D.begin(),D2.begin(),D2.end()) // Insert copies of elements in the range before iterator

//ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LIST
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <list> 
#include <forward_list>

list<int> L;
forward_list<int> FL; // only links forward, no reverse iteration

L.empty()                // returns true/false if empty (faster than size)
L.pop_front()            // Deletes the element at the beginning of a list.
L.push_front(x)          // Adds an element to the beginning of a list.
L.reverse()              // Reverses the order in which the elements occur in a list.
L.remove(x)              // Removes all elements with value x from list
L.remove_if(boolLambda)  // Removes all elements returning true from lamda
L.sort()                 // sorts using < in ascending order  speed: L(N*logN)  stable sort
L.merge(one)             // merges one into two, leaving one empty  assumes both are sorted
L.splice(L.begin(), L2)  // inserts L2 in front of L.begin(), leaving one empty
L.unique()               // removes duplicate values in list  assumes list is sorted
L.clear()                // removes all from container
L.front()                // returns reference to first element
L.swap(L2)               // swaps two of SAME containers around
L.erase(itr1, itr2)      // Erases the elements in the range  erase_after() for forward list
L.erase(itr)             // Erases at particular place  erase_after() for forward list
L.max_size()             // returns maximum possible size
L.resize(x)              // resizes container for x units

//LIST SPECIFIC METHODS
L.size()  //number of elements
L.pop_back() //Deletes the element at the end of a list.
L.push_back(x) //Adds an element to the end of a list.
L.back()  //returns reference to last element
L.capacity() //returns number of elements vector can contain before more memory needed
L.emplace_back(obj, 0, "arg2") // Creates element at end and calls constructor with given arguments (varadic)
L.emplace_front(obj, 0, "arg2") // Creates element at front and calls constructor with given arguments (varadic)
L.emplace(itr, obj, 0, "arg2") // Creates element before itr and calls constructor with given arguments (varadic)
L.insert(L.begin(),t) // Inserts a reference of t before iterator
L.insert(L.begin(),n,t) // Inserts n references of t before iterator 
L.insert(itr,L2.begin(),L2.end()) // Insert copies of elements in the range before itr

//FORWARD LIST SPECIFIC METHODS
L.emplace_after(itr, obj, 0, "arg2") // Creates element at after itr and calls constructor with given arguments (varadic)
L.insert_after(L.begin(),t) // Inserts a reference of t after iterator 
L.insert_after(L.begin(),n,t) // Inserts n references of t after iterator
L.insert_after(itr,L2.begin(),L2.end()) // Insert copies of elements in the range after itr

//ITERATORS
begin()   end()   cbegin()   cend()  // Both lists
rbegin()  rend()  crbegin()  crend() // List only

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <map> 
#include <unordered_map>

// ORDERED MAP
// Every entry is sorted according to a compare function std::function<bool(const T&, const T&)>
std::map<Key, T> MyMap;
std::map<key, T, std::function<bool(const T&, const T&)>> myMap(comparisonFn);
std::map<Key, T, comparisonFunctor> MyMap;
std::multi_map<Key, T> MyMultiMap // can have multiple entries for the one key
std::map<Key, T>::iterator itr;   // iterator for map

// UNORDERED MAP (HASH TABLE)
// Organized into buckets depending on hash values to allow for fast access using keys
std::unordered_map<KeyType, ObjType> hashMap;
std::unordered_multimap<KeyType, ObjType> hashMap;

// VALUE TYPE
// const Key is important when iterating
// If std::pair<Key,T> used will create temporary copy of pair
std::map<Key, T>::value_type; /*or*/ std::pair<const Key, T>
for (const std::pair<const Key, T>& p : M){}

// METHODS
M.empty();      // returns true/false if empty (faster than size)
M.size();       // number of element pairs
M.count("Key")  // returns number of items that have that key
M.erase("Key")  // removes element with matching key, returns number of elements removed or 0 if none
M.find("Key")   // returns MyMap.end() if not found or iterator MyMap::iterator if found
M.at("Key")     // returns object at key or throws out_of_range exception if doesn't exist
M["Key"]        // returns object if key exists or creates through default contructor if doesn't exist 

// INSERTING ITEMS
// More effecient to use insert; operator[] creates default object then assigns if object doesn't exist 
M.insert(MyMap::value_type("Key",2.0)); // value_type is typedef for maps pair
M["Key"] = 2.0; // Adds entry if key doesn't exist otherwise overwrites

// ITERATING
// value_type is std::pair<const KeyType, ObjType>
std::for_each(M.begin(), M.end(), [&](const MyMap::value_type& item){ item.second->MyMethod(); });

//ITERATORS
begin()   end()   cbegin()   cend() 
rbegin()  rend()  crbegin()  crend()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SET
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <set> 
#include <unordered_set>

set<int> S;

S.empty();   // returns true/false if empty (faster than size)
S.size();    // number of elements
S.clear();   // clear the container
S.insert(x); // Returns pair: itr to the inserted item or item that prevented insertion / bool if successful
S.find(x);   // return iterator to element position or S.end() if not found
S.erase(x);  // erase element
S.erase(itr) // erase element at iterator 

//ITERATORS
begin()   end()   cbegin()   cend()
rbegin()  rend()  crbegin()  crend()

//UNORDERED SET (HASH TABLE)
//Organized into buckets depending on hash values to allow for fast access using keys
std::unordered_set<int> hashSet;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QUEUE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <queue>

queue<int> Q; //FIFO queue
priority_queue<int> pQ; //largest is automatically sorted to front of queue using heap sort

Q.empty()   // returns true/false if empty (faster than size)
Q.size()    // number of elements
Q.front()   // returns reference to element at front of queue
Q.back()    // returns reference to element at back of the queue
Q.push(x)   // inserts x at back
Q.pop()     // removes element at front

// Clearing a queue
std::queue<int> empty; 
std::swap(Q, empty);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//STACK
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stack> 

stack<int> S; //LIFO stack

S.empty()   // returns true/false if empty (faster than size)
S.size()    // number of elements
S.top()     // returns reference to element at top of stack
S.push(x)   // inserts type int to top of the stack
S.pop()     // removes the element at top of stack

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BITSET
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <bitset>

bitset<n> mybits;          // Fills container with n zeroed bits, n must be constant, zero-based index
bitset<n> mybits(value)    // Takes integer type and flips required bits
bitset<n> mybits(0x080)    // Takes hex value and flips required bits
bitset<n> mybits("110101") // Takes binary string and flips requied bits starting from bit 0

mybits[1]           // access bit
mybits.test(1)      // returns true if bit 1 is set, does index bounds checking on n
mybits.size()       // size of array
mybits.any()        // returns true if any bit is set to true
mybits.none()       // returns true if no bits are set to true
mybits.set()        // sets all to true
mybits.set(1,true)  // set bit 1 to true
myBits.set(1)       // set bit 1 to true
mybits.reset()      // sets all to false
mybits.reset(1)     // set bit 1 to false
mybits.flip()       // flips all bits to opposite value
mybits.flip(1)      // flips bit 1 to opposite
mybits.count()      // returns number of true bits
mybits.to_ulong()   // converts bitset to unsigned long
mybits.to_string()  // returns a string representation (1101101)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MULTIPLE TYPED CONTAINERS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//TUPLES
#include <tuple>
std::tuple<int, double, std::string> myTuple = std::make_tuple(0,2.0,"hello");
auto value = std::get<0>(myTuple); //Get value at index 0, must be const index
std::tie(myInt, myDouble, std::ignore) = myTuple; //copies from tuple into variables 
std::ignore //ignore copying of variable

//PAIRS
std::pair<int, double> myPair = std::make_pair(1,2.0);
myPair.first / myPair.second //access members of pair

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ITERATOR
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iterator>

std::end(O) //iterator pointing at one past end of container object
std::begin(O) //iterator pointing at beginning of container object
std::advance(itr, n) //advance iterator by n; Random access iterators use +=/-= else ++/-- 
std::distance(itr1, itr2) //returns int distance between 2 iterators, it2 must be after it1

//ITERATING OVER CONTAINER
auto endItr = myVec.end(); // to prevent recomputing each iteration
for (vector<int>::iterator itr = myVec.begin(); itr != endItr; ++itr)
    itr->myMethod();

auto endItr = myVec.rend(); // to prevent recomputing each iteration
for (vector<int>::reverse_iterator itr = myVec.rbegin(); itr = endItr; ++itr)
    itr->myMethod();

for (auto& item : myVec)
    int x = item;

//================================================================================================================
//CONTAINER ITERATORS
//================================================================================================================

//ITERATOR
vector<int>::iterator itr;
*itr //dereferencing gives the value of an element pointed to

//REVERSE ITERATOR
vector<int>::reverse_iterator rItr;
rItr.base() //returns normal iterator pointing to element one after rIt
*rItr //dereferencing gives the value of an element one before the pointed to element
O.erase(++rItr).base()); //erase element rIt holds

//CONST ITERATOR
vector<int>::const_iterator cItr;

//CONVERTING CONST ITR TO ITR
vector<int>::iterator itr(myVec.begin());
std::advance(itr, std::distance<vector<int>::const_iterator>(itr, cItr)); //move itr to where const itr is

//================================================================================================================
//INSERT ITERATORS
//================================================================================================================

//Algorithms that require a range to copy can insert instead
transform(S, E, back_inserter(myCon), doCopyLam); //insert at end rather than copying
transform(S, E, front_inserter(myCon), doCopyLam); //insert at front rather than copying
transform(S, E, inserter(myCon, myCon.begin()+myCon.size()/2), doCopyLam); //insert in middle

//BACK INSERT ITERATOR
//inserts at back of container
back_insert_iterator<vector<int>> backIter; 
back_inserter(myContainer) //creates back_insert_iterator

//FRONT INSERT ITERATOR
//inserts at front of container
front_insert_iterator<vector<int>> frontIter; 
front_inserter(myContainer) //creates front_insert_iterator

//INSERT ITERATOR
//inserts at given position
insert_iterator<vector<int>> insertIter;
inserter(myContainer, myContainer.begin()) //creates insert_iterator

//================================================================================================================
//STREAM ITERATORS
//================================================================================================================

//OSTREAM ITERATOR
ostream_iterator<T,char> ostreamItr(cout, " "); //stream, seperator between each item
*out_iter++ = 15;  //works like cout << 15 << " ";
std::copy(object.begin(), object.end(), ostreamItr);
std::copy(object.begin(), object.end(), ostream_iterator<T>(cout, " "));

//ISTREAM ITERATOR
ifstream myFile("myFile.txt");
myFile.unset(ios::skipws); //disable skipping of whitespace (uses operator<< which skips by default)
std::string myString((istream_iterator<char>(myFile)), istream_iterator<char>());

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

auto doCopyLam = [](MyClass o) -> MyClass { o.SomeMethod(); return o; };
auto doLam = [](const std::shared_ptr<MyClass>& ptr) { ptr->NonConstMethod(); };
auto boolLam = [](const MyClass& o) ->bool { return o.Exists(); };
auto equalLam = [](const MyClass& o1, const MyClass& o2) -> bool { return o1 == o2; };
auto sortLam = [](const MyClass& o1, const MyClass& o2) -> bool { return o1.myInt < o2.myInt; };
auto createLam = []() -> int { return rand()%10; }
struct DelFunctor { template<typename T> void operator()(const T* ptr) const { delete ptr; ptr = nullptr; } };

// ACCEPTED FUNCTION OBJECTS
struct myFunctor { void operator()(int i){} };   // ..., myFunctor);
std::plus<T> stdFunctor;                         // ..., stdFunctor); or ..., std::plus<T>());
auto myLambda = [](int i) {};                    // ..., myLambda);
inline void myFunction(const MyClass& o){}       // ..., myFunction);
class MyClass { static void MyStatic(int i){} }; // ..., MyClass::MyStatic);
class MyClass { void MyMember(int i){} };        // ..., std::bind(&MyClass::MyMember, &obj, _1));

// OPERATION FUNCTORS
plus<T> op          // (const T& x, const T& y) const {return x+y;}
minus<T> op         // (const T& x, const T& y) const {return x-y;}
divides<T> op       // (const T& x, const T& y) const {return x/y;}
multiplies<T> op    // (const T& x, const T& y) const {return x*y;}
not_equal_to<T> op  // (const T& x, const T& y) const {return x!=y;}
modulus<T> op       // (const T& x, const T& y) const {return x%y;}
less<T> op          // (const T& x, const T& y) const {return x<y;}    
less_equal<T> op    // (const T& x, const T& y) const {return x<=y;}    
greater_equal<T> op // (const T& x, const T& y) const {return x>=y;}
greater<T> op       // (const T& x, const T& y) const {return x>y;}
equal_to<T> op      // (const T& x, const T& y) const {return x==y;}

//================================================================================================================
//ITERATIVE ALGORITHMS
//================================================================================================================

//ITERATIVE
for_each(S, E, doLam) //Non-modifying; Sends const dereferenced object into lambda for each element
for_each(S, E, DelFunctor); //Non-modifying; fast memory deletion in array
transform(S, E, S2, doCopyLam) //Modifying; each element calls lambda then is copied to second container
transform(myString.begin(), myString.end(), myString.begin(), toupper); //Modifying; can be copied in place
transform(S, E, back_inserter(myCon), doCopyLam); //insert at end rather than copying

//STREAMING
copy(S, E, ostream_iterator<T>(cout, " ")); //copy container into output stream with space between elements

//NUMERIC (in #include <numeric>)
accumulate(S, E, initial) //returns initial+values over whole range 
accumulate(S, E, initial, std::minus<T>()) //returns initial-values over whole range
iota(S, E, value) //for each element: assign value then increment value (value++)
partial_sum(S1, E1, S2) //for each C2 element add all previous values in C1: S2[i] = S1[i] + S1[i-1] + ... + S1[0]
inner_product(s1, E1, S2, value) //multiplies elements and accumulates: value += S1[i] * S2[i], returns final value
adjacent_difference(S1, E1, S2) //for each C2 element: S2[i] = S1[i] - S1[i-1] with S2[0] = S1[0]
adjacent_difference(S1, E1, S2, std::plus<T>()) //for each C2 element: S2[i] = S1[i] + S1[i-1] with S2[0] = S1[0]

//FILLING
fill(S, E, "A") //fill range with reference of value A
fill_n(S, n, "A") //fill from S to n elements with reference of value A
generate(S, E, createLam) //calls lamda and assigns return for each element
generate_n(S, n, createLam) //calls lamda and assigns return for each element from S to n elements

//================================================================================================================
//SEARCHING ALGORITHMS
//================================================================================================================

//ELEMENT EXISTANCE
count(S, E, myObj) //returns int on number of items of myObj in container
count_if(S, E, boolLam) //returns number of obj that lamda returns true
binary_search(S, E, myObj, equalLam) //returns true if lamda is true, requires sorting

//FIND OBJECT
//If not found, returns E
find(S, E, myObj, equalLam) //Returns iterator to first instance of element
find_if(S, E, boolLam) //Returns iterator to first element in range that lambda returns true
find_if_not(S, E, boolLam) //Returns iterator to first element in range that lambda returns false
lower_bound(S, E, myObj, sortLam) //returns first value found >= myObj, requires sorting
upper_bound(S, E, myObj, sortLam) //returns first value found > myObj, requires sorting

//FIND MULTIPLE OBJECTS
search(S, E, S2, E2, equalLam) //Search for range 2 in range 1, returns iterator to start of sequence found or E if none
find_end(S, E, S2, E2, equalLam) //Same as search but back to front, returns S if none found
find_first_of(S, E, S2, E2, equalLam) //Returns iterator to first element that matches any element in range 2 else returns end
search_n(S, E, n, myObj, equalLam) //Searches for obj repeating n times, returns iterator to start of sequence or E if none
adjacent_find(S, E, equalLam) //Returns iterator to first element that is repeated consecutivly or E if not found
equal_range(S, E, myObj, equalLam) //Returns pair of itrs for bounds of subrange with values that return true for equalLam

//MIN-MAX
min(T, T) //returns minimum of two values
max(T, T) //returns maximum of two values
minmax(T, T) //returns std::pair(min,max) where .first is min and .second is max
min_element(S, E, sortLam) //returns minimum element between range
max_element(S, E, sortLam) //returns maximum element between

//CONTAINER STATE
all_of(S, E, boolLam) //If all objs return true then returns true, else false; If no objs in range returns true
any_of(S, E, boolLam) //If any obj is true returns true, else false; If no objs in range returns false
none_of(S, E, boolLam) //If all objs return false returns true, else false; If no objs in range returns true

//CONTAINER COMPARISON
mismatch(S, E, S2, equalLam) //returns std::pair of iterators to first elements that don't match between range 1 and 2
equal(S, E, S2, equalLam) //returns true if both ranges are equal to each other including ordering
is_permutation(S, E, S2, equalLam) //returns true if both ranges are equal to each other excluding ordering
includes(S, E, S2, E2) //returns true if range 2 is in range 1; both ranges must be sorted in ascending order

//================================================================================================================
//MOVING ALGORITHMS
//================================================================================================================

//COPYING
copy(S, E, S2) //copies O into O2, returns iterator to E2
copy(S, E, back_inserter(O2)) //inserts O into O2, returns iterator to E2
copy_n(S, n, S2) //copies from O to n elements into O2, returns iterator to E2, does nothing if n <= 0
copy_if(S, E, S2, boolLam) //only copies element if lamda is true, returns iterator to E2
copy_if(S, E, back_inserter(O2), boolLam) //inserts into C2 rather than copies, returns iterator to E2
copy_backward(S, E, E2) //copies O into O2 backwards, returns iterator to S2

//MOVING
//Requires move constructor/assignment operator
move(S, E, S2) //moves from O to O2 leaving O in undefined, valid state, returns iterator to E2
move_backward(S, E, E2) //moves from O to O2 leaving O in undefined, valid state, returns iterator to S2

//SWAP
//Also swaps both containers iterators, pointers, references to other container
swap(T, T) //swap any type object with the other
swap_ranges(S, E, S2) //exchange values of two ranges, returns iterato to E2
iter_swap(it1, it2) //swap what each iterator points to but not underlying objects

//REPLACING
replace(S, E, 'A', 'B') //replaces over range any values that are A with value B
replace_if(S, E, boolLam, 'A') //replaces element with A if lambda returns true
replace_copy(S, E, S2, 'A', 'B') //copies S to S2 and replaces in range 2 any A with B
replace_copy_if(S, E, S2, boolLam, 'A') //copies S to S2, replaces with A if lambda returns true in range 2 

//MERGING
//Only used on sorted ranges, all elements remain in sorted ascending order
merge(S, E, S2, E2, std::back_inserter(S3)) //copies 1 and 2 into 3
set_union(S, E, S2, E2, std::back_inserter(S3)) //copies 1 and 2 into 3 and removes duplicates
set_intersection(S, E, S2, E2, std::back_inserter(S3)) //copies elements in 1 that are also in 2 into 3
set_difference(S, E, S2, E2, std::back_inserter(S3)) //copies elements in 1 that are not in 2 into 3
set_symmetric_difference(S, E, S2, E2, std::back_inserter(S3)) //copies elements in 1 that don't exist in 2 and vice versa into 3

//================================================================================================================
//SORTING ALGORITHMS
//================================================================================================================

//CHANGE ORDER
reverse(S, E) //reverses order of elements
reverse_copy(S, E, S2) //copies into 2 with the reverse order, returns iterator E2
rotate(A, B, C) //ranges B-C and A-B swap places. B needs to be between A and C.
rotate_copy(A, B, C, S2) //Copies into 2 with ranges B-C and A-B swapped. B needs to be between A and C.
random_shuffle(S, E) //randomly shuffles elements

//PARTITIONS
//Splits container to those returning true and those returning false
is_partitioned(S, E, boolLam) //returns true if all elements returning true occur before those returning false
partition(S, E, boolLam) //splits the container to returning true->returning false; returns it to first returning false
stable_partition(S, E, boolLam) //same as parition but keeps original ordering between both partitions
partition_copy(S, E, S2, S3, boolLam) //those returning true copied to 2, those returning false copied to 3
partition_point(S, E, boolLam) //requires container to be partitioned; returns iterator to first element returning false

//SORTING
//requires random access (can't be used on lists)
sort(S, E, sortLam) //sorts container in ascending order, without lamda uses operator<
sort(S, E, std::greater<double>()) //using inbuilt functor
stable_sort(S, E, sortLam) //sorts container in ascending order, equal elements preserve original order
partial_sort(S, M, E, sortLam) //smallest elements from S-E are put in ascending order from S-M, M-E becomes unordered
partial_sort_copy(S, E, S2, E2, sortLam) //copies range to 2 and sorts in ascending order
is_sorted(S, E, sortLam) //returns false if not sorted in ascending order, stop when mismatching pair found
is_sorted_until(S, E, sortLam) //Returns itr to first element which does not follow an ascending order else returns E
nth_element(S, M, E, sortLam) //puts M at the position it'd be if range was sorted, elements before are less/after are more (in any order)

//================================================================================================================
//REMOVING ALGORITHMS
//================================================================================================================

//CLEARING CONTAINERS
//Reducing capactiy not needed for list, set, map as they don't reserve space
obj.clear();                         // Make obj empty with current capacity
std::vector<MyClass>().swap(obj);    // Make obj empty with minimal capacity
std::vector<MyClass>(obj).swap(obj); // Make obj with minimal capacity

//SEPERATE WANTED/UNWANTED ITEMS
//Only on sequence containers, requires Erase remove idiom to actually remove
//Doesn't remove anything, only moves wanted items to start of range, overwriting values if needed
remove(S, E,"A") //moves all items that aren't A to front of range; returns iterator to end of this range
remove_if(S, E, boolLam) ///moves all items that return false to front of range; returns iterator to end of this range
unique(S, E) //moves all unique items to front of range; returns iterator to end of this range, requires sorting

//REMOVE WITH COPY
unique_copy(S, E, S2) //copies into 2 and removes double values, returns iterator in 2 to new end
remove_copy(S, E, S2, "A") //copies to range 2 with all instances of A removed, return iterator is from 2
remove_copy_if(S, E, S2, boolLam) //copies to range 2 with elements returning true removed, return it is from 2

//REMOVING FROM LIST
L.remove("A"); //more effecient to use member versions
L.remove_if(boolLam);
L.unique("A");

//REMOVING FROM VECTOR/DEQUE/STRING
O.erase(remove(O.begin(), O.end(), "A"), O.end()); //Erase-remove idiom
O.erase(remove_if(S, E, boolLam), O.end());
O.erase(unique(S, E), O.end());
for(deque<T>::iterator it = O.begin(); it != O.end(); ) //alternative remove_if
{
    if(boolLam()){ it = O.erase(it); }
    else { ++it; }
}

//REMOVING FROM ASSOCIATIVE CONTAINERS
C.erase("A"); //remove all with key for associative containers
for(map<T>::iterator it = O.begin(); it != O.end(); ) //remove_if
{
    if(boolLam()){ O.erase(it++); }
    else { ++it; }
}

//================================================================================================================
//CONVERSION ALGORITHMS
//================================================================================================================

//CONVERT TO C-STYLE CONTAINERS
//modifying c-style version cannot change number of elements
//for non-continuous containers, need to copy to continuous
&myVector[0] //pointer to first member in vector; memory in continuous block
myString.c_str() //string in c-style, can't use &myString[0] as string may not be in continuous block

//CONVERT TO HEAP
make_heap(S, E, sortLam) //change range into a heap structure
sort_heap(S, E, sortLam) //sorts heap into ascending order; doing this loses properties as a heap
is_heap(S, E, sortLam) //returns true if range is a heap
push_heap(S, E) //push any values not already in heap structure in range to the heap
pop_heap(S, E) //pop highest value on heap off heap (doesn't remove from container though)
myContainer.front() //get highest value on the heap
