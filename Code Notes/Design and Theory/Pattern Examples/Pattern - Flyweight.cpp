////////////////////////////////////////////////////////////////////////////////////////////////////////
//FLYWEIGHT PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Structural
USE: Use of an object/static variables to store common information for a group of objects
     Reduces amount of memory used to store common values for objects
-------------------------------------------------------------------------------------------*/

//FLYWEIGHT
class MyObjectFlyweight
{
	int groupValue;
};

//EXAMPLE1
class MyObject
{
public:
	int individualValue;
	void SetValue(MyObjectFlyweight& f)
	{
		individualValue = f.groupValue;
	}
}

//EXAMPLE2
class MyObject
{
	static MyObjectFlyweight f;
	int individualValue;
	void SetValue(MyObjectFlyweight& f)
	{
		individualValue = f.groupValue;
	}
};

