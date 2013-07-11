////////////////////////////////////////////////////////////////////////////////////////////
//DELEGATES
////////////////////////////////////////////////////////////////////////////////////////////

Func<int, double> myFn; //Takes in int, returns double
Action<int> myFn; //Takes in int, no return value
Action myFn; //No params/return value
delegate void MyDelegate(int x) //custom delegate signature

//CREATING DELEGATES
//Outside variables are auto captured if used
MyDelegate myDel = null;
MyDelegate myDel = MyFunction;
MyDelegate myDel = new MyDelegate(MyFunction);
MyDelegate myDel = delegate(int x){ myOutsideInt += x; }
myDel(); //calling delegate

//STATIC FUNCTIONS
public static void MyStaticFunction(int x){}
MyDelegate myDel = MyClass.MyStaticFunction;

//MEMBER FUNCTIONS
public void MyMemberFunction(int x){}
MyDelegate myDel = this.MyMemberFunction; //auto binds object calling
MyDelegate myDel = obj.MyMemberFunction;

//LAMBDAS
MyDelegate myDel = x => myOutsideInt += x;

x => (double)x * 2;            //Takes in int, returns double
x => myOutsideInt += x;        //Takes in int, no return value
(int x) => x*x                 //explicitly specifying argument type
(x,y) => x*y                   //multiple arguments
() => { i += 2.0; i += 3.0; }  //no auto return for multiple lines
() => { return i+j; }          //explicitly returning

//MULTI-CASTING DELEGATES
MyDelegate multiDel = myDel1 + myDel2; //methods are called one after each other in list
multiDel -= myDel2; //can also remove
multiDel.GetInvocationList().GetLength(0); //get int number of delegates in list

//DELEGATE TEMPLATES
public delegate void MyDelegate<T>(T item);
public void MyFunction(int i) {}
MyDelegate<int> myDel = new MyDelegate<int>(MyFunction); /*or*/
MyDelegate<int> myDel = MyFunction;

////////////////////////////////////////////////////////////////////////////////////////////
//DELEGATE INHERITANCE
////////////////////////////////////////////////////////////////////////////////////////////

public class Base {}
public class Derived : Base {}

//COVARIANCE IN DELEGATES
//• Allows delegate to accept a method which returns a higher derived type than delegate defines

public delegate Base MyDelegate(); //Delegate signature
public static void Derived MyFunction();
MyDelegate myDel = MyFunction; //Accepts despite requiring return to be Base

//CONTRAVARIANCE IN DELEGATES
//• Allows delegate to accept a method which has parameters of a lower derived type than delegate defines

public delegate void MyDelegate(Derived d); //Delegate signature
public static void MyFunction(Base b);
MyDelegate myDel = MyFunction; //Accepts despite requiring derived as a parameter

////////////////////////////////////////////////////////////////////////////////////////////
//OBJECT LIFETIME
////////////////////////////////////////////////////////////////////////////////////////////

//BOXING
object boxed = 10; //occurs implicitly for value-types
int unBoxed = boxed as int; //occurs explicitly for value-types

//WEAK REFERENCES
//allows reference to object but doesn't count as a strong reference for the gc
var myWeakRef = new WeakReference<MyClass>(myObj1)

//returns false if myObj1 has been collected else true
//stores strong reference into myObj2 if returns true
MyClass myObj2;
bool isAlive = myWeakRef.TryGetTarget(out myObj2)

////////////////////////////////////////////////////////////////////////////////////////////
//UNSAFE CODE
////////////////////////////////////////////////////////////////////////////////////////////

//POINTERS
//Pointers can only be used in unsafe code
int* myPointer = &myInt; 
int** myPointer
int*[] myPointer //array of pointers to ints
char* myPointer //pointer to a char
void* myPointer
MyStruct* myPointer
*myPointer = 2; //dereferencing

unsafe static void MyUnsafeFn(int* p)
{    
    //PINNING VARIABLES
    //prevents garbage collector from changing address of a variable
    //can only use in unsafe context
    MyClass obj = new MyClass();
    fixed (int* x = &obj.x)
    {
        *x = 1;
    }  
}

//DISPOSING OF UNMANAGED RESOURCES
class MyClass : public IDisposable
{
    bool isDisposed = false;

    //Implementation of IDisposable.Dispose
    public virtual void Dispose() override
    {
        if(!isDisposed)
        {
            //Free any unmanaged/managed resources here
            //prevent finalise from being called as Dispose will do the destructors job
            GC.SuppressFinalize(this);
            isDisposed = true; 
        }
    }
    public void MyFunction()
    {   
        //if implementing, must check if object has been disposed
        if(isDisposed)
        {
            throw new ObjectDisposedException("MyClass","Called MyFunction() on disposed object");
        }
    }
    ~MyClass()
    {
        Dispose();
    }
};