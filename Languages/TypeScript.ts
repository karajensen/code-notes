/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TYPESCRIPT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Adds type system to Javascript and future features
• Node.js is the environment used to run the TypeScript compiler
• Use VSCode and Live Server for hotloading
• Use NVM for Windows Node.js and NPM management
**************************************************************************************************************/

// VARIABLES
let x: string;                     // Define type of variable  
let x: 'str';                      // String literal, can only hold value 'str'
let x: boolean = true;
let x: number = 100;               // All numbers are floating or bigint
const x: number = "str";           // BAD Assigning string to number gives error (accepted in Javascript)
let x = 10;                        // Auto adds the ': number' with first assignment

// UNKNOWN
let x: unknown;                    // Type not initially known but still requires type checking
(x as number[]).length             // Requires calling methods with explicit type

// ANY
let x: any;                        // Type not known and disable type checking (Javascript)
let x;                             // No type or assignment auto becomes 'any'

// ARRAYS
let x: string[] = ['x', 'y']; 
let x = [1, 2, 3, 'x'];            // Type set to array of numbers and strings only

// TUPLES
let x: [string, number, number?];  // Tuple with 2 arguments and 1 optional argument
x = ['str', 5];

// UNIONS
let x: number | string;            // Allow both number of string but no other type

// ENUMS
enum MyEnum {
    One = 1,    // Normally starts with 0
    Two         // Auto assigned 2
}
MyEnum.One

// OBJECTS
let obj: {};   // Empty object
let obj: {
    str: string;
    value: number;
};

// CLASSES
interface MyObj {
    str: string,
    value: number
};

// FUNCTIONS
function fn(x: number, y: number) : number { return x + y; } 
function fn(x: number | string) { }      // Union as type
function fn(x: MyEnum) { }               // Enum as type
function fn(x: number, y?: number) { }   // Optional parameter, if not set will be undefined, must be last in list
function fn(x: number = 10) { }          // Default values, can be set in any order in list
function fn() : void { }                 // Void for no return, implicit
function fn() : MyObj {
  return {
    str: "str",
    value: 1.0
  };
}

// ARROW FUNCTIONS
let fn : (x: string) => string;
fn = function (x: string) { return "str"};

// TYPE ALIAS
type MyAlias = MyType;
type MyObject = {  // Alias object
  str: string;
  x: number;
};
type MyConcat = MyObject & MyObject2;  // Combining types
let myConcat: MyConcat = {
    str: "str"
    x: 10
    x2: 20
};










