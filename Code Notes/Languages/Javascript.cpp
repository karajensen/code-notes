////////////////////////////////////////////////////////////////////////////////////////////////////
//JAVASCRIPT
////////////////////////////////////////////////////////////////////////////////////////////////////

myBool = true;
myInt = 8;
myInt--;
myFloat = 4.0;
myObj = null;
myObj = myObj || "default value";
myObj = { x: 2, y : 1 }           // auto creates object with parameters
var myObj;                        // Makes local to scope (Without becomes global to all)
typeof arg === "string"           // Test if variable is type
typeof x != 'undefined'           // returns bool if true, can use null instead
x === y                           // equal value and equal type
x !== y                           // not equal value or not equal type

// CONVERSIONS
myString = myInt.toString();
myString = 8 + "MyString";       // Auto converts: "8MyString"
myInt = parseInt("8");           // Returns NaN if not a number

// ENUMS
MyEnum = {
  ONE: 1,
  TWO : 3,
  THREE : 3
}
var myEnum = myVar.MyEnum.ONE

// EXCEPTIONS
try 
}
catch(ex) 
    alert(ex.toString());
    throw ex; // rethrow same exception so console can log it
}

// MESSAGING
alert("Message");
console.log("Message"); // requires test for console == null before use
console.error("Message");

// PROMPT BOX
result = prompt("Question Text", "Default Answer");
if(result){ } // result will be null or 0 if cancel clicked

// CONDITIONALS
if(myInt == 10) { }
else if(!(myInt != 10) || (myInt < 4)) { }
else { }
  
// LOOPS
for (i = 1; i <= 100; i++) { }
do { } while (myBoolean)
for (var key in myArray){ var x = myArray[key] } // safe way to iterate, using i++ may create key

//================================================================================================
// STRINGS
//================================================================================================
str = "MyString\n";               // supports escape characters
str = new String("MyString");     
str.toUpperCase();                // Returns upper case of string
str.toLowerCase();                // Returns lower case of string
str.indexOf("substring");         // Returns first index of or -1 if not found
str.length                        // Number of characters in string
str.substr(0, 3);                 // Generate substring from index 0 to 3
str.replace(/_[A-Za-z0-9]*/g,"")  // replace everything after _ with ""
str.replace(str1, str2);          // returns new string
str.split(",")                    // returns array of string without seperator
      
//================================================================================================
// ARRAYS
//================================================================================================
myArray = new Array();
myArray.length 
myArray[0] = "myEntry";
myArray["one"] = 2.0;             // creates new entry if key doesn't exist
"one" in myArray                  // returns true if 'one' is a key in myArray

// Remove key from array
var index = myArray.indexOf(key); // returns -1 if cannot find key
if (index > -1) {
    myArray.splice(index, n);    // number of keys to remove
}

//================================================================================================
// FUNCTIONS
//================================================================================================
function MyFunction(myString, myArg) 
    var localInt = 10;            // Local to function scope, without becomes global
    return myArg + myint;         // All global variables avaliable
}
myArg = MyFunction("MyText", 5);
MyFunction("MyText");            // any arguments to right not used become null
MyFunction({a:"MyText", b:5});   // using named arguments

//================================================================================================
// CLASSES
//================================================================================================
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

//================================================================================================
// LIBRARIES
//================================================================================================
Math.max(a,b)
Math.abs(a)
Math.random()  // random number [0, 1)
