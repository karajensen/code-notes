////////////////////////////////////////////////////////////////////////////////////////////
//LAMBDA FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////
//DELEGATES
////////////////////////////////////////////////////////////////////////////////////////////

//DELEGATE SIGNATURE
//Can store a static/instanced method with same signature as delegate sig
delegate void MyDelegate(string message); 

//============================================================================
//DELEGATES FROM NAMED FUNCTIONS
//============================================================================
public static void MyFunction(string message) { System.Console.WriteLine(message); }

MyDelegate myDelFn = MyFunction; //creating object
myDelFn("Send Message"); //calling fn

//============================================================================
//DELEGATES FROM NAMED CLASS METHODS
//============================================================================
public class MyClass
{
    public void MyMethod(string message) { System.Console.WriteLine(message); }
    public static void MyStatic(string message) { System.Console.WriteLine(message); }
}

MyDelegate myDelMethod = obj.MyMethod(); //stores both function and object calling it
MyDelegate myDelStatic = new MyDelegate(MyClass.MyStatic()); //can also be created using 'new'
myDelMethod("Send Message"); //calling fn

//============================================================================
//DELEGATES FROM ANONYMOUS FUNCTIONS
//============================================================================

// Instantiate the delegate using an anonymous method
MyDelegate myAnonFn = delegate(string message) { System.Console.WriteLine(message); };

// Create a handler for a click event
myButton.Click += delegate(System.Object o, System.EventArgs e)
    { System.Windows.Forms.MessageBox.Show("Click!"); };


//============================================================================
//TEMPLATED DELEGATES
//============================================================================

public delegate void MyDelegate<T>(T item);
public void MyFunction(int i) {}

MyDelegate<int> myDel = new MyDelegate<int>(MyFunction); /*or*/
MyDelegate<int> myDel = MyFunction;

//============================================================================
//MULTI-CASTING DELEGATES
//============================================================================

MyDelegate multiDel = myDelMethod + myDelFn; //methods are called one after each other in list
multiDel -= myDelF2n; //can also remove
multiDel.GetInvocationList().GetLength(0); //get int number of delegates in list

//============================================================================
//COVARIANCE/CONTRAVARIANCE IN DELEGATES
//============================================================================

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
