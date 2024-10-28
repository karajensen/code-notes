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
let x: boolean = true;
let x: number = 100;               // All numbers are floating or bigint
const x: number = "str";           // BAD Assigning string to number gives error (accepted in Javascript)
let x = 10;                        // Auto adds the ': number' with first assignment

// UNKNOWN
let x: unknown;                    // Type not initially known but still requires type checking
(x as number[]).length             // Requires calling methods with explicit type

// ARRAYS
let x: string[] = ['x', 'y']; 
let x = [1, 2, 3, 'x'];            // Type set to array of numbers and strings only

// OBJECTS
let obj: {};                       // Empty object
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
// Allow specifying function type
function fn(x: number, y: number) {
   return x + y;
}
function fn() : MyObj {
  return {
    str: "str",
    value: 1.0
  };
}

// ARROW FUNCTIONS
let fn : (x: string) => string;
fn = function (x: string) { return "str"};

// TUPLE










