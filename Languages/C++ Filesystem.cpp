/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STREAMS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
BUFFER
• Bloack of memory for storage/transfer of information
• Flushed when endl, when full or when specified
• Controls rate of stream of bytes to/from buffer

BITMASK TYPES    
• OPENMODE: bitmask type for setting the file mode
• FMTFLAGS: Setting the formatting for the stream
• IOSTATE: A stream state contained in a cout/cin object
           eofbit  = Is set to 1 if end-of-file reached.
           badbit  = Is set to 1 if the stream has file read error
           failbit = Is set to 1 if an input operation failed to read/write expected characters

IOSTREAM
• Creates 8 stream objects (four narrow/four wide character streams)
  CIN/WCIN
  COUT/WCOUT
  CERR/WCERR (error stream unbuffered)
  CLOG/WCLOG (error stream)

FILESTREAM
• Redirects the input/output streams to either use a file instead of console
• This doesn't affect CERR or CLOG unless changed.

OSTREAM CLASS
• translates data as binary bit patterns to an output stream of char bytes
• ostream & operator<<(type); returns reference back to the ostream object
• all methods return ostream type allowing concatenation (cout.put(1).put(1))
• cout << "one" << endl; "one" sent to buffer, returns cout. 
• Endl reached, buffer flushes, inserts \n, no cout returned.

ISTREAM CLASS
• translates data as char from the input stream into binary bit patterns
• istream & operator>>(type &); returns reference back to the istream object
• all methods return istream type allowing concatenation

BINARY FILES
• Smaller, take up less room
• No hidden conversions; written in computer binary language
• More accurate as no conversion/round-off errors for numbers
• Risky as different computers have different internal representation
**************************************************************************************************************/

#include <sstream> 
#include <iostream> 
#include <fstream> 
#include <iomanip>

// OUTPUT STREAMS
cout << "Value" << 20; // Store values into stream
cout << std::flush; // flushes buffer
cout << std::endl; // flushes buffer and adds \n
cout.put('V'); // Put character into stream

// INPUT STREAMS
cin >> "Value" >> 20; // adds values to stream
cin.ignore(255, '\n') // reads up to 255 characters or up to the next deliminator
cin.peek() // returns next character from input without taking from stream
cin.gcount() // returns the number of characters read by the last unformatted extraction method
cin.putback('\n')
cin.get() // returns type int so you can't concatenate
cin.get(mychar) // gets the next character in the input queue including \0, spaces etc.
getline(cin, myString, 'M') // read line up to deliminator or \r, returns true if not eof

// each reads the line up to 49 characters or the deliminator 
// Failbit set if more characters exist than allocated size or no characters found
cin.get(chararray, 50, 'M') // leaves deliminator in queue, adds \0 to last element
cin.get(chararray, 50); 
cin.getline(chararray, 50, 'M') // discards deliminator, adds \0 to last element
cin.getline(chararray, 50) 

// CHANGING CURSOR POSITION
seekg() // moves the input pointer to a given file location
seekp() // moves the output pointer to a given file location
stream.seekg(0); // go to beginning
stream.seekg(30, ios_base::beg); // 30 bytes beyond the beginning
stream.seekg(-1, ios_base::cur); // back up one byte from current cursor spot
stream.seekg(0, ios_base::end); // go to the end of the file

// STREAM STATES: eofbit, badbit, failbit
cin.eof() // returns true when eofbit set
cin.fail() // returns true if input fails (eofbit or failbit set)
cin.bad() // returns true if input operation failed (badbit set)
cin.good() // returns true if stream can be used
cin.rdstate() // returns the current stream state
cin.clear() // clears all three states
cin.clear(ios_base::eofbit) // clears badbit and failbit
cin.exceptions(ios_base::badbit | ios_base::eofbit) // results in ios_base::failure thrown if either badbit or eofbit are set

// STRINGSTREAM [OUTPUT STREAM]
ostringstream sstream;
stringstream sstream;
sstream.str() // return std::string of stream
sstream.seekp(0) // set stream pointer back to 0
sstream.str("") // clear stream
sstream.clear() // clear flags
sstream.rdbuf()->in_avail() // whether stream is empty
sstream.rdbuf() // Returns a pointer to the internal string

// OFSTREAM [OUTPUT STREAM]
ofstream myFile("file.txt") /*or*/ ofstream myFile;
myFile.open("file.txt", filemode);
myFile.is_open() // return true if file has opened
myfile.sync(); // make sure all info has been written to file
myfile.close(); // closing flushes the data ensuring none is lost
myfile.clear(); // clear any flags set

// IFSTREAM [INPUT STREAM]
ifstream myFile("file.txt") /*or*/ ifstream myFile;
myFile.open("file.txt", filemode);
myFile.is_open() // return true if file has opened
myfile.sync(); // make sure all info has been written to file
myfile.close(); // closing flushes the data ensuring none is lost
myfile.clear(); // clear any flags set
myFile.read(myArray, x) // reads x characters from the file and places them in the array

// Read whole file into string
std::ifstream file(m_filepath, std::ios::in|std::ios::ate|std::ios::_Nocreate);
const int size = static_cast<int>(file.tellg());
file.seekg(0, std::ios::beg);
myText.clear();
myText.resize(size);
file.read(&myText[0], myText.size());
    
// FSTREAM [INPUT/OUTPUT STREAM]
fstream myFile; //requires filemode
myFile.open("file.txt", ios_base::in|ios_base::out|ios_base::binary)

// STREAM MANIPULATION
// Use in stream or stream.setf to set flags, strea.unsetf to remove flags
std::setw(3)              // for next item only expands item to fill the width with the fill character
std::setfill('*')         // changes the fill character from the default " "
std::boolalpha            // converts 1 or 0 to true or false
std::skipws               // enable skipping of whitespace
std::showpoint            // shows decimal point no matter what
std::showpos              // use + for positive numbers
std::hex                  // shows numbers as hex
std::dec                  // shows number as decimal
std::nouppercase          // don't use uppercase
std::uppercase            // use uppercase
std::fixed                // use fixed-point notation
std::scientific           // uses scientific notation
std::setprecision(2)      // will show trailing 0s, precision is number of digits to right
std::right                // adjust output to right
std::left                 // adjust output to right

// FILEMODES
std::ios_base::in         // Open file for reading.
std::ios_base::out        // Open file for writing.
std::ios_base::ate        // Seek to end-of-file upon opening file.
std::ios_base::app        // Append to end-of-file.
std::ios_base::trunc      // Wipe file if it exists.
std::ios_base::binary     // open/create as Binary file
std::ios_base::_Nocreate  // don't create file
std::ios_base::_Noreplace // only create new files, existing will not open
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FILESYSTEM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Paths /tmp/test.txt or /tmp/dir (without closing /)- \tmp\test.txt supported only by windows
• Dot and dotdot supported
• Can be relative or absolute
• Normalizing path uses native formatting (windows \)
*************************************************************************************************************/

current_path()              // Yields the path of the current working directory 
temp_directory_path()       // Yields the path for temporary files

std::filesystem::path p;    // Can be dir or file
p = p / "data.txt"          // Combine dir with file
p.string()
p.is_absolute()             // Whether absolute or relative
p.is_relative()
p.has_filename()
p.has_extension()
p.has_parent_path()
p.filename()
p.extension()
p.parent_path()
p.wstring()
p.native()
p.replace_filename(name)
p.replace_extension(ext)
p.clear()
p.lexically_normal()        // Normalize path
p.empty()                   // Whether path p is empty
is_empty(p)                 // True if inside file at path p is empty
is_directory(p)
is_regular_file(p)
exists(p)
equivalent(p1, p2)
last_write_time(p)          // returns the timepoint of the last modification or write access of the file
current_path(p)             // Sets the path of the current working directory to p
file_size(p)                // In Bytes
space(p)                    // Yields information about the disk space available at path p 
  
// STATUS
auto status = status(p)
status.type()               // returns file_type enum
status.permissions()        // returns perms enum 
  
// CREATE DIRECTORY
// Creates all missing dirs in path, returns false if already exists,
create_directory(p)         // Creates single directory, throws filesystem_error if fails
create_directory(p, ec);    // Creates single directory, std::error_code instead of throwing
create_directories(p)       // Creates all missing dirs in path, throws filesystem_error if fails
create_directories(p, ec)   // Creates all missing dirs in path, std::error_code instead of throwing

// REMOVE DIRECTORY
remove(p)
  
// ITERATE PATHS
for (const auto& itr : std::filesystem::directory_iterator(p)) { std::cout << itr.path(); }
for (const auto& itr : std::filesystem::recursive_directory_iterator(p)) { std::cout << itr.path(); }
for (auto part : p) {}        // iterate parts of path, part is also std::filesystem::path  

// COPY PATHS
copy(from, to)                // Copies a file of any type 
copy(from, to, options)       // Copies a file of any type with options 
copy_file(from, to)           // Copies a file (but not directory or symbolic link) 
copy_file(from, to, options)  // Copies a file with options

// ERROR CODES
std::error_code ec
ec.message()
ec == std::errc::read_only_file_system
