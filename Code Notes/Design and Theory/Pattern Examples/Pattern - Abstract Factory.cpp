////////////////////////////////////////////////////////////////////////////////////////////////////////
//ABSTRACT FACTORY PATTERN
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Creational
USE: Creates a group of related objects
     Can be used as a base class to derive different factories which work on different objects

DISADVANTAGE: Many subclasses of factories needed for different object management/creation
ADVANTAGE: Hides creation of objects from user
-------------------------------------------------------------------------------------------*/

#include <vector>
#include "MyObjects.h"
using namespace std;

class ObjectFactory
{
private:

	//container; can use map/hash table
	deque<MyObject*> objects;

public:

	//Create a new object and pass the access ID to the user
	int CreateObject(int objectType)
	{
		MyObject* newobject = nullptr;
		switch(objectType)
		{
		case OBJECT1:
			newobject = new MyObject1();
			break;
		case OBJECT2:
			newobject = new MyObject2();
			break;
		}
		objects.push_back(newobject);
		return (objects.size()-1);
	}

};
