//////////////////////////////////////////////////////////////////////////////
//CLASSES
//////////////////////////////////////////////////////////////////////////////

class MyClass
{
public:

    virtual ~MyClass(){}                        //virtual destructor
    MyClass(){}                                 //default constructor
    MyClass(int x, double y = 0);               //constructor
    explicit MyClass(float myFloat);            //single argument constructor
    MyClass(const MyClass& obj);                //copy constructor
    MyClass(MyClass && obj);                    //move constructor
    MyClass& operator=(const MyClass& obj);     //assignnment operator
    MyClass& operator=(MyClass && obj);         //move assignment operator
    static int StaticFunction(int x);           //static function
    operator double();                          //cast operator
    
private:

    //Prevent copying, no declaration required
    //Important if dynamic allocation occurs in class
    MyClass(const MyClass); 
    MyClass& operator=(const MyClass);

    int m_member;
    const int m_constMember; 
    static const int STATIC = 20; //Only const in can be defined in class header
    static std::unique_ptr<MyClass> sm_singleton; //static pointer to class
};

//IMPLICIT MEMBERS
MyClass() //default constructor
~MyClass() //default destructor
MyClass(const MyClass& obj); //copy constructor
MyClass& operator=(const MyClass& obj); //assignnment operator
unsigned int MyClass::operator&(); //address operator

//STATIC MEMBERS
std::unique_ptr<MyClass> MyClass::sm_singleton; 
int MyClass::StaticFunction(int x)
{
    //Static functions can only access static members
    //Static pointer to class can access private members in static function
    return sm_singleton->m_member; 
}

//CONSTRUCTOR
//const members can only be initialised in initialisation list
//make initialisation list in same order members are defined
MyClass::MyClass(int x, double y): 
    m_member(x), 
    m_constMember(y)
{}

//DESTRUCTOR 
//make virtual if class is to be inherited from
virtual ~MyClass();
MyClass::~MyClass(){}

//COPY CONSTRUCTOR
MyClass::MyClass(const MyClass& obj)
{
    this.m_member = obj.m_member;
}

//ASSIGNMENT OPERATOR
MyClass& MyClass::operator=(const MyClass& obj)
{
    if(&obj == this) //check not copying self
    { 
        return *this;
    } 
    this->m_member = obj.m_member; //copy over values
    return *this;
}

//SINGLE ARGUMENT CONSTRUCTOR
//use explicit stop implicit conversions from taking place
//otherwise works similar to a cast operator
explicit MyClass(double x); 
MyClass::MyClass(double x) :
    m_member(x)
{}
MyClass myObj(4.3) // With/without explicit okay  
myObj = 4.3        // Without explicit okay, with explicit prevented


//MOVE CONSTRUCTOR
//Uses Move Semantics; allows resources to transfer between objects
//Doesn't take const objects as it modifies rvalue passed in
MyClass::MyClass(MyClass && obj):
    m_pointer(std::move(obj.myPointer),
    m_member(std::move(obj.m_member)
{}

//MOVE ASSIGNMENT OPERATOR
//Doesn't take const objects as it modifies rvalue passed in
MyClass& MyClass::operator=(MyClass && obj)
{
    if(this == &obj)
    {
        return *this;
    }
    delete [] m_pointer; //delete any dynamic allocation for object
    m_member = obj.m_member;
    m_pointer = obj.m_pointer; //steal the address
    obj.myPointer = nullptr; //set to null
    return *this;
}

//////////////////////////////////////////////////////////////////////////////
//CREATING OBJECTS 
//////////////////////////////////////////////////////////////////////////////

//DEFAULT CONSTRUCTOR PITFALL
ONE one(); //sees as function declaration, fixed by ONE one;

//CONSTRUCTOR INSIDE CONSTRUCTOR PITFALL
ONE one(TWO(x)); //can't be done; thinks it's a function declarion
ONE one(TWO(3)); //can be done; realises it's object creation
ONE one((TWO(x))); //can be done; realises it's object creation
ONE one(two); //where two = TWO(x) can be done


//////////////////////////////////////////////////////////////////////////////
//TYPES OF CLASSES
//////////////////////////////////////////////////////////////////////////////

//=========================================================================
//STRUCTURES
//=========================================================================
//Clas with members public by default
struct MyStruct
{
    float x;
    float y;
}; 

//creating a new object from mystructure
MyStruct obj = {32, 23.1}; 

//=========================================================================
//AGGREGATES
//=========================================================================
//NO: Constructors, virtual methods, private/protected non-static data members
class Aggregate 
{
public:
    int member;
    Aggregate& operator=(const Aggregate&);
    static int pubStaticMember;
    static void staticFunction();
    ~Aggregate();

private:
    void privateFunction();
    static int privStaticMember;
};
Aggregate obj = {3}; //can be initialized with {}

//=========================================================================
//PLAIN OLD DATA (POD)
//=========================================================================
//NO: Constructors, virtual methods, private/protected non-static data members
//NO: Destructors, assignment operators
class POD 
{
public:
    int member;
    static int pubStaticMember;
    static void staticFunction();

private:
    void privateFunction();
    static int privStaticMember;
};
POD obj = {3}; //can be initialized with {}

//////////////////////////////////////////////////////////////////////////////
//OPERATOR OVERLOADING
//////////////////////////////////////////////////////////////////////////////

//USING OVERLOADS
obj1*obj2  /*->*/  obj1.operator*(obj2);
obj1+obj2  /*->*/  obj1.operator+(obj2);
obj1[4]    /*->*/  obj1.operator[](4) 
obj1[0][1] /*->*/  (class1[0].operator[](1)).operator[0];

//OVERLOAD DECLARATIONS
MyClass& operator++(); //prefix
MyClass& operator--(); //prefix
MyClass operator++(int unused); //postfix
MyClass operator--(int unused); //postfix
const MyClass operator+(const MyClass& x) const;
const MyClass operator*(const MyClass& x) const;
MyClass& operator[](const int i);
const MyClass& operator[](const int i) const;

void* operator new(std::size_t);                         //plain new
void* operator new(std::size_t, std::nothrow_t) throw(); //nothrow new
void* operator new(std::size_t, void*);                  //in-place new

//USING FRIENDS COUPLED WITH OVERLOADED OPERATOR
A = B * 2.0 /*->*/ A = B.operator*(2.0);
const MyClass operator*(const double val) const;

A = 2.0 * B /*->*/ A = operator*(2.0, B); 
friend const MyClass operator*(const double val, const MyClass& obj) const;


//OVERLFOADING STD::COUT 
friend std::ostream & operator<<(std::ostream& os, const MyClass& obj); 
std::ostream & TestClass::operator<<(std::ostream & os, const MyClass& obj)
{
    os << obj.m_member;
    return os;
}
std::cout << obj;

//////////////////////////////////////////////////////////////////////////////
//CAST OPERATOR
//////////////////////////////////////////////////////////////////////////////

operator double(); //typecast prototype (must be method)
MyClass::operator double()
{
    return m_member; //returns double even without return type in signature
}
double myDouble = obj; //implicitly
double myDouble = double(obj); //explicitly

//CAST OPERATOR FOR CUSTOM TYPES
operator Float3();
Matrix::operator Float3()
{
    return Float3(1,2,4);
}
Float3 myVector = Float3(myMatrix);


//////////////////////////////////////////////////////////////////////////////
//FRIENDS
//////////////////////////////////////////////////////////////////////////////

//FRIEND FUNCTIONS
class A
{
public:
    class B; //forward declaraction
    friend void B::MyMethod(); 
};

class B
{
public:
    void B::MyMethod(); //method can access privates of A
};


//FRIEND CLASSES
class A
{
public:
    //auto forward declares
    //doesn't matter where defined- public/private/protected
    friend class B; 
};

class B
{
public: //class can access privates of A
};

//////////////////////////////////////////////////////////////////////////////
//CLASS DYNAMIC MEMORY
//////////////////////////////////////////////////////////////////////////////

//USING THE COPY-SWAP IDIOM FOR DEEP COPYING
class Array
{
public:

    int* arr;
    int size;

    //CONSTRUCTOR
    Array(int x = 0) 
      : size(x), 
        arr(new int[size]())
    {}

    //COPY-CONSTRUCTOR
    Array(const Array& other)
      : size(other.size),
        arr(new int[other.size]())
    {
        //Non-throwing due to type used
        std::copy(other.arr, other.arr + other.size, arr);
    }

    //DESTRUCTOR
    ~Array()
    {
        delete [] arr;
    }

    //SWAP FUNCTION
    friend void swap(Array& first, Array& second)
    {
        std::swap(first.size, second.size); 
        std::swap(first.arr, second.arr);
    }

    //ASSIGNMENT OPERATOR
    //take parameter by-val to use copy constructor
    Array& operator=(const Array other)
    {
        swap(*this, other);
        return *this;
    } 
};