///////////////////////////////////////////////////////////////////////////////////////////////////////
//SENDING EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////////
//DESIGN PATTERN: OBSERVER

struct message
{
    long type; //event type
    long time; //dispatch time
    long delay; //how long to keep message before sending
    OBJHANDLE sender; //if observer needs to know what sent message
    OBJHANDLE receiver; //if sender wants a particular observer to recieve
    void * data;
};

OBJHANDLE
//OBJHANDLE: Flyweight reference to objects
//FLYWEIGHT: Instantiate multiple instances of a class which all refer to a common component
//Using a simple pointer can be dangerous if object is deleted; use smart pointer or object int ID

void * data
//Message information cast to void pointer
//Recast depending on message type (use switch with type to determine correct cast)

//UNION MESSAGE EXAMPLE
struct InputEvent
{
    enum EType
    {
        MOUSE, KEYBOARD, JOYSTICK
    } Type;
    
    union UEvent
    {
        struct SMouse
        {
            bool buttonDown[3];
            bool buttonUp[3];

        } Mouse;

        struct SJoystick
        {
            float Axis[8];
            bool Buttons[32];
            char Hats[4];
        } JoyStick;

        struct SKeyboard
        {
            bool Keys[255];
        } Keyboard;

    } Event;
};

InputEvent msg;
msg.Type = InputEvent::MOUSE;
msg.Event.Mouse.buttonDown[0] = true; //change values depending on type 


///////////////////////////////////////////////////////////////////////////////////////////////////////
//DISPATCHING EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////////
//DESIGN PATTERN: MEDIATOR

std::map<Message type, Observers subscribed to Message type>
std::map<unsigned long, std::list<GameEntity*>>   //observers are list of pointers
std::map<unsigned long, std::list<unsigned long>> //observers are list of object IDS

//A Simple pointer can be dangerous if object is deleted; use smart pointer or object int ID
//ID is given to entity repository and asks for reference/pointer to object
//If object doesn't exist, null is handed back


///////////////////////////////////////////////////////////////////////////////////////////////////////
//HANDLING EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////////
//DESIGN PATTERN: COMMAND

//Objects that are observers derive from base class and override OnMessage
//OnMessage returns a bool to indicate whether message was processed by object or not
template <typename E>
class GameEntity
{
    public:
        virtual bool OnMessage(E & msg) = 0;
        //Other methods game entities may need to share
};
