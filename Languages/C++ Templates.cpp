/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GENERIC TYPE DEDUCTION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//===============================================================================================================
// TEMPLATE TYPE DEDUCTION
//===============================================================================================================
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

// GENERIC LAMDAS
// Auto in lambda param/return type use template, not auto, type deduction
auto MyFn = [](auto x) -> int { return 2; } /*or*/
decltype(auto) MyFn = [](auto x) { return 2; }

//===============================================================================================================
// AUTO TYPE DEDUCTION
//===============================================================================================================
// Uses same rules as template type deduction
// Exception is auto assumes {} type is std::initializer_list

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

//===============================================================================================================
// DECL TYPE DEDUCTION
//===============================================================================================================
// Unlike auto/template deduction, does not ignore const/references

const int x = 1;
const int& y = x;
decltype(x) value;          // Value is int
decltype(y) value;          // Value is const int&
decltype(y+2.0) value;      // Value is double
decltype(Fn(x)) value;      // Value is same return type of Fn 
decltype(auto) value = y;   // Value is const int&, if using just auto value would be int

//EXTRA BRACKETS PITFALL
// Putting extra () around variable name can affect the type returned
decltype((x)) value;                                 // Value is int&
decltype(auto) MyFn = [](){ int x = 1; return (x); } // Is returning int&!

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//- Only creates instantiation of template for objects used with the template
//- Will force create version of template with explicit instantiation
//- Only adds methods to template instantiation if object actually uses the method
//- Keyword 'class' interchangable with 'typename'
//- Definition must be in header unless explicit instantiation is used

// TEMPLATED VARIABLES
// Use as value<float>, value<int>
template<typename T> constexpr T value = T(2.0);

// FORWARD DECLARATION
template <typename T> class MyClass;

// IMPLICIT INSTANTIATION
// Compiler determines what types require templates and creates versions for them only
template <typename T> void MyFunction(T x) {} 
MyFunction<int>(x) /*or*/ MyFunction(x)

template <typename T, typename S = int> // int = default type, only one allowed on class templates
class MyClass
{
public:
    MyClass<T>() :     // <T> optional
        m_member(S())  // initialise templated member to default
    {
    } 
  
    // Template function inside template class
    template <typename T>
    template <typename U>
    void MyClass<T>::fn() { }
 
private:
    S m_member;
};
MyClass<int, double> obj;

// EXPLICIT INSTANTIATION
// Tells compiler to create a version of the template for the type
template MyClass<int>; 
template void MyFunction<int>(int x);
template void MyFunction<int>(MyClass<int>& x);

// CLASS TEMPLATES IN CPP
// In Header File:
template<typename T> class MyClass
{
public:
    MyClass();
};
// In Cpp File:
template MyClass<int>; // for every use of template add an explicit instantiation to .cpp file
template<typename T> MyClass<T>::MyClass() {}

// FUNCTION TEMPLATES IN CPP
// In Header File:
template <typename T> void MyFn();
// In Cpp File:
template MyClass::MyFn<int>; // for every use of template add an explicit instantiation to .cpp file
template <typename T> void MyClass::MyFn() {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATE SPECIALISATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// EXPLICIT SPECIALISATION
// Tells compiler to not use template; use a specialised function instead for the given types
template <> void MyFunction(int x); 
template <> MyClass<int>::MyFunction();

// PARTIAL SPECIALIZATION (CLASSES)
// Can only partially specialize at class level, not member functions
template <typename T, typename S> class MyClass {}; 
template <typename T> class MyClassSpec <T, int> {}; // Set S as int
template <typename S> class MyClassSpec <S, S> {}; // Set T as S
template <typename T> void MyClass<T, int>::MyFunction(); // Cannot be done
MyClassSpec<float> obj;

// PARTIAL SPECIALIZATION (FUNCTIONS)
// Functions can't be partially specialised- overloaded instead
template <typename T, typename S> void MyFunction(T t, S s){}
template <typename T> void MyFunction(T t, float s){} // overloads MyFunction
MyFunction(x, y); // uses overload resolution

// TAG DISPATCH
// Uses tags std::false_type and std::true_type to force overload
template<typename T> void MyFn(T x) { MyFn(x, std::is_integral<typename std::remove_reference<T>::type>()); }
template<typename T> void MyFn(T x, std::false_type){}; // overload if a non-integral type
template<typename T> void MyFn(T x, std::true_type){};  // overload if an integral type

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATE PARAMETERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VALUE PARAMETERS
// Forces a parameter to a type
template <typename T, int n>
class MyClass
{
    T[n] m_myArray;
};
MyClass<double, 20> myObj;

// AUTO PARAMTERS
template<typename T, auto N> 
class MyClass
{ 
    MyClass(const std::array<T,N>&) {}
}
MyClass obj{"str"}
MyClass obj{std::array<double,10>()}

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATE ENABLE-IF
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Only instantiate for T*
template <typename T>
typename std::enable_if<std::is_pointer<T>::value, T>::type fn(const std::vector<T>& vec, int index) const
{
    return vec[index];
}

// Only instantiate for T
template <typename T>
typename std::enable_if<!std::is_pointer<T>::value, const T*>::type fn(const std::vector<T>& vec, int index) const
{
    return &vec[index];
}

// Only instantiate if T2 is derived from T1
template <typename T1, typename T2>
typename std::enable_if<std::is_base_of<T1, T2>::value, ReturnObject>::type fn()
{
    return ReturnObject();
}

// Instantiate depending on value parameters
template <int n> typename std::enable_if_t<(n < 1), float> fn() { return 5.0f; };
template <int n> typename std::enable_if_t<(n >= 1 && n < 3), float> fn() { return 1.0f; };
template <int n> typename std::enable_if_t<(n == 10)> fn() {};
fn<1>();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATE INHERITANCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T> class Base
{
public:
    Base<T>() {}
    virtual void MyMethod() = 0;
};

template <typename T> class Derived : public Base<T> 
{
    Derived() : Base<T>() {}

    virtual void MyMethod() override
    {
        Base<T>::MyMethod();
    }
};

// CURIOUSLY RECURRING TEMPLATE PATTERN (CRTP)
// class A has a base class which is a template specialization for the class A itself.
template <typename A> 
class Base
{
    A& DoSomething();
};
// Class A derives from base and passes own type in
class A : public Base<A> 
{
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATE ALIAS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TYPEDEF TEMPLATE
template <typename T> using my_unordered_map = std::unordered_map<T, MyClass>;
using T = typename std::decay<decltype(*vec.begin())>::type; // Decay to vector type

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATE FRIENDS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNIVERSAL REFERENCES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
UNIVERSAL REFERENCES
• Reference that can bind to rvalue and lvalue reference of form T&&
• T&& that uses Reference Collapsing to bind to both rvalue/lvalue references
• Requires type deduction that must be determined each time its called (not class templates)
• Requires Pefect Fowarding to pass on arguments
• Bad for overloading: instantiate to create exact matches for almost any type of argument
• Cannot be used with class templates, const or volitile

PERFECT FORWARDING
• Function templates that take arbitrary arguments and forward exactly the same arguments
• Preserves R/L value-ness of passed args as all function params are lvalues
• std::foward used to pass on correct type by casting to rvalue if pass argument was an rvalue
• Fails with {}, NULL, static const members without a definition, template/overloaded function names, bitfields

REFERENCE COLLAPSING
• Occurs in universal references, typedef T&& MyTypedef, aliases and decltype
• When lvalue reference is passed to T&&, creates type MyClass& && which collapses to MyClass&
• Only compiler can create type T& && for collapsing, otherwise error
*************************************************************************************************************/

void fn(T& x) {}
void fn(T&& x) {}
void MyFn(T&& x) { return fn(x); } // Calls fn(T& x) for rvalues/lvalues
void MyFn(T&& x) { return fn(std::move(x)); } // Calls fn(T&& x) for rvalues/lvalues
void MyFn(T&& x) { return fn(std::forward<T>(x)); } // Calls fn(T&& x) for rvalues, fn(T& x) for lvalues 
                                              
auto MyFn = [](auto&& x){ MyFn2(std::foward<decltype(x)>(x)); };
auto&& x = myObj; // initialised with lvalue reference, T/x = MyClass&
auto&& x = 3;     // initialised with rvalue, T = MyClass, x = MyClass&&

// VARIADIC UNIVERSAL REFERENCES
template<typename...T>
void fn(T&&...v)
{
     (..., vec.push_back(std::forward<T>(v))); // Fold expression
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIADIC TEMPLATES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------
// VARIADIC FUNCTIONS
//-----------------------------------------------------------------------------------------------

// Recursive function
template<typename T, typename... Args> // Args is a template parameter pack
void MyFn(const T& value, const Args&... args) // args is a function parameter pack
{
    // uses recursion to take first element from list
    // sends rest (minus head) to next call of function
    cout << value << ",";
    MyFn(args...);
}

// Perfect Forwarding for arguments
template<typename T, typename... Args>
std::unique_ptr<T> MyFn(Args&&... args)
{    
    return std::move(std::make_unique<T>(std::forward<Args>(args)...));
}

// Functions with args using std forwarding
template <typename... Args>
std::vector<int> fn()
{
    // Can also use fold expressions with C++17
    return std::initializer_list<int> { Args::myStaticFn()... };
}
fn<MyClassA, MyClassB>(); // calls MyCalssA::staticFun()...

// Functions with args using static loop
template <int First, int Last, typename Fn>
inline void static_for(Fn const& fn)
{
    if constexpr (First < Last)
    {
        fn(std::integral_constant<int, First>{});
        static_for<First + 1, Last>(fn);
    }
}
template <typename... Args>
std::vector<int> fn()
{
    std::vector<int> vec;
    static_for<0, sizeof...(Args)>([&](auto index) {
        vec.push_back(std::tuple_element_t<index, std::tuple<Args...>>::myStaticFn());
    });
    return vec;
}
fn<MyClassA, MyClassB>(); // calls MyCalssA::staticFun()...

//-----------------------------------------------------------------------------------------------
// VARIADIC CLASSES
//-----------------------------------------------------------------------------------------------

// Used for the visiter pattern and tuples, inherits itself minus one arg each time
template<typename... Args> struct MyClass; // Forward Decl

template<typename T, typename... Args> 
struct MyClass<T, Args...> : MyClass<Args...>
{
     typedef MyClass<Args...> Base;
     void MyFn()
     {
         std::cout << typeid(value).name() << std::endl;
         Base::MyFn(); // Recurse down to one
     }
     T value;
};

template<typename T> 
struct MyClass<T> // Specialized for one
{
    void MyFn() 
    {
        std::cout << typeid(value).name() << std::endl;
    }
    T value;
};

MyClass<int, float, double> myClass;

//-----------------------------------------------------------------------------------------------
// VARIADIC LAMBDAS
//-----------------------------------------------------------------------------------------------

auto MyFn = [](const auto& value, const Args&... args)
{
    cout << value << ",";
    MyFn(args...);
}
MyFn(2.0,"hello",4,'c'); // can use any number, order or type of arguments
MyFn(1.0,'d',"astring");

// Perfect Forwarding for lambda arguments
auto MyFn = [](auto&&... x)
{
    MyFn2(std::foward<decltype(x)>(x)...);
}

// Passing Variadic arguments to lambda callback
template<typename... Args>
void MyFn(Args&&... args)
{
    m_fn(std::forward<Args>(args)...);
}

//-----------------------------------------------------------------------------------------------
// FOLD EXPRESSIONS
//-----------------------------------------------------------------------------------------------

// For accessing variadic template arguments
// Order inside brackets matters except for comma operator which is always left to right
(... op args ) = ((arg1 op arg2) op arg3) ... = left to right
(args op ... ) = (arg1 op (arg2 op arg3)) ... = right to left

// Empty parameter packs: 
op = &&           // returns true
op = ||           // returns false
op = ,            // returns void
op = all others   // undefined (must add initial value)
  
template<typename T, typename... Args> 
auto sum(Args... args) 
{ 
    (std::cout << ... << fn(args));
    (... , vec.push_back(args));
    return (0 + ... + args); // init value required for empty args
    return (std::is_same_v<T,Args> && ...); // will short circuit on first false
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEDUCTION GUIDES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> struct S { T val; };
S(const char*) -> S<std::string>; // map S<> for string literals to S<std::string>

