////////////////////////////////////////////////////////////////////////////////////////////
//IENUMERABLE / LINQ
////////////////////////////////////////////////////////////////////////////////////////////
//LINQ queries can be used on containers that supports IEnumerable<T> interface
//Most containers inherit from IEnumerable<T> except ArrayList which inherits IEnumerable
//IEnumerable is the untemplated version of IEnumerable and cannot use LINQ

using System.Collections.Generic;
using System.LINQ;

IEnumerable<int> myIEnum = myContainer.Where(item => item.IsActive()); // from subset of container
IEnumerable<int> myIEnum = new List<int>(){1,2,3}; // from whole container
IEnumerable<int> myIEnum = myContainer; // implicit conversion

myIEnum.Exlude(myIEnum2) // remove myIEnum2 from myIEnum
myIEnum.Union(myIEnum2)  // joint two IEnumerable<T>
myIEnum.ToArray()        // Converting to array
myIEnum.ToList()         // Converting to list
myIEnum.Cast<int>()      // Cast back to original container type

// Query subset of container
var myQuery = from item in myContainer //for each number
              where (item % 2) == 0    //if number is even (optional line)
              select item;             //use the number

// Call item method 
var myQuery = from item in myArray  
              orderby item.GetValue() descending
              select item.GetValue();     

// Array generation of 100 items (note Enumerable requires LINQ)
var myQuery = from number in Enumerable.Range(0, 100)
              select item * 2.0;

// Nested queries, second from is nested inside first from
var myQuery = from x in Enumerable.Range(0, 100)
              from y in Enumerable.Range(0, 100)
              select Tuple.Create(x, y);

//Query Aggregate Methods; apply function to each successive element
myQuery.Count(); // returns number of elements that pass condition
myQuery.ToList(); // returns list of elements that pass condition
myQuery.ToArray(); // returns array of elements that pass condition
myQuery.Min(); // returns the minimum value in query

//Using in loops
foreach (int item in myIEnum)
foreach (int item in myQuery)

////////////////////////////////////////////////////////////////////////////////////////////
//MULTI-TYPED CONTAINERS
////////////////////////////////////////////////////////////////////////////////////////////

//TUPLES
//Create structure with multiple types
var myTuple = Tuple.Create(3,"hello",1.0)

//ANONYMOUS TYPES
//Create Class with multiple types
//members are read-only, has manged name and cannot be passed around as has anon type
var autoClass = new { myInt = 10, myString = "String" };

////////////////////////////////////////////////////////////////////////////////////////////
//STRINGS
////////////////////////////////////////////////////////////////////////////////////////////

//STRINGS
//Strings are constant, anything that modifies it actually returns new string
string myString = "one"+"two";
string myString = "one"+1; //auto converts to string using concatonation
string myString = 1; //doesn't auto convert

str.ToUpper();        //returns upper case version
str.ToLower();        //returns lower case version
str.PadLeft(x);       //add x spaces to front of string 
str.PadRight(x);      //add x spaces to end of string 
str.PadLeft(x,'a');   //add x 'a' to front of string 
str.PadRight(x,'a');  //add x 'a' to end of string 
str.Split(seperator); //splits into string[] minus the seperator

string.Empty //returns empty string

//STRING BUILDER
//string that can be modified directly
StringBuilder builder = new StringBuilder();
builder.Append("hello");
builder.Append(2);

////////////////////////////////////////////////////////////////////////////////////////////
//ARRAYS
////////////////////////////////////////////////////////////////////////////////////////////
//• Derived from System.Array
//• Can't be dynamically resized
//• Array name is reference type despite the variable type it holds

int[] myArray = new int[ArrayAmount] 
int[] myArray = new int[] { 1,2,3,4 };
int[] myArray = { 1,2,3,4 };

//JAGGED MULTI-DIMENSIONAL ARRAYS
//Can have difference size colums
int[][] myArray = new int[3][]
{
    new [] { 1, 2 },
    new [] { 1, 2, 3 },
    new [] { 1 }
};

//RECTANGLE MULTI-DIMENSIONAL ARRAYS
//All columns must be same size
int[,] myArray = new int[5, 10];
int[,] myArray = new int[,]
{
    { 1, 2, 3 },
    { 4, 5, 6 }
};

//CUBOID MULTI-DIMENSIONAL ARRAYS
var cuboid = new int[,,]
{
    {
        { 1, 2, 3 },
        { 4, 5, 6 }
    },
    {
        { 7, 8, 9 },
        { 4, 5, 6 }
    }
};

myArray[0] //normal arrays
myArray[0][1] //jaggered array
myArray[0,2] //rectangle array
myArray.Length // number of elements
myArray.Min(x => x.GetValue())

Array.IndexOf(myArray, 2) //returns index of first element found from start or -1 if not found
Array.LastIndexOf(myArray, 2) //returns index of first element found from end or -1 if not found
Array.FindIndex(myArray, BoolFunction) //returns index of first element from start that returns true
Array.FindLastIndex(myArray, BoolFunction) //returns index of first element from end that returns true
Array.Find(myArray, BoolFunction) //returns value of first element from start that returns true
Array.FindLast(myArray, BoolFunction) //returns value of first element from end that returns true
Array.FinalAll(myArray, value => value != null) //returns an array of elements that returns true
Array.Sort(myArray) //sorts into ascending order
Array.BinarySearch(myArray, 2) //returns index of first element found or < 0 if not found, must be sorted
Array.Reverse(myArray) //reverses elements
Array.Copy(myArray1, myArray2, n) //copies n elements from start of 1 to start of 2
Array.Clear(myArray, i, n) //clears to default from index i for n number of elements

////////////////////////////////////////////////////////////////////////////////////////////
//ARRAYLIST
////////////////////////////////////////////////////////////////////////////////////////////
//• Derives from IEnumerable, not IEnumerable<T> and cannot use LINQ
//• Stores a list of System.Object

ArrayList myArrayList = new ArrayList();

myArrayList[0]
myArrayList.Add("myObject")

////////////////////////////////////////////////////////////////////////////////////////////
//LISTS
////////////////////////////////////////////////////////////////////////////////////////////
//• Dynamically resizes, memory layout same as std::vector
//• Inheritance: List<T> -> IList<T> -> ICollection<T> -> IEnumerable<T>
//• Does not have virtual methods for Add/Remove as it was designed to be fast
//• Inherit from ICollection<T> not IList<T> due to no virtual methods

List<int> myList = new List<int>();
List<int> myList = new List<int>(20); //reserve space for 20 elements
List<int> myList = new List<int>{ 1, 2, 3 };

myList[0]
myList.ForEach(x => x.DoSomething()) // iterate over all elements and call action
myList.Count //return number of elements
myList.Capacity //amount of items that can be added in the reserved space 
myList.Add(myItem) //add item of type T to end of list
myList.AddRange(myArray) //add each member of array to list
myList.Insert(i, myItem) //adds item at index i
myList.InsertRange(i, myArray) //adds array at index i
myList.Clear() //removes all items, capacity remains same though
myList.Contains(myItem) //returns true if item exists
myList.RemoveAt(i) //remove element at index
myList.TrimExcess() //remove any extra reserved space, won't do anything if 90% of space used
myList.IndexOf(myItem) //returns index of first element found from start or -1 if not found
myList.LastIndexOf(myItem) //returns index of first element found from end or -1 if not found
myList.Find(BoolFunction) //returns value of first element from start that returns true
myList.FindLast(BoolFunction) //returns value of first element from end that returns true
myList.FinalAll(value => value != null) //returns list of elements that returns true
myList.Sort() //sorts into ascending order
myList.BinarySearch(myItem) //returns index of first element found or < 0 if not found, must be sorted

////////////////////////////////////////////////////////////////////////////////////////////
//DICTIONARY
////////////////////////////////////////////////////////////////////////////////////////////
//• Dictionary<K,V> -> IDictionary<K,V> -> ICollection<KeyValuePair<K,V>> -> IEnumerable<KeyValuePair<K,V>>
//• Relies on hash keys for fast lookup
//• No duplicate keys, value can be multiple
//• Faster, less storage used than sorted variations

var myD = new Dictionary<key, value>()
var myD = new Dictionary<key, value>(20) //gives capacity of 20 key/value pairs
var myD = new Dictionary<key, value> { {"One",2}, {"Two",1} };

//Setting the IEqualityComparer<K> to use case-insensitive lookup
var myD = new Dictionary<key, value>(StringComparer.InvariantCultureIgnoreCase)
{ 
    {"One",2}, 
    {"Two",1} 
};

myD.Comparer //returns IEqualityComparer<T> used to compare equality of keys
myD.Count //returns number of key/value pairs 
myD.Item[key] //get value for key, if key doesn't exist throws KeyNotFoundException
myD.Item[key] = value //set value for key, if key doesn't exist creates new entry
myD.Keys //returns Dictionary<key,value>.KeyCollection; used same as array
myD.Values //returns Dictionary<key,value>.ValueCollection; used same as array
myD.Add(key,value) //throws ArgumentException if key already exists
myD.Clear() //clears all key/value pairs, capacity remains same
myD.ContainsKey(key) //returns true if key exists
myD.ContainsValue(value) //returns true if value exists
myD.Remove(key) //returns true if key/value pair found and successfully removed
myD.TryGetValue(key, out result) //if key exists uses value else default for type into result; returns true if key found

//SORTED DICTIONARY
//• Always remains sorted, doesn't use hash keys
//• Inserting/removing inexpensive as using tree structure for sorting
var mySD = new SortedDictionary<key, value>()

//SORTED LIST
//• Always remains sorted, doesn't use hash keys
//• Inserting/removing items expensive as have to update key/value lists
var mySL = new SortedList<key, value>()
mySL.Keys //returns IList<K> with the keys sorted in ascending order
mySL.Values //returns IList<V> with the values sorted in ascending order

////////////////////////////////////////////////////////////////////////////////////////////
//LINKED LISTS
////////////////////////////////////////////////////////////////////////////////////////////
//• Each node in list is a double-linked LinkedListNode<T>

var myList = new LinkedList<T>()

myList.Count //returns number of elements
myList.First //returns first LinkedListNode<T> or null if list is empty
myList.Last //returns last LinkedListNode<T> or null if list is empty
myList.Clear() //clears the list
myList.Contains(Item) //returns true if list contains the item using linear O(n) search from first
myList.Find(Item) //returns LinkedListNode<T> of node using linear O(n) search from first else null
myList.FindLast(Item) //returns LinkedListNode<T> of node using linear O(n) search from last else null
myList.AddFirst(item) //adds item to start of list; returns LinkedListNode<T> of new node
myList.AddLast(item) //adds item to end of list; returns LinkedListNode<T> of new node
myList.AddBefore(node, item) //adds item before node; returns LinkedListNode<T> of new node
myList.AddAfter(node, item) //adds item after node; returns LinkedListNode<T> of new node
myList.Remove(item) //removes first occurance of item, returns true if item found and successfull removed
myList.RemoveFirst() //removes first item from the list
myList.RemoveLast() //removes last item from the list

////////////////////////////////////////////////////////////////////////////////////////////
//SETS
////////////////////////////////////////////////////////////////////////////////////////////
//• Inheritance: HashSet<T>/SortedSet<T> -> ISet<T> -> ICollection<T> -> IEnumerable<T>
//• Dynamically resizes, memory layout same as std::vector

var myHS = new HashSet<T>() //uses hash based lookup, faster insertion
var mySS = new SortedSet<T>() //values sorted in ascending order, slower insertion

mySet.Count //returns number of elements
mySet.Add(item) //adds item to set, true if item added, false if item already in set
mySet.Clear() //clear all items
mySet.Contains(item) //returns true if item exists
mySet.IsSubsetOf(myContainer) //pass in IEnumerable<T>, returns true if set is subset of container
mySet.Remove(item) //returns true if item found and successfully removed

mySS.Max //returns maximum value in sorted set
mySS.Min //returns mimimum value in sorted set

////////////////////////////////////////////////////////////////////////////////////////////
//STACK
////////////////////////////////////////////////////////////////////////////////////////////

var myStack = new Stack<T>() //last in first out
var myStack = new Stack<T>(20) //allocate reserved space

myStack.Count //returns number of elements
myStack.Clear() //removes all elements
myStack.Contains(item) //returns true if item exists
myStack.Peek() //returns next item in line without removing it
myStack.Pop() //returns and removes item at top of stack
myStack.Push(item) //Inserts item to top of stack

////////////////////////////////////////////////////////////////////////////////////////////
//QUEUE
////////////////////////////////////////////////////////////////////////////////////////////

var myQueue = new Queue<T>() //first in first out
var myQueue = new Queue<T>(20) //allocate reserved space

myQueue.Count //returns number of elements
myQueue.Clear() //removes all elements
myQueue.Contains(item) //returns true if item exists
myQueue.Peek() //returns next item in line without removing it
myQueue.Dequeue() //returns and removes item at beginning of queue
myQueue.Enqueue(item) //adds item to end of queue

////////////////////////////////////////////////////////////////////////////////////////////
//ITERATORS
////////////////////////////////////////////////////////////////////////////////////////////

//CREATING CUSTOM ITERATOR
public class MyIteratorClass<T>
{
    private T[] values = new T[100];
    T someValue = 10;

    //Iterator method
    public IEnumerable<T> GetEnumerator()
    {
        for (int i = 0; i < values.Length; ++i)
        {
            if (i == someValue)
            {
                yield break; //stop the iterating
            }
            yield return values[i]; //return next value
        }
    }
    //Iterator method
    public IEnumerable<T> FirstThree()
    {
        //Using in foreach loop returns next until reaching end
        yield return values[0];
        yield return values[1];
        yield return values[2];
    }
}

//USING CUSTOM ITERATOR
var myObj = new MyIteratorClass<int>();
foreach (int n in myObj.GetEnumerator())
{
    System.Console.Write("{0} ", n); //use n in some way
}
foreach (int n in myObj.FirstThree())
{
    System.Console.Write("{0} ", n); //use n in some way
}