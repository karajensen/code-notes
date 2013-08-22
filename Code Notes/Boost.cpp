///////////////////////////////////////////////////////////////////////////
//BOOST LIBRARIES
///////////////////////////////////////////////////////////////////////////

//PREVENT COPYING OF CLASSES
//inherits privately, gives compiler error if copying occurs
class MyClass : boost::noncopyable 

//OBJECT WITH OPTIONAL NONE
boost::optional<double> myOptional;
myOptional.is_initialized(); //check if has a value assigned
myOptional = 2.0; //assign a value
myOptional = boost::none; //assign no value

//BOOST DATE/TIME
boost::gregorian::date today = boost::gregorian::day_clock::universal_day();
std::string today = boost::gregorian::to_iso_string(today);

///////////////////////////////////////////////////////////////////////////
//CONTAINERS
///////////////////////////////////////////////////////////////////////////

//ITERATE OVER CONTAINERS
BOOST_FOREACH(Shader_Ptr shader, m_shaders)

//FILL A STD::VECTOR
boost::assign::list_of<T>("one")("two"); //returns std::vector<T>

///////////////////////////////////////////////////////////////////////////
//STRINGS
///////////////////////////////////////////////////////////////////////////

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

boost::algorithm::to_lower(str);                     //all lower case
boost::algorithm::to_upper(str);                     //all upper case
boost::algorithm::trim(str);                         //removes spaces at start/end of string
boost::algorithm::iequals(str1,str2);                //case-sensitive comparison
boost::algorithm::istarts_with(str,"text");          //returns true or false
boost::algorithm::iends_with(str, ".exe");           //returns true or false
boost::algorithm::trim_left_if(str,is_any_of("0"));  //removes 0 from start
boost::algorithm::trim_right_if(str,is_any_of("0")); //removes 0 from end
boost::algorithm::replace_first(str,"one","three");  //replaces first one with three
boost::algorithm::replace_last(str,"one","three");   //replaces last one with three
boost::algorithm::replace_all(str,"one","three");    //replaces all one with three
boost::algorithm::erase_all(str, " ");               //erase all spaces      
boost::algorithm::erase_head(str, 6);                //erase first 6 characters

//BOOST REGEX
boost::regex_replace("OneTwo", boost::regex("One"), "Three") //returns "ThreeTwo"

//BOOST LEXICAL CAST
str = boost::lexical_cast<string>(number);   //number->string
number = boost::lexical_cast<int>(str);      //string->number
number = boost::lexical_cast<unsigned int>("-1") //returns a large number!!

catch(const boost::bad_lexical_cast& e)
{
    LogError(e.what());
}

//BOOST SPLIT
std::vector<std::string> components;
boost::split(components, line, boost::is_any_of("|"));

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
//FILESYSTEM
//////////////////////////////////////////////////////////////////////////////

#include <boost/filesystem.hpp>

filesystem::path filePath("MyFile.txt");
filesystem::exists(filePath)

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

// Copy files
boost::filesystem::copy_file("CopyFromPath.txt","CopyToPath.txt")

// Removing files
filesystem::remove(prevPath);

// Create directory
filesystem::create_directory(dir)

// Renaming files
filesystem::rename(filePath,prevPath);

//////////////////////////////////////////////////////////////////////////////
//INPUT/OUTPUT
//////////////////////////////////////////////////////////////////////////////

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

<one>
    <two>
        <three>5</three>
    </two>
</one>

//=======================================================================
//READING XML
//=======================================================================

filesystem::path filePath("Meshes.xml");
if(filesystem::exists(filePath))
{
    try
    {
        property_tree::ptree tree;
        property_tree::xml_parser::read_xml(filePath.generic_string(), tree, 
            boost::property_tree::xml_parser::trim_whitespace);

        property_tree::ptree& root = tree.get_child("Meshes");
        property_tree::ptree::iterator it;
        for(it = root.begin(); it != root.end(); ++it)
        {
            std::string name = it->second.get_child("Name").data();

            //throws const boost::bad_lexical_cast& e
            int number = lexical_cast<int>(it->second.get_child("Number").data()); 
            
            //throws const boost::property_tree::ptree_bad_data
            int number = it->second.get<int>("Number");
        }
    }
    catch(const boost::filesystem::filesystem_error& e)
    {
        LogError(e.what());
        return false;
    }
}
else
{
    LogError("Could not find " + sm_assetsPath + "Meshes.xml");
    return false;
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

tree.size(); // Size of direction children for a property tree
tree.count("X"); // NUmber of direct children called X

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
