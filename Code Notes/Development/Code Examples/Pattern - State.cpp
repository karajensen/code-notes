////////////////////////////////////////////////////////////////////////////////////////////////////////
//STATE PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioral
USE: Alters an object's behaviour when its state changes
-------------------------------------------------------------------------------------------*/

//---------------------------------------------
//EXAMPLE 1
//---------------------------------------------
class State
{
public:
    enum StateType{ ONE=1,TWO=2,THREE=3 };
    int value;
    bool ChangeState(StateType type); //return true if state changed
};

class Object
{
public:
    State state;
    bool ChangeState(State::StateType type) { return state.ChangeState(type); }
    void DoSomething()
    {
        switch(state.value)
        {
            case 1: //do this
            case 2: //do that
            case 3: //do soemthing else
        }
    }
};

//---------------------------------------------
//EXAMPLE 2
//---------------------------------------------