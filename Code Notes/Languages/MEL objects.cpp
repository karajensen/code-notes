///////////////////////////////////////////////////////////////////////////////////////////////////////
//OBJECTS/NODES
///////////////////////////////////////////////////////////////////////////////////////////////////////

//CREATE NODES
createNode file;     //create a texture file node
createNode checker;  //create a checker node
createNode script;   //create a custom script node

//OBJECTS
sphere;                    //NURBS sphere
polySphere;                //poly sphere
polyCube -n "mycube";      //poly cube
textCurves - t "mytext";   //text as curves

delete "objName";
delete; //currently selected

//COMMON
DeleteHistory; 
CenterPivot; 
duplicate -rr;

///////////////////////////////////////////////////////////////////////////////////////////////////////
//TRANSFORMING OBJECTS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//world matrix returns array of float
float $worldMat[] = `xform -query -matrix "objName"`;

//GETTING TRANSFORMATIONS
xform -query -matrix;                    //local matrix 
xform -query -worldSpace -matrix;        //world matrix 
xform -query -translate;                //translation in object space
xform -query -worldSpace -translation;  //translation in world space
xform -query -relative -scale;            //scale in object space
xform -query -rotation;                    //rotation in object space
xform -query -rotateAxis;                //rotation orientation

//SETTING TRANSFORMATIONS
xform -translation 2 3 4;                //set position in local space
xform -worldSpace -translation 2 3 4;    //set position in world space
xform -rotation 45 0 0                    //rotation
xform -scale 1.2 0.3 0                    //scaling

//RESETTING
makeIdentity -apply false;                //reset transformation/move object back to default
makeIdentity -apply true;                //reset/freeze transformations


///////////////////////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIPS
///////////////////////////////////////////////////////////////////////////////////////////////////////

parent "obj1" "ob2";    //parent obj1 to obj2    
parent -world "ob1";    //unparent obj1 (ie. parent to world)    

group -em -n "groupName" -p"parentName"; //create an empty(-em) group, parent under parentName
group -n "groupName" $childList;         //create a group, add children to it
ungroup -world "myObj";                     //remove myObj from the group

reorder -front "myObj";    //move myObj up to front/back of list of siblings

renameSelectionList("NewName"); //renames selection list to NewName incrementing
rename $objName $objNewName;    //note; renaming transform node auto renames shape node

inheritTransform -off "childObject"; //parent's transform doesn't effect specific child

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ATTRIBUTES
///////////////////////////////////////////////////////////////////////////////////////////////////////

//GET ATTRIBUTE
getAttr sphere1.rotateZ;
getAttr -time 10 sphere1.rotateZ;
getAttr transforml.matrix;    //returns array of 16 floats, not matrix

//SET ATTRIBUTE
setAttr sphere1.rotateZ 15;

//LIST ATTRIBUTES
listAttr "MyObj";                 //returns array of strings with attribute names
listAttr -userDefined "MyObj";    //list custom attributes only
listAttr -keyable "MyObj";        //list keyable/attributes in channel box only
listAnimatable "myObj";            //lists all attributes that can be animated

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
deleteAttr ($myObj + ".attr"); //only avaliable for custom attributes

//RENAME ATTRIBUTES
renameAttr ($myObj + ".oldName") "newName"; //only avaliable for custom attributes

//CONNECT ATTRIBUTES
connectAttr -force sphere1.attributeName sphere2.attributeName    //connect sphere2 attribute to sphere1, force breaks prior connections
CBdeleteConnection ($myObj + ".attr"); //delete the key connection
listConnections -plug on -destination off "MyObject.tx" //lists outgoing attributes (destination/source automatically true)
listConnections -plug off -source off "MyObject.tx" //lists incoming objects

//OTHER
editRenderLayerAdjustment ($myObj + ".attr");  //add a layer override to attribute using current layer

///////////////////////////////////////////////////////////////////////////////////////////////////////
//COMPONENTS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//POLYGONS
polyUnite -name "newName" -ch 0 "objName"; //merge several meshes together, new mesh is selected
polyMergeVertex  -d 0.01 -am 1 -ch 0 "objName"; //merge all verts selected in mesh
polyChipOff -ch 0 -kft 1 -dup 0 -off 0 $faceArray; //extract selected faces in mesh
polySeparate -rs 1 -ch 0 "objShapeName"]; //seperate all seperate faces into individual objects, use shape name
polyExtrudeFacet -ch 0 -keepFacesTogether 1 -pvx 0 -pvy 0 -pvz 0 -divisions 1 -twist 0 -taper 1 -off 0 -smoothingAngle 30 $faceArray; 
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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//SELECTION
///////////////////////////////////////////////////////////////////////////////////////////////////////

select -cl;
select "*Base*";    //select all objects with string
select "*:Base";    //namespaces
select "*:*:Base";  //double namespaces

//LIST SELECTION
//each object has transform node/shape node which are both selected unless specified
string $sel[] = `ls -sl`; //stores in order selected, shape/transform nodes, "" if nothing selected
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
//MAYA EXPRESSIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*
OBJECT EXPRESSIONS
  Can't use string/matrices
  Use full group path to prevent issues: parent|child.translateX
  Avoid setAttr/getAttr; use child.attribute
  Expression nodes are auto deleted when connecting objects are deleted
  I[x] means connections have been deleted
  Object names are auto renamed when changed

PARTICLE EXPRESSIONS
  Runtime expressions always run after start, even if start is set to later time
  Runtime expressions run on particles who have ages > 0
  Attributes with a PP and non-PP name are PP and Per-Object
  Attributes with no PP and only non-PP name are PP

COMBINING EXPRESSIONS/KEYFRAME ANIMATION
  Connect animation curve output to a custom attribute
  Use expression to manipulate this attribute
  Feed the final output to object's translate/rotate/scale attributes
*/

//CREATING EXPRESSIONS
expression -string "plane.translateY = plane.animTranslateY" -name "newExpression";

//PARTICLE ATTRIBUTE LIST
myParticles.position = <<0,0,0>>;
myParticles.rgbPP = <<0,0,0>>;        //use add dynaimc attribute
myParticles.radiusPP = 0;            //use add dynaimc attribute
myParticles.velocity = <<0,0,0>>;
myParticles.lifespacePP = 0;
myParticles.id;

//FUNCTIONS
sin(angle/time)        //returns between -1,1
cos(angle/time)        //returns between -1,1
noise(time)            //randonly generated noise curve, returns between -1,1
sqrt(amount)        
trunc(amount)

//----------------------------------------------------------------------
//RANDOM GENERATION
//----------------------------------------------------------------------
seed(3);             //sets the seed used by random gen
rand(20, 50);         //returns a float between 20 and 50 inclusive
sphrand(x);             //creates random vector within a sphere with radius x
sphrand(<<1,2,1>>);     //creates random vector within a skewed sphere 1 unit radius in x etc.

//create random set of points covering sphere with $radius
for($i = 0; $i < size($vecArray); $i++)
{$vecArray[$i] = unit(sphrand(1))*$radius;}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ANIMATION
///////////////////////////////////////////////////////////////////////////////////////////////////////

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

//==========================================================================
//TIME
//==========================================================================
currentUnit -query -time; //query the time units
currentUnit -time "min";  //set the time units; keys are changed to keep animation speed relative to new time
currentUnit -time "min" -updateAnimation false;  //set the time units; keys aren't changed (can become faster/slower)

currentTime 10sec;  //can use: hour, min, sec, millisec, game, film, pal, ntsc, show, palf, ntscf

//Changing time without changing viewport
float $cTime = `currentTime -query`;
currentTime -update false 10sec; //set new time
currentTime -update false $cTime; //reset back

//==========================================================================
//ANIMATION CURVES
//==========================================================================

if(isAnimCurve("myNode")){...} //determine if node is animation curve
delete "animationCurve";

//QUERY KEYFRAMES
keyframe -query -name "myObj";    //lists all animation curve nodes for obj
keyframe -query -name "myObj.tx"; //lists animation curve node for specific attribute
keyframe -query -valueChange "myObj.tx"; //lists all values for all keys of tx
keyframe -query -keyframeCount "myObj.tx"; //returns amount of keyframes for curve
keyframe -query -selected -valueChange "myObj.tx"; //returns value of selected keyframe

//MOVE KEYFRAMES
keyframe -edit -time 48 -timeChange 20 "myObj.tx"; //moves key at frame 48 to 20
keyframe -edit -time 10 -relative -timeChange 5 "myObj.tx"; //moves key 5 paces to right
keyframe -edit -time "0:12" -relative -timeChange 5 "myObj.tx"; //moves keys from 0 to 12 five paces
keyframe -edit -time ":12" -relative -timeChange 5 "myObj.tx"; //moves keys before 12 five paces
keyframe -edit -time ":" -relative -timeChange 5 "myObj.tx"; //moves all keys five paces
keyframe -edit -index 0 -index 2 -relative -timeChange 5 "myObj.tx"; //move first/third frame right 5 places
keyframe -edit -index "0:12" -relative -timeChange 5 "myObj.tx"; //move first 13 frames right 5 paces
keyframe -edit -index ":" -relative -timeChange 5 "myObj.tx"; //move all frames five paces

scaleKey -time ":" -valueScale 0.5 "myObj.tx"; //scale values of all frames by 1/2
scaleKey -timeScale 0.5 "myObj.tx"; //scale all frames time by 1/2

snapKey -timeMultiple 1 "myObj.tx"; //snapes keys back to whole frames

//SET KEY FRAME
setKeyframe;                             //set keyframe for selected objects on all keyable attributes
setKeyframe "myObj"                         //set keyframe for object on all keyable attributes
setKeyframe    -attribute "translateX";     //set keyframe for selected objects for translate x
setKeyframe -time 1 -value 5 "myObj.tx"; //set keyframe at specific time
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

//==========================================================================
//SKELETONS/JOINTS
//==========================================================================

//GET ALL CHILDREN FROM ROOT JOINT
string $AllJoints[] = `listRelatives -fullPath -type "joint" -allDescendents $RootNode`; //fullPath important due to naming of joints

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
//DYNAMICS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//SHATTER FUNCTIONS
//returns and selects list of created shards
//SCRIPTS: App location/scripts/other/*shatter
crackShatter(string $name, int $crackCount, int $crackLength, int $triangulate, 
             float $perturb, float $extrude, int $seedValue, int $original, 
             string $postOp, int $makeRigid, int $verbose) 

solidShatter(string $name, int $shardCount, int $triangulate, int $applyMaterial, 
             int $removeInterior, float $extrude, float $perturbFactor, int $seedValue, 
             int $original, string $postOp, int $makeRigid, int $verbose)

surfaceShatter(string $name, int $shradCount, int $exactCount, int $smoothing, 
               int $triangulate, float $extrude, float $perturb, int $seedValue, 
               int $original, string $postOperation, int $makeRigid, int $verbose)

