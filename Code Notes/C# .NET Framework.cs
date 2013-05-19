////////////////////////////////////////////////////////////////////////////////////////////
//RANDOM VALUES
////////////////////////////////////////////////////////////////////////////////////////////

var rand = new Random(0);
rand.Next(max) //returns value from 0 to max
rand.Next() % max //returns value from 0 to max

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
//SYSTEM.OBJECT
////////////////////////////////////////////////////////////////////////////////////////////

//returns string of the object's type by default
obj.ToString() [virtual]

//If o/obj are reference-type, calls ReferenceEquals()
//If o/obj are value-type, checks the values they hold against each other
obj.Equals(Object o) [virtual]

//Static: Tests if both objects refer to the same internal object by comparing hash codes
Object.ReferenceEquals(Object o1, Object o2)

//returns hash int value for equality testing/indexing in a collection
obj.GetHashCode() [virtual]

//returns type of the object called on
obj.GetType()

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
//LINQ
////////////////////////////////////////////////////////////////////////////////////////////
using System.Linq;

//LINQ data source is any object that supports the generic IEnumerable<T> interface
int[] numbers = new int[7]{ 0, 1, 2, 3, 4, 5, 6 };
List<int> numbers = new List<int>{ 0, 1, 2, 3, 4, 5, 6 };

//Creating a query
var numQuery = from num in numbers   //for each number
               where (num % 2) == 0  //if number is even
               select num;           //return it

//Executing query
foreach (int num in numQuery)
{
    /*use the number*/
}