////////////////////////////////////////////////////////////////////////////////////////////////////////
//BUILDER PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Creational
USE: Takes various objects and puts them together in a meaningful way
	 Can use it with base class pointer so final object can be constructor from any derived class
-------------------------------------------------------------------------------------------*/

//EXAMPLE 1
//Base classes for componenets of the final Node Object
class TileBase
{
public:
	int id;
	int connectedPoleID;
};
class PoleBase
{
public:
	int id;
	int connectedTileID;
};
//Builder takes object componenets and connects them together
class Builder
{
public:
	void BuildNode(TileBase* t, PoleBase* p)
	{
		t->connectedPoleID = p->id;
		p->connectedTileID = t->id;
	}
};

//EXAMPLE 2
//Another version returns the finished new object to something like a Factor to manage/delete
class Builder
{
public:
	Node* BuildNode(TileBase* t, PoleBase* p)
	{
		Node newnode = new Node();
		newnode->AttachTile(t);
		newnode->AttachPole(p);
	}
};
