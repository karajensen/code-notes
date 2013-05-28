///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm> 
///////////////////////////////////////////////////////////////////////////////////////////////////////
//• Equality lambda can be omitted as operator== can be used
//• Preferable to use container's equivalent method for stability except for Begin(O)/End(O)
//• All ranges are [Start, End) with End non-inclusive

auto doCopyLam = [](MyClass o) -> MyClass { o.SomeMethod(); return o; };
auto doLam = [](const MyClass& o) { o.SomeMethod(); };
auto boolLam = [](const MyClass& o) ->bool { return o.Exists(); };
auto equalLam = [](const MyClass& o1, const MyClass& o2) ->bool { return !(o1 == o2); }; //equal values should always return false
auto sortLam = [](const MyClass& o1, const MyClass& o2) -> bool { return o1.myInt < o2.myInt; }; //equal values should always return false
auto createLam = []() -> int { return rand()%10; }
struct DelFunctor { template<typename T> void operator()(const T* ptr) const { delete ptr; ptr = nullptr; } };

//STATE
all_of(S, E, boolLam) //If all objs return true then returns true, else false; If no objs in range returns true
any_of(S, E, boolLam) //If any obj is true returns true, else false; If no objs in range returns false
none_of(S, E, boolLam) //If all objs return false returns true, else false; If no objs in range returns true

//ITERATIVE
for_each(S, E, doLam) //Non-modifying; Sends const dereferenced object into lambda for each element
for_each(S, E, DelFunctor); //Non-modifying; fast memory deletion in array
transform(S, E, S2, doCopyLam) //Modifying; each element calls lambda then is copied to second container
transform(myString.begin(), myString.end(), myString.begin(), toupper); //Modifying; can be copied in place

//ELEMENT EXISTANCE
count(S, E, myObj) //returns int on number of items of myObj in container
count_if(S, E, boolLam) //returns number of obj that lamda returns true
binary_search(S, E, myObj, equalLam) //Only used on sorted ranges, return true if myObj exists, effecient for random acess iterators

//FIND OBJECT
//If not found, returns E
find(S, E, myObj, equalLam) //Returns iterator to first instance of element
find_if(S, E, boolLam) //Returns iterator to first element in range that lambda returns true
find_if_not(S, E, boolLam) //Returns iterator to first element in range that lambda returns false+

//FIND MULTIPLE OBJECTS
search(S, E, S2, E2, equalLam) //Search for range 2 in range 1, returns iterator to start of sequence found or E if none
find_end(S, E, S2, E2, equalLam) //Same as search but back to front, returns S if none found
find_first_of(S, E, S2, E2, equalLam) //Returns iterator to first element that matches any element in range 2 else returns end
search_n(S, E, n, myObj, equalLam) //Searches for obj repeating n times, returns iterator to start of sequence or E if none
adjacent_find(S, E, equalLam) //Returns iterator to first element that is repeated consecutivly or E if not found

//MIN-MAX
min(T, T) //returns minimum of two values
max(T, T) //returns maximum of two values
minmax(T, T) //returns std::pair(min,max) where .first is min and .second is max
min_element(S, E) //returns minimum element between range
max_element(S, E) //returns maximum element between
accumulate(S, E, initial, op) //returns initial+values over whole range; BinaryOperation op defaults to + and is optional

//CONTAINER COMPARISON
mismatch(S, E, S2, equalLam) //returns std::pair of iterators to first elements that don't match between range 1 and 2
equal(S, E, S2, equalLam) //returns true if both ranges are equal to each other including ordering
is_permutation(S, E, S2, equalLam) //returns true if both ranges are equal to each other excluding ordering
includes(S, E, S2, E2) //returns true if range 2 is in range 1; both ranges must be sorted in ascending order

//FILLING
fill(S, E, "A") //fill range with reference of value A
fill_n(S, n, "A") //fill from S to n elements with reference of value A
generate(S, E, createLam) //calls lamda and assigns return for each element
generate_n(S, n, createLam) //calls lamda and assigns return for each element from S to n elements

//COPYING
copy(S, E, S2) //copies O into O2, returns iterator to E2
copy_n(S, n, S2) //copies from O to n elements into O2, returns iterator to E2, does nothing if n <= 0
copy_if(S, E, S2, boolLam) //only copies element if lamda is true
copy_backward(S, E, E2) //copies O into O2 backwards, returns iterator to S2; both containers end with same ordering

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
replace(S, E, "A", "B") //replaces over range any values that are A with value B
replace_if(S, E, boolLam, "A") //replaces element with A if lambda returns true
replace_copy(S, E, S2, "A", "B") //copies S to S2 and replaces in range 2 any A with B
replace_copy_if(S, E, S2, boolLam, "A") //copies S to S2, replaces with A if lambda returns true in range 2 

//CHANGE ORDER
reverse(S, E) //reverses order of elements
reverse_copy(S, E, S2) //copies into 2 with the reverse order, returns iterator E2
rotate(S, M, E) //shifts so M becomes start of container, S loops around to other end
rotate_copy(S, M, E, S2) //copies into 2 and shifts so M becomes start of container
random_shuffle(S, E) //randomly shuffles elements

//PARTITIONS
//Splits container to those returning true and those returning false
is_partitioned(S, E, boolLam) //returns true if all elements returning true occur before those returning false
partition(S, E, boolLam) //splits the container to returning true->returning false; returns it to first returning false
stable_partition(S, E, boolLam) //same as parition but keeps original ordering between both partitions
partition_copy(S, E, S2, S3, boolLam) //those returning true copied to 2, those returning false copied to 3
partition_point(S, E, boolLam) //requires container to be partitioned; returns iterator to first element returning false

//SORTING
sort(S, E, sortLam) //sorts container in ascending order, without lamda uses operator<
stable_sort(S, E, sortLam) //sorts container in ascending order, equal elements preserve original order
partial_sort(S, M, E, sortLam) //smallest elements from S-E are put in ascending order from S-M, M-E becomes unordered
partial_sort_copy(S, E, S2, E2, sortLam) //copies range to 2 and sorts in ascending order
is_sorted(S, E, sortLam) //returns false if not sorted in ascending order, stop when mismatching pair found
is_sorted_until(S, E, sortLam) //Returns it to first element which does not follow an ascending order else returns E
nth_element(S, M, E, sortLam) //puts M at the position it'd be if sorted, all elements before are less, all after are more than it in any order

//MERGING
//Only used on sorted ranges, all elements remain in sorted ascending order
merge(S, E, S2, E2, S3) //copies 1 and 2 into 3
set_union(S, E, S2, E2, S3) //copies 1 and 2 into 3 and removes duplicates
set_intersection(S, E, S2, E2, S3) //copies elements in 1 that are also in 2 into 3
set_difference(S, E, S2, E2, S3) //copies elements in 1 that are not in 2 into 3
set_symmetric_difference(S, E, S2, E2, S3) //copies elements in 1 that don't exist in 2 and vice versa into 3

//SEPERATE WANTED/UNWANTED ITEMS
//Doesn't remove anything, only moves wanted items to start of range.
remove(S, E,"A") //moves all items that aren't A to front of range; returns iterator to end of this range [SEQUENCE]
remove_if(S, E, boolLam) ///moves all items that return false to front of range; returns iterator to end of this range [SEQUENCE]
unique(S, E) //moves all unique items to front of range; returns iterator to end of this range [SEQUENCE]

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

//ADDING ELEMENTS TO CONTAINERS
O.resize(MAX_ELEMENTS);
std::generate(O.begin(), O.end(), [&](){ return MyClassPtr(new MyClass()); });
std::generate(O.begin(), O.end(), [&](){ return MyClass(); });

//CONVERTING TO C-STYLE CONTAINERS
//modifying c-style version cannot change number of elements
//for non-continuous containers, need to copy to continuous
&myVector[0] //pointer to first member in vector; memory in continuous block
myString.c_str() //string in c-style, can't use &myString[0] as string may not be in continuous block

//TRIMMING CONTAINERS
//constructor creates temp container with mimimum capacity and swap this into old container
vector<MyClass>(O).swap(O)
string(str).swap(str)

///////////////////////////////////////////////////////////////////////////////////////////////////////
//MULTIPLE TYPED CONTAINERS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//TUPLES
std::tuple<int, double, std::string> myTuple = std::make_tuple(0,2.0,"hello");
auto value = std::get<0>(myTuple); //Get value at index 0, must be const index
std::tie(myInt, myDouble, std::ignore) = myTuple; //copies from tuple into variables 
std::ignore //ignore copying of variable

//PAIRS
std::pair<int, double> myPair = std::make_pair(1,2.0);
myPair.first / myPair.second //access members of pair

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
///////////////////////////////////////////////////////////////////////////////////////////////////////

string::npos //maximum allowable size for string; maximum value of unsigned int

string str; //initialises to ""
string str("one"); 
string str(n,'a'); //fill n times with 'a'
string str(char_array, n); //fill n times with char_array

str[0]
str.empty(); //returns true/false if empty (faster than size)
str.size(); //number of elements
str.length() //same as str.size()
str.insert(4, "hello") //inserts substring one before index 4
str.replace(4, 5, "hello") //replace over index 4 for 5 characteres
str.c_str(); //returns pointer to cstring with strings contents
str.clear(); //removes all from container
str.back(); //returns reference to last element
str.front(); //returns reference to first element
str.begin(); //iterator to start of array
str.end(); //iterator to one place past end of array
str.rbegin(); //iterator to last value
str.rend(); //iterator to one past first value
str.swap(str2); //swaps two of SAME containers around
str.erase(Begin(str),End(str)) //Erases the elements in the range
str.erase(it) //Erases at particular place
str.max_size() //returns maximum possible size
str.resize(x) //resizes container for x units
str.capacity() //returns number of elements vector can contain before more memory needed
str.reserve(100) //reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
str.insert(Begin(str),t) //Inserts a reference of t before iterator
str.insert(Begin(str),n,t) //Inserts n references of t before iterator
str.insert(Begin(str),str2.begin(),str2.end()) //Insert copies of elements in the range before iterator

//returns index int
str.find(chararray, 2)  //starts at position 2 and searches for the substring (cstring/string)
str.find("hello", 2)  // returning first occurance's index or string::npos
str.rfind() //finds last occurance of substring
str.find_first_of("hello") //returns index of first occurance of ANY character in substring
str.find_last_of("hello") //returns index of last occurance of ANY character in substring
str.find_first_not_of("hello") //returns index of first occurance of ANY character NOT in substring
str.find_last_not_of("hello") //returns index of last occurance of ANY character NOT in substring

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <array>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::array<int,40> myArray; //fixed array stored on stack

myArray[i]
myArray.Fill(0) //fills array with value
myArray.empty(); //returns true/false if empty (faster than size)
myArray.size(); //number of elements
myArray.clear();

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector> 
///////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> V;
vector<int,numOfSpots> V;   

V[i]
V.empty(); //returns true/false if empty (faster than size)
V.size(); //number of elements
V.pop_back() //Deletes the element at the end of a list.
V.push_back(x) //Adds an element to the end of a list.
V.assign(V.size(),value) //assigns reference to value over size of array
V.clear(); //removes all from container
V.back(); //returns reference to last element
V.front(); //returns reference to first element
V.begin(); //iterator to start of array
V.end(); //iterator to one place past end of array
V.rbegin(); //iterator to last value
V.rend(); //iterator to one past first value
V.swap(V2); //swaps two of SAME containers around
V.erase(Begin(V),End(V)) //Erases the elements in the range
V.erase(it) //Erases at particular place
V.max_size() //returns maximum possible size
V.resize(x) //resizes container for x units
V.capacity() //returns number of elements vector can contain before more memory needed
V.reserve(100) //reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
V.insert(Begin(V),t) //Inserts a reference of t before iterator
V.insert(Begin(V),n,t) //Inserts n references of t before iterator
V.insert(Begin(V),V2.begin(),V2.end()) //Insert copies of elements in the range before iterator

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <deque> 
///////////////////////////////////////////////////////////////////////////////////////////////////////

deque<int> D;

D[i]
D.empty(); //returns true/false if empty (faster than size)
D.size(); //number of elements
D.pop_back() //Deletes the element at the end of a list.
D.pop_front() //Deletes the element at the beginning of a list.
D.push_back(x) //Adds an element to the end of a list.
D.push_front(x) //Adds an element to the beginning of a list.
D.assign(D.size(),value) //assigns reference to value over size of array
D.clear(); //removes all from container
D.back(); //returns reference to last element
D.front(); //returns reference to first element
D.begin(); //iterator to start of array
D.end(); //iterator to one place past end of array
D.rbegin(); //iterator to last value
D.rend(); //iterator to one past first value
D.swap(D2); //swaps two of SAME containers around
D.erase(Begin(D),End(D)) //Erases the elements in the range
D.erase(it) //Erases at particular place
D.max_size() //returns maximum possible size
D.resize(x) //resizes container for x units
D.capacity() //returns number of elements vector can contain before more memory needed
D.reserve(100) //reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
D.insert(Begin(D),t) //Inserts a reference of t before iterator
D.insert(Begin(D),n,t) //Inserts n references of t before iterator
D.insert(Begin(D),D2.begin(),D2.end()) //Insert copies of elements in the range before iterator

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <list> 
///////////////////////////////////////////////////////////////////////////////////////////////////////

list<int> L1;

L.empty(); //returns true/false if empty (faster than size)
L.size(); //number of elements
L.pop_back() //Deletes the element at the end of a list.
L.pop_front() //Deletes the element at the beginning of a list.
L.push_back(x) //Adds an element to the end of a list.
L.push_front(x) //Adds an element to the beginning of a list.
L.reverse() //Reverses the order in which the elements occur in a list.
L.remove(x) //Removes all elements with value x from list
L.sort() //sorts using < in ascending order; speed: L(N*logN)
L.merge(one) //merges one into two, leaving one empty; assumes both are sorted
L.splice(L.begin(), L2) //inserts L2 in front of L.begin(), leaving one empty
L.unique() //removes duplicate values in list; assumes list is sorted
L.clear(); //removes all from container
L.back(); //returns reference to last element
L.front(); //returns reference to first element
L.begin(); //iterator to start of array
L.end(); //iterator to one place past end of array
L.rbegin(); //iterator to last value
L.rend(); //iterator to one past first value
L.swap(L2); //swaps two of SAME containers around
L.erase(Begin(L),End(L)) //Erases the elements in the range
L.erase(it) //Erases at particular place
L.max_size() //returns maximum possible size
L.resize(x) //resizes container for x units
L.capacity() //returns number of elements vector can contain before more memory needed
L.reserve(100) //reserves 100 spots (but doesn't create any objects) of vector's type (doesn't affect size)
L.insert(Begin(L),t) //Inserts a reference of t before iterator
L.insert(Begin(L),n,t) //Inserts n references of t before iterator
L.insert(Begin(L),L2.begin(),L2.end()) //Insert copies of elements in the range before iterator
L.emplace //Inserts an element constructed in place into a list at a specified position.
L.emplace_back //Adds an element constructed in place to the end of a list.
L.emplace_front //Adds an element constructed in place to the beginning of a list.

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <queue>
///////////////////////////////////////////////////////////////////////////////////////////////////////

queue<int> Q;
priority_queue<int> pQ; //largest is automatically sorted to head of queue using heap sort

Q.empty(); //returns true/false if empty (faster than size)
Q.size(); //number of elements
Q.front() //returns reference to element at front of queue
Q.back() //returns reference to element at back of the queue
Q.push(x) //inserts x at back
Q.pop() //removes element at front

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stack> 
///////////////////////////////////////////////////////////////////////////////////////////////////////

stack<int> S;
stack<int,vector<int>> S; //create the stack from the vector container (can be deque/list)

S.empty(); //returns true/false if empty (faster than size)
S.size(); //number of elements
S.top() //returns reference to element at top of stack
S.push(x) //inserts type int to top of the stack
S.pop() //removes the element at top of stack

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <set>
///////////////////////////////////////////////////////////////////////////////////////////////////////

set<string> S;
set<string> S(&Array[0], &Array[6]); // initialize set using a range from array

S.empty(); //returns true/false if empty (faster than size)
S.size(); //number of elements

insert_iterator<set<string>> ins(C, C.begin()) //use insert or output iterator
set_union(A.begin(), A.end(), B.begin(), B.end(), ins); //range for set A, set B and the output for resulting union
set_intersection(A.begin(), A.end(), B.begin(), B.end(), ins);
set_difference(A.begin(), A.end(), B.begin(), B.end(), ins);

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <map> 
#include <unordered_map>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//MAP: Auto sorted by key, fast for range iteration over elements
//UNORDERED MAP: Not sorted at all, fast for accessing individual elements by key
//Map iterators point to pairs where key is const to prevent breaking sorted order
//Internal pair has key non-const

typedef std::string KeyType;
typedef std::string ObjType;
typedef std::pair<const KeyType, ObjType> Pair; 
typedef std::map<KeyType, ObjType> MyMap;

MyMap M;

M.empty(); //returns true/false if empty (faster than size)
M.size(); //number of element pairs
M.count("MyKey") //returns number of items that have that key
M.find("MyKey") //returns MyMap.end() if not found or iterator MyMap::iterator if found

//MAP ITERATORS
MyMap::iterator it;
it->first //returns key
it->second //returns object

//INSERTING ITEMS
//More effecient to use insert; operator[] creates default object then assigns if object doesn't exist 
M.insert(MyMap::value_type("Key","Object")); //value_type is typedef for maps pair
M["MyKey"] = "MyObject"; // Adds entry if key doesn't exist otherwise overwrites

//MULTIMAP
std::multi_map<KeyType, ObjType> //can have multiple entries for the one key

//UNORDERED MAP
//Organized into buckets depending on hash values to allow for fast access using keys
std::unordered_map<KeyType, ObjType> 
std::unordered_multimap<KeyType, ObjType>


///////////////////////////////////////////////////////////////////////////////////////////////////////  
#include <hash_set>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Functor for comparing two values in the hash table
struct cmp { bool operator()(const char *str1, const char *str2) const { return strcmp(str1, str2) == 0; } };

hash_set<const char*, hash<const char*>, cmp> hashSet;
hash_set<const char*, hash<const char*>,cmp>::iterator it;

hashSet.find("A char* string");     //returns iterator to element or end if not found
hashSet.insert("A Char* string");   //inserts into the has table
hashSet.size();                     //number of elements in hashset
hashSet.empty();                    //returns true/false if empty

///////////////////////////////////////////////////////////////////////////////////////////////////////  
#include <hash_map>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//functor for comparing two values in the hash table
struct cmp { bool operator()(const char *str1, const char *str2) const { return strcmp(str1, str2) == 0; } };

hash_map<const char*, int, hash<const char*>, cmp> hashMap;

hashMap.empty();        //returns true/false if empty
hashMap.size();         //number of elements in hashmap
hashMap["Key"] = 30;    //inserts under key the value 30
hashMap["Key"];         //accesses value using key  

///////////////////////////////////////////////////////////////////////////////////////////////////////
//HEAPS
///////////////////////////////////////////////////////////////////////////////////////////////////////

make_heap(S, E, sortLam) //change range into a heap structure
sort_heap(S, E, sortLam) //sorts heap into ascending order; doing this loses properties as a heap
is_heap(S, E, sortLam) //returns true if range is a heap
push_heap(S, E) //push any values not already in heap structure in range to the heap
pop_heap(S, E) //pop highest value on heap off heap (doesn't remove from container though)
myContainer.front() //get highest value on the heap

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iterator>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::end(O) //iterator pointing at one past end of container object
std::begin(O) //iterator pointing at beginning of container object
std::advance(myIt, n) //advance iterator by n; Random access iterators use +=/-= else ++/-- 
std::distance(myIt1, myIt2) //returns int distance between 2 iterators, it2 must be after it1

//ITERATING OVER CONTAINER
for (vector<int>::iterator it = scores.begin(); it != scores.end(); ++it)
    it->myMethod();
for (auto& item : myVector) //doesn't work with vs2010
    int x = item;

//REVERSE ITERATING
vector<int>::reverse_iterator rit;
for (rit = scores.rbegin(); rit = scores.rend(); rit++)
    cout << *rit << endl;

//OSTREAM ITERATOR
ostream_iterator<int,char>out(cout, " "); //iterator<data type, char> name (stream, seperator between each item)
*out_iter++ = 15;   // works like cout << 15 << " ";
copy(object.begin(), object.end(), out); // copy vector to output stream, out is a function pointer

//ISTREAM ITERATOR
istream_iterator<int, char>(cin)

//REVERSE ITERATOR
vector<int>::reverse_iterator ri;
*ri //dereferencing gives the value of an element one before the pointed to element

//BACK INSERT ITERATOR
// inserts items at the end of the container. can be used only with container types that 
allow rapid insertion at the end
back_insert_iterator<vector<int> > back_iter(v_array); 

//FRONT INSERT ITERATOR
// inserts items at the front. only with container types that allow constant time insertion at the beginning
front_insert_iterator<vector<int> > front_iter(v_array); 

//INSERT ITERATOR
// inserts items in front of the location specified as an argument
insert_iterator<vector<int> > insert_iter(v_array, v_array.begin())
