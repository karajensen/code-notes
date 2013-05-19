//////////////////////////////////////////////////////////////////////////////
//TEMPLATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------
//TRAILING RETURN TYPE
//-------------------------------------------------------------------
//shifts the return type to after the function arguments
double myFunction(int x, int y) {} /*or*/
auto myFunction(int x, int y) -> double {}
auto myFunction(int x, int y) -> decltype(x) {} //make return type same as x

//useful for template functions when return type isn't known
template<class T, class C>
auto myFunction(T x, C y) -> decltype(x+y){ return x+y; }

//-------------------------------------------------------------------
//TEMPLATES WITH CALLBACKS
//-------------------------------------------------------------------
template <typename T, typename F>
T use_f(T v, F f){ return f(v); }

//-------------------------------------------------------------------
//EXPLICIT SPECIALISATION
//-------------------------------------------------------------------
//don't use template; use a specialised function coded instead
template <> void testspec(char x, char y); 

//-------------------------------------------------------------------
//EXPLICIT INSTANTIATION
//-------------------------------------------------------------------
//use template to create function for type int
template void Swap<int>(int x, int y); 

//-------------------------------------------------------------------
//IMPLICIT INSTANTIATION (normal)
//-------------------------------------------------------------------
//Compiler substitutes 'any' for the variable needed (int, double etc.)
template <class Any> 
void Swap(Any &a, Any &b) 
{
    Any temp; //declare new Any variable
    temp = a;
    a = b;
    b = temp;
}
//-------------------------------------------------------------------
//EXPLICITLY CALLING A VERSION OF A TEMPLATE
//-------------------------------------------------------------------
Swap<int>(var1, var2);
Swap<float>(var1, var2);

//////////////////////////////////////////////////////////////////////////////
//CLASS TEMPLATES
//////////////////////////////////////////////////////////////////////////////

template <typename T, typename S = int> //int = default type, only allowed on class templates
class Tclass
{
private:
    T * item;
public:

    //CONSTRUCTOR
    Tclass(){ item = new T; }

    //DESTRUCTOR
    ~Tclass(){ delete item; }

    //METHODS
    void TestFunction(const T & item){}

    //ASSIGNMENT OPERATOR
    Tclass<T> & operator=(const Tclass<T> & o)
    {
        if (this == &o)
            return *this;
        delete item;
        item = new T;
        *item =*o.item;
        return *this;
    }

    //COPY CONSTRUCTOR
    Tclass(const Tclass<T> & c)
    {
        item = new T;
        *item = *c.item; 
    }

    //GENERALISED COPY CONSTRUCTOR
    template<typename U>
    Tclass(const Tclass<U>* other) : item(other) {}

    //FRIEND CLASS WITH OPERATOR OVERLOAD
    //use a non-member function (friend) to allow implicit conversion
    friend const Tclass<T> operator*(const Tclass<T>& lhs, const Tclass<T>& rhs)
    { return doMultiply(lhs, rhs); }
};

//main.cpp
Tclass<int> intobj; //create instantiation of class using template
Tclass<int,double> pairObj; //for paired templates

//////////////////////////////////////////////////////////////////////////////
//TEMPLATE INHERITANCE
//////////////////////////////////////////////////////////////////////////////

//BASE CLASS
template <typename T> class BaseClass
{
public:
    BaseClass<T>(){}

    void SomeFunction()
    { 
        /*do something*/ 
    }
};

//DERIVED CLASS
template <typename T> class DerivedClass : public BaseClass<T> 
{
    //CONSTRUCTOR
    DerivedClass():BaseClass<T>{}

    //CALLING BASE CLASS METHODS
    void SomeFunction()
    {
        //Need accesser as base class template methods cannot be found when using inheritance
        BaseClass<T>::SomeFunction();
    }
};


//////////////////////////////////////////////////////////////////////////////
//TEMPLATE SPECIALIZATIONS
//////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------
//IMPLICIT INSTANTIATION (Normal use)
//-------------------------------------------------------------------
//compiler will create a class from the template for the object
Tclass<int,double> Tobj;

//-------------------------------------------------------------------
//EXPLICIT INSTANTIATION
//-------------------------------------------------------------------
//the compiler uses the general template to generate an int instantiation 
//even though no objects have yet been requested of that class.
template class Tclass<int, 100>; //in main.cpp

//-------------------------------------------------------------------
//EXPLICIT SPECIALIZATION
//-------------------------------------------------------------------
//Uses this template instead of normal one for the specific type
template <> 
class Tclass<char *> //in Tclass.h
{
private:
public:
};

//-------------------------------------------------------------------
//PARTIAL SPECIALIZATION
//-------------------------------------------------------------------
//For specialising when there's more than one value passed in
template <class T, class S> //original template
class Pair 
{
};
//specialising original template partially;
//what's not specialised is in first <>
template <class T> 
class Pair<T, int> //S is specialised to int
{
};

//-------------------------------------------------------------------
//POINTER PARTIAL SPECIALIZATION
//-------------------------------------------------------------------
template <class T>
class Pair
{
};
template <class T *>
class Pair
{
};

//-------------------------------------------------------------------
//RESTRICTING WITH PARTIAL SPECIALIZATION
//-------------------------------------------------------------------
//Alternative way to do default values
template <class T, class S, class R>
class Pair
{
};
template <class T, class S> //what's not specialised goes here
class Pair<T,S,S> //R is set to S
{
};

Pair<int, float> pairObj; //makes R same type as S


//////////////////////////////////////////////////////////////////////////////
//TEMPLATES AS PARAMETERS
//////////////////////////////////////////////////////////////////////////////

//pass float into class two which is used as type for class one
one < two <float> >;

template <typename T>
class two
{
};

template < template<typename T> typename S>
class one
{
private:
    S oneobj; //make S using the type of T
}

//////////////////////////////////////////////////////////////////////////////
//TEMPLATE CLASS FRIENDS
//////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------
//NON TEMPLATE FRIEND FUNCTIONS
//---------------------------------------------------------------
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
//---------------------------------------------------------------
//BOUND TEMPLATE FRIEND FUNCTIONS
//---------------------------------------------------------------
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
//---------------------------------------------------------------
//UNBOUND TEMPLATE FRIEND FUNCTIONS
//---------------------------------------------------------------
template <typename T>
class ManyFriend
{
public:
    template <typename C, typename D> friend void testOne(C &, D &);
};


//////////////////////////////////////////////////////////////////////////////
//TEMPLATE NESTED TYPES
//////////////////////////////////////////////////////////////////////////////

//if a type (C::iterator) can be seen as either a static member of class 
//C or a type of C, must use typename before the type is declared
//Exception is for base object in derived class constructors

//EXAMPLE1
template<class C> 
void f(const C& container, typename C::iterator iter);

//EXAMPLE2
template<typename T>
class Derived: public Base<T>::Nested //don't use typename
{
public:                               
    explicit Derived(int x) : 
        Base<T>::Nested(x)  //don't use typename
    {}
 
    typename Base<T>::Nested temp; //use typename 
};

//EXAMPLE3
//value_type is nested inside iterator_traits<IterT> 
//and IterT is a template parameter
template<class IterT>
void workWithIterator(IterT iter)
{
    typedef typename std::iterator_traits<IterT>::value_type value_type;
    value_type temp(*iter);
}

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

