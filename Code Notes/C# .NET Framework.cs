////////////////////////////////////////////////////////////////////////////////////////////
//RANDOM VALUES
////////////////////////////////////////////////////////////////////////////////////////////

var rand = new Random(0);
rand.Next(max) //returns value from 0 to max
rand.Next() % max //returns value from 0 to max

////////////////////////////////////////////////////////////////////////////////////////////
//EXCEPTIONS
////////////////////////////////////////////////////////////////////////////////////////////

IndexOutOfRangeException //derives from SystemException
NullReferenceException //derives from SystemException
ArgumentException //derives from SystemException
InvalidOperationException //derives from SystemException
FormatException
OverflowException
Collections.Generic.KeyNotFoundException
InvalidCastException
IOException
FileNotFoundException //derives from IOException
NotImplementedException
NotSupportedException

//TRY-CATCH BLOCK
try
{
}
catch (FileNotFoundException e)
{
    e.FileName //filename of the file not found
    e.Message //IO message
}
catch (IOException e)
{
    e.Message //IO message
}
finally //will always run even if goto is used to jump out
{
}

//THROWING EXCEPTIONS
throw new ArgumentException("Some text");

//RE-THROWING EXCEPTIONS
try
{
}
catch (ArgumentException e)
{
    throw; //continues the exception forward
}

////////////////////////////////////////////////////////////////////////////////////////////
//MATHS
////////////////////////////////////////////////////////////////////////////////////////////

Math.Sqrt(myDouble)
Math.Sin(myDouble)
Math.Cos(myDouble)
Math.Tan(myDouble)
Math.Min(myVar)
Math.Max(myVar)    
Math.Sign(myVar)

////////////////////////////////////////////////////////////////////////////////////////////
//INPUT/OUTPUT
////////////////////////////////////////////////////////////////////////////////////////////

System.Environment.Newline  // Newline character
System.IO.File.WriteAllText(@"C:\Users\Public\TestFolder\WriteText.txt", text);
System.IO.File.AppendAllText(@"C:\Users\Public\TestFolder\WriteText.txt", text);

//XML LOADING
XmlReader file = XmlReader.Create(openFileDialog.FileName);
file.MoveToContent(); //moves to root
file.ReadToDescendant("Map"); //reads to first child
file.MoveToFirstAttribute();
file.GetAttribute("width");
file.ReadToNextSibling("Edge");
file.Close();

//XML WRITING
XmlWriter file = XmlWriter.Create(saveFileDialog.FileName);
file.WriteStartDocument();
file.WriteStartElement("Root");
file.WriteStartElement("Map");
file.WriteAttributeString("width", "0");
file.WriteEndElement();
file.WriteEndElement();
file.WriteEndDocument();
file.Close();

////////////////////////////////////////////////////////////////////////////////////////////
//WINDOWS FORMS
////////////////////////////////////////////////////////////////////////////////////////////
using System.Windows.Forms;

// Message Box
System.Windows.Forms.MessageBox.Show("My message here");

// Dialog Box
DialogResult result = myDialog.ShowDialog();
if (result == System.Windows.Forms.DialogResult.OK)
{
    myFileName = myDialog.FileName;
    myDialog.InitialDirectory = Path.GetDirectoryName(myDialog.FileName);
}

////////////////////////////////////////////////////////////////////////////////////////////
//REFLECTION
////////////////////////////////////////////////////////////////////////////////////////////

//GET DLL INFORMATION
System.Reflection.Assembly assem = System.Reflection.Assembly.Load("myDLL.dll");
assem.GetName() //get name, version information for dll

//GET CALLING METHOD NAME
string methodName = new StackTrace().GetFrame(1).GetMethod().Name;

//GET METHODS AVALIABLE IN A CLASS
Type myType = typeof(MyClass);
MethodInfo[] myArrayMethodInfo = myType.GetMethods(BindingFlags.FlattenHierarchy 
    | BindingFlags.Public | BindingFlags.Instance);

for (int i = 0; i < myArrayMethodInfo.Length; ++i)
{
    MethodInfo myMethodInfo = (MethodInfo)myArrayMethodInfo[i];
    Console.WriteLine("\n{0}.", myMethodInfo.Name);
}

//GET CLASS HANDLES
IntPtr handle = myForm->Handle;
IntPtr instance = System::Runtime::InteropServices::Marshal::GetHINSTANCE(
    System::Reflection::Assembly::GetExecutingAssembly()->GetModules()[0]);

//LOAD A DLL AT RUNTIME
System.Reflection.Assembly assembly = System.Reflection.Assembly.LoadFile("mydll.dll");
System.Type type = assembly.GetType("MyNamespace.MyClass");
object instance = assembly.CreateInstance(type);

//Calling a method
object[] argstopass = new object[] { (object)"argument" };
string ReturnValue = (string)instance.GetType().GetMethod("MyMethod").Invoke(instance, argstopass);

//Calling Properties
instance.GetType().GetProperty("MyProperty").SetValue(instance, (object)"argument", null);
instance.GetType().GetProperty("MyProperty").GetValue(instance, null);


////////////////////////////////////////////////////////////////////////////////////////////
//DIAGNOSTICS
////////////////////////////////////////////////////////////////////////////////////////////
using System.Diagnostics.Debug
using System.Diagnostics.Trace

Trace.WriteLine("Writing a line to the debug console");
Debug.Assert(myObject != null, methodName, "myObject cannot be null");

//Creating custom listener
public class MyListener : DefaultTraceListener
{
    public override void Fail(string message); //called on failed assertion
    public override void Fail(string message, string detailmessage); //called on failed assertion
}
DefaultTraceListener listener = new MyListener();
listener.AssertUiEnabled = false;
Debug.Listeners.Remove("Default");
Debug.Listeners.Add(listener);

////////////////////////////////////////////////////////////////////////////////////////////
//TIMERS
////////////////////////////////////////////////////////////////////////////////////////////

using System.Diagnostics
var stopWatch = new Stopwatch()
stopWatch.Start() //begin counting
stopWatch.Stop() //stop counting
stopWatch.Elapsed() //returns time passed
stopWatch.Elapsed().ToString("s\\.f") //returns time passed as string
stopWatch.Reset() //resets timer
