/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// MAXSCRIPT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

/*************************************************************************************************************
VERY IMPORTANT NOTES:
    MAXSCRIPT VARS AUTO-CONVERT DURING ASSIGNMENT
    MAXSCRIPT VARS/FUNCTIONS ARE NOT CASE SENSITIVE!
    MAXSCRIPT ARRAY INDEXES ARE 1-BASED, NOT 0-BASED
    MAXSCRIPT ARRAYS CAN HOLD MULTIPLE TYPES (IE. INT/BOOL/STRINGS...)

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
*************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// VARIABLES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

//Any variables declared in Listener are Global unless surrounded by ()
//Any variables declared outside () are Global
global myInt
local myInt

//===============================================================================================================
// BASIC TYPES
//===============================================================================================================

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

//===============================================================================================================
// MAXSCRIPT REFERENCES
//===============================================================================================================
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

//===============================================================================================================
// STRINGS
//===============================================================================================================

myString = "hello" + "again"
mySubString = findString myString "hell"   //find a substring

//REPLACE
//one = string to insert
//1 = position to start replacing, 1-based index in string
//3 = how many letters to delete including position before inserting
//two letters = string to insert into
//output: "one letters"
myString = replace "one" 1 3 "two letters"

//===============================================================================================================
// ARRAYS [1-BASED]
//===============================================================================================================
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

//===============================================================================================================
// COLLECTIONS
//===============================================================================================================

//stores all objects of type teapot in scene into collection
//any collections auto-updated when the scene is updated
myCollection = $teapot*    

myArray = myCollection as array    //move objects in collection into array
myArray = myCollection             //arrays aren't auto-updated

//===============================================================================================================
// STRUCTURES
//===============================================================================================================

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

//===============================================================================================================
// VECTORS
//===============================================================================================================
myPoint = point3 1.0 23.0 43.3

myPoint = cross v1 v2
myFloat = dot v1 v2
myPoint = normalize myPoint

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// LOGIC OPERATIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// OPERATIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

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
   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// SELECTION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

$.name              //name of currently selected object
myCollection = $*   //put all objects in scene into collection

//PICKING OBJECTS FROM SCENE
//Set function that returns bool in filter
fn MySphereFilter obj = ( ClassOf obj == Sphere ) //returns bool if sphere
mySel = PickObject message:"Pick any sphere" filter:MySphereFilter

//PICKING POINTS FROM SCENE
//3D snaps need to be turned on
myPoint = pickPoint snap:#3D

//ITERATING OVER SELECTED OBJECTS
for i in myCollection do
(
    i.pos.x += 1.0
)

//TESTING OBJECTS SELECTED
if (selectedObj == undefined) then
    messagebox "Please select a valid object"
else if (isDeleted selectedObj) then
    messagebox "Please select a valid object"
else
( /*do stuff*/ )

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// OBJECTS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//CREATING OBJECTS
mybox = box()
mysphere = sphere()

//OBJECT RTTI
classOf obj == Sphere                   //class type for obj
superClassOf obj == geometryClass       //base class for obj

//DISPLAYING PROPERTIES
showProperties mybox
myBoxProps = getPropNames myBox         //returns array of all property names

//OBJECT PROPERTIES
obj.isSelected = true
obj.isHidden = false
obj.name = "nodeName"
obj.pos = [10, 15, 20]
obj.pos.x = 20
obj.rotation = ang //where ang = eulerAngles x y z in deg
obj.rotation.x_rotation = 30  //in deg
obj.scale = [10, 15, 20]
obj.wirecolor = [255, 255, 255]
obj.wirecolor.r = 128
obj.length = 40    
obj.width = 20
obj.height = 10
obj.radius = 2.0
obj.pivot           //position of pivot
obj.center          //center of object
obj.material        //material assigned to object

//OBJECT COORDINATE SYSTEMS
in coordsys local rotate obj (quat 45 y_axis) //do transform in local
set coordsys local  //set all transformations to local
set coordsys world

//COPYING OBJECTS
mybox1 = copy mybox2  //copies everything including properties
mybox1 = instance mybox2 //creates instance of box2
mybox1 = reference mybox2 //creates reference; makes child to mybox2

//ADDING MODIFIERS
addmodifier mybox (bend())  //add bend modifier to box
addmodifier mybox (bend()) before:2 //put at second position in stack
deletemodifier mybox 1 //delete the modifier stored at top of stack

//DELETING OBJECTS
delete myObject

//OBJECT METHODS
hide obj
move obj [10.0, 2.0, 4.0]
scale obj [10.0, 2.0, 4.0]
rotate obj (quat 45 y_axis)
about obj1 rotate obj2 (quat 45 y_axis) //use obj1's pivot point as origin

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// EDITABLE MESHES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//CONVERT NODE TO EDITABLE MESH
myMesh = convertToMesh myBox

//CREATE A MESH
mymesh = mesh vertices:vertArray faces:indices

//MESH FUNCTIONS
vertNumber = getNumVerts myMesh //get number of verts in mesh

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// LIGHTS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//CREATE A LIGHT
mylight = directionalLight()
mylight = omnilight pos:[0,0,0] castshadows:on

//LIGHT PROPERTIES
mylight.rgb             //light color
mylight.excludeList     //nodes excluded from light
mylight.projectorMap    //can assign texturemap to allow patterns in light

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// SHADERS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//MATERIAL EDITOR
meditmaterials[2]   //access slot 2 in material editor, only has 24 slots

//MATERIALS
myshader = standard()
myshader = checker()

//MATERIAL PROPERTIES
myshader.diffusemap

//TEXTURE MAPS
mymap = marble Vein_Width:0.1 size:12

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// CAMERAS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//Free camera
mycam = freeCamera()

//Target camera; camera will always point at target
mytarget = targetObject pos:[0,0,0]
mycam = targetCamera pos:[0,10,2] target:mytarget

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// ANIMATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

/*************************************************************************************************************
PROPERTIES: 
translate, radius etc. that an object has
CONTROLLER: 
controls the properties through curves, add keys to this
controllers can be set values above min/max for properties
Controller types: Linear, Bezier and TCB
*************************************************************************************************************/

//ANIMATE ON
//auto-sets a key at frame 0 
animate on
(
    at time 50 mysphere.radius = 10 /*or*/
    at time 50 myspehre.contoller.value = 10
    at time 100 mysphere.radius = 40
)

//ADDING KEYS
//doesn't auto-set key at frame 0
addNewKey (mysphere.radius.controller) 20   //adds a key at frame 20

//DELETING KEYS
deleteKeys (mysphere.radius.controller)

//GETTING KEYS
mysphere.radius.keys[2].value = 30

//KEY TANGENTS
mysphere.radius.keys[2].inTangentType = #fast
mysphere.radius.keys[2].outTangentType = #slow
mysphere.radius.keys[0].outTangentType = #linear
   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// MAXSCRIPT FORMS / UI
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

//===============================================================================================================
// CREATING A FLOATING WINDOW
//===============================================================================================================
if((myRollout != undefined) and (myRollout.isdisplayed)) do
(destroyDialog myRollout)

rollout myRollout "Name"
(
    //FORM ELEMENTS
    spinner mySpinner "Enter value: "
    button myButton "Button text"
    pickbutton myPicker "Pick object"

    //FORM LOCAL VARS
    local myVar

    //FORM FUNCTIONS
    fn myFunction =
    (
        //do something with local vars
    )

    //FORM EVENT HANDLERS
    on myButton pressed do  //event handler for myButton
    (
        value = mySpinner.value
        messagebox(value)
    )
    on myPicker picked obj do //obj is object picked
    (
        myVar += 10.0
        obj.pos.x += 10.0
    )
)
createDialog myRollout \    //name of form to create
             200 \          //width of form
             50             //height of form

//===============================================================================================================
// CREATING A SECTION IN THE UTILITIES PANEL
//===============================================================================================================
utility myUtility "Name"
(
    //Form events
    spinner mySpinner "Enter value: "
    button myButton "Button text"

    //Form local variables
    local myVar

    //Form event handlers
    on myButton pressed do  //event handler for myButton
    (
        myVar += 10.0
        value = mySpinner.value
        messagebox(value as string)
    )
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// UI ELEMENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

//UI EVENT HANDLERS
on myElement pressed do () //when element is pressed
on myElement changed value do () //when element's value is changed
on myElement picked obj do ()  //when object is selected in scene
on myElement selected do () //when item in list/combo is selected
on myElement rickclick do () //when element is right clicked

//GROUPING ELEMENTS IN A PANEL
group "group description"
(
    //UI elements
)

//ELEMENT PROPERTIES
//All can be accessed through element: myElement.enabled = true
range:[1,10,3]  //from 1 to 10 with a default value of 3
type:#integer   //value type
enabled:false   //enable/disabled
fieldwidth: 40

//===============================================================================================================
// ELEMENT TYPES
//===============================================================================================================

//SPINNER (value with up/down arrows)
spinner mySpinner "Enter value: "

//BUTTON
button myButton "Button text"

//LABEL
label myLabel "Text"

//PROGRESS BAR
progressBar myProgress value:0  //from 0-100

//PICKBUTTON 
//allows select object in scene
pickbutton myPickButton "Text" autoDisplay:true //display name of picked obj

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// OPEN/SAVE DIALOGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

myFileName = getOpenFileName caption:"select a file"
                             filename:"test.txt"
                             types:"Text(*.txt)|*.txt|All(*.*)|*.*|"

myFileName = getSaveFileName caption:"Save your file"
                             filename:"test.txt"
                             types:"Text(*.txt)|*.txt|All(*.*)|*.*|"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// FILES/INPUT/OUTPUT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

myFile = openFile "c:\\mypath"
myFile = createFile "c:\\mypath"
close myFile

//===============================================================================================================
// READING FROM FILES
//===============================================================================================================
readLine myFile
readChar myFile 2   //read two characters
while NOT eof myFile do readLine myFile     //read till end of file

//USING TAGS
skipToString myFile "$$MyTag" //looks from current pointer position
myValue = readValue myFile  //read value at tag
seek myFile 0   //move back to start if needed

//FILE POINTER
seek myFile 6
filePos myFile  //returns position pointer is at

//===============================================================================================================
// WRITING TO FILES
//===============================================================================================================

format "My Text %" myValue to:myFile    //similar to printf
format "My\n Text % %" myValue1 myValue2 to:myFile 

//===============================================================================================================
// WORKING WITH FILES
//===============================================================================================================

fileList = getFiles "c:\\*.max" //get all .max files in specific folder
directoryList = getDirectories "c:\\*"   //get array of all directions at path

fileList.count //returns number of files found

//Create directory
makeDir "c:\\myNewDir"

//Delete a file
deleteFile "c:\\myFile.txt"

//Rename a file
renameFile "c:\\myFile.txt" "c:\\renamedFile.txt"

//Copy a file
copyFile "c:\\myFile.txt" "c:\\copiedFile.txt"

//Delete a directory
DOSCommand "rd \"C:\MyDirectory\""

sysInfo.windowsdir  //windows install directory
sysInfo.systemdir   //windows system directory
sysInfo.tempdir     //windows temp directory
#startupScripts     //maxscript startup scripts directory
#scene              //3ds max scene directory
#maxroot            //main 3ds max executable directory
#matlib             //materials library directory
#scripts            //scripts directory
#image              //images directory
#ui                 //user interfaces directory
#userscripts        //user scripts directory
#usericons          //user icons directory

//Project path
mypath = pathConfig.getCurrentProjectFolder()

//===============================================================================================================
// IMPORT/EXPORTING
//===============================================================================================================

//List of import plugins
importerPlugin.classes

//Import a file; no prompt skips dialog windows
importFile "c:\\myFile.xxx" #noPrompt using:myPlugin

//Export a file
exportFile  "c:\\myFile.xxx" #noPrompt using:myPlugin
