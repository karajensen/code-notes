//////////////////////////////////////////////////////////////////////////////
//GENERIC TYPE DEDUCTION
//////////////////////////////////////////////////////////////////////////////

//============================================================================
//TEMPLATE TYPE DEDUCTION
//============================================================================
// References/pointer part is ignored and not part of T
// Passing l-value to universal reference will always pass as T&
// Const-ness auto becomes part of T except for passing by-val
// Passing arrays/functions by-value will change the type to a pointer
// Does not assume {} means std::initializer_list

template<typename T> void Fn(T param);
const int& y = x;      Fn(y);     // T/param is int as makes copy and const/reference ignored
const char s[] = "s";  Fn(s);     // T/param is const char* due to array pointer decay rule
void fn(int);          Fn(fn);    // T/param is void(*)(int) pointer to function
                       Fn({2.0})  // CAN'T DO: requires std::initializer_list<T> as template type

template<typename T> void Fn(T& param);
int x = 1;             Fn(x);     // T is int, param is int&
const int& y = x;      Fn(y);     // T is const int, param is const int& (reference ignored)
const char s[] = "s";  Fn(s);     // T is const char [1], param is const char (&)[1]
void fn(int);          Fn(fn);    // T/param is void(&)(int) reference to function

template<typename T> void Fn(const T& param);
int x = 1;             Fn(x);     // T is int, param is const int&
const int& y = x;      Fn(y);     // T is const int, param is const int& (reference ignored)

template<typename T> void Fn(T* param);
int x = 1;             Fn(&x);    // T is int, param is int*
const int* y = &x;     Fn(y);     // T is const int, param is const int* (pointer ignored)

template<typename T> void Fn(T&& param);
int x = 1;             Fn(x);     // T is int&, param is int& (x is l-value)
const int& y = x;      Fn(y);     // T is const int&, param is const int& (x is l-value)
                       Fn(1);     // T is int, param is int&& (1 is r-value)

//GENERIC LAMDAS
//Auto in lambda param/return type use template, not auto, type deduction
auto MyFn = [](auto x) -> int { return 2; } /*or*/
decltype(auto) MyFn = [](auto x) { return 2; }

//============================================================================
//AUTO TYPE DEDUCTION
//============================================================================
//Uses same rules as template type deduction
//Exception is auto assumes {} type is std::initializer_list

auto x = 2.0;      // auto is type double
auto x(2.0);       // auto is type double
auto x = { 2.0 };  // auto is type std::initializer_list<double> with value { 2.0 }
auto x{ 2.0 };     // auto is type std::initializer_list<double> with value { 2.0 }
const auto& y = x; // auto is type double

const char[n]
auto arr2 = arr1;  // auto is type const char* (array-to-pointer decay)
auto& arr2 = arr1; // auto is type const char&[n]

void fn1(int);
auto fn2 = fn1;    // auto is type void(*)(int) (function-to-pointer decay)
auto& fn2 = fn1;   // auto is type void(&)(int) 

//============================================================================
//DECL TYPE DEDUCTION
//============================================================================
//Unlike auto/template deduction, does not ignore const/references

const int x = 1;
const int& y = x;
decltype(x) value;          // Value is int
decltype(y) value;          // Value is const int&
decltype(y+2.0) value;      // Value is double
decltype(Fn(x)) value;      // Value is same return type of Fn 
decltype(auto) value = y;   // Value is const int&, if using just auto value would be int

//EXTRA BRACKETS PITFALL
//Putting extra () around variable name can affect the type returned
decltype((x)) value;                                 // Value is int&
decltype(auto) MyFn = [](){ int x = 1; return (x); } // Is returning int&!

///////////////////////////////////////////////////////////////////////////////////////////////////
//TEMPLATES
///////////////////////////////////////////////////////////////////////////////////////////////////

//- Only creates instantiation of template for objects used with the template
//- Will force create version of template with explicit instantiation
//- Only adds methods to template instantiation if object actually uses the method
//- Keyword 'class' interchangable with 'typename'

// FORWARD DECLARATION
template <typename T> class MyClass;

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

///////////////////////////////////////////////////////////////////////////////////////////////////
//TEMPLATE PARAMETERS
///////////////////////////////////////////////////////////////////////////////////////////////////

// VALUE PARAMETERS
// Forces a parameter to a type
template <typename T, int n>
class MyClass
{
    T[n] m_myArray;
};
MyClass<double, 20> myObj;

// TAG DISPATCH
// Uses tags std::false_type and std::true_type to force overload
template<typename T> void MyFn(T x) { MyFn(x, std::is_integral<typename std::remove_reference<T>::type>()); }
template<typename T> void MyFn(T x, std::false_type){}; // overload if a non-integral type
template<typename T> void MyFn(T x, std::true_type){};  // overload if an integral type

// TEMPLATE TEMPLATE PARAMETERS
// Allows a parameter that is a template itself to be passed in as a type
// Template type passed in must match template template signature

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

///////////////////////////////////////////////////////////////////////////////////////////////////
//TEMPLATE INHERITANCE
///////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////
//TEMPLATE ALIAS
///////////////////////////////////////////////////////////////////////////////////////////////////

// NESTED TYPES
// Type MyClass::MySubClass seen as static member of class unless typename is used
template<typename T> 
class MyClass: public Base<T>::Nested // doesn't require typename
{
public:          

    explicit MyClass(int x) : 
        Base<T>::Nested(x)  // doesn't require typename
    {
    }

    typename Base<T>::Nested myVar; // requires typename 
};

template<typename T>
class MyClass
{
public:
    void MyFunction(typename T::Nested& arg);   // requires typename
    std::unique_ptr<typename T::Nested> myPtr;  // requires typename
    typename T::Nested myValue;                 // requires typename
};

// ALIAS TEMPLATES
// Cannot be typedefined but can use alias declaration
template<typename T>
class MyClass
{
public:
    using MyAlias = typename T::Nested;
    MyAlias myValue;  // doesn't require typename
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//TEMPLATE FRIENDS
///////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////
//VARIADIC TEMPLATES
///////////////////////////////////////////////////////////////////////////////////////////////////

//accept a variable number of arguments
template<typename T, typename... Args> // Args is a template parameter pack
void MyFn(const T& value, const Args&... args) // args is a function parameter pack
{
    //uses recursion to take first element from list
    //sends rest to next call of function
    cout << value << ",";
    show_list(args...);
}
//can use any number, order or type of arguments
MyFn(2.0,"hello",4*2,'c');
MyFn(1.0,'d',"astring");

//VARIADIC PERFECT FORWARDING
template<typename... T>
void MyFn(T&&... args)
{
    MyFn2(std::foward<T>(args)...);
}