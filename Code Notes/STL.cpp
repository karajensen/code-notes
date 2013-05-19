///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <random>
///////////////////////////////////////////////////////////////////////////////////////////////////////

srand(time(0)); //choose a seed

//USING RAND()
int r = rand() % MAX_RANGE + 1; //for 1 to MAX_RANGE (not including maxrange) 
int r = rand() % MAX_RANGE; //for 0 to MAX_RANGE (not including maxrange)

//USING DISTRIBUTION
std::default_random_engine generator;
std::uniform_int_distribution<int> dist(lower, upper); //integer distribution
std::uniform_real_distribution<float> dist(lower, upper); //real distribution

auto getRand = [&]() ->int { return dist(generator); } //Generates number in the range [lower,upper]
auto getRand = std::bind(dist, generator); //Bind and use as function object

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <sstream>
///////////////////////////////////////////////////////////////////////////////////////////////////////
    
//converting number to string
std::stringstream s;
s << 800;
string temp = s.str();

//clearing stream
s.seekp(0);
s.str("");


///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//==================================================================================================
//OUTPUT
//==================================================================================================
cout << 'H' //displays int value of char
cout.put('H') //displays H. Can use int/double values which convert to char
cout.write(teststring, n) //display n characters from teststring

//==================================================================================================
//INPUT
//==================================================================================================
cin >> testint; //always use cin.get() afterwards to get rid of the newline character from input queue
cin >> ch;  //doesn't read \0 or spaces, reads first word then stops leaving second word incl space in input queue

cin.ignore(255, '\n') //reads up to 255 characters or up to the next deliminator
cin.peek() //returns next character from input without taking from stream
cin.gcount() //returns the number of characters read by the last unformatted extraction method
cin.putback('\n')

//READING CHARACTERS
cin.get() //returns type int so you can't concatenate
cin.get(mychar) //gets the next character in the input queue including \0, spaces etc.
    
//READING LINES
//each reads the line up to 49 characters or the deliminator 
//Failbit set if more characters exist than allocated size or no characters found
cin.get(chararray2, 50, 'M') //leaves deliminator in queue, adds \0 to last element
cin.get(chararray2, 50); 
cin.getline(chararray2, 50, 'M') //discards deliminator, adds \0 to last element
cin.getline(chararray2, 50) 

//READING STRINGS
getline(cin, myString, 'M') //read line up to deliminator or string::npos, discard deliminator
        

/////STREAM STATES/////
//STATES: eofbit, badbit, failbit

//==================================================================================================
//STREAM STATES
//==================================================================================================
cin.eof() //returns true when eofbit set
cin.fail() //returns true if input fails (eofbit or failbit set)
cin.bad() //returns true if input operation failed (badbit set)
cin.good() //returns true if stream can be used
cin.rdstate() //returns the current stream state
cin.clear() //clears all three states
cin.clear(ios_base::eofbit) //clears badbit and failbit
cin.exceptions(ios_base::badbit | ios_base::eofbit) //results in ios_base::failure thrown if either badbit or eofbit are set

cout << flush; //flushes buffer
cout << endl; //flushes buffer and adds \n

system("cls");   //clear the console
system("pause"); //pause the console


///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <fstream>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//==================================================================================================
//WRITING
//==================================================================================================
ofstream myFile; /*or*/ ofstream myFile("hello.txt")
myFile.open("hello.txt", openmode) //default open mode is ios_base::out | ios_base::trunc
myFile.open(myFileName.c_str())

myfile << "This is a test";

//==================================================================================================
//READING
//==================================================================================================
ifstream myFile; /*or*/ ifstream myFile("hello.txt")
myFile.open("hello.txt", openmode) //default open mode is ios_base::in
myFile.open(myFileName.c_str())

myFile >> ch
myFile.getline(line, 20);
myFile.get();
getline(myFile, myString);

if(!myFile.is_open()) //better to use over !myFile.good due to it testing if opening using innappropriate file mode

myFile.read(gross, 144) //reads 144 characters from the file and places them in the array
myFile.peek() //returns next character from input without taking from stream
myFile.eof() //returns true when EOF
myFile.fail() //returns true if input fails (ie, type mismatch or EOF)
myFile.bad() //returns true if corrupted file or a hardware failure
myFile.good() //returns true if stream can be used

//==================================================================================================
//FILE STREAM
//==================================================================================================

//FILE MODES
ios_base::in  //Open file for reading.
ios_base::out  //Open file for writing.
ios_base::ate  //Seek to end-of-file upon opening file.
ios_base::app  //Append to end-of-file.
ios_base::trunc  //Wipe file if it exists.
ios_base::binary  //Binary file.
ios_base::_Nocreate //don't create file
ios_base::_Noreplace //only create new files, existing will not open

//CLOSING FILES
myfile.sync(); //make sure all info has been written to file
myfile.close(); //closing flushes the data ensuring none is lost
myfile.clear(); //clear any flags set

//BINARY FILES
ofstream myFile = myFile.open("text", ios_base::binary); //must create file as a binary, use as normal file

//BOTH READING/WRITING
fstream myFile = myFile.open("yes.txt", ios_base::in|ios_base::out|ios_base::binary) //NEEDS openmode type!

//CHANGING CURSOR POSITION
seekg() //moves the input pointer to a given file location
seekp() //moves the output pointer to a given file location
myFile.seekg(0); // go to beginning
myFile.seekg(30, ios_base::beg); // 30 bytes beyond the beginning
myFile.seekg(-1, ios_base::cur); // back up one byte from current cursor spot
myFile.seekg(0, ios_base::end); // go to the end of the file


///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iomanip>
///////////////////////////////////////////////////////////////////////////////////////////////////////

cout.width(3) /*or*/ setw(3) //sets width to 3, affects next item displayed ONLY, will expand width if too small to fit item, uses fill character
cout.fill('*') /*or*/ setfill('*') //changes the fill character from the default " "

cout.setf(ios_base::showpoint); //shows decimal point no matter what
cout.setf(ios_base::boolalpha); //converts 1 or 0 to true or false when using expression such as x<3
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
setprecision(2)     //will show trailing 0s, precision is number of digits to right
cout.precision(2);  //of decimal point (float) use showpoint to show trailing 0s on ints
                                        
//STANDARD NOTATION 
cout.unsetf(ios_base::floatfield);
setprecision(2) /*or*/ //sets number of sig digits to 2 from standard 6, no trailing 0s
cout.precision(2);     //(0.0234 -> 0.023, 23.4 -> 23, 323 -> 323, 323.3 -> 3.2e002)                          

//SAVING SETTINGS
ios_base::fmtflags initialState = cout.setf(ios::left, ios::adjustfield); //save old settings into fmtflags old
cout.setf(initialState); //restore original settings

//RESETTING SETTINGS
cout.unsetf(ios_base::boolalpha); //sets bit back to 0 for boolalpha


///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cmath>
///////////////////////////////////////////////////////////////////////////////////////////////////////

abs(-1); //Gets absolute value
pow(2, 8); //finding 2⁸
sqrt(4); //finding square root of 4
atan2(o, a) //calculates tan(o/a)
cos(1);
sin(1);
tan(1);

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ctime>
///////////////////////////////////////////////////////////////////////////////////////////////////////

CLOCKS_PER_SEC //const that equals the number of ticks per second
clock_t //data type used for time in ticks
clock() //returns clock ticks passed since program started
time() //returns current time


///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <climits>
///////////////////////////////////////////////////////////////////////////////////////////////////////

CHAR_BIT //the number of bits in a byte

char   SCHAR_MIN, SCHAR_MAX, UCHAR_MAX
short  SHRT_MIN, SHRT_MAX, USHRT_MAX
int    INT_MIN, INT_MAX, UINT_MAX
long   LONG_MIN, LONG_MAX, ULONG_MAX

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <type_traits>
///////////////////////////////////////////////////////////////////////////////////////////////////////

std::is_base_of<A,B>::value //returns true if A is a base class of B
std::is_assignable<A,B>::value //returns true if A==B is possible
std::is_move_assignable<A>::value //returns true if A has a move assignment operator
std::is_move_constructible<A>::value //returns true if A has a move constructor
std::has_virtual_destructor<A>::value //returns true if A has a virtual destructor

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cstring>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//gives the length of the string array minus the null character
//counts the number of bytes from the first character so if unintialised, 
//can show different length than specified
strlen(chararray2) 
                
//copy chararray2 to chararray1
strcpy(chararray1,chararray2)

//copy 29 members of chararray2 to chararray1
//chararray1[28] = '\0' (remember to section off as a string once copying)
strncpy(chararray1,chararray2, 29) 
    
//append contents of chararray2 to chararray1
strcat(chararray1,chararray2) 
strcat(chararray1,"hello")

//returns 0 if same, - value if second follows first, + value if first follows second
strcmp(chararray1, chararray2) 
strcmp(chararray1, "hello")

//returns address of first occurance of char chosen, or nullptr if not there
strchr("testing", ch)

//converts cstring to number
atoi("testing")
atof("testing")

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cctype>
///////////////////////////////////////////////////////////////////////////////////////////////////////

isalpha(myChar) //letter
isalnum(myChar) //letter or number
isdigit(myChar) //decimal digit (0-9)
isxdigit(myChar) //hexadecimal digit (0-9, A-F)

isspace(myChar) //whitespace characters (newlines, spaces, and tabs)
isblank(myChar) //space or tab
ispunct(myChar) //punctuation character
iscntrl(myChar) //control character

islower(myChar)
isupper(myChar)
tolower(myChar)
toupper(myChar)

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
