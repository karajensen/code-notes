///////////////////////////////////////////////////////////////////////////////////////////////////////
//MELSCRIPT
///////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************************

GUI -------->  MEL ENGINE --------> DEPENDENCY GRAPH
Melscript      script executed      all data/scene-series of connected nodes

COMMAND LINE: Single MEL code
SCRIPT EDITOR: Multiline MEL code (highlight code to keep in editor when executing)
EXPRESSION EDITOR: Code run at particluar events

NOTE: All proc/vars made in script editor become automatically global
      To fix, enclose body in {}, procs can't be helped
      Pathnames can't have spaces in them
***************************************************************************************/

\n  //newline
\\  //slash
\t  //tab
\r  //return
$   //variable
%   //modulus

help sphere; //prints flags avaliable to command
print("Hello world\n" + $myInt);
print($myInt);
print($myString);
print($myStringArray);
trace($myInt);  //prints filename/line number of script issued the call
warning -showLineNumber true "warning message";
error -showLineNumber true "error message";  //execute of script stops and exception is called

//EXECUTING COMMANDS
currentTime -query;         //command executed but nothing returned
`currentTime -query`;       //command executed and results returned
eval("currentTime -query"); //command as string executed and results returned

//DETERMINING TYPES
whatIs "$myInt";   //returns string "int variable"
whatIs sphere;     //returns string "command"
whatIs myProc;
whatIs myscript;

//LOADING SCRIPTS
source myscript.mel;
if(`exists myscript`){...} //for myscript.mel;

//START EXTERNAL PROGRAM
system("start pathname.exe");

//=================================================================================================
// CONDITIONS / LOOPS
//=================================================================================================

//IF STATEMENT
if(x < y) {}
else if (x < y) {}
else {}

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

for($i = 0; $i < 10; $i++) {}
for($each in $myArray) {} // no need for type of 'each'
while($i = 0) {}
do{} while($i = 0)

continue; //skip the rest of the loop to the next iteration
break; //cancel the whole loop

//=================================================================================================
// PROCEEDURES
//=================================================================================================

// defined as local to script unless specified
// name global uniquely; last compiled version overwrites others
proc myProc() { return; }
global proc myProc() {}

proc float myProc(int $procVar) { return 3.4; }
proc int[] myProc(float $myfloatArray[]) { return $myIntArray; }

///////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLES
///////////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBAL VARIABLES (CONST!)
// can be used by any code, name uniquely as last compiled version overwrites others
// Lasts for lifetime of Maya session
// Not assigned gives 0, can't be assigned dynamic variable
global int $myInt; // Initialise at top of code
{
    global int $myInt;      // Reinitialize to use in any blocks of code; once reinitialised code is skipped
    global int $myInt=0;    // Assignment during reinitialising only occurs when proc is compiled/changed
    $myInt = 0;             // If not reinitialized Maya creates new local variable of type int
}
string $envVars[] = `env`; //gives list of all current global variables

// VARIABLES
// Local to script/block unless specified
float &myFloat; //default val: 0
int $myInt; //default val: 0
int $myInt = true; //can have yes,on,false,off,no
$counter = $counter + 1; /*or*/ $counter++;

//CONVERSIONS
int $myInt = $myString;
int $myInt = $myFloat;

//=================================================================================================
// ARRAYS
//=================================================================================================

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

//=================================================================================================
//STRINGS
//=================================================================================================

string $myString;  //assigned default value of ""
string $myStringArray[];
int $NoOfCharas = size($myString);

substituteAllString($myString,"a","b"); //in myString replace all a with b, returns string
match "[0-9]+" $myString;  //finds all numbers in myString and returns them as a string (if none returns "")

//------------------------------------------------------------------------------
//SPLITTING A STRING
//------------------------------------------------------------------------------
//TOKENIZE: splits string up using token into substrings storing in string list
string $mySubStrings[]; //will have "A","B","C","D" stored
$subStringNumber = `tokenize "A-B--C-D" "-" $mySubStrings; //Number returns is 4

string $mySubStrings[]; //will have "A","B","C" stored
$subStringNumber = `tokenize "A B C" $mySubStrings; //Number returns is 3

//------------------------------------------------------------------------------
//SEARCHING A STRING
//------------------------------------------------------------------------------
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
// MATH
///////////////////////////////////////////////////////////////////////////////////////////////////////

rad_to_deg(myRad);
deg_to_rad(myDeg);
sin(angle / time)      // returns between -1,1
cos(angle / time)      // returns between -1,1
noise(time)            // randonly generated noise curve, returns between -1,1
sqrt(amount)
trunc(amount)

//RANDOM GENERATION
seed(3);                     // sets the seed used by random gen
rand(20, 50);                // returns a float between 20 and 50 inclusive
sphrand(x);                  // creates random vector within a sphere with radius x
sphrand(<< 1, 2, 1 >> );     // creates random vector within a skewed sphere 1 unit radius in x etc.

//=================================================================================================
// MATRICES
//=================================================================================================
// not dynamic: needs values to initialise and can't be resized
// only hold float values and needs dimensions to be set
// To get object's matrices, see Xform
matrix $myMatrix[$rows][$cols] = << 0.0, 1.0, 0.0 ;    
                                    1.0, 1.0, 1.0 ;
                                    0.0, 0.0, 1.0 >>;
$m + $n  //matrix addition
$m * $n  //matrix multiplication (make sure they conform!)

//=================================================================================================
// VECTORS
//=================================================================================================
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
// OBJECTS / NODES
///////////////////////////////////////////////////////////////////////////////////////////////////////

sphere;                   //NURBS sphere
polySphere;               //poly sphere
polyCube -n "MyObj";      //poly cube
textCurves - t "mytext";  //text as curves
createNode file;          //create a texture file node
createNode checker;       //create a checker node
createNode script;        //create a custom script node
delete "MyObj";
delete; //currently selected
objType "MyObj";
objExists "MyObj"

//=================================================================================================
//TRANSFORMING OBJECTS
//=================================================================================================

DeleteHistory;
CenterPivot;
duplicate - rr;

//GETTING TRANSFORMATIONS
xform -query -matrix;                    //local matrix as array of float
xform -query -worldSpace -matrix;        //world matrix  as array of float
xform -query -translate;                 //translation in object space
xform -query -worldSpace -translation;   //translation in world space
xform -query -relative -scale;           //scale in object space
xform -query -rotation;                  //rotation in object space
xform -query -rotateAxis;                //rotation orientation

//SETTING TRANSFORMATIONS
xform -translation 2 3 4;                //set position in local space
xform -worldSpace -translation 2 3 4;    //set position in world space
xform -rotation 45 0 0                   //rotation
xform -scale 1.2 0.3 0                   //scaling

//RESETTING
makeIdentity -apply false;               //reset transformation/move object back to default
makeIdentity -apply true;                //reset/freeze transformations

//=================================================================================================
//RELATIONSHIPS
//=================================================================================================

parent "obj1" "ob2";    //parent obj1 to obj2    
parent -world "ob1";    //unparent obj1 (ie. parent to world)    

group -em -n "groupName" -p"parentName"; //create an empty(-em) group, parent under parentName
group -n "groupName" $childList;         //create a group, add children to it
ungroup -world "myObj";                     //remove myObj from the group

reorder -front "myObj";    //move myObj up to front/back of list of siblings

renameSelectionList("NewName"); //renames selection list to NewName incrementing
rename $objName $objNewName;    //note; renaming transform node auto renames shape node

inheritTransform -off "childObject"; //parent's transform doesn't effect specific child

//=================================================================================================
//ATTRIBUTES
//=================================================================================================

//GET ATTRIBUTE
attributeExists "attr" "MyObj"
getAttr "MyObj.attr";
getAttr -time 10 "MyObj.attr";
getAttr transforml.matrix;    //returns array of 16 floats, not matrix

//SET ATTRIBUTE
setAttr "MyObj.attr" 15;

//LIST ATTRIBUTES
listAttr "MyObj";                 //returns array of strings with attribute names
listAttr -userDefined "MyObj";    //list custom attributes only
listAttr -keyable "MyObj";        //list keyable/attributes in channel box only
listAnimatable "myObj";           //lists all attributes that can be animated

//ADD ATTRIBUTES
addAttr -longName "attr" -attributeType long int $obj;
addAttr -k true -longName "attr" -attributeType bool $obj; //To display new attributes in channel box, make keyable
addAttr -longName "attr" -attributeType enum -enumNames "Weapon:Potion:Obstacle" $obj; //label type attribute

//color slider with 3 attributes assigned to it
addAttr -longName "Name" -usedAsColor -at "float3"; 
addAttr -longName "R" -at "float" -parent "Name";
addAttr -longName "G" -at "float" -parent "Name";
addAttr -longName "B" -at "float" -parent "Name";

//DELETE ATTRIBUTES
deleteAttr "MyObj.attr"; //only avaliable for custom attributes

//RENAME ATTRIBUTES
renameAttr "MyObj.oldName" "newName"; //only avaliable for custom attributes

//CONNECT ATTRIBUTES
connectAttr -force "MyObj1.attr" "MyObj2.attr" //connect sphere2 attribute to sphere1, force breaks prior connections
CBdeleteConnection "MyObj.attr"; //delete the key connection
listConnections -plug on -destination off "MyObject.tx" //lists outgoing attributes (destination/source automatically true)
listConnections -plug off -source off "MyObject.tx" //lists incoming objects

//OTHER
editRenderLayerAdjustment "MyObj.attr";  //add a layer override to attribute using current layer

//=================================================================================================
//COMPONENTS
//=================================================================================================

//POLYGONS
polyUnite -name "newName" -ch 0 "objName"; //merge several meshes together, new mesh is selected
polyMergeVertex  -d 0.01 -am 1 -ch 0 "objName"; //merge all verts selected in mesh
polyChipOff -ch 0 -kft 1 -dup 0 -off 0 $faceArray; //extract selected faces in mesh
polySeparate -rs 1 -ch 0 "objShapeName"]; //seperate all seperate faces into individual objects, use shape name
polyCloseBorder -ch 0 $faceArray; //use selected faces to fill in hole
polySoftEdge -a 0 -ch 0 "objName"; //set normals to hard edge; process one obj at time
polyNormal -normalMode 0 -userNormalMode 0 -ch 0 "objName"; //flip normals

//VERTICES
polyEvaluate -vertex "objName"; //returns number of verts for the mesh in int[]
pointPosition -local ($mySel[0]+".vtx["+$vertNo[$i]+"]"); //get local position of vertex
pointPosition -world ($mySel[0]+".vtx["+$vertNo[$i]+"]"); //get world position of vertex

//EDGES
polyEvaluate -edge "objName"; //returns number of edges for the mesh in int[]

//FACES
polyEvaluate -face "objName"; //returns number of faces for mesh in int[]

//SELECT ALL VERTICES
hilite $mySel[0];
int $vertNo[] = `polyEvaluate -v $mySel[0]`;
for($i = 0; $i < size($vertNo); $i++)
{select -add ($mySel[0] + ".vtx[" + $vertNo[$i] + "]");}

//SELECT ALL FACES
hilite $mySel[0];
int $faceNo[] = `polyEvaluate -f $mySel[0]`;
for($i = 0; $i < size($faceNo); $i++)
{select -add ($mySel[0] + ".f[" + $faceNo[$i] + "]");}

//SELECT ALL EDGES
hilite $mySel[0];
int $edgeNo[] = `polyEvaluate -e $mySel[0]`;
for($i = 0; $i < size($edgeNo); $i++)
{select -add ($mySel[0] + ".e[" + $edgeNo[$i] + "]");}

//GET VERTICES FROM A FACE
string $pi[]= `polyInfo -faceToVertex ($node+".f["$j+"]")`;
string $piParts[];
tokenize $pi[0] $piParts;
for($k=2; $k < size($piParts); $k++)
{
    int $vIndex = $piParts[$k];
    $pos = `pointPosition -world ($node + ".vtx["+$vIndex+"]")`;
}

//GET VERTICES FROM AN EDGE
string $pi[] = `polylnfo -edgeToVertex($node+".e["+$j+"]")`;
string $piParts[];
tokenize $pi[0] $piParts;
int $v0 = int ($piParts[2]);
int $vl = int ($piParts[3]);
$pos0 = `pointPosition -world ($node + ".vtx["+$v0+"]")`;
$pos1 = `pointPosition -world ($node + ".vtx["+$v1+"]")`;

//=================================================================================================
//SELECTION
//=================================================================================================

select -cl;
select "*Base*";    //select all objects with string
select "*:Base";    //namespaces
select "*:*:Base";  //double namespaces

//LIST SELECTION
string $sel[] = `ls -sl`; //stores in order selected, shape/transform nodes, "" if nothing selected
string $sel[] = `ls -sl -tr`; //store only transform nodes
string $sel[] = `ls -sl -tr`; //store only transform nodes
string $sel[] = `ls -sl -tr "*Base"`; //with string in name
string $sel[] = `ls -sl -tr "*:Base"`; //with string in name (namespace)
string $sel[] = `ls -type surfaceShape`; //all surface shapes in scene

//LIST RELATIVES
listRelatives -c "myObject"; //list all children of object
listRelatives -ad "myObject"; //list all children/grandchildren etc. of object
listRelatives -p "myObject"; //list parent of object
listRelatives -ap "myObject"; //list all parents of object (if instanced)

//CONVERT SELECTION
ConvertSelectionToFaces;

//PICKWALK
pickWalk -d "up"; //go up to parent node
pickWalk -d "down"; //go down to first child node
pickWalk -d "right"; //right/left through children nodes

//SELECTING COMPONENTS
hilite "objName";    //allow component selection for obj
hilite -u "objName"; //remove from hilite list

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ANIMATION
///////////////////////////////////////////////////////////////////////////////////////////////////////

frame // global variable integer storing current frame number
time  // global variable number of seconds (default settings) past since playback

play;    
play -state off;
play -forward false; //plays backwards
play -query -state;     //1 if playing, 0 if stopped

playbackOptions -minTime 12 -maxTime 20; //change playback range to 12-20
playbackOptions -animationStartTime 0;    //change animation start
playbackOptions -animationEndTime 20;
playbackOptions -loop "oscillate"; //oscillates between playing forwards/backwards, continuous sets back
playbackOptions -playbackSpeed 0.5; //play at half speed

playblast -filename "test.mov";    //creates playblast using active viewport

//=================================================================================================
// TIME
//=================================================================================================
currentUnit -query -time; //query the time units
currentUnit -time "min";  //set the time units; keys are changed to keep animation speed relative to new time
currentUnit -time "min" -updateAnimation false;  //set the time units; keys aren't changed (can become faster/slower)

currentTime 10sec;  //can use: hour, min, sec, millisec, game, film, pal, ntsc, show, palf, ntscf

//Changing time without changing viewport
float $cTime = `currentTime -query`;
currentTime -update false 10sec; //set new time
currentTime -update false $cTime; //reset back

//=================================================================================================
//ANIMATION CURVES
//=================================================================================================

if(isAnimCurve("myNode")){...} //determine if node is animation curve
delete "animationCurve";

//QUERY KEYFRAMES
keyframe -query -name "myObj";                      //lists all animation curve nodes for obj
keyframe -query -name "myObj.tx";                   //lists animation curve node for specific attribute
keyframe -query -valueChange "myObj.tx";            //lists all values for all keys of tx
keyframe -query -keyframeCount "myObj.tx";          //returns amount of keyframes for curve
keyframe -query -selected -valueChange "myObj.tx";  //returns value of selected keyframe

//MOVE KEYFRAMES
keyframe -edit -time 48 -timeChange 20 "myObj.tx";                    //moves key at frame 48 to 20
keyframe -edit -time 10 -relative -timeChange 5 "myObj.tx";           //moves key 5 paces to right
keyframe -edit -time "0:12" -relative -timeChange 5 "myObj.tx";       //moves keys from 0 to 12 five paces
keyframe -edit -time ":12" -relative -timeChange 5 "myObj.tx";        //moves keys before 12 five paces
keyframe -edit -time ":" -relative -timeChange 5 "myObj.tx";          //moves all keys five paces
keyframe -edit -index 0 -index 2 -relative -timeChange 5 "myObj.tx";  //move first/third frame right 5 places
keyframe -edit -index "0:12" -relative -timeChange 5 "myObj.tx";      //move first 13 frames right 5 paces
keyframe -edit -index ":" -relative -timeChange 5 "myObj.tx";         //move all frames five paces

scaleKey -time ":" -valueScale 0.5 "myObj.tx"; //scale values of all frames by 1/2
scaleKey -timeScale 0.5 "myObj.tx"; //scale all frames time by 1/2

snapKey -timeMultiple 1 "myObj.tx"; //snapes keys back to whole frames

//SET KEY FRAME
setKeyframe;                              //set keyframe for selected objects on all keyable attributes
setKeyframe "myObj"                       //set keyframe for object on all keyable attributes
setKeyframe    -attribute "translateX";   //set keyframe for selected objects for translate x
setKeyframe -time 1 -value 5 "myObj.tx";  //set keyframe at specific time
setKeyframe -insert -time "myObj.tx";     //inserts without changing shape of curve 

//POST/PRE KEYS
setInfinity -query -preInfinite "myObj.tx";  //query settings for left of first key
setInfinity -query -postInfinite "myObj.tx";  //query settings for right of last key
setInfinity -preInfinite "cycle" //set preinfinite to cycle; Options: constant(default), linear, cycle, cycleRelative, oscillate

//SET DRIVEN KEYFRAME
setDrivenKeyframe -driverValue 0 -value 0 -currentDriver "myObj.tx" "myObj.sx";  //Creates tx as sx's driver and sets keyframe so when tx is 0, sx is 0
setDrivenKeyframe -driverValue 5 -value 10 "myObj.sx"; //Sets another key so scale is 10 when translate is 5

//BREAKDOWN KEYS (interpolated keys)
keyframe -query -time 10 -breakdown "myObj.tx"; //1 if breakdown at time 10, 0 if keyframe
keyframe -time 10 -breakdown true "myObj.tx"; //make keyframe breakdown key at time 10

//KEY TANGENTS
//Out Tangent = right handle for key
//In Tangent = left hand for key
//Types: flat, step, spline
keyTangent -index 0 -outTangentType flat "MyObj.tx";  //type determines interpolation between first key and next key

//KEY CLIPBOARD
copyKey -index 0 "myObj.tx";
pasteKey -time 10 -option insert "MyObj.tx";
cutKey -index 0 -option keys "MyObj.tx";
cutKey -index 0 -clear "MyObj.tx"; //doesn't add to clipboard

//=================================================================================================
//SKELETONS/JOINTS
//=================================================================================================

//GET ALL CHILDREN FROM ROOT JOINT
string $joints[] = `listRelatives -fullPath -type "joint" -allDescendents $RootNode`; //fullPath important due to naming of joints

//CREATE JOINT
joint -position 0 0 10; //if a joint is selected, adds new joint as child and selects child
insertJoint "joint1";  //insert a new joint as a child of joint 1 and parent of any previous children of joint1, inserted at origon
removeJoint "joint1";

//MOVE JOINT
joint -edit -position 0 0 10 "joint1"; //change position of joint and its children
joint -edit -position 0 0 10 -component "joint1"; //change position of joint but don't affect children
joint -edit -relative -position 0 0 10 "joint1"; //change position of joint relative to its parent

//ROTATE JOINT
joint -query -degreeOfFreedom "joint1"; //returns degrees of freedom as xyz
joint -edit -degreeOfFreedom "y" "joint1"; //set degrees of freedom to only y axis
joint -edit -limitSwitchY "yes" "joint1"; //turn on rotation limits for y axis
joint -edit -limitY 0deg 90deg "joint1"; //set the rotation limits for y axis
joint -query -limitY "joint1"; //query current rotation limits
xform -query -rotation "joint1"; //query rotation value

///////////////////////////////////////////////////////////////////////////////////////////////////////
// RENDERING
///////////////////////////////////////////////////////////////////////////////////////////////////////

//VIEWPORTS
playbackOptions -view "all";    //view all viewports
playbackOptions -view "active"; //view active viewport
upAxis -q -axis;  //returns current up axis
setUpAxis "z";    //set the current up axis

//SETTING / GETTING RENDERER
//Types: "mayaSoftware" "mayaHardware" "mentalRay"
defaultRenderGlobals.currentRenderer;                                
string &renderer = `getAttr defaultRenderGlobals.currentRenderer`; //store current renderer
setAttr defaultRenderGlobals.currentRenderer -type "string" "mayaHardware";  //change renderer

// HYPERSHADE
hyperShade -assign initialShadingGroup; //assign default lambert shader to selected

// SELECT MESH SHADER
hyperShade -smn; //select material node of geometry
string $sel[] = `ls -sl`;
select -cl;
string $sel2[] = `hyperShade -lun $sel[0]`; //select connected nodes to shader
select $sel2;

// CREATING SHADERS
string $shaderName = `shadingNode -asShader blinn`;

// VERTEX COLOR
setAttr ($objName + ".displayColors") 1; //allow vertex color to be displayed
polyColorPerVertex -rgb $r $g $b; //rgb as floats will color selected vertices


