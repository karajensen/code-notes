/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <utility>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::forward    // Casts to rvalue only if argument was initialized with an rvalue, compile time
std::move       // Casts to rvalue no matter what type it is, compile time, stl containers auto become empty
std::swap       // Swaps the value of two variables, non-throwing on primitive types
std::as_const   // Creates const lvalue reference, useful for forcing const function overloads

std::pair<int, double> myPair = std::make_pair(1,2.0);
myPair.first / myPair.second // access members of pair
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cstring>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// works on character arrays and string temp/literals

strlen(str) // gives the length of the string array minus the null character
strcpy(str1, str2) // copy cstring2 to cstring1 including '\0'
strncpy(str1, str2, 3) // copy 3 members of cstring2 to cstring1, must do cstring1[4] = '\0' after
strcat(str1, str2) // append contents of cstring2 to cstring1
strcmp(str1, str2) // checks each char until reaching a '\0', returns 0 if same or < or > 0 if 1 < or > 2
strchr(str, ch) // returns ptr to first occurance of char chosen, or null if not there
strrchr(str, ch) // returns ptr to last occurance of char chosen, or null if not there
strpbrk(str1, str2) // returns ptr to first occurance of any character in str2 or null if none
strtok(str, delim) // removes token from str and returns it using deliminators
wcscpy(str1, str2) // strcpy for wide strings
wcsncpy(str1, str2) // strncpy for wide strings

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cctype>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

isalpha(myChar)  // is character a letter
isalnum(myChar)  // is character a letter or number
isdigit(myChar)  // is character a decimal digit (0-9)
isxdigit(myChar) // is character a hexadecimal digit (0-9, A-F)
isspace(myChar)  // is character a whitespace characters (newlines, spaces, and tabs)
isblank(myChar)  // is character a space or tab
ispunct(myChar)  // is character a punctuation character
iscntrl(myChar)  // is character a control character
islower(myChar)  // is character lower case
isupper(myChar)  // is character upper case
tolower(myChar)  // returns lower case of character
toupper(myChar)  // returns upper case of character

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <typeinfo>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typeid(myObject)               // returns const type_info& for object
typeid(MyClass)                // returns const type_info& for class
typeid(*myBasePtr)             // will use most derived type as works on object
typeid(*this)                  // if done in constructor/destructor will use actual type, not most derived type
typeid(T) == typeid(const T)   // cv and * and & qualifiers ignored

// String identifying class type, compilier dependent
// Visual Studio: class MyNamespace::MyClass
typeid(myObject).name()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <type_traits>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// is_const_v<A> == is_const<A>::value
// decay_t<A> == decay<A>::type
std::is_aggregate<T>::value // Whether a aggregate type
std::is_arithmetic<T>::value // Whether a numeric type
std::is_base_of<A,B>::value // returns true if A is a base class of B
std::is_assignable<A,B>::value // returns true if A==B is possible
std::is_move_assignable<A>::value // returns true if A has a move assignment operator
std::is_move_constructible<A>::value // returns true if A has a move constructor
std::has_virtual_destructor<A>::value // returns true if A has a virtual destructor
std::is_same<A,B>::value // returns true if A and B are of the same type and constness
std::is_integral<A>::value // returns true if A is int/char/bool reguardless of constness, note if int& will be false
std::is_void<A>::value // returns true if A is void reguardless of constness
std::is_null_pointer<A>::value // returns true if A is nullptr reguardless of constness
std::is_const<A>::value // returns true if A is const
std::is_pointer<A>::value // returns true if A is a pointer
std::is_array<A>::value // returns true if A is an array
std::is_reference<A>::value // returns true if A is a reference
std::is_polymorphic<A>::value // returns true if A is a non-union class with at least 1 virtual function
std::is_abstract<A>::value // returns true if A is a non-union class with a pure virtual function
std::is_enum<A>::value // returns true if enum or enum class
std::is_signed<A>::value // returns true if type is signed
std::remove_cv<A>::type // returns A with any const or volitile or both modifiers removed
std::remove_const<A>::type // returns A with any const modifiers removed
std::remove_volatile<A>::type // returns A with any volitile modifiers removed
std::remove_reference<A>::type // returns A with any reference removed
std::remove_pointer<A>::type // returns A with any pointer removed
std::decay<A>::type // functions/arrays will decay to pointer, other types is remove_cv with remove_reference
std::underlying_type<A>::type // Underlying type of enum

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <tuple>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::tuple<int, double, std::string> myTuple = std::make_tuple(0,2.0,"hello");
auto value = std::get<0>(myTuple); // Get value at index 0, must be const index
std::tie(myInt, myDouble, std::ignore) = myTuple; // copies from tuple into variables
std::ignore // ignore copying of variable at position
MyClass obj{std::make_from_tuple(myTuple)}; // allows initializing a POD from the tuple
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <optional>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
std::optional<int> opt; // std::nullopt
std::optional<int> opt = make_optional(0);
*opt // Undefined if doesn't exist
if (opt) {} // boolean cast operator if has a value
if (opt == 0) {} // Comparison works on value
opt.reset(); // destroys the value
opt.value(); // returns a reference to the value, throws if doesn't exist
opt.has_value(); // whether has a value
opt.value_or(0); // returns copy of value or default value

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <variant>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Union with internal memory for the maximum size of the underlying types plus overhead for management
// No heap memory is allocated
// Cannot hold references / void / C-style array
// Cannot be empty except in undefined states from exceptions
// First type must have a default constructor which is automatically called on creation

std::variant<int, float> var;            // can hold int or float, default constructor called if needed
std::variant<int, float> var{1.0};       // can hold int or float
var = 20;                                // assign a value, current type is now int
var.index();                             // returns 0-based index for current type (eg. 0 for int, 1 for float)
std::get<int>(var);                      // throws std::bad_variant_access if wrong current type
std::get<0>(var);                        // throws std::bad_variant_access if wrong current index
std::get_if<int>(&var);                  // returns T* if the correct current type, nullptr if incorrect
std::get_if<0>(&var);                    // returns T* if the correct current index, nullptr if incorrect
var.emplace<0>(77);                      // initializes int, destroys float 
std::variant<std::monostate, int, float> // use if first type has no default constructor

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <any>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Allows changing type with type safety, can hold any type and be empty

std::any a;                 // empty 
a = 4;                      // assign new value/type
a.type();                   // compare with typeid(int), empty is typeid(void)
a.reset();                  // makes empty
a = {}                      // makes empty
a = std::make_any<short>(4) // force change type
a.emplace_back<short>(4)    // allow force set type
a.has_value()               // whether empty
std::any_cast<int>(a)       // throws if empty or wrong type
std::any_cast<int&>(a)      // throws if empty or wrong type
std::any_cast<int>(&a)      // returns int* or null if empty or wrong type
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <random>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

srand(time(0));                     // choose a seed
rand()                              // returns int between [0, RAND_MAX]
(rand() % (max - min)) + min;       // [min, max)
(rand() % (max - min + 1)) + min;   // [min, max]

// Distribution
// create one generator per application
std::default_random_engine generator;
std::uniform_int_distribution<int> dist(lower, upper); // integer distribution
std::uniform_real_distribution<float> dist(lower, upper); // real distribution
auto getRand = [&]() ->int { return dist(generator); } // Generates number in the range [lower,upper]
auto getRand = std::bind(dist, generator); // Bind and use as function object

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ctime> <chrono>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
CLOCKS_PER_SEC         // Number of ticks per second
std::clock()           // Returns clock ticks passed since program started as std::clock_t
std::time()            // Returns current time as std::time_t
std::localtime(&time)  // Returns std::tm object
int year = (tm->tm_year + 1900)
int month = (tm->tm_mon + 1)
int day = tm->tm_mday
int hour = tm->tm_hour
int minutes = tm->tm_min
int seconds = tm->tm_sec

std::chrono::seconds sec(1);
std::chrono::microseconds ms(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <limits>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//minimum negative, maximum positive
char   SCHAR_MIN  SCHAR_MAX  UCHAR_MAX
short  SHRT_MIN   SHRT_MAX   USHRT_MAX
int    INT_MIN    INT_MAX    UINT_MAX
long   LONG_MIN   LONG_MAX   ULONG_MAX

//minimum positive, maximum positive
float  FLT_MIN  FLT_MAX 

std::is_same<float, T>::value // true/false whether types are the same (including constness)
std::remove_const<T>::type // returns the type without const

numeric_limits<int>::min() // mimimum negative for int, minimum positive for float
numeric_limits<int>::max() // maximum positive for int/float
numeric_limits<int>::lowest() // mimimum negative for int/float
numeric_limits<int>::is_signed // whether signed/unsigned
numeric_limits<int>::digits // number of non-signed bits for int, number of digits for float
numeric_limits<int>::has_infinity // whether type can represent infinity
numeric_limits<int>::infinity() // representation of positive infinity if possible
numeric_limits<int>::round_style // returns rounding style used
numeric_limits<float>::epsilon() // floating point error amount

round_toward_zero // if it rounds toward zero.
round_to_nearest // if it rounds to the nearest representable value.
round_toward_infinity // if it rounds toward infinity.
round_toward_neg_infinity // if it rounds toward negative infinity.
round_indeterminate // if the rounding style is indeterminable at compile time.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cmath>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

modf(x, &y) // returns the fractional part of double x and puts integer part in double y
abs(-1); // Gets absolute value for double
fabs(-1); // Gets absolute value for float
pow(2, 8); // finding 2⁸
sqrt(4); // finding square root of 4
ceil(4.3) // returns closest integer rounding up (5)
floor(4.7) // returns closest integer rounding down (4)
round(4.5) // math round- to closest integer up/down with 0.5 going up
cos(angle) // angle in radians
sin(angle) // angle in radians
tan(angle) // angle in radians
acos(x/r) // cosӨ = A/C, returns radians
asin(y/r) // sinӨ = O/C, returns radians
atan(x/y) // tanӨ = O/A, returns radians
atan2(x, y) // calculates tan(x/y), returns radians
_finite(0.0) // returns whether its a valid (not infinite/undefined) double
_chgsign(x) // returns x with its sign reversed
_copysign(x, y) // returns double with magnitude of x and sign of y
copysign(x, y) // returns double with magnitude of x and sign of y

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef _Longlong int64_t;
typedef _ULonglong uint64_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <regex>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::regex pattern {R"(\w{2}?)"}
std::smatch matches;
std::regex_search(line, matches, pattern); // returns true if match found

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <future> <thread> <mutex>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// THREADING
// Moves arguments into thread
// Will terminate if out of scope
std::thread thread(&MyFunction, arg1, arg2);
thread.join(); // stop thread once function call is finished
std::this_thread::get_id() // Returns std::thread::id which can be used in std::cout or compared
std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep this current thread

// MUTEX
// Move-only object
std::mutex myMutex;
std::lock_guard<std::mutex> lock(myMutex); // scoped locking/unlocking
if (std::lock_guard<std::mutex> lg{mutex}; str.empty()) {}
if(myMutex.try_lock()) // doesn't block if can't lock
{
    myMutex.unlock()
}

// FUTURE
// Do function asynchronously and hold return type once finished
// Will terminate if out of scope
std::future<T> handle = std::async(std::launch::async, &MyFunction);
handle.wait() // blocks until result is available
handle.get()  // blocks until result is available and returns result

// FUTURE POLICIES
std::launch::async     // A new thread is launched to execute the task asynchronously 
std::launch::deferred  // Task is executed on the calling thread the first time its result is requested 
    
// ATOMIC
// Threadsafe, not copyable or movable, unless to T, T can be basic bool, integers, floats, char etc.
std::atomic<T> myThreadsafeVar; 
