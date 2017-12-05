///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <utility>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::forward    // Casts to rvalue only if argument was initialized with an rvalue, compile time
std::move       // Casts to rvalue no matter what type it is, compile time
std::swap       // swaps the value of two variables, non-throwing on primitive types

std::pair<int, double> myPair = std::make_pair(1,2.0);
myPair.first / myPair.second // access members of pair
    
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cstring>
///////////////////////////////////////////////////////////////////////////////////////////////////////
// works on character arrays and string temp/literals

strlen(str) //gives the length of the string array minus the null character
strcpy(str1, str2) //copy cstring2 to cstring1 including '\0'
strncpy(str1, str2, 3) //copy 3 members of cstring2 to cstring1, must do cstring1[4] = '\0' after
strcat(str1, str2) //append contents of cstring2 to cstring1
strcmp(str1, str2) //checks each char until reaching a '\0', returns 0 if same or < or > 0 if 1 < or > 2
strchr(str, ch) //returns ptr to first occurance of char chosen, or null if not there
strrchr(str, ch) //returns ptr to last occurance of char chosen, or null if not there
strpbrk(str1, str2) //returns ptr to first occurance of any character in str2 or null if none
strtok(str, delim) //removes token from str and returns it using deliminators
wcscpy(str1, str2) //strcpy for wide strings
wcsncpy(str1, str2) //strncpy for wide strings

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cctype>
///////////////////////////////////////////////////////////////////////////////////////////////////////

isalpha(myChar)  //is character a letter
isalnum(myChar)  //is character a letter or number
isdigit(myChar)  //is character a decimal digit (0-9)
isxdigit(myChar) //is character a hexadecimal digit (0-9, A-F)
isspace(myChar)  //is character a whitespace characters (newlines, spaces, and tabs)
isblank(myChar)  //is character a space or tab
ispunct(myChar)  //is character a punctuation character
iscntrl(myChar)  //is character a control character
islower(myChar)  //is character lower case
isupper(myChar)  //is character upper case
tolower(myChar)  //returns lower case of character
toupper(myChar)  //returns upper case of character

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <typeinfo>
///////////////////////////////////////////////////////////////////////////////////////////////////////

typeid(myObject)               //returns const type_info& for object
typeid(MyClass)                //returns const type_info& for class
typeid(*myBasePtr)             //will use most derived type as works on object
typeid(*this)                  //if done in constructor/destructor will use actual type, not most derived type
typeid(T) == typeid(const T)   //cv and * and & qualifiers ignored

// String identifying class type, compilier dependent
// Visual Studio: class MyNamespace::MyClass
typeid(myObject).name()

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <type_traits>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::is_arithmetic<T>::value //Whether a numeric type
std::is_base_of<A,B>::value //returns true if A is a base class of B
std::is_assignable<A,B>::value //returns true if A==B is possible
std::is_move_assignable<A>::value //returns true if A has a move assignment operator
std::is_move_constructible<A>::value //returns true if A has a move constructor
std::has_virtual_destructor<A>::value //returns true if A has a virtual destructor
std::is_same<A,B>::value //returns true if A and B are of the same type and constness
std::is_integral<A>::value //returns true if A is int/char/bool reguardless of constness, note if int& will be false
std::is_void<A>::value //returns true if A is void reguardless of constness
std::is_null_pointer<A>::value //returns true if A is nullptr reguardless of constness
std::is_const<A>::value //returns true if A is const
std::is_pointer<A>::value //returns true if A is a pointer
std::is_reference<A>::value // returns true if A is a reference
std::is_polymorphic<A>::value //returns true if A is a non-union class with at least 1 virtual function
std::is_abstract<A>::value //returns true if A is a non-union class with a pure virtual function
std::remove_cv<A>::type //returns A with any const or volitile or both modifiers removed
std::remove_const<A>::type //returns A with any const modifiers removed
std::remove_volatile<A>::type //returns A with any volitile modifiers removed
std::remove_reference<A>::type //returns A with any reference removed
std::remove_pointer<A>::type //returns A with any pointer removed

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <tuple>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::tuple<int, double, std::string> myTuple = std::make_tuple(0,2.0,"hello");
auto value = std::get<0>(myTuple); // Get value at index 0, must be const index
std::tie(myInt, myDouble, std::ignore) = myTuple; // copies from tuple into variables
std::ignore // ignore copying of variable at position
    
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <optional>
///////////////////////////////////////////////////////////////////////////////////////////////////////
    
std::optional<std::string> myOptional = make_optional("str");
std::optional<std::string> myOptional(std::nullopt); // object of no type
myOptional.reset(); // destroys the value
myOptional.value(); // returns a reference to the value
myOptional.has_value(); // whether has a value
myOptional.value_or("empty"); // returns copy of value or default value

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <variant>
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Type-safe union that can hold multiple types, cannot hold references, arrays, or void

std::variant<int, float> myVariant; // can hold int or float
myVariant = 20;                     // assign a value, current type is now int
myVariant.index();                  // returns 0-based index for current type (eg. 0 for int, 1 for float)
std::get<T>(myVariant);             // will throw std::bad_variant_access if asked for wrong current type
std::get_if<T>(&myVariant);         // returns T* if the correct current type

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <random>
///////////////////////////////////////////////////////////////////////////////////////////////////////

srand(time(0));                     //choose a seed
rand()                              // returns int between [0, RAND_MAX]
(rand() % (max - min)) + min;       // [min, max)
(rand() % (max - min + 1)) + min;   // [min, max]

// Distribution
// create one generator per application
std::default_random_engine generator;
std::uniform_int_distribution<int> dist(lower, upper); //integer distribution
std::uniform_real_distribution<float> dist(lower, upper); //real distribution
auto getRand = [&]() ->int { return dist(generator); } //Generates number in the range [lower,upper]
auto getRand = std::bind(dist, generator); //Bind and use as function object

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ctime>
///////////////////////////////////////////////////////////////////////////////////////////////////////
    
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

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <limits>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//minimum negative, maximum positive
char   SCHAR_MIN  SCHAR_MAX  UCHAR_MAX
short  SHRT_MIN   SHRT_MAX   USHRT_MAX
int    INT_MIN    INT_MAX    UINT_MAX
long   LONG_MIN   LONG_MAX   ULONG_MAX

//minimum positive, maximum positive
float  FLT_MIN  FLT_MAX 

std::is_same<float, T>::value //true/false whether types are the same (including constness)
std::remove_const<T>::type //returns the type without const

numeric_limits<int>::min() //mimimum negative for int, minimum positive for float
numeric_limits<int>::max() //maximum positive for int/float
numeric_limits<int>::lowest() //mimimum negative for int/float
numeric_limits<int>::is_signed //whether signed/unsigned
numeric_limits<int>::digits //number of non-signed bits for int, number of digits for float
numeric_limits<int>::has_infinity //whether type can represent infinity
numeric_limits<int>::infinity() //representation of positive infinity if possible
numeric_limits<int>::round_style //returns rounding style used
numeric_limits<float>::epsilon() //floating point error amount

round_toward_zero //if it rounds toward zero.
round_to_nearest //if it rounds to the nearest representable value.
round_toward_infinity //if it rounds toward infinity.
round_toward_neg_infinity //if it rounds toward negative infinity.
round_indeterminate //if the rounding style is indeterminable at compile time.

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cmath>
///////////////////////////////////////////////////////////////////////////////////////////////////////

modf(x, &y) //returns the fractional part of double x and puts integer part in double y
abs(-1); //Gets absolute value for double
fabs(-1); //Gets absolute value for float
pow(2, 8); //finding 2⁸
sqrt(4); //finding square root of 4
ceil(4.3) //returns closest integer rounding up (5)
floor(4.7) //returns closest integer rounding down (4)
round(4.5) //math round- to closest integer up/down with 0.5 going up
cos(angle) //angle in radians
sin(angle) //angle in radians
tan(angle) //angle in radians
acos(x/r) //cosӨ = A/C, returns radians
asin(y/r) //sinӨ = O/C, returns radians
atan(x/y) //tanӨ = O/A, returns radians
atan2(x, y) //calculates tan(x/y), returns radians
_finite(0.0) //returns whether its a valid (not infinite/undefined) double
_chgsign(x) //returns x with its sign reversed
_copysign(x, y) //returns double with magnitude of x and sign of y
copysign(x, y) //returns double with magnitude of x and sign of y

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <sstream> <iostream> <fstream> <iomanip>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//OUTPUT STREAMS
cout << "Value" << 20; //Store values into stream
cout << std::flush; //flushes buffer
cout << std::endl; //flushes buffer and adds \n
cout.put('V'); //Put character into stream

//INPUT STREAMS
cin >> "Value" >> 20; //adds values to stream
cin.ignore(255, '\n') //reads up to 255 characters or up to the next deliminator
cin.peek() //returns next character from input without taking from stream
cin.gcount() //returns the number of characters read by the last unformatted extraction method
cin.putback('\n')
cin.get() //returns type int so you can't concatenate
cin.get(mychar) //gets the next character in the input queue including \0, spaces etc.
getline(cin, myString, 'M') //read line up to deliminator or \r, returns true if not eof

//each reads the line up to 49 characters or the deliminator 
//Failbit set if more characters exist than allocated size or no characters found
cin.get(chararray, 50, 'M') //leaves deliminator in queue, adds \0 to last element
cin.get(chararray, 50); 
cin.getline(chararray, 50, 'M') //discards deliminator, adds \0 to last element
cin.getline(chararray, 50) 

//CHANGING CURSOR POSITION
seekg() //moves the input pointer to a given file location
seekp() //moves the output pointer to a given file location
stream.seekg(0); // go to beginning
stream.seekg(30, ios_base::beg); // 30 bytes beyond the beginning
stream.seekg(-1, ios_base::cur); // back up one byte from current cursor spot
stream.seekg(0, ios_base::end); // go to the end of the file

//STREAM STATES: eofbit, badbit, failbit
cin.eof() //returns true when eofbit set
cin.fail() //returns true if input fails (eofbit or failbit set)
cin.bad() //returns true if input operation failed (badbit set)
cin.good() //returns true if stream can be used
cin.rdstate() //returns the current stream state
cin.clear() //clears all three states
cin.clear(ios_base::eofbit) //clears badbit and failbit
cin.exceptions(ios_base::badbit | ios_base::eofbit) //results in ios_base::failure thrown if either badbit or eofbit are set

//STRINGSTREAM [OUTPUT STREAM]
ostringstream sstream;
stringstream sstream;
sstream.str() //return std::string of stream
sstream.seekp(0) //set stream pointer back to 0
sstream.str("") //reset stream

//OFSTREAM [OUTPUT STREAM]
ofstream myFile("file.txt") /*or*/ ofstream myFile;
myFile.open("file.txt", filemode);
myFile.is_open() //return true if file has opened
myfile.sync(); //make sure all info has been written to file
myfile.close(); //closing flushes the data ensuring none is lost
myfile.clear(); //clear any flags set

//IFSTREAM [INPUT STREAM]
ifstream myFile("file.txt") /*or*/ ifstream myFile;
myFile.open("file.txt", filemode);
myFile.is_open() //return true if file has opened
myfile.sync(); //make sure all info has been written to file
myfile.close(); //closing flushes the data ensuring none is lost
myfile.clear(); //clear any flags set
myFile.read(myArray, x) //reads x characters from the file and places them in the array

//Read whole file into string
std::ifstream file(m_filepath, std::ios::in|std::ios::ate|std::ios::_Nocreate);
const int size = static_cast<int>(file.tellg());
file.seekg(0, std::ios::beg);
myText.clear();
myText.resize(size);
file.read(&myText[0], myText.size());
    
//FSTREAM [INPUT/OUTPUT STREAM]
fstream myFile; //requires filemode
myFile.open("file.txt", ios_base::in|ios_base::out|ios_base::binary)

//STREAM MANIPULATION
// Use in stream or stream.setf to set flags, strea.unsetf to remove flags
std::setw(3)              //for next item only expands item to fill the width with the fill character
std::setfill('*')         //changes the fill character from the default " "
std::boolalpha            //converts 1 or 0 to true or false
std::skipws               //enable skipping of whitespace
std::showpoint            //shows decimal point no matter what
std::showpos              //use + for positive numbers
std::hex                  //shows numbers as hex
std::dec                  //shows number as decimal
std::nouppercase          //don't use uppercase
std::uppercase            //use uppercase
std::fixed                //use fixed-point notation
std::scientific           //uses scientific notation
std::setprecision(2)      //will show trailing 0s, precision is number of digits to right
std::right                //adjust output to right
std::left                 //adjust output to right

//FILEMODES
std::ios_base::in         //Open file for reading.
std::ios_base::out        //Open file for writing.
std::ios_base::ate        //Seek to end-of-file upon opening file.
std::ios_base::app        //Append to end-of-file.
std::ios_base::trunc      //Wipe file if it exists.
std::ios_base::binary     //open/create as Binary file
std::ios_base::_Nocreate  //don't create file
std::ios_base::_Noreplace //only create new files, existing will not open

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef _Longlong int64_t;
typedef _ULonglong uint64_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <regex>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::regex pattern {R"(\w{2}?)"}
std::smatch matches;
std::regex_search(line, matches, pattern); // returns true if match found

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <future> <thread> <mutex>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//THREADING
//Moves arguments into thread
//Will terminate if out of scope
std::thread thread(&MyFunction, arg1, arg2);
thread.join(); //stop thread once function call is finished

//MUTEX
//Move-only object
std::mutex myMutex;
std::lock_guard<std::mutex> lock(myMutex); //scoped locking/unlocking
if(myMutex.try_lock()) //doesn't block if can't lock
{
    myMutex.unlock()
}

//FUTURE
//Do function asynchronously and hold return type once finished
//Will terminate if out of scope
std::future<T> handle = std::async(std::launch::async, &MyFunction);
handle.wait() //blocks until result is available
handle.get()  //blocks until result is available and returns result

//FUTURE POLICIES
std::launch::async     //A new thread is launched to execute the task asynchronously 
std::launch::deferred  //Task is executed on the calling thread the first time its result is requested 
