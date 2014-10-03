//////////////////////////////////////////////////////////////////////////////
//TEMPLATES
//////////////////////////////////////////////////////////////////////////////

//- Only creates instantiation of template for objects used with the template
//- Will force create version of template with explicit instantiation
//- Only adds methods to template instantiation if object actually uses the method
//- Keyword 'class' interchangable with 'typename'

// IMPLICIT INSTANTIATION
// Compiler determines what types require templates and creates versions for them only
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
template void MyFunction<int>(MyClass<int>& x);

//EXPLICIT SPECIALISATION
//Tells compiler to not use template; use a specialised function instead for the given types
template <> void MyFunction(int x); 
template <> MyClass<int>::MyFunction();

//CLASSES: PARTIAL SPECIALIZATION
//Can only partially specialize at class level, not member functions
template <typename T, typename S> class MyClass {}; 
template <typename T> class MyClassSpec <T, int> {}; // Set S as int
template <typename S> class MyClassSpec <S, S> {}; // Set T as S
template <typename T> void MyClass<T, int>::MyFunction(); // Cannot be done
MyClassSpec<float> obj;

//FUNCTIONS: PARTIAL SPECIALIZATION
//Functions can't be partially specialised- overloaded instead
template <typename T, typename S> void MyFunction(T t, S s){}
template <typename T> void MyFunction(T t, float s){} // overloads MyFunction
MyFunction(x, y); // uses overload resolution

//FORWARD DECLARATION
template <typename T> class MyClass;

//TYPEDEF
using myType = T;

//////////////////////////////////////////////////////////////////////////////
//TEMPLATE PARAMETERS
//////////////////////////////////////////////////////////////////////////////

// VALUE PARAMETERS
// Forces a parameter to a type
template <typename T, int n>
class MyClass
{
    T[n] m_myArray;
};
MyClass<double, 20> myObj;

//TRAILING RETURN TYPE
//useful for template functions when return type isn't known
template<typename T, typename C>
auto MyFunction(T x, C y) -> decltype(x+y) { return x+y; }

//TEMPLATE TEMPLATE PARAMETERS
//Allows a parameter that is a template itself to be passed in as a type
//Template type passed in must match template template signature

// Template parameter with single parameter
template <typename T, template <typename> class B> class ClassA {}
template <typename S> class ClassB {}; // signature of ClassB matches B
ClassA<int, ClassB<double>> obj;

// Template parameter with multiple parameters
template <template <typename, typename> class B> class ClassA {} 
template <typename T, typename S> ClassB {}; // signature of ClassB matches B
ClassA<ClassB<double, int>> obj;

// Template parameter for functions
template <template <typename> class B, typename T> void MyFunction(C<T>& obj){}
template <typename S> class ClassB {}; // signature of ClassB matches B
MyFunction(ClassB<double>());

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
//TEMPLATE FRIENDS
//////////////////////////////////////////////////////////////////////////////

template <typename T> class MyClass; //forward dec
template <typename S> void MyFn(MyClass<S>& x){}

template <typename T> class MyClass
{
    // All instantiations of MyFn are friends with all instantiations of MyClass
    // eg. template void MyFn<double>(MyClass<double>& x) is friends with MyClass<int>
    template <typename S> friend void MyFn(MyClass<S>& x);

    // Only T instantiation of MyFn is friends with T instantiation of MyClass
    friend void MyFn<T>(MyClass<T>& x);

    // Only specialisation of MyFn for MyClass is friends with MyClass
    friend void MyFn <> (MyClass& x);
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
