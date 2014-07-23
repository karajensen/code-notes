//////////////////////////////////////////////////////////////////////////////
//TEMPLATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//IMPLICIT INSTANTIATION
//Compiler substitutes T for the variable needed
//only types that require it will create a version of the template
//class/typename interchangable
template <class T> void MyFunction(T x);
template <typename T> void MyFunction(T x);

//EXPLICIT INSTANTIATION
//use template to create function for type int
//To allow template class/methods to live in .cpp, for every use of 
//template add an explicit instantiation to .cpp file
template MyClass<float>; //for class templates
template void MyFunction<int>(int x, int y); //for function templates

//EXPLICIT SPECIALISATION
//don't use template; use a specialised function coded instead
template <> void MyFunction(char x, char y); 

//TRAILING RETURN TYPE
//useful for template functions when return type isn't known
template<typename T, typename C>
auto myFunction(T x, C y) -> decltype(x+y){ return x+y; }

//TEMPLATES FOR CALLBACKS
template <typename T, typename F>
T UseObjectWithFuntion(T obj, F fn){ return fn(obj); }

//EXPLICITLY CALLING A VERSION OF A TEMPLATE
MyFunction<int>(x, y);
MyFunction<float>(x, y);

//////////////////////////////////////////////////////////////////////////////
//CLASS TEMPLATES
//////////////////////////////////////////////////////////////////////////////

template <typename T, typename S = int> //int = default type, only allowed on class templates
class MyClass
{
public:

    //constructor, <T> not required
    MyClass<T>() : 
        m_member(S()) //initialise templated member to default
    {
    }
   
    ~MyClass<T>(); //destructor, <T> not required
    MyClass<T>& operator=(const MyClass<T> & o); //assignment operator
    MyClass(const MyClass<T> & c); //copy constructor

private:

    S m_member; //member of type S
};

MyClass<int> intobj;
MyClass<int,double> pairObj;

//////////////////////////////////////////////////////////////////////////////
//TEMPLATE INHERITANCE
//////////////////////////////////////////////////////////////////////////////

//BASE CLASS
template <typename T> class Base
{
public:
    Base<T>;
    void MyMethod();
};

//DERIVED CLASS
template <typename T> class Derived : public Base<T> 
{
    Derived():Base<T>
    {}

    void MyMethod()
    {
        //Need accesser as base class template methods 
        //cannot be found when using inheritance
        Base<T>::MyMethod();
    }
};

//////////////////////////////////////////////////////////////////////////////
//NESTED TYPES
//////////////////////////////////////////////////////////////////////////////
// Type MyClass::MySubClass seen as static member of class unless typename is used

template<typename T, typename C>
class Derived: public Base<T>::Nested //don't use typename
{
public:          

    explicit Derived(int x) : 
        Base<T>::Nested(x)  //don't use typename
    {}

    void MyFunction(typename C::MyValue& myValue); //use typename
 
private
    typename Base<T>::Nested temp; //use typename 
    std::unique_ptr<typename C::MyValue> myPtr; //use typename
};

//////////////////////////////////////////////////////////////////////////////
//PARTIAL SPECIALIZATIONS
//////////////////////////////////////////////////////////////////////////////

//PARTIAL SPECIALIZATION
template <class T, class S> class Pair {}; //original template
template <class T> class Pair<T, int> {}; //S is specialised to int

//POINTER PARTIAL SPECIALIZATION
template <class T> class Pair {};
template <class T*> class Pair {};

//RESTRICTING WITH PARTIAL SPECIALIZATION
//Alternative way to do default values
template <class T, class S, class R> class Pair {}; //original template
template <class T, class S> class Pair<T,S,S> {}; //R is specialised to S
Pair<int, float> obj; //makes R same type as S

//////////////////////////////////////////////////////////////////////////////
//TEMPLATE CLASS FRIENDS
//////////////////////////////////////////////////////////////////////////////

//NON TEMPLATE FRIEND FUNCTIONS
//Allows the function to be friends to all possible instantiations 
template <class T>
class Tclass
{
public:
    friend void friendFunction(Tclass<T> &); //friend to all instantiations
};

void Tclass::counts(Tclass<T> &)
{
};

//BOUND TEMPLATE FRIEND FUNCTIONS
//template prototypes before class declaration
template <class T> void testOne();
template <class T> void testTwo(T &);

//template class
template <class C>
class Tclass
{
public:
    friend void testOne<C>();
    friend void testTwo<C>(Tclass<C> &);
};

template <typename T>
void testOne()
{
}
template <typename T>
void testTwo(T & hf)
{
}

//UNBOUND TEMPLATE FRIEND FUNCTIONS
template <typename T>
class ManyFriend
{
public:
    template <typename C, typename D> friend void testOne(C &, D &);
};

//////////////////////////////////////////////////////////////////////////////
//VARIADIC TEMPLATES
//////////////////////////////////////////////////////////////////////////////
//accept a variable number of arguments

template<typename T, typename... Args> // Args is a template parameter pack
void show_list(const T& value, const Args&... args) // args is a function parameter pack
{
    //uses recursion to take first element from list
    //sends rest to next call of function
    cout << value << ",";
    show_list(args...);
}

//can use any number, order or type of arguments
show_list(2.0,"hello",4*2,'c');
show_list(1.0,'d',"astring");

//////////////////////////////////////////////////////////////////////////////
//CURIOUSLY RECURRING TEMPLATE PATTERN (CRTP)
//////////////////////////////////////////////////////////////////////////////
//Occurs when class A has a base class which is a template specialization 
//for the class A itself.

//Template base class
template <class Derived> 
class Base
{
    Derived& doSomething();
};
//Class A derives from base and passes own type in
class A : public Base<A> 
{
};

