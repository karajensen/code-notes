//////////////////////////////////////////////////////////////////////////////  
//MAXSCRIPT
//////////////////////////////////////////////////////////////////////////////  
/*
*************************************************************************
VERY IMPORTANT NOTES:
    MAXSCRIPT VARS AUTO-CONVERT DURING ASSIGNMENT
    MAXSCRIPT VARS/FUNCTIONS ARE NOT CASE SENSITIVE!
    MAXSCRIPT ARRAY INDEXES ARE 1-BASED, NOT 0-BASED
    MAXSCRIPT ARRAYS CAN HOLD MULTIPLE TYPES (IE. INT/BOOL/STRINGS...)
*************************************************************************

SCRIPT TYPES:
Maxscript             .ms       standard/utility/plugins
Macroscript           .mcr      generated from user operations
Encrypted Maxscript   .mse      encrypted maxscript or macroscripts

INSTALLING SCRIPTS:
.\Scripts               general scripts
.\Scripts\Startup       auto-load scripts when Max is launched
.\ui\macroscripts       auto-load macros
.\plugins               auto-loads plugins
.\stdplugs\stdscripts   scripts containing functions; auto-loads first
                        Maxscript extentions stored here
CREATING SCRIPTS:
Use Maxscript Listener (F11)
SHIFT-ENTER: performs selected line operations
Maxscript->Preferences->Tick Use Fast Name Look Up for cached node names

MULTILINE: 
Maxscript doesn't use ;
torus radius1:10 \
      pos:[0,0,20]

COMMENTS: 
--this is a comment
/*this is also a comment*/

//////////////////////////////////////////////////////////////////////////////  
//VARIABLES
//////////////////////////////////////////////////////////////////////////////  

//Any variables declared in Listener are Global unless surrounded by ()
//Any variables declared outside () are Global
global myInt
local myInt

//----------------------------------------------------------------------
//BASIC TYPES
//----------------------------------------------------------------------

//Variables are created without a type; Max auto assigns a type
//Variables implicitly converted with assignment
x = 10;     //x is declared as an int
x = 4.0;    //x is converted to a float
x = "hello" //x is connverted to a string
x = true    //x is converted to a bool

//Variable names are not case-sensitive
temp == Temp == TEMP

//Explicitly casting variables
myString = myFloat as string
myFloat = myString as float
myInt = myString as integer

//COLORS
newColor = color 255 128 255     //color r g b
newColor = color 255 128 255 255 //color r g b a

//----------------------------------------------------------------------
//MAXSCRIPT REFERENCES
//----------------------------------------------------------------------
//Use C++ reference syntax; generates C++ pointer behaviour
//Unless specified, all values are passed by-val
//Except properties of an object which are always passed by-ref

&myInt  //gets address of variable

//FUNCTION DEFINITION
fn MyFunction &x () 

//PASSING TO FUNCTION
MyFunction &myInt

//BY-REF PASSING OF OBJECT PROPERTIES
pnt = point3 0.0 0.0 0.0
fn MyFunction mypoint               //passing by-val
(
    mypoint.x = 2.0                 //affects pnt directly
    mypoint = point3 1.0 3.0 5.0    //creates new var and returns it
)                                   //not assigns it to pnt as by-val
//result is: 
//pnt = 2.0 0.0 0.0
//return value = 1.0 3.0 5.0

//----------------------------------------------------------------------
//STRINGS
//----------------------------------------------------------------------

myString = "hello" + "again"
mySubString = findString myString "hell"   //find a substring

//REPLACE
//one = string to insert
//1 = position to start replacing, 1-based index in string
//3 = how many letters to delete including position before inserting
//two letters = string to insert into
//output: "one letters"
myString = replace "one" 1 3 "two letters"



//----------------------------------------------------------------------
//ARRAYS [1-BASED]
//----------------------------------------------------------------------
//Arrays can be of one type or hold multiple types
//It's valid for an array to have strings and ints and bools etc.
//Some functions will fail if more than one type is in array (ie. sort)

intArray = #()           
intArray = #(1,2,4,2,5)
objArray = #(myBox, mySphere, myCylinder)

intArray[3]             //returns 1 from the array
intArray[1] = 0         //changes 1 to 0
intArray.count          //size of the array

append intArray (3)         //add 3 to end of array, resizes dynamically
delete intArray 2           //deletes the second item, resizes dynamically
joint intArray floatArray   //joints two arrays or collection and array
findItem intArray 1         //returns index to value in array or 0
sort intArray               //sorts array in ascending order
isDeleted myArray[1]        //true if value is referencing a deleted object

//Iterating over an array
for i = 1 to intArray.count do
(
    intArray[i] = 0
)

//All arrays declared are C++ references; change a and b changess
a = b = #(1,2,3)

//PRINTING ARRAYS
options.PrintAllElements = true  //set to true otherwise only first 20 printed
for i in myArray do print i

//MULTIDIMENSIONAL ARRAYS
myArray = #(myIntArray, myFloatArray)
myArray[1][2]   //accesses myIntArry[2]

//COPYING ARRAYS
myArray = copy myArray2 #nomap

//SORTING ARRAYS
qsort myArray mySortFunction
fn mySortFunction &v1 &v2 =
(
	case of
	(
		(v1.z < v2.z) : -1
		(v1.z > v2.z) : 1
		default: 0
	)
)

//DELETING ARRAYS
//No 'clear' for arrays, make equal new array and call garbage
myArray = #()
gc light:true

//----------------------------------------------------------------------
//COLLECTIONS
//----------------------------------------------------------------------

//stores all objects of type teapot in scene into collection
//any collections auto-updated when the scene is updated
myCollection = $teapot*    

myArray = myCollection as array    //move objects in collection into array
myArray = myCollection             //arrays aren't auto-updated

//----------------------------------------------------------------------
//STRUCTURES
//----------------------------------------------------------------------

//Note: Last member (function/var) doesn't have , all others do
struct myStruct
(
    name = "hello", //assign default value
    age,
    height
)
struct myStruct
(
    var1,
    fn myMemberFunction = 
    ( 
        return var 
    ),
    fn myMemberFunction2 = 
    (  
        //do something else
    ),
    var2 = myMemberFunction2()  //assign default value of var2 with function    
)

var = myStruct()
var = myStruct name:"hello" age:12 height:4.0
var.name = "hello"

//----------------------------------------------------------------------
//VECTORS
//----------------------------------------------------------------------
myPoint = point3 1.0 23.0 43.3

myPoint = cross v1 v2
myFloat = dot v1 v2
myPoint = normalize myPoint


//----------------------------------------------------------------------
//MATRICES
//----------------------------------------------------------------------



//////////////////////////////////////////////////////////////////////////////  
//LOGIC OPERATIONS
//////////////////////////////////////////////////////////////////////////////  

if(not i == 0) then ()
if(i != 0) then ()
if(x == 0 and y == 0) then ()
if(x == 0 or y == 0) then ()
if((x == 0) or (y == 0) or (z == 0) then ()

//IF-THEN-ELSE STATEMENT
if i == 0 then
(
    //do something
)
else if i == 2 then
(
    //do stuff
)
else
(
    //do something else
)

//SHORT FOR STATEMENT
for i = 1 to 3 do   //includes doing 3
    //do something  

//FOR STATEMENT
for i = 1 to 3 do //includes doing 3
(
    //do something
)
for i = 1 to 10 by 2 do
(
    //do something
)

//FOR-IN STATEMENT
for i in myCollection do
(
    i.pos.x = 0
)

//CASE STATEMENTS
case myCounter of
(
    1: print ("The counter is: " + (myCounter as string))
    2:  (
            //do something
        )
    default: messageBox "Failed"
)

//WHILE LOOP
while i < 5
(
    i = i + 1
)

//DO-WHILE
do
(
    i = i + 1
) while i < 5

//////////////////////////////////////////////////////////////////////////////  
//FUNCTIONS
//////////////////////////////////////////////////////////////////////////////  

//Function names are not case sensitive
Myfunction() == MYFUNCTION() == MyFunction()

//Calling a function without arguments
MyFunction()

//Calling a function with arguments (needs to be in order)
MyFunction 2.0 "somestring"

//Calling a function with arguments (in any order)
MyFunction arg3:20.0 arg1:24.0 arg2:43.2

//CREATING FUNCTIONS
fn MyFunction obj =   //obj is an argument
(
    if superclassof obj == geometryClass then
    (
        obj.wirecolor = [255, 0, 0]

        //RETURN VALUES
        value = 4.0*2.0  //return value is last statement executed
        /*or*/
        4.0*2.0          //doesn't have to be assignment to return
        /*or*/
        return 4.0*2.0  //better to explicitly say return
    )
)

//DEFAULT VALUES
fn MyFunction myText:"Some default value" myInt:4 ()

//CALLING FUNCTIONS
MyFunction obj  


//////////////////////////////////////////////////////////////////////////////  
//OPERATIONS
//////////////////////////////////////////////////////////////////////////////  

//PRINTING
messagebox "MyText" //prints a string in messagebox on screen
print myVar
for i in myArray do print i

//LOADING FILES
LoadMaxFile "c:/scenes/somefile.max" //return true if success

//CALLBACKS
registerTimeCallback myFunction     //called when time changes
unRegisterTimeCallback myFunction

//RANDOM
seed 30
myInt = random 10 48            //lowest to highest including
myFloat = random 10.0 48.0      //lowest to highest including
myPoint3 = random [0.3,0.4,0.0] [4.2,5.2,5.3]

//SPEEDING UP SCRIPTS
disableSceneRedraw()
suspendEditing()
undo off
/*do stuff*/
enableSceneRedraw()
resumeEditing()
redrawViews()

//GARBAGE COLLECT
gc light:true

//CONSOLE COMMANDS
DOSCommand "cd F:" 