/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JAVASCRIPT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VARIABLE MODIFIERS
// Attempt to access an undeclared variable results in a ReferenceError exception
// Type determined by assignment, undefined if not assigned, type changes with assigning
// Undefined value converts to NaN when used as a number, false when used as a boolean
value = true;         // Global variable
var value = true;     // Local variable to function, rest of function can see even if inside block scope
const value = true;   // Same as var but const, must be initialized
let value = true;     // Local variable to scope, rest of function cannot see

// VARIABLE COMPARISON
x === y                           // equal value and equal type
x !== y                           // not equal value or not equal type
value !== null                    // Use === when comparing with null
typeof value !== "undefined"      // Use === when comparing with undefined
typeof value === "string" 
    
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
for (var key in arr) { var x = arr[key]; } // safe way to iterate, using i++ may create key
for (var value of arr) { var x = value; } // iterate over values
for (var key in obj) { var x = obj[key]; } // iterate over object property keys
for (var value in obj) { var x = value; } // iterate over object property values

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
// STRINGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

str = new String("MyString");
str = "MyString\n";               // Allows using escaped characters
str = `String Template`           // Allows using escaped characters and multiline
str.toUpperCase();                // Returns upper case of string
str.toLowerCase();                // Returns lower case of string
str.indexOf("substring");         // Returns first index of or -1 if not found
str.length                        // Number of characters in string
str.substr(0, 3);                 // Generate substring from index 0 to 3
str.replace(str1, str2);          // Replace str1 with str2, returns new string
str.split(",")                    // Returns array of string without seperator
str.slice(start, end)             // Index to [start, end), end optional
  
escape("str")   // Returns new string with escaped version eg. " becomes \"
unescape("str") // Returns new string with unescaped version eg. \" becomes "
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAYS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
myArray = new Array();
myArray = ["a","b","c",];         // Last , not needed and ignored
myArray = [, ,];                  // Adds undefined for the empty element between , ,
myArray.length 
myArray[0] = "myEntry";
myArray["one"] = 2.0;             // creates new entry if key doesn't exist
"one" in myArray                  // returns true if 'one' is a key in myArray

// Remove key from array
var index = myArray.indexOf(key); // returns -1 if cannot find key
if (index > -1) {
    myArray.splice(index, n);     // number of keys to remove
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

obj = null;                       // Null object
obj = { x: 2, y : 1 };            // Object with properties/attributes
obj = { "x": 2, "y" : 1 };        // Object with properties/attributes
obj.x /*or*/ obj["x"]             // Access object attributes, key requires "
obj = obj || "default value";     // If null use default value

eval("x = 0;"); // Evaluates JavaScript code represented as a string
uneval(obj) // Creates a string representation of the source code of an Object
eval(uneval(obj)); // Make deep copy of object

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Always pass by value, but for object/arrays, the "value" is a reference to the object
• Changing the value of a variable never changes the underlying primitive or object, 
  it just points the variable to a new primitive or object
• Changing a property of an object referenced by a variable does change the underlying object
• Parameters of functions default to undefined
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
// CLASSES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// No constructors/destructors
function MyClass(b) 
{
    this.myMember = b; 

    this.MyMethod = function(a)
    {
        this.myMember = a;
    }
}
var myObj = new MyClass(b);

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
// LIBRARIES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

isFinite(value); // Determines whether the passed value is a finite number
isNaN(value); // Determines whether a value is NaN or not

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
  
// JAVASCRIPT OBJECT NOTATION (JSON)
JSON.parse('{"x":1, "y":0}'); // Creates object with properties x/y
JSON.stringify( {x: 1, y: 0 })); // Outputs string "{"x":1,"y":0}"
