///////////////////////////////////////////////////////////////////////////////////////////////////////
//PYTHON FOR REALFLOW
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*

BATCH SCRIPT = runs when user specifies
EVENT SCRIPT = run multiple times during simulation depending on event
CUSTOM NODE SCRIPT = create custom entities
SCRIPTED DAEMON = create custom daemon

Simulation Step = occurs a set number of times per frame
Simulation Frame = occurs every frame of simulation

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
//SCENE CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

scene.message("hello")	//only takes strings

//CREATE NEW ENTITIES
myObject = scene.addHemisphere(int = 2)						//resolution
myObject = scene.addVase(int = 10, int = 1, float = 2.0)	//vertice number, segments, ratio of upper/lower edges 
myObject = scene.addCube()
myObject = scene.addObject("name",vertexList,faceList)	

//GET ENTITIES
myObject = scene.getObject("objectName")
myEmitter = scene.getEmitter("emitterName")
myPathName = scene.getRootPath()+"/particles"	//add /name to get into individual folders

CurrentFrame = scene.getCurrentFrame()

//GLOBAL VARIABLES
if (scene.getGlobalVariableValue("objPath") == None):	//check if variable exists
	scene.setGlobalVariableValue("objPath","C:/")		//will create if doesn't exist

//LOADING SCRIPS
scene.loadEventsScript("scriptlocation/script.rfs")


///////////////////////////////////////////////////////////////////////////////////////////////////////
//VECTOR CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

myVector = Vector.new(float,float,float)

myFloat = myVector.module()			//magnitude of vector
myVector = myVector.scale(myFloat)	//scale vector by value
myVector = myVector.normalize()		//unit vector

///////////////////////////////////////////////////////////////////////////////////////////////////////
//IMAGE CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

myImage = Image.new()
myImage.open("location/image.tga")	//open an image
myImage.close()


///////////////////////////////////////////////////////////////////////////////////////////////////////
//OBJECT CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//GET 
myObject.getParameter("@ mass")		//returns vector
myObject.getName()					//returns string name of object
myObject.getFaces()					//returns list storing face information
myObject.getVertices()				//returns list storing vertex information

//SET
myObject.setParameter("Dynamics","Rigid body")
myObject.setForce(myVector)

//METHODS
myObject.freezeTransformations()			//freeze all transformations
Obj1.getCollisionPoints(Obj2)	//returns list of points of collision between two objects


///////////////////////////////////////////////////////////////////////////////////////////////////////
//FACE CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//GET
myFace.getIndices()		//returns list of index buffer values corresponding to particle vertices for face


///////////////////////////////////////////////////////////////////////////////////////////////////////
//EMITTER CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//SET
myEmitter.setParameter("Type","Dumb")
myEmitter.setParameter("Speed",0.0)

//GET
myEmitter.getParticlesColliding()			//returns list of particles colliding with objects

//METHODS
myEmitter.addParticle(position,velocity)	//Position, Velocity = vector
myEmitter.removeParticle(ParticleID)		//removes particle with specific ID number

//GETTING PARTICLES FROM AN EMITTER
particle = myEmitter.getFirstParticle()
while particle:
	//edit the particle as desired
	particle = particle.getNextParticle()


///////////////////////////////////////////////////////////////////////////////////////////////////////
//PARTICLE CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//GET
myParticle.getVelocity()	//returns vector velocity for particle
myParticle.getPosition()	//returns vector position for particle
myParticle.getId()			//returns ID number for particle particle

//SET
myParticle.setExternalForce(myVector)	//set a force using a vector, for custom daemons
myParticle.setInternalForce(myVector)	//use for custom emitters

//METHODS
myParticle.freeze()		//freezes the particle to its spot when it collides
myParticle.unfreeze()


///////////////////////////////////////////////////////////////////////////////////////////////////////
//GUI FORM DIALOG CLASS 
///////////////////////////////////////////////////////////////////////////////////////////////////////

myForm = GUIFormDialog.new()

//ADDING FIELDS
myForm.addIntField("Columns",0)		//field name, default value
myForm.addBoolField("Yes/No",True)	//field name, True/False default value
myForm.addFloatField("Name",1.0)

//GETTING FIELDS
myForm.getFieldValue("Columns")

//USER CLICK
if(myForm.show() == GUI_DIALOG_ACCEPTED):
	//save values etc.


///////////////////////////////////////////////////////////////////////////////////////////////////////
//GUI FILE PICKER DIALOG CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

filePath = dlg.show( FILE_PICKER_LOAD, "C:/", "*.sd", "Select File" ) //returns "" if nothing chosen
if (filePath != ""):
	//process request


///////////////////////////////////////////////////////////////////////////////////////////////////////
//GUI NODES PICKER CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////////

picker = GUINodesPickerDialog.new()
myList = picker.show()				//show all nodes
myList = picker.show(TYPE_EMITTER)	//show only emitters

//FILTER TYPES
	TYPE_EMITTER
	TYPE_OBJECT


///////////////////////////////////////////////////////////////////////////////////////////////////////
//SAMPLE CODE
///////////////////////////////////////////////////////////////////////////////////////////////////////


//=======================================================================
//CREATE PARTICLE WHEN TWO OBJECTS COLLIDE (EVENT)
//=======================================================================

//Simulation Begin
	import random
	myEmitter.setParameter("Type","Dumb")
	myEmitter.setParameter("Speed",0.0)
//Simulation Step
	myList = Obj1.getCollisionPoints(Obj2)
	myEmitter.setParameters
	for i in myList:
		myEmitter.addParticle(i, Vector.new(random.uniform(-1.0,1.0),
											random.uniform(-1.0,1.0),
											random.uniform(-1.0,1.0)))

//=======================================================================
//BACK UP BIN FILES AFTER SIMULATION (EVENT)
//=======================================================================

//Simulation End
	import shutil, time
	myTime = time.strftime("%d-%m-%Y-%H-%M-%S",time.localtime())
	shutil.copytree(scene.getRootPath()+"/particles",
					scene.getRootPath()+"/particles_new"+myTime)

//=======================================================================
//CREATE DAEMON (SCRIPTED DAEMON)
//=======================================================================

//applyForceToEmitter
	particle = emitter.getFirstParticle()
	gravity = Vector.new(0,-9.8,0)
	while particle:
		particle.setExternalForce(gravity)
		particle = particle.getNextParticle()
//applyForceToBody
	mass = body.getParameter("@ mass")
	gravity = Vector.new(0,-9.8,0).scale(mass)
	body.setForce(gravity)

//=======================================================================
//SHATTER OBJECT (BATCH)
//=======================================================================

	picker = GUINodesPickerDialog.new()
	objList = picker.show(TYPE_OBJECT)		//show only objects in scene
	obj = objList[0]						//only use the first picked
	faceList = obj.getFaces()
	vertexList = obj.getVertices()
	objNumber = 0

	//FOR EVERY FACE:
	//Find its vertices using the index buffer
	//Add the face to a list to create a new object
	for face in faceList:
		curVertexList = []
		curFaceList = [Face.new(0,1,2)]
		for index in face.getIndices():
			curVertexList.append(vertexList[index])	
		scene.addObject("obj%d" %objNumber, curVertexList, curFaceList)
		objNumber = objNumber + 1
