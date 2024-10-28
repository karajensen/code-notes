/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TYPESCRIPT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Adds type system to Javascript and future features
• Node.js is the environment used to run the TypeScript compiler
• Use VSCode and Live Server for hotloading
• Use NVM for Windows Node.js and NPM management
**************************************************************************************************************/

let x: string = 'str';        // Define type of variable

// OBJECTS
// Define types of an object
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











