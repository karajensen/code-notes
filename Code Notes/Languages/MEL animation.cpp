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
myParticles.rgbPP = <<0,0,0>>;		//use add dynaimc attribute
myParticles.radiusPP = 0;			//use add dynaimc attribute
myParticles.velocity = <<0,0,0>>;
myParticles.lifespacePP = 0;
myParticles.id;

//FUNCTIONS
sin(angle/time)		//returns between -1,1
cos(angle/time)		//returns between -1,1
noise(time)			//randonly generated noise curve, returns between -1,1
sqrt(amount)		
trunc(amount)

//----------------------------------------------------------------------
//RANDOM GENERATION
//----------------------------------------------------------------------
seed(3);			 //sets the seed used by random gen
rand(20, 50);		 //returns a float between 20 and 50 inclusive
sphrand(x);			 //creates random vector within a sphere with radius x
sphrand(<<1,2,1>>);	 //creates random vector within a skewed sphere 1 unit radius in x etc.

//create random set of points covering sphere with $radius
for($i = 0; $i < size($vecArray); $i++)
{$vecArray[$i] = unit(sphrand(1))*$radius;}


///////////////////////////////////////////////////////////////////////////////////////////////////////
//ANIMATION
///////////////////////////////////////////////////////////////////////////////////////////////////////

play;	
play -state off;
play -forward false; //plays backwards
play -query -state;	 //1 if playing, 0 if stopped

playbackOptions -minTime 12 -maxTime 20; //change playback range to 12-20
playbackOptions -animationStartTime 0;	//change animation start
playbackOptions -animationEndTime 20;
playbackOptions -loop "oscillate"; //oscillates between playing forwards/backwards, continuous sets back
playbackOptions -playbackSpeed 0.5; //play at half speed

playblast -filename "test.mov";	//creates playblast using active viewport

//==========================================================================
//TIME
//==========================================================================
currentUnit -query -time; //query the time units
currentUnit -time "min";  //set the time units; keys are changed to keep animation speed relative to new time
currentUnit -time "min" -updateAnimation false;	//set the time units; keys aren't changed (can become faster/slower)
 -----------------------------------------
| game  |	Games Animation Speed |	15fps |
| film  |	Standard Film Speed	  |	24fps |
| pal   |	PAL(frames)			  |	25fps |
| ntsc  |	NTSC(frames)		  |	30fps |
| show  |	Show Format(frames)	  |	48fps |
| palf  |	PAL(fields)			  |	50fps |
| ntscf |	NTSC(fields)		  |	60fps |
 -----------------------------------------

currentTime 10sec;	//can use: hour, min, sec, millisec, game, film, pal, ntsc, show, palf, ntscf

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
keyframe -query -name "myObj";	//lists all animation curve nodes for obj
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
setKeyframe;							 //set keyframe for selected objects on all keyable attributes
setKeyframe "myObj"						 //set keyframe for object on all keyable attributes
setKeyframe	-attribute "translateX";	 //set keyframe for selected objects for translate x
setKeyframe -time 1 -value 5 "myObj.tx"; //set keyframe at specific time
setKeyframe -insert -time "myObj.tx";	 //inserts without changing shape of curve 

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

