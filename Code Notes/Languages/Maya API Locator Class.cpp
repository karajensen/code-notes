///////////////////////////////////////////////////////////////////////////////////////////////////////
//LOCATOR CLASS TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////////////////
//Similar to to a Maya node but with extras

//--------------------------------------------------------------------------------------------
//LOCATOR CLASS
//--------------------------------------------------------------------------------------------

#include <iostream>
#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>

#include <maya/MPxNode.h>
#include <maya/MPxLocatorNode.h>
#include <maya/M3dView.h>
#include <maya/MDagPath.h>
#include <maya/MBoundingBox.h>
#include <maya/MTypeId.h>
#include <maya/MPointArray.h>

#include <maya/MFnUnitAttribute.h>
#include <maya/MDistance.h>

//use createNode basicLocator to create
class BasicLocator : public MPxLocatorNode
{
private:

	void GetPoints(MPointArray& points) const;
	struct NodeAttributes
	{
		MObject myAttribute;
	};

public:
	
	virtual void draw(M3dView& view, const MDagPath& path, M3dView::DisplayStyle style, M3dView::DisplayStatus status);
	virtual bool isBounded() const { return true; }
	virtual MBoundingBox boundingBox() const;

	static void* creator(){ return new BasicLocator; }
	static MStatus initialize();

	static MTypeId id;
	static NodeAttributes NodeAttr;

};

MTypeId BasicLocator::id(0x00333);
BasicLocator::NodeAttributes BasicLocator::NodeAttr;

//--------------------------------------------------------------------------------------------
//Get the points
//--------------------------------------------------------------------------------------------
void BasicLocator::GetPoints(MPointArray& points) const
{
	points.clear();
	points.setSizeIncrement(4);
	points.append(-0.5,0.0,0.0);
	points.append(0.5,0.0,0.0);
	points.append(0.0,0.0,0.5);
	points.append(0.0,0.0,-0.5);
}
//--------------------------------------------------------------------------------------------
//Draw the locator
//--------------------------------------------------------------------------------------------
void BasicLocator::draw(M3dView& view, const MDagPath& path, M3dView::DisplayStyle style, M3dView::DisplayStatus status)
{
	//being OpenGL drawing
	view.beginGL();
	glPushAttrib(GL_CURRENT_BIT);

	//Get points to draw from local 0,0,0
	MPointArray points;
	GetPoints(points);

	//Draw points
	glBegin(GL_LINES);
	for(unsigned int i = 0; i < points.length(); i++)
		glVertex3f(float(points[i].x),float(points[i].y),float(points[i].z));
	glEnd();

	//IMPORTANT: OpenGL must be left in same state as before this function is called
	glPopAttrib();
	view.endGL();
}
//--------------------------------------------------------------------------------------------
//Determine the bounds of the locator (for Maya 'frame all' functionality)
//--------------------------------------------------------------------------------------------
MBoundingBox BasicLocator::boundingBox() const
{
	MPointArray points;
	GetPoints(points);
	
	MBoundingBox bbox;
	for(unsigned int i = 0; i < points.length(); i++)
		bbox.expand(points[i]);

	return bbox;
}
//--------------------------------------------------------------------------------------------
//Initialize the node
//--------------------------------------------------------------------------------------------
MStatus BasicLocator::initialize()
{
	MFnUnitAttribute unitFn;
	NodeAttr.myAttribute = unitFn.create("myAttributeName","shortname", MFnUnitAttribute::kDistance);
	unitFn.setDefault(MDistance(1.0,MDistance::uiUnit()));
	unitFn.setMin(MDistance(0.0,MDistance::uiUnit()));
	unitFn.setKeyable(true);
	addAttribute(NodeAttr.myAttribute);

	return MStatus::kSuccess;
}
//=========================================================================================
//INITIALISE PLUGIN
//=========================================================================================
MStatus initializePlugin(MObject obj)
{
	//initialise
	MFnPlugin pluginFn(obj,"VendorName", "1.0");
	MStatus stat = pluginFn.registerNode("basicLocator", BasicLocator::id, BasicLocator::creator, BasicLocator::initialize, MPxNode::kLocatorNode);
	if(!stat){ stat.perror("Register of 'Node' failed"); }

	return stat;
}
//=========================================================================================
//UNINITIALISE PLUGIN
//=========================================================================================
MStatus uninitializePlugin(MObject obj)
{
	//uninitilise
	MFnPlugin pluginFn(obj);
	MStatus stat = pluginFn.deregisterNode(BasicLocator::id);
	if(!stat){ stat.perror("Deregister of 'Node' failed"); }

	return stat;
}
