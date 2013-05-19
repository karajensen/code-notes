//////////////////////////////////////////////////////////////////////////////  
//SELECTION
//////////////////////////////////////////////////////////////////////////////  

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

//////////////////////////////////////////////////////////////////////////////  
//OBJECTS
////////////////////////////////////////////////////////////////////////////// 

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


//////////////////////////////////////////////////////////////////////////////  
//EDITABLE MESHES
////////////////////////////////////////////////////////////////////////////// 

//CONVERT NODE TO EDITABLE MESH
myMesh = convertToMesh myBox

//CREATE A MESH
mymesh = mesh vertices:vertArray faces:indices

//MESH FUNCTIONS
vertNumber = getNumVerts myMesh //get number of verts in mesh


//////////////////////////////////////////////////////////////////////////////  
//LIGHTS
////////////////////////////////////////////////////////////////////////////// 

//CREATE A LIGHT
mylight = directionalLight()
mylight = omnilight pos:[0,0,0] castshadows:on

//LIGHT PROPERTIES
mylight.rgb             //light color
mylight.excludeList     //nodes excluded from light
mylight.projectorMap    //can assign texturemap to allow patterns in light


//////////////////////////////////////////////////////////////////////////////  
//SHADERS
////////////////////////////////////////////////////////////////////////////// 

//MATERIAL EDITOR
meditmaterials[2]   //access slot 2 in material editor, only has 24 slots

//MATERIALS
myshader = standard()
myshader = checker()

//MATERIAL PROPERTIES
myshader.diffusemap

//TEXTURE MAPS
mymap = marble Vein_Width:0.1 size:12


//////////////////////////////////////////////////////////////////////////////  
//CAMERAS
////////////////////////////////////////////////////////////////////////////// 

//Free camera
mycam = freeCamera()

//Target camera; camera will always point at target
mytarget = targetObject pos:[0,0,0]
mycam = targetCamera pos:[0,10,2] target:mytarget


//////////////////////////////////////////////////////////////////////////////  
//ANIMATION
//////////////////////////////////////////////////////////////////////////////  

/*---------------------------------------------------------------------------
PROPERTIES: 
translate, radius etc. that an object has

CONTROLLER: 
controls the properties through curves, add keys to this
controllers can be set values above min/max for properties
Controller types: Linear, Bezier and TCB
---------------------------------------------------------------------------*/

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