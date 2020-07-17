/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JAVASCRIPT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VARIABLES
// Attempt to access an undeclared variable results in a ReferenceError exception
// Type determined by assignment, undefined if not assigned, type changes with assigning
// Undefined value converts to NaN when used as a number, false when used as a boolean
value = true;         // Global variable
var value = true;     // Hoisted local variable to whole function
const value = true;   // Non-hoisted local variable to scope, must be initialized, can't be changed
let value = true;     // Non-hoisted local variable to scope

// HOISTING
// Hoisted variable declarations (var) are implicitly moved to the top of the function/scope
// Variable initialization is not hoisted
// Function declarations are hoisted with their body
// Function expressions are not hoisted, even if 'var' is used
{ x = 10; { var x = 2; } } /*becomes*/ { var x; x = 10; { x = 2; } }

// OPERATORS
x++ / ++x
x ** y                           // x ^ y
x == y                           // equal value only
x === y                          // equal value and equal type
x !== y                          // not equal value or not equal type
value !== null                   // Use === when comparing with null
typeof value !== "undefined"     // Use === when comparing with undefined 
!!x                              // Forces boolean type for object, 0/null/undefined becomes false

// VARIABLE TYPES
"undefined"
"object"
"string" 
"boolean"
"number"
"function"
    
// CONVERSIONS
myString = myInt.toString();
myString = myInt.toLocaleString(Qt.locale(), 'f', 0)
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
• Return optional- returns 'undefined' otherwise
**************************************************************************************************************/

fn("MyValue");                  // automatically assigns b = null
fn({ a:"MyValue", b:0 });       // Using named arguments

// FUNCTION DECLARACTIONS
// Hoisted to top of scope, body is also hoisted, cannot see variables in parent scope
function fn(a, b) { return 0; }

// FUNCTION EXPRESSIONS
// Non-hoisted to top of scope, even with var, can take reference to variables in parent scope
var fn = function(a, b) { return 0; };

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

// NESTED FUNCTION
// Inner function has reference to outer variables
function fnOuter(a, b) {
  function fnInner() {
    return a + b;
  }
  return fnInner(a) + fnInner(b);
}

// CLOSURES
// Allows keeping variables alive through scope
function outerFn() {
    var value = 2;
    return function innerFn() {
        value = 3;
    };
}
var myFn = outerFn(); // value is kept alive
myFn();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OBJECT / CLASSES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CLASS
class MyClass extends MyBaseClass { // MyBaseClass becomes prototype
    constructor(value) {
        super(value); // Call base constructor
        this.x = 0;
    }
    
    function fn() { }
    get getFn() { return this.x; }
    set setFn(value) { this.x = value; }
    static staticFn() { return 0; }
}

// FUNCTION CLASS
function MyClass(value) { // Constructor Function
    this.x = 0;
    this.fn = function() { }
}
MyClass.prototype = new MyBaseClass(); // Set prototype for all instances

// OBJECTS
var obj = new MyClass(2)
var obj = new Object()
var obj = {}                      // Empty object
var obj = null                    // Null object
var obj = { x: 2, y : 1 }
var obj = { "x": 2, "y" : 1 }
var obj = { fn: function() {} }
var obj = { obj2: { x: 2 } }

obj.x /*or*/ obj["x"]             // Access/create object properties, will create if doesn't exist
obj = obj || "default value"      // If null use default value
"x" in obj                        // If 'x' is a property in obj
obj.hasOwnProperty("x")           // If 'x' is a property in obj, doesn't search prototype chain
obj instanceof MyClass            // Returns true if instance of MyClass
delete obj                        // Delete the object
delete obj.x                      // Delete the object property
Object.getPrototypeOf(obj)        // Returns the prototype of obj
Object.entries(obj)               // Returns array of [key, value] pairs where enumerable is true
Object.values(obj)                // Returns array of property values where enumerable is true
Object.keys(obj)                  // Returns array of property keys where enumerable is true
Object.getOwnPropertyNames(obj)   // Returns array of property keys
Object.assign(dstObj, srcObj)     // Copies enumerable properties from src to dst, return dst
Object.freeze(obj)                // Prevent obj from deleting or changing properties
Object.isFrozen(obj)              // Whether freeze is on the object
Object.seal(obj)                  // Prevent obj from deleting properties
Object.isSealed(obj)              // Whether seal is on the object
    
// OBJECT DEEP COPY
eval("x = 0;")                    // Evaluates JavaScript code represented as a string
uneval(obj)                       // Creates a string representation of the source code of an Object
eval(uneval(obj))                 // Make deep copy of object
    
// ITERATING PROPERTIES
for (var key in obj) { var x = obj[key]; } // iterate over object property keys
for (var value of obj) { var x = value; }  // iterate over object property values

// PROTOTYPE CHAINING
// Inheritance in Javascript where each object has a prototype property of its base, last link is 'null'
// When looking up a property, searches down hierarchy as well, returns first match
MyClass.prototype.x = 2.0 // overshadowed by obj.x if exists, sets for all instances
Object.getPrototypeOf(obj).x = 2.0 // overshadowed by obj.x if exists, sets only for obj
    
// ENUMERABLE PROPERTIES
// Properties automatically enumerable for normal assign/creation
// Non-enumerable do not show in for...in loops
Object.defineProperties(obj, {
    x: { enumerable: true, value: 2 },
    y: { enumerable: false, value: 1 },
});

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
str.split('a').join('b')          // Replace all a with b
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
arr = Array.from(set)              // Create array from a set
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
arr.splice(index, 0, value)        // Remove 0 items starting from index, insert new value at index
arr.reverse()                      // Reverses array in-place
arr.indexOf(0, start)              // Returns index of first value 0 found from optional start index
arr.lastIndexOf(0, start)          // Returns index of first value 0 found backwards from optional start index
arr.map(x => return x * 2)         // Returns new array from transformed items
arr.filter(x => return true)       // Returns new array from all items that return true
arr.every(x => return true)        // Returns true if all item callbacks return true
arr.some(x => return true)         // Returns true if at least one item callback returns true
arr.reduce(a,b => return a+b)      // Iterates over all elements, returns single combined value
arr.reduceRight(a,b => return a+b) // Iterates over all elements backwards, returns single combined value
delete arr[i]                      // Only sets element to undefined, use splice instead to actually remove
    
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
// MAPS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var map = new Map()
map.set('key', 1.0) // Key can be any type
map.size
map.get('key') // Returns value or undefined
map.has('key')
map.delete('key')
map.clear()

// ITERATING
for (var [key, value] of map) {
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SETS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var set = new Set()
set.add(value) // can add any type and have multiple different types
set.has(value)
set.delete(value)
set.size

// ITERATING
for (let item of mySet) {
}
            
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
Math.asin(a) // Radians
Math.acos(a) // Radians
Math.atan(a) // Radians    
Math.atan2(x, y) // Radians            
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
