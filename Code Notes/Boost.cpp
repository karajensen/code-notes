///////////////////////////////////////////////////////////////////////////
//BOOST LIBRARIES
///////////////////////////////////////////////////////////////////////////

//BOOST NON-COPYABLE
//inherits privately, gives compiler error if copying occurs
class MyClass : boost::noncopyable 

//BOOST OPTIONAL
boost::optional<double> myOptional;
myOptional.is_initialized(); //check if has a value assigned
myOptional = 2.0; //assign a value
myOptional = boost::none; //assign no value

//BOOST DATE/TIME
boost::gregorian::date today = boost::gregorian::day_clock::universal_day();
std::string today = boost::gregorian::to_iso_string(today);

//BOOST THREADING
boost::mutex::scoped_lock lock(myMutex);

///////////////////////////////////////////////////////////////////////////
//CONTAINERS
///////////////////////////////////////////////////////////////////////////

//ITERATE OVER CONTAINERS
BOOST_FOREACH(Shader_Ptr shader, m_shaders)

//FILL A STD::VECTOR
boost::assign::list_of<T>("one")("two"); //returns std::vector<T>

//BOOST BIMAP
boost::bimap<a, b> myBiMap = boost::assign::list_of<boost::bimap<a, b>::relation>(objA1, objB1)(objA2, objB2);
auto it = myBiMap.left.find(objA1); // returns itr for objA1 or myBiMap.left.end() where itr->second is value
auto it = myBiMap.right.find(objB1); // returns itr for objB1 or myBiMap.right.end() where itr->second is value

///////////////////////////////////////////////////////////////////////////
//STRINGS
///////////////////////////////////////////////////////////////////////////

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

boost::algorithm::to_lower(str);                     //all lower case
boost::algorithm::to_upper(str);                     //all upper case
boost::algorithm::trim(str);                         //removes spaces at start/end of string
boost::algorithm::trim_copy(str);                    //removes spaces at start/end of string
boost::algorithm::trim_left_copy(str);               //removes spaces at start of string
boost::algorithm::trim_right_copy(str);              //removes spaces at end of string
boost::algorithm::trim_left_if(str,is_any_of("0"));  //removes 0 from start
boost::algorithm::trim_right_if(str,is_any_of("0")); //removes 0 from end
boost::algorithm::iequals(str1,str2);                //case-sensitive comparison
boost::algorithm::istarts_with(str,"text");          //returns true or false
boost::algorithm::iends_with(str, ".exe");           //returns true or false
boost::algorithm::replace_first(str,"one","three");  //replaces first one with three
boost::algorithm::replace_last(str,"one","three");   //replaces last one with three
boost::algorithm::replace_all(str,"one","three");    //replaces all one with three
boost::algorithm::erase_all(str, " ");               //erase all spaces      
boost::algorithm::erase_head(str, 6);                //erase first 6 characters
boost::algorithm::icontains(str, "substring")

//BOOST REGEX
boost::regex_replace("OneTwo", boost::regex("One"), "Three") //returns "ThreeTwo"
boost::regex_replace(str, boost::regex("//.*?\n"), "") //returns str removing all between // to \n
boost::regex_replace(line, boost::regex("//.*?$"), ""); //return str removing all between // to end of string

//BOOST LEXICAL CAST
str = boost::lexical_cast<string>(number);   //number->string
number = boost::lexical_cast<int>(str);      //string->number
number = boost::lexical_cast<unsigned int>("-1") //returns a large number!!

catch(const boost::bad_lexical_cast& e)
{
    LogError(e.what());
}

//BOOST SPLIT REGEX
//will split when str is found; does not keep deliminator in vector
//if deliminator is at start or end of text may have empty entry in vector
#include "boost/algorithm/string/regex.hpp"
std::vector<std::string> components;
boost::algorithm::split_regex(components, text, boost::regex(str))

//BOOST SPLIT
//will split string when a,b or c is found; keeps deliminator in vector
std::vector<std::string> components;
boost::split(components, text, boost::is_any_of("abc"), boost::token_compress_on);

//BOOST TOKENIZER
std::string removedSeperator;
boost::char_separator<char> seperator("|");
boost::tokenizer<boost::char_separator<char>> tokens(line, seperator);
for (const auto& token : tokens) 
{
    removedSeperator += token;
}

//////////////////////////////////////////////////////////////////////////////
//NUMBERS
//////////////////////////////////////////////////////////////////////////////

#include <boost/numeric/conversion/converter.hpp>

//CONVERTING NUMBERS
typedef boost::numeric::converter<int,double> Double2Int;
int x = Double2Int::convert(2.0);
assert(x == 2);

//NUMBER BOUNDS/OVERFLOW
try
{
    double m = boost::numeric::bounds<double>::highest();
    int z = Double2Int::convert(m);
}
catch (boost::numeric::positive_overflow const &)
{
    //overflow error!
}

//////////////////////////////////////////////////////////////////////////////
//SMART POINTERS
//////////////////////////////////////////////////////////////////////////////

#include "boost/smart_ptr.hpp"

// SCOPED POINTER
// Single ownership, no transfer
boost::scoped_ptr<MyClass> scopedPtr(new MyClass());
scopedPtr.reset(new MyClass());

// SHARED POINTER
// Shared ownership, destroys when reference = 0
boost::shared_ptr<MyClass> sharedPtr(new MyClass());
sharedPtr.reset(new MyClass());

// WEAK POINTER
// observer of shared pointer; goes null when shared_ptr reference = 0
boost::weak_ptr<MyClass> weakPtr(sharedPtr);

//////////////////////////////////////////////////////////////////////////////
//THREADING
//////////////////////////////////////////////////////////////////////////////

// Automatically locks/unlocks thread in scope
boost::mutex::scoped_lock lock(myMutex);

// Doesn't wait if mutex is already locked
if(myMutex.try_lock())
{
    myMutex.unlock();
}

// Creating a new thread
void MyFunction(int a1, double a2){ /*do something*/ }
boost::thread myThread(&MyFunction, 10, 2.0); // Does copy (use pointers for objects)
myThread.join();


//////////////////////////////////////////////////////////////////////////////
//FILESYSTEM
//////////////////////////////////////////////////////////////////////////////

#include <boost/filesystem.hpp>

filesystem::path filePath("MyFile.txt");
filesystem::exists(filePath)
filesystem::remove(prevPath);          // Removing files
filesystem::create_directory(dir)      // Create directory
filesystem::rename(filePath,prevPath); // Renaming files
filesystem::copy_file("a.txt","b.txt") // Copy files from path a to path b

// Recurse backwards through parent directories
filesystem::path directory("MyParentFolder/MyFolder");
while(!directory.string().empty())
{
    std::string filepath = directory.string() + "/myFile.txt";
    if(filesystem::exists(filepath))
    {
        return filepath;
    }
    directory = directory.parent_path();
}

//////////////////////////////////////////////////////////////////////////////
//INPUT/OUTPUT
//////////////////////////////////////////////////////////////////////////////

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

<root>
    <two>
        <three>3</three>
        <four x="0.0"></four>
    </two>
    <two>
        <three>0</three>
        <four x="4.0"></four>
    </two>
</root>

property_tree::ptree tree;
tree.size();                  // Size of direction children for a property tree
tree.count("X");              // Number of direct children named X
tree.get_child("X");          // Gets first direct child named X or throws if doesn't exist
tree.get_child_optional("X"); // returns boost::optional<const ptree&> of first direct child

//=======================================================================
//READING XML
//=======================================================================

filesystem::path myPath("myfile.xml");
property_tree::ptree tree;

// Throws const boost::filesystem::filesystem_error& if fails
property_tree::xml_parser::read_xml(myPath.generic_string(), tree, property_tree::xml_parser::trim_whitespace);
property_tree::ptree& root = tree.get_child("root");

// Creates a pair where first is name and second is ptree
BOOST_FOREACH(boost::property_tree::ptree::value_type const& value, root)
{
    if (boost::iequals(type.first, "two"))
    {
        //throws const boost::bad_lexical_cast& e, use e.what() to get more info
        double x = lexical_cast<double>(type.second.get_child("three").data());
        double x = lexical_cast<double>(type.second.get_child("four.<xmlattr>.x").data());

        //throws const boost::property_tree::ptree_bad_data&, use e.what() to get more info
        double x = type.second.get<double>("three").data();
        double x = type.second.get<double>("four.<xmlattr>.x").data();
    }
}

// Gets the correct value depending on if it exists in the tree
template<typename T> 
T GetValue(boost::property_tree::ptree::iterator& it, T defaultValue, char* node)
{
    int count = it->second.count(node);
    if(count > 0)
    {
        if(count > 1)
        {
            Logger::LogInfo(std::string("Warning: node ") + node + " is duplicated");
        }
        return boost::lexical_cast<T>(it->second.get_child(node).data());
    }
    return defaultValue;
}

//=======================================================================
//WRITING XML
//=======================================================================

// Adding nodes: Nodes added inside to outside
ptree root;
ptree one;
ptree two;
two.add("three",5);
one.add_child("two",two);
root.add_child("one",one);

// Writing property tree to xml
property_tree::xml_parser::xml_writer_settings<char> settings('\t', 1);
property_tree::write_xml(filePath.generic_string(), root, std::locale(), settings);

//////////////////////////////////////////////////////////////////////////////
//BOOST GEOMETRY
//////////////////////////////////////////////////////////////////////////////

#include <boost/polygon/polygon.hpp>

// Only supports int
typedef boost::polygon::point_data<int> point;
typedef boost::polygon::polygon_set_data<int> polygon_set;
typedef boost::polygon::polygon_data<int> polygon_data;
typedef std::vector<polygon_data> polygon_container;
using namespace boost::polygon::operators; // required for operator overloads

// CREATE A POLYGON SET
polygon_container polygons;
std::vector<point> points;
points.push_back(point(0,1));
points.push_back(point(2,3));
points.push_back(point(3,4));
points.push_back(point(0,1)); // requires first point again to end shape
polygon_data polygon;
boost::polygon::set_points(polygon, points.begin(), points.end());
polygons.push_back(polygon); // doesn't clean polygon
polygons += polygon; // cleans polygon (removes intersections etc.) while adding
polygon_set mySet = polygons;  // set container of polygons
mySet.get(polygons);   // retrieve container of polygons

// OBTAIN POINTS FROM POLYGON CONTAINER
for each(const polygon_data& polygon in polygons)
{
    // Don't obtain the duplicate last point
    for(auto itr = polygon.begin(); itr != polygon.end()-1; ++itr)
    {
        const int x = itr->get(boost::polygon::HORIZONTAL);
        const int z = itr->get(boost::polygon::VERTICAL);
    }
}

// FUNCTIONS
// polys can either be polygon_container or polygon_set
mySet = polys1 - polys2;     // boolean SUBTRACT (difference)
mySet = polys1 | polys2;     // boolean OR (union)
mySet = polys1 & polys2;     // boolean AND (intersection)
mySet = polys1 ^ polys2;     // boolean XOR (disjoint-union)
equivalence(polys1, polys2)  // whether two sets equal
area(polys)                  // returns enclosed area of polygon