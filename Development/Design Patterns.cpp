/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DESIGN PATTERNS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
--------------------------------------------------------------------------------------------------------------
CREATIONAL PATTERNS
--------------------------------------------------------------------------------------------------------------
ABSTRACT FACTORY  Creates an instance of several families of classes    When requiring interface
FACTORY METHOD    Creates an instance of several derived classes        When requiring object
BUILDER           Different objects are initialised by same process     Complex initialisation sharing      
SINGLETON         A class of which only a single instance can exist     Main application class
PROTOTYPE         A fully initialized instance to be copied             Multiple object variations
                                                   
--------------------------------------------------------------------------------------------------------------
STRUCTURAL PATTERNS  
--------------------------------------------------------------------------------------------------------------
FLYWEIGHT     A fully initialized instance to referenced                       Sharing/Instancing objects
DECORATOR     Allows mixing subclasses to form a final object                  Chaining together individual components
COMPOSITE     A tree class that holds and recurses through child objects       Tree/Node objects
FACADE        A class that manages groups of various objects                   Object managers
PIMPL         Change the single implementation without changing the interface  Data hiding
BRIDGE        Switch multiple implementations without changing the interface   Switching implementations                     
PROXY         A wrapper that provides same functionality as class wrapped      C++/CLI wrappers/pointers
ADAPTER       A wrapper that changes the interface of the class wrapped        Legacy libraries      

--------------------------------------------------------------------------------------------------------------
BEHAVIOURAL PATTERNS
--------------------------------------------------------------------------------------------------------------
MEDIATOR        Talks between two classes that don't know each other        Keep unrelated classes apart
OBSERVER        Looks at another object and updated when that object is     Ad-Hoc object updates
CHAIN OF RESP   Passes a command through series of objects until handled    Events
COMMAND         Holds a method and anything needed to call that method      Functors/lambdas
STATE           Alters an objects behavior when its state changes           Multiple states/behaviours
STRATEGY        Implements from interchangable algorithms                   Switching algorithms
POLICY          Implements from templated inherited classes                 Creating class with multiple implementations
TEMPLATE        Algorithm with some steps as pure virtual functions         Base class/skeleton algorithms
MEMENTO         Allows capture and restore an objects internal state        Undo/Redo
ITERATOR        Allows movement over range of elements in a container       Containers
INTERPRETER     Decodes each symbol in a string for a particular meaning    Compilers
VISITOR         Class methods are seperated into a seperate class           High method code change
*************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FACTORY
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "IMyObject.h"
class Factory
{
public:

    // Creates a new object but doesn't own it
    std::shared_ptr<IMyClass> CreateObject()
    {
        return std::shared_ptr<IMyClass>(new MyClass());
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BUILDER
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Different objects are initialised by same process
class Builder
{
public:

    // Calls overridden build methods of derived to fully construct the object
    void BuildObject(MyBaseClass& object)
    {
        object.BuildSomething();
        object.BuildSomethingElse(m_value);
    }

private:
    int m_value;
};

int main()
{
    Builder myBuilder;

    MyBaseClass* object1 = new MyDerivedClass1();
    myBuilder.BuildObject(object1);

    MyBaseClass* object2 = new MyDerivedClass2();
    myBuilder.BuildObject(object2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SINGLETON
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// A class of which only a single instance can exist
class MyClass : boost::noncopyable
{
public:

    // Returns the pointer to the single instance of the class
    static MyClass* GetPointer()
    {
        if(!sm_singleton)
        {
            sm_singleton.reset(new MyClass());
        }
        return sm_singleton.get();
    }

private:
    static std::unique_ptr<MyClass> sm_singleton;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROTOTYPE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TemplateTypes
{
    TemplateAB,
    TemplateCD
};

// A fully initialized instance to be copied 
std::vector<MyClass> m_templates;
m_template.push_back(MyClass(a,b));
m_template.push_back(MyClass(c,d));

// Use the templates to initialise new objects
MyClass object1 = m_templates[TemplateAB];
MyClass object2 = m_templates[TemplateCD];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FLYWEIGHT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TemplateTypes
{
    TemplateAB,
    TemplateCD
};

// A fully initialized instance to referenced
std::vector<std::shared_ptr<MyClass>> m_templates;
m_template.push_back(std::shared_ptr<MyClass>(new MyClass(a,b)));
m_template.push_back(std::shared_ptr<MyClass>(new MyClass(c,d)));

// Usage of the templates is shared
std::shared_ptr<MyClass> object1(m_templates[TemplateAB]);
std::shared_ptr<MyClass> object2(m_templates[TemplateCD]);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DECORATOR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Abstract base class for all decorator objects
class MyBaseClass 
{
public:
    virtual void MyMethod() = 0;
};

// Default implementation of base class as final 'stopper' for decorator chaining
class MyDerivedClass: public MyBaseClass 
{
public:
    virtual void MyMethod() override {}
};

// Base decorator class that takes in the next decorator in the chain
class Decorator: public MyBaseClass
{
public:

    Decorator(MyBaseClass* object) :
        m_inner(object)
    { 
    }

    // Calls the next decorator or stopper in the chain
    virtual void MyMethod() override   
    { 
        m_inner->MyMethod();
    }

private:
    std::unique_ptr<MyBaseClass> m_inner;
};

// Decorator link X
class X: public Decorator
{
public:

    X(MyBaseClass* object) : 
        Decorator(object)
    {
    }

    // Do something for X then call the next link
    virtual void MyMethod() override 
    {
        Decorator::MyMethod(); 
    }
};

// Decorator link Y
class Y: public Decorator 
{
public:

    Y(MyBaseClass* object) : 
        Decorator(object)
    {
    }

    // Do something for Y then call the next link
    virtual void MyMethod() override 
    { 
        Decorator::MyMethod(); 
    }
};

// Decorator link Z
class Z: public Decorator
{
public:

    Z(MyBaseClass* object) : 
        Decorator(object)
    {
    }

    // Do something for Z then call the next link
    virtual void MyMethod() override 
    { 
        Decorator::MyMethod();
    }
};

int main() 
{ 
    // Allows mixing subclasses to form a final object
    // Each decorate class holds MyBaseClass of next in link
    // Creation order right to left with MyDerivedClass acting as a stopper
    std::unique_ptr<MyBaseClass> x(new X(new MyDerivedClass()));
    std::unique_ptr<MyBaseClass> yx(new Y(new X(new MyDerivedClass())));
    std::unique_ptr<MyBaseClass> xzy(new X(new Z(new Y(new MyDerivedClass()))));

    x->MyMethod();    // calls x, Decorator, MyDerivedClass
    yx->MyMethod();   // calls y, x, Decorator, MyDerivedClass
    xzy->MyMethod();  // calls x, z, y, Decorator, MyDerivedClass
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPOSITE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// A tree class that holds and recurses through child objects
class Node
{
public:

    void AddChild(std::shared_ptr<Node> node)
    {
        m_nodes.push_back(node);
    }

    void IterateChildren() 
    {
        for(const std::shared_ptr<Node>& node : m_nodes)
        {
            node->IterateNodes();
        }
    }

private:
    std::vector<std::shared_ptr<Node>> m_children;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FACADE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// A class that manages groups of various objects
class Facade
{
public:

    // Use objects owned by facade in meaningful way
    void DoSomething()
    {
        m_objB->MyFunction();
        m_objA->MyOtherFunction();
    }

private:

    MyClassA m_objA;
    MyClassB m_objB;
    MyClassC m_objC;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PIMPL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Change the single implementation without changing the interface
class MyClass
{
public:

   void MyMethod();

private:

   class MyClassPimpl; 
   std::unique_ptr<MyClassPimpl> m_pimpl;
};

// Internal class lives in .cpp file
class MyClass::MyClassPimpl
{
public:

    // Actual method implementation here
   void MyMethod()
   {
   }
};
 
// Creation of internal class in .cpp
MyClass::MyClass():  
    m_pimpl(new MyClassPimpl())
{
}

// Calling of internal class in .cpp
void MyClass::MyMethod()
{
   m_pimpl->MyMethod();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BRIDGE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Switch multiple implementations without changing the interface
class Implementation
{
    virtual void MyMethod = 0;
}

// Implementation type A
class ImplementationA : public Implementation
{
    virtual void MyMethod() override;
};

// Implementation type B
 class ImplementationB : public Implementation
{
    virtual void MyMethod() override;
};

 // Base class for switching implementations
 class MyClass
 {
 public:

     // Change the currently set implementation
     void ChangeImplementation(Implementation* imp)
     {
         m_implementation.reset(imp);
     }

     // Call the currently set implementation
     void MyMethod()
     {
         m_implementation->MyMethod();
     }

 private:
     std::unique_ptr<Implementation> m_implementation;
 }

 // ClassA initially sets desired implementation
 class MyClassA
 {
     MyClassA()
     {
         ChangeImplementation(new ImplementationA());
     }
 };

 // ClassB initially sets desired implementation
 class MyClassB
 {
     MyClassB()
     {
         ChangeImplementation(new ImplementationB());
     }
 };

 int main()
 {
     std::unique_ptr<MyClassA> objA(new MyClassA()); // has A implementation
     std::unique_ptr<MyClassB> objB(new MyClassB()); // has B implementation
     objA->ChangeImplementation(new ImplementationB()); // now has B implementation
 }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROXY
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// A wrapper that provides same functionality as class wrapped
public ref class ManagedWrapper
{
public:

    // Call the inner object method
    void DoSomething()
    {
        m_native->DoSomething();
    }

private:
    NativeObject* m_native;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ADAPTER
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// A wrapper that changes the interface of the class wrapped
class Adapter
{
public:

    // Add some extra functionality and call the legacy method
    void NewFunction()
    {
        m_legacyClass->LegacyFunction();
    }

private:
    std::unique_ptr<LegacyClass> m_legacyClass;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEDIATOR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Talks between two classes that don't know each other
class Mediator
{
public:

    // Add a class to be talked to by all others in list
    void AddClass(MediatedClass* obj)
    {
        m_objs.push_back(obj);
    }

    // Send a message to all list classes except the sender
    void SendMessage(const MediatedClass* sender, const std::string& message)
    {
        for(MediatedClass* obj : m_objs)
        {
            if(obj != sender)
            {
                obj->RecieveMessage(message);
            }
        }
    }

private:
    std::vector<MediatedClass*> m_objs;
};

// Any unrelated classes that want to be mediated derive from this
class MediatedClass
{
public:

    MediatedClass(Mediator& mediator) : 
        m_mediator(mediator)
    {
        mediator.AddClass(this);
    }

    // Send message to all mediated classes
    void SendMessage(const std::string& message)
    {
        m_mediator.SendMessage(this, message);
    }

    // Called by the mediator
    virtual void RecieveMessage(const std::string& message) = 0;

private:
    Mediator& m_mediator;
};

// Mediated class type 1
class MyClass1 : public MediatedClass
{
    MyClass1(Mediator& mediator) :
        MediatedClass(mediator)
    {
    }

    // Called by the mediator
    virtual void RecieveMessage(const std::string& message) override
    {
    }
};

// Mediated class type 2
class MyClass2 : public MediatedClass
{
    MyClass2(Mediator& mediator) :
        MediatedClass(mediator)
    {
    }

    // Called by the mediator
    virtual void RecieveMessage(const std::string& message) override
    {
    }
};

int main()
{
    std::unique_ptr<Mediator> mediator(new Mediator());
    std::unique_ptr<MyClass1> obj1(new MyClass1(*mediator));
    std::unique_ptr<MyClass2> obj2(new MyClass2(*mediator));

    obj1->SendMessage("hello from obj1");
    obj2->SendMessage("hello from obj2");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OBSERVER
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Looks at another object and updated when that object is
class MyClass
{
public:

    // Update any obsevers when changing state
    void ChangeSomething()
    {
        m_myInt++;
        if(m_observer)
        {
            m_observer->Update(m_myInt);
        }
    }

    void SetObserver(std::shared_ptr<Observer> observer)
    {
        m_observer.reset(observer);
    }

private:
    std::shared_ptr<Observer> m_observer;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHAIN OF RESPONSIBILITY
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Passes a command through series of objects until handled
class ChainMember
{
public:

    // Set the next link in the chain
    void SetSuccesser(std::shared_ptr<ChainMember> member)
    {
        m_successor = member;
    }

    void ProcessEvent(Event& e)
    {
        if(e.receiver == this)
        {
            // process the event
        }
        else if(m_successor)
        {
            m_successor->ProcessEvent(e);
        }
    }
private:
    std::shared_ptr<ChainMember> m_successor;
};


int main()
{
    std::unique_ptr<ChainMember> member1(new ChainMember());
    std::unique_ptr<ChainMember> member2(new ChainMember());
    std::unique_ptr<ChainMember> member3(new ChainMember());

    member1->SetSuccesser(member2);
    member2->SetSuccesser(member3);
    member1->ProcessEvent(e); // calls member1, member2, member3
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMMAND
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Holds a method and anything needed to call that method
std::function<void(void)> command = std::bind(&MyClass::MyFunction, this, myInt);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STATE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Alters an objects behavior when its state changes
class State
{
    virtual void ChangeState(MyClass& obj) = 0;
};

class StateA : public State
{
    virtual void ChangeState(MyClass& obj) override;
};

class StateB : public State
{
    virtual void ChangeState(MyClass& obj) override;
};

class MyClass
{
public:

    void MyMethod()
    {
        // do something that triggers a state change
        m_state->ChangeState(*this);
    }

    // Takes ownership of a new state
    void SetState(State* state)
    {
        m_state.reset(state);
    }

private:
    std::unique_ptr<State> m_state;
};

// In .cpp to prevent forward declaration of StateB
void StateA::ChangeState(MyClass& obj)
{
    obj.SetState(new StateB());
}

// In .cpp to prevent forward declaration of StateA
void StateB::ChangeState(MyClass& obj)
{
    obj.SetState(new StateA());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STRATEGY
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Family of interchangable algorithms 
class SortStrategy
{
    virtual void Sort(std::vector<std::string>& container) = 0;
};

class QuickSort : public SortStrategy
{
public:
    virtual void Sort(std::vector<std::string>& container) override;
};

class ShellSort : public SortStrategy
{
public:
    virtual void Sort(std::vector<std::string>& container) override;
};

class MyClass
{
public:

    MyClass(SortStrategy& strategy) :
        m_strategy(strategy)
    {
    }

    void ChangeSortStrategy(SortStrategy& strategy)
    {
        m_strategy = strategy;
    }

    void Sort()
    {
        m_strategy.Sort(m_container);
    }

private:
    std::vector<std::string> m_container;
    SortStrategy& m_strategy;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Algorithm with only function calls to other classes
class MyBaseClass
{
public:

    virtual void Step1() = 0;
    virtual void Step2() = 0;
    virtual void Step3() = 0;

    void MyAlgorithm()
    {
        Step1();
        Step2();
        Step3();
    }
};

class MyClass1 : public MyBaseClass
{
public:
    virtual void Step1() override {}
    virtual void Step2() override {}
    virtual void Step3() override {}
};

class MyClass2 : public MyBaseClass
{
public:
    virtual void Step1() override {}
    virtual void Step2() override {}
    virtual void Step3() override {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEMENTO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Allows capture and restore an objects internal stat
class Memento
{
public:

    void Undo()
    {
        if(!m_states.Empty())
        {
            m_currentState = m_states[m_states.size()-1];
            m_states.pop_back();
        }
    }

    void ChangeState()
    {
        if(m_states.Size() > MAX_SIZE)
        {
            m_states.pop_front();
        }
        m_states.push_back(m_currentState);
        m_currentState.myInt++;
    }

private:
    std::deque<State> m_states;
    State m_currentState;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITERATOR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Allows movement over range of elements in a container
for(std::vector<int>::iterator itr = myVector.begin(); itr != myVector.end(); ++itr)
{
    itr->myMethod();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERPRETER
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Decodes each symbol in a string/object for a particular meaning
class One : public Interpreter
{
public:

    // Read the string then can remove chosen key if needed
    void Interpret(std::string str)
    {
        if(str.find("one") != std::string::npos)
        {
            DoSomething();
        }
    }
};

class Two : public Interpreter
{
public:

    // Read the string then can remove chosen key if needed
    void Interpret(std::string str)
    {
        if(str.find("two") != std::string::npos)
        {
            DoSomething();
        }
    }
};

int main()
{
    std::vector<std::unique_ptr<Interpreter>> myContainer;
    myContainer.push_back(std::unique_ptr<Alphabet>(new ClassA));
    myContainer.push_back(std::unique_ptr<Alphabet>(new ClassB));
    myContainer.push_back(std::unique_ptr<Alphabet>(new ClassA));

    std::string myString("onetwofive");
    for(auto& interpreter : myContainer)
    {
        interpreter->Interpret(myString);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VISITOR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Holds only private internal data
class ClassObject
{
private:
    friend class ClassMethods;
    int m_myInt;
};

// Class methods are seperated into a seperate class
class ClassMethods
{
public:

    void DoSomething(MyClass& obj)
    {
        obj.m_myInt = 10;
    }

    void DoSomethingElse(MyClass& obj)
    {
        obj.m_myInt = 20;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POLICY BASED DESIGN
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BASIC PATTERN: Host class inherits from one policy class
class PolicyClassA
{
public:
    void DoSomething(){}
protected:
    ~PolicyClassA(){} // protected non-virtual destructor prevents polymorphism
};

class PolicyClassB
{
public:
    void DoSomething(){}

    // can define extra functions to use outside host cass
    // require specialisation if using in host class
    void DoSomethingElse(){} 

protected:
    ~PolicyClassB(){} // protected non-virtual destructor prevents polymorphism
};

template <typename MyPolicy>
class MyHostClass : public MyPolicy
{
public:

    void MyFunction()
    {
        MyPolicy::DoSomething();
    }
};

// ADVANCED PATTERN: Templated policy classes
template <template <typename> class MyPolicy> 
class MyHostClass : public MyPolicy<double> // optional
{
    void MyIntFunction(){ MyPolicy<int>().DoSomething(); }
    void MyDoubleFunction(){ MyPolicy<double>().DoSomething(); }
    void MyObjFunction(){ MyPolicy<MyClass>().DoSomething(); }
};

MyHostClass<PolicyClassA> objA;
MyHostClass<PolicyClassB> objB; 

objA.DoSomething();
objB.DoSomething();
objB.DoSomethingElse();

