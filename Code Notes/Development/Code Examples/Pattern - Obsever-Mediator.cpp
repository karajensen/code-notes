////////////////////////////////////////////////////////////////////////////////////////////////////////
//MEDIATOR/OBSERVER PATTERN
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioural
USE: Mediator and Observer are coupled together when used in event handling
     When an object's state changes, it sends an event message to the mediator
     The mediator will notify any observers of the object about the change
     Mediator talks between two classes without either having to know about the other
 -------------------------------------------------------------------------------------------*/

//-------------------------------------------------------------
//BASIC OBSERVER
//-------------------------------------------------------------
class Observer;
class Object
{
public:
    Observer* observer;
    void AttachObserver(Observer* ob){ observer = ob; }
    void ChangeState(){ /*change state*/ observer->ChangeState(); }
};
class Observer
{
public:
    void ChangeState();
};
//-------------------------------------------------------------
//BASIC MEDIATOR
//-------------------------------------------------------------
class ObjectMediator
{
public:
    void CallStuff()
    {
        //casses that Object doesn't know about
        Object2->Stuff();
        Object3->Stuff();
    }
};

class Object
{
public:
    ObjectMediator * med;
    void Method(){ med->CallStuff(); }
};



//-------------------------------------------------------------
//OBSERVER WITH MEDIATOR
//-------------------------------------------------------------
class Object;
class Observer;
struct Message
{
    int ID;
    void* message;
    Message(int id, void* m=0){ ID = id; message = m; }
};
class Mediator
{
public:
    /*hash table*/
    static void ProcessMessage(Message& m)
    {
        //look up hash table using sending object's ID
        //to find attached observers and send them a message
    };
    static void AttachObserver(Object* observer, int ID)
    {
        //look up hash table using object's ID
        //attach the observer under the ID
    };
};

class Object
{
    int ID;
    void ChangeState(){ Mediator::ProcessMessage(Message(ID)); }
};