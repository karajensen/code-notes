/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JAVASCRIPT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VARIABLES
// Attempt to access an undeclared variable results in a ReferenceError exception
// Type determined by assignment, undefined if not assigned, type changes with assigning
// Undefined value converts to NaN when used as a number, false when used as a boolean
value = true;         // Global variable
var value = true;     // Local variable to function, rest of function can see even if inside block scope
const value = true;   // Same as var but const, must be initialized
let value = true;     // Local variable to scope, rest of function cannot see

// OPERATORS
x++ / ++x
x ** y                           // x ^ y
x == y                           // equal value only
x === y                          // equal value and equal type
x !== y                          // not equal value or not equal type
value !== null                   // Use === when comparing with null
typeof value !== "undefined"     // Use === when comparing with undefined 

// VARIABLE TYPES
"undefined"
"object"
"string" 
"boolean"
"number"
"function"
    
// CONVERSIONS
myString = myInt.toString();
myString = myInt + "MyString";   // Auto converts and concatenates
myInt = parseInt("8");           // Returns NaN if not a number
myFloat = parseFloat("8.0");     // Returns NaN if not a number
myNumber = (+"8.0")              // Returns NaN if not a number

// ENUMS
MyEnum = {
  ONE: 1,
  TWO : 3,
  THREE : 3
}
var myEnum = myVar.MyEnum.ONE

// CONDITIONALS
if(myInt == n) { }
else if(!(myInt != n) || (myInt < n)) { }
else { }
  
// LOOPS
for (i = 1; i <= n; i++) { break; }
while(bool) { continue; }
do { } while (bool)

// SWITCH STATEMENTS
switch (myString) {
  case "one":
    break;
  case "two":
    break;
  default:
}
switch (myInt) {
  case 0:
    break;
  case 1:
    break;
  default:
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Always pass by value, but for object/arrays, the "value" is a reference to the object
• Changing the value of a variable never changes the underlying primitive or object, 
  it just points the variable to a new primitive or object
• Changing a property of an object referenced by a variable does change the underlying object
• Parameters of functions default to undefined
• 'this' is calling object in a method, use as normal object
**************************************************************************************************************/

// FUNCTION
function fn(a, b) { return 0; } // Return optional, can use 'arguments' array inside fn which holds a/b
fn("MyValue");                  // Any arguments to right not used become null
fn({ a:"MyValue", b:0 });       // Using named arguments

// FUNCTION EXPRESSIONS
var fn = function(value) { return value; };
fn("MyValue");

// NESTED FUNCTION
// Inner function has access to outer variables
function fnOuter(a, b) {
  function fnInner() {
    return a + b;
  }
  return fnInner(a) + fnInner(b);
}

// ARROW FUNCTIONS
// Shorthand way of writing function expression
function(s) { return s.length; } /*or*/ s => s.length

// FUNCTION ARGUMENTS
// iterate through arguments, not an array, but has index/length
function fn(arg1, arg2) {
   for (i = 0; i < arguments.length; i++) {
      console.log(arguments[i])
   }
}

// DEFAULT PARAMETERS
// If no default param, defaults to undefined
function fn(a, b = 0) {
}

// REST PARAMETERS
// Represent an indefinite number of arguments as an array
function fn(value, ...args) {
  args.map(x => console.log(x));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OBJECT / CLASSES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MyClass extends MyBaseClass {

    constructor(value) {
        super(value); // Call base constructor
        this.x = 0;
    }
    
    static staticMethod() {
        return 0;
  }
}

var obj = new MyClass(b);
var obj = null;                   // Null object
var obj = { x: 2, y : 1 };        // Object with properties/attributes
var obj = { "x": 2, "y" : 1 };    // Object with properties/attributes

for (var key in obj) { var x = obj[key]; } // iterate over object property keys
for (var value of obj) { var x = value; } // iterate over object property values
            
obj.x /*or*/ obj["x"];            // Access object properties, key requires "
obj = obj || "default value";     // If null use default value
"x" in obj;                       // returns true if 'x' is a property in myArray
obj instanceof MyClass            // Returns true if instance of MyClass
    
eval("x = 0;"); // Evaluates JavaScript code represented as a string
uneval(obj) // Creates a string representation of the source code of an Object
eval(uneval(obj)); // Make deep copy of object
delete obj // Delete the object

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ERROR HANDLING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

try {
  throw "My Exception"
  throw { toString: function() { return "My Exception"; } };
}
catch(ex) {
    alert(ex.toString());
    throw ex; // rethrow same exception so console can log it
}
finally {
  return true; // if finally returns, any return used in catch is overridden
}

alert("Message");
console.log("Message");
console.error("Message");

result = prompt("Question Text", "Default Answer");
if(result){ } // result will be null or 0 if cancel clicked

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STRINGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STRING
// Each char is 16-bit unsigned integer (UTF-16) and immutable
str = new String("MyString");
str = "MyString\n";               // Allows using escaped characters
str = `String Template`           // Allows using escaped characters and multiline
str.charAt(index);                // Returns char at index
str.toUpperCase();                // Returns upper case of string
str.toLowerCase();                // Returns lower case of string
str.indexOf("substring");         // Returns first index of or -1 if not found
str.length                        // Number of characters in string
str.replace(str1, str2);          // Replace str1 with str2, returns new string
str.split(",")                    // Returns array of string without seperator
str.slice(start, end)             // Returns string between index [start, end), end optional
str.trim()                        // Returns string, trims whitespace from the beginning and end
str.repeat(count);                // Returns string as str repeated count times
str.substr(start, length);        // Returns string, length optional, start is index
str.substring(start, end);        // Returns string, end optional, start/end are index
str.concat(str1, str2);           // Returns string, takes any amount of strings and adds them
str.includes(str1, start);        // Whether str1 is in str, search starts from start index
str.endsWith(str1);               // If ends with str1
str.startsWith(str1);             // If starts with str1
str.lastIndexOf(str1, start);     // Returns index from start index searching backwards
str.indexOf(str1, start);         // Returns index from start index searching forwards
escape(str)                       // Returns new string with escaped version eg. " becomes \"
unescape(str)                     // Returns new string with unescaped version eg. \" becomes "
    
// REGULAR EXPRESSIONS
var regex = /ab+c/; // Literal exp can improve performance
var regex = /ab+c/i; // Literal exp with flags
var regex = new RegExp('ab+c', 'flags'); // flags optional
regex.exec(str) // Tests str and returns string array of matches or null
regex.test(str) // Tests str and returns boolean if match found
regex.source // Regex string

// Regex Flags
g   // Global search
i   // Case-insensitive search
m   // Multi-line search
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAYS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
arr = new Array("a","b", 3.0)
arr = Array("a","b", 3.0)
arr = Array(2)                     // Creates array with size 2, not an item with value 2
arr = ["a","b", 3.0,]              // Last , not needed and ignored
arr = [, ,]                        // Adds undefined for the empty element between , , 
arr[0] = "myEntry"                 // Creates new entry if key doesn't exist
arr["0"] = "myEntry"               // Adds to array object, not actual array list (doesn't affect length)
arr.length                         // Length of array list
arr.concat(arr2)                   // Joins two arrays and returns a new array
arr.join("str")                    // Joins all items using delim and returns a string
arr.push(0)                        // Adds one or more elements to the end of an array, returns arr length
arr.pop()                          // Remove from end of array and return its value
arr.shift()                        // Remove from front of array and return its value
arr.unshift(0)                     // Adds one or more elements to the front of an array, returns arr length
arr.slice(start, end)              // starts at index start and extracts all elements until index end
arr.splice(index, n)               // Remove n items starting from index, returns removed items
arr.splice(index, n, 0, 1)         // Additional args inserted after remove at index
arr.reverse()                      // Reverses array in-place
arr.indexOf(0, start)              // Returns index of first value 0 found from optional start index
arr.lastIndexOf(0, start)          // Returns index of first value 0 found backwards from optional start index
arr.map(x => return x * 2)         // Returns new array from transformed items
arr.filter(x => return true)       // Returns new array from all items that return true
arr.every(x => return true)        // Returns true if all item callbacks return true
arr.some(x => return true)         // Returns true if at least one item callback returns true
arr.reduce(a,b => return a+b)      // Iterates over all elements, returns single combined value
arr.reduceRight(a,b => return a+b) // Iterates over all elements backwards, returns single combined value
    
// SORTING
// Sorts array ascending order in-place
arr.sort()
arr.sort(function(a, b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
})
    
// ITERATING
// Only forEach skips unassigned values, though keeps manual undefined assigned
for (var i = 0; i < arr.length; i++) { var x = arr[i]; } 
arr.forEach(value => var x = value)); 
arr.forEach(function(value) { var x = value; }
    
// DESTRUCTURING
var arr = ['one', 'two', 'three'];
var [one, two, three] = arr // Assign each member to their own variable
var a, b;
[a, ...b] = [1, 2, 3]; // a = 1, b = [2,3]
            
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAPS / SETS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            
            
            
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LIBRARIES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// NUMBER
Number.MAX_VALUE
Number.MIN_VALUE
Number.POSITIVE_INFINITY
Number.NEGATIVE_INFINITY
Number.NaN
Number.EPSILON
Number.MIN_SAFE_INTEGER
Number.MAX_SAFE_INTEGER
Number.isFinite()
Number.isInteger()
Number.isNaN()

// MATHS
Math.max(a,b)
Math.min(a,b)
Math.abs(a)
Math.random() // random number [0, 1)
Math.PI
Math.ceil(a)
Math.floor(a)
Math.round(a)
Math.sign(a)
Math.sqrt(a)
Math.sin(a) // Radians
Math.cos(a) // Radians
Math.tan(a) // Radians
Math.pow(a,n) // aⁿ
    
// DATE
var date = new Date(); // Current day/time
var date = new Date(1995, 11, 25);
var date = new Date(1995, 11, 25, 13, 30, 0);
var date = new Date("December 25, 1995");
var date = new Date("December 25, 1995 13:30:00");
date.getTime();
date.setTime(Date.parse("December 25, 1995"));
date.getMonth(); // Returns 11
date.getFullYear(); // Returns 1995
date.setFullYear(1995);
date.getHours()
date.getMinutes()
date.getSeconds()
  
// JAVASCRIPT OBJECT NOTATION (JSON)
JSON.parse('{"x":1, "y":0}'); // Creates object with properties x/y
JSON.stringify( {x: 1, y: 0 })); // Outputs string "{"x":1,"y":0}"
