////////////////////////////////////////////////////////////////////////////////////////////////////////
//CHAIN OF RESPONSIBILITY PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioural
USE: Passes a command through a series of objects until one can handle it
-------------------------------------------------------------------------------------------*/

//COMMAND
class Object;
class Command
{
public:
	typedef void(Object::*Method)();
	Method m_method;
	int ID;
	Command(int id, Method method) { ID = id; m_method = method; }
};

//CHAINING OBJECTS
class Object
{
public:
	Object* next;
	int ID;

	Object(Object* Next){ next = Next; }
	void ChainOfResponsibility(Command* c)
	{
		if(c->ID == ID)
			(this->*(c->m_method))();
		else if(next != 0)
			next->ChainOfResponsibility(c);
		else
			return;
	}

};