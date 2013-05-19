///////////////////////////////////////////////////////////////////////////////////////////////////////
//MELSCRIPT
///////////////////////////////////////////////////////////////////////////////////////////////////////

GUI -------->  MEL ENGINE --------> DEPENDENCY GRAPH
Melscript      script executed      all data/scene-series of connected nodes

//COMMAND LINE: Single MEL code
//SCRIPT EDITOR: Multiline MEL code (highlight code to keep in editor when executing)
//EXPRESSION EDITOR: Code run at particluar events
//**********************************************************************
//NOTE: All proc/vars made in script editor become automatically global
//        To fix, enclose body in {}, procs can't be helped
//        Pathnames can't have spaces in them
//**********************************************************************

\n        //newline
\\        //slash
\t        //tab
\r        //return
$        //variable
%        //modulus


//EXECUTING
currentTime -query;            //command executed but nothing returned
`currentTime -query`;        //command executed and results returned
eval("currentTime -query"); //command as string executed and results returned

//LOADING SCRIPTS
source myscript.mel;

//HELP
help sphere;  //prints flags avaliable to command

//GENERAL FLAGS
-ch          //construction history on/off
-query      //query mode
-fullPath //name of node with namespaces

//PRINT/TRACE
print("Hello world\n" + $myInt);
print($myInt);
print($myString);
print($myStringArray);
trace($myInt);    //prints filename/line number of script issued the call

//ERROR CONTROL
warning -showLineNumber true "warning message";
error -showLineNumber true "error message";    //execute of script stops and exception is called

//EXISTS
if(`exists myscript`){...} //for myscript.mel;
if(`objExists "objName"`){...}
if(attributeExists("attrName","ObjName")){...}

//DETERMINING TYPES
whatIs "$myInt"; //returns string "int variable"
whatIs sphere;     //returns string "command"
whatIs myProc;
whatIs myscript;
objType "$mynode";

//VIEWPORTS
playbackOptions -view "all"; //view all viewports
playbackOptions -view "active"; //view active viewport
upAxis -q -axis;  //returns current up axis
setUpAxis "z";      //set the current up axis

//START EXTERNAL PROGRAM
system("start pathname.exe");

//ANGLES
rad_to_deg(myRad);
deg_to_rad(myDeg);

//-------------------------------------------------------------------------------
//CONDITIONS
//-------------------------------------------------------------------------------

//IF STATEMENT
if(x < y) {}
else if (x < y) {}
else {}

//shorthand version
if($a > 1) $score = 10;
else $score = 20;
$score = ($a > 1) ? 10 : 20;

//SWITCH
switch($a)
{
    case 1 :
        break;
    default:
        break;
}

//-------------------------------------------------------------------------------
//LOOPS
//-------------------------------------------------------------------------------

for($i = 0; $i < 10; $i++) {}
for($each in $myArray) {}
while($i = 0) {}
do{}while($i = 0)

continue; //skip the rest of the loop to the next iteration
break; //cancel the whole loop


//-------------------------------------------------------------------------------
//PROCEEDURES
//-------------------------------------------------------------------------------
//defined as local to script unless specified
//name global uniquely; last compiled version overwrites others
proc myProc() { return; }
global proc myProc() {}

proc float myProc(int $procVar) { return 3.4; }
proc int[] myProc(float $myfloatArray[]) { return $myIntArray; }



///////////////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLES
///////////////////////////////////////////////////////////////////////////////////////////////////////


//PREDEFINED VARIABLES
frame    //integer storing current frame number
time    //no of seconds (default settings) past since playback
deg/rad //used after number only

//CONVERSIONS
int $myInt = $myString;
int $myInt = $myFloat;


//---------------------------------------------------------------------
//GLOBAL VARIABLES (CONST!)
//---------------------------------------------------------------------
//can be used by any code, name uniquely as last compiled version overwrites others
//Lasts for lifetime of Maya session
//Not assigned gives 0, can't be assigned dynamic variable

global int $myInt; //Initialise at top of code
{
    global int $myInt;      //Reinitialize to use in any blocks of code; once reinitialised code is skipped
    global int $myInt=0;  //Assignment during reinitialising only occurs when proc is compiled/changed
    $myInt = 0;              //If not reinitialized Maya creates new local variable of type int
}

string $envVars[] = `env`; //gives list of all current global variables

//---------------------------------------------------------------------
//VARIABLES
//---------------------------------------------------------------------
//Local to script/block unless specified

float &myFloat; //default val: 0
int $myInt; //default val: 0
int $myInt = true; //can have yes,on,false,off,no

$counter = $counter + 1; /*or*/ &counter++;

//-----------------------------------------------------------------
//ARRAYS
//-----------------------------------------------------------------
//dynamically adds elements for you
int $myIntArray[]; //initialised with ""
int $myIntArray[5];
int $myIntArray[] = {0,1,2,3,4};
vector $myVecArray[2] = { <<x,y,z>>, <<x,y,z>> };

//accessing from array
$myIntArray[0] = 10;

//adding to array 
$myIntArray[size($myIntArray)] = 10; //assinging a value adds to array if index doesn't exist
$myIntArray[2] = 10;  //if index used doesn't exist, resizes adds 0s up until new index {0,0,10}

//removing from array
int $tempArray[];
for($i = 0; $i < size($myIntArray); $i++)
{
    if($i == 2) //copy all but a particular value
        continue;
    else
        $tempArray[size($tempArray)] = $myIntArray[$i];
}
clear($myIntArray); //removes all values from array
$myIntArray = $tempArray;

//-----------------------------------------------------------------
//MATRICES
//-----------------------------------------------------------------
//not dynamic: needs values to initialise and can't be resized
//only hold float values and needs dimensions to be set
//To get object's matrices, see Xform
matrix $myMatrix[$rows][$cols] = <<    0.0, 1.0, 0.0 ;    
                                    1.0, 1.0, 1.0 ;
                                    0.0, 0.0, 1.0 >>;
$m + $n        //matrix addition
$m * $n        //matrix multiplication (make sure they conform!)


//-----------------------------------------------------------------
//VECTORS
//-----------------------------------------------------------------
vector $vector = <<x,y,z>>; //default: 0,0,0
int $vectorX = ($vector.x); //using component of vector must be enclosed in brackets

//ASSIGNING VALUES
$myVector = <<2,$myVector.y,$myVector.z>>; 
$myVec = $myInt //gives <<$myInt,$myInt$,myInt>>

//MOVE OBJECT USING A VECTOR
move -absolute ($myVector.x)($myVector.y)($myVector.z);

//NORMALIZE VECTOR
$myVec = unit($myVec);

//ANGLE
angle($vec1,$vec2);
angleBetween -v1 1 0 0 -v2 0 1 0;

//MAGNITUDE OF VECTOR
float $myfloat = $myVec    //gives magniture of vector
mag(vector)                //gives magniture of vector

//DOT PRODUCT
$dot = $myVec1 * $myVec2;
dot($myVec1,$myVec2);

//CROSS PRODUCT
$myVec1 = $myVec2 ^ $myVec3;
cross($myVec1,$myVec2);



///////////////////////////////////////////////////////////////////////////////////////////////////////
//STRINGS
///////////////////////////////////////////////////////////////////////////////////////////////////////

string $myString;    //assigned default value of ""
string $myStringArray[];
int $NoOfCharas = size($myString);

substituteAllString($myString,"a","b");    //in myString replace all a with b, returns string
match "[0-9]+" $myString;    //finds all numbers in myString and returns them as a string (if none returns "")

//----------------------------------------------------------------------
//SPLITTING A STRING
//----------------------------------------------------------------------
//TOKENIZE: splits string up using token into substrings storing in string list

string $mySubStrings[]; //will have "A","B","C","D" stored
$subStringNumber = `tokenize "A-B--C-D" "-" $mySubStrings; //Number returns is 4

string $mySubStrings[]; //will have "A","B","C" stored
$subStringNumber = `tokenize "A B C" $mySubStrings; //Number returns is 3

//----------------------------------------------------------------------
//SEARCHING A STRING
//----------------------------------------------------------------------
//MATCH: Returns portion of string that matches to given string or "" if no match

match "this" "this is a test"; //returns "this"
match "a*b*" "aaabbcc"; //returns "aaabb"
match "a*b*" "bbcc"; //returns "bb", doesnt have to have value if using *
match "a+b+" "abbcc"; //returns "abb" 
match "a+b+" "bbcc"; //needs 'a', will fail
match "^this" "this is a test"; //test for word at start of string, returns "this"
match "test$" "this is a test"; //test for word at end of string, returns "test"
match "[0-9]+" "testing01252a"; //returns 01252
match "(abc)+" "123abcabc456"; //returns abcabc



///////////////////////////////////////////////////////////////////////////////////////////////////////
//RENDERING/HYPERSHADE
///////////////////////////////////////////////////////////////////////////////////////////////////////

//SETTING/GETTING RENDERER
//Types: "mayaSoftware" "mayaHardware" "mentalRay"
defaultRenderGlobals.currentRenderer;                                
string &renderer = `getAttr defaultRenderGlobals.currentRenderer`;              //store current renderer
setAttr defaultRenderGlobals.currentRenderer -type "string" "mayaHardware";      //change renderer

//HYPERSHADE
hyperShade -assign initialShadingGroup; //assign default lambert shader to selected

//select shader attached to geometry
hyperShade -smn; //select material node of geometry
string $sel[] = `ls -sl`;
select -cl;
string $sel2[] = `hyperShade -lun $sel[0]`; //select connected nodes to shader
select $sel2;

//CREATING SHADERS
string $shaderName = `shadingNode -asShader blinn`;

//VERTEX COLOR
setAttr ($objName + ".displayColors") 1; //allow vertex color to be displayed
polyColorPerVertex -rgb $r $g $b; //rgb as floats will color selected vertices


