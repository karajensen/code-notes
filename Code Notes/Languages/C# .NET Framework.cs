/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LINQ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using System.LINQ;

// QUERY FROM A CONTAINER
var myQuery = from item in myContainer
              where (item % 2) == 0 
              orderby item.GetValue() descending
              select item.GetValue(); 

// USING OVER RANGE
var myQuery = from number in Enumerable.Range(0, 100)
              select item * 2.0;

// FILLING A CONTAINER
myContainer = (from i in Enumerable.Range(0, 100)
               select new MyClass()).ToList();

// NESTED QUERIES
// second from is nested inside first from
var myQuery = from x in Enumerable.Range(0, 100)
              from y in Enumerable.Range(0, 100)
              select Tuple.Create(x, y);

// GROUPING
// creates array of anonymous types where the group category is 
// Key() and all items that fit into that group are in ToList()
var myQuery = from item in myArray
              group item by item.ID into g
              select new { ID = g.Key, Items = g.ToList() }; 

// USING IN LOOP
foreach (var item in myQuery){}

myQuery.Count(); // returns number of elements that pass condition
myQuery.ToList(); // returns list of elements that pass condition
myQuery.ToArray(); // returns array of elements that pass condition
myQuery.Min(); // returns the minimum value in query
myQuery.Max(); // return the maximum value in query
myQuery.Sum(); // return the sum of all values in query

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSOLE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Writing information to an inaccessible console does not cause an exception to be raised
// Represents the standard input, output, and error streams for console applications
// Cannot be inherited
System.Console.WriteLine("Hello World!");
System.Console.ReadLine(); //pause

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RANDOM VALUES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var rand = new Random(0);
rand.Next(max) //returns value from 0 to max
rand.Next() % max //returns value from 0 to max

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MATHS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Math.Sqrt(myDouble)
Math.Sin(myDouble)
Math.Cos(myDouble)
Math.Tan(myDouble)
Math.Min(myVar)
Math.Max(myVar)    
Math.Sign(myVar)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EXCEPTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INPUT/OUTPUT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//FILESYSTEM
Path.GetDirectoryName(path);
Path.GetFileNameWithoutExtension(path);
Path.GetFileName(path);
Path.HasExtension(path)
Path.IsPathRooted(path) //whether absolute or relative path

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WINDOWS FORMS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TIMERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using System.Diagnostics
var stopWatch = new Stopwatch()
stopWatch.Start() //begin counting
stopWatch.Stop() //stop counting
stopWatch.Elapsed() //returns time passed
stopWatch.Elapsed().ToString("s\\.f") //returns time passed as string
stopWatch.Reset() //resets timer

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// REFLECTION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DIAGNOSTICS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DATABASES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//TableAdapters, DataAdapters and DataCommands will open/close the connection automatically if not already open
//SqlConnection manages connection pooling implicitly

using System.Data;
using System.Data.SqlClient;

string connectionStr = Properties.Settings.Default.ConnectionString;
using (SqlConnection connection = new SqlConnection(connectionStr))
{
    connection.Open();

    // RETRIEVE TABLE INFORMATION
    string query = "SELET * FROM MyTable";
    SqlDataAdapter adapter = new SqlDataAdapter(query, connection);
    DataTable table = new DataTable;
    adapter.Fill(table);
    foreach (DataRow row in table.Rows)
    {
        int id = Convert.ToInt32(row["ID"]);
        string name = row["Name"];
    }    

    // CALL A STORED PROCEDURE
    using (SqlCommand cmd = new SqlCommand("MyProcedure", connection)) 
    {
        cmd.CommandType = CommandType.StoredProcedure;
        cmd.Parameters.Add("@Name", SqlDbType.VarChar).Value = "MyName";
        cmd.ExecuteNonQuery(); // for no return types
    }

    // CREATING A DATA CONTEXT
    DataContext context = new DataContext(connection);
    DataLoadOptions options = new DataLoadOptions();

    options.LoadWith<MyTable>(t => t.MyColumn); // preload required column
    options.LoadWith<MyTable2>(t => t.MyColumn3); // preload from another table
    options.AssociateWith<MyTable>(t => t.MyColumn.Where(r => r.RowValue != 1)); // only retrieve a subset

    context.ObjectTrackingEnabled = false; //set as readonly to improve performance, turns off defered loading
    context.DeferredLoadingEnabled = false; //retrieve all related tables, not just the queried one
    context.LoadOptions = dlo;

    // LINQ DATABASE QUERYING WITH CONTEXT
    var myQuery = from item in context.MyTable
                  where item.MyColumn1 == "MyColumn" 
                  orderby item.MyColumn2
                  select item;

    // EXECUTE SQL QUERY WITH CONTEXT
    IEnumerable<MyColumn> results = context.ExecuteQuery<MyColumn>(@"SELECT * FROM MyColumn");

} //using() will automatically call Close()
