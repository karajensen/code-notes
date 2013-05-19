///////////////////////////////////////////////////////////////////////////////////////////////////////
//NODE CLASS TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////////////////
//Coupled together with a command class for creating the node
//Node ID needs to be globally unique for real in-house development

//NODE RULES:
// 1) A node should never access beyond it's own attributes
// 2) A node should never know where it is in the DG
// 3) Commands should be used when talking between nodes is necessary

//CREATE A NODE INSIDE A COMMAND METHOD
MObject mynode = dgMod.createNode(MyNode::id);
MFnDependencyNode mynodeFn(mynode);

//CREATE A NODE IN MAYA
createNode nodeCommand;


//--------------------------------------------------------------------------------------------
//NODE CLASS
//--------------------------------------------------------------------------------------------
class MyNode : public MPxNode
{
private:
	struct NodeAttributes
	{
		MObject myInputAttribute;
		MObject myOutputAttribute;
	};

public:
	virtual MStatus compute(const MPlug& plug, MDataBlock& data);
	
	static void* creator(){ return new MyNode; }
	static MStatus initialize();
	static NodeAttributes NodeAttr;
	static MTypeId id;
};

MTypeId MyNode::id(0x00333); //ID used (can be between 0 to 0x7FFFE)
MyNode::NodeAttributes MyNode::NodeAttr;
//--------------------------------------------------------------------------------------------
//ON COMPUTE
//--------------------------------------------------------------------------------------------
MStatus MyNode::compute(const MPlug& plug, MDataBlock& data)
{
	//NOTE: don't use MEL setAttr/getAttr inside here!

	MStatus stat;

	//if request to recompute output attribute (do for all custom output attrs)
	if(plug == NodeAttr.myOutputAttribute)
	{
		//create handles to the node's attributes
		MDataHandle inputData = data.inputValue(NodeAttr.myInputAttribute);
		MDataHandle outputData = data.outputValue(NodeAttr.myOutputAttribute);
		
		//convert the attributes to the required types
		double dblInput = inputData.asDouble();

		//set/change output attributes
		outputData.set(dblInput/2.0);

		//tell Maya attributes have been updated
		data.setClean(plug);
		return MS::kSuccess;
	}
	else
		return MS::kUnknownParameter; //attribute from base class; let Maya update it
}
//--------------------------------------------------------------------------------------------
//ON INITIALISE
//--------------------------------------------------------------------------------------------
MStatus MyNode::initialize()
{
	//Set up attributes
	MFnNumericAttribute nAttr;
	NodeAttr.myOutputAttribute = nAttr.create("fullOutputName", "shortOutputName", MFnNumericData::kDouble, 0.0);	
	addAttribute(NodeAttr.myOutputAttribute);

	MFnUnitAttribute uAttr; 
	NodeAttr.myInputAttribute = uAttr.create("fullInputName", "shortInputName", MFnUnitAttribute::kAngle, 0.0);
	addAttribute(NodeAttr.myInputAttribute);

	//add attribute dependencies (what attributes affect others; output affected by input)
	attributeAffects(NodeAttr.myInputAttribute, NodeAttr.myOutputAttribute);

	return MS::kSuccess;
}

//=============================================================================================
//INITIALISE PLUGIN
//=============================================================================================
MStatus initializePlugin(MObject obj)
{
	//initialise node
	stat = pluginFn.registerNode("MyNode", MyNode::id, MyNode::creator, MyNode::initialize);
	if(!stat){ stat.perror("Register of 'Node' failed"); }

	return stat;
}
//=============================================================================================
//UNINITIALISE PLUGIN
//=============================================================================================
MStatus uninitializePlugin(MObject obj)
{
	//uninitialise node
	stat = pluginFn.deregisterNode(MyNode::id);
	if(!stat){ stat.perror("Deregister of 'Node' failed"); }

	return stat;
}