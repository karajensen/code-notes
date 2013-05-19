//////////////////////////////////////////////////////////////////////////////
//LAMBDAS
//////////////////////////////////////////////////////////////////////////////
//• Can't be templated

//LAMBDA SYNTAX
auto myLamda = [](int x) { return 3*2; } //if only one line, can omit trailing return
auto myLamda = [](int x)->double { return 3*2; }
auto myLamda = &MyFunction; //storing pointer to function
auto myLamda = MyFunctor; //storing functor object
std::function<double(int)> myLamda = [](int x){ return x+2.0; }

//CAPTURING OUTSIDE VARIABLES
//Can also capture member vars, functions etc.
int myVar = 0;
auto myLambda = [&myVar](int x){ myVar += 10; } //by reference
auto myLambda = [myVar](int x){ myVar += 10; } //by value
auto myLambda = [&](int x){ myVar += 10; } //use all vars in scope by ref
auto myLambda = [=](int x){ myVar += 10; } //use all vars in scope by val
auto myLambda = [&](int x){ MyClassFunction(x); m_myMember += 1; }

//CAPTURING CLASS OBJECT
typedef std::function<void(void)> MyFn;
MyFn fn = std::bind(&MyClass::MyMethod, this);
MyFn fn = std::bind(&MyClass::MyMethod, myObjPointer);
fn() // object is bound with method, can also bind any other arugments in MyMethod

//////////////////////////////////////////////////////////////////////////////
//BINDING FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

using namespace std::placeholders; //for _1, _2...
void MyFunction(int x, double y, float z);

//SETTING ALL ARGUMENTS
auto fullFn = std::bind(&MyFunction, 1, 10.0, 2.0);
fullFn();

//FULL BINDING
auto fullFn = std::bind(&MyFunction, _1, _2, _3); //_n maps to argument given
fullFn(1,10.0,2.0); //use same as MyFunction, passes by-val default
fullFn(1,10.0,std::cref(myFloat)); //pass in argument by-ref

//PARTIALLY BINDING
auto partialFn = std::bind(&MyFunction, _1, 10.0, _2); //map only two arguments
partialFn(1,2.0); //only requires two arguments, middle is auto given

//CHANGING ARGUMENT ORDER
auto orderChangedFn = std::bind(&MyFunction, _3, _1, _2); //rearranges order of arguments
orderChangedFn(1,10.0,2.0); //becomes MyFunction(2.0,1,10.0)

//BINDING MEMBER FUNCTIONS
MyClass obj; //where void MyClass::MyMethod(int x);
auto memberFn = std::bind(&MyClass::MyMethod, _1, _2); //_1 is always object to work on
memberFn(&obj, 1);


//////////////////////////////////////////////////////////////////////////////
//FUNCTION POINTERS 
//////////////////////////////////////////////////////////////////////////////

//POINTER-TO-FUNCTION
typedef bool (*p_function)(int x);
p_function pf = &AddName; 
pf(5);

//POINTER-TO-MEMBER FUNCTIONS
class Test
{
public:
    
    typedef void(Test::*Action)();
    typedef void(Test::*ActionConst)() const;

    void DrawConst(){} const;
    void Draw(){}

    Action m_action;
    ActionConst m_actionconst;
};

m_action = &Test::Draw;
m_actionconst = &Test::DrawConst;


//////////////////////////////////////////////////////////////////////////////
//FUNCTORS
//////////////////////////////////////////////////////////////////////////////

//using as function
plus<double> add; // create a plus<double> object
double y = add(2.2, 3.4); // using plus<double>::operator()()

//types
plus<int> func //+
minus<int> func //-
multiplies<int> func //*
divides<int> func ///
modulus<int> func //%
negate<int> func //-
equal_to<int> func //==
not_equal_to<int> func //!=
greater<int> func //>
less<int> func //<
greater_equal<int> func //>=
less_equal<int> func //<=
logical_and<int> func //&&
logical_or<int> func //||
logical_not<int> func //!

//Creating own derived functor
//type of 2 parameters, return type
template<typename T>
struct MyFunctor : public std::binary_function<T,T,bool> 
{
    bool operator()(const T & a, const T & b)
    {
        //do calculations and return true/false
    }
};

//creating own functor
class BaseFunctor
{
    virtual bool operator()(int,int) = 0;
};
class DerivedFunctor: public BaseFunctor
{
    virtual bool operator()(int a,int b){ return true; }
};

//Using own functor
DerivedFunctor func;        DerivedFunctor * func;
func(x,y);                  (*func)(x,y);

