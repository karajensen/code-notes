////////////////////////////////////////////////////////////////////////////////////////////////////////
//COMMAND PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioural
USE: Encapsulate a function/method and any extra information within an object and sends this to 
     another object to be called later. Uses pointer functions/functors
-------------------------------------------------------------------------------------------*/

//BASE OBJECT
class Object
{
private:
    int someValue;
public:
    virtual void Print();
    virtual void AddFive();
};

//COMMAND
//Can be used as a functor
class Command
{
public:
    typedef void(Object::*Method)();
    Method m_method;
    Object* m_receiver;

    Command(Object* receiver, Method method) { m_receiver = receiver; m_method = method; }
    void operator()(){ (m_receiver->*m_method)(); }
};