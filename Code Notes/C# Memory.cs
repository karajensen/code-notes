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
//UNSAFE CODE/POINTERS
////////////////////////////////////////////////////////////////////////////////////////////

int* myPointer 
int** myPointer
int*[] myPointer //array of pointers to ints
char* myPointer //pointer to a char
void* myPointer

//POINTER TO STRUCTS
MyStruct* myPointer;
myPointer->member;

//UNSAFE CODE
//Pointers can only be used in this
unsafe static void MyUnsafeFn(int* p)
{
    *p = 2; //dereferencing

    //FIXING VARIABLES
    //prevents garbage collector from changing address of a variable
    //can only use in unsafe context
    MyClass obj = new MyClass();
    fixed (int* x = &obj.x)
    {
        *x = 1;
    }  
}

int myInt = 1;
MyUnsafeFn(&myInt); //obtain address