////////////////////////////////////////////////////////////////////////////////////////////////////////
//PROTOTYPE PATTERN
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Creational
USE: Create objects by copying previously made ones

DISADVANTAGE: Each object needs a copy function that provides a deep copy
ADVANTAGE: Reduces the need to create derived classes like with a base factory class
		   Allows loading of custom classes on run-time
		   Avoids using slow 'new/delete' to create objects as uses copying
-------------------------------------------------------------------------------------------*/

#include <vector>
#include "MyObjects.h"
using namespace std;

//An object derived from MyObject
class Object1 : public MyObject
{
private:
	int value;
public:
	//overloaded/virtual clone function, do deep copy if needed
	virtual Object1 Clone(); 
};

//Prototype class
class Prototype
{
private:
	vector<MyObject*> objects;

public:

	//Add a template object to copy from
	int AddObject(MyObject* o)
	{
		objects.push_back(o);
		return objects.size()-1;
	}
	//Get a template object
	MyObject* GetObject(int id)
	{
		return objects[id];
	}
};

//Create the template objects and add to the prototype class
Object1 baseObject1;
int id = prototype->AddObject(baseObject1);

//Any additional objects of that type can just be cloned
Object1 newObject1 = prototype->GetObject(id)->Clone();