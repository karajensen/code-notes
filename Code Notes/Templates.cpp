//////////////////////////////////////////////////////////////////////////////
//TEMPLATES
//////////////////////////////////////////////////////////////////////////////

// IMPLICIT INSTANTIATION
// Compiler determines what types require templates and creates versions for them only
// keyword 'class' interchangable with 'typename'
template <typename T> void MyFunction(T x) {} 
MyFunction<int>(x) /*or*/ MyFunction(x)

template <typename T, typename S = int> //int = default type, only one allowed on class templates
class MyClass
{
public:
    MyClass<T>() : m_member(S()) {} //<T> optional, initialise templated member to default
    MyClass<T>& operator=(const MyClass<T> & o);
    MyClass(const MyClass<T> & c);
    friend void MyFunction(T& value); ///< friends to all possible instantiations 
private:
    S m_member;
};
MyClass<int, double> obj;

// EXPLICIT INSTANTIATION
// Tells compiler to create a version of the template for the type
// To allow template class/methods to live in .cpp, for every use of template add an explicit instantiation to .cpp file
template MyClass<int>; 
template void MyFunction<int>(int x);

//EXPLICIT SPECIALISATION
//Tells compiler to not use template; use a specialised function instead for the given types
template <> void MyFunction(int x); 
template <> MyClass<int>::MyFunction();

//TRAILING RETURN TYPE
//useful for template functions when return type isn't known
template<typename T, typename C>
auto MyFunction(T x, C y) -> decltype(x+y) { return x+y; }

//TEMPLATES FOR CALLBACKS
template <typename T, typename F>
T UseObjectWithFuntion(T obj, F fn){ return fn(obj); }

//PARTIAL SPECIALIZATION
//Alternative way to do default values
//Can only partially specialize classes, cannot specialise single member functions
template <typename T, typename S> class MyClass {}; 
template <typename T> class MyClassSpec <T, int> {}; // Set S as int
template <typename S> class MyClassSpec <S, S> {}; // Set T as S
template <typename T> void MyClass<T, int>::MyFunction(); // Cannot specialise without specialising whole class
MyClassSpec<float> obj;

//////////////////////////////////////////////////////////////////////////////
//TEMPLATE INHERITANCE
//////////////////////////////////////////////////////////////////////////////

template <typename T> class Base
{
public:
    Base<T>;
    void MyMethod();
};

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

//CURIOUSLY RECURRING TEMPLATE PATTERN (CRTP)
//class A has a base class which is a template specialization for the class A itself.
template <typename A> 
class Base
{
    A& DoSomething();
};
//Class A derives from base and passes own type in
class A : public Base<A> 
{
};

//NESTED TYPES
//Type MyClass::MySubClass seen as static member of class unless typename is used
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
