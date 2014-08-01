//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm> 
///////////////////////////////////////////////////////////////////////////////////////////////////////

auto doCopyLam = [](MyClass o) -> MyClass { o.SomeMethod(); return o; };
auto doLam = [](const std::shared_ptr<MyClass>& ptr) { ptr->NonConstMethod(); };
auto boolLam = [](const MyClass& o) ->bool { return o.Exists(); };
auto equalLam = [](const MyClass& o1, const MyClass& o2) -> bool { return o1 == o2; };
auto sortLam = [](const MyClass& o1, const MyClass& o2) -> bool { return o1.myInt < o2.myInt; };
auto createLam = []() -> int { return rand()%10; }
struct DelFunctor { template<typename T> void operator()(const T* ptr) const { delete ptr; ptr = nullptr; } };

// ACCEPTED PREDICATES
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

//=======================================================================================================
//ITERATIVE ALGORITHMS
//=======================================================================================================

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

//=======================================================================================================
//SEARCHING ALGORITHMS
//=======================================================================================================

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

//=======================================================================================================
//GENERATING ALGORITHMS
//=======================================================================================================

//FILLING
fill(S, E, "A") //fill range with reference of value A
fill_n(S, n, "A") //fill from S to n elements with reference of value A
generate(S, E, createLam) //calls lamda and assigns return for each element
generate_n(S, n, createLam) //calls lamda and assigns return for each element from S to n elements

//ADDING ELEMENTS TO CONTAINERS
O.resize(MAX_ELEMENTS);
std::generate(O.begin(), O.end(), [&](){ return MyClassPtr(new MyClass()); });
std::generate(O.begin(), O.end(), [&](){ return MyClass(); });

//=======================================================================================================
//MOVING ALGORITHMS
//=======================================================================================================

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
replace(S, E, "A", "B") //replaces over range any values that are A with value B
replace_if(S, E, boolLam, "A") //replaces element with A if lambda returns true
replace_copy(S, E, S2, "A", "B") //copies S to S2 and replaces in range 2 any A with B
replace_copy_if(S, E, S2, boolLam, "A") //copies S to S2, replaces with A if lambda returns true in range 2 

//MERGING
//Only used on sorted ranges, all elements remain in sorted ascending order
merge(S, E, S2, E2, S3) //copies 1 and 2 into 3
set_union(S, E, S2, E2, S3) //copies 1 and 2 into 3 and removes duplicates
set_intersection(S, E, S2, E2, S3) //copies elements in 1 that are also in 2 into 3
set_difference(S, E, S2, E2, S3) //copies elements in 1 that are not in 2 into 3
set_symmetric_difference(S, E, S2, E2, S3) //copies elements in 1 that don't exist in 2 and vice versa into 3

//=======================================================================================================
//SORTING ALGORITHMS
//=======================================================================================================

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

//=======================================================================================================
//REMOVING ALGORITHMS
//=======================================================================================================

//TRIMMING CONTAINERS
//constructor creates temp container with mimimum capacity and swap this into old container
vector<MyClass>(O).swap(O)
string(str).swap(str)

//SEPERATE WANTED/UNWANTED ITEMS
//Doesn't remove anything, only moves wanted items to start of range, overwriting values if needed
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

//=======================================================================================================
//CONVERSION ALGORITHMS
//=======================================================================================================

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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//CUSTOM ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//CHANGE RANGE OF A VALUE
template<typename T> 
T ChangeRange(T value, T currentInner, T currentOuter, T newInner, T newOuter)
{
    return ((value-currentInner)*((newOuter-newInner)/(currentOuter-currentInner)))+newInner;
}

//CAP A VALUE
template<typename T>T 
CapValue(T value, T minValue, T maxValue)
{
    value = std::min(value, maxValue);
    value = std::max(value, minValue);
    return value;
}

//DEGREES/RADIANS CONVERSION
#define _USE_MATH_DEFINES
#include <math.h>
template<typename T> T DegToRad(T degrees)
{
    return static_cast<T>(M_PI/180.0)*degrees;
}
template<typename T> T RadToDeg(T radians)
{
    return static_cast<T>(180.0/M_PI)*radians;
}

//CSTRING: REVERSE LETTERS
char test[] = "this is a test";
char saved = ' ';
int len = strlen(test);
for(int i = 0; i < l/2; ++i)
{
    saved = test[i];
    test[i] = test[len-i-1];
    test[len-i-1] = saved;
}

//STRING: REVERSE LETTERS
std::reverse(str.begin(), str.end());

//STRING: MAKE UPPER/LOWER CASE
std::transform(str.begin(), str.end(), str.begin(), &std::toupper);
std::transform(str.begin(), str.end(), str.begin(), &std::tolower);

//STRING: CASE INSENSITIVE COMPARISON
str1.size() == str2.size() &&
std::equal(str1.begin(), str1.end(), str2.begin(), 
    [](char c1, char s2){ return toupper(c1) == toupper(c2); });

//WINDOWS ERROR MESSAGE POPUP
MessageBox(nullptr, TEXT(error), TEXT("ERROR"), MB_OK);

//GET 1D INDEX FROM 2D COORD
for(int x = 0; x < columns; ++x)
{
    for(int z = 0; z < rows; ++z)
    {
        int index = (columns*z)+x;
    }
}

//WHETHER NUMBER IS EVEN
if(x % 2)
{
    //x is odd
}

//GET DIGIT AT RADIX SIGNIFICANT POSITION (1, 10, 100..)
int digit = number/position % 10;

//GETTING COLOR COMPONENTS VIA BIT SHIFTING
unsigned int color;
int r = color & 0xFF;
int g = (color >> 8) & 0xFF;
int b = (color >> 16) & 0xFF;
int a = (color >> 24) & 0xFF;

//GENERATE FIBONACCI NUMBERS
//copies into container: 1 1 2 3 5 8 13 21 34 55
std::vector<int> v = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
std::adjacent_difference(v.begin(), v.end() - 1, v.begin() + 1, std::plus<int>());

//SAFE RELEASE
SafeRelease(&myPointer); // pointer to object
template <typename T> void SafeRelease(T** pObject)
{
    if(*pObject)
    {
        (*pObject)->Release();
        *pObject = nullptr;
    }
}