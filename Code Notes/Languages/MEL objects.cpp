///////////////////////////////////////////////////////////////////////////////////////////////////////
//OBJECTS/NODES
///////////////////////////////////////////////////////////////////////////////////////////////////////

//CREATE NODES
createNode file;	//create a texture file node
createNode checker;	//create a checker node
createNode script;	//create a custom script node

//OBJECTS
sphere;						//NURBS sphere
polySphere;					//poly sphere
polyCube -n "mycube";		//poly cube
textCurves - t "mytext";	//text as curves

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
xform -query -matrix;					//local matrix 
xform -query -worldSpace -matrix;		//world matrix 
xform -query -translate;				//translation in object space
xform -query -worldSpace -translation;  //translation in world space
xform -query -relative -scale;			//scale in object space
xform -query -rotation;					//rotation in object space
xform -query -rotateAxis;				//rotation orientation

//SETTING TRANSFORMATIONS
xform -translation 2 3 4;				//set position in local space
xform -worldSpace -translation 2 3 4;	//set position in world space
xform -rotation 45 0 0					//rotation
xform -scale 1.2 0.3 0					//scaling

//RESETTING
makeIdentity -apply false;				//reset transformation/move object back to default
makeIdentity -apply true;				//reset/freeze transformations


///////////////////////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIPS
///////////////////////////////////////////////////////////////////////////////////////////////////////

parent "obj1" "ob2";	//parent obj1 to obj2	
parent -world "ob1";	//unparent obj1 (ie. parent to world)	

group -em -n "groupName" -p"parentName"; //create an empty(-em) group, parent under parentName
group -n "groupName" $childList;		 //create a group, add children to it
ungroup -world "myObj";					 //remove myObj from the group

reorder -front "myObj";	//move myObj up to front/back of list of siblings

renameSelectionList("NewName"); //renames selection list to NewName incrementing
rename $objName $objNewName;    //note; renaming transform node auto renames shape node

inheritTransform -off "childObject"; //parent's transform doesn't effect specific child

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ATTRIBUTES
///////////////////////////////////////////////////////////////////////////////////////////////////////

//GET ATTRIBUTE
getAttr sphere1.rotateZ;
getAttr -time 10 sphere1.rotateZ;
getAttr transforml.matrix;	//returns array of 16 floats, not matrix

//SET ATTRIBUTE
setAttr sphere1.rotateZ 15;

//LIST ATTRIBUTES
listAttr "MyObj";				 //returns array of strings with attribute names
listAttr -userDefined "MyObj";	//list custom attributes only
listAttr -keyable "MyObj";		//list keyable/attributes in channel box only
listAnimatable "myObj";			//lists all attributes that can be animated

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
connectAttr -force sphere1.attributeName sphere2.attributeName	//connect sphere2 attribute to sphere1, force breaks prior connections
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
select "*Base*";	//select all objects with string
select "*:Base";	//namespaces
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
hilite "objName";	//allow component selection for obj
hilite -u "objName"; //remove from hilite list
