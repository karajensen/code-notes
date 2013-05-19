///////////////////////////////////////////////////////////////////////////////////////////////////////
//CREATING PLUGINS
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*
PLUGIN WIZARD
  - devkit/pluginwizard
  - make sure MayaPluginWizard.vsz has Wizard=VsWizard.VsWizardEngine.10.0 for vs10
  - copy files to required files per readme

MANUAL SETUP
  - create new windows console and set as .dll
  - Configuration Properties -> Target Extension -> .mll
  - Configuration Type -> Dynamic Library (.dll)
  - Preprocessor -> Preprocessor Definitions -> NT_PLUGIN
  - General -> Additional Include Directories -> [MayaInstallDir]\Include
  - General -> Additional Library Directories -> [MayaInstallDir]\lib
  - Input -> Additional Dependencies ->
		 Foundation.lib;
		 OpenMaya.lib;
  		 OpenMayaUI.lib;
		 OpenMayaAnim.lib;
		 OpenMayaFX.lib;
		 OpenMayaRender.lib;
		 Image.lib;
		 opengl32.lib

DEBUGGING MAYA
  - Debugging -> Command -> [MayaInstallDir]\bin\maya.exe
  - Write a load/unload plugin script for instant loading

CODING PLUGINS
  - Maya uses smart pointers for object types; creating objects inside a function which is called
    and recording those objects in a modifier won't destroy them 
  - Maya gives array members Logical Index (ID) and Physical Index (Array index). MEL can't access Physical Index

MAYA TRANSFORMATIONS
  - For each object: Transform node with child Shape node
  - Transform node holds object's world matrix to transform shape into world coordinates
  - When parented, parent's world matrix multiplied with child's transform matrix 
	 ---------------------------------------------
	| [World Matrix] = [Scale][Rotate][Translate] |
	 --------------------------------------------------------------------------------------
	| [Final World Matrix] = [World Matrix][Parent1 World Matrix][Parent2 World Matrix]... |
	 --------------------------------------------------------------------------------------

SPACE TYPES
	OBJECT SPACE: space where no transformations have been applied, including pivot points
	LOCAL/PARENT SPACE: where the top-most parent's origin is the object's origin
	WORLD SPACE: using world origin


*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
//PLUGIN CODE
///////////////////////////////////////////////////////////////////////////////////////////////////////

//DEFINES
M_PI

//SPACES
MSpace::kInvalid;	//identifies an invalid space
MSpace::kWorld;		//work with function objects assigned to shapes (MFnMesh, MFnNurbsSurface etc.); world space
MSpace::kObject;    //work with function objects assigned to shapes; local space

//TRANSFORM SPACES (only used with MFnTransform/MFnTransformationMatrix function objects)
MSpace::kTransform; //if used with scale space is [M]=[S], if used with rotation, space is [M]=[S][R]...
MSpace::kPreTransform //space [M]=[I]
MSpace::kPostTransform //space [M]=[S][R][T]

//ERROR CHECKING
MStatus status;
if(!status){ stat.perror("Register of 'CommandName' failed"); }
MS::kSuccess;
MS::kFailure;

//PRINTING TO CONSOLE
MGlobal::displayError( "object has been deleted" ); //message in red in command feedback
MGlobal::displayError( MString("An error:")+status.errorString());
MGlobal::displayWarning ( "the selected object is of the wrong type" ); //displayed in red in command feedback
MGlobal::displayInfo( "select a light, then try again" );	//displayed in command feedback

//EXECUTING COMMANDS
MGlobal::executeCommand(MString("cylinder -pivot") + x + " " + y + " " + z ); //executs but doesn't save undo/redo info

//ANGLES
degToRad();
radToDeg();

//AXIS
MGlobal::isYAxisUp();		//returns true if y is up axis
MGlobal::upAxis();			//returns up axis as a MVector
MGlobal::setZAxisUp(true);  //set the up axis

//ID
MTypeId id(0x00333); //ID for nodes (can be between 0 to 0x7FFFE)

///////////////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLES
///////////////////////////////////////////////////////////////////////////////////////////////////////

//NOTES ON POINTS, VECTORS AND MATRICES:
//	- points and vectors need to be homogenous for transformations against Matricesx		
//	- points, vectors and matrices will work together only if all double or all float

//===============================================================================
//POINTS
//===============================================================================
MPoint point;
MFloatPoint point;

//CONVERSIONS
point = vector;
point.homogenize();
point.cartesionize();

//METHODS
point.distanceTo(point2); //length of vector between points
point * matrix;			  //transforming points, returns new point
point *= matrix;		  //transforming points

//POINTS ARRAY
MPointArray points;
points.length();					//size of the array
points.clear();						//clear the array
points.setSizeIncrement(elementNo);	//sets size of array
points.append(point);				//chooses the next avaliable slot to fill?


//===============================================================================
//VECTORS
//===============================================================================
MVector vector;
MFloatVector vector;

//PREDEFINED
MVector::zero;
MVector::xAxis;
MVector::xNegAxis;

//CONVERSIONS
vector = point;

//METHODS
vector *= 2.0f;			  //times by scalar
vector*vector1;			  //dot product
vector^vector1;			  //cross product
vector.length();		  //length of vector
vector.normalize();		  //normalize the vector
vector.normal();		  //returns normalized copy of vector
vector.angle(vector2);	  //returns angle between two vectors
vector.rotateBy(eulerRot);
vector.rotateBy(quat);
vector.rotateTo(vector2);		//returns quaternion necessary to rotate vec to vec2
vector * matrix;				//transforming vectors, returns new point
vector *= matrix;				//transforming vectors
vector.transformAsNormal(mat);	//where mat is the world matrix; creates the inverse normal matrix and transforms

//===============================================================================
//QUATERNIONS
//===============================================================================
MQuaternion quat;

quat *= quat1;	//quaternion *


//===============================================================================
//MATRICES
//===============================================================================
MMatrix matrix;
MFloatMatrix matrix;

matrix.setToIdentity();
matrix(row,column);		  //returns value at row,column
matrix * matrix2;		  //matrix multiplication
matrix.get(floatMatrix);  //convert between float/double matrices
matrix.inverse();		  //inverse of matrix
matrix.transpose();		  //transpose of matrix
matrix.tansformAsNormal(mat) //pass in transformation matrix and function converst it to inverse tranpose

//===============================================================================
//TRANSFORMATION MATRICES
//===============================================================================
MTransformationMatrix transMat;

//Needed to be filled in!
transMat.addRotationQuaternion();
transMat.addRotation();
transMat.addScale();
transMat.addTranslation();
transMat.asMatrixInvers();
transMat.getRotationQuaternion();
transMat.getRotation();
transMat.getScale();
transMat.getTranslation();


//===============================================================================
//MAYA STRINGS
//===============================================================================
MString("My string");


//===============================================================================
//TIME
//===============================================================================
MTime time;
MTime time(value,MTime::kSeconds);

time = MAnimControl::minTime();	//can be maxTime; gives start/end range of timeline
MGlobal::viewFrame(time);		//change the frame


//===============================================================================
//EULER ROTATION
//===============================================================================
MEulerRotation eulerRot;

eulerRot.asMatrix();	//returns rotation matrix


//===============================================================================
//DISTANCE OBJECT
//===============================================================================
MDistance distance(1.0, MDistance::uiUnit());


//===============================================================================
//DAGPATH OBJECTS
//===============================================================================
MDagPath dagpath;

dagpath.isValid();			//whether the path stored is an actual node or not
dagpath.pop();				//when a dagpath is requested, it gives path to shape; use pop to get transform
dagpath.apiType();			//gives type of object the path is of
dagPath.instanceNumber();	//returns instance number of node


//===============================================================================
//MAYA OBJECTS
//===============================================================================
MObject object; //a void* to an internal object

object.isNull();	//checks whether nullptr
thisMObject();		//returns MObject for object that called the method

//===============================================================================
//MAYA HANDLES
//===============================================================================
MDataHandle handle;

handle.copy(handle1);	//copy data from one handle to another

//Converting Handles
double dbl = handle.asDouble();
MVector vec = handle.asDouble3();

//===============================================================================
//ITERATOR OBJECTS
//===============================================================================

//Iterating loop
for(iter.reset(); !iter.isDone(); iter.next()){}

//GEOMETRY ITERATOR
MItGeometry iter;

//VERTEX ITERATOR
MItMeshVertex iter(dagPath,component,&status); //component is MObject, dagPath is component's dagpath
iter.count();					//number of verts for the mesh
iter.position(MSpace::kWorld);	//returns position of pointed-to vertex
iter.index();					//returns int index of vertex for mesh

//EDGE ITERATOR
MItMeshEdge iter(dagPath,component,&status);
iter.count();					//number of edges for the mesh
iter.index();					//returns int index of edge for mesh
iter.index(0); iter.index(1);   //returns index of vertices 0/1 connected to the edge
iter.point(0,MSpace::kWorld);	//returns MPoint vertex 0 connected to edge
iter.point(1,MSpace::kWorld);	//returns MPoint vertex 1 connected to edge

//FACE ITERATOR
MItMeshPolygon iter(dagPath,component,&status);
iter.count();					//number of faces for the mesh
iter.polygonVertexCount();		//number of verts for the face
iter.index();					//returns int index for face
iter.point(i,MSpace::kWorld);	//returns MPoint for vertex at index 
iter.getNormal(normalVector);	//returns MVector for normal for face


//===============================================================================
//BOUNDING BOX
//===============================================================================
MBoundingBox bbox;

bbox.expand(point);	//expands the bounding box to include any points added



///////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTION OBJECTS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//TYPES OF FUNCTION OBJECTS
MFnPlugin pluginFn;					//initialising/uninitialising plugin
MFnNurbsCurve curveFn;				//working with curve objects
MFnTransform transformFn;			//wokring with objects that have transform nodes
MFnDependencyNode shapeFn;			//working with objects that have shape nodes
MFnSurface surfaceFn;				//working with NURBS
MFnSurfaceData surfaceDataFn;		//working with NURBS
MFnSet setFn;						//working with shader groups
MFnDagNode dagNodeFn;				//working with dag paths/objects
MFnEulerRotation eulerFn;			//wokring with objects that have transform nodes
MFnQuaternion quatFn;				//wokring with objects that have transform nodes
MFnMesh meshFn;						//working with meshes

//REGISTERING OBJECTS WITH FUNCTION OBJECTS
//allows using certain methods on the objects
//not all function objects will have both object/path enabled
myFunctionObject.setObject(myDagPath);
myFunctionObject.setObject(myMayaObject);

//FUNCTION OBJECT METHODS
myFunctionObject.object();	//get the attached object


//----------------------------------------------------------------------------
//CURVE FUNCTION OBJECT
//----------------------------------------------------------------------------
curveFn.getKnotDomain(tStart,tEnd);	//get start/end t (usually 0-1) values from curve parametric equation
curveFn.getPointAtParam(t,point,MSpace::kWorld); //get world coordinate given value of t from parametric equation
curveFn.getPointAtParam(t,point,MSpace::kObject); //get local coordinate given value of t from parametric equation

//----------------------------------------------------------------------------
//TRANSFORM FUNCTION OBJECT
//----------------------------------------------------------------------------
transformFn.getRotation(eulerObject);
transformFn.findPlug("translateX"); //returns MPlug
transformFn.getScale(myScale); //Get local scale vector, requires 'double myScale[3];'
transformFn.getShear(myShear); //Get local shear vector
transformFn.getRotation(myRotation,ro); //requires 'MTransformationMatrix::RotationOrder ro;'
transformFn.translation(MSpace::kTransform); //returns a vector for the translate
transformFn.rotateOrientation(MSpace::kTransform); //returns a quaternion for the rotation orientation
transformFn.transformation(); //returns MTransformationMatrix for the transformation matrix
transformFn.setTranslation(MVector(1.0,2.0,3.0), MSpace::kTransform);
transformFn.translateBy(MVector(-1.0,0.0,0.0), MSpace::kTransform);
transformFn.setScale(s); //requires 'double myScale[3];'
transformFn.scaleBy(s); //requires 'double myScale[3];'
transformFn.setRotation(q); //requires quaternion
transformFn.rotateBy(q); //requires quaternion	
transformFn.setRotation(e); //requires euler angle
transformFn.rotateBy(e); //requires euler angle
transformFn.set(mat); //set as a matrix, use 'MTransformationMatrix tm;' to set back to identity

//----------------------------------------------------------------------------
//EULER ROTATION FUNCTION OBJECT
//----------------------------------------------------------------------------
eulerFn.getRotation(e); //requires 'MEulerRotation e;'

//----------------------------------------------------------------------------
//QUATERNION FUNCTION OBJECT
//----------------------------------------------------------------------------
quatFn.getRotation(q); //requires 'MQuaternion q;'

//----------------------------------------------------------------------------
//DEPENDENCY NODE FUNCTION OBJECT
//----------------------------------------------------------------------------
shapeFn.findPlug("create"); //returns MPlug

//----------------------------------------------------------------------------
//SURFACE FUNCTION OBJECT
//----------------------------------------------------------------------------
surfaceFn.copy(surfaceObject1, surfaceObject2); //copy 1 into 2
surfaceFn.setCVs(myPointArray);	//set an array of points into the surface object (requires Set Object)
surfaceFn.updateSurface();	//update the surface when any changes are made to it (requires Set Object)

//----------------------------------------------------------------------------
//SET FUNCTION OBJECT
//----------------------------------------------------------------------------
setFn.addMember(myObject);	//add an object to the shading group set

//----------------------------------------------------------------------------
//DAG PATH FUNCTION OBJECT
//----------------------------------------------------------------------------
dagNodeFn.findPlug("translate");	//find the translate plug for the path (requires Set Object)
dagNodeFn.duplicate(false,false);	//returns a MObject copy or instance of the geometry (requires Set Object of shape path)
dagNodeFn.child(childNumber)		//returns a MObject for the child requrested (child 0 is the shape node given a transform path)

//----------------------------------------------------------------------------
//MESH FUNCTION OBJECT
//----------------------------------------------------------------------------
meshfn.getPoints(vertices) //Takes reference to MPointArray and gets all vertices for mesh
meshfn.create(vertices.length(), polycounts.length(), vertices, polycounts, indices);


///////////////////////////////////////////////////////////////////////////////////////////////////////
//COMPONENTS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//ITERATING OVER COMPONENTS
MDagPath dagPath; MObject component;
SelectionIter.getDagPath(dagPath,component); //where selectioniter is iterating over selected objects
MltMeshVertex iter(dagPath,component,&status); //component = MObject, status = MStatus, dagpath = MDagPath
if(status == MS::kSuccess) //will fail if dagpath isn't to an acceptable mesh/vertex
{
	for(iter.reset(); !iter.isDone(); iter.next())
	{ 
		//do stuff on vertex
		MPoint pt = iter.position(MSpace::kWorld);
		int index = iter.index();
	}
}
s
///////////////////////////////////////////////////////////////////////////////////////////////////////
//SELECTION
///////////////////////////////////////////////////////////////////////////////////////////////////////

MSelectionList selection;

MGlobal::getActiveSelectionList	(selection);			 //get user selection
MGlobal::getSelectionListByName("nodeName",selection);	//get specific selection

//METHODS
selection.clear();	//clear container
selection.length(); //size of container

//SELECTING A SHADER
MObject shadingGroupObj;
MGlobal::getSelectionListByName("initialShadingGroup",selection);
selection.getDependNode(0,shadingGroupObj);


//ITERATING OVER SELECTED 
MItSelectionList iter(selection);
iter.setFilter(MFn::kNurbsCurve);
for(iter.reset(); !iter.isDone(); iter.next())
{
	//get the node path
	MDagPath dagPath;		
	iter.getDagPath(dagPath);

	//attach a function object
	MFnNurbsCurve curveFn;
	curveFn.setObject(dagPath);
}

//SELECTION MASKS
MFn::kGeometric;	//poly,NURBS,SubD objects


///////////////////////////////////////////////////////////////////////////////////////////////////////
//ATTRIBUTES
///////////////////////////////////////////////////////////////////////////////////////////////////////

//NUMERIC ATTRIBUTE SETUP (for numbers)
MFnNumericAttribute nAttr;
NodeAttr.myAttribute = nAttr.create("fullName", "shortName", MFnNumericData::kDouble, 0.0);
	
//UNIT ATTRIBUTE SETUP (for angles/distance)
MFnUnitAttribute uAttr; 
NodeAttr.myAttribute = uAttr.create("fullName", "shortName", MFnUnitAttribute::kAngle, 0.0);
NodeAttr.myAttribute = uAttr.create("fullName", "shortName", MFnUnitAttribute::kDistance, 0.0);

//TYPED ATTRIBUTE SETUP (for specific object types)
MFnTypedAttribute tAttr;
NodeAttr.myAttribute = tAttr.create("fullName","shortName",MFnNurbsSurfaceData::kNurbsSurface);

//GENERIC ATTRIBUTE SETUP (for multiple object types)
MFnGenericAttribute gAttr;
NodeAttr.myAttribute = gAttr.create("fullName","shortName");
gAttr.addAccept(MFnData::kMesh); //choose which types to accept
gAttr.addAccept(MFnData::kNurbsSurface);

//COMPOUND ATTRIBUTE SETUP (for creating a parent attribute)
MFnCompoundAttribute cAttr;
NodeAttr.myAttribute = cAttr.create("fullName","shortName");
cAttr.addChild(NodeAttr.attribute1); //add other attributes to parent
cAttr.addChild(NodeAttr.attribute2);


//ATTRIBUTE SETTINGS
nAttr.setKeyable(true);		 //Set an attribute keyable; this puts it in the channel box (doesn't happen by default)
nAttr.setDefault(0);		 //Value initialised to when instance is created; data not stored in attribute if never changed from default (saves space)
nAttr.setHidden(true);		 //Set attribute hidden (visible by default)
nAttr.setStorable(false);	 //don't save attribute information (for output attributes as they're calculated)
nAttr.setReadable(false);	 //whether attribute can send data to another attribute
nAttr.setWritable(false);	 //whether attribute can receive data from another attribute
nAttr.setConnectable(false); //whether attribute can be connected to another attribute
nAttr.setArray(false);		 //whether attribute holds single value (default settings) or any array
nAttr.setCached(false);		 //whether compute() is called for all queries of data
nAttr.setMin(value);
nAttr.setMax(value);

//DYNAMIC ATTRIBUTES
MFnDependencyNode nodeFn(nodeObj);
nodeFn.addAttribute(nAttr, MFnDependencyNode::kLocalDynamicAttr); //add a attribute to a single node
nodeFn.addAttribute(nAttr, MFnDependencyNode::kGlobalDynamicAttr); //add a attribute to a all nodes
nodeFn.removeAttribute(nAttr, MFnDependencyNode::kLocalDynamicAttr);

//FINALISE ATTRIBUTES
addAttribute(NodeAttr.myAttribute);			 //add attributes to node
addAttribute(NodeAttr.myCompoundAttribute);  //add compound attribute (also need to add any children seperately)
attributeAffects(NodeAttr.myInputAttribute, NodeAttr.myOutputAttribute); //set input effects output

///////////////////////////////////////////////////////////////////////////////////////////////////////
//PLUGS/CONNECTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////
//Plugs look after connections between attributes
//Any attribute can have one input and many output connections
//Get plug for transform nodes: use MFnTransform
//Get plug for shape nodes: use MFnDependencyNode

MPlug plug;

myPlug.value();

//CHOOSING A PLUG FROM AN OBJECT
MPlug myPlug = shapeFn.findPlug("attributeName");	//shape node
MPlug myPlug = transformFn.findPlug("translateX");	//transform node

//GETTING/SETTING VALUES
myPlug.setValue(value);
myPlug.getValue(value);

//GETTING AT DIFFERENT TIME
MDGContext ctx(time);
myPlug.getValue(value, ctx);

//SETTING AT DIFFERENT TIME
MGlobal::viewFrame(time); //makes DG update so use sparingly
myPlug.setValue(value);	

//GETTING INPUT/OUTPUT CONNECTIONS
MPlugArray plugConnections;
myPlug.connectedTo(plugConnections,true,false);
MPlug inputPlug = plugConnections[0]; //first element is the single input connection for the attribute

//POINT PLUG TO AN ELEMENT OF OUTPUT CONNECTIONS
unsigned int instanceNum = myShapeDagPath.instanceNumber();	//get instance number of shape
myPlug.selectAncestorLogicalIndex(instanceNum); //point plug to correct output connection

//COMPOUND PLUGS
MPlug myPlug = nodeFn.findPlug("translate"); //is a compound plug with children translateX, translateY...

for(unsigned int i = 0; i < myPlug.numChildren(); i++)
{
	//get the child plug
	MPlug child = myPlug.child(i);
}

//ARRAY PLUGS
myArrayPlug.numElements();
myArrayPlug.elementByPhysicalIndex(i);	//returns MPlug for that element
myArrayPlug.elementByLogicalIndex(23);	//returns MPlug, if element doesnt exist, creates it
myArrayPlug.logicalIndex();				//returns ID for element


//GET PLUG NAME DEPENDING ON GEOMETRY TYPE
MString outGeomPlugName, inGeomPlugName;
switch(geomShapePath.apiType())	//type of geometry the shape path is
{
case MFn::kMesh:
	outGeomPlugName = "worldMesh";
	inGeomPlugName = "inMesh";
	break;
case MFn::kNurbsSurface:
	outGeomPlugName = "worldSpace";
	inGeomPlugName = "create";
	break;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//DATABLOCKS
///////////////////////////////////////////////////////////////////////////////////////////////////////

MDataHandle inputData = data.inputValue(NodeAttr.myInputAttribute);
MDataHandle outputData = data.outputValue(NodeAttr.myOutputAttribute);

//DATA BLOCK ARRAYS
MDataHandle inputArrayData = data.inputArrayValue(NodeAttr.myInputArrayAttribute);

//iterate over data in data block array
for(unsigned int i = 0; i < inputArrayData.elementCount(); i++)
{
	inputArrayData.jumpToElement(i);//moves over to the corrent element
	MDataHandle element = inputArrayData.inputValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//MODIFIERS
///////////////////////////////////////////////////////////////////////////////////////////////////////
//SAVING COMMANDS FOR UNDO/REDO
//dgMod/dagMod only saves info for executing the commands; it doesn't actually execute them
//dagMod used when dealing with parent/child relationships between nodes

MDGModifier dgMod;
MDagModifier dagMod;

dgMod.commandToExecute(MString("cylinder -pivot")+x+" "+y+" "+z); 
dgMod.createNode("MyNode");
dgMod.createNode(MeltNode::id);
dgMod.connect(transformFn.findPlug("translateX"),transformFn2.findPlug("translateY")); //connect two attributes
dgMod.disconnect(inputPlug,desintationPlug);
dgMod.renameNode(myNode,MString("myname"));

dagMod.reparentNode(object,parent);				//parents object under parent (both are MObject)
dagMod.MDGModifier::createNode(MeltNode::id);	
