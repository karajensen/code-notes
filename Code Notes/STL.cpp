///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <random>
///////////////////////////////////////////////////////////////////////////////////////////////////////

srand(time(0)); //choose a seed

//USING RAND()
int r = rand() % MAX_RANGE + 1; //for 1 to MAX_RANGE (not including maxrange) 
int r = rand() % MAX_RANGE; //for 0 to MAX_RANGE (not including maxrange)

//USING DISTRIBUTION
//create one generator per application
std::default_random_engine generator;
std::uniform_int_distribution<int> dist(lower, upper); //integer distribution
std::uniform_real_distribution<float> dist(lower, upper); //real distribution

auto getRand = [&]() ->int { return dist(generator); } //Generates number in the range [lower,upper]
auto getRand = std::bind(dist, generator); //Bind and use as function object

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

numeric_limits<int>::min() //mimimum negative for int, minimum positive for float
numeric_limits<int>::max() //maximum positive for int/float
numeric_limits<int>::lowest() //mimimum negative for int/float
numeric_limits<int>::is_signed //whether signed/unsigned
numeric_limits<int>::digits //number of non-signed bits for int, number of digits for float
numeric_limits<int>::has_infinity //whether type can represent infinity
numeric_limits<int>::infinity() //representation of positive infinity if possible
numeric_limits<int>::round_style //returns rounding style used

round_toward_zero //if it rounds toward zero.
round_to_nearest //if it rounds to the nearest representable value.
round_toward_infinity //if it rounds toward infinity.
round_toward_neg_infinity //if it rounds toward negative infinity.
round_indeterminate //if the rounding style is indeterminable at compile time.

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <type_traits>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::is_base_of<A,B>::value //returns true if A is a base class of B
std::is_assignable<A,B>::value //returns true if A==B is possible
std::is_move_assignable<A>::value //returns true if A has a move assignment operator
std::is_move_constructible<A>::value //returns true if A has a move constructor
std::has_virtual_destructor<A>::value //returns true if A has a virtual destructor

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cmath>
///////////////////////////////////////////////////////////////////////////////////////////////////////

abs(-1); //Gets absolute value for double
fabs(-1); //Gets absolute value for float
pow(2, 8); //finding 2⁸
sqrt(4); //finding square root of 4
ceil(4.3) //returns closest integer rounding up (5)
floor(4.7) //returns closest integer rounding down (4)
round(4.5) //math round- to closest integer up/down with 0.5 going up (not in VS yet)
copysign(x, y) //returns double with magnitude of x and sign of y (not in VS yet)
cos(angle) //angle in radians
sin(angle) //angle in radians
tan(angle) //angle in radians
acos(x/r) //cosƟ = A/C, returns radians
asin(y/r) //sinƟ = O/C, returns radians
atan(x/y) //tanƟ = O/A, returns radians
atan2(x, y) //calculates tan(x/y), returns radians

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <sstream>
#include <iostream>
#include <fstream>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------
//FILE STREAMS
//-------------------------------------------------------------------------------
ios_base::in  //Open file for reading.
ios_base::out  //Open file for writing.
ios_base::ate  //Seek to end-of-file upon opening file.
ios_base::app  //Append to end-of-file.
ios_base::trunc  //Wipe file if it exists.
ios_base::binary  //open/create as Binary file
ios_base::_Nocreate //don't create file
ios_base::_Noreplace //only create new files, existing will not open

myfile.sync(); //make sure all info has been written to file
myfile.close(); //closing flushes the data ensuring none is lost
myfile.clear(); //clear any flags set

//-------------------------------------------------------------------------------
//OUTPUT STREAMS
//-------------------------------------------------------------------------------
cout << "Value" << 20; //Store values into stream
cout << std::flush; //flushes buffer
cout << std::endl; //flushes buffer and adds \n
cout.put('V'); //Put character into stream

//-------------------------------------------------------------------------------
//INPUT STREAMS
//-------------------------------------------------------------------------------
cin >> "Value" >> 20; //adds values to stream
cin.ignore(255, '\n') //reads up to 255 characters or up to the next deliminator
cin.peek() //returns next character from input without taking from stream
cin.gcount() //returns the number of characters read by the last unformatted extraction method
cin.putback('\n')
cin.get() //returns type int so you can't concatenate
cin.get(mychar) //gets the next character in the input queue including \0, spaces etc.
getline(cin, myString, 'M') //read line up to deliminator or string::npos, discard deliminator

//each reads the line up to 49 characters or the deliminator 
//Failbit set if more characters exist than allocated size or no characters found
cin.get(chararray, 50, 'M') //leaves deliminator in queue, adds \0 to last element
cin.get(chararray, 50); 
cin.getline(chararray, 50, 'M') //discards deliminator, adds \0 to last element
cin.getline(chararray, 50) 

//-------------------------------------------------------------------------------
//CHANGING CURSOR POSITION
//-------------------------------------------------------------------------------
seekg() //moves the input pointer to a given file location
seekp() //moves the output pointer to a given file location
stream.seekg(0); // go to beginning
stream.seekg(30, ios_base::beg); // 30 bytes beyond the beginning
stream.seekg(-1, ios_base::cur); // back up one byte from current cursor spot
stream.seekg(0, ios_base::end); // go to the end of the file

//-------------------------------------------------------------------------------
//STREAM STATES: eofbit, badbit, failbit
//-------------------------------------------------------------------------------
cin.eof() //returns true when eofbit set
cin.fail() //returns true if input fails (eofbit or failbit set)
cin.bad() //returns true if input operation failed (badbit set)
cin.good() //returns true if stream can be used
cin.rdstate() //returns the current stream state
cin.clear() //clears all three states
cin.clear(ios_base::eofbit) //clears badbit and failbit
cin.exceptions(ios_base::badbit | ios_base::eofbit) //results in ios_base::failure thrown if either badbit or eofbit are set

//-------------------------------------------------------------------------------
//STRINGSTREAM [OUTPUT STREAM]
//-------------------------------------------------------------------------------
ostringstream sstream;
stringstream sstream;
sstream.str() //return std::string of stream
sstream.seekp(0) //set stream pointer back to 0
sstream.str("") //reset stream

//-------------------------------------------------------------------------------
//OFSTREAM [OUTPUT STREAM]
//-------------------------------------------------------------------------------
ofstream myFile("file.txt") /*or*/ ofstream myFile;
myFile.open("file.txt", filemode);
myFile.is_open() //return true if file has opened

//-------------------------------------------------------------------------------
//IFSTREAM [INPUT STREAM]
//-------------------------------------------------------------------------------
ifstream myFile("file.txt") /*or*/ ifstream myFile;
myFile.open("file.txt", filemode);
myFile.is_open() //return true if file has opened
myFile.read(myArray, x) //reads x characters from the file and places them in the array

//-------------------------------------------------------------------------------
//FSTREAM [INPUT/OUTPUT STREAM]
//-------------------------------------------------------------------------------
fstream myFile; //requires filemode
myFile.open("file.txt", ios_base::in|ios_base::out|ios_base::binary)

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iomanip>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//sets width to 3, affects next item displayed only, will expand width if too small to fit item, uses fill character
cout.width(3) /*or*/ setw(3) 

//changes the fill character from the default " "
cout.fill('*') /*or*/ setfill('*') 

//SETTING/UNSETTING STREAM FLAGS
cout.unsetf(ios_base::boolalpha); //sets bit back to 0 for boolalpha
cout.setf(ios_base::boolalpha); //converts 1 or 0 to true or false when using expression such as x<3
cout.setf(ios::skipws); //enable skipping of whitespace
cout.setf(ios_base::showpoint); //shows decimal point no matter what
cout.setf(ios_base::showpos); //use + for positive numbers
cout.setf(ios_base::uppercase); //Use uppercase letters for hex output/E notation
cout.setf(ios_base::showbase); //Use C++ base prefixes (0,0x) for decimal/hex
cout.setf(ios_base::adjustfield, ios_base::left); //adjust output to left
cout.setf(ios_base::adjustfield, ios_base::right); //adjust output to right

//HEX/DECIMAL
cout.setf(ios_base::basefield, ios_base::dec)
cout.setf(ios_base::basefield, ios_base::hex)

//FIXED/SCIENTIFIC NOTATION
cout.setf(ios_base::floatfield, ios_base::fixed); //uses fixed-point notation
cout.setf(ios_base::floatfield, ios_base::scientific); //uses scientific notation

//PRECISION
setprecision(2) //will show trailing 0s, precision is number of digits to right
cout.precision(2); //of decimal point (float) use showpoint to show trailing 0s on ints
                                        
//STANDARD NOTATION 
cout.unsetf(ios_base::floatfield);
setprecision(2) //sets number of sig digits to 2 from standard 6, no trailing 0s
cout.precision(2); //(0.0234 -> 0.023, 23.4 -> 23, 323 -> 323, 323.3 -> 3.2e002)                          

//SAVING SETTINGS
ios_base::fmtflags initialState = cout.setf(ios::left, ios::adjustfield); //save old settings into fmtflags old
cout.setf(initialState); //restore original settings

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ctime>
///////////////////////////////////////////////////////////////////////////////////////////////////////

CLOCKS_PER_SEC //const that equals the number of ticks per second
clock_t //data type used for time in ticks
clock() //returns clock ticks passed since program started
time() //returns current time

//TIMER DELAY LOOP
clock_t delay = NoOfSeconds * CLOCKS_PER_SEC; 
clock_t start = clock(); //set the start of the time
while ((clock() - start) < delay) // calculate the difference
    continue;

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cstring>
///////////////////////////////////////////////////////////////////////////////////////////////////////
//works on character arrays and string temp/literals

strlen(cstring) //gives the length of the string array minus the null character
strcpy(cstring1, cstring2) //copy cstring2 to cstring1
strncpy(cstring1, cstring2, 3) //copy 3 members of cstring2 to cstring1, must do cstring1[4] = '\0' after
strcat(cstring1, cstring2) //append contents of cstring2 to cstring1
strcmp(cstring1, cstring2) //returns 0 if same, < 0 if first < second, > 0 value if first > second
strchr(cstring1, ch) //returns address of first occurance of char chosen, or nullptr if not there
atoi("3") //converts cstring to int
atof("3.0") //converts cstring to float

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
#include <exception>
///////////////////////////////////////////////////////////////////////////////////////////////////////

assert(x == 0); //will break if x != 0
throw("Message goes here");
exit(EXIT_FAILURE);

//TRY-CATCH BLOCK
try 
{ 
    myFunction();
} 
catch(std::exception& e)
{
    cout << e.what() << endl;
}
catch (...) //catches anything
{
}

//EXCEPTION THROWING
void myFunction(); //can throw anything
void myFunction() throw(const char*, std::exception&); //can throw string or std::exception
void myFunction() throw(); //DOESN'T THROW EXCEPTION

//UNEXPECTED EXPECTION: 
//Occurs when exception thrown that function doesn't expect to be thrown
//calls unexpected() -> terminate() -> abort()
set_unexpected(MyUnexpectedFn);
void MyUnexpectedFn()
{
    throw; //original exception is thrown again
    throw std::bad_exception(); //bad_exception is thrown
}

//UNCAUGHT EXCEPTION: Occurs when no matching handlers
//calls terminate() -> abort()
set_terminate(MyQuitFn);
void MyQuitFn()
{
}

//CREATING CUSTOM EXCEPTION
class MyClass: public std::exception
{
public:
    virtual const char* what() const override 
    { 
        return "bad arguments";
    } 
};
try 
{
    throw MyClass();
}
catch(std::exception & e)
{
    cout << e.what() << endl;
}
