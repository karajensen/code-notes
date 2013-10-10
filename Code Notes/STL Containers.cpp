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

std::array<int,40> myArray; //fixed, continuous array stored on stack

myArray[i]
myArray.Fill(0) //fills array with value
myArray.empty(); //returns true/false if empty (faster than size)
myArray.size(); //number of elements
myArray.data(); //returns pointer to datas
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
#include <forward_list>
///////////////////////////////////////////////////////////////////////////////////////////////////////

list<int> L;
forward_list<int> FL;

L.empty(); //returns true/false if empty (faster than size)
L.pop_front() //Deletes the element at the beginning of a list.
L.push_front(x) //Adds an element to the beginning of a list.
L.reverse() //Reverses the order in which the elements occur in a list.
L.remove(x) //Removes all elements with value x from list
L.remove_if(boolLambda) //Removes all elements returning true from lamda
L.sort() //sorts using < in ascending order; speed: L(N*logN); stable sort
L.merge(one) //merges one into two, leaving one empty; assumes both are sorted
L.splice(L.begin(), L2) //inserts L2 in front of L.begin(), leaving one empty
L.unique() //removes duplicate values in list; assumes list is sorted
L.clear(); //removes all from container
L.front(); //returns reference to first element
L.swap(L2); //swaps two of SAME containers around
L.erase(Begin(L),End(L)) //Erases the elements in the range; erase_after() for forward list
L.erase(it) //Erases at particular place; erase_after() for forward list
L.max_size() //returns maximum possible size
L.resize(x) //resizes container for x units
L.insert(L.begin(),t) //Inserts a reference of t before iterator; insert_after() for forward list
L.insert(L.begin(),n,t) //Inserts n references of t before iterator;  insert_after() for forward list
L.insert(itr,L2.begin(),L2.end()) //Insert copies of elements in the range before itr; insert_after() for forward list
L.emplace_front //Adds an element constructed in place to the beginning of a list.
L.emplace //Inserts an element constructed in place into a list at a specified position; emplate_after() for forward list

//LIST SPECIFIC METHODS
L.size(); //number of elements
L.pop_back() //Deletes the element at the end of a list.
L.push_back(x) //Adds an element to the end of a list.
L.back(); //returns reference to last element
L.capacity() //returns number of elements vector can contain before more memory needed
L.emplace_back //Adds an element constructed in place to the end of a list.

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <map> 
#include <unordered_map>
///////////////////////////////////////////////////////////////////////////////////////////////////////

typedef std::string KeyType;
typedef std::string ObjType;
typedef std::pair<const KeyType, ObjType> Pair; 
typedef std::map<KeyType, ObjType> MyMap;

MyMap M;
MyMap::iterator itr;

M.empty(); //returns true/false if empty (faster than size)
M.size(); //number of element pairs
M.count("MyKey") //returns number of items that have that key
M.find("MyKey") //returns MyMap.end() if not found or iterator MyMap::iterator if found
itr->first //returns key
itr->second //returns object

//INSERTING ITEMS
//More effecient to use insert; operator[] creates default object then assigns if object doesn't exist 
M.insert(MyMap::value_type("Key","Object")); //value_type is typedef for maps pair
M["MyKey"] = "MyObject"; // Adds entry if key doesn't exist otherwise overwrites

//ITERATING
std::for_each(M.begin(), M.end(), 
    [&](const MyMap::value_type& item){ item.second->DoSomething(); });

//MULTIMAP
std::multi_map<KeyType, ObjType> //can have multiple entries for the one key

//UNORDERED MAP
//Organized into buckets depending on hash values to allow for fast access using keys
std::unordered_map<KeyType, ObjType> 
std::unordered_multimap<KeyType, ObjType>

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <set>
///////////////////////////////////////////////////////////////////////////////////////////////////////

set<string> S;
set<string> S(&Array[0], &Array[6]); // initialize set using a range from array

S.empty(); //returns true/false if empty (faster than size)
S.size(); //number of elements

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
#include <iterator>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::end(O) //iterator pointing at one past end of container object
std::begin(O) //iterator pointing at beginning of container object
std::advance(itr, n) //advance iterator by n; Random access iterators use +=/-= else ++/-- 
std::distance(itr1, itr2) //returns int distance between 2 iterators, it2 must be after it1

//Iterating over container
for (vector<int>::iterator itr = scores.begin(); itr != scores.end(); ++itr)
    itr->myMethod();

for (auto& item : myVector) //doesn't work with vs2010
    int x = item;

for (vector<int>::reverse_iterator rItr = scores.rbegin(); rItr = scores.rend(); ++rItr)
    rItr->myMethod();

//==================================================================================================
//CONTAINER ITERATORS
//==================================================================================================

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

//converting between given cItr to itr
vector<int>::iterator itr(myVec.begin());
std::advance(itr, std::distance<vector<int>::const_iterator>(itr, cItr)); //move itr to where const itr is

//==================================================================================================
//INSERT ITERATORS
//==================================================================================================

//Algorithms that require a range to copy can insert instead
//Call reserve in advance to prevent memory allocation
transform(S, E, back_inserter(myCon), doCopyLam); //insert at end rather than copying
transform(S, E, front_inserter(myCon), doCopyLam); //insert at front rather than copying
transform(S, E, inserter(myCon, myCon.begin()+myCon.size()/2), doCopyLam); //insert in middle

//BACK INSERT ITERATOR
back_insert_iterator<vector<int>> backIter; 
back_inserter(myContainer) //creates back_insert_iterator

//FRONT INSERT ITERATOR
front_insert_iterator<vector<int>> frontIter; 
front_inserter(myContainer) //creates front_insert_iterator

//INSERT ITERATOR
insert_iterator<vector<int>> insertIter;
inserter(myContainer, myContainer.begin()) //creates insert_iterator, inserts at given position

//==================================================================================================
//STREAM ITERATORS
//==================================================================================================

//OSTREAM ITERATOR
ostream_iterator<int,char> ostreamItr(cout, " "); //stream, seperator between each item
*out_iter++ = 15;  //works like cout << 15 << " ";
std::copy(object.begin(), object.end(), ostreamItr);

//OSTREAMBUF ITERATOR
//Faster than ostream_iterator
ostreambuf_iterator<char> ostreamItr(cout);
std::copy(mystring.begin(), mystring.end(), ostreamItr);

//ISTREAM ITERATOR
ifstream myFile("myFile.txt");
myFile.unset(ios::skipws); //disable skipping of whitespace (uses operator<< which skips by default)
std::string myString((istream_iterator<char>(myFile)), istream_iterator<char>());

//ISTREAMBUF ITERATOR
//Faster than istream_iterator, doesn't skip over any character
ifstream myFile("myFile.txt");
std::string myString((istreambuf_iterator<char>(myFile)), istreambuf_iterator<char>());
