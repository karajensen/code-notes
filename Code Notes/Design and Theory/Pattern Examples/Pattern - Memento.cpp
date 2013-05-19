////////////////////////////////////////////////////////////////////////////////////////////////////////
//MEMENTO PATTERN
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioural
USE: Seperates state from the object so the state can be saved/restored/undone
	 Command saves the object and the function to use on the object into the history
 -------------------------------------------------------------------------------------------*/

#include <deque>
#include <iostream>
using namespace std;

//MEMENTO
class State
{
public:
    int value;
	State(){ value = 0; }
	State(int v){ value = v; }
};

//BASE OBJECT
class Object
{
private:
    State state;
public:
    Object(State s)					{ state = s;  }
    void CreateMemento(State* s)	{ *s = state; }
    void ReinstateMemento(State* s) { state = *s; }

	virtual void Print()   { cout << state.value << endl; }
	virtual void AddFive() { state.value += 5; }
};

//COMMAND
class Command
{
public:
	typedef void(Object:: *Action)();
	Action m_action;
	Object* m_receiver;
	Command(Object* receiver, Action action) { m_receiver = receiver; m_action = action; }
};

//HISTORY
class History
{
public:
	static const int amount = 20;
	deque<Command*> commands;
	deque<State> states;
	State highestState;
	int current; //last executed command index

	History()
	{ 
		highestState = 0;
		current = 0;
	}
	//----------------------------------------------------------------
	//Execute command
	//----------------------------------------------------------------
	void ExecuteCommand(Command* command)
	{
		current++;
		if(current >= amount)
		{
			current = amount-1;
			commands.pop_front();
			states.pop_front();
		}

		//Add a new command/state to the history
		//State is saved before command is executed
		commands.push_back(command);
		states.push_back(State());
		command->m_receiver->CreateMemento(&states[states.size()-1]);
		(command->m_receiver->*command->m_action)(); //object calls it's method

		//save highest state
		command->m_receiver->CreateMemento(&highestState);
	}
	//----------------------------------------------------------------
	//Undo the commad
	//----------------------------------------------------------------
	void Undo()
	{
		current--;
		if(current < 0)
		{
			current = 0;
			cout << "no more to undo" << endl;
		}
		else
		{
			cout << "undo ";
			commands[current]->m_receiver->ReinstateMemento(&states[current]);
		}
	}
	//----------------------------------------------------------------
	//Redo the command
	//----------------------------------------------------------------
	void Redo()
	{
		if(current >= (int)commands.size())
		{
			cout << "no more to redo" << endl;
			current = commands.size()-1;
			return;
		}
		if(current == commands.size()-1) //if on last state
		{
			cout << "redo ";
			commands[current]->m_receiver->ReinstateMemento(&highestState);
			current++;
		}
		else
		{
			cout << "redo ";
			commands[current]->m_receiver->ReinstateMemento(&states[current+1]);
			current++;
		}
	}

};

int main()
{

	History history;
	Object obj(0);
	obj.Print();
	
	Command cmd(&obj,&Object::AddFive);

	history.ExecuteCommand(&cmd);
	obj.Print();

	history.Undo();
	obj.Print();

	history.Redo();
	obj.Print();

	cin.get();
}