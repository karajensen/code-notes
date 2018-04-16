/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JAVASCRIPT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VARIABLE MODIFIERS
//• Attempt to access an undeclared variable results in a ReferenceError exception
//• Type determined by assignment, undefined if not assigned
//• Undefined value converts to NaN when used as a number, false when used as a boolean
value = 0;         // Global variable
var value = 0;     // Local variable to function, rest of function can see even if inside block scope
const value = 0;   // Same as var but const
let value = 0;     // Local variable to scope, rest of function cannot see

// VARIABLE COMPARISON
x === y                           // equal value and equal type
x !== y                           // not equal value or not equal type
value !== null                    // Use === when comparing with null
typeof value !== "undefined"      // Use === when comparing with undefined
typeof value === "string" 
  
// OBJECTS
obj = null;                       // Null object
value = { x: 2, y : 1 };          // Object with parameters
obj = obj || "default value";
  
// CONVERSIONS
myString = myInt.toString();
myString = myInt + "MyString";   // Auto converts and concatenates
myInt = parseInt("8");           // Returns NaN if not a number

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
for (i = 1; i <= n; i++) { }
while(bool) { }
do { } while (bool)
for (var key in myArray){ var x = myArray[key] } // safe way to iterate, using i++ may create key

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STRINGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

str = "MyString\n";               // supports escape characters
str = new String("MyString");     
str.toUpperCase();                // Returns upper case of string
str.toLowerCase();                // Returns lower case of string
str.indexOf("substring");         // Returns first index of or -1 if not found
str.length                        // Number of characters in string
str.substr(0, 3);                 // Generate substring from index 0 to 3
str.replace(str1, str2);          // Replace str1 with str2, returns new string
str.split(",")                    // Returns array of string without seperator
str.slice(start, end)             // Index to [start, end), end optional
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAYS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
myArray = new Array();
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
// FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function MyFunction(a, b) { return 0; } // Return optional
MyFunction("MyText");                   // Any arguments to right not used become null
MyFunction({a:"MyText", b:5});          // Using named arguments

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
}
catch(ex) {
    alert(ex.toString());
    throw ex; // rethrow same exception so console can log it
}

alert("Message");
console.log("Message");
console.error("Message");

result = prompt("Question Text", "Default Answer");
if(result){ } // result will be null or 0 if cancel clicked

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LIBRARIES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Math.max(a,b)
Math.abs(a)
Math.random()  // random number [0, 1)
