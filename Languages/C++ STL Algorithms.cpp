/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ALGORITHMS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

/*************************************************************************************************************
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

• Non-modifying: on const objects; Modifying: on non-const objects
• Preferable to use container's equivalent method for stability
• All ranges are [Start, End) with End non-inclusive
• Can be used with reverse and const iterators
• Comparison lambdas should always return false for equal values
• Functors used are passed by-val and copied
• In-built functors are faster than passing lambdas/function pointers due to them being inlined

CONDITION          UNSORTED      SORTED               SET/MAP         MULTI SET/MAP
does obj exist     std::find     std::binary_search  .count()        .find()
find obj           std::find     std::equal_range    .count()        .find()     
no. obj with val   std::count    std::equal_range    .count()        .count()
find all obj       std::find     std::equal_range    .equal_range()  .equal_range()
find obj if        std::find_if  std::lower_bound    .lower_bound()  .lower_bound()      

SORT/SEARCHING
• Sorting Fastest-slowest: Partitions, partial_sort, sort, stable_sort
• Require sort ascending, Search speed O(logN): binary_search, lower_bound, upper_bound, equal_range
• Don't require sorting, Search speed O(N): count, count_if, find, find_if
• std::sort must be any algorithm with O(NlogN), std::stable_sort must be stable with O(NlogN)
                    
INSERTING
• Algorithms that copy over a range can be changed to insert with back/front insert iterators
• Emplacing is always as (if not more) effecient as insert/push
• Never emplace arguments allocating memory through new in case of memory exception; use push/insert
**************************************************************************************************************/

auto doCopyLam = [](auto obj) -> MyClass { obj.SomeMethod(); return obj; };
auto doLam = [](const auto& obj) { obj.NonConstMethod(); };
auto boolLam = [](const auto& obj) ->bool { return o.Exists(); };
auto equalLam = [](const auto& obj1, const auto& obj2) -> bool { return obj1 == obj2; };
auto sortLam = [](const auto& obj1, const auto& obj2) -> bool { return obj1.myInt < obj2.myInt; };
auto reverseSortLam = [](const auto& obj1, const auto& obj2) -> bool { return obj1.myInt > obj2.myInt; };
auto createLam = [i = 0]() mutable -> MyClass { return MyClass(i++); });
struct DelFunctor { template<typename T> void operator()(const T* ptr) const { delete ptr; ptr = nullptr; } };

// ACCEPTED FUNCTION OBJECTS
struct myFunctor { void operator()(int i){} };   // ..., myFunctor);
std::plus<T> stdFunctor;                         // ..., stdFunctor); or ..., std::plus<T>());
auto myLambda = [](int i) {};                    // ..., myLambda);
inline void myFunction(const MyClass& obj){}     // ..., myFunction);
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

//===============================================================================================================
// NON-MODIFYING SEQUENCE OPERATIONS
//===============================================================================================================

adjacent_find(S, E, equalLam) // Returns iterator to first element that is repeated consecutivly or E if not found
all_of(S, E, boolLam) // If all objs return true then returns true, else false; If no objs in range returns true
any_of(S, E, boolLam) // If any obj is true returns true, else false; If no objs in range returns false
count(S, E, myObj) // Returns int on number of items of myObj in container
count_if(S, E, boolLam) // Returns number of obj that lamda returns true
equal(S, E, S2, equalLam) // Returns true if both ranges are equal to each other including ordering
find(S, E, myObj, equalLam) // Returns iterator to first instance of element, If not found, returns E
find_end(S, E, S2, E2, equalLam) // Same as search but back to front, returns S if none found
find_first_of(S, E, S2, E2, equalLam) // Returns iterator to first element that matches any element in range 2 else returns end
find_if(S, E, boolLam) // Returns iterator to first element in range that lambda returns true, If not found, returns E
find_if_not(S, E, boolLam) // Returns iterator to first element in range that lambda returns false, If not found, returns E
for_each(S, E, doLam)  // For each item calls function
for_each_n(S, n, doLam); // For n items from S calls function
mismatch(S, E, S2, equalLam) // Returns std::pair of iterators to first elements that don't match between range 1 and 2
none_of(S, E, boolLam) // If all objs return false returns true, else false; If no objs in range returns true
search(S, E, S2, E2, equalLam) // Search for range 2 in range 1, returns iterator to start of sequence found or E if none
search_n(S, E, n, myObj, equalLam) // Searches for obj repeating n times, returns iterator to start of sequence or E if none

// Finds the first mismatching item between two ranges, returns true if item from 1 is < item from 2
// If first mismatch is end of a range, the shorter range is less than the other
// Two empty ranges are equal, and empty range is < a non-empty range
lexicographical_compare(S1, E1, S2, E2, equalLam)
    
// CONVERT TO C-STYLE CONTAINERS
// modifying c-style version cannot change number of elements
// for non-continuous containers, need to copy to continuous
&myVector[0] // pointer to first member in vector; memory in continuous block
myString.c_str() // string in c-style, can't use &myString[0] as string may not be in continuous block
                                                                                           
//===============================================================================================================
// MODIFYING SEQUENCE OPERATIONS
//===============================================================================================================

copy(S, E, ostream_iterator<T>(cout, " ")); // copy container into output stream with space between elements   
copy(S, E, S2) // copies O into O2, returns iterator to E2
copy(S, E, back_inserter(O2)) // inserts O into O2, returns iterator to E2
copy_backward(S, E, E2) // copies O into O2 backwards, returns iterator to S2
copy_if(S, E, S2, boolLam) // only copies element if lamda is true, returns iterator to E2
copy_if(S, E, back_inserter(O2), boolLam) // inserts into C2 rather than copies, returns iterator to E2
copy_n(S, n, S2) // copies from O to n elements into O2, returns iterator to E2, does nothing if n <= 0
fill(S, E, "A") // fill range with reference of value A
fill_n(S, n, "A") // fill from S to n elements with reference of value A
generate(S, E, createLam) // calls lamda and assigns return for each element
generate_n(S, n, createLam) // calls lamda and assigns return for each element from S to n elements
iter_swap(it1, it2) // swap what each iterator points to but not underlying objects    
move(S, E, S2) // moves from O to O2 leaving O in undefined, valid state, returns iterator to E2, requires move constructor/op
move_backward(S, E, E2) // moves from O to O2 leaving O in undefined, valid state, returns iterator to S2, requires move constructor/op
random_shuffle(S, E) // randomly shuffles elements
remove_copy(S, E, S2, "A") // copies to range 2 with all instances of A removed, return iterator is from 2
remove_copy_if(S, E, S2, boolLam) // copies to range 2 with elements returning true removed, return it is from 2
replace(S, E, 'A', 'B') // replaces over range any values that are A with value B
replace_copy(S, E, S2, 'A', 'B') // copies S to S2 and replaces in range 2 any A with B
replace_copy_if(S, E, S2, boolLam, 'A') // copies S to S2, replaces with A if lambda returns true in range 2 
replace_if(S, E, boolLam, 'A') // replaces element with A if lambda returns true, useful for replacing characters in a string
reverse(S, E) // reverses order of elements
reverse_copy(S, E, S2) // copies into 2 with the reverse order, returns iterator E2
rotate(A, B, C) // ranges B-C and A-B swap places. B needs to be between A and C.
rotate_copy(A, B, C, S2) // Copies into 2 with ranges B-C and A-B swapped. B needs to be between A and C.
sample(S1, E2, back_inserter(S1), n) // Selects random n items from 1
swap(T, T) // swap any type object with the other, works on all types/containers
swap_ranges(S, E, S2) // exchange values of two ranges, returns iterato to E2    
transform(S, E, S2, doCopyLam) // Modifying; each element calls lambda then is copied to second container
transform(str.begin(), str.end(), str.begin(), toupper); // Modifying; can be copied in place
transform(S, E, back_inserter(myCon), doCopyLam); // insert at end rather than copying
unique_copy(S, E, S2) // copies into 2 and removes double values, returns iterator in 2 to new end  

// MOVING BETWEEN SEQUENCE CONTAINERS
O.insert(O.end(), make_move_iterator(O2.begin()), make_move_iterator(O2.end()));

// REMOVING DUPLICATES
//Fastest is unordered_set, then std::unique
unique(S, E) //moves all unique items to front of range; returns iterator to end of this range, requires sorting
unordered_set<int> set; //Faster to fill a set manually than use its constructor
for (int i : vec) { set.insert(i); }
vec.assign(set.begin(), set.end());
  
// REMOVING FROM SEQUENCE CONTAINERS
// Only works for array/vector/deque/list, better to use list.remove though
// Requires Erase remove idiom to actually remove, std::remove only moves wanted items to start of range, overwriting values if needed
remove(S, E,"A") // moves all items that aren't A to front of range; returns iterator to end of this range
remove_if(S, E, boolLam) // moves all items that return false to front of range; returns iterator to end of this range
O.erase(remove(O.begin(), O.end(), "A"), O.end()); //Erase-remove idiom
O.erase(remove_if(S, E, boolLam), O.end());
O.erase(unique(S, E), O.end());
  
// REMOVING FROM ASSOCIATIVE CONTAINERS
O.erase("A"); //remove all with key for associative containers
for(auto it = O.begin(); it != O.end(); ) //remove_if
{
    if(boolLam()){ it = O.erase(it); }
    else { ++it; }
}

// CLEARING CONTAINERS
// Reducing capactiy not needed for list, set, map as they don't reserve space
obj.clear();                         // Make obj empty with current capacity
std::vector<MyClass>().swap(obj);    // Make obj empty with minimal capacity
std::vector<MyClass>(obj).swap(obj); // Make obj with minimal capacity

//===============================================================================================================
// PARTITIONING OPERATIONS
//===============================================================================================================

// Splits container to those returning true and those returning false
is_partitioned(S, E, boolLam) // returns true if all elements returning true occur before those returning false
partition(S, E, boolLam) // splits the container to returning true->returning false; returns it to first returning false
partition_copy(S, E, S2, S3, boolLam) // those returning true copied to 2, those returning false copied to 3
partition_point(S, E, boolLam) // requires container to be partitioned; returns iterator to first element returning false
stable_partition(S, E, boolLam) // same as parition but keeps original ordering between both partitions

//===============================================================================================================
// SORTING OPERATIONS
//===============================================================================================================

// requires random access (can't be used on lists)
is_sorted(S, E, sortLam) // returns false if not sorted in ascending order, stop when mismatching pair found
is_sorted_until(S, E, sortLam) // Returns itr to first element which does not follow an ascending order else returns E
nth_element(S, M, E, sortLam) // puts M at the position it'd be if range was sorted, elements before are less/after are more (in any order)
partial_sort(S, M, E, sortLam) // smallest elements from S-E are put in ascending order from S-M, M-E becomes unordered
partial_sort_copy(S, E, S2, E2, sortLam) // copies range to 2 and sorts in ascending order
sort(S, E, sortLam) // sorts container in ascending order, without lamda uses operator<
sort(S, E, greater<double>()) // using inbuilt functor
stable_sort(S, E, sortLam) // sorts container in ascending order, equal elements preserve original order
    
//===============================================================================================================
// BINARY SEARCH OPERATIONS
//===============================================================================================================

binary_search(S, E, myObj, equalLam) // returns true if lamda is true, requires sorting
equal_range(S, E, myObj, equalLam) // Returns pair of itrs for bounds of subrange with values that return true for equalLam
lower_bound(S, E, myObj, sortLam) // returns first value found >= myObj, requires sorting, If not found, returns E
upper_bound(S, E, myObj, sortLam) // returns first value found > myObj, requires sorting, If not found, returns E
    
//===============================================================================================================
// SET OPERATIONS
//===============================================================================================================

// Only used on sorted ranges, all elements remain in sorted ascending order
// Use inserter(S3, S3.begin())
includes(S, E, S2, E2) // returns true if range 2 is in range 1; both ranges must be sorted in ascending order
merge(S, E, S2, E2, inserter) // copies 1 and 2 into 3
set_union(S, E, S2, E2, inserter) // copies 1 and 2 into 3 and removes duplicates
set_intersection(S, E, S2, E2, inserter) // copies elements in 1 that are also in 2 into 3
set_difference(S, E, S2, E2, inserter) // copies elements in 1 that are not in 2 into 3
set_symmetric_difference(S, E, S2, E2, inserter) // copies elements in 1 that don't exist in 2 and vice versa into 3

//===============================================================================================================
// HEAP OPERATIONS
//===============================================================================================================

is_heap(S, E, sortLam) // returns true if range is a heap
make_heap(S, E, sortLam) // change range into a heap structure
push_heap(S, E) // push any values not already in heap structure in range to the heap
pop_heap(S, E) // pop highest value on heap off heap (doesn't remove from container though)
sort_heap(S, E, sortLam) // sorts heap into ascending order; doing this loses properties as a heap
myContainer.front() // get highest value on the heap
    
//===============================================================================================================
// MINIMUM/MAXIMUM OPERATIONS
//===============================================================================================================

clamp(T, min, max) // returns reference to min if T < min, reference to max if T > max or reference to T
min(T, T) // returns minimum of two values
max(T, T) // returns maximum of two values
minmax(T, T) // returns std::pair(min,max) where .first is min and .second is max
min_element(S, E, sortLam) // returns minimum element between range
max_element(S, E, sortLam) // returns maximum element between
    
//===============================================================================================================
// PERMUTATIONS
//===============================================================================================================

is_permutation(S, E, S2, equalLam) // returns true if both ranges are equal to each other excluding ordering
prev_permutation(S, E) // rearranges container to the next permutation, starting from sorted descended ordering
next_permutation(S, E) // rearranges container to the next permutation, starting from sorted ascended ordering
    
//===============================================================================================================
// NUMERIC OPERATIONS
//===============================================================================================================

// In #include <numeric>
accumulate(S, E, initial) // returns initial+values over whole range 
accumulate(S, E, initial, std::minus<T>()) // returns initial-values over whole range
adjacent_difference(S1, E1, S2) // for each C2 element: S2[i] = S1[i] - S1[i-1] with S2[0] = S1[0]
adjacent_difference(S1, E1, S2, std::plus<T>()) // for each C2 element: S2[i] = S1[i] + S1[i-1] with S2[0] = S1[0]
inner_product(s1, E1, S2, value) // multiplies elements and accumulates: value += S1[i] * S2[i], returns final value
iota(S, E, value) // for each element: assign value then increment value (value++)
reduce(execution::par, S, E, initial) // faster version of accumulate that can modify inputs
transform_reduce(execution::par, S1, E1, S2, initial) // same as reduce but copies results into another buffer
partial_sum(S1, E1, S2) // for each C2 element add all previous values in C1: S2[i] = S1[i] + S1[i-1] + ... + S1[0]
inclusive_scan(S1, E1, S2) // same as partial_sum except non-associative container operations may be done in any order    
    
//===============================================================================================================
// STRING CONVERSIONS
//===============================================================================================================
    
// STD::WSTRING TO/FROM STD::STRING
// Requires #include <codecvt>
str = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wstr);
wstr = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
    
// STD::STRING TO CHAR*:
std::string str = "test";
std::vector<char> vec(str.size() + 1);
std::copy(str.begin(), str.end(), vec.begin());
vec[vec.size()-1] = '\0';
char* myCStr = &vec[0];

// HEX STRING TO INT
unsigned int x = std::stoul("0xfffefffe", nullptr, 16);

// STRING TO NUMBER
atoi("3")   // converts cstring to int
atof("3.0") // converts cstring to float

// NUMBER TO STRING
// Only for integers and floating types
// Gives large precision with no control
std::to_string(value);
std::to_wstring(value);

// NUMBER TO STRING: PRINTF/WPRINTF
// On success, total number of characters written is returned, not including \0 auto added to end
// On failure, a negative number is returned, \0 not guaranteed to be written
// %[flag][width.precision][length modifier][conversion specifier]
char buffer[256];
sprintf(buf, "%%")            // display % sign

// Conversion Specifiers:
sprintf(buf, "%d", value)     // display integer (length modifier required for some types)
sprintf(buf, "%x", value)     // display integer in hexadecimal
sprintf(buf, "%X", value)     // display integer in hexadecimal in caps
sprintf(buf, "%f", value)     // display float/double (length modifier required for some types)
sprintf(buf, "%e", value)     // display float/double using scientific notation with e (eg. 1.86e6)
sprintf(buf, "%E", value)     // display float/double using scientific notation with E (eg. 1.86E6)
sprintf(buf, "%g", value)     // display float/double using the shorter of %f or %e
sprintf(buf, "%G", value)     // display float/double using the shorter of %f or %E
sprintf(buf, "%s", value)     // display cstring, using empty str will not give any output
    
// Length Modifiers:
// Required for numbers using 'short', 'long' etc. otherwise gives garbage values
sprintf(buf, "%hd", value)    // requires 'h' in front for short int/unsigned short int
sprintf(buf, "%ld", value)    // requires 'l' in front for long int/unsigned long int
sprintf(buf, "%Ld", value)    // requires 'L' in front for long double
sprintf(buf, "%ls", value)    // requires 'l' in front for wide strings

// Width.Precision:
// Precision: Controls padding for integers, precision for floats
// Width: Controls padding for floats/strings
sprintf(buf, "%.3f", value);  // number of values after decimal point, will round up/down
sprintf(buf, "%.3g", value);  // number of significant numbers (not 0) used for whole number
sprintf(buf, "%.3d", value);  // minimum number of digits, will pad with 0 in front
sprintf(buf, "%.3s", value);  // maximum characters to use in string
sprintf(buf, "%3s", value);   // minimum characters to use in string, will pad with space in front

// Flags
sprintf(buf, "%#x", value);   // puts 0x in front of hexadecimal number
sprintf(buf, "%-5d", value);  // puts padding at the end rather than start
    
